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
T* alloc(T a)
{
	T* ptr = new T();
	*ptr = a;
	return ptr;
}


int main()
{
	
}
