//make_random
//long long
ll rand_ll(ll l, ll r){
    if(l > r)swap(l, r);
    random_device rd;
    mt19937_64 gen(rd());
    uniform_int_distribution<ll>dis(l, r);
    return dis(gen);
}

//int
int rand_int(int l, int r){
    if(l > r)swap(l, r);
    return l + rand() % (r - l + 1);
}

//double
ld rand_double(){
    return (ld)1.0 * rand() / RAND_MAX;
}
