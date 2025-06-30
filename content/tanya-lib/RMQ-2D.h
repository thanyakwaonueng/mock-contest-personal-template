/**
 * Author: Tanya
 * Description: TODO
 */
//general template for 2D offline queries
int rmq[N][N][20][20]; //N need to be around 1e2

void build_rmq(vector<vi>& a){
    for(int j=0;j<20;++j){
        for(int k=0;k<20;++k){
            for(int r=0;r<(int)a.size();++r){
                for(int c=0;c<(int)a[0].size();++c){
                    if(j==0&&k==0)rmq[r][c][0][0]=a[r][c];
                    else {
                        if(j==0 && k>0 && (c+(1<<(k-1))<(int)a[0].size() )){
                            rmq[r][c][j][k]=min(rmq[r][c][j][k-1],
                            rmq[r][c+(1<<(k-1))][j][k-1]);
                        } else if(k==0 && j>0 && (r+(1<<(j-1))<(int)a.size()) ){
                            rmq[r][c][j][k]=min(rmq[r][c][j-1][k],
                            rmq[r+(1<<(j-1))][c][j-1][k]);
                        } else if( c+(1<<(k-1))<(int)a[0].size()
                        && r+(1<<(j-1))<(int)a.size() ){
                            rmq[r][c][j][k]=min({rmq[r][c][j-1][k-1],
                            rmq[r][c+(1<<(k-1))][j-1][k-1],
                            rmq[r+(1<<(j-1))][c][j-1][k-1],
                            rmq[r+(1<<(j-1))][c+(1<<(k-1))][j-1][k-1]});
                        }
                    }
                }
            }
        }
    }
}

int query(int r1,int c1,int r2,int c2){
    int x=r1,y=c1,h=r2-r1+1,w=c2-c1+1,ans=INF;
    for(int j=0;j<30;++j){
        if((1<<j)&h){
            for(int k=0;k<30;++k){
                if((1<<k)&w){
                    ans=min(ans,rmq[x][y][j][k]);
                    y+=(1<<k);
                }
            }
            y=c1;
            x+=(1<<j);
        }
    }
    return ans;
}

