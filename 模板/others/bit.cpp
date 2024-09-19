#include<bits/stdc++.h>
using namespace std;
int Knum(int n,int k){
    return n>>k&1;
}
int lowbit(int n){
    return n&-n;
}
//2的幂
bool isPowerOfTwo(int n) {
    return n>0&&(n&(n-1))==0;
} 
//4 de mi
bool isPowerOfFour(int n) {
    return n>0&&(n&(n-1))==0&&n%3==1;
} 