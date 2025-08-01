/*
    ==============
    === MEDIUM ===
    ==============

    ==================================================================
    3372) Maximize the Number of Target Nodes After Connecting Trees I
    ==================================================================

    ============
    Description:
    ============

    There exist two undirected trees with n and m nodes, with distinct labels
    in ranges [0, n - 1] and [0, m - 1], respectively.

    You are given two 2D integer arrays edges1 and edges2 of lengths n - 1 and
    m - 1, respectively, where edges1[i] = [ai, bi] indicates that there is an
    edge between nodes ai and bi in the first tree and edges2[i] = [ui, vi]
    indicates that there is an edge between nodes ui and vi in the second tree.

    You are also given an integer k.

    Node u is target to node v if the number of edges on the path from u to v
    is less than or equal to k. Note that a node is always target to itself.

    Return an array of n integers answer, where answer[i] is the maximum
    possible number of nodes target to node i of the first tree if you have to
    connect one node from the first tree to another node in the second tree.

    =====
    Note: that queries are independent from each other. That is, for every
          query you will remove the added edge before proceeding to the next
          query.
    =====

    ======================================================================================================
    FUNCTION: vector<int> maxTargetNodes(vector<vector<int>>& edges1, vector<vector<int>>& edges2, int k);
    ======================================================================================================

    ==========================================================================
    ================================ EXAMPLES ================================
    ==========================================================================

    --- Example 1 ---
    Input: edges1 = [[0,1],[0,2],[2,3],[2,4]], edges2 = [[0,1],[0,2],[0,3],[2,7],[1,4],[4,5],[4,6]], k = 2
    Output: [9,7,9,8,8]
    Explanation:
        For i = 0, connect node 0 from the first tree to node 0 from the second tree.
        For i = 1, connect node 1 from the first tree to node 0 from the second tree.
        For i = 2, connect node 2 from the first tree to node 4 from the second tree.
        For i = 3, connect node 3 from the first tree to node 4 from the second tree.
        For i = 4, connect node 4 from the first tree to node 4 from the second tree.


    --- Example 2 ---
    nput: edges1 = [[0,1],[0,2],[0,3],[0,4]], edges2 = [[0,1],[1,2],[2,3]], k = 1
    Output: [6,3,3,3,3]
    Explanation:
    For every i, connect node i of the first tree with any node of the second tree.


    *** Constraints ***
    2 <= n, m <= 1000
    edges1.length == n - 1
    edges2.length == m - 1
    edges1[i].length == edges2[i].length == 2
    edges1[i] = [ai, bi]
    0 <= ai, bi < n
    edges2[i] = [ui, vi]
    0 <= ui, vi < m
    The input is generated such that edges1 and edges2 represent valid trees.
    0 <= k <= 1000

*/

#include <algorithm>
#include <vector>
using namespace std;

/*
    ------------
    --- IDEA ---
    ------------

    TODO

*/

/* Time  Beats: 81.57% */
/* Space Beats: 83.41% */

/* Time  Complexity: O(N^2 + M^2) */
/* Space Complexity: O(N^2 + M^2) */
class Solution {
public:
    vector<int> maxTargetNodes(vector<vector<int>>& edges1,
                               vector<vector<int>>& edges2, int k)
    {
        const int N = edges1.size() + 1;
        const int M = edges2.size() + 1;

        vector<int> count1 = build(edges1, k  );
        vector<int> count2 = build(edges2, k-1);

        int max_count2 = *max_element(count2.begin(), count2.end());

        vector<int> result(N);
        for (int node = 0; node < N; node++)
            result[node] = count1[node] + max_count2;

        return result;
    }

private:
    int dfs(int node, int parent, const vector<vector<int>>& children, int k)
    {
        if (k < 0)
            return 0;

        int result = 1;
        for (int child : children[node])
        {
            if (child == parent)
                continue;

            result += dfs(child, node, children, k-1);
        }

        return result;
    }

    vector<int> build(const vector<vector<int>>& edges, int k)
    {
        int N = edges.size() + 1;

        vector<vector<int>> children(N);
        for (const auto& edge : edges)
        {
            children[edge[0]].push_back(edge[1]);
            children[edge[1]].push_back(edge[0]);
        }

        vector<int> result(N);
        for (int i = 0; i < N; i++)
            result[i] = dfs(i, -1, children, k);

        return result;
    }
};
