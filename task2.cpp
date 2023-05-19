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

template < typename T >
concept Req =
requires (T a, T b)
{
	{a < b} -> std::same_as<bool>;
};

template < typename T >
requires Req<T>
class Node
{
public:
	T value;
	Node<T>* left = nullptr;
	Node<T>* right = nullptr;

	Node<T>(T val)
	{
		value = val;
	}
};

template < typename T >
void add(T x, Node<T>* root)
{
	if (root->value == x)
	{
		if (!root->right)
		{
			root->right = new T(x);
			return;
		}
		add(x, root->right);
		return;
	}

	if (x < root->value)
	{
		if (!root->left)
		{
			root->left = new T(x);
			return;
		}
		add(x, root->left);
		return;
	}

	if (x > root->value)
	{
		if (!root->right)
		{
			root->right = new T(x);
			return;
		}
		add(x, root->right);
		return;
	}
}

template < typename T >
bool find(T x, Node<T>* root)
{
	if (root->value == x)
	{
		return true;
	}

	if (x < root->value)
	{
		if (!root->left)
			return false;
		return find(x, root->left);
	}
	if (x > root->value)
	{
		if (!root->right)
			return false;
		return find(x, root->right);
	}
}


int main()
{
	
}
