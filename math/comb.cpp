ll comb(ll n, ll r){
    vector dp(n + 1, vector<ll>(r + 1));
    for(ll i = 0; i < n + 1; ++i){
        dp[i][0] = 1;
    }
    for(ll i = 0; i < r + 1; ++i){
        dp[i][i] = 1;
    }
    for(ll i = 1; i < n + 1; ++i){
        for(ll j = 1; j < min(i, r + 1); ++j){
            dp[i][j] = dp[i - 1][j - 1] + dp[i - 1][j];
        }
    }
    return dp[n][r];
}
