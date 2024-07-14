// comb_mod
using mint_comb = atcoder::static_modint<1000000007>;

vector<mint_comb> fac, finv, inv;

// テーブルを作る前処理
void init_comb_mod(ll size) {
    size += 109;
    fac.resize(size);
    finv.resize(size);
    inv.resize(size);
    const ll MOD = mint_comb::mod();
    fac[0] = fac[1] = 1;
    finv[0] = finv[1] = 1;
    inv[1] = 1;
    for (ll i = 2; i < size; i++){
        fac[i] = fac[i - 1] * i;
        inv[i] = MOD - inv[MOD%i] * (MOD / i);
        finv[i] = finv[i - 1] * inv[i];
    }
}

// 二項係数計算
mint_comb comb_mod(ll n, ll k){
    if (n < k) return 0;
    if (n < 0 || k < 0) return 0;
    return fac[n] * finv[k] * finv[n - k];
}
