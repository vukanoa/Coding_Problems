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

#include <vector>
using namespace std;

/*
    ------------
    --- IDEA ---
    ------------

    This is a typical Union_&_Find(aka "Disjoint-Set Union") Problem.

    If you haven't done "Number of Connected Components in an Undirected Graph"
    do that first.

*/

/* Time  Beats: 100.00% */
/* Space Beats:  53.63% */

/* Time  Complexity: O(E * alpha(V)) */
/* Space Complexity: O(E)            */
class DSU {
private:
    vector<int> rank;
    vector<int> parent;

public:
    DSU(int n)
    {
        rank.resize(n+1);
        parent.resize(n+1);

        for (int i = 1; i <= n; i++)
        {
            rank[i]   = 1;
            parent[i] = i;
        }
    }

    int find_root(int node)
    {
        while (node != parent[node])
        {
            /* Reverse Ackerman function, i.e. <= 5 in practice */
            parent[node] = parent[parent[node]];

            node = parent[node];
        }

        return node;
    }

    bool union_components(int node_1, int node_2)
    {
        int root_1 = find_root(node_1);
        int root_2 = find_root(node_2);

        if (root_1 == root_2)
            return false;

        if (rank[root_1] < rank[root_2])
            swap(root_1, root_2);

        parent[root_2] = root_1;
        rank[root_1]  += rank[root_2];

        return true;
    }

    bool already_connected(int node_1, int node_2)
    {
        return find_root(node_1) == find_root(node_2);
    }
};

class Solution_dsuuu {
public:
    vector<int> findRedundantConnection(vector<vector<int>>& edges)
    {
        const int N = edges.size();

        DSU dsu(N);

        for (const auto& edge : edges)
        {
            if (dsu.already_connected(edge[0], edge[1]))
                return edge; // Because there's AT MOST ONE extra edge

            dsu.union_components(edge[0], edge[1]);
        }

        return {}; // Unreachable
    }
};
