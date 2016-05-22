#pragma once
class Graph
{
private:
	int n;
	int **A;
	void recursivesearch(int start, int target, bool *visited, bool* found);
public:
	Graph(int size = 2);
	~Graph();
	bool isConnected(int, int);
	void addEdge(int x, int y);
	void CreateRandomGraph(int size, int edges);
	void DFS(int, int);
	void Parallel_DFS_OMP(int, int);
	void Parallel_DFS_MPI(int, int);
};

