#include <iostream>
#include <string>
#include <vector>
#include <stack>
#include <queue>
#include <algorithm>
#include <math.h>
#include <limits>

using namespace std;

const int INF = numeric_limits<int>::max();

int main() {
    int m, n;
    cin >> n >> m;
    int adj[n][n];
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++j) {
            adj[i][j] = 0;
        }
    }
    
    int a, b, t; //two connected vertices and edge weight
    for (int i = 0; i < m; ++i) {
        cin >> a >> b >> t;
        adj[a][b] = t;
        adj[b][a] = t;
    }

    int lim[n]; //the time limit of the nodes
    for (int i = 0; i < n; ++i) {
        cin >> lim[i];
    }

    int s, d; //starting point and ending point
    cin >> s >> d;

    vector<int> dist(n, INF);
    dist[s] = 0;

    priority_queue<pair<int, int>, vector<pair<int, int>>, greater<pair<int, int>>> q; //priority queue
    q.push({0, s});

    int cnode, cdist;
    while (!(q.empty())) {
        cdist = q.top().first;
        cnode = q.top().second;
        q.pop();

        if (cdist > dist[cnode]) {
            continue; // if the current distance is greater that the recorded shortest distance, then pass
        }

        for (int i = 0; i < n; ++i) {
            if (adj[cnode][i] != 0) {
                int newdist = cdist + adj[cnode][i];
                if (dist[i] > newdist && newdist < lim[i]) { //update the shortest distance
                    dist[i] = newdist;
                    q.push({newdist, i});
                }
            }
        }
    }

    if (dist[d] == INF) { //INF indicates that this node hasn't been updated, so it is not reachable
        cout << -1 << endl;
    } else {
        cout << dist[d] << endl;
    }
    
    return 0;
}