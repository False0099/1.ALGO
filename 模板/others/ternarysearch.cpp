//整数三分，凹函数极小
int lans=0,rans=0;
while(l < r) {
    int lmid = l + (r - l) / 3;
    int rmid = r - (r - l) / 3;
    lans = calc(lmid), rans = calc(rmid);
    if(lans <= rans){
        r = rmid - 1;
    }
    else{
        l = lmid + 1;
    } 
}
cout << min(lans,rans) << endl;

//整数三分，凸函数极大
int lans=0,rans=0;
while(l < r) {
    int lmid = l + (r - l) / 3;
    int rmid = r - (r - l) / 3;
    lans = calc(lmid), rans = calc(rmid);
    if(lans >= rans){
        r = rmid - 1;
    }
    else{
        l = lmid + 1;
    } 
}
cout << max(lans,rans) << endl;

//实数三分，凹函数极小
const double EPS = 1e-9;
while(r - l < EPS) {
    double lmid = l + (r - l) / 3;
    double rmid = r - (r - l) / 3;
    lans = calc(lmid),rans = calc(rmid);
    if(lans <= rans) r = rmid;
    else l = lmid;
}
cout << l << endl;

//实数三分,凸函数极大
const double EPS = 1e-9;
while(r - l < EPS) {
    double lmid = l + (r - l) / 3;
    double rmid = r - (r - l) / 3;
    lans = calc(lmid),rans = calc(rmid);
    if(lans >= rans) l = lmid;
    else r = rmid;
}
cout << l << endl;