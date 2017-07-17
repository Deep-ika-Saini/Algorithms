// Implemented on Visual Studio Express 2015
// Used Union-Find as was suggested in one of the answers in the forum

#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <stdlib.h>
#include <time.h>

using namespace std;

// representing an edge
struct Edge
{
	int start;
	int end;
};

// representing a graph
struct Graph
{
	int V, E;			// V = Number of vertices, E = Number of edges
	Edge* edge;			// pointer to an edge
};

// Generates the graph
struct Graph* generate(int v, int e)
{
	Graph* graph = new Graph;
	graph->V = v;
	graph->E = e;
	//generating 'e' number of edges
	graph->edge = new Edge[e];
	return graph;
}

// defines sets in the graph, initially one set for each vertex
struct sets
{
	int parent;
	int rank;
};

// finding the sets
int find(struct sets set[], int i)
{
	if (set[i].parent != i)
		set[i].parent = find(set, set[i].parent);

	return set[i].parent;
}

// joining the sets
void Union(struct sets set[], int x, int y)
{
	int xroot = find(set, x);
	int yroot = find(set, y);

	if (set[xroot].rank < set[yroot].rank)
		set[xroot].parent = yroot;
	else if (set[xroot].rank > set[yroot].rank)
		set[yroot].parent = xroot;

	else
	{
		set[yroot].parent = xroot;
		set[xroot].rank++;
	}
}


// Implememting Karger's minimum cut algorithm
int karger(struct Graph* graph)
{
	// Initialising the graph
	int V = graph->V, E = graph->E;
	Edge *edge = graph->edge;

	struct sets *set = new sets[V];

	// creating V subsets, one for each vertex
	for (int v = 0; v < V; ++v)
	{
		set[v].parent = v;
		set[v].rank = 0;
	}

	int vertices = V;

	// combining vertices till more than 2 vertices are present
	while (vertices > 2)
	{
		int pick = rand() % E;					// picking a random edge out of 'E' edges

												// finding the endpoints of the edge
		int set1 = find(set, edge[pick].start);
		int set2 = find(set, edge[pick].end);

		// if the endpoints are in same set then continue the loop and find another edge 
		if (set1 == set2)
			continue;

		// iff endpoints are in different sets then combine the vertices and decrease the number of vertices
		else
		{
			vertices--;
			Union(set, set1, set2);
		}
	}

	// counting the crossing edges when left with two vertices
	int crossing = 0;
	for (int i = 0; i<E; i++)
	{
		int set1 = find(set, edge[i].start);
		int set2 = find(set, edge[i].end);
		if (set1 != set2)
			crossing++;
	}

	return crossing;
}

// Driver program to test above functions
int main()
{
	int min = 200;				//initializing minimum to 200 

								// For iterating with 500 different seed values
	for (int seeding = 0; seeding < 500; seeding++)
	{
		int v = 200, e = 0, ctr = 0;

		int matrix[200][200];
		for (int i = 0; i < v; i++)
			for (int j = 0; j < v; j++)
				matrix[i][j] = 0;

		ifstream infile;
		infile.open("kargerMinCut.txt");
		string line;

		// Saving from file in an adjacency matrix
		while (getline(infile, line))
		{
			stringstream stream(line);

			int n;
			if (!(stream >> n).fail())
			{
				while (1)
				{
					int m;
					if (!(stream >> m).fail())
					{
						matrix[n - 1][m - 1] = 1;
					}
					if (!stream)
						break;
				}
			}
		}
		infile.close();

		//counting the number of edges
		for (int i = 0; i < v; i++)
		{
			for (int j = 0; j <= i; j++)
			{
				if (matrix[i][j] == 1)
					e++;
			}
		}

		// generating the graph
		struct Graph* graph = generate(v, e);

		//linking the edges with their start and end vertices
		for (int i = 0; i < v; i++)
		{
			for (int j = 0; j <= i; j++)
			{
				if (matrix[i][j] == 1)
				{
					graph->edge[ctr].start = i;
					graph->edge[ctr++].end = j;
				}
			}
		}

		srand(time(NULL));			//for generating seeds

									//comparing and finding the minimum
		int found = karger(graph);
		if (found < min)
			min = found;
	}

	//Printing the minimum cut after testing with 500 seeds
	cout << "The minimum cut is: " << min << endl;
	system("pause");
	return 0;
}