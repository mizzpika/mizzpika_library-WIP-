ll LCS(string s, string t){
    vector dp(s.size() + 1,vector<ll>(t.size() + 1));
    rep(i,s.size()){
        rep(j,t.size()){
            if(s[i] == t[j]){
                dp[i + 1][j + 1] = max({dp[i][j + 1],dp[i + 1][j],dp[i][j] + 1});
            }else{
                dp[i + 1][j + 1] = max(dp[i][j + 1],dp[i + 1][j]);
            }
        }
    }
    return dp[s.size()][t.size()];
}
