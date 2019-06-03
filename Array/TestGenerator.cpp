#include <bits/stdc++.h>
using namespace std;

int main()
{
	int n, m;
	n = 1000000;
	m = 1000000;
	cout << n << ' ' << m << endl;
	for (int i = 0; i < n; i++)
		cout << rand() % 10000 << ' ';
	cout << endl;
	
	while(m--)
	{
		int type = rand() % 7;
		type++;
		cout << type << " ";
		int l = rand() % n;
		int r = rand() % n;
		if (l > r)
			swap(l, r);
			
		if (type == 1 || type == 4 || type == 6 || type == 7)
			cout << l << ' ' << r << endl;
		else
		{
			if (type == 2 || type == 5)
				cout << l << ' ' << r << ' ' << (rand() % 10000) << endl;
			else
				cout << l << ' ' << r << ' ' << (rand() % (n - (r - l))) << endl;
		}		
	}
	
	//cerr << "Time elapsed: " << clock() / (double)CLOCKS_PER_SEC << endl;
	return 0;
}

