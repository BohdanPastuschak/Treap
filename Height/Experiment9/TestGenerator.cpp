#include <bits/stdc++.h>
using namespace std;

int main()
{
	int n, m;
	n = 1000000;
	m = 25;
	cout << n << ' ' << m << endl;
	for(int j = 0; j < m; ++j)
	{
		for (int i = 0; i < n; i++)
			cout << rand() % 10000 << ' ';
		cout << endl;
	}
	
	return 0;
}

