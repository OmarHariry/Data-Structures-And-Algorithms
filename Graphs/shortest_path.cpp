#include "shortest_path.h"
#include <vector>
#include<climits>  
#include <queue>
#include <stack>
using namespace std;

shortest_path::shortest_path()
{
	int m, n, r, s, d, t; int N = 0, totalcost = 0, totaltime = 0;
	std::priority_queue<node*, std::vector<node*>, node_cmp> Q;
	string shortestPath;



	cout << "please enter amount M:";
	cin >> m;
	if (m <= 0) {
		cout << "Invalid Data Entered";
		exit(0);
	}

	cout << "please enter number of cities:";
	cin >> n;
	if (n <= 0) {
		cout << "Invalid Data Entered";
		exit(0);
	}

	cout << "please enter number of routes:";
	cin >> r;
	if (r <= 0) {
		cout << "Invalid Data Entered";
		exit(0);
	}

	vector<vector<int>> input(r, vector<int>(4));



	cout << "please enter source , destination , time and cost for each route:";
	for (int i = 0; i < r; i++) {
		for (int j = 0; j < 4; j++) {
			cin >> input[i][j];
			if (input[i][j] <= 0) {
				cout << "Invalid Data Entered";
				exit(0);
			}
		}

	}



	cout << "please enter source city: ";
	cin >> s;
	if (s <= 0) {
		cout << "Invalid Data Entered";
		exit(0);
	}

	cout << "please enter destination city:";
	cin >> d;
	if (d <= 0) {
		cout << "Invalid Data Entered";
		exit(0);
	}



	vector<vector<int>> graph(n + 1, vector<int>(n + 1, 0));
	vector<vector<int>> time(n + 1, vector<int>(n + 1, 0));



	vector<node> NodesArr(n + 2);
	//Giving Ids to nodes
	for (int i = 1; i <= n; i++) {
		NodesArr[i].ID = i;
	}



	for (int i = 0; i < r; i++) {

		graph[input[i][0]][input[i][1]] = input[i][2] * input[i][3];
		time[input[i][0]][input[i][1]] = input[i][2];





	}



	///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////





	//Giving Nodes distance from source

	for (int i = 1; i <= n; i++) {
		if ((i != s) && (graph[s][i]) != 0) {
			NodesArr[i].cost = graph[s][i];
			NodesArr[i].time = time[s][i];
			Q.push(&NodesArr[i]);

		}
	}


	///////////////////////////////////////////Algorithm///////////////////////////////////////////////////////////////
	//////////////////////////////////////////loop works until The destination is the top of the queue////////////////////////////////////////////// 
	int f = 0; node* temp = &NodesArr[s];
	while ((!Q.empty()) && (Q.top()->ID != NodesArr[d].ID))
	{
		/////////////////////////////////////////assigning parents////////
		if ((f > 0) && (graph[Q.top()->ID][temp->ID] != 0))
		{
			Q.top()->parent = temp;

		}
		node* a = Q.top();
		f++;
		////////////////////////making source as a first parent//////////////////////////////////////////////////////
		if (f == 1)
		{
			Q.top()->parent = &NodesArr[s];

		}
		temp = Q.top();
		Q.pop();
		////////////////////////////////////////////////////////relaxing///////////////////////////////////////////////////////////////////////
		for (int i = 1; i <= n; i++) {
			if (((i != temp->ID) && (graph[temp->ID][i]) != 0) && (temp->parent != nullptr)) {

				if (((graph[temp->ID][i]) != 0) && ((graph[temp->parent->ID][i]) > ((graph[temp->ID][i]) + (graph[temp->parent->ID][temp->ID]))))
					NodesArr[i].cost = graph[temp->ID][i];
				NodesArr[i].time = time[temp->ID][i];


			}
		}


	}

	////////////////////////////////////////////extracting destination node////////////////////////////////////////
	if (graph[temp->ID][d] == 0)cout << "NO PATH FOUND";
	else
	{
		NodesArr[d].cost = graph[temp->ID][d];
		system("cls");
		cout << "The route with minimum cost is";
		cout << "\n";
		cout << NodesArr[s].ID;
		cout << "->";



		stack<node> route;

		route.push(*temp);
		////////////////////////////////////printing

		while (temp->parent != NULL)
		{

			route.push(*temp->parent);
			temp = temp->parent;


		}

		int k = route.size();

		while (!route.empty())
		{
			if ((route.top().ID == NodesArr[d].ID) || (route.top().ID == NodesArr[s].ID)) {
				route.pop();
				continue;

			}
			cout << route.top().ID;
			if (k != 0)
				cout << "->";
			k--;
			if (route.top().ID != NodesArr[s].ID) {
				totaltime = totaltime + route.top().time;
				totalcost = totalcost + route.top().cost;

			}
			if (route.top().ID != NodesArr[d].ID) {
				totaltime = totaltime + 1;



			}

			route.pop();
		}


		cout << NodesArr[d].ID;

		totaltime = totaltime + NodesArr[d].time;
		totalcost = totalcost + totaltime * m + NodesArr[d].cost;
		cout << "\n";

		cout << "Total time: ";
		cout << totaltime;
		cout << " hours";
		cout << "\n";

		cout << "Total cost: ";

		cout << totalcost;
		cout << "$";



	}
}
