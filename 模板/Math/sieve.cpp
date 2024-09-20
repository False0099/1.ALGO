#include<bits/stdc++.h>
using namespace std;


constexpr int N  =1e6+10;
int primes[N], cnt;     // primes[]存储所有素数
bool st[N];         // st[x]存储x是否被筛掉
void get_primes(int n){
    for (int i = 2; i <= n; i ++ ){
        if (!st[i]) primes[cnt ++ ] = i;
        for (int j = 0; primes[j] <= n / i; j ++ ){
            st[primes[j] * i] = true;
            if (i % primes[j] == 0) break;
        }
    }
    st[1]=st[0]=true;
}

vector<int> prime;
auto euler_Prime = [&](int n){
    int cnt=0;
    vector<int> v(n + 1);
    for (int i = 2; i <= n; ++i) {
        if (!v[i]) {
            v[i] = i;cnt+=i;
            prime.push_back(i);
        }
        for (int j = 0; j < prime.size(); ++j) {
            if (prime[j] > v[i] || prime[j] > n / i) break;
            v[i * prime[j]] = prime[j];
            cnt+=prime[j];
        }
    }
    //return sum of 1~n min prime factor
    return cnt; 
};