#include<bits/stdc++.h>
using namespace std;


int exgcd(int a, int b, int &x, int &y) {
    if (!b) {
        x = 1, y = 0;
        return a;
    }
    int g = exgcd(b, a % b, y, x);
    y -= a / b * x;
    return g;
}
auto calc = [&](int a,int b,int c)->int{
    int x, y, d = exgcd(a, b, x, y);
    if (c % d != 0) {
        return -1;
    }
    return (x*c/d%b/d+b/d)%b/d;
};
//求逆元，要求a与p互质
int inv(int a, int p){
    int x, y;
    exgcd(a, p, x, y);
    return (p + x % p) % p;
}



template <class T> T sign(const T &a) {
    return a == 0 ? 0 : (a < 0 ? -1 : 1);
}
template <class T> T ceil(const T &a, const T &b) {
    T A = abs(a), B = abs(b);
    assert(b != 0);
    return sign(a) * sign(b) > 0 ? (A + B - 1) / B : -A / B;
}
int exgcd(int a, int b, int &x, int &y) {
    if (!b) {
        x = 1, y = 0;
        return a;
    }
    int d = exgcd(b, a % b, y, x);
    y -= a / b * x;
    return d;
}
auto calc = [&](int a, int b, int c) -> void {
    int x, y, d = exgcd(a, b, x, y);
    if (c % d != 0) {
        cout << -1 << endl;
        return;
    }
    x *= c / d, y *= c / d;
    int p = b / d, q = a / d, k;
    if (x < 0) {
        k = ceil(1 - x, p);
        x += p * k;
        y -= q * k;
    }
    else if (x >= 0) { //将x提高到最小正整数
        k = (x - 1) / p;
        x -= p * k; //将x降低到最小正整数
        y += q * k;
    }
    if (y > 0) { //有正整数解
        // cout << (y - 1) / q + 1 <<" "; //将y减到1的方案数即为解的个数
        cout << x << "\n"; //当前的x即为最小正整数x
        // cout << (y - 1) % q + 1 << " "; //将y取到最小正整数
        // cout << x + (y - 1) / q * p << " "; //将x提升到最大
        // cout << y << "\n"; //特解即为y最大值      
    } else { //无整数解
        cout << x << "\n"; //当前的x即为最小的正整数x
        // cout << y + q * ceil(1 - y, q) << endl; //将y提高到正整数
    }
};
