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

struct User {
    mutex balance_mutex, name_mutex;

    string id;
    string username;
    int balance;

    void set_name(string _name)
    {
        name_mutex.lock();
        username = _name;
        name_mutex.unlock();
    }

    void set_balance(int _balance) {
        balance_mutex.lock();
        balance = _balance;
        balance_mutex.unlock();
    }

    string get_username()
    {
        name_mutex.lock();
        return username;
        name_mutex.unlock();
    }

    int get_balance()
    {
        balance_mutex.lock();
        return balance;
        balance_mutex.unlock();
    }
};