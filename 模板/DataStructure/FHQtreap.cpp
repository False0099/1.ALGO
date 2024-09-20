#include<bits/stdc++.h>
using namespace std;
using ll = long long;
constexpr ll N=400400;
constexpr ll INF=1000000000;
int n;
struct FHQ_Treap{
	struct Tree{
		long long l;
		long long r;
		long long sz;
		long long val;
		long long heap;
		bool tag;
	};
	Tree tr[N];
	long long a[N];
	long long root;
	long long cnt=0;
    inline void Clear(){
        root=cnt=0;
        for(register int i=0;i<=n+1145;++i){
            tr[i].l=tr[i].r=tr[i].sz=tr[i].val=tr[i].heap=tr[i].tag=a[i]=0;
        }
    }
	inline void Pushup(long long x){
		tr[x].sz=tr[tr[x].l].sz+tr[tr[x].r].sz+1;
		return void();
	}
	inline void Pushdown(long long x){
		tr[x].tag=false;
		swap(tr[x].l,tr[x].r);
		tr[tr[x].l].tag^=1;
		tr[tr[x].r].tag^=1;
		return void();
	}
	inline long long Merge(long long x,long long y){
		if(!x||!y){
			return x+y;
		}
		if(tr[x].heap<tr[y].heap){
			if(tr[x].tag){
				Pushdown(x);
			}
			return tr[x].r=Merge(tr[x].r,y),Pushup(x),x;
		}
		else{
			if(tr[y].tag){
				Pushdown(y);
			}
			return tr[y].l=Merge(x,tr[y].l),Pushup(y),y;
		}
	}
	inline void Split(long long x,long long key,long long &u,long long &v){
		if(!x){
			u=v=0;
			return void();
		}
		if(tr[x].tag){
			Pushdown(x);
		}
		if(tr[tr[x].l].sz<key){
			u=x;
			Split(tr[x].r,key-tr[tr[x].l].sz-1,tr[u].r,v);
		}
		else{
			v=x;
			Split(tr[x].l,key,u,tr[v].l);
		}
		Pushup(x);
		return void();
	}
	inline long long Create(long long key){
		tr[++cnt].val=key;
		tr[cnt].heap=rand();
		tr[cnt].sz=1;
		tr[cnt].tag=false;
		return cnt;
	}
	long long x,y,z;
	inline void Insert(long long key){
		root=Merge(root,Create(key));
		return void();
	}
	inline void Reverse(long long l,long long r){
		Split(root,l-1,x,y);
		Split(y,r-l+1,y,z);
		tr[y].tag^=1;
		root=Merge(x,Merge(y,z));
		return void();
	}
	inline void Dfs(long long x){
		if(!x){
			return void();
		}
		if(tr[x].tag){
			Pushdown(x);
		}
		Dfs(tr[x].l);
        putchar(tr[x].val+'a'-1);
		Dfs(tr[x].r);
		return void();
	}
};
FHQ_Treap FT;