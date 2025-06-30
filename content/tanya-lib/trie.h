/**
 * Author: Tanya
 * Description: TODO
 */
// string trie structure
const int K = 26;

struct node{
    int to[K];
    bool output = false;
    
    node(){
        fill(begin(to), end(to), -1);
    }
};

vector<node>trie(1);

void add(const& string s){
    int v = 0;
    for(char ch: s){
        int c = ch - 'a';
        if(trie[v][c] == -1){
            trie[v][c] = trie.size();
            trie.push_back(node());
        }
        v = trie[v][c];
    }
    trie[v].output = true;
}

