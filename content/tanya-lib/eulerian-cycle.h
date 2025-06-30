/**
 * Author: Tanya
 * Description: TODO
 */
    //TODO: checking all node degrees is even ? 
    //TODO: checking if all edges are connectedly reachable

    stack<int> st;
    vi res;
    st.push(1);
    while(!st.empty()){
        int v = st.top(); 
        if(deg[v] == 0){
            res.pb(v);
            st.pop();
        } else {
            int rm = -1; //must exist
            for(auto &b:adj[v]){
                rm = b;
                break;
            }
            adj[v].erase(rm); deg[v]--;
            adj[rm].erase(v); deg[rm]--;
            st.push(rm);
        }
    }
    //reverse the res if the edge is directed !! also changing the checking condition
    for(auto &x:res)cout << x << " ";
    cout << nl;
