/*
    ==============
    === MEDIUM ===
    ==============

    ==============================================
    4108) Minimum Cost to Make Red Nodes Connected
    ==============================================

    ============
    Description:
    ============

    You are given an integer n representing a tree with n nodes, where the
    nodes are numbered from 0 to n - 1 and the tree is rooted at node 0. The
    tree is represented by a 2D array edges of length n - 1, where edges[i] =
    [ui, vi] indicates an undirected edge between nodes ui and vi.

    You are also given a string colors of length n, where colors[i] represents
    the color of node i: 'R' if it is Red, or 'B' if it is Blue.

    You may flip the color of any node: from 'R' to 'B', or from 'B' to 'R'.
    Flipping node u incurs a cost equal to the size of the subtree of node u.

    Your goal is to perform flips so the Red nodes form a single connected
    component in the tree. Blue nodes may be disconnected. A configuration with
    no Red nodes is also considered valid.

    Return the minimum total cost required to achieve this.

    In a rooted tree, the subtree of a node v is the set of all nodes whose
    path to the root contains v.

    ==============================================================================
    FUNCTION: long long minCost(int n, string colors, vector<vector<int>>& edges);
    ==============================================================================

    ==========================================================================
    ================================ EXAMPLES ================================
    ==========================================================================

    --- Example 1 ---
    Input: n = 3, colors = "RBR", edges = [[0,1],[1,2]]
    Output: 1
    Explanation:
        There are two Red nodes (0 and 2) that are not connected to each other.
        We can flip node 2 from 'R' (Red) to 'B' (Blue). The subtree size of node 2 is 1, so the cost is 1.
        After this flip only node 0 remains Red, forming exactly one connected Red component.

    --- Example 2 ---
    Input: n = 3, colors = "RBR", edges = [[0,1],[0,2]]
    Output: 0
    Explanation:
        There are two Red nodes (0 and 2) that are already connected to each other.
        No flips are needed since all Red nodes already form a single connected group. Thus, the minimum total cost is 0.

    --- Example 3 ---
    Input: n = 4, colors = "BRRR", edges = [[0,1],[0,2],[0,3]]
    Output: 2
    Explanation:
        There are three Red nodes (1, 2 and 3), which are not connected to each other.
        All three Red nodes are leaves and are disconnected from one another.
        To obtain a single Red group, we keep one Red leaf and flip the other two to Blue.
        Each leaf subtree size is 1, so flipping any two costs 2.

    --- Explanation 4 ---
    Input: n = 3, colors = "BBB", edges = [[0,1],[1,2]]
    Output: 0
    Explanation:
        All nodes are Blue, so there are no Red nodes.
        An empty Red group is considered a single connected group, so this state is already valid. Thus, the cost is 0.


    *** Constraints ***
    1 <= n <= 10^5
    n == colors.length
    colors[i] is either 'R' or 'B'.
    edges.length == n - 1
    edges[i] = [ui, vi]
    0 <= ui, vi <= n - 1
    The input is generated such that edges represents a valid tree.

*/

#include <climits>
#include <string>
#include <vector>
#include <algorithm>

using namespace std;

/*
    ------------
    --- IDEA ---
    ------------

    TODO

*/

/* Time  Beats: 100.00% */
/* Space Beats: 100.00% */

/* Time  Complexity: O(N) */
/* Space Complexity: O(N) */
class Solution {
private:
    vector<vector<long long>> dp;
    vector<int> subtree_size;

public:
    long long minCost(int n, string colors, vector<vector<int>>& edges)
    {
        dp.assign(n, vector<long long>(3, 0LL));
        subtree_size.assign(n, 1);

        /* Build an Adjacency List */
        vector<vector<int>> adj_list(n, vector<int>());
        for (const auto& edge : edges)
        {
            const int& one = edge[0];
            const int& two = edge[1];

            adj_list[one].push_back(two);
            adj_list[two].push_back(one);
        }

        /* Solve */
        dfs(0, -1, colors, adj_list);

        return min( {dp[0][0], dp[0][1], dp[0][2]} );
    }

private:
    void dfs(int node, int parent, string& colors, vector<vector<int>>& adj_list)
    {
        long long total_cost_blue = 0LL;
        long long total_cost_red  = 0LL;

        for (const int& neighbor : adj_list[node])
        {
            if (neighbor == parent) continue;

            /* From here "neighbor" is a CHILD of "node" */
            const int& child = neighbor;

            dfs(child, node, colors, adj_list);

            subtree_size[node] += subtree_size[child];

            total_cost_blue += dp[child][0];
            total_cost_red  += min(dp[child][0], dp[child][1]);
        }

        long long cost_to_make_curr_node_red  = (colors[node] == 'R') ? 0LL : subtree_size[node];
        long long cost_to_make_curr_node_blue = (colors[node] == 'B') ? 0LL : subtree_size[node];

        dp[node][0] = cost_to_make_curr_node_blue + total_cost_blue; // Cost to CONVERT entire subtree to be BLUE
        dp[node][1] = cost_to_make_curr_node_red  + total_cost_red;  // Cost to CONVERT entire subtree to be RED
        dp[node][2] = LLONG_MAX;

        for (const int& neighbor : adj_list[node])
        {
            if (neighbor == parent)
                continue;

            /* From here "neighbor" is a CHILD of "node" */
            const int& child = neighbor;

            // dp[node][2] represents the minimum cost when the subtree is
            // entirely BLUE except for at most one child subtree, which is
            // allowed to be RED (using either dp[child][1] or dp[child][2]).
            long long isolated_red_cost = min(dp[child][1], dp[child][2]);
            dp[node][2] = min(dp[node][2],
                              dp[node][0] - dp[child][0] + isolated_red_cost);
        }
    }
};
