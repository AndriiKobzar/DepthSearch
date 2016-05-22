// DepthSearch.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <iostream>
#include <string>
#include <fstream>
#include <Windows.h>
#include "Graph.h"
#include "omp.h"


using namespace std;

int main(int argc, char *argv[], char *envp[])
{
	/*cout << "Enter filepath" << endl;
	string filepath = "";
	cin >> filepath;*/
	ifstream input_stream;
	input_stream.open("D:\\Study\\prog_labs\\pdc\\kursova\\DepthSearch\\Debug\\graph.txt");

	for (int i = 1; i < argc - 1; i++) {
		string value = argv[i];
		if (value == "-o" && i != argc - 1) {
			omp_set_num_threads(stoi(argv[i]));
		}
		if (value == "-m") {

		}
	}

	int size;
	input_stream >> size;
	Graph graph = Graph(size);
	int x;
	int y;
	while (input_stream >> x >> y) {
		graph.addEdge(x, y);
	}
	input_stream.close();
	int start = 1;
	int target = 1;
	cout << "Enter start vertex: ";
	cin >> start;
	cout << "Enter target vertex: ";
	cin >> target;
	
	omp_set_num_threads(2);

	if (argc == 1) {
		int t1 = GetTickCount();
		graph.DFS(start, target);
		int t2 = GetTickCount();
		cout << "Time:" << t2 - t1;
	}
	else if (argc > 1) {
		string mode = argv[1];

		if (mode == "-s") {
			int t1 = GetTickCount();
			graph.DFS(start, target);
			int t2 = GetTickCount();
			cout << "Time:" << t2 - t1;
		}
		else if (mode == "-p") {
			int t1 = GetTickCount();
			graph.Parallel_DFS(start, target);
			int t2 = GetTickCount();
			cout << "Time:" <<t2 - t1;
		}
	}
	return 0;
}

