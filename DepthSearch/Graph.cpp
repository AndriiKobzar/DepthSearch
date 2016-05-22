#include "stdafx.h"
#include "Graph.h"
#include <omp.h>
#include <stdio.h>
#include <iostream>
#include <stack>
#include <stdlib.h>
using namespace std;

Graph::Graph(int size) {
	int i, j;
	if (size < 2) n = 2;
	else n = size;
	A = new int*[n];
	for (i = 0; i < n; i++)
		A[i] = new int[n];
	for (i = 0; i < n; ++i) {

		for (j = 0; j < n; j++) {
			A[i][j] = 0;
		}
	}
}

void Graph::CreateRandomGraph(int size, int edges) {
	int i, j;
	if (size < 2) n = 2;
	else n = size;
	A = new int*[n];
	for (i = 0; i < n; i++)
		A[i] = new int[n];
	for (i = 0; i < n; ++i) {

		for (j = 0; j < n; j++) {
			A[i][j] = 0;
		}
	}
	srand(1000);
	int x, y;
	for (i = 0; i < edges; i++) {
		x = rand() % size;
		y = rand() % size;
		A[x][y] = 1;
	}
}

bool Graph::isConnected(int x, int y) {
	return (A[x][y] == 1);
}

void Graph::addEdge(int x, int y) {
	A[x - 1][y - 1] = 1;
}

void Graph::DFS(int x, int required)
{
	x--;
	required--;
	stack<int> s;
	bool *visited = new bool[n + 1];
	int i;
	for (i = 0; i <= n; i++) {
		visited[i] = false;
	}
	s.push(x);
	visited[x] = true;
	if (x == required) return;
	cout << "Depth first Search starting from vertex ";
	cout << x + 1 << " : " << endl;
	while (!s.empty()) {
		int k = s.top();
		s.pop();

		if (k == required) {
			cout << k + 1 << "Vertex found";
			break;
		}
		cout << k + 1 << " ";
		for (i = n; i >= 0; i--) {
			if (isConnected(k, i) && !visited[i]) {
				s.push(i);
				visited[i] = true;
			}
		}
	}
	cout << endl;
	delete[] visited;
}

void Graph::Parallel_DFS_OMP(int start, int target) {
	start--;
	target--;
	bool *visited = new bool[n + 1];
	int i;
	for (i = 0; i <= n; i++) {
		visited[i] = false;
	}
	bool found = false;
	recursivesearch(start, target, visited, &found);
}

void Graph::Parallel_DFS_MPI(int start, int target) {
	start--;
	target--;
	bool *visited = new bool[n + 1];
	int i;
	for (i = 0; i <= n; i++) {
		visited[i] = false;
	}
	bool found = false;
	recursivesearch(start, target, visited, &found);
}

void Graph::recursivesearch(int start, int target, bool *visited, bool* found) {
	visited[start] = true;
	if (start == target) {
		cout << start + 1 << " target found" << endl;
		*found = true;
		return;
	}
	cout << " " << start + 1 << " ";

#pragma omp parallel for
	for (int i = 0; i < n; i++) {
		if (A[start][i] == 1 && !visited[i] && !(*found)) {
			{
				recursivesearch(i, target, visited, found);
			}
		}

	}
}

Graph::~Graph()
{
	for (int i = 0; i < n; ++i) {
		delete[] A[i];
	}
	delete[] A;
}
