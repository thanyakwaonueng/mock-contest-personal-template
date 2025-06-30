/**
 * Author: Tanya
 * Description: TODO
 */
/*hld*/
//TODO: initialize constant N
vector<int>adj[N];

void add_edges(int a, int b){
    adj[a].pb(b);
    adj[b].pb(a);
}

const int LOG = 20;
int timer = 0, seg_tree_size = 0;
int depth[N], parent[N], n_subtree[N], heavyChild[N], chain[N], SegTreePos[N];
int cost[N];
int up[N][LOG]; // 2^j-th ancestor of n

/*SegTree*/
//finding max edge query
ll tree[4*N];
void update(int node,int n_l,int n_r,int q_i,int value){
    if(n_r<q_i || q_i<n_l)return;
    if(q_i==n_l && n_r==q_i){
        tree[node] = value;
        return;
    }
    int mid = (n_r+n_l)/2;
    update(2*node,n_l,mid,q_i,value);
    update(2*node+1,mid+1,n_r,q_i,value);
    tree[node] = max(tree[2*node], tree[2*node+1]);
}

long long f(int node,int n_l,int n_r,int q_l,int q_r){
    if(n_r<q_l || q_r<n_l)return 0;
    if(q_l<=n_l && n_r<=q_r)return tree[node];
    int mid = (n_l+n_r)/2;
    return max(f(2*node,n_l,mid,q_l,q_r) , f(2*node+1,mid+1,n_r,q_l,q_r));
}
/*SegTree*/


//preprecessing the arrays above
void dfs(int a,int e){
    chain[a] = a;
    n_subtree[a] = 1;
    int bestSon = -1, hmax = -1;
    for(auto b:adj[a]){
        if(b == e)continue;
        depth[b] = depth[a] + 1;
        parent[b] = a;
        up[b][0] = parent[b];
        for(int i=1;i<LOG;++i){
            up[b][i] = up[up[b][i-1]][i-1];
        }
        dfs(b,a);
        n_subtree[a] += n_subtree[b];
        if(n_subtree[b] > hmax){
            hmax = n_subtree[b], bestSon = b;
        }
    }
    heavyChild[a] = bestSon;
}

void computeHeavyChains(int a, int e){
    if(heavyChild[a] != -1){
        chain[heavyChild[a]] = chain[a];
    } 
    for(auto b:adj[a]){
        if(b == e)continue;
        computeHeavyChains(b, a);
    }
}

void setHeavyChains(int a, int e){
    SegTreePos[a] = timer++;
    if(heavyChild[a] != -1){
        setHeavyChains(heavyChild[a], a);
        int w = 0;
        for(auto b:adj[a]){
            if(b == heavyChild[a]){
                w = 1;
                break;
            }
        }
        //setting cost of heavyChild[a] = weight of edge (a, heavyChild[a])
        cost[heavyChild[a]] = w; //change when tree is weighted
    }
    for(auto b:adj[a]){
        if(b == e || heavyChild[a] == b)continue;
        cost[b] = 1; //change when tree is weighted
        setHeavyChains(b ,a);
    }
}

void buildSegTree(int n_node){
    seg_tree_size = n_node;
    while(__builtin_popcount(seg_tree_size)!=1)++seg_tree_size;
    for(int i=0;i<n_node;++i){
        update(1,0,seg_tree_size-1,SegTreePos[i], cost[i]);
    }
    for(int i=seg_tree_size-1;i>=1;--i){
        tree[i] = max(tree[2*i], tree[2*i+1]);
    }
}

ll queryPath(int mother, int son){
    ll ans = LONG_MIN;
    while(chain[mother] != chain[son]){
        if(chain[son] == son){
            ans = max(ans,f(1,0,seg_tree_size-1,SegTreePos[son],SegTreePos[son]));
        } else {
            ans = max(ans, f(1,0,seg_tree_size-1,SegTreePos[chain[son]],SegTreePos[son]));
        }
        son = parent[chain[son]];
    }
    
    ans = max(ans, f(1,0,seg_tree_size-1,SegTreePos[mother]+1,SegTreePos[son]));
    
    return ans;
}

int lca(int a, int b){
    if(depth[a]<depth[b])swap(a,b);
    int k = depth[a] - depth[b];
    for(int i=LOG-1;i>=0;--i){
        if(k &(1<<i)){
            a = up[a][i];
        }
    }

    if(a == b)return a;
    for(int i=LOG-1;i>=0;--i){
        if(up[a][i] != up[b][i]){
            a = up[a][i];
            b = up[b][i];
        }
    }
    return up[a][0];
}

ll query(int x, int y){
    int l = lca(x,y);
    return max( queryPath(l, x), queryPath(l, y)); //combine the answer

}

void hld_init(int n){
    dfs(0,-1);
    computeHeavyChains(0,-1);
    setHeavyChains(0,-1);
    buildSegTree(n);
}

/*hld*/
