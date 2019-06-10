#include <bits/stdc++.h>
using namespace std;
mt19937 rng(chrono::steady_clock::now().time_since_epoch().count());//for fast and uniformly randoming

class Treap
{
private:
	
	struct Node
	{
		int x;//element's value
		int left;//left son
		int right;//right son
		int y;//priotity
		int size;//size of subtree
		bool reversed;//whether subtree should be reversed
		long long sum;//sum in subtree
		int add;//how many should be added to every element in subtre
		int maximum;//maximum in subtree
		int minimum;//minimum in subtree
		
		Node(){};
		
		Node(int _x)
		{
			x = _x;
			sum = _x;
			maximum = _x;
			minimum = _x;
			add = 0;
			left = right = -1;
			size = 1;
			reversed = false;
			y = rng();
		}
	};

	int root;//root of treap
	vector<Node> a;//array, corresponding to this treap
	//-1 always stands for non-existing vertex
	 
	int getSize(int v)
	{
		if (v == -1)
			return 0;
		return a[v].size;
	}

	long long getSum(int v)
	{
		if (v == -1)
			return 0;
		return a[v].sum;
	}
	
	int getMaximum(int v)
	{
		if (v == -1)
			return INT_MIN;
		return a[v].maximum;
	}
	
	int getMinimum(int v)
	{
		if (v == -1)
			return INT_MAX;
		return a[v].minimum;;
	}
		
	void push(int v)//pushing updates from vertex to sons
	{
		if (v == -1)
			return;
		
		if (a[v].reversed == true)
		{	
			if (a[v].left != -1)
				a[a[v].left].reversed ^= 1;//promising to reverse n future
				
			if (a[v].right != -1)
				a[a[v].right].reversed ^= 1;//promising to reverse n future
				
			swap(a[v].left, a[v].right);//swapping sons			
			a[v].reversed = false;
		}
		
		if (a[v].add > 0)
		{
			if (a[v].left != -1)
				a[a[v].left].add += a[v].add;//promising to add in future
			if (a[v].right != -1)
				a[a[v].right].add += a[v].add;//promising to add in future
			
			a[v].x += a[v].add;//updating value
			a[v].sum += a[v].add * (long long) a[v].size;//updating sum
			a[v].maximum += a[v].add;//updating maximum
			a[v].minimum += a[v].add;//updating minimum
			a[v].add = 0;			
		}
	}

	void update(int v)//updating vertex
	{
		if (v == -1)
			return;
		
		push(v);
		push(a[v].left);
		push(a[v].right);
		
		a[v].maximum = max(a[v].x, max(getMaximum(a[v].left), getMaximum(a[v].right)));
		a[v].minimum = min(a[v].x, min(getMinimum(a[v].left), getMinimum(a[v].right)));
		a[v].sum = a[v].x + getSum(a[v].left) + getSum(a[v].right);	
		a[v].size = 1 + getSize(a[v].left) + getSize(a[v].right);	
	}

	int merge(int l, int r)//merging two trees
	{
		if (l == -1)
			return r;
		if (r == -1)
			return l;
		
		push(l);
		push(r);
		
		if (a[l].y > a[r].y)
		{
			//now l should be root
			a[l].right = merge(a[l].right, r);//recursive call
			update(l);//updating root
			return l; 
		}
		else
		{
			//now r should be root
			a[r].left = merge(l, a[r].left);//recursive call
			update(r);//updating root
			return r;
		}	
	}

	pair<int, int> split(int v, int c)//spliting tree on two
	{
		if (v == -1)
			return {-1, -1};
		if (c == 0)
			return {-1, v};
		
		push(v);
		if (getSize(a[v].left) >= c)
		{
			//should split in left subtree
			pair<int, int> res = split(a[v].left, c);
			a[v].left = res.second;
			update(v);
			return {res.first, v};
		}
		else
		{
			//should split in right subtree
			pair<int, int> res = split(a[v].right, c - getSize(a[v].left) - 1);
			a[v].right = res.first;
			update(v);
			return {v, res.second};
		}	
	}
	
	int erase(int l, int len)
	{
		pair<int, int> s = split(root, l);
		pair<int, int> t = split(s.second, len);
		
		root = merge(s.first, t.second);
		return t.first;
	}
		
public:
	
	Treap()
	{
		root = -1;
	}
	
	Treap(int size)
	{
		root = -1;
		a.reserve(size);
	}
	
	Treap(vector<int>& el)//creating treap, corresponding to array
	{
		a.resize(el.size());
		root = -1;
		for (int i = 0; i < (int)el.size(); i++)
		{
			a[i] = Node(el[i]);
			root = merge(root, i);
		}
	}
	
	void reverseSegment(int l, int len)//reverseing segment
	{
		pair<int, int> s = split(root, l);
		pair<int, int> t = split(s.second, len);
		
		a[t.first].reversed ^= 1;
		root = merge(s.first, merge(t.first, t.second));	
	}
	
	void addOnSegment(int l, int len, int value)//add value on segment
	{		
		pair<int, int> s = split(root, l);
		pair<int, int> t = split(s.second, len);
		
		a[t.first].add += value;
		root = merge(s.first, merge(t.first, t.second));	
	}	

	long long sumOnSegment(int l, int len)//find sum on segment
	{
		pair<int, int> s = split(root, l);
		pair<int, int> t = split(s.second, len);
		
		long long result = a[t.first].sum;
		root = merge(s.first, merge(t.first, t.second));	
		return result;
	}

	void replaceSegment(int l, int len, int newPlace)//replacing segment
	{
		int seg = erase(l, len);
		pair<int, int> s = split(root, newPlace);
		root = merge(s.first, merge(seg, s.second));		
	}	

	void cyclicShiftOfSegment(int l, int len, int shift)//cyclic shyft
	{
		shift %= len;
		pair<int, int> s = split(root, l);
		pair<int, int> t = split(s.second, len);
		
		pair<int, int> parts = split(t.first, shift);
		root = merge(s.first, merge(merge(parts.second, parts.first), t.second));
	}	
	
	int maximumOnSegment(int l, int len)//maximum on segment
	{
		pair<int, int> s = split(root, l);
		pair<int, int> t = split(s.second, len);
		
		int result = a[t.first].maximum;
		root = merge(s.first, merge(t.first, t.second));		
		return result;
	}
	
	int minimumOnSegment(int l, int len)//minimum on segment
	{
		pair<int, int> s = split(root, l);
		pair<int, int> t = split(s.second, len);
		
		int result = a[t.first].minimum;
		root = merge(s.first, merge(t.first, t.second));		
		return result;
	}
};

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
		
		Treap treap(a);
		
		for (int i = 0; i < m; i++)
		{
			int type;
			scanf("%d", &type);
			if (type == 1)
			{
				int l, r;
				scanf("%d %d", &l, &r);
				treap.reverseSegment(l, r - l + 1);
			}
			
			if (type == 2)
			{
				int l, r, value;
				scanf("%d %d %d", &l, &r, &value);
				treap.addOnSegment(l, r - l + 1, value);
			}
			
			if (type == 3)
			{
				int l, r, newPlace;
				scanf("%d %d %d", &l, &r, &newPlace);
				treap.replaceSegment(l, r - l + 1, newPlace);
			}
			
			if (type == 4)
			{
				int l, r;
				scanf("%d %d", &l, &r);
				printf("%lld\n", treap.sumOnSegment(l, r - l + 1));
			}
			
			if (type == 5)
			{
				int l, r, shift;
				scanf("%d %d %d", &l, &r, &shift);
				treap.cyclicShiftOfSegment(l, r - l + 1, shift);
			}
			
			if (type == 6)
			{
				int l, r;
				scanf("%d %d", &l, &r);
				printf("%d\n", treap.maximumOnSegment(l, r - l + 1));
			}
			
			if (type == 7)
			{
				int l, r;
				scanf("%d %d", &l, &r);
				printf("%d\n", treap.minimumOnSegment(l, r - l + 1));
			}
		}		
	}
	
	double time = 	clock() / (double)CLOCKS_PER_SEC;
	double average = time / tests;
	
	cerr << "Time elapsed: " << time << endl;
	cerr << "Average time: " << average << endl;
	return 0;
}
