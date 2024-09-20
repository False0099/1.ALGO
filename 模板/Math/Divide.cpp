map<int,int> cnt;
void divide(int x){
    for(int i=2;i<=x/i;i++){
        if(x%i==0){
            while(x%i==0){
                x/=i;
                cnt[i]++;
            }
        }
    }
    if(x>1) cnt[x]++;
}


