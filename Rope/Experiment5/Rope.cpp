#include <bits/stdc++.h>
#include <ext/rope> //header with rope
using namespace std;
using namespace __gnu_cxx; //namespace with rope

int main()
{	
	int n;//number of elements in array
	scanf("%d", &n);
	int m;//number of erase & insert operations
	scanf("%d", &m);
	
	rope<int> v;//making rope
	for (int i = 0; i < n; i++)
	{
		int x;
		scanf("%d", &x);
		v.push_back(x);
	}
	
	for (int i = 0; i < m; i++)
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
	
	for(auto i: v)
		printf("%d ", i);
	printf("\n");
		
	cerr << "Time elapsed: " << clock() / (double)CLOCKS_PER_SEC << endl;//to measure total time
	return 0;
}
