#include <iostream>
#include <vector>
#include <queue>
#include <cstring>
using namespace std;

const int MAXN = 100005;
vector<int> adj[MAXN];
int color[MAXN];
bool removed[MAXN];
bool visited[MAXN];
int degree[MAXN];
int n, m;

pair<bool, int> checkComponent(int start) {
    queue<int> q;
    q.push(start);
    color[start] = 0;
    visited[start] = true;
    bool isBipartite = true;
    int count = 1;
    
    while (!q.empty()) {
        int u = q.front();
        q.pop();
        
        for (int v : adj[u]) {
            if (removed[v]) continue;
            
            if (color[v] == -1) {
                color[v] = 1 - color[u];
                visited[v] = true;
                count++;
                q.push(v);
            } else if (color[v] == color[u]) {
                isBipartite = false;
            }
        }
    }
    return {isBipartite, count};
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    
    cin >> n >> m;
    
    memset(color, -1, sizeof(color));
    memset(removed, false, sizeof(removed));
    memset(visited, false, sizeof(visited));
    memset(degree, 0, sizeof(degree));
    
    for (int i = 0; i < m; i++) {
        int x, y;
        cin >> x >> y;
        if (x == y) continue; // Skip self-loops
        adj[x].push_back(y);
        adj[y].push_back(x);
        degree[x]++;
        degree[y]++;
    }
    
    // Iteratively remove nodes with degree <= 1
    queue<int> toRemove;
    for (int i = 1; i <= n; i++) {
        if (degree[i] <= 1) {
            toRemove.push(i);
            removed[i] = true;
        }
    }
    
    while (!toRemove.empty()) {
        int u = toRemove.front();
        toRemove.pop();
        
        for (int v : adj[u]) {
            if (!removed[v]) {
                degree[v]--;
                if (degree[v] <= 1) {
                    toRemove.push(v);
                    removed[v] = true;
                }
            }
        }
    }
    
    // Count nodes that are removed or in bipartite components
    int cannotInvite = 0;
    
    // Count removed nodes
    for (int i = 1; i <= n; i++) {
        if (removed[i]) {
            cannotInvite++;
        }
    }
    
    // Check remaining nodes for bipartite components
    for (int i = 1; i <= n; i++) {
        if (!removed[i] && !visited[i]) {
            auto [isBipartite, count] = checkComponent(i);
            
            if (isBipartite) {
                cannotInvite += count;
            }
        }
    }
    
    cout << cannotInvite << endl;
    
    return 0;
}
