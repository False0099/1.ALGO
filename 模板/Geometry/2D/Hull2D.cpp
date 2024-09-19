struct Point{
    double x,y;
};
const int N=5e5+10;
Point st[N];
int top=0;
double cross(Point a,Point b,Point c){
    return (b.x-a.x)*(c.y-a.y)-(b.y-a.y)*(c.x-a.x);
}
double dis(Point a,Point b){
    return hypot(a.x-b.x,a.y-b.y);
}
double Hull(vector<Point> &p){
    sort(p.begin()+1,p.end(),[&](Point a,Point b){
        if(a.x==b.x){
            return a.y<b.y;
        }
        return a.x<b.x;
    });
    int n=p.size()-1;
    for(int i=1;i<=n;i++){
        while(top>1&&cross(st[top-1],st[top],p[i])<=0) top--;
        st[++top]=p[i];
    }
    int t=top;
    for(int i=n-1;i>=1;i--){
        while(top>t&&cross(st[top-1],st[top],p[i])<=0) top--;
        st[++top]=p[i];
    }
    double res=0;
    for(int i=1;i<top;i++){
        res+=dis(st[i],st[i+1]);
    }
    return res;
}