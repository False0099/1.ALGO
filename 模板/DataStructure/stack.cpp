#include<bits/stdc++.h>
using namespace std;
constexpr int N = 1e7+10;
int tt=0;
int st[N];

void push(int x){
    st[++tt]=x;
}
void pop(){
    tt--;
}
int top(){
    return st[tt];
}
bool isEmpty(){
    return !(tt>0);
}