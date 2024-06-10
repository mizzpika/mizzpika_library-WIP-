ll ntodec(const char c){
    if(c >= '0' && c <= '9'){
        return (ll)c - '0';
    }else{
        return (ll)c - 55;
    }
}
char decton(const ll n){
    if(n >= 0 && n <= 9){
        return (char)'0' + n;
    }else{
        return (char)55 + n;
    }
}
inline ll pow_ll(ll x,ll n){
    ll ret = 1;
    rep(i,n){
        ret *= x;
    }
    return ret;
}
string base_conversion(string str, ll n, ll m){
    ull tmp = 0;
    string ret;
    rep(i,str.size()){
        tmp += (ull)ntodec(str[str.size() - 1 - i]) * pow_ll(n, i);
    }
    if(tmp == 0){
        return "0";
    }
    while(tmp != 0){
        ret = decton(tmp % m) + ret;
        tmp /= m;
    }
    return ret;
}
