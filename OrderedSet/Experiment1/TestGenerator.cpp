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
	unordered_set<int> used;//for already used numbers
	for (int i = 0; i < n; i++)
	{
		int type = rng() & 1;
		int k;
		if (type == 0 || size == 0)
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
			select++;
			k = rng() % size;
		}	
		
		printf("%d %d\n", type, k);
	}	
	
	cerr << insert << ' ' << select << endl;
	return 0;
}
