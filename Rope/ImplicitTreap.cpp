#include <bits/stdc++.h>
using namespace std;
mt19937 rng(chrono::steady_clock::now().time_since_epoch().count());//for fast and uniformly randoming

template <class T>
class ImplicitTreap
{
private:
	
	struct Node
	{
		T x;
		int l, r, y, cnt;
		Node(){};
		
		Node(T _x)
		{
			x = _x;
			l = r = -1;
			cnt = 1;
			y = rand();
		}
	};

	int root;//root of tree
	vector<Node> a;//all nodes

	int getCnt(int v)//count number of vertices in subtree
	{
		if (v == -1)
			return 0;
		return a[v].cnt;
	}

	void update(int v)//updating info about vertex
	{
		if (v == -1)
			return;
		
		a[v].cnt = 1 + getCnt(a[v].l) + getCnt(a[v].r);	
	}

	int merge(int l, int r)//merging two trees
	{
		if (l == -1)
			return r;
		if (r == -1)
			return l;
		
		if (a[l].y > a[r].y)
		{
			a[l].r = merge(a[l].r, r);
			update(l);
			return l; 
		}
		else
		{
			a[r].l = merge(l, a[r].l);
			update(r);
			return r;
		}	
	}

	pair<int, int> split(int v, int c)//splitiing tree on two trees
	{
		if (v == -1)
			return {-1, -1};
		if (c == 0)
			return {-1, v};
		
		if (getCnt(a[v].l) >= c)
		{
			pair<int, int> res = split(a[v].l, c);
			a[v].l = res.second;
			update(v);
			return {res.first, v};
		}
		else
		{
			pair<int, int> res = split(a[v].r, c - getCnt(a[v].l) - 1);
			a[v].r = res.first;
			update(v);
			return {v, res.second};
		}	
	}

	int eraseSegment(int l, int len)//erasing segment [l; l + len)
	{
		pair<int, int> s = split(root, l);
		pair<int, int> t = split(s.second, len);
		root = merge(s.first, t.second);
		return t.first;
	}
	
	void insertSegment(int segmentRoot, int newPlace)//inserting segment on newPlace
	{
		pair<int, int> s = split(root, newPlace);
		root = merge(s.first, merge(segmentRoot, s.second));
	}
	
	vector<T> inorder(int v)//inorder traverse
	{
		if (v == -1)
			return vector<T>();
		
		vector<T> result = inorder(a[v].l);
		result.push_back(a[v].x);
		vector<T> resultRight = inorder(a[v].r);
		
		for(T i: resultRight)
			result.push_back(i);
			
		return result;
	}
	
public:
	
	ImplicitTreap(){root = -1;};
	
	ImplicitTreap(int size)
	{
		root = -1;
		a.reserve(size);
	}
	
	~ImplicitTreap(){};
	
	ImplicitTreap(vector<T>& el)
	{
		a.resize(el.size());
		root = -1;
		for (int i = 0; i < (int)el.size(); i++)
		{
			a[i] = Node(el[i]);
			root = merge(root, i);
		}
	}
	
	void add(T el)
	{
		a.push_back(Node(el));
		root = merge(root, (int)(a.size()) - 1);
	}

	void replaceSegment(int l, int r, int newPlace)
	{
		int segmentRoot = eraseSegment(l, r - l + 1);
		insertSegment(segmentRoot, newPlace);
	}

	vector<T> inorder()
	{
		return inorder(root);
	}
};

int main()
{
	int n;//number of elements in array
	scanf("%d", &n);
	int m;//number of erase & insert operations
	scanf("%d", &m);
	
	ImplicitTreap<int> treap(n);
	for (int i = 0; i < n; i++)
	{
		int x;
		scanf("%d", &x);
		treap.add(x);
	}
	
	for (int i = 0; i < m; i++)
	{
		int l, r;//segment [l; r] to erase
		scanf("%d %d", &l, &r);
		int newPlace;//insert this segment here
		scanf("%d", &newPlace);
		
		treap.replaceSegment(l, r, newPlace);
	}
	
	vector<int> order = treap.inorder();
	for(int i: order)
		printf("%d ", i);
	printf("\n");
		
	cerr << "Time elapsed: " << clock() / (double)CLOCKS_PER_SEC << endl;//to measure total time
	return 0;
}
