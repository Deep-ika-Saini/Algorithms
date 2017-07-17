//This programming assignment has been implemented on VS Express 2015

#include <iostream>
#include <fstream>

using namespace std;

int comp1 = 0;
int comp2 = 0;
int comp3 = 0;

int partition(int A[], int l, int r, int pivot, int *comp)
{
	*comp += (r - l);
	int p = A[pivot];
	int i = l + 1;
	for (int j = i; j <= r; j++)
	{
		if (A[j] < p)
		{
			int temp = A[j];
			A[j] = A[i];
			A[i] = temp;
			i++;
		}
	}
	A[pivot] = A[i - 1];
	A[i - 1] = p;
	return (i - 1);
}

void quicksort(int A[], int l, int r, int type)
{
	if (r > l)
	{
		if (type == 1)
		{
			int p = partition(A, l, r, l, &comp1);
			quicksort(A, l, p - 1, 1);
			quicksort(A, p + 1, r, 1);
		}

		else if (type == 2)
		{
			int temp = A[l];
			A[l] = A[r];
			A[r] = temp;
			int p = partition(A, l, r, l, &comp2);
			quicksort(A, l, p - 1, 2);
			quicksort(A, p + 1, r, 2);
		}

		else
		{
			int mid = (r + l) / 2;
			int median;
			if (r - l == 1)
				median = l;
			else if ((A[mid] < A[l] && A[mid] > A[r]) || (A[mid] > A[l] && A[mid] < A[r]))
				median = mid;
			else if ((A[l] < A[mid] && A[l] > A[r]) || (A[l] > A[mid] && A[l] < A[r]))
				median = l;
			else
				median = r;
			int temp = A[l];
			A[l] = A[median];
			A[median] = temp;
			int p = partition(A, l, r, l, &comp3);
			quicksort(A, l, p - 1, 3);
			quicksort(A, p + 1, r, 3);
		}
	}
}

int main()
{
	int A[10000], ctr = 0;
	ifstream infile;
	infile.open("QuickSort.txt");
	int number;
	while (!infile.eof())
	{
		infile >> number;
		A[ctr++] = number;
	}
	infile.close();
	quicksort(A, 0, 9999, 1);
	cout << "Pivot first: " << comp1 << endl;
	
	ctr = 0;
	infile.open("QuickSort.txt");
	while (!infile.eof())
	{
		infile >> number;
		A[ctr++] = number;
	}
	infile.close();
	quicksort(A, 0, 9999, 2);
	cout << "Pivot last: " << comp2 << endl;
	
	ctr = 0;
	infile.open("QuickSort.txt");
	while (!infile.eof())
	{
		infile >> number;
		A[ctr++] = number;
	}
	infile.close();
	quicksort(A, 0, 9999, 3);
	cout << "Pivot median: " << comp3 << endl;
	
	system("pause");
	return 0;
}