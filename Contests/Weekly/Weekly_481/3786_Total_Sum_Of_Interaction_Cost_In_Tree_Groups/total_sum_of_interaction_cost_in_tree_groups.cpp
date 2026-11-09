/*
    ============
    === HARD ===
    ============

    ==================================================
    3786) Total Sum of Interaction Cost in Tree Groups
    ==================================================

    ============
    Description:
    ============

    You are given an integer n and an undirected tree with n nodes numbered
    from 0 to n - 1. This is represented by a 2D array edges of length n - 1,
    where edges[i] = [ui, vi] indicates an undirected edge between nodes ui and
    vi.

    You are also given an integer array group of length n, where group[i]
    denotes the group label assigned to node i.

        + Two nodes u and v are considered part of the same group if
          group[u] == group[v].

        + The interaction cost between u and v is defined as the number of
          edges on the unique path connecting them in the tree.

    Return an integer denoting the sum of interaction costs over all unordered
    pairs (u, v) with u != v such that group[u] == group[v].

    ============================================================================================
    FUNCTION: long long interactionCosts(int n, vector<vector<int>>& edges, vector<int>& group);
    ============================================================================================

    ==========================================================================
    ================================ EXAMPLES ================================
    ==========================================================================

    --- Example 1 ---
    Input: n = 3, edges = [[0,1],[1,2]], group = [1,1,1]
    Output: 4
    Explanation:
    All nodes belong to group 1. The interaction costs between the pairs of
    nodes are:
        Nodes (0, 1): 1
        Nodes (1, 2): 1
        Nodes (0, 2): 2
    Thus, the total interaction cost is 1 + 1 + 2 = 4.


    --- Example 2 ---
    Input: n = 3, edges = [[0,1],[1,2]], group = [3,2,3]
    Output: 2
    Explanation:
        Nodes 0 and 2 belong to group 3. The interaction cost between this pair
        is 2.
        Node 1 belongs to a different group and forms no valid pair. Therefore,
        the total interaction cost is 2.


    --- Example 3 ---
    Input: n = 4, edges = [[0,1],[0,2],[0,3]], group = [1,1,4,4]
    Output: 3
    Explanation:
    Nodes belonging to the same groups and their interaction costs are:
        Group 1: Nodes (0, 1): 1
        Group 4: Nodes (2, 3): 2
    Thus, the total interaction cost is 1 + 2 = 3.


    --- Example 4 ---
    Input: n = 2, edges = [[0,1]], group = [9,8]
    Output: 0
    Explanation:
    All nodes belong to different groups and there are no valid pairs. Therefore, the total interaction cost is 0.



    *** Constraints ***
    1 <= n <= 10^5
    edges.length == n - 1
    edges[i] = [ui, vi]
    0 <= ui, vi <= n - 1
    group.length == n
    1 <= group[i] <= 20
    The input is generated such that edges represents a valid tree.

*/

#include <vector>
using namespace std;

/*
    ------------
    --- IDEA ---
    ------------

    TODO

*/

/* Time  Beats: 75.29% */
/* Space Beats: 84.71% */

/* Time  Complexity: O((V + E) * 21) --> ((V + V) * 1) --> (2*V) --> O(V) */
/* Space Complexity: O((V + E) * 21) --> ((V + V) * 1) --> (2*V) --> O(V) */ 
class Solution {
private:
    static constexpr int MAX_N = 1e5;
    long long total_cost = 0;

    int subtree_group_counts[MAX_N + 1][21] = {};
    int total_nodes_in_group[21] = {};

    vector<vector<int>> adj_list;

public:
    long long interactionCosts(int n, vector<vector<int>>& edges, vector<int>& group)
    {
        const int V = n;
        const int E = edges.size(); // But it's ALWAYS (V-1) so it can be treated as V.

        /* Create an Adjacency List */
        adj_list.assign(n, vector<int>());

        for (const auto& edge : edges)
        {
            const int& u = edge[0];
            const int& v = edge[1];

            /* UNDIRECTED edge */
            adj_list[u].push_back(v);
            adj_list[v].push_back(u);
        }

        for (const int& g : group)
            ++total_nodes_in_group[g];

        dfs(0, -1, group);

        return total_cost;
    }

private:
    void dfs(int node, int parent, vector<int>& group)
    {
        subtree_group_counts[node][group[node]] = 1;

        for (const int& neighbor : adj_list[node])
        {
            if (neighbor == parent)
                continue;

            const int& child = neighbor;
            
            /* Postorder DFS */
            dfs(child, node, group);
            
            for (int g = 1; g <= 20; g++)
            {
                if (total_nodes_in_group[g] < 2)
                    continue;
                
                long long nodes_of_curr_group_inside_child_subtree  = subtree_group_counts[child][g];
                long long nodes_of_curr_group_outside_child_subtree = total_nodes_in_group[g] - nodes_of_curr_group_inside_child_subtree;
                
                // This is the amount of PAIRS that pass thorugh the CURRENT EDGE
                long long pairs_of_curr_group_with_one_node_inside_and_one_node_outside_child_subtree = nodes_of_curr_group_inside_child_subtree *
                                                                                                        nodes_of_curr_group_outside_child_subtree;

                total_cost += pairs_of_curr_group_with_one_node_inside_and_one_node_outside_child_subtree;

                subtree_group_counts[node][g] += nodes_of_curr_group_inside_child_subtree;
            }
        }
    }
};
