//This assignment has been implemented on VS Express 2015

#include<iostream>
#include<fstream>

using namespace std;

//To keep track of inversions
long long inv = 0;

//Merges the two arrays and also counts the number of inversions
void merge(int A[], int l, int m, int r)
{
	int i, j, k;
	int n1 = m - l + 1;
	int n2 = r - m;

	int L[50000], R[50000];

	for (i = 0; i < n1; i++)
		L[i] = A[l + i];
	for (j = 0; j < n2; j++)
		R[j] = A[m + 1 + j];

	i = 0;
	j = 0;
	k = l;

	while (i < n1 && j < n2)
	{
		if (L[i] <= R[j])
		{
			A[k] = L[i];
			i++;
		}
		else
		{
			A[k] = R[j];
			j++;
			inv += n1 - i;
		}
		k++;
	}

	while (i < n1)
	{
		A[k] = L[i];
		i++;
		k++;
	}

	while (j < n2)
	{
		A[k] = R[j];
		j++;
		k++;
	}
}

//Sorts the two arrays using the merge sort technique
void mergeSort(int A[], int l, int r)
{
	if (l < r)
	{
		int m = (l + r) / 2;

		mergeSort(A, l, m);
		mergeSort(A, m + 1, r);

		merge(A, l, m, r);
	}
}

int main()
{
	int A[100000], ctr = 0;				//ctr keeps track of the index of the array A in which the numbers are stored
	
	//The following code snippet stores the numbers from file to an array A
	ifstream infile;
	infile.open("IntegerArray.txt");
	int number;
	while (!infile.eof())
	{
		infile >> number;
		A[ctr++] = number;
	}
	infile.close();

	mergeSort(A, 0, 99999);

	cout << "No. of inversions is: " << inv << endl;
	system("pause");
	return 0;
}