#include <iostream>
#include <string>
#include <vector>
#include <stack>
#include <queue>
#include <algorithm>
#include <math.h>
#include <limits>

using namespace std;

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

    int s; //starting point
    cin >> s;

    int visit[n];
    for (int i = 0; i < n; ++i) {
        visit[i] = 0;
    }
    
    queue<int> q; //BFS
    q.push(s);
    visit[s] = 1;

    int cur;
    while (!(q.empty())) {
        cur = q.front();
        visit[cur] = 1;
        q.pop();
        for (int i = 0; i < n; ++i) {
            if (adj[cur][i] != 0 && visit[i] == 0) {
                q.push(i);
            }
        }
    }

    int count = 0;
    for (int i = 0; i < n; ++i) {
        if (visit[i] == 0) {
            count++;
        }
    }

    cout << count << endl;
    
    return 0;
}