#include<iostream>

#include<vector>
#include<set>
#include<queue>

#include"Linkedin_Header.h"
using namespace std;
Graph::Graph(int V)
{
    this->V = V;
    adj = new list<int>[V];
}
void Graph::add_edge(int v, int w)
{
    adj[v].push_back(w); // Add w to v’s list. 
    adj[w].push_back(v); // Add w to v’s list. 
}
vector<int> Graph::BFS(int s, int k)
{
    // Create a queue for BFS 
    set<int>visited;
    queue<pair<int, int>> queue;

    // Mark the current node as visited and enqueue it
    visited.insert(s);
    queue.push(make_pair(s, 0));

    list<int>::iterator i;
    vector<int>ans;
    while (!queue.empty())
    {
        s = queue.front().first;
        int depth = queue.front().second;
        if (depth == k)
        {
            ans.push_back(s);
        }
        queue.pop();
        for (i = adj[s].begin(); i != adj[s].end(); ++i)
        {
            if (visited.count(*i) == 0)
            {
                visited.insert(*i);
                queue.push(make_pair(*i, depth + 1));
            }
        }
    }
    return ans;
}
void Graph::solve()
{
    int vertices, e, u, v, root, k;
    vector<int>ans;
    cout << "please enter number of vertices:" << "\n";
    cin >> vertices;
    cout << "please enter number of edges:" << "\n";
    cin >> e;
    cout << "please enter edges in the form (u  v):" << "\n";
    Graph* graph = new Graph(vertices + 1);
    for (int i = 0; i < e; ++i)
    {
        cin >> u >> v;
        graph->add_edge(u, v);
    }
    cout << "please enter starting vertex:" << "\n";
    cin >> root;
    cout << "please enter value k: " << "\n";
    cin >> k;
    ans = graph->BFS(root, k);
    cout << "There are " << ans.size() << " People with " << k << " connection away starting from " << 4 << "\n";
    cout << "And The People Are: " << "\n";
    for (int x : ans)
        cout << x << " ";
}
