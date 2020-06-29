#include "maze.h"
#include <queue>
#include <iostream>
#include <stack>
//function used mark maze blocks as visited using a simple  
//hash function to store them
//in a 1D boolean array with size of N*N
void maze::visit(int i, int j) {
	visited_locations[i * N + j] = true;
	unvisited_nodes--;
}

//check if a block is visited
bool maze::visited(int i, int j) {
	return visited_locations[i * N + j];
}

//traverse the 4 neighbours of a given block by i and j
//and return the unvisited neighbours in a vector
vector<int> maze::unvisited_neighbours(int i, int j, vector<vector<int>> maze) {

	vector<int> unvisited_neighbours;
	if (j != N - 1 && maze[i][j + 1] == 0 && !visited(i, j + 1)) {
		
		unvisited_neighbours.push_back((i)* N + j + 1);
	}
	if (j != 0 && maze[i][j - 1] == 0 && !visited(i, j - 1)) {
		unvisited_neighbours.push_back(i * N + j - 1);
	}

	if (i != N- 1  && maze[i + 1][j] == 0 && !visited(i+1 , j) ) {
		unvisited_neighbours.push_back((i + 1)*N+j);
	}
	if (i!= 0 && maze[i - 1][j] == 0 && !visited(i - 1, j)) {
		unvisited_neighbours.push_back((i - 1) * N + j);
	}
		return unvisited_neighbours;
}

// Depth First Traversal
void maze::DFS() {
	int i = 0;
	int j = 0;
	parents[0] = -1;
	stack<int> s;
	int new_node;
	//iterate while there is unvisited nodes in the graph 
	// and the end not reached
	while (unvisited_nodes > 0 && !visited(3, 3)) {
		visit(i, j);
		s.push(i * N + j);
		while (!s.empty() && !visited(3, 3)) {
			new_node = s.top();
			// get the neighbours of the current nodes
			vector<int> neighbours = unvisited_neighbours(new_node / N, new_node % N, input_maze);
			//if there is neighbours visit it and add it to stack
			if (!neighbours.empty()) {
				i = neighbours[0] / N;
				j = neighbours[0] % N;
				visit(i, j);
				s.push(i * N + j);
				parents[i * N + j] = new_node;
			}
			else {
				s.pop();
			}


		}

	}

}
// Breadth First Traversal
void maze::BFS() {
	int i = 0;
	int j = 0;
	parents[0] = -1;
	queue<int> q;
	int new_node;
	//iterate while there is unvisited nodes in the graph
	// and the finish block not visited
	while (unvisited_nodes > 0 && !visited(3, 3)) {
		visit(i, j);
		q.push(i * N + j);
		while (!q.empty() && !visited(3, 3)) {
			new_node = q.front();
			q.pop();
			//get all node neighbours and visit the unvisited ones
			vector<int> neighbours = unvisited_neighbours(new_node / N, new_node % N , input_maze);
			for (int k = 0; k < neighbours.size();k++) {
				i = neighbours[k] / N;
				j = neighbours[k] % N;
				visit(i,j);
				q.push(i * N + j);
				parents[i * N + j] = new_node;
	
			}

			
		}

	}	
	
}

void maze::solve_maze(string traversal) {
	stack < pair<int, int> >solution;
	cout << "Solution" << endl;
	//check if start and end are in the path
	if (input_maze[N - 1][N - 1] == 0 && input_maze[0][0] == 0 ) {
		//choose the traversal according to user input
		if (traversal == "BFS")
			BFS();
		else
			DFS();
		//if last element have a parent
		//then there is a path to the end
		if (parents[N*N-1] != -1)
		{ 
			int i = N * N - 1;
			
			pair<int, int> maze_block(3, 3);
			solution.push(maze_block);
			//getting the path from parents array
			while (i > 0) {
				maze_block.first = parents[i] / N;
				maze_block.second = parents[i] % N;
				solution.push(maze_block);	i = parents[i];
			}
			//printing the path
			while (!solution.empty()) {
				cout << "( " << solution.top().first << " , " << solution.top().second << " )" << endl;
				solution.pop();
			}
		}
		else {
			cout << "NO PATH FOUND" << endl;

		}
	}
	else {
		cout << "NO PATH FOUND" << endl;
	}
}
//maze constructor which take 2D vector for maze
// and number of rows or coloumns
// and number of valiid blocks to traverse
maze::maze(vector<vector<int>> maze, int n, int number_of_zeros)
{
	N = n;
	vector<bool> new_visited_locations(N * N, false);
	visited_locations = new_visited_locations;
	input_maze = maze;
	unvisited_nodes = number_of_zeros;
	vector<int> new_parents(N * N, -1);
	parents = new_parents;
}
