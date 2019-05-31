#include <bits/stdc++.h>
using namespace std;

int main()
{
	mt19937 rng(chrono::steady_clock::now().time_since_epoch().count());
	freopen("In.txt", "w", stdout);//write data to file for testing
	
	int n = 10000000;
	printf("%d\n", n);
	int size = 0;//total size of set now
	int select = 0;
	int insert = 0;
	int rank = 0;
	int erase = 0;
	set<int> used;//for already used numbers
	for (int i = 0; i < n; i++)
	{
		int type = rng() % 100;//60% - insert, 25% - erase, 10% - select, 5% - rank
		int k;
		if (type < 60 || size == 0)
		{
			type = 0;
			k = rng() % INT_MAX;
			while(used.count(k) > 0)
				k = rng() % INT_MAX;
			
			used.insert(k);	
			size++;
			insert++;
		}
		else
		{
			if (type < 85)
			{
				type = 3;
				k = rng() % INT_MAX;
				k = *used.lower_bound(k);
				used.erase(k);
				size--;
				++erase;
			}
			else
			{
				if (type < 95)
				{
					type = 1;
					select++;
					k = rng() % size;
				}
				else
				{
					type = 2;
					rank++;
					k = rng() % INT_MAX;
				}
			}
		}	
		
		printf("%d %d\n", type, k);
	}	
	
	cerr << insert << ' ' << erase << ' ' << select << ' ' << rank << endl;
	return 0;
}
