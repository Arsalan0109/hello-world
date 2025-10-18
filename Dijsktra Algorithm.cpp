#include <bits/stdc++.h>
using namespace std;

typedef pair<int,int> p;

class DijkstraAlgo{
    public:
        int n;
        vector<vector<pair<int,int>>> adjList;
    
        Dijkstra(int n){
            this->n=n;
            adjList.resize(n);
        }
    
        void addEdge(int u, int v, int w, bool directed=false){
            adjList[u].push_back({v,w});
            if(!directed){
                adjList[v].push_back({u,w});
            }
        }
    
        pair<int, vector<int>> shortestPath(int start, int end){
            vector<int> dist(n,INT_MAX);
            vector<int> parent(n,-1);
            priority_queue<p,vector<p>,greater<p>> pq;
    
            dist[start]=0;
            pq.push({0,start});
    
            while(!pq.empty()){
                auto [d,u] = pq.top(); 
                pq.pop();
    
                if(d>dist[u]){
                    continue;
                }
    
                for(auto [v,w] : adjList[u]){
                    if(dist[u]+w<dist[v]){
                        dist[v]=dist[u]+w;
                        parent[v]=u;
                        pq.push({dist[v],v});
                    }
                }
            }
    
            vector<int> path;
            for(int v=end; v!=-1; v=parent[v]){
                path.push_back(v);
            }
            reverse(path.begin(),path.end());
            return {dist[end],path};
        }
};

int main(){
    int n,m;
    cout<<"Enter number of nodes and edges: ";
    cin>>n>>m;

    DijkstraAlgo graph(n);

    cout<<"Enter edges and weight (u v w):\n";
    for(int i=0; i<m; i++){
        int u,v,w;
        cin>>u>>v>>w;
        graph.addEdge(u,v,w);
    }

    int start,end;
    cout<<"Enter starting node and ending node: ";
    cin>>start>>end;

    auto [cost,path] = graph.shortestPath(start,end);

    cout<<"Shortest cost: "<<cost<< "\n";
    cout<<"Path: ";
    for(int node : path){
        cout<<node<<" ";
    }
    cout << "\n";

    return 0;
}

// Input:
// Enter number of nodes and edges: 6 8
// Enter edges and weight (u v w):
// 0 1 4
// 0 2 2
// 1 2 5
// 1 3 10
// 2 4 3
// 4 3 4
// 3 5 11
// 4 5 5
// Enter starting and ending node: 0 5

// Output:

// Shortest cost: 10
// Path: 0 2 4 5