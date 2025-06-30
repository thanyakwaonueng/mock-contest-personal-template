/**
 * Author: Tanya
 * Description: TODO
 */
// subset sum using knapsack
ll dp[N];

void solve(){
    int n;cin>>n;
    for(int i=1;i<=n;++i)dp[i] = -INF;
    dp[0] = 0;
    rep(i,n){
        int x;
        cin>>x;
        for(int j=n;j>=1;--j){
            dp[j] = max(dp[j], dp[j-1] + x);
        }
    }
    for(int i=1;i<=n;++i)cout << dp[i] << " ";
    cout << nl;
}
// subset sum using pascal triangle relation
ll dp[100][100];

void solve(){
    for(int i=0;i<100;++i){
        for(int j=0;j<100;++j)dp[i][j] = -1;
    }
    dp[0][0] = 0;
    int n;cin>>n;
    for(int i=1;i<=n;++i){
        int x;cin>>x;
        for(int j=n;j>=1;--j){
            for(int k=1;k<=n;++k){
                if(dp[k-1][j-1]!=-1){
                    dp[k][j] = max(dp[k][j], dp[k-1][j-1] + x);
                }

                if(dp[k-1][j]!=-1){
                    dp[k][j] = max(dp[k][j], dp[k-1][j]);
                }
            }
        }
    }

    for(int i=1;i<=n;++i)cout << dp[n][i] << " ";
    cout << nl;
}
