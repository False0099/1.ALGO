#include<bits/stdc++.h>
using namespace std;
struct KMP{
    vector<int> ne;
    vector<int> pos;
    string s,p;

    KMP(string s,string p){
        ne.resize(p.size()+1);
        this->s=s,this->p=p;
        getNext(p);
    }

    KMP(string p){
        ne.resize(p.size()+1);
        this->p=p;
        getNext(p);
    }
    inline void getNext(string p) {
        int i=0,j;
        ne[0]=j=-1;
        while(i<p.size()) 
            if(j==-1 || p[i]==p[j])
                ne[++i]=++j;
            else j=ne[j];
    } 
    inline int work(){ 
        int cnt=0;
        int i=0,j=0;
        while(i<s.size()) { 
            if(j==-1 || s[i]==p[j])  
                i++,j++;
            else j=ne[j]; 
            if(j==p.size()){
                //剪断操作
                // j=0; 
                //不剪断
                pos.push_back(i-p.size());
                j=ne[j];
                cnt++;  
            }  
        } 
        return cnt;
    } 
    //最小循环节
    inline int MLoop(){
        return p.size()-ne[p.size()];
    }
    //返回位置数组
    auto getPos(){
        return pos;
    }
};


auto kmp=[&](string s,string p){
    vector<int> ne,pos;
    ne.resize(p.size()+1);
    int i=0,j;
    ne[0]=j=-1;
    while(i<p.size()){ 
        if(j==-1||p[i]==p[j]) ne[++i]=++j;
        else j=ne[j];
    }
    int cnt=0;
    i=0,j=0;
    while(i<s.size()){ 
        if(j==-1||s[i]==p[j]) i++,j++;
        else j=ne[j]; 
        if(j==p.size()){
            pos.push_back(i-p.size());
            //不剪断
            j=ne[j];
            //剪断操作
            // j=0; 
            cnt++;  
        }  
    } 
    pair<int,vector<int>> res{cnt,pos};
    return res;
};

// //最小循环节
// return p.size()-ne[p.size()];