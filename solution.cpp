#include <iostream>
#include <vector>
#include <queue>
using namespace std;

const int MAXN = 100005;
vector<int> adj[MAXN];
int color[MAXN];
bool inCycle[MAXN];
int degree[MAXN];
int n, m;

bool checkBipartite(int start, vector<int>& component) {
    queue<int> q;
    q.push(start);
    color[start] = 0;
    component.push_back(start);
    bool bipartite = true;
    
    while (!q.empty()) {
        int u = q.front();
        q.pop();
        
        for (int v : adj[u]) {
            if (!inCycle[v]) continue;
            
            if (color[v] == -1) {
                color[v] = 1 - color[u];
                component.push_back(v);
                q.push(v);
            } else if (color[v] == color[u]) {
                bipartite = false;
            }
        }
    }
    
    return bipartite;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    
    cin >> n >> m;
    
    for (int i = 1; i <= n; i++) {
        color[i] = -1;
        inCycle[i] = false;
        degree[i] = 0;
    }
    
    for (int i = 0; i < m; i++) {
        int x, y;
        cin >> x >> y;
        if (x == y) continue;
        adj[x].push_back(y);
        adj[y].push_back(x);
        degree[x]++;
        degree[y]++;
    }
    
    // Mark all nodes as potentially in cycles
    for (int i = 1; i <= n; i++) {
        inCycle[i] = true;
    }
    
    // Remove nodes with degree <= 1 iteratively
    queue<int> q;
    for (int i = 1; i <= n; i++) {
        if (degree[i] <= 1) {
            q.push(i);
            inCycle[i] = false;
        }
    }
    
    while (!q.empty()) {
        int u = q.front();
        q.pop();
        
        for (int v : adj[u]) {
            if (inCycle[v]) {
                degree[v]--;
                if (degree[v] <= 1) {
                    q.push(v);
                    inCycle[v] = false;
                }
            }
        }
    }
    
    // Count nodes not in cycles
    int answer = 0;
    for (int i = 1; i <= n; i++) {
        if (!inCycle[i]) {
            answer++;
        }
    }
    
    // Check remaining nodes (in cycles) for bipartiteness
    for (int i = 1; i <= n; i++) {
        if (inCycle[i] && color[i] == -1) {
            vector<int> component;
            bool bipartite = checkBipartite(i, component);
            
            if (bipartite) {
                // This component only has even cycles
                answer += component.size();
            }
        }
    }
    
    cout << answer << endl;
    
    return 0;
}
