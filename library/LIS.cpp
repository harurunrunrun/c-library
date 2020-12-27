
int n,a[10000],dp[10000];

int LIS(){
  int res=0;
	for(int i=0;i<n;i++){
	  dp[i]=1;
		for(int j=0;j<i;j++)if(a[j]<a[i]){
			dp[i]=max(dp[i],dp[j]+1);
		}
		res=max(res,dp[i]);
	}
	return res;
}