#include "Graph.h"

/*Do not add new libraries or files*/


Graph::Graph() {
    _ver = 0;
    _edge = 0;
    firstkey = 0;
}

Graph::Graph(const Graph& rhs) {
    _ver = rhs._ver;
    _edge = rhs._edge;
    firstkey = rhs.firstkey;
    adjList = rhs.adjList;

}

Graph& Graph::operator=(const Graph& rhs) {
    _ver = rhs._ver;
    _edge = rhs._edge;
    firstkey = rhs.firstkey;
    adjList = rhs.adjList;

}

Graph::~Graph() {

}


void Graph::addNode(const Node &node) {
    list<Edge> nlist;
    adjList.Insert(node.getVid(),nlist);

    _ver++;


}

void Graph::addConnection(const Node& headNode, const Node& tailNode, int import) {
    Edge newedge(tailNode, import);
    adjList.Get(headNode.getVid()).push_back(newedge);
    if(_edge == 0){
        firstkey = headNode.getVid();
    }
    _edge++;

}

list<Node> Graph::getAdjacentNodes(const Node& node) {
    list<Edge>::iterator itr;
    list<Node> result;
    itr = adjList.Get(node.getVid()).begin();
    for( ; itr != adjList.Get(node.getVid()).end(); itr++){
        result.push_back((*itr).getTailNode());
    }
    return result;
}

long Graph::getTotalImports(const Node& node) {
    list<Edge>::iterator itr;
    long result = 0;
    itr = adjList.Get(node.getVid()).begin();
    for( ; itr != adjList.Get(node.getVid()).end(); itr++){
        result += (*itr).getImport();
    }
    return result;
}

void Graph::deleteNode(const Node& node) {
    int *keys;
    keys = new int [_ver];
    adjList.getKeys(keys);

    for(int i = 0; i < _ver; i++){
        if(keys[i] != node.getVid()){
            deleteHelper(node.getVid(), keys[i]);
        }
    }

    adjList.Delete(node.getVid());
    _ver--;
    delete [] keys;

}

void Graph::deleteHelper(int k1, int k2){
    list<Edge>::iterator itr;
    itr = adjList.Get(k2).begin();
    for( ; itr != adjList.Get(k2).end(); itr++){
        if((*itr).getTailNode().getVid() == k1){
            itr = adjList.Get(k2).erase(itr);
        }
    }
}

list<string> Graph::findLeastCostPath(const Node& srcNode, const Node& destNode) {
    priority_queue<Pair,vector<Pair>,myComparator> que;
    HashTable<int,Pair> shortest;

    int *keys;
    keys = new int [_ver];
    adjList.getKeys(keys);

    for(int i = 0; i < _ver; i++){
        shortest.Insert(keys[i],Pair(keys[i],std::numeric_limits<int>::max(),NULL,NULL));
        que.push(Pair(keys[i],std::numeric_limits<int>::max(),NULL,NULL));
    }

    delete [] keys;

    shortest.Insert(srcNode.getVid(), Pair(srcNode.getVid(),0,&srcNode,NULL));
    que.push(Pair(srcNode.getVid(),0,&srcNode,NULL));

    while(!que.empty()){
        Pair top = que.top();
        que.pop();

        try{list<Edge>::iterator itr = adjList.Get(top.key).begin();
        for(;itr != adjList.Get(top.key).end(); itr++){
            long new_distance = itr->getImport() + top.distance;
            if(new_distance < shortest.Get(itr->getTailNode().getVid()).distance){
                shortest.Insert(itr->getTailNode().getVid(), Pair(itr->getTailNode().getVid(), new_distance, &itr->getTailNode(), top.node));
                que.push(Pair(itr->getTailNode().getVid(), new_distance, &itr->getTailNode(), top.node));
            }
        }}
        catch(ItemNotFoundException){};

    }

    list<string> result;
    const Node* temp = shortest.Get(destNode.getVid()).node;

    while(temp != NULL){
        result.push_front(temp->getCountry());
        temp = shortest.Get(temp->getVid()).prev;
    }
    return result;
}

bool Graph::cyclicHelper(int key, HashTable<int,bool> & visited, HashTable<int,bool> & stack) {
    try{
        if(!visited.Get(key)){
            visited.Insert(key,true);
            stack.Insert(key,true);

            list<Edge>::iterator itr;
            for(itr = adjList.Get(key).begin(); itr != adjList.Get(key).end(); itr++){
                if(!visited.Get(itr->getTailNode().getVid()) && cyclicHelper(itr->getTailNode().getVid(), visited, stack)){
                    return true;
                }
                else if(stack.Get(itr->getTailNode().getVid())){
                    return true;
                }
            }
        }
    }
    catch(ItemNotFoundException){}
    stack.Insert(key,false);
    return false;
}

bool Graph::isCyclic() {
    HashTable<int,bool> visited;
    HashTable<int,bool> stack;
    int *keys;
    keys = new int [_ver];
    adjList.getKeys(keys);

    for(int i = 0; i < _ver; i++){
        visited.Insert(keys[i],false);
        stack.Insert(keys[i],false);
    }

    for(int i = 0; i < adjList.Capacity(); i++){
        if(cyclicHelper(keys[i],visited,stack)){
            delete [] keys;
            return true;
        }
    }

    delete [] keys;
    return false;
}


list<string> Graph::getBFSPath(const Node& srcNode, const Node& destNode) {
    queue<Node> que;
    list<string> result;
    HashTable<int,int> visited;
    que.push(srcNode);
    visited.Insert(srcNode.getVid(),1);

    while(que.front().getVid() != destNode.getVid()){
        list<Edge>::iterator itr = adjList.Get(que.front().getVid()).begin();
        result.push_back(que.front().getCountry());
        for(;itr != adjList.Get(que.front().getVid()).end(); itr++){
            try{
                visited.Get(itr->getTailNode().getVid());
            }
            catch(ItemNotFoundException){
                que.push(itr->getTailNode());
                visited.Insert(itr->getTailNode().getVid(),1);
            }
        }
        que.pop();
    }

    result.push_back(destNode.getCountry());
    return result;
}
