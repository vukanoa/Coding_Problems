/*
    ============
    === HARD ===
    ============

    =========================================
    3108) Minimum Cost Walk in Weighted Graph
    =========================================

    ============
    Description:
    ============

    There is an undirected weighted graph with n vertices labeled from 0 to
    n - 1.

    You are given the integer n and an array edges, where
    edges[i] = [ui, vi, wi] indicates that there is an edge between vertices
    ui and vi with a weight of wi.

    A walk on a graph is a sequence of vertices and edges. The walk starts and
    ends with a vertex, and each edge connects the vertex that comes before it
    and the vertex that comes after it. It's important to note that a walk may
    visit the same edge or vertex more than once.

    The cost of a walk starting at node u and ending at node v is defined as
    the bitwise AND of the weights of the edges traversed during the walk.

    In other words, if the sequence of edge weights encountered during the walk
    is w0, w1, w2, ..., wk, then the cost is calculated as:

        w0 & w1 & w2 & ... & wk,

    where & denotes the bitwise AND operator.

    You are also given a 2D array query, where query[i] = [si, ti].
    For each query, you need to find the minimum cost of the walk starting at
    vertex si and ending at vertex ti. If there exists no such walk, the
    answer is -1.

    Return the array answer, where answer[i] denotes the minimum cost of a walk
    for query i.

    =================================================================================================
    FUNCTION: vector<int> minimumCost(int n, vector<vector<int>>& edges, vector<vector<int>>& query);
    =================================================================================================

    ==========================================================================
    ================================ EXAMPLES ================================
    ==========================================================================

    --- Example 1 ---
    Input: n = 5, edges = [[0,1,7],[1,3,7],[1,2,1]], query = [[0,3],[3,4]]
    Output: [1,-1]

    --- Example 2 ---
    Input: n = 3, edges = [[0,2,7],[0,1,15],[1,2,6],[1,2,1]], query = [[1,2]]
    Output: [0]

    --- Example 3 ---


    *** Constraints ***
    2 <= n <= 10^5
    0 <= edges.length <= 10^5
    edges[i].length == 3
    0 <= ui, vi <= n - 1
    ui != vi
    0 <= wi <= 10^5
    1 <= query.length <= 10^5
    query[i].length == 2
    0 <= si, ti <= n - 1
    si != ti

*/

#include <vector>
using namespace std;

/*
    ------------
    --- IDEA ---
    ------------

    TODO

*/

/* Time  Beats: 61.69% */
/* Space Beats: 92.21% */

/* Time  Complexity: O(M + Q) */  // M - number of edges, Q - number of queries
/* Space Complexity: O(N)     */
class Solution {
public:
    vector<int> parent;
    vector<int> depth;

    vector<int> minimumCost(int n, vector<vector<int>>& edges, vector<vector<int>>& queries)
    {
        vector<int> answer;

        parent.resize(n, -1);
        depth.resize(n, 0);

        vector<unsigned int> component_cost(n, -1);

        for (auto& edge : edges)
            Union(edge[0], edge[1]);

        for (auto& edge : edges)
        {
            int root = Find(edge[0]);
            component_cost[root] &= edge[2];
        }

        for (auto& query : queries)
        {
            int start = query[0];
            int end   = query[1];

            if (Find(start) != Find(end))
            {
                answer.push_back(-1);
            }
            else
            {
                int root = Find(start);
                answer.push_back(component_cost[root]);
            }
        }

        return answer;
    }

private:
    int Find(int node)
    {
        if (parent[node] == -1)
            return node;

        return parent[node] = Find(parent[node]);
    }

    void Union(int node1, int node2)
    {
        int root1 = Find(node1);
        int root2 = Find(node2);

        if (root1 == root2)
            return;

        if (depth[root1] < depth[root2])
            swap(root1, root2);

        parent[root2] = root1;

        if (depth[root1] == depth[root2])
            depth[root1]++;
    }
};
