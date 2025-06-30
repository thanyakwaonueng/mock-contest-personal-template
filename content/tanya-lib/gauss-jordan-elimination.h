/**
 * Author: Tanya
 * Description: TODO
 */
const double EPS = 1e-9;
const int INF = 2; // it doesn't actually have to be infinity or a big number

int gauss (vector < vector<double> > a, vector<double> & ans) {
    int n = (int) a.size();
    int m = (int) a[0].size() - 1;

    vector<int> where (m, -1);
    for (int col=0, row=0; col<m && row<n; ++col) {
        // 2.1 Pick the row with largest |a[i][col]| among i = row..n-1
        int sel = row;
        for (int i=row; i<n; ++i)
            if (abs (a[i][col]) > abs (a[sel][col]))
                sel = i;

        // 2.2 If pivot is “zero” (|a[sel][col]| < EPS), skip this column
        if (abs (a[sel][col]) < EPS)
            continue;

        // 2.3 Swap pivot row into the ‘row’-th position
        for (int i=col; i<=m; ++i)
            swap (a[sel][i], a[row][i]);
        where[col] = row;
        
        // 2.4 Eliminate this variable from all other rows
        for (int i=0; i<n; ++i)
            if (i != row) {
                double c = a[i][col] / a[row][col];
                for (int j=col; j<=m; ++j)
                    a[i][j] -= a[row][j] * c;
            }
        ++row;
    }

    ans.assign (m, 0);
    // 3.1 If column col had a pivot (where[col] != –1), compute that variable
    for (int i=0; i<m; ++i)
        if (where[i] != -1)
            ans[i] = a[where[i]][m] / a[where[i]][i];

    // 3.2 Verify each original equation still holds
    for (int i=0; i<n; ++i) {
        double sum = 0;
        for (int j=0; j<m; ++j)
            sum += ans[j] * a[i][j];
        if (abs (sum - a[i][m]) > EPS)
            return 0; // contradiction -> no solution
    }

    // If any variable never got a pivot → it’s “free”
    for (int i=0; i<m; ++i)
        if (where[i] == -1)
            return INF; //infinite solution
    return 1; //unique solution
}
