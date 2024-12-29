/*
    ============
    === HARD ===
    ============

    ===================================================
    3203) Find Minimum Diameter After Merging Two Trees
    ===================================================

    ============
    Description:
    ============

    There exist two undirected trees with n and m nodes, numbered from:
        0 to n - 1 and from 0 to m - 1, respectively.

    You are given two 2D integer arrays edges1 and edges2 of lengths:
        n - 1 and m - 1, respectively, where edges1[i] = [ai, bi] indicates
        that there is an edge between nodes ai and bi in the first tree and
        edges2[i] = [ui, vi] indicates that there is an edge between nodes
        ui and vi in the second tree.

    You must connect one node from the first tree with another node from the
    second tree with an edge.

    Return the minimum possible diameter of the resulting tree.

    The diameter of a tree is the length of the longest path between any two
    nodes in the tree.

    ===============================
    FUNCTION:
    ===============================

    ==========================================================================
    ================================ EXAMPLES ================================
    ==========================================================================

    --- Example 1 ---
    Input: edges1 = [[0,1],[0,2],[0,3]], edges2 = [[0,1]]
    Output: 3
    Explanation:
    We can obtain a tree of diameter 3 by connecting node 0 from the first tree
    with any node from the second tree.


    --- Example 2 ---
    Input: edges1 = [[0,1],[0,2],[0,3],[2,4],[2,5],[3,6],[2,7]],
           edges2 = [[0,1],[0,2],[0,3],[2,4],[2,5],[3,6],[2,7]]
    Output: 5
    Explanation:
    We can obtain a tree of diameter 5 by connecting node 0 from the first tree
    with node 0 from the second tree.


    *** Constraints ***
    1 <= n, m <= 10^5
    edges1.length == n - 1
    edges2.length == m - 1
    edges1[i].length == edges2[i].length == 2
    edges1[i] = [ai, bi]
    0 <= ai, bi < n
    edges2[i] = [ui, vi]
    0 <= ui, vi < m
    The input is generated such that edges1 and edges2 represent valid trees.

*/

#include <cmath>
#include <queue>
#include <vector>
using namespace std;

/*
    ------------
    --- IDEA ---
    ------------

    TODO

*/

/* Time  Beats: 28.97% */
/* Space Beats: 40.19% */

/* Time  Complexity: O(n + m) */
/* Space Complexity: O(n + m) */
class Solution {
public:
    int minimumDiameterAfterMerge(vector<vector<int>>& edges1, vector<vector<int>>& edges2)
    {
        // Calculate the number of nodes for each tree
        const int n = edges1.size() + 1;
        const int m = edges2.size() + 1;

        // Build adjacency lists for both trees
        vector<vector<int>> adj_list1 = build_adj_list(n, edges1);
        vector<vector<int>> adj_list2 = build_adj_list(m, edges2);

        // Calculate the diameters of both trees
        int diameter1 = findDiameter(n, adj_list1);
        int diameter2 = findDiameter(m, adj_list2);

        // Calculate the longest path that spans across both trees
        int combinedDiameter = ceil(diameter1 / 2.0) + ceil(diameter2 / 2.0) + 1;

        // Return the maximum of the three possibilities
        return max( diameter1, max(diameter2, combinedDiameter) );
    }

private:
    vector<vector<int>> build_adj_list(int size, vector<vector<int>>& edges)
    {
        vector<vector<int>> adjList(size);

        for (auto edge : edges)
        {
            adjList[edge[0]].push_back(edge[1]);
            adjList[edge[1]].push_back(edge[0]);
        }

        return adjList;
    }

    // Function to find the diameter of a tree using two BFS calls
    int findDiameter(int n, vector<vector<int>>& adjList)
    {
        // First BFS to find the farthest node from any arbitrary node (e.g., 0)
        auto [farthestNode, b] = find_farthest_node(n, adjList, 0);

        // Second BFS from the farthest node to determine the diameter
        auto [a, diameter] = find_farthest_node(n, adjList, farthestNode);
        return diameter;
    }

    // BFS helper function to find the farthest node and its distance from the
    // source
    pair<int, int> find_farthest_node(int n, vector<vector<int>>& adj_list, int sourceNode)
    {
        queue<int> nodes_queue;
        vector<bool> visited(n, false);
        // Push source node into the queue
        nodes_queue.push(sourceNode);
        visited[sourceNode] = true;

        int max_distance = 0;
        int farthest_node = sourceNode;

        // Explore neighbors
        while ( ! nodes_queue.empty())
        {
            int size = nodes_queue.size();

            for (int i = 0; i < size; i++)
            {
                int curr_node = nodes_queue.front();
                nodes_queue.pop();

                // Update farthest node
                // The farthest node is the last one that was popped out of the
                // queue.
                farthest_node = curr_node;

                for (int neighbor : adj_list[curr_node])
                {
                    // Explore neighbors
                    if ( ! visited[neighbor])
                    {
                        visited[neighbor] = true;
                        nodes_queue.push(neighbor);
                    }
                }
            }

            if ( ! nodes_queue.empty())
                max_distance++;
        }

        return {farthest_node, max_distance};
    }
};
