#include<bits/stdc++.h>
using namespace std;
struct Splay_tree{
    struct node{
        int fa, ch[2], val, siz, cnt;
        node() {
            fa = val = siz = cnt = 0;
            memset(ch, 0, sizeof ch);
        };
    };
    int tot,root;
    std::vector <node> t;
    void update(int x){
        t[x].siz = t[t[x].ch[0]].siz + t[t[x].ch[1]].siz + t[x].cnt;
    }
    void rotate(int x){
        int y = t[x].fa, z = t[y].fa, k = (t[y].ch[1] == x);
        t[z].ch[t[z].ch[1] == y] = x;
        t[x].fa = z;
        t[y].ch[k] = t[x].ch[k ^ 1];
        t[t[x].ch[k ^ 1]].fa = y;
        t[x].ch[k ^ 1] = y;
        t[y].fa = x;
        update(y);
        update(x);
    }
    void splay(int x, int s){
        while(t[x].fa != s){
            int y = t[x].fa, z = t[y].fa;
            if(z != s) (t[y].ch[1] == x) ^ (t[z].ch[1] == y) ? rotate(x) : rotate(y);
            rotate(x);
        }
        if(s == 0) root = x;
    }
    void find(int x){
        int u = root;
        if(!u) return ;
        while(t[u].ch[x > t[u].val] && x != t[u].val) u = t[u].ch[x > t[u].val];
        splay(u, 0);
    }
    void insert(int x){
        int u = root,fa = 0;
        while(u && t[u].val != x){
            fa = u;
            u = t[u].ch[x > t[u].val];
        }
        if(u) t[u].cnt++;
        else{
              u = ++tot;
              if(fa) t[fa].ch[x > t[fa].val] = u;
              t[u].ch[0] = t[u].ch[1] = 0;
              t[u].fa = fa;
              t[u].val = x;
              t[u].siz = t[u].cnt = 1;
        }
        splay(u, 0);
    }
    int Next(int x, int f){
        find(x);
        int u = root;
        if((t[u].val > x && f) || (t[u].val < x && !f)) return u;
        u = t[u].ch[f];
        while(t[u].ch[f ^ 1]) u = t[u].ch[f ^ 1];
        return u;
    }
    void Delete(int x){
        int last = Next(x, 0), next = Next(x, 1);
        splay(last, 0), splay(next, last);
        int del = t[next].ch[0];
        if(t[del].cnt > 1){
            t[del].cnt--;
            splay(del, 0);
        }
        else{
            t[next].ch[0] = 0;
        }
    }
    int k_th(int x){
        int u = root;
        if(t[u].siz < x) return 0;
        while(1){
            int y = t[u].ch[0];
            if(t[y].siz + t[u].cnt < x) {
                x -= t[y].siz + t[u].cnt;
                u = t[u].ch[1];
            }
            else if(t[y].siz >= x) {
                u = y;
            }
            else  return t[u].val;
        }
    }
    int rank(int x){
        find(x);
        return t[t[root].ch[0]].siz;
    }
    int pre(int x){
        return t[Next(x,0)].val;
    }
    int sub(int x){
        return t[Next(x,1)].val;
    }
    Splay_tree(int n) : tot(0), root(0), t(n << 1) {insert(-1e9), insert(1e9);}
};
