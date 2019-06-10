#include <bits/stdc++.h>
using namespace std;

int main()
{
	int t = 10;
	printf("%d\n", t);
	while(t--)
	{
		int n, m;
		n = 1000000;
		m = 1000000;
		printf("%d %d\n", n, m);
		for (int i = 0; i < n; i++)
			printf("%d ", rand() % 10000);
		printf("\n");
		
		while(m--)
		{
			int type = rand() % 7;
			type++;
			printf("%d ", type);
			int l = rand() % n;
			int r = rand() % n;
			if (l > r)
				swap(l, r);
				
			if (type == 1 || type == 4 || type == 6 || type == 7)
				printf("%d %d\n", l, r);
			else
			{
				if (type == 2 || type == 5)
					printf("%d %d %d\n", l, r, rand() % 10000);
				else
					printf("%d %d %d\n", l, r, rand() % (n - r + l));
			}		
		}
	}
	
	cerr << "Time elapsed: " << clock() / (double)CLOCKS_PER_SEC << endl;
	return 0;
}
