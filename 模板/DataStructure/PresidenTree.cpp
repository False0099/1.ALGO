#include <cstdio>
#include <cstring>
#include <iostream>

using namespace std;
using LL = long long;
using LLL = __int128;

const int N = 2e5 + 5, A = 1e5 + 5, LOG = 18;
int a[N];
int n, m;

class chairmanTree {
   private:
    static const int C = N * LOG;
    int lc[C], rc[C], val[C],count[C],root[N],cnt;

    int modify(int p, int l, int r, int po) {
        int q = ++cnt;
        val[q] = val[p];
        if (l == r) return val[q]++, q;
        int mid = (l + r) >> 1;
        if (po <= mid)
            lc[q] = modify(lc[p], l, mid, po), rc[q] = rc[p];
        else
            lc[q] = lc[p], rc[q] = modify(rc[p], mid + 1, r, po);
        return val[q] = val[lc[q]] + val[rc[q]], q;
    }
	/*查询区间[p,q]内在[ql,qr]之间的数*/
    int query(int p, int q, int l, int r, int ql, int qr) {
        if (ql <= l && qr >= r) return val[q] - val[p];
        int mid = (l + r) >> 1;
        return (ql <= mid ? query(lc[p], lc[q], l, mid, ql, qr) : 0) +
               (qr > mid ? query(rc[p], rc[q], mid + 1, r, ql, qr) : 0);
    }
    /* 查询[p,q]内第k小值*/ 
	int querysingle(int p,int q,int l,int r,int k){
		int cnt=val[lc[q]]-val[lc[p]];
		if(l==r){
			return l;
		}
		int mid=l+r>>1;
		if(cnt>=k){
			return querysingle(lc[p],lc[q],l,mid,k);
		}else{
			return querysingle(rc[p],rc[q],mid+1,r,k-cnt);
		}
	} 
   public:
    void modify(int ver, int base, int po) {
        root[ver] = modify(root[base], 0, A, po);
    }

    bool query(int l, int r, int ql, int qr) {
        return query(root[l - 1], root[r], 0, A, max(ql, 0), min(qr, A));
    }
    int query(int l,int r,int k){
    	return querysingle(root[l-1],root[r],1,A,k);
	}
} tree;

template <class T>
void read(T &ret) {
    ret = 0;
    char ch = getchar();
    bool found = false;
    while ((ch < '0' || ch > '9') && ch != '-') ch = getchar();
    if (ch == '-') ch = getchar(), found = true;
    while (ch >= '0' && ch <= '9') ret = ret * 10 + ch - '0', ch = getchar();
    if (found) ret = -ret;
}

template <class T, class... Args>
void read(T &ret, Args &...rest) {
    read(ret), read(rest...);
}

int main() {
    read(n, m);
    for (int i = 1; i <= n; i++) cin>>a[i], tree.modify(i, i - 1, a[i]);
    while(m--){
    	int l,r,k;
    	cin>>l>>r>>k;
    	cout<<(tree.query(l,r,k)-1)<<endl;
	}
    return 0;
}
