/**
 * Author: Tanya
 * Description: TODO
 */
typedef __int128 HASH;
HASH p[NN], h[NN];
constexpr HASH M = 1000000000000000003;
mt19937 rng(chrono::steady_clock::now().time_since_epoch().count());//delete this if using my template
#define uid(a, b) uniform_int_distribution<long long>(a, b)(rng)//delete this if using my template

void compute_hash(string const& s){
    p[0] = 1, p[1] = uid(256, M-1);
    for(ll i=0;i<(int)s.length();++i){
        p[i+1] = p[i]*p[1]%M;
        h[i+1] = (h[i]*p[1] + s[i])%M;
    }
}

HASH sub_hash(ll l, ll r){ //range [l, r)
    return (h[r] - p[r-l]*h[l]%M + M)%M;
}


