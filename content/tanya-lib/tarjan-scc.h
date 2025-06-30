/**
 * Author: Tanya
 * Description: TODO
 */
//Trajan's algorithm
vi adj[N+1];
int id[N+1], low[N+1]; 
bool vst[N+1], in_stack[N+1];

stack<int>st;
vector<vi>scc;
vi comp;
int tin=0;
void dfs(int a){
    st.push(a);
    vst[a]=in_stack[a]=1;
    id[a]=low[a]=tin++;

    for(auto&b:adj[a]){
        if(!vst[b]){
            dfs(b); 
            low[a]=min(low[a],low[b]); //Backtrack low-link value
        } else if(in_stack[b]){
            //Backtrack low-link value
            low[a]=min(low[a],low[b]); 
        }
    }
    if(id[a] == low[a]){ //pop scc
        while(!st.empty()){
            int v=st.top();
            comp.pb(v), st.pop();
            in_stack[v]=0;
            if(v==a)break; //stop when scc is found
        }
    }
    if(!comp.empty()){
        scc.pb(comp), comp.clear();
    }
}
