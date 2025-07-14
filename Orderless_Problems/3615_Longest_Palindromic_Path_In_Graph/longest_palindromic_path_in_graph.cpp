/*
    ============
    === HARD ===
    ============

    =======================================
    3615) Longest Palindromic Path in Graph
    =======================================

    ============
    Description:
    ============

    You are given an integer n and an undirected graph with n nodes labeled
    from 0 to n - 1 and a 2D array edges, where edges[i] = [ui, vi] indicates
    an edge between nodes ui and vi.

    You are also given a string label of length n, where label[i] is the
    character associated with node i.

    You may start at any node and move to any adjacent node, visiting each node
    at most once.

    Return the maximum possible length of a
    that can be formed by visiting a set of unique nodes along a valid path.

    ======================================================================
    FUNCTION: int maxLen(int n, vector<vector<int>>& edges, string label);
    ======================================================================

    ==========================================================================
    ================================ EXAMPLES ================================
    ==========================================================================

    --- Example 1 ---
    Input: n = 3, edges = [[0,1],[1,2]], label = "aba"
    Output: 3
    Explanation:
    The longest palindromic path is from node 0 to node 2 via node 1, following
    the path 0 → 1 → 2 forming string "aba". This is a valid palindrome of
    length 3.

    --- Example 2 ---
    Input: n = 3, edges = [[0,1],[0,2]], label = "abc"
    Output: 1
    Explanation:
    No path with more than one node forms a palindrome.
    The best option is any single node, giving a palindrome of length 1.

    --- Example 3 ---
    Input: n = 4, edges = [[0,2],[0,3],[3,1]], label = "bbac"
    Output: 3
    Explanation:
    The longest palindromic path is from node 0 to node 1, following the path
    0 → 3 → 1, forming string "bcb".
    This is a valid palindrome of length 3.


    *** Constraints ***
    1 <= n <= 14
    n - 1 <= edges.length <= n * (n - 1) / 2
    edges[i] == [ui, vi]
    0 <= ui, vi <= n - 1
    ui != vi
    label.length == n
    label consists of lowercase English letters.
    There are no duplicate edges.

*/

#include <cstring>
#include <string>
#include <unordered_set>
#include <vector>
using namespace std;

/*
    ------------
    --- IDEA ---
    ------------

    TODO

*/

/* Time  Beats:  50.00% */
/* Space Beats: 100.00% */

/* Time  Complexity: O(N * 2^N) */
/* Space Complexity: O(N)       */
class Solution {
private:
    bool memo[1 << 14]; // Because constraints say: 1 <= n <= 14

public:
int result = 0;
    int maxLen(int n, vector<vector<int>>& edges, string label)
    {
        vector<unordered_set<int>> adj_list(n);
        for (const auto& edge : edges)
        {
            adj_list[edge[0]].insert(edge[1]);
            adj_list[edge[1]].insert(edge[0]);
        }

        for (int node = 0; node < n; node++)
        {
            memset(memo, 0, sizeof(memo));

            vector<bool> visited_one(n, false);
            solve(node, node, adj_list, label, 0, visited_one);

            for (int neighbor : adj_list[node])
            {
                if (node < neighbor && label[node] == label[neighbor])
                {
                    vector<bool> visited_two(n, false);
                    solve(node, neighbor, adj_list, label, 0, visited_two);
                }
            }
        }

        return result;
    }        

private:
    void solve(int node_i, int node_j, vector<unordered_set<int>>& adj_list, const string& label, uint mask, vector<bool>& visited)
    {
        mask |= (1 << node_i) | (1 << node_j);

        if (__exchange(memo[mask], true)) // If memo[mask] is already true, then return
            return;

        visited[node_i] = visited[node_j] = true;

        // __popcount returns the number of set-bits in a number
        result = max(result, __popcount(mask));

        for (int neighbor_one : adj_list[node_i])
        {
            if (visited[neighbor_one])
                continue;

            for (int neighbor_two : adj_list[node_j])
            {
                if (visited[neighbor_two])
                    continue;

                if (neighbor_one != neighbor_two && label[neighbor_one] == label[neighbor_two])
                    solve(neighbor_one, neighbor_two, adj_list, label, mask, visited);
            }
        }

        visited[node_i] = visited[node_j] = false;
    }
};
