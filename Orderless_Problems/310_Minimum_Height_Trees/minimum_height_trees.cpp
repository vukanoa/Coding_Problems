#include <iostream>
#include <vector>
#include <climits>
#include <queue>

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

/*
    ------------
    --- IDEA ---
    ------------

    Basic DFS, however it is quite obvious that this won't work since we're
    doing a lot of repeated work.

    However, this IDEA comes up to mind at first, so I wanted to include this
    Solution as a Warning not to do it.

*/

/* Time  Complexity: O(n^2) */
/* Space Complexity: O(n) */
class Solution {
public:
    std::vector<int> findMinHeightTrees(int n, std::vector<std::vector<int>>& edges)
    {
        std::vector<std::vector<int>> adj(n, std::vector<int>());

        // Make adjacency list
        for (int i = 0; i < edges.size(); i++)
        {
            adj[edges[i][0]].push_back(edges[i][1]);
            adj[edges[i][1]].push_back(edges[i][0]);
        }

        int min_height = INT_MAX;
        std::vector<std::vector<int>> heights;

        for (int i = 0; i < adj.size(); i++)
        {
            int farthest = 0;

            dfs(adj, i, i, 0, farthest);

            min_height = std::min(min_height, farthest);
            heights.push_back({i, farthest});
        }

        std::vector<int> results;
        for (int i = 0; i < heights.size(); i++)
        {
            if (heights[i][1] == min_height)
                results.push_back(heights[i][0]);
        }

        return results;
    }

private:
    void dfs(std::vector<std::vector<int>>& adj, int curr, int prev, int curr_len, int& farthest)
    {
        farthest = std::max(farthest, curr_len);

        for (int j = 0; j < adj[curr].size(); j++)
        {
            if (adj[curr][j] == prev)
                continue;

            dfs(adj, adj[curr][j], curr, curr_len+1, farthest);
        }
    }
};




/*
    ------------
    --- IDEA ---
    ------------

    Minimum Height Trees.

    How can you prove this statement if the interviewer asks for a proof?

    Basic idea:
        The roots of MHT must be the mid points of the longest leaf to leaf
        path in the tree.

*/

/* Time  Beats: 98.03% */
/* Space Beats: 72.29% */

/* Time  Complexity: O(n) */
/* Space Complexity: O(n) */
class Solution_MTH_BFS {
public:
    std::vector<int> findMinHeightTrees(int n, std::vector<std::vector<int>>& edges)
    {
        if(n == 0)
            return {};
        else if(n == 1)
            return {0};

        std::vector<int> result;

        std::vector<std::vector<int>> adj(n);
        std::vector<int> degrees(n, 0);

        for (int i = 0; i < edges.size(); i++)
        {
            adj[edges[i][0]].push_back(edges[i][1]); // Creating adjacent list
            adj[edges[i][1]].push_back(edges[i][0]);

            degrees[edges[i][1]]++; // Updating how many edges each node has
            degrees[edges[i][0]]++;
        }

        std::queue<int>queue;
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
int
main()
{
    Solution_MTH_BFS sol_mth_bfs;

    /* Example 1 */
    int n = 4;
    std::vector<std::vector<int>> edges = {{1,0},
                                          {1,2},
                                          {1,3}};


    /* Example 2 */
    // int n = 4;
    // std::vector<std::vector<int>> edges = {{1,0},
    //                                       {1,2},
    //                                       {1,3}};


    /* Example 3 */
    // int n = 6;
    // std::vector<std::vector<int>> edges = {{3,0},
    //                                       {3,1},
    //                                       {3,2}};
    //                                       {3,4}};
    //                                       {5,4}};


    /* Example 4 */
    // int n = 10;
    // std::vector<std::vector<int>> edges = {{6, 7},
    //                                        {6, 8},
    //                                        {3, 4},
    //                                        {0, 2},
    //                                        {2, 3},
    //                                        {5, 6},
    //                                        {3, 5},
    //                                        {1, 2},
    //                                        {8, 9}};


    /* Example 5 */
    // int n = 6;
    // std::vector<std::vector<int>> edges = {{0, 3},
    //                                        {1, 2},
    //                                        {2, 3},
    //                                        {3, 4},
    //                                        {4, 5}};


    /* Example 6 */
    // int n = 6;
    // std::vector<std::vector<int>> edges = {{0, 2},
    //                                        {3, 4},
    //                                        {4, 5},
    //                                        {2, 1},
    //                                        {2, 3}};


    /* Example 7 */
    // int n = 2;
    // std::vector<std::vector<int>> edges = {{0, 1}};


    /* Example 8 */
    // int n = 10;
    // std::vector<std::vector<int>> edges = {{0, 1},
    //                                        {1, 2},
    //                                        {2, 3},
    //                                        {3, 4},
    //                                        {4, 5},
    //                                        {5, 6},
    //                                        {6, 7},
    //                                        {7, 8},
    //                                        {8, 9}};


    /* Example 9 */
    // int n = 1;
    // std::vector<std::vector<int>> edges = {};



    std::cout << "\n\t============================";
    std::cout << "\n\t=== MINIMUM HEIGHT TREES ===";
    std::cout << "\n\t============================\n";



    /* Write Input */
    bool first = true;
    std::cout << "\n\tEdges: [";
    for (auto x: edges)
    {
        if (!first)
            std::cout << ", ";

        bool first_first = true;
        std::cout << "[";
        for (const auto& xx : x)
        {
            if (!first_first)
                std::cout << ", ";

            std::cout << xx;
            first_first = false;
        }
        std::cout << "]";

        first = false;
    }
    std::cout << "]\n\n";


    /* Solution */
    std::vector<int> results = sol_mth_bfs.findMinHeightTrees(n, edges);


    /* Write Output */
    first = true;
    std::cout << "\n\tResults: [";
    for (auto x: results)
    {
        if (!first)
            std::cout << ", ";

        std::cout << x;
        first = false;
    }
    std::cout << "]";


    std::cout << "\n\n";
    return 0;
}
