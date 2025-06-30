/**
 * Author: Tanya
 * Description: TODO
 */
//more practical to precal C[n][r] with pascal triangle...
//...if constrain is O(n^2) able
long long C(int n, int k) {
    if(k==0)return 1;
    else if(k<0 || n<k)return 0;
    double res = 1;
    for (int i = 1; i <= k; ++i)
        res = res * (n - k + i) / i;
    return (long long)(res + 0.01);
}
