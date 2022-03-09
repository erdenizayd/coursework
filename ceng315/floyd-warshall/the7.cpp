#include "the7.h"

void FindRoute(int n, std::vector<Road> roads, int s, int d, int x, int y) {
  // You can change these variables. These are here for demo only.
    std::vector<int> path;
    int cost = INT_MAX;
  // Write your code here...
    int graph[n][n];
    int dist[n][n];
    int nextnode[n][n];
    int path1, path2;
    int road = roads.size();
    
    for(int i = 0; i < n; i++){
        for(int j = 0; j < n; j++){
            nextnode[i][j] = -1;
            if(i != j) graph[i][j] = INT_MAX;
            else graph[i][j] = 0;
        }
    }   

    
    for(int i = 0; i < road; i++){
        graph[roads[i].endpoints.first][roads[i].endpoints.second] = roads[i].time;
        graph[roads[i].endpoints.second][roads[i].endpoints.first] = roads[i].time;
        nextnode[roads[i].endpoints.first][roads[i].endpoints.second] = roads[i].endpoints.second;
        nextnode[roads[i].endpoints.second][roads[i].endpoints.first] = roads[i].endpoints.first;
    }
    
    for(int i = 0; i < n; i++){
        for(int j = 0; j < n; j++){
            dist[i][j] = graph[i][j];
        }
    }   
    
    for (int k = 0; k < n; k++) {
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < n; j++) {
                if (dist[i][j] > (dist[i][k] + dist[k][j]) && (dist[k][j] != INT_MAX && dist[i][k] != INT_MAX)){
                    dist[i][j] = dist[i][k] + dist[k][j];
                    nextnode[i][j] = nextnode[i][k];
                }
            }
        }
    }
    
    path1 = dist[s][x] + dist[x][y] + dist[y][d];
    path2 = dist[s][y] + dist[y][x] + dist[x][d];
    
    if(path1 < path2){
        int m = s;
        cost = path1;
        path.push_back(m);
        while(m != x){
            m = nextnode[m][x];
            path.push_back(m);
        }
        while(m != y){
            m = nextnode[m][y];
            path.push_back(m);
        }
        while(m != d){
            m = nextnode[m][d];
            path.push_back(m);
        }
    }
    else{
        int m = s;
        cost = path2;
        path.push_back(m);
        while(m != y){
            m = nextnode[m][y];
            path.push_back(m);
        }
        while(m != x){
            m = nextnode[m][x];
            path.push_back(m);
        }
        while(m != d){
            m = nextnode[m][d];
            path.push_back(m);
        }
    }
    

  // Your output should be like this. You can change this as long as you keep
  // the output format. PrintRange function helps you print elements of
  // containers with iteratos (e.g., std::vector).
  std::cout << cost << " ";
  PrintRange(path.begin(), path.end());
  std::cout << std::endl;
}