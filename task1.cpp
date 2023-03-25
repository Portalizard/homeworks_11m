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


using namespace std;

int n = 0;
long long mod = 1e9 + 7;
vector < vector < long long > > mtx;

long long f(int w_a, int w_b, int h_a, int h_b) 
{
    //cout << "RUN\n";
    int sum = 0;
    if (w_b - w_a > 1 and h_b - h_a > 1)
    {
        //cout << "DIVIDE\n";
        // 1 | 2
        // -----
        // 3 | 4
        future < long long > s1 = async(f, w_a, (w_a + w_b) / 2,    h_a, (h_a + h_b) / 2);
        future < long long > s2 = async(f, (w_a + w_b) / 2, w_b,    h_a, (h_a + h_b) / 2);
        future < long long > s3 = async(f, w_a, (w_a + w_b) / 2,    (h_a + h_b) / 2, h_b);
        future < long long > s4 = async(f, (w_a + w_b) / 2, w_b,    (h_a + h_b) / 2, h_b);
        sum = s1.get() + s2.get() + s3.get() + s4.get();
        sum %= mod;
    }
    else
    {
        for (int i = w_a; i < w_b; i++)
        {
            for (int j = h_a; j < h_b; j++)
            {
                sum += mtx[i][j];
                sum %= mod;
            }
        }
    }

    //cout << sum << "\n";
    return sum;
}


int main()
{
    cin >> n;

    mtx.resize(n);

    for (int i = 0; i < n; i++)
    {
        mtx[i].resize(n);
        for (int j = 0; j < n; j++)
        {
            cin >> mtx[i][j];
        }
    }

    future < long long > ft = async(f, 0, n, 0, n);

    cout << ft.get() << "\n";
}