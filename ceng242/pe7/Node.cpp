#include "Node.h"

// // // THE FRIEND METHODS ARE ALREADY IMPLEMENTED. // // //
// // // // // // // DO NOT CHANGE THEM! // // // // // // //

Node::Node(int id) : id(id) {
    
}

Node::~Node() {
    for(int i = 0; i < children.size(); i++){
        delete children[i];
    }

}

Node::Node(const Node& node) {
    Node* theNode = NULL;
	vector<Node*> stack;
	vector<Node*> stack2;
	Node* temp = NULL;
	int stackIndex = 0, stackSize = 0; 
	this->id = node.getId();
	
	
	for(int i = 0; i < node.children.size(); i++) {
	    stack.push_back(node.children[i]);
	    try{
    	        int newData = node.children[i]->getData();
    	        int newId = node.children[i]->getId();
    	        DataNode* newNode = new DataNode(newId,newData);
    	        this->children.push_back(newNode);
    	        stack2.push_back(newNode);
    	    }
        catch(InvalidRequest e){
    	        int newId = node.children[i]->getId();
    	        Node* newNode = new Node(newId);
    	        this->children.push_back(newNode);
    	        stack2.push_back(newNode);
    	}
	    stackSize++;
	}
	
	while(stackIndex != stackSize){
    	if(!stack.empty()){
    	    theNode = stack[stackIndex];
    	    temp = stack2[stackIndex];
    	    stackIndex++;
    	    for(int j = 0; j < theNode->getChildren().size(); j++){
    	        stack.push_back(theNode->getChildren()[j]);
    	        try{
    	            int newData = theNode->getChildren()[j]->getData();
    	            int newId = theNode->getChildren()[j]->getId();
    	            DataNode* newNode = new DataNode(newId,newData);
    	            *temp += *newNode;
    	            stack2.push_back(newNode);
    	        }
    	        catch(InvalidRequest e){
    	            int newId = theNode->getChildren()[j]->getId();
    	            Node* newNode = new Node(newId);
    	            *temp += *newNode;
    	            stack2.push_back(newNode);
    	        }
    	        stackSize++;
    	    }
    	}   
	}
	
}

int Node::getId() const {
	return id;
}

char Node::getData() const {
	throw InvalidRequest();
}

vector<Node*>& Node::getChildren() {
	return children;
}

void Node::operator+=(Node& childNode) {
	children.push_back(&childNode);
}

Node* Node::operator&(const Node& node) const {
	try{
	    char data = node.getData();
	    int id = node.getId();
	    DataNode* newNode = new DataNode(id,data);
	    return newNode;
	}
	catch(InvalidRequest e){
	    try{
	        char data = this->getData();
	        int id = this->getId();
	        DataNode* newNode = new DataNode(id,data);
	        return newNode;
	    }
	    catch(InvalidRequest ex){
	        int id = node.getId();
	        Node* newNode = new Node(id);
	        return newNode;
	    }
	}
}

// This is already implemented for you, do NOT change it!
ostream& operator<<(ostream& os, const Node& node) {
	try {
		node.getData();
		os << *(DataNode*)&node;
	}
	catch (InvalidRequest e) {
		os << "[" << node.id;
		for (int i = 0; i < node.children.size(); i++)
			os << ", " << *node.children[i];
		os << "]";
	}
	return os;
}

/*************** DataNode *****************/

DataNode::DataNode(int id, char data) : Node(id) , data(data) {
	
}

DataNode::~DataNode() {
    for(int i = 0; i < children.size(); i++){
        delete children[i];
    }

}

DataNode::DataNode(const DataNode& dataNode) : Node(dataNode.getId()) {
    Node* theNode = NULL;
	vector<Node*> stack;
	vector<Node*> stack2;
	Node* temp = NULL;
	int stackIndex = 0, stackSize = 0; 
	this->data = dataNode.getData();
	
	
	for(int i = 0; i < dataNode.children.size(); i++) {
	    stack.push_back(dataNode.children[i]);
	    try{
    	        int newData = dataNode.children[i]->getData();
    	        int newId = dataNode.children[i]->getId();
    	        DataNode* newNode = new DataNode(newId,newData);
    	        this->children.push_back(newNode);
    	        stack2.push_back(newNode);
    	    }
        catch(InvalidRequest e){
    	        int newId = dataNode.children[i]->getId();
    	        Node* newNode = new Node(newId);
    	        this->children.push_back(newNode);
    	        stack2.push_back(newNode);
    	}
	    stackSize++;
	}
	
	while(stackIndex != stackSize){
    	if(!stack.empty()){
    	    theNode = stack[stackIndex];
    	    temp = stack2[stackIndex];
    	    stackIndex++;
    	    for(int j = 0; j < theNode->getChildren().size(); j++){
    	        stack.push_back(theNode->getChildren()[j]);
    	        try{
    	            int newData = theNode->getChildren()[j]->getData();
    	            int newId = theNode->getChildren()[j]->getId();
    	            DataNode* newNode = new DataNode(newId,newData);
    	            *temp += *newNode;
    	            stack2.push_back(newNode);
    	        }
    	        catch(InvalidRequest e){
    	            int newId = theNode->getChildren()[j]->getId();
    	            Node* newNode = new Node(newId);
    	            *temp += *newNode;
    	            stack2.push_back(newNode);
    	        }
    	        stackSize++;
    	    }
    	}   
	}
	
}

DataNode::DataNode(const Node& node, char data) : Node(node), data(data) {
}

char DataNode::getData() const {
	return this->data;
}

// This is already implemented for you, do NOT change it!
ostream& operator<<(ostream& os, const DataNode& dataNode) {
	os << "[" << "(" << dataNode.id << ", \'" << dataNode.data << "\')";
	for (int i = 0; i < dataNode.children.size(); i++)
		os << ", " << *dataNode.children[i];
	os << "]";
	return os;
}

