/*
    ==============
    === MEDIUM ===
    ==============

    ===========================
    310) Minimum Height Trees
    ===========================

    ============
    Description:
    ============

    A tree is an undirected graph in which any two vertices are connected by
    exactly one path. In other words, any connected graph without simple cycles
    is a tree.

    Given a tree of n nodes labelled from 0 to n - 1, and an array of n - 1
    edges where edges[i] = [ai, bi] indicates that there is an undirected edge
    between the two nodes ai and bi in the tree, you can choose any node of the
    tree as the root. When you select a node x as the root, the result tree has
    height h. Among all possible rooted trees, those with minimum height (i.e.
    min(h))  are called minimum height trees (MHTs).

    Return a list of all MHTs' root labels. You can return the answer in any
    order.

    The height of a rooted tree is the number of edges on the longest downward
    path between the root and a leaf.

    ============================================================================
    FUNCTION: vector<int> findMinHeightTrees(int n, vector<vector<int>>& edges);
    ============================================================================

    ==========================================================================
    ================================ EXAMPLES ================================
    ==========================================================================

    --- Example 1 ---
    Input: n = 4, edges = [[1,0],[1,2],[1,3]]
    Output: [1]
    Explanation: As shown, the height of the tree is 1 when the root is the
    node with label 1 which is the only MHT.


    --- Example 2 ---
    Input: n = 6, edges = [[3,0],[3,1],[3,2],[3,4],[5,4]]
    Output: [3,4]


    *** Constraints ***
    1 <= n <= 2 * 10^4
    edges.length == n - 1
    0 <= ai, bi < n
    ai != bi
    All the pairs (ai, bi) are distinct.
    The given input is guaranteed to be a tree and there will be no repeated
    edges.

*/

#include <vector>
#include <queue>
using namespace std;

/*
    ------------
    --- IDEA ---
    ------------

    Doing a Kahn's Algorithm, i.e. Topological sort, however since we're
    dealing with UNDIRECTED edges, we're NOT pushing elements with degree[node]
    == 0, but degree[node] == 1, as those are the "leaves".

    Then we slowly go inwards.

*/

/* Time  Beats: 13.11% */
/* Space Beats: 11.46% */

/* Time  Complexity: O(V + E) */
/* Space Complexity: O(V + E) */
class Solution_Topological_Sort__Kahn_Algorithm {
public:
    vector<int> findMinHeightTrees(int n, vector<vector<int>>& edges)
    {
        const int E = edges.size();

        if (n == 1)
            return {0};

        if (E == 1)
            return {0, 1};

        /* Build an Adjacency List */
        vector<vector<int>> adj_list(n, vector<int>());
        vector<int> degree(n, 0);

        for (const auto& edge : edges)
        {
            const int& a = edge[0];
            const int& b = edge[1];

            /* Undirected edge */
            adj_list[a].push_back(b);
            adj_list[b].push_back(a);

            ++degree[a];
            ++degree[b];
        }

        queue<int> queue;

        for (int node = 0; node < n; node++)
        {
            if (degree[node] == 1)
                queue.push(node);
        }

        vector<int> result;
        while ( ! queue.empty())
        {
            result.clear();
            int level_size = queue.size();

            for (int i = 0; i < level_size; i++)
            {
                int node = queue.front();
                queue.pop();

                result.push_back(node);

                for (const int& neighbor : adj_list[node])
                {
                    --degree[neighbor];

                    if (degree[neighbor] == 1)
                        queue.push(neighbor);
                }
            }
        }

        return result;
    }
};
