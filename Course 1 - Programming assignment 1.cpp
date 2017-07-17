// This programming assignment has been implemented using VS Express 2015

#include<iostream>
#include<string>

using namespace std;

//The following code snippet finds the maximum out of two numbers and returns the maximum
int max(int num1, int num2)
{
	return num1>num2 ? num1 : num2;
}

//The following function adds the two numbers stored as strings and returns the addition as a string
string add(string a, string b)
{
	string addition = "\0";
	int al = a.length();
	int bl = b.length();
	int l;
	if (al != bl)
	{
		if (al < bl)
		{
			a = string(bl - al, '0') + a;
			l = bl;
		}
		else
		{
			b = string(al - bl, '0') + b;
			l = al;
		}
	}
	else
		l = al;
	int result = 0;
	for (int i = l-1; i>=0; i--)
	{
		int first = a.at(i) - '0';
		int second = b.at(i) - '0';
		result = result + first + second;
		string temp = to_string(result);
		if (temp.length() == 2)
		{
			result = temp.at(0) - '0';
			addition = temp.at(1) + addition;
		}
		else
		{
			result = 0;
			addition = temp.at(0) + addition;
		}
	}
	if (result)
		addition = to_string(result) + addition;
	return addition;
}

//The following block subtracts the two numbers stored as strings and returns the subtraction of the second number from first as a string
string subtract(string a, string b)
{
	string subtraction = "\0";
	int al = a.length();
	int bl = b.length();
	int l;
	if (al != bl)
	{
		if (al < bl)
		{
			a = string(bl - al, '0') + a;
			l = bl;
		}
		else
		{
			b = string(al - bl, '0') + b;
			l = al;
		}
	}
	else
		l = al; 
	int result = 0;
	for (int i = l-1; i >= 0; i--)
	{
		int first = a.at(i) - '0';
		int second = b.at(i) - '0';
		result = first - second - result;
		string temp;
		if (result < 0)
		{
			result = 10 + result;
			temp = to_string(result);
			result = 1;
		}
		else
		{
			temp = to_string(result);
			result = 0;
		}
		subtraction = temp + subtraction;
	}
	return subtraction;
}

//The following code snippet uses recursion to multiply two numbers passed as string
//It implements 'Karatsuba' method of multiplication and returns the answer as string
string karatsuba(string x, string y)
{
	int l1 = x.length();
	int l2 = y.length();
	int l = max(l1, l2);
	string ret;

	//Performs 'Karatsuba' if the length of any of the two numbers is more than 4
	//Else normal multiplication is done
	if (l>4)	
	{
		int r = l / 2;
		int xl = l1 - r;
		int yl = l2 - r;
		string s1 = karatsuba(x.substr(0, xl), y.substr(0, yl));			//First multiplication
		string product1 = s1 + string(2 * r,'0');
		string product2 = karatsuba(x.substr(xl, r), y.substr(yl, r));		//Second multiplication
		string s2 = add(x.substr(0, xl), x.substr(xl, r));
		string s3 = add(y.substr(0, yl), y.substr(yl, r));
		string s4 = karatsuba(s2, s3);										//Third multiplication
		
		//Subtraction step
		string s5 = subtract(s4, s1);
		string s6 = subtract(s5, product2);
		string product3 = s6 + string(r, '0');
		
		//Final addition step
		string ret1 = add(product1, product2);
		ret = add(ret1, product3);
	}
	else
	{
		int i1 = stoi(x);
		int i2 = stoi(y);
		long int ans = i1*i2;
		ret = to_string(ans);
	}
	return ret;
}


int main()
{
	string x, y, z;
	
	//Taking the two input numbers
	cout << "Enter the two integers:\n";
	cout << "Integer 1: ";	cin >> x;
	cout << "Integer 2: ";	cin >> y;
	
	//Performing multiplication
	z = karatsuba(x, y);
	
	//Displaying the result
	cout << "Answer is: " << z << endl;
	system("pause");
	return 0;
}
