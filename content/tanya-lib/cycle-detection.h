/**
 * Author: Tanya
 * Description: TODO
 */
vi adj[N+1];
bool vst[N+1];
bool cur[N+1];
bool cycle=0;

vi temp;
void dfs(int a){
    vst[a]=1;
    cur[a]=1;
    for(auto&b:adj[a]){
        if(!vst[b])dfs(b);
        else if(cur[b])cycle=1;
    }
    temp.pb(a); //topological sort order
    cur[a]=0;
}
