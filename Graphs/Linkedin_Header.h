#pragma once
#include<list>
using namespace std;
class Graph
{
private:
    int V;
    list<int>* adj;
public:
    Graph(int V); 
    void add_edge(int v, int w);
    // prints BFS traversal from a given source s 
    vector<int> BFS(int s, int k);
    void solve();
};