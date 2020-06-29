#include <iostream>
#include<vector>
#include"maze.h"
#include<chrono>
#include "shortest_path.h"
using namespace std;
using namespace std::chrono;
int main()
{
	int N = 0;
	
	cout << "please enter N:\n";
	cin >> N;
	int number_of_zeros = N * N;
	vector<vector<int>> input(N, vector<int>(N));
	cout << "please enter values for maze:\n";
	for (int i = 0; i < N; i++) {
		for (int j = 0; j < N; j++)
		{
			cin >> input[i][j];
			number_of_zeros -= input[i][j];
		}
	}
	
	cout << "DFS" << endl;
	maze mymaze_DFS(input, N , number_of_zeros);
	auto start_DFS = high_resolution_clock::now();
	mymaze_DFS.solve_maze("DFS");
	auto stop_DFS = high_resolution_clock::now();
	cout << "\n";
	auto duration_DFS = duration_cast<microseconds>(stop_DFS - start_DFS);

	cout << "Time taken by DFS: "
		<< duration_DFS.count() << " microseconds" << endl;
	cout << "BFS" << endl;
	maze mymaze(input, N , number_of_zeros);
	auto start_BFS = high_resolution_clock::now();
	mymaze.solve_maze("BFS");
	auto stop_BFS = high_resolution_clock::now();
	cout << "\n";
	auto duration_BFS = duration_cast<microseconds>(stop_BFS - start_BFS);

	cout << "Time taken by BFS: "
		<< duration_BFS.count() << " microseconds" << endl;
	cout << "\n";
	shortest_path path;
	
	}