#include<bits/stdc++.h>
using namespace std;
constexpr int N = 1000010;
int son[N][26],idx,cnt[N];
void insert(string str){
    int p=0;
    for(int i=0;i<str.size();i++){
        int u=str[i]-'a';
        if(!son[p][u]){
            son[p][u]=++idx;
        }
        p=son[p][u];
    }
    cnt[p]++;
}
int query(string str){
    int p=0;
    for(int i=0;i<str.size();i++){
        int u=str[i]-'a';
        if(!son[p][u]){
            return 0;
        }
        p=son[p][u];
    }
    // cnt[p]++;
    return cnt[p];
}


using ll = long long;
const int N = 100010;
struct Trie {
    int ch[N][63], cnt[N], idx = 0;
    int chk=0; //判断某一个单词路上有几个单词
    map<char, int> mp;
    Trie(){init();}
    void init() {
        ll id = 0;
        for (char c = 'a'; c <= 'z'; c++) mp[c] = ++id;
        for (char c = 'A'; c <= 'Z'; c++) mp[c] = ++id;
        for (char c = '0'; c <= '9'; c++) mp[c] = ++id;
    }
    void insert(string s) {
        int u = 0;
        for (int i = 0; i < s.size(); i++) {
            int v = mp[s[i]];
            if (!ch[u][v]) ch[u][v] = ++idx;
            u = ch[u][v];
            // cnt[u]++;  //ins "abc" -> q("abc")=1,q("ab")=1
        }
        cnt[u]++;//不存在包含关系放for外面，存在包含放里面 ins "abc" -> q("abc")=1,q("ab")=0
    }
    ll query(string s) {
        int u = 0;
        chk = 0;
        for (int i = 0; i < s.size(); i++) {
            int v = mp[s[i]];
            if (!ch[u][v]) return 0;
            u = ch[u][v];
            if(cnt[u]==1){
                chk++;
            }
        }
        return cnt[u];
    }
    void Clear() {
        for (int i = 0; i <= idx; i++) {
            cnt[i] = 0;
            for (int j = 0; j <= 62; j++) {
                ch[i][j] = 0;
            }
        }
        idx = 0;
    }
}trie;