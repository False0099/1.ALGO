#include<bits/stdc++.h>
using namespace std;
#define int long long
const int N = 1000010;
int dp[N];
int cnt[2];
signed main(){
	int n;
	cin>>n;
	vector<int> a(n+1,0);
	for(int i=1;i<=n;i++){
		cin>>a[i];
	}
	int sum=0;
	for(int i=0;i<=20;i++){
		for(int j=1;j<=n;j++){
			if((a[j]>>i)&1) dp[j]=dp[j-1]^1;
			else dp[j]=dp[j-1];
		}
		cnt[0]=cnt[1]=0;
		for(int i=0;i<=n;i++){
			cnt[dp[i]]++;
		}
		sum+=(1ll<<i)*cnt[0]*cnt[1];
	}
	cout<<sum<<"\n";
	return 0;
}