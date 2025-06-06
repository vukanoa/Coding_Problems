/*
    ==============
    === MEDIUM ===
    ==============

    ===================================================================
    3067) Count Pairs of Connectable Servers In A Weighted Tree Network
    ===================================================================

    ============
    Description:
    ============

    You are given an unrooted weighted tree with n vertices representing servers
    numbered from 0 to n - 1, an array edges where edges[i] = [ai, bi, weighti]
    represents a bidirectional edge between vertices ai and bi of weight
    weighti. You are also given an integer signalSpeed.

    Two servers a and b are connectable through a server c if:

        + a < b, a != c and b != c.
        + The distance from c to a is divisible by signalSpeed.
        + The distance from c to b is divisible by signalSpeed.
        + The path from c to b and the path from c to a do not share any edges.

    Return an integer array count of length n where count[i] is the number of
    server pairs that are connectable through the server i

    ==================================================================================================
    FUNCTION: vector<int> countPairsOfConnectableServers(vector<vector<int>>& edges, int signalSpeed);
    ==================================================================================================

    ==========================================================================
    ================================ EXAMPLES ================================
    ==========================================================================

    --- Example 1 ---
    Input: edges = [[0,1,1],[1,2,5],[2,3,13],[3,4,9],[4,5,2]], signalSpeed = 1
    Output: [0,4,6,6,4,0]
    Explanation: Since signalSpeed is 1, count[c] is equal to the number of
                 pairs of paths that start at c and do not share any edges. In
                 the case of the given path graph, count[c] is equal to the
                 number of servers to the left of c multiplied by the servers
                 to the right of c.


    --- Example 2 ---
    Input: edges = [[0,6,3],[6,5,3],[0,3,1],[3,2,7],[3,1,6],[3,4,2]], signalSpeed = 3
    Output: [2,0,0,0,0,0,2]
    Explanation: Through server 0, there are 2 pairs of connectable servers:
                 (4, 5) and (4, 6). Through server 6, there are 2 pairs of
                 connectable servers: (4, 5) and (0, 5). It can be shown that
                 no two servers are connectable through servers other than 0
                 and 6.


    *** Constraints ***
    2 <= n <= 1000
    edges.length == n - 1
    edges[i].length == 3
    0 <= ai, bi < n
    edges[i] = [ai, bi, weighti]
    1 <= weighti <= 10^6
    1 <= signalSpeed <= 10^6
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

/* Time  Beats: 52.17% */
/* Space Beats: 89.67% */

/* Time  Complexity: O(N^2) */
/* Space Complexity: O(N)   */
class Solution {
public:
    vector<int> countPairsOfConnectableServers(vector<vector<int>>& edges, int signal_speed)
    {
        const int N = edges.size() + 1;
        vector<int> count(N);

        vector<vector<pair<int, int>>> adj_list(N);
        for (const auto& edge : edges)
        {
            int u = edge[0];
            int v = edge[1];
            int w = edge[2];

            adj_list[u].push_back({v, w});
            adj_list[v].push_back({u, w});
        }

        for (int root_server = 0; root_server < N; root_server++)
        {
            count[root_server] = dfs(root_server, root_server, 0, signal_speed, adj_list);
        }

        return count;
    }

private:
    int dfs( int curr, int parent, int curr_path_len, int& signal_speed, vector<vector<pair<int, int>>>& adjacency_list)
    {
        int is_divisible_path = curr_path_len > 0 && curr_path_len % signal_speed == 0;
        int total_valid_pairs = 0;

        for (const auto& [neighbor, edge_weight] : adjacency_list[curr])
        {
            if (neighbor != parent)
            {
                int valid_paths_from_subtree = dfs(neighbor, curr, curr_path_len + edge_weight, signal_speed, adjacency_list);

                total_valid_pairs += is_divisible_path * valid_paths_from_subtree;
                is_divisible_path += valid_paths_from_subtree;
            }
        }

        return curr == parent ? total_valid_pairs : is_divisible_path;
    }
};
