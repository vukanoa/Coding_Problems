/*
    ============
    === HARD ===
    ============

    ==================================================
    3910) Count Connected Subgraphs with Even Node Sum
    ==================================================

    ============
    Description:
    ============


    You are given an undirected graph with n nodes labeled from 0 to n - 1.
    Node i has a value of nums[i], which is either 0 or 1. The edges of the
    graph are given by a 2D array edges where edges[i] = [ui, vi] represents an
    edge between node ui and node vi.

    For a non-empty subset s of nodes in the graph, we consider the induced
    subgraph of s generated as follows:

        + We keep only the nodes in s.
        + We keep only the edges whose two endpoints are both in s.

    Return an integer representing the number of non-empty subsets s of nodes
    in the graph such that:

        + The induced subgraph of s is connected.
        + The sum of node values in s is even.

    ==============================================================================
    FUNCTION: int evenSumSubgraphs(vector<int>& nums, vector<vector<int>>& edges);
    ==============================================================================

    ==========================================================================
    ================================ EXAMPLES ================================
    ==========================================================================

    --- Example 1 ---
    Input: nums = [1,0,1], edges = [[0,1],[1,2]]
    Output: 2
    s        connected?    sum of node values    counted?
    [0]        Yes                1                No
    [1]        Yes                0                Yes
    [2]        Yes                1                No
    [0,1]      Yes                1                No

    [0,2]      No,node 0 and
               node 2 are
               disconnected.      2                No

    [1,2]      Yes                1                No
    [0,1,2]    Yes                2                Yes


    --- Example 2 ---
    Input: nums = [1], edges = []
    Output: 0


    *** Constraints ***
    1 <= n == nums.length <= 13
    nums[i] is 0 or 1.
    0 <= edges.length <= n * (n - 1) / 2
    edges[i] = [ui, vi]
    0 <= ui < vi < n
    All edges are distinct.

*/

#include <vector>
using namespace std;

/*
    ------------
    --- IDEA ---
    ------------

    Since constraints for 'n' are small (i.e. 13), in order to get every
    possible combination of nodes, we treat each of the 2^n binary
    representations (i.e. [0..2^n - 1]) as a distinct combination of present
    nodes in the graph.

    Imagine that we're having a 0-based indexing, but from the RIGHT.

        011001 --> Subgraph of nodes: 4, 3 and 0.
        543210 <-- indices

    For each combination, we're using a DSU data structure and we're merging
    ONLY the edges which have BOTH od the nodes present in our subgraph(i.e.
    our current combination).

    How, then, do we know whether those specific nodes are connected?

    At the beginning there are exactly 'n' components. Let's say n=8 and let's
    say our bitmask is 0b11100000, i.e. Node 7, node 6 and node 5 are
    connected.

    The 0s will remain separate components, so there will be 5 of them, however
    if we successfully connected all three of our 1s from thsi combination,
    then we'll have (n - 0s + 1), i.e. (8 - 5 + 1) = 4 components.

    That's why I've added a "number_of_components" in our DSU data structure.

    If "number_of_components" is equal to (n - 0s + 1), then that means all of
    the 1s form a SINGLE component.

    Now we only need to check whether the total SUM of this connected component
    of 1s is EVEN or not.

    To do that, I've added "sum" vector in our DSU data structure along side
    traditional "parent" and "size"(sometimes "rank") vectors.

    Each node "i" has a sum of nums[i] at the beginning, and each time we
    connect two nodes(or components), we add the total sum of that smaller
    component to the sum of the new, bigger, component.

    At the end we simply check whether this SINGLE component, that is formed by
    1s in this combination, has a total SUM that is even.

    If both conditions are met, we count that combination.

    Special case is only for single nodes because our "node" variable will NOT
    be assigned, since no edge can satisfy both conditions, and thus will
    remain -1.

    In that case, we only check whether that node itself has a an even SUM.

    If it does, ++result.

*/

/* Time  Beats: 53.22% */
/* Space Beats: 58.26% */

/* Time  Complexity: O(2^V * (V  +  E * alpha(V))) */
/* Space Complexity: O(V)                          */
class DSU {
private:
    vector<int> parent;
    vector<int> size;
    vector<int> sum;
    int components;

public:
    DSU (int n, vector<int>& nums)
    {
        components = n;

        parent.resize(n);
        size.resize(n);
        sum.resize(n);

        for (int i = 0; i < n; i++)
        {
            parent[i] = i;
            size[i]   = 1;
            sum[i]    = nums[i];
        }
    }

    int find_root(int node)
    {
        while (node != parent[node])
        {
            /* Inverse Ackerman function, <= 5 for all practical Inputs */
            parent[node] = parent[parent[node]]; // O(alpha(V)) --> O(1)

            node = parent[node];
        }

        return node;
    }

    bool union_components(int node_1, int node_2)
    {
        int root_1 = find_root(node_1); // O(alpha(V)) --> O(1)
        int root_2 = find_root(node_2); // O(alpha(V)) --> O(1)

        if (root_1 == root_2)
            return false;

        if (size[root_1] < size[root_2])
            swap(root_1, root_2);

        parent[root_2] = root_1;
        size[root_1]  += size[root_2];
        sum[root_1]   += sum[root_2];
        
        --components;

        return true;
    }

    int number_of_components()
    {
        return components;
    }

    int sum_of_component(int node)
    {
        int root = find_root(node);

        return sum[root];
    }

    bool are_connected(int node_1, int node_2)
    {
        int root_1 = find_root(node_1);
        int root_2 = find_root(node_2);

        return root_1 == root_2;
    }
};

class Solution {
public:
    int evenSumSubgraphs(vector<int>& nums, vector<vector<int>>& edges)
    {
        const int n = nums.size();
        int result = 0;

        for (int bitmask = 1; bitmask < (1 << n); bitmask++)
        {
            DSU dsu(n, nums);

            int node = -1;
            for (const auto& edge : edges)
            {
                const int& u = edge[0];
                const int& v = edge[1];

                if ((bitmask & (1 << u)) == 0 ||
                    (bitmask & (1 << v)) == 0)
                {
                    continue;
                }

                node = u; // ANY node that is a part of this subgraph
                dsu.union_components(u, v);
            }

            int set_bits = __builtin_popcount(bitmask);

            if (set_bits == 1)
            {
                node = __builtin_ctz(bitmask);

                if (dsu.sum_of_component(node) % 2 == 0)
                    ++result;
            }
            else
            {
                if (node == -1)
                    continue;

                if (dsu.number_of_components() == (n - set_bits + 1) && dsu.sum_of_component(node) % 2 == 0)
                    ++result;
            }
        }

        return result;
    }
};
