int work(int x,int t){
    string str=to_string(x);
    int m=str.size();
    int mem[200][200];
    memset(mem,-1,sizeof(mem));
    function<int(int,int,bool,bool)> dfs = [&](int i,int sum,bool limit,bool isnum)->int{
        if(i==m) return isnum?sum:0;
        if(!limit&&isnum&&mem[i][sum]!=-1) return mem[i][sum];
        int res=0;
        if(!isnum) res=dfs(i+1,sum,false,false);
        int up=limit?str[i]-'0':9;
        for(int d=1-isnum;d<=up;d++){
            res+=dfs(i+1,sum+(d==t),limit&&d==up,true);
        }
        if(!limit&&isnum){
            mem[i][sum]=res;
        }
        return res;
    };
    return dfs(0,0,true,false);
}