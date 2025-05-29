/*
    ============
    === HARD ===
    ============

    ===================================================================
    3373) Maximize the Number of Target Nodes After Connecting Trees II
    ===================================================================

    ============
    Description:
    ============

    There exist two undirected trees with n and m nodes, labeled from
    [0, n - 1] and [0, m - 1], respectively.

    You are given two 2D integer arrays edges1 and edges2 of lengths n - 1 and
    m - 1, respectively, where edges1[i] = [ai, bi] indicates that there is an
    edge between nodes ai and bi in the first tree and edges2[i] = [ui, vi]
    indicates that there is an edge between nodes ui and vi in the second tree.

    Node u is target to node v if the number of edges on the path from u to v
    is even. Note that a node is always target to itself.

    Return an array of n integers answer, where answer[i] is the maximum
    possible number of nodes that are target to node i of the first tree if
    you had to connect one node from the first tree to another node in the
    second tree.

    =====
    Note: that queries are independent from each other. That is, for every
          query you will remove the added edge before proceeding to the next
          query.
    =====

    ===============================================================================================
    FUNCTION: vector<int> maxTargetNodes(vector<vector<int>>& edges1, vector<vector<int>>& edges2);
    ===============================================================================================

    ==========================================================================
    ================================ EXAMPLES ================================
    ==========================================================================

    --- Example 1 ---
    Input: edges1 = [[0,1],[0,2],[2,3],[2,4]], edges2 = [[0,1],[0,2],[0,3],[2,7],[1,4],[4,5],[4,6]]
    Output: [8,7,7,8,8]
    Explanation:
        For i = 0, connect node 0 from the first tree to node 0 from the second tree.
        For i = 1, connect node 1 from the first tree to node 4 from the second tree.
        For i = 2, connect node 2 from the first tree to node 7 from the second tree.
        For i = 3, connect node 3 from the first tree to node 0 from the second tree.
        For i = 4, connect node 4 from the first tree to node 4 from the second tree.


    --- Example 2 ---
    Input: edges1 = [[0,1],[0,2],[0,3],[0,4]], edges2 = [[0,1],[1,2],[2,3]]
    Output: [3,6,6,6,6]
    Explanation:
    For every i, connect node i of the first tree with any node of the second tree.


    *** Constraints ***
    2 <= n, m <= 10^5
    edges1.length == n - 1
    edges2.length == m - 1
    edges1[i].length == edges2[i].length == 2
    edges1[i] = [ai, bi]
    0 <= ai, bi < n
    edges2[i] = [ui, vi]
    0 <= ui, vi < m
    The input is generated such that edges1 and edges2 represent valid trees.

*/

#include <vector>
using namespace std;

/*
    ------------
    --- IDEA ---
    ------------

    TODO

*/

/* Time  Beats: 92.51% */
/* Space Beats: 52.06% */

/* Time  Complexity: O(N + M) */
/* Space Complexity: O(N + M) */
class Solution {
public:
    vector<int> maxTargetNodes(vector<vector<int>>& edges1, vector<vector<int>>& edges2)
    {
        const int N = edges1.size() + 1;
        const int M = edges2.size() + 1;

        vector<int> color1(N);
        vector<int> color2(M);

        vector<int> count1 = build(edges1, color1);
        vector<int> count2 = build(edges2, color2);

        vector<int> result(edges1.size() + 1);
        for (int i = 0; i < N; i++)
            result[i] = count1[color1[i]] + max(count2[0], count2[1]);

        return result;
    }

private:
    int dfs(int node, int parent, int depth, const vector<vector<int>>& children, vector<int>& color)
    {
        int result = 1 - depth % 2;

        color[node] = depth % 2;
        for (int child : children[node])
        {
            if (child == parent)
                continue;

            result += dfs(child, node, depth + 1, children, color);
        }

        return result;
    }

    vector<int> build(const vector<vector<int>>& edges, vector<int>& color)
    {
        const int N = edges.size() + 1;
        vector<vector<int>> children(N);

        for (const auto& edge : edges)
        {
            children[edge[0]].push_back(edge[1]);
            children[edge[1]].push_back(edge[0]);
        }

        int result = dfs(0, -1, 0, children, color);

        return {result, N - result};
    }
};
