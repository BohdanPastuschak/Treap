#include <bits/stdc++.h>
using namespace std;

int main()
{
	mt19937 rng(chrono::steady_clock::now().time_since_epoch().count());
	freopen("In.txt", "w", stdout);//write data to file for testing
	
	int n = 1000000;
	int m = 3000000;
	
	printf("%d %d\n", n, m);
	for (int i = 0; i < n; i++)
	{
		int x = rng() % INT_MAX;
		printf("%d ", x);
	}
	
	for (int i = 0; i < m; i++)
	{
		int l = rng() % n;
		int r = rng() % n;
		if (l > r)
			swap(l, r);
			
		int newPlace = rng() % (n - (r - l));
		printf("%d %d %d\n", l, r, newPlace);
	}
	
	return 0;
}
