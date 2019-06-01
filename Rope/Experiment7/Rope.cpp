#include <bits/stdc++.h>
#include <ext/rope> //header with rope
using namespace std;
using namespace __gnu_cxx; //namespace with rope

int main()
{	
	int n;//number of operations
	scanf("%d", &n);
	
	rope<int> v;//making rope
	for (int i = 0; i < n; i++)
	{
		int type;
		scanf("%d", &type);
		
		if (type == 0)
		{
			int x;
			scanf("%d", &x);
			v.push_back(x);
		}
		
		if (type == 1)
		{
			int l, r;//segment [l; r] to erase
			scanf("%d %d", &l, &r);
			int newPlace;//insert this segment here
			scanf("%d", &newPlace);
			
			int len = r - l + 1;//length of segment
			rope<int> segment = v.substr(l, len);//getting this segment
			v.erase(l, len);//erasing segment
			v.insert(v.mutable_begin() + newPlace, segment);			
		}
		
		if (type == 2)
		{
			int x;
			scanf("%d", &x);
			v.erase(x, 1);
		}
	}
	
	for(auto i: v)
		printf("%d ", i);
	printf("\n");
		
	cerr << "Time elapsed: " << clock() / (double)CLOCKS_PER_SEC << endl;//to measure total time
	return 0;
}
