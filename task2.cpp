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

pair < int, int > rfactorial(int s){
    pair < int, int > ans;
    int x = rand() % 100;
    long long f = 1;
    for (int i = 2; i < x; i++){
        f *= i;
        f %= (int)1e9 + 7;
    }
    ans.first = x;
    ans.second = f;
    return ans;
}

int main(){
    int n, s;
    cin >> n >> s;

    srand(s);

    vector < future < pair < int, int > > > vec;
    for (int i = 0; i < n; i++){
        future < pair < int, int > > ft = async(rfactorial, s);
        vec.push_back(move(ft));
    }

    for (int i = 0; i < n; i++){
        pair < int, int > out = vec[i].get();
        cout << out.first << " : " << out.second << "\n";
    }
}