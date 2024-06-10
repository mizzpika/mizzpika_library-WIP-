ll GCD(ll A, ll B){
    if(B == 0){
        return A;
    }else{ 
        return GCD(B, A % B);
    }
}
