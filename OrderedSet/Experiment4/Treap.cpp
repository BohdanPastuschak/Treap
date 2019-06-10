#include <bits/stdc++.h>
using namespace std;
mt19937 rng(chrono::steady_clock::now().time_since_epoch().count());//for fast and uniformly randoming

template <class T>
class Treap
{
private:

	struct Node
	{
		T x;//key
		int y;//priority
		int cnt;//number of nodes in subtree
		Node* left;//left son
		Node* right;//right son
		
		Node(){}
		
		Node(T _x)
		{
			x = _x;
			y = rng();
			cnt = 1;
			left = NULL;
			right = NULL;
		}
	};

	Node* root;//root of tree

	int getCnt(Node* v)//count number of nodes in subtree
	{
		if (v == NULL)
			return 0;
		return v->cnt;
	}

	void update(Node* v)//updating vertex
	{
		if (v == NULL)
			return;
		
		v->cnt = 1 + getCnt(v->left) + getCnt(v->right);
	}

	Node* merge(Node* l, Node* r)//merging trees with roots l and r
	{
		if (l == NULL)
			return r;
		if (r == NULL)
			return l;
		
		if (l->y > r->y)
		{
			l->right = merge(l->right, r);
			update(l);
			return l;
		}
		else
		{
			r->left = merge(l, r->left);
			update(r);
			return r;
		}	
	}

	void split(Node* v, T value, Node*& l, Node*& r)//spliting tree by key 
	{
		if (v == NULL)
		{
			l = NULL;
			r = NULL;
			return;
		}
		
		if (v->x <= value)
		{
			split(v->right, value, v->right, r);
			l = v;
		}
		else
		{
			split(v->left, value, l, v->left); 
			r = v;
		}
		
		update(v);
	}
	
	T select(Node* v, int k)//k-th number
	{
		int count = getCnt(v->left);
		if (count == k)
			return v->x;
		if (count > k)
			return select(v->left, k);
		else
			return select(v->right, k - count - 1);
	}

	int rank(Node* v, T k)//number of keys less than k
	{
		if (v == NULL)
			return 0;
		
		if (v->x == k)
			return v->cnt;
		if (v->x > k)
			return rank(v->left, k);
		else
			return rank(v->right, k) + getCnt(v->left) + 1;
	}
	
	void clear(Node* v)
	{
		if (v == NULL)
			return;
		clear(v->left);
		clear(v->right);
		delete(v);
	}
	
public:

	Treap(){root = NULL;}
	
	~Treap()
	{
		clear(root);
	}
	
	T select(int k)
	{
		return select(root, k);
	}
	
	int rank(T k)
	{
		return rank(root, k);
	}

	void insert(T value)
	{
		if (root == NULL)
		{
			root = new Node(value);
			return;		
		}
		
		Node *l, *r;
		Node* m = new Node(value);
		split(root, value, l, r);
		root = merge(l, merge(m, r));
	}

	void erase(T value)
	{
		Node *l, *r, *m;
		split(root, value - 1 , l, r);
		split(r, value, m, r);
		root = merge(l, r);	
		delete(m);
	}

	T lower_bound(T value)
	{
		return lower_bound(root, value);		
	}
};

int main()
{
	int tests;
	scanf("%d", &tests);
	for(int test = 0; test < tests; ++test)
	{
		Treap<int> treap;//making cartesian tree
		int n;//number of operations
		scanf("%d", &n);
		
		for (int i = 0; i < n; i++)
		{
			int type;//type of operation: 0 for insert, 1 for select, 2 for rank, 3 for erase
			scanf("%d", &type);
			if (type == 0)
			{
				int k;//value to insert
				scanf("%d", &k);
				treap.insert(k);//inserting new value
			}		
			
			if (type == 1)
			{
				int k;//value to select
				scanf("%d", &k);
				printf("%d\n", treap.select(k));//selecting k
			}
			
			if (type == 2)
			{
				int k;//value to rank
				scanf("%d", &k);
				printf("%d\n", treap.rank(k));//rank of k
			}
			
			if (type == 3)
			{
				int k;//value to erase
				scanf("%d", &k);
				treap.erase(k);//erasing value
			}	
		}		
	}
	
	double time = clock() / (double) CLOCKS_PER_SEC;
	double average = time / tests;
	
	cerr << "Time elapsed: " << time << endl;
	cerr << "Average time: " << average << endl;
	return 0;
}
