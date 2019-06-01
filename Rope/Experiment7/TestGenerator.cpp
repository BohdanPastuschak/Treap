#include <bits/stdc++.h>
using namespace std;

int main()
{
	mt19937 rng(chrono::steady_clock::now().time_since_epoch().count());
	freopen("In.txt", "w", stdout);//write data to file for testing
	
	int n = 10000000;
	int size = 0;
	printf("%d\n", n);
	int insert = 0;
	int replace = 0;
	int erase = 0;
	for (int i = 0; i < n; i++)
	{
		int type = rng() % 100;
		if (type < 60 || size == 0)
		{
			type = 0;
			size++;
			insert++;
			int x = rng() % INT_MAX;			
			printf("%d %d\n", type, x);			
		}
		else
		{
			if (type < 80)
			{
				type = 1;
				replace++;
				int l = rng() % size;
				int r = rng() % size;
				if (l > r)
					swap(l, r);
				int newPlace = rng() % (size - (r - l));
				printf("%d %d %d %d\n", type, l, r, newPlace);		
			}
			else
			{
				type = 2;
				++erase;
				int x = rng() % size;
				--size;
				printf("%d %d\n", type, x);
			}
		}
	}
	
	cerr << insert << ' ' << replace << ' ' << erase << endl;
	return 0;
}
