int n,dp[100000],a[100000];
const int INF=1000000001;

int LIS_log(){
	fill(dp,dp+n,INF);
	for(int i=0;i<n;i++)*lower_bound(dp,dp+n,a[i])=a[i];
	return lower_bound(dp,dp+n,INF)-dp;
}