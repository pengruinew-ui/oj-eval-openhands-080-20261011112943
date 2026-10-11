#include <iostream>
#include <vector>
#include <set>
#include <algorithm>

using namespace std;

int main() {
    int n, m;
    cin >> n >> m;
    
    // Create adjacency list for the graph
    vector<set<int>> adj(n + 1);
    
    // Read the m edges
    for (int i = 0; i < m; i++) {
        int x, y;
        cin >> x >> y;
        adj[x].insert(y);
        adj[y].insert(x);
    }
    
    // Count vertices that can be part of an odd cycle
    vector<bool> canBeInOddCycle(n + 1, false);
    
    // For each vertex, check if it can be in an odd cycle
    for (int start = 1; start <= n; start++) {
        // Skip isolated vertices
        if (adj[start].empty()) continue;
        
        // Use BFS to check for odd cycles
        vector<int> color(n + 1, -1); // -1: unvisited, 0/1: colors
        vector<int> dist(n + 1, -1);  // distance from start
        
        color[start] = 0;
        dist[start] = 0;
        
        vector<int> queue = {start};
        int front = 0;
        
        bool foundOddCycle = false;
        
        while (front < queue.size() && !foundOddCycle) {
            int u = queue[front++];
            
            for (int v : adj[u]) {
                if (color[v] == -1) {
                    color[v] = color[u] ^ 1;
                    dist[v] = dist[u] + 1;
                    queue.push_back(v);
                } else if (color[v] == color[u]) {
                    // Found an odd cycle
                    foundOddCycle = true;
                    break;
                }
            }
        }
        
        if (foundOddCycle) {
            // Mark all vertices in the connected component as able to be in odd cycle
            for (int i = 0; i < queue.size(); i++) {
                canBeInOddCycle[queue[i]] = true;
            }
        }
    }
    
    // Count vertices that cannot be in any odd cycle
    int count = 0;
    for (int i = 1; i <= n; i++) {
        if (!canBeInOddCycle[i]) {
            count++;
        }
    }
    
    cout << count << endl;
    
    return 0;
}