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

    TODO

*/

/* Time  Beats: 98.03% */
/* Space Beats: 72.29% */

/* Time  Complexity: O(n) */
/* Space Complexity: O(n) */
class Solution_MTH_BFS {
public:
    vector<int> findMinHeightTrees(int n, vector<vector<int>>& edges)
    {
        if(n == 0)
            return {};
        else if(n == 1)
            return {0};

        vector<int> result;

        vector<vector<int>> adj(n);
        vector<int> degrees(n, 0);

        for (int i = 0; i < edges.size(); i++)
        {
            adj[edges[i][0]].push_back(edges[i][1]); // Creating adjacent list
            adj[edges[i][1]].push_back(edges[i][0]);

            degrees[edges[i][1]]++; // Updating how many edges each node has
            degrees[edges[i][0]]++;
        }

        queue<int>queue;
        for (int i = 0; i < n; i++)
        {
            if (degrees[i] == 1) // Adding all the leaf nodes
                queue.push(i);
        }

        while (!queue.empty())
        {
            /* Clear vector before we start traversing level by level */
            result.clear();

            int size = queue.size();
            for (int i = 0; i < size; i++)
            {
                int curr = queue.front();
                queue.pop();

                /*
                    Goal is to get a vector of just 1 or 2 nodes avaiable.
                */
                result.push_back(curr); // Adding nodes to vector.

                for (auto& neighbor : adj[curr])
                {
                    degrees[neighbor]--;        // Removing currrent leaf nodes

                    if (degrees[neighbor] == 1) // Adding currrent leaf nodes
                        queue.push(neighbor);
                }
            }
        }

        return result;
    }
};
