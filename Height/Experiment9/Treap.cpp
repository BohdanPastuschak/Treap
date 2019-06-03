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
		int height;//height of subtree
		Node(){};
		
		Node(int _x)
		{
			x = _x;
			left = right = -1;
			size = 1;
			height = 1;
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

	int getHeight(int v)
	{
		if (v == -1)
			return 0;
		return a[v].height;
	}
	
	void update(int v)//updating vertex
	{
		if (v == -1)
			return;
		
		a[v].height = 1 + max(getHeight(a[v].left), getHeight(a[v].right));
		a[v].size = 1 + getSize(a[v].left) + getSize(a[v].right);	
	}

	int merge(int l, int r)//merging two trees
	{
		if (l == -1)
			return r;
		if (r == -1)
			return l;
		
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
	
	int height()
	{
		return a[root].height;
	}	
};

int main()
{
	int n, m;	
	scanf("%d %d", &n, &m);
	int sum = 0;
	int mx = 0;
	int mn = INT_MAX;
	for(int j = 0; j < m; ++j)
	{
		vector<int> a(n);
		for (int i = 0; i < n; i++)
			scanf("%d", &a[i]);
		
		Treap treap(a);
		int h = treap.height(); 
		sum += h;
		mx = max(mx, h);
		mn = min(mn, h);
	}
	
	printf("%d\n", sum / m);
	printf("%d %d\n", mn, mx);
		
	cerr << "Time elapsed: " << clock() / (double)CLOCKS_PER_SEC << endl;
	return 0;
}


