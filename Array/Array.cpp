
#include <bits/stdc++.h>
using namespace std;

int main()
{
	int tests;
	scanf("%d", &tests);
	for(int test = 0; test < tests; ++test)
	{
		int n, m;
		scanf("%d %d", &n, &m);
		vector<int> a(n);
		for (int i = 0; i < n; i++)
			scanf("%d", &a[i]);
		
		for (int t = 0; t < m; t++)
		{
			int type;
			scanf("%d", &type);
			
			if (type == 1)
			{
				int l, r;
				scanf("%d %d", &l, &r);
				for(int i = l, j = r; i < j; i++, j--)
					swap(a[i], a[j]);
			}
			
			if (type == 2)
			{
				int l, r, value;
				scanf("%d %d %d", &l, &r, &value);
				for (int i = l; i <= r; i++)
					a[i] += value;
			}
			
			if (type == 3)
			{
				int l, r, newPlace;
				scanf("%d %d %d", &l, &r, &newPlace);
				
				vector<int> tut(r - l + 1);
				for(int i = l; i <= r; ++i)
					tut[i - l] = a[i];
					
				vector<int> b(n - (r - l + 1));
				for(int i = 0; i < l; ++i)
					b[i] = a[i];
				for(int i = r + 1; i < n; ++i)
					b[i - (r - l + 1)] = a[i];
				
				a = b;
				b.resize(n);
				for(int i = newPlace; i < newPlace + (r - l + 1); ++i)
					b[i] = tut[i - newPlace];
				
				for(int i = newPlace; i < (int)a.size(); ++i)
					b[i + (r - l + 1)] = a[i];
					
				a = b;
			}
			
			if (type == 4)
			{
				int l, r;
				scanf("%d %d", &l, &r);
				
				long long sum = 0;
				for(int i = l; i <= r; ++i)
					sum += a[i];
				
				printf("%lld\n", sum);
			}
		
			if (type == 5)
			{
				int l, r, shift;
				scanf("%d %d %d", &l, &r, &shift);
			
				shift %= (r - l + 1);
				vector<int> b;
				for(int i = l + shift; i <= r; ++i)
					b.push_back(a[i]);
				for(int i = l; i < l + shift; ++i)
					b.push_back(a[i]);
				for(int i = l; i <= r; ++i)
					a[i] = b[i - l];
			}
			
			if (type == 6)
			{
				int l, r;
				scanf("%d %d", &l, &r);
				int mx = INT_MIN;
				for(int i = l; i <= r; ++i)
					mx = max(mx, a[i]);
				printf("%d\n", mx);
			}
			
			if (type == 7)
			{
				int l, r;
				scanf("%d %d", &l, &r);
				int mn = INT_MAX;
				for(int i = l; i <= r; ++i)
					mn = min(mn, a[i]);
				printf("%d\n", mn);
			}
		}
	}
	
	double time = 	clock() / (double)CLOCKS_PER_SEC;
	double average = time / tests;
	
	cerr << "Time elapsed: " << time << endl;
	cerr << "Average time: " << average << endl;
	return 0;
}
