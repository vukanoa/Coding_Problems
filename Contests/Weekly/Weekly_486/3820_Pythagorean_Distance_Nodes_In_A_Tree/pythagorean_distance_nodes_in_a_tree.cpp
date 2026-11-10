/*
    ==============
    === MEDIUM ===
    ==============

    ==========================================
    3820) Pythagorean Distance Nodes in a Tree
    ==========================================

    ============
    Description:
    ============

    You are given an integer n and an undirected tree with n nodes numbered
    from 0 to n - 1. The tree is represented by a 2D array edges of length n -
    1, where edges[i] = [ui, vi] indicates an undirected edge between ui and
    vi.

    You are also given three distinct target nodes x, y, and z.

    For any node u in the tree:

        Let dx be the distance from u to node x
        Let dy be the distance from u to node y
        Let dz be the distance from u to node z

    The node u is called special if the three distances form a Pythagorean
    Triplet.

    Return an integer denoting the number of special nodes in the tree.

    A Pythagorean triplet consists of three integers a, b, and c which, when
    sorted in ascending order, satisfy a2 + b2 = c2.

    The distance between two nodes in a tree is the number of edges on the
    unique path between them.

    ===================================================================================
    FUNCTION: int specialNodes(int n, vector<vector<int>>& edges, int x, int y, int z);
    ===================================================================================

    ==========================================================================
    ================================ EXAMPLES ================================
    ==========================================================================

    --- Example 1 ---
    Input: n = 4, edges = [[0,1],[0,2],[0,3]], x = 1, y = 2, z = 3
    Output: 3
    Explanation:
    For each node, we compute its distances to nodes x = 1, y = 2, and z = 3.
        Node 0 has distances 1, 1, and 1. After sorting, the distances are 1, 1, and 1, which do not satisfy the Pythagorean condition.
        Node 1 has distances 0, 2, and 2. After sorting, the distances are 0, 2, and 2. Since 02 + 22 = 22, node 1 is special.
        Node 2 has distances 2, 0, and 2. After sorting, the distances are 0, 2, and 2. Since 02 + 22 = 22, node 2 is special.
        Node 3 has distances 2, 2, and 0. After sorting, the distances are 0, 2, and 2. This also satisfies the Pythagorean condition.
    Therefore, nodes 1, 2, and 3 are special, and the answer is 3.


    --- Example 2 ---
    Input: n = 4, edges = [[0,1],[1,2],[2,3]], x = 0, y = 3, z = 2
    Output: 0
    Explanation:
    For each node, we compute its distances to nodes x = 0, y = 3, and z = 2.
        Node 0 has distances 0, 3, and 2. After sorting, the distances are 0, 2, and 3, which do not satisfy the Pythagorean condition.
        Node 1 has distances 1, 2, and 1. After sorting, the distances are 1, 1, and 2, which do not satisfy the Pythagorean condition.
        Node 2 has distances 2, 1, and 0. After sorting, the distances are 0, 1, and 2, which do not satisfy the Pythagorean condition.
        Node 3 has distances 3, 0, and 1. After sorting, the distances are 0, 1, and 3, which do not satisfy the Pythagorean condition.
    No node satisfies the Pythagorean condition. Therefore, the answer is 0.


    --- Example 3 ---
    Input: n = 4, edges = [[0,1],[1,2],[1,3]], x = 1, y = 3, z = 0
    Output: 1
    Explanation:
    For each node, we compute its distances to nodes x = 1, y = 3, and z = 0.
        Node 0 has distances 1, 2, and 0. After sorting, the distances are 0, 1, and 2, which do not satisfy the Pythagorean condition.
        Node 1 has distances 0, 1, and 1. After sorting, the distances are 0, 1, and 1. Since 02 + 12 = 12, node 1 is special.
        Node 2 has distances 1, 2, and 2. After sorting, the distances are 1, 2, and 2, which do not satisfy the Pythagorean condition.
        Node 3 has distances 1, 0, and 2. After sorting, the distances are 0, 1, and 2, which do not satisfy the Pythagorean condition.
    Therefore, the answer is 1.


    *** Constraints ***
    4 <= n <= 10^5
    edges.length == n - 1
    edges[i] = [ui, vi]
    0 <= ui, vi, x, y, z <= n - 1
    x, y, and z are pairwise distinct.
    The input is generated such that edges represent a valid tree.

*/

#include <algorithm>
#include <queue>
#include <unordered_set>
#include <vector>
using namespace std;

/*
    ------------
    --- IDEA ---
    ------------

    TODO

*/

/* Time  Beats: 65.50% */
/* Space Beats: 67.83% */

/* Time  Complexity: O(V + E) */
/* Space Complexity: O(V + E) */
class Solution {
public:
    int specialNodes(int n, vector<vector<int>>& edges, int x, int y, int z)
    {
        const int V = n;
        const int E = edges.size();

        /* Build an Adjacency List */
        vector<vector<int>> adj_list(n, vector<int>());

        for (const auto& edge : edges)
        {
            const int& one = edge[0];
            const int& two = edge[1];

            /* UNDIRECTED edge */
            adj_list[one].push_back(two);
            adj_list[two].push_back(one);
        }

        /* BFS */
        vector<int> dist_to_x = bfs(adj_list, x);
        vector<int> dist_to_y = bfs(adj_list, y);
        vector<int> dist_to_z = bfs(adj_list, z);

        /* Count Special nodes */
        int result = 0;
        for (int i = 0; i < n; i++)
        {
            unsigned long long vec[3] = {};

            vec[0] = 1ULL * dist_to_x[i];
            vec[1] = 1ULL * dist_to_y[i];
            vec[2] = 1ULL * dist_to_z[i];

            sort(begin(vec), end(vec));

            if (vec[0] * vec[0]  +  vec[1] * vec[1]  ==  (vec[2] * vec[2]))
                ++result;
        }

        return result;
    }

    vector<int> bfs(const vector<vector<int>>& adj_list, int start_node)
    {
        const int N = adj_list.size();

        vector<int> dist(N, 0);
        vector<bool> visited(N, false);

        queue<int> queue;
        queue.push(start_node);
        visited[start_node] = true;

        int level = 0;
        while ( ! queue.empty())
        {
            int size = queue.size();

            for (int i = 0; i < size; i++)
            {
                int node = queue.front();
                queue.pop();

                dist[node] = level;

                for (const int& neighbor : adj_list[node])
                {
                    if (visited[neighbor])
                        continue;

                    visited[neighbor] = true;
                    queue.push(neighbor);
                }
            }

            ++level;
        }

        return dist;
    }
};
