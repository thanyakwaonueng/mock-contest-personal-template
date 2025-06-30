/**
 * Author: Tanya
 * Description: TODO
 */
//don't forget to initialize the base case of weight 
//for example d[i][i] = 0 for all i and other given weight
//this work for negative weight without negative cycle
for (int k = 0; k < n; ++k) {
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++j) {
            if (d[i][k] < INF && d[k][j] < INF)
                d[i][j] = min(d[i][j], d[i][k] + d[k][j]); 
        }
    }
}
