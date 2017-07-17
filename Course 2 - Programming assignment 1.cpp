//Implemented on Visual Studio Express 2015

#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>

using namespace std;

struct node
{
	int key;
	node *next;
};

typedef vector<int> int_vector;

int t = 0, ctr;
const int v = 875715;
int_vector explored(v), f(v);

// DFS without recursion
// i contains the element passed from DFSLoop
// x=0 is for computing the finishing times
// x=1 is for couting the elements in SCC
void DFS(node *adj_list[v], int i, int x)
{
	node *top = new node();					//top of stack for DFS
	top->key = i;
	top->next = NULL;

	explored[top->key] = 1;
	
	node *temp3 = adj_list[i];				//Pointer for traversing through the adjacency list
	while (top != NULL)						//Looping till stack is empty
	{
		if (temp3 != NULL && explored[temp3->key] == 0)		//if the element in adjaceny list is unexplored
		{
			explored[temp3->key] = 1;
		
			node *temp = new node();
			if (temp == NULL)
			{
				cout << "Can't allocate memory\n";
				exit(0);
			}
			temp->key = temp3->key;
			temp->next = top;
			top = temp;										//adding the vertex on the stack
			temp3 = adj_list[top->key];
		}
		else if (temp3 == NULL || temp3->next == NULL)		//if the adjacency list is empty or there are no more unexplored elements
		{
			t++;
			f[top->key] = t;
			if (x == 1)
			{
				ctr++;										//adding 1 to the current SCC count
			}
			top = top->next;								//removing the vertex from the stack
			if (top == NULL)
				break;
			temp3 = adj_list[top->key];
		}
		//if there are more unexplored elements in the list move to the next element
		else
		{
			temp3 = temp3->next;
		}
	}
}

//x=0 is for computing the finishing times
//x=1 is for couting the elements in SCC
void DFSLoop(node *adj_list[v], int x)
{
	for (int i = v - 1; i >= 1; i--)
	{
		if (explored[i] == 0)
		{
			if (x == 1)
			{
				ctr = 0;
			}
			DFS(adj_list, i, x);
			//Displays the count only if number of vertices in SCC is more than 200
			if (x == 1 && ctr > 200)
				cout << "count " << ctr << endl;
		}
	}
}

int main()
{
	node *adj_list[v];					//Maintaining an adjacency list
	if (adj_list == NULL)
	{
		cout << "Error allocating memory\n";
		exit(0);
	}

	//Initializing all the lists
	for (int i = 0; i < v; i++)
	{
		adj_list[i] = NULL;
		explored[i] = 0;
		f[i] = 0;
	}

	ifstream infile;
	infile.open("SCC.txt");
	if (!infile.is_open())
	{
		cout << "Cannot open file\n";
		exit(0);
	}

	string line;

	//The following code snippet is for initializing adjacency list to the reverse of original graph for the first pass
	while (getline(infile, line))
	{
		int m, n;
		stringstream stream(line);
		stream >> m;
		stream >> n;
		node *temp = new node;
		if (temp == NULL)
		{
			cout << "Error allocating memory\n";
			exit(0);
		}
		temp->key = m;
		temp->next = adj_list[n];
		adj_list[n] = temp;
	}
	infile.close();

	//First pass
	DFSLoop(adj_list, 0);

	//Reinitialising the lists again for the second pass
	for (int i = 0; i < v; i++)
	{
		adj_list[i] = NULL;
		explored[i] = 0;
	}

	infile.open("SCC.txt");
	if (!infile.is_open())
	{
		cout << "Cannot open file\n";
		exit(0);
	}

	//The following code snippet is for initializing adjacency list according to finishing times for the second pass
	while (getline(infile, line))
	{
		int m, n;
		stringstream stream(line);
		stream >> m;
		stream >> n;
		node *temp = new node;
		if (temp == NULL)
		{
			cout << "Error allocating memory\n";
			exit(0);
		}
		temp->key = f[n];
		temp->next = adj_list[f[m]];
		adj_list[f[m]] = temp;
	}
	infile.close();

	//As we only need the top 5 SCCs
	cout << "The SCCs with more than 200 vertices are: \n";
	//Second pass
	DFSLoop(adj_list, 1);

	system("pause");
	return 0;
}
