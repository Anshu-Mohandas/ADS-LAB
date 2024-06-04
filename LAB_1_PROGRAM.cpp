#include <bits/stdc++.h>
using namespace std;

class DisJointSet {
public:
    vector<int> rank, parent;
    int n;

    DisJointSet(int n) {
        this->n = n;
        parent.resize(n);
        for (int i = 0; i < n; i++) {
            parent[i] = i;
        }
        rank.resize(n, 0);
    }

    int findParent(int node) {
        if (parent[node] == node) return node;
        // path compression code
        return parent[node] = findParent(parent[node]);
    }

    void unionR(int u, int v) {
        int pu = findParent(u);
        int pv = findParent(v);
        if (pu == pv) return;
        if (rank[pu] > rank[pv]) {
            parent[pv] = pu;
        } else if (rank[pv] > rank[pu]) {
            parent[pu] = pv;
        } else {
            // increase the rank of the parent node
            parent[pu] = pv;
            rank[pv]++;
        }
    }
};

int main() {
    int m, n;
    cin >> m >> n;
    vector<vector<int>> matrix(m, vector<int>(n, 0));
    for (int i = 0; i < m; i++) {
        for (int j = 0; j < n; j++)
            cin >> matrix[i][j];
    }

    DisJointSet *ds = new DisJointSet(m * n);

    vector<int> row_offsets = {0, 0, 1, 1, 1, -1, -1, -1};
    vector<int> col_offsets = {1, -1, 0, 1, -1, 0, 1, -1};

    for (int i = 0; i < m; i++) {
        for (int j = 0; j < n; j++) {
            if (matrix[i][j] == 1) {
                for (int k = 0; k < 8; k++) {
                    int ni = i + row_offsets[k];
                    int nj = j + col_offsets[k];
                    if (ni >= 0 && ni < m && nj >= 0 && nj < n && matrix[ni][nj] == 1) {
                        ds->unionR(i * n + j, ni * n + nj);
                    }
                }
            }
        }
    }

    int count = 0;
    vector<int> arr(m * n, 0);
    for (int i = 0; i < m; i++) {
        for (int j = 0; j < n; j++) {
            if (matrix[i][j] == 1 && arr[ds->findParent(i * n + j)] == 0) {
                arr[ds->findParent(i * n + j)] = 1;
                count++;
            }
        }
    }

    cout << "Number of islands in the graph is " << count << endl;
    delete ds;
    return 0;
}
