/*
    ============
    === HARD ===
    ============

    =================================
    1483) Kth Ancestor of a Tree Node
    =================================

    ============
    Description:
    ============


    You are given a tree with n nodes numbered from 0 to n - 1 in the form of a
    parent array parent where parent[i] is the parent of ith node. The root of
    the tree is node 0. Find the kth ancestor of a given node.

    The kth ancestor of a tree node is the kth node in the path from that node
    to the root node.

    Implement the TreeAncestor class:

        + TreeAncestor(int n, int[] parent) Initializes the object with the
          number of nodes in the tree and the parent array.

        + int getKthAncestor(int node, int k) return the kth ancestor of the
          given node node. If there is no such ancestor, return -1.

    ===============================
    CLASS:
    class TreeAncestor {
    public:
        TreeAncestor(int n, vector<int>& parent)
        {

        }


        int getKthAncestor(int node, int k)
        {

        }
    };
    ===============================

    ==========================================================================
    ================================ EXAMPLES ================================
    ==========================================================================

    --- Example 1 ---
    Input
    ["TreeAncestor", "getKthAncestor", "getKthAncestor", "getKthAncestor"]
    [[7, [-1, 0, 0, 1, 1, 2, 2]], [3, 1], [5, 2], [6, 3]]
    Output
    [null, 1, 0, -1]
    Explanation:
    TreeAncestor treeAncestor = new TreeAncestor(7, [-1, 0, 0, 1, 1, 2, 2]);
    treeAncestor.getKthAncestor(3, 1); // returns 1 which is the parent of 3
    treeAncestor.getKthAncestor(5, 2); // returns 0 which is the grandparent of 5
    treeAncestor.getKthAncestor(6, 3); // returns -1 because there is no such ancestor



    *** Constraints ***
    1 <= k <= n <= 5 * 10^4
    parent.length == n
    parent[0] == -1
    0 <= parent[i] < n for all 0 < i < n
    0 <= node < n
    There will be at most 5 * 10^4 queries.

*/

#include <queue>
#include <vector>
using namespace std;

/*
    ------------
    --- IDEA ---
    ------------

    TODO

*/

/* Time  Beats: 95.19% */
/* Space Beats: 15.05% */

/* Time  Complexity: O(N * logN  +  Q * logN) */
/* Space Complexity: O(N * logN)              */
class TreeAncestor {
private:
    static constexpr int MAX_N = 5 * 1e4;

    int up   [MAX_N + 1][20]; // log2(10^6) = 20
    int depth[MAX_N + 1];

    int LOG;
public:
    TreeAncestor(int n, vector<int>& parent)
    {
        LOG = 0;
        while ((1 << (LOG + 1)) <= n)
            LOG++;
        LOG++;

        /* Build an Adjacency List */
        vector<vector<int>> children(n);
        for (int node = 1; node < n; node++)// Start at 1 since parent[0] == -1
            children[ parent[node] ].push_back(node);

        /* BFS to get the depths */
        depth[0] = 0;

        queue<int> queue;
        queue.push(0);

        while ( ! queue.empty())
        {
            int node = queue.front();
            queue.pop();

            for (const int& child : children[node])
            {
                depth[child] = depth[node] + 1;

                queue.push(child);
            }
        }
        /* --------------------- */

        up[0][0] = 0;
        for (int node = 1; node < n; node++)// Start at 1 since parent[0] == -1
            up[node][0] = parent[node];

        for (int level = 1; level < LOG; level++)
        {
            for (int node = 0; node < n; node++)
            {
                up[node][level] = up[ up[node][level-1] ][level-1];
            }
        }
    }

    
    int getKthAncestor(int node, int k)
    {
        if (depth[node] < k)
            return -1;
        
        for (int level = 0; level < LOG; level++) // eg. 19 = 1 + 2 + 16
        {
            if (k & (1 << level))
                node = up[node][level];
        }

        return node;
    }
};
