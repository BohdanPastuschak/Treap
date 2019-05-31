#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>
#include <ext/pb_ds/tree_policy.hpp>
using namespace std;
using namespace __gnu_pbds;

typedef tree<
int,
null_type,
less<int>,
rb_tree_tag,
tree_order_statistics_node_update>
ordered_set;

int main()
{	
	ordered_set s;//making cartesian tree
	int n;//number of operations
	scanf("%d", &n);
	long long result = 0;//in order to not output many values, 
						 //let's calcutlate only some hash function 
						 //to see whether our results in both programs are equal
	
	for (int i = 0; i < n; i++)
	{
		int type;//type of operation: 0 for insert, 1 for select, 2 for rank, 3 for erase
		scanf("%d", &type);
		if (type == 0)
		{
			int k;//value to insert
			scanf("%d", &k);
			s.insert(k);//inserting new value
		}		
		
		if (type == 1)
		{
			int k;//value to select
			scanf("%d", &k);
			result += *s.find_by_order(k);//selecting k
		}
		
		if (type == 2)
		{
			int k;//value to rank
			scanf("%d", &k);
			result += s.order_of_key(k);//rank of k
		}
		
		if (type == 3)
		{
			int k;//value to erase
			scanf("%d", &k);
			s.erase(k);//erasing value
		}	
	}	
	
	printf("%lld\n", result);
	cerr << "Time elapsed: " << clock() / (double)CLOCKS_PER_SEC << endl;//to measure total time
	return 0;
}
