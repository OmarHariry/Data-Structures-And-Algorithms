#pragma once
#include <iostream>
#include <string>
#include <vector>
#include<climits>  
#include <queue>
#include <stack>
using namespace std;


class shortest_path
{
private:

	typedef struct node
	{
		int ID;
		int cost = std::numeric_limits<int>::max();;
		node* parent;
		int time = 0;
	}node;

	typedef struct node_cmp
	{
		bool operator()(const node* a, const node* b) const
		{
			return a->cost > b->cost;
		}
	}node_cmp;





public:
	shortest_path();

};

