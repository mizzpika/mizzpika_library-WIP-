ll make_random(ll l, ll r){
    random_device rd;
    mt19937_64 gen(rd());
    uniform_int_distribution<ll>dis(l, r);
    return dis(gen);
}
