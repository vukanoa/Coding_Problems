#include <iostream>
#include <vector>

/*
    ==============
    === MEDIUM ===
    ==============

    ===========================
    684) Redundant Connection
    ===========================

    ============
    Description:
    ============

    In this problem, a tree is an undirected graph that is connected and has no
    cycles.

    You are given a graph that started as a tree with n nodes labeled from 1 to
    n, with one additional edge added. The added edge has two different
    vertices chosen from 1 to n, and was not an edge that already existed. The
    graph is represented as an array edges of length n where edges[i] = [ai,
    bi] indicates that there is an edge between nodes ai and bi in the graph.

    Return an edge that can be removed so that the resulting graph is a tree of
    n nodes. If there are multiple answers, return the answer that occurs last
    in the input.

    ==========================================================================
    FUNCTION: vector<int> findRedundantConnection(vector<vector<int>>& edges);
    ==========================================================================

    ==========================================================================
    ================================ EXAMPLES ================================
    ==========================================================================

    --- Example 1 ---

            1 --- 2
            |   /
            |  /
            | /
            |/
            3

    Input: edges = [[1,2],[1,3],[2,3]]
    Output: [2,3]

    --- Example 2 ---

            2 --- 1 --- 5
            |     |
            |     |
            |     |
            3 --- 4

    Input: edges = [[1,2],[2,3],[3,4],[1,4],[1,5]]
    Output: [1,4]


    *** Constraints ***
    n == edges.length
    3 <= n <= 1000
    edges[i].length == 2
    1 <= ai < bi <= edges.length
    ai != bi
    There are no repeated edges.
    The given graph is connected.

*/

/*
    ------------
    --- IDEA ---
    ------------

    This is a typical Union_&_Find Problem.

    If you haven't done "Number of Connected Components in an Undirected Graph"
    do that first.

    There is a detailed Explanation(IDEA) about how and why Union_&_Find works.

    One small thing I've changed in this Implementation of Union_&_Find is that
    in "Find" function, I only have one line in body of a "while loop".

    But, for didactic purposes, it is better to write it as two liners as in
    the "Number of Connected Components in an Undirected Graph" version of this
    Solution.

*/

/* Time  Beats: 90.67% */
/* Space Beats: 79.01% */

/* Time  Complexity: O(N) */
/* Space Complexity: O(N) */
class Solution {
public:
    std::vector<int> findRedundantConnection(std::vector<std::vector<int>>& edges)
    {
        const int N = edges.size();

        std::vector<int> parent(N+1);
        std::vector<int> rank(N+1, 1);

        // parent = [0, 1, 2, 3, ..., n]
        std::iota(parent.begin(), parent.end(), 0);

        std::vector<int> result;
        for (const auto& edge : edges)
        {
            int node_1 = edge[0];
            int node_2 = edge[1];

            if (! Union(node_1, node_2, parent, rank))
                result = edge;
        }

        return result;
    }

private:
    int Find(int node, std::vector<int>& parent)
    {
        while (node != parent[node])
            node = parent[parent[node]]; // We can write it in one line instead

        return node;
    }

    bool Union(int node_1, int node_2, std::vector<int>& parent, std::vector<int>& rank)
    {
        int p1 = Find(node_1, parent);
        int p2 = Find(node_2, parent);

        if (p1 == p2)
            return false;

        if (rank[p2] > rank[p1])
        {
            parent[p1] = parent[p2];
            rank[p2] += rank[p1];
        }
        else // rank[p1] > rank[p2]
        {
            parent[p2] = parent[p1];
            rank[p1] += rank[p2];
        }

        return true;
    }
};
