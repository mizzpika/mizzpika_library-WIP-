//平方数かどうかをO(log(n))で判定
template<typename T> bool is_square(T n){
    if(n < 0)return false;
    T m = sqrt(n);
    if(n == m * m){
        return true;
    }else{
        return false;
    }
}
