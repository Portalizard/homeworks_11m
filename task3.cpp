#include <iostream>
#include <string>
#include <cmath>
#include <vector>
#include <set>
#include <algorithm>
#include <list>
#include <thread>
#include <mutex>
#include <condition_variable>
#include <random>
#include <future>
#include <chrono>


using namespace std;

// Mysterius function
template < typename T >
T combine(T a, T b)//;
{
	return a + b;
}

template < typename T >
concept Combinable = requires(T a, T b) {
	{combine(a, b)} -> same_as<T>;
};

template < Combinable T >
class Tree
{
public:
	vector<T> tree;

	Tree(vector<T> vec, int root, int tl, int tr);
	void build(vector<T> vec, int root, int tl, int tr);
	void set(int pos, T value, int v, int tl, int tr);
	T get(int l, int r, int root, int tl, int tr);
};

template < Combinable T >
Tree<T>::Tree(vector<T> vec, int root, int tl, int tr)
{
	tree.resize(vec.size() * 4, T());
	build(vec, root, tl, tr);
}

template < Combinable T >
void Tree<T>::build(vector<T> vec, int root, int tl, int tr)
{
	if (tr < tl)
	{
		return;
	}

	if (tl == tr)
	{
		tree[root] = vec[tl - 1];
		return;
	}

	int tm = (tl + tr) / 2;
	build(vec, 2 * root, tl, tm);
	build(vec, 2 * root + 1, tm + 1, tr);

	tree[root] = combine(tree[2 * root], tree[2 * root + 1]);
}

template < Combinable T >
void Tree<T>::set(int pos, T value, int root, int tl, int tr)
{
	if (tr < tl)
		return;

	if (pos < tl or tr < pos)
		return;

	if (tl == tr)
	{
		tree[root] = value;
		return;
	}

	set(pos, value, 2 * root, tl, (tl + tr) / 2);
	set(pos, value, 2 * root + 1, (tl + tr) / 2 + 1, tr);

	tree[root] = combine(tree[2 * root], tree[2 * root + 1]);
}

template < Combinable T >
T Tree<T>::get(int l, int r, int root, int tl, int tr)
{
	if (tr < tl)
		return T();

	if (l <= tl and tr <= r)
	{
		return tree[root];
	}

	if (r < tl or tr < l)
	{
		return T();
	}

	return combine(get(l, r, 2 * root, tl, (tl + tr) / 2), get(l, r, 2 * root + 1, (tl + tr) / 2 + 1, tr));
}

int main()
{
	vector < int > vec = { 1, -3, 3, 4 };
	Tree t(vec, 1, 1, vec.size());
	cout << t.get(1, 2, 1, 1, vec.size()) << "\n";
	t.set(2, 2, 1, 1, vec.size());
	cout << t.get(1, 2, 1, 1, vec.size()) << "\n";
}
