#include <bits/stdc++.h>
using namespace std;

int main()
{
	mt19937 rng(chrono::steady_clock::now().time_since_epoch().count());
	
	int tests = 10;
	printf("%d\n", tests);
	while(tests--)
	{
		int n = 10000000;
		printf("%d\n", n);
		int size = 0;//total size of set now
	
		set<int> used;//for already used numbers
		for (int i = 0; i < n; i++)
		{
			int type = rng() % 100;
			int k;
			
			int percentInsert = 60;
			int percentErase = 30;
			int percentSelect = 5;
			
			if (type < percentInsert || size == 0)
			{
				type = 0;
				k = rng() % INT_MAX;
				while(used.count(k) > 0)
					k = rng() % INT_MAX;
				
				used.insert(k);	
				size++;
			}
			else
			{
				type -= percentInsert;
				if (type < percentErase)
				{
					type = 3;
					k = rng() % INT_MAX;
					k = *used.lower_bound(k);
					used.erase(k);
					size--;
				}
				else
				{
					type -= percentErase;
					if (type < percentSelect)
					{
						type = 1;
						k = rng() % size;
					}
					else
					{
						type = 2;
						k = rng() % INT_MAX;
					}
				}
			}	
			
			printf("%d %d\n", type, k);
		}	
	}
	
	return 0;
}
