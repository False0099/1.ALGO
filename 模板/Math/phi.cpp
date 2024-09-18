int phi(int x){
    int res = x;
    for (int i = 2; i <= x / i; i ++ )
        if (x % i == 0){
            res = res / i * (i - 1);
            while (x % i == 0) x /= i;
        }
    if (x > 1) res = res / x * (x - 1);
    return res;
}



// 扩展欧拉定理降幂 p = phi(m) b为次数
// auto depow = [&](string str){
//     int b=0;
//     bool flag=false;
//     for(int i=0;i<str.size();i++){
//         b=b*10+str[i]-'0';
//         if(b>=p){
//             flag=true;
//             b%=p;
//         }
//     }
//     if(flag){
//         b+=p;
//     }
//     return b;
// };