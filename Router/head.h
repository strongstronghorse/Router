#pragma once
#include<string>

using namespace std;


struct Vertex
{
	int numRouter;
	string nameRouter;
	
	Edge *adj;
};

struct Edge
{
	int dest;
	string netNum;
	int cost;

	Edge *link;
	Edge() {}
	Edge(int i_dest, string s_netNum, int i_cost)
	{
		dest = i_dest;
		netNum = s_netNum;
		cost = i_cost;
	}
	bool operator!=(const Edge& t)const
	{
		return (dest != t.dest) ? true : false;
	}
};

class Graph
{
public:
	Graph();
	~Graph();
	
protected:
	Vertex *NodeTable;
	int getVertexPos(const int vertex)
	{
		for (int i = 0; i < numVertices; i++)
			if (NodeTable[i].numRouter == vertex)
				return i;
		return -1;
	}

	int numVertices;
	int numEdges;
};