/**
 * Author: Tanya
 * Description: TODO
 */
long long bigmod(long long a, int n){
    long long res = 1;
    while(n>0){
        if(n&1){
            res = res * a % MOD;
        }
        a = a * a % MOD;
        n>>=1;
    }
    return res;
}
