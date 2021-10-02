#include "Action.h"
#include "Exception.h"

Action::Action() {
    rootNode = NULL;
}

Action::~Action() {
	if(rootNode != NULL) delete rootNode;
}

/********************** CompleteAction **************************/

CompleteAction::CompleteAction(const Node& node) {
	rootNode = new Node(node);
}

CompleteAction::~CompleteAction() {
	delete rootNode;
}

Node* CompleteAction::act(const Node* node) const {
    Node* newTree = NULL;
	Node* tempNode = new Node(*node);
	Node* theNode;
	vector<Node*> stack;
	vector<Node*> stack2;
	int stackIndex = 0, stackSize = 0;
	stack.push_back(tempNode);
	stackSize++;
	while(stackIndex != stackSize){
	    if(!stack.empty()){
	        Node* temp;
	        theNode = stack[stackIndex];
	        if(newTree == NULL){
	            newTree = (*theNode & *node);
	            stack2.push_back(newTree);
	        }
            temp = stack2[stackIndex];
	        stackIndex++;
	        for(int j = 0; j < theNode->getChildren().size(); j++){
    	        stack.push_back(theNode->getChildren()[j]);
    	        *temp += *(*theNode->getChildren()[j] & *(getHelper(theNode->getChildren()[j]->getId())));
    	        stack2.push_back(temp->getChildren()[j]);
    	        stackSize++;
    	    }
	    }
	}
	stack.clear();
	stack2.clear();
	delete tempNode;
	return newTree;
}

Node* CompleteAction::getHelper(int id) const {
    Node* theNode = NULL;
	vector<Node*> stack;
	int stackIndex = 0, stackSize = 0; 
	stack.push_back(rootNode);
	stackSize++;
	while(stackIndex != stackSize){
    	if(!stack.empty()){
    	    theNode = stack[stackIndex];
    	    stackIndex++;
    	    if(theNode->getId() == id){ 
    	        break;
    	    }
    	    for(int j = 0; j < theNode->getChildren().size(); j++){
    	        stack.push_back(theNode->getChildren()[j]);
    	        stackSize++;
    	    }
    	}   
	}
	
	return theNode;
}

/************************* CutAction ***************************/

CutAction::CutAction(char character) {
	theChar = character;
}

CutAction::~CutAction() {
}

Node* CutAction::act(const Node* node) const {
	Node* newTree = NULL;
	Node* tempNode = new Node(*node);
	Node* theNode;
	vector<Node*> stack;
	vector<Node*> stack2;
	int oldSize = 0, root = 0;
	int stackIndex = 0, stackSize = 0;
	while(1){
    	stack.push_back(tempNode);
    	stackSize++;
    	while(stackIndex != stackSize){
    	    if(!stack.empty()){
    	        Node* temp;
    	        theNode = stack[stackIndex];
    	        if(newTree == NULL /*&& checkHelper(theNode , 0) < 2*/){
    	            try{
    	                int data = theNode->getData();
    	                int id = theNode->getId();
    	                if(checkHelper(theNode,0) < 2) {
    	                    newTree = new DataNode(id,data);
    	                    stack2.push_back(newTree);
    	                    
    	                }
    	                
    	                else{
    	                    
    	                    newTree = new DataNode(id,theChar);
    	                    root = 1;
    	                    break;
    	                }
    	            }
    	            catch(InvalidRequest e){
    	                int id = theNode->getId();
    	                if(checkHelper(theNode,0) < 2) {
    	                    newTree = new Node(id);
    	                    stack2.push_back(newTree);
    	                }
    	                
    	                else{
    	                    
    	                    newTree = new DataNode(id,theChar);
    	                    root = 1;
    	                    break;
    	                }
    	            }
    	        }
                temp = stack2[stackIndex];
    	        stackIndex++;
    	        for(int j = 0; j < theNode->getChildren().size(); j++){
    	            if(checkHelper(theNode->getChildren()[j], 0) < 2){
    	                Node* newNode;
            	        stack.push_back(theNode->getChildren()[j]);
            	        try{
        	                int data = theNode->getChildren()[j]->getData();
        	                int id = theNode->getChildren()[j]->getId();
        	                newNode = new DataNode(id,data);
        	                stack2.push_back(newNode);
        	                *temp += *newNode;
        	            }
        	            catch(InvalidRequest e){
        	                int id = theNode->getChildren()[j]->getId();
        	                newNode = new Node(id);
        	                stack2.push_back(newNode);
        	                *temp += *newNode;
        	            }
            	        stackSize++;
    	            }
    	            else{
    	                DataNode* newNode = new DataNode(theNode->getChildren()[j]->getId(), theChar);
    	                *temp += *newNode;
    	            }
        	    }
    	    }
    	}
    	
    	
    	
    	stack.clear();
    	stack2.clear();
    	delete tempNode;
    	
    	if(root) break;
    	
    	if(oldSize == stackSize) break;
    	else{
    	    tempNode = new Node(*newTree);
    	    delete newTree;
    	    newTree = NULL;
    	    oldSize = stackSize;
    	    stackSize = 0;
    	    stackIndex = 0;
    	}
    }
	
	return newTree;
}

int CutAction::checkHelper(Node* node, int grand) const{
   int result = 0;
   for(int i = 0; i < node->getChildren().size(); i++){
       try{
           if(node->getChildren()[i]->getData() == theChar){
               result++;
        
           }
           if(grand == 0) result += checkHelper(node->getChildren()[i], 1);
       }
       catch(InvalidRequest e){
           if(grand == 0) result += checkHelper(node->getChildren()[i], 1);
       }
   }
   return result;
}

int CutAction::nodeNumber(Node* node) const{
    Node* theNode = NULL;
	vector<Node*> stack;
	int stackIndex = 0, stackSize = 0; 
	for(int i = 0; i < node->getChildren().size(); i++) {
	    stack.push_back(node->getChildren()[i]);
	    stackSize++;
	}
	while(stackIndex != stackSize){
    	if(!stack.empty()){
    	    theNode = stack[stackIndex];
    	    stackIndex++;
    	    for(int j = 0; j < theNode->getChildren().size(); j++){
    	        stack.push_back(theNode->getChildren()[j]);
    	        stackSize++;
    	    }
    	}   
	}
	return stackSize;
}

/************************* CompositeAction ***************************/

CompositeAction::CompositeAction() {
}

CompositeAction::~CompositeAction() {

}

CompositeAction* CompositeAction::addAction(const Action* action) {
	actionList.push_back(action);
	return this;
}

Node* CompositeAction::act(const Node* node) const {
	Node* newNode = NULL;
	Node* tempNode = NULL;
	
	newNode = actionList[0]->act(node);
	//cout << *newNode << endl;
	for(int i = 1; i < actionList.size(); i++){
	    if(tempNode == NULL){
	        tempNode = actionList[i]->act(newNode);
	  //      cout<<*tempNode<<endl;
	        delete newNode;
	        newNode = NULL;
	    }
	    else if(newNode == NULL){
	        newNode = actionList[i]->act(tempNode);
	    //    cout<<*newNode<<endl;
	        delete tempNode;
	        tempNode = NULL;
	    }
	}
	if(tempNode == NULL) return newNode;
	else return tempNode;
}