//素数かどうかをO(sqrt(n))で判定する
template<typename T> bool is_prime(T n){
    if(n <= 1)return false;
    T m = sqrt(n);
    for(ll i = 2; i <= m; ++i){
        if(n % i == 0)return false;
    }
    return true;
}
