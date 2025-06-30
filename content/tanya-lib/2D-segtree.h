/**
 * Author: Tanya
 * Description: TODO
 */
// 2D segtree stored as tree[4*n][4*m] 
vector<vector<ll>> tree;
int n, m; // This shit in global remember
vector<vector<ll>> A; // This shit in global too

void buildY(int vx, int lx, int rx, int vy, int ly, int ry) {
    if (ly == ry) {
        if (lx == rx) {
            tree[vx][vy] = A[lx][ly];
        } else {
            tree[vx][vy] = tree[vx*2][vy] + tree[vx*2+1][vy];
        }
    } else {
        int my = (ly + ry) >> 1;
        buildY(vx, lx, rx, vy*2,   ly,   my);
        buildY(vx, lx, rx, vy*2+1, my+1, ry);
        tree[vx][vy] = tree[vx][vy*2] + tree[vx][vy*2+1];
    }
}

void buildX(int vx = 1, int lx = 1, int rx = n) {
    if (lx != rx) {
        int mx = (lx+rx)>>1;
        buildX(vx*2,   lx,   mx);
        buildX(vx*2+1, mx+1, rx);
    }
    buildY(vx, lx, rx, 1, 1, m);
}

void updateY(int vx, int lx, int rx, int x,
             int vy, int ly, int ry, int y, ll val) {
    if (ly == ry) {
        if (lx == rx) {
            tree[vx][vy] = val;
        } else {
            tree[vx][vy] = tree[vx*2][vy] + tree[vx*2+1][vy];
        }
    } else {
        int my = (ly+ry)>>1;
        if (y <= my)
            updateY(vx,lx,rx,x, vy*2,   ly,   my, y, val);
        else
            updateY(vx,lx,rx,x, vy*2+1, my+1, ry, y, val);
        tree[vx][vy] = tree[vx][vy*2] + tree[vx][vy*2+1];
    }
}

void updateX(int vx, int lx, int rx, int x, int y, ll val) {
    if (lx != rx) {
        int mx = (lx+rx)>>1;
        if (x <= mx) updateX(vx*2,   lx,   mx, x, y, val);
        else         updateX(vx*2+1, mx+1, rx, x, y, val);
    }
    updateY(vx, lx, rx, x, 1, 1, m, y, val);
}

ll queryY(int vx, int vy, int ly, int ry, int y1, int y2) {
    if (y2 < ly || ry < y1) return 0;
    if (y1 <= ly && ry <= y2) return tree[vx][vy];
    int my = (ly+ry)>>1;
    return queryY(vx,vy*2,  ly,   my, y1,y2)
         + queryY(vx,vy*2+1,my+1, ry,  y1,y2);
}

ll queryX(int vx, int lx, int rx,
          int x1, int x2, int y1, int y2) {
    if (x2 < lx || rx < x1) return 0;
    if (x1 <= lx && rx <= x2)
        return queryY(vx, 1, 1, m, y1, y2);
    int mx = (lx+rx)>>1;
    return queryX(vx*2,   lx,   mx, x1,x2,y1,y2)
         + queryX(vx*2+1, mx+1, rx, x1,x2,y1,y2);
}

void build(int n, int m){
    tree.assign(4*(n+2), vector<ll>(4*(m+2), 0));
    buildX();
}
 
//using like this n,m = row,col dimention (1-base index)
//updateX(1,1,n,x,y,v);
//queryX(1,1,n,x1,x2,y1,y2)
