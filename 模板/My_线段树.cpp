class SegmentTree
{
public:
    struct Node
    {
        int l, r;
        int sum;
    }tr[N << 2];
    Node merge(Node x, Node y)
    {
        if (x.l == -1) return y;
        if (y.l == -1) return x;
        Node z;
        z.l=min(x.l,y.l);
        z.r=max(x.r,y.r);
        z.sum=(x.sum+y.sum);
        return z;
    }//这里需要改 
    void pushup(int u)
    {
        tr[u] = merge(tr[u << 1], tr[u << 1 | 1]);
    }
    void build(int u, int l, int r)
    {
        tr[u] = {l, r, 0};
        if (l == r) return;
        int mid = l + r >> 1;
        build(u << 1, l, mid);
        build(u << 1 | 1, mid + 1, r);
        pushup(u);
    }
    void update(int u, int p, int x)
    {
        if (tr[u].l == tr[u].r)
        {
            //这里需要改 
            tr[u].sum+=x;
            return;
        }
        int mid = tr[u].l + tr[u].r >> 1;
        if (p <= mid) update(u << 1, p, x);
        else update(u << 1 | 1, p, x);
        pushup(u);
    }
    Node query(int u, int l, int r)
    {
        if (tr[u].l >= l and tr[u].r <= r) 
        {
            return tr[u];
        }
        int mid = tr[u].l + tr[u].r >> 1;
        Node ret;
        ret.l = -1;
        if (l <= mid) ret = query(u << 1, l, r);
        if (r > mid) ret = merge(ret, query(u << 1 | 1, l, r));
        return ret;
    }
}t;