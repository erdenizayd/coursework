
#include "NodeManager.h"

NodeManager::NodeManager() {

}

NodeManager::~NodeManager() {
	for(int i = 0; i < roots.size(); i++){
        delete roots[i];
    }
}

void NodeManager::addRelation(int parent, int child) {
	Node* parentNode = NULL;
	Node* childNode = NULL;
	Node* theNode = NULL;
	vector<Node*> stack;
	int stackIndex = 0, stackSize = 0; 
	for(int i = 0; i < roots.size(); i++) {
	    stack.push_back(roots[i]);
	    stackSize++;
	}
	while(stackIndex != stackSize){
    	if(!stack.empty()){
    	    theNode = stack[stackIndex];
    	    stackIndex++;
    	    if(theNode->getId() == parent) parentNode = theNode;
    	    if(theNode->getId() == child) childNode = theNode;
    	    for(int j = 0; j < theNode->getChildren().size(); j++){
    	        stack.push_back(theNode->getChildren()[j]);
    	        stackSize++;
    	    }
    	}   
	}
	if(parentNode != NULL && childNode != NULL) {
	    int pIndex = -1;
	    int cIndex = -1;
	    *parentNode += *childNode;
	    for(int i = 0; i < roots.size(); i++){
	        if(roots[i]->getId() == child) cIndex = i;
	    }
	    if(cIndex != -1) roots.erase(roots.begin()+cIndex);
	}
	else if (parentNode != NULL) {
	    Node* newNode = new Node(child);
	    *parentNode += *newNode;
	}
	else if (childNode != NULL) {
	    int pIndex = -1;
	    int cIndex = -1;
	    Node* newNode = new Node(parent);
	    roots.push_back(newNode);
	    *newNode += *childNode;
	    for(int i = 0; i < roots.size(); i++){
	        if(roots[i]->getId() == child){
	            cIndex = i;
	            break;
	        }        
	    }
	    if(cIndex != -1) roots.erase(roots.begin()+cIndex);
	}
	else {
	    Node* newParent = new Node(parent);
	    Node* newChild = new Node(child);
	    *newParent += *newChild;
	    roots.push_back(newParent);
	}
	relations.push_back(ParentChildPair(child, parent));
}

void NodeManager::setDataToNode(int id, char data) {
	Node* theNode = NULL;
	Node* parentNode = NULL;
	Node* childNode = NULL;
	vector<Node*> stack;
	int parentId = -1;
	int stackIndex = 0, stackSize = 0; 
	for(int i = 0; i < relations.size(); i++){
	    if(relations[i].id == id) parentId = relations[i].parentId;
	}
	for(int i = 0; i < roots.size(); i++) {
	    stack.push_back(roots[i]);
	    stackSize++;
	}
	while(stackIndex != stackSize){
    	if(!stack.empty()){
    	    theNode = stack[stackIndex];
    	    stackIndex++;
    	    if(theNode->getId() == id) {
    	        childNode = theNode;
    	        break;
    	    }
    	    if(parentId != -1 && theNode->getId() == parentId) parentNode = theNode;
    	    for(int j = 0; j < theNode->getChildren().size(); j++){
    	        stack.push_back(theNode->getChildren()[j]);
    	        stackSize++;
    	    }
    	}   
	}
	
	if(childNode != NULL) {
	    DataNode* newNode = new DataNode(*childNode, data);
	    
	    if(parentNode != NULL) {
	        for(int i = 0; i < parentNode->getChildren().size(); i++){
	            if(parentNode->getChildren()[i]->getId() == id) {
	                parentNode->getChildren()[i] = newNode;
	                break;
	            }
	        }
	        
	    }
	    else{
	        for(int i = 0; i < roots.size(); i++){
	            if(roots[i]->getId() == id){
	                roots[i] = newNode;
	                break;
	            }
	        }
	    }
	    delete childNode;
	    
	}
	else {
	    Node* newNode = new DataNode(id,data);
	    roots.push_back(newNode);
	}
	
}

const Node& NodeManager::getNode(int id) {
	Node* theNode = NULL;
	vector<Node*> stack;
	int stackIndex = 0, stackSize = 0; 
	for(int i = 0; i < roots.size(); i++) {
	    stack.push_back(roots[i]);
	    stackSize++;
	}
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
	
	return *theNode;
}