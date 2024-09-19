#include<bits/stdc++.h>
using namespace std;


inline __int128 read(){
    __int128 x=0,f=1;
    char ch=getchar();
    while(ch<'0'||ch>'9'){
        if(ch=='-')
            f=-1;
        ch=getchar();
    }
    while(ch>='0'&&ch<='9'){
        x=x*10+ch-'0';
        ch=getchar();
    }
    return x*f;
}
inline void write(__int128 x){
    if(x<0){
        putchar('-');
        x=-x;
    }
    if(x>9)
        write(x/10);
    putchar(x%10+'0');
}

namespace my128 { // 读入优化封装，支持__int128 38位
    using i64 = __int128_t;
    i64 abs(const i64 &x) {
        return x > 0 ? x : -x;
    }
    auto &operator>>(istream &it, i64 &j) {
        string val;
        it >> val;
        reverse(val.begin(), val.end());
        i64 ans = 0;
        bool f = 0;
        char c = val.back();
        val.pop_back();
        for (; c < '0' || c > '9'; c = val.back(), val.pop_back()) {
            if (c == '-') {
                f = 1;
            }
        }
        for (; c >= '0' && c <= '9'; c = val.back(), val.pop_back()) {
            ans = ans * 10 + c - '0';
        }
        j = f ? -ans : ans;
        return it;
    }
    auto &operator<<(ostream &os, const i64 &j) {
        string ans;
        function<void(i64)> write = [&](i64 x) {
            if (x < 0) ans += '-', x = -x;
            if (x > 9) write(x / 10);
            ans += x % 10 + '0';
        };
        write(j);
        return os << ans;
    }
} // namespace my128