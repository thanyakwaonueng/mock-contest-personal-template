/**
 * Author: Tanya
 * Description: TODO
 */
void lcs(){
    //pseudo code
    for(int i=1;i<=n;++i){
        for(int j=1;j<=m;++j){
            bool have = (s[i] == t[j]);
            dp[i][j] = max({dp[i-1][j], dp[i][j-1], dp[i-1][j-1] + have});
        }
    }
}
//maximum subarray sum can also be done by dp
