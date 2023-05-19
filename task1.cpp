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
concept Addable =
requires (T a, T b)
{
	a + b;
};

template < typename T >
requires Addable<T>
T sum(vector < T > a)
{
	T sum = T();
	
	for (int i = 0; i < a.size(); i++)
	{
		sum += a[i];
	}

	return sum;
}


int main()
{
	vector < int > vec = { 1, 2, -3, 4, 5 };
	std::cout << sum<int>(vec);
}
