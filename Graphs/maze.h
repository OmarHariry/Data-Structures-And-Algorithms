#pragma once
#include<vector>
#include <string>
using namespace std;
class maze
{
private:
	int N;
	vector < bool> visited_locations;
	vector<vector<int>> input_maze;
	int unvisited_nodes;
	vector<int> parents;
	void visit(int i, int j);
	bool visited(int i, int j);
	vector<int> unvisited_neighbours(int i, int j, vector<vector<int>> maze);
	void DFS();
	void BFS();
public:
	void solve_maze(string traversal);
	maze(vector<vector<int>> maze, int N , int number_of_zeros);
};

