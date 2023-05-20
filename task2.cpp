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
T sum(T a)
{
	return a;
}

template < typename T >
T sum(vector<T> a)
{
	T sum = T();
	for (int i = 0; i < a.size(); i++)
	{
		sum += a[i];
	}
	return sum;
}

template < typename T >
T sum(set<T> a)
{
	T sum = T();
	for (auto e : a)
	{
		sum += e;
	}
	return sum;
}

int main()
{
	set<int> s = { 1, 4, 3 };
	cout << sum(s);
}
