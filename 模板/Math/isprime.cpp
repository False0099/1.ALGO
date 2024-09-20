bool isPrime(int x){
    if(x<2){
        return false;
    }
    for(int i=2;i<=x/i;i++){
        if(x%i==0){
            return false;
        }
    }
    return true;
}

//常数优化 sqrt(x)/3
bool isPrime(int n) {
    if (n == 1) return false;
    if (n == 2 || n == 3) return true;
    if (n % 6 != 1 && n % 6 != 5) return false;
    for (int i = 5, j = n / i; i <= j; i += 6) {
        if (n % i == 0 || n % (i + 2) == 0) {
            return false;
        }
    }
    return true;
}