/*
    ==============
    === MEDIUM ===
    ==============

    ============================
    3607) Power Gird Maintenance
    ============================

    ============
    Description:
    ============

    You are given an integer c representing c power stations, each with a
    unique identifier id from 1 to c (1‑based indexing).

    These stations are interconnected via n bidirectional cables, represented
    by a 2D array connections, where each element connections[i] = [ui, vi]
    indicates a connection between station ui and station vi. Stations that are
    directly or indirectly connected form a power grid.

    Initially, all stations are online (operational).

    You are also given a 2D array queries, where each query is one of the
    following two types:

        + [1, x]: A maintenance check is requested for station x. If station x
          is online, it resolves the check by itself. If station x is offline,
          the check is resolved by the operational station with the smallest id
          in the same power grid as x. If no operational station exists in that
          grid, return -1.

        + [2, x]: Station x goes offline (i.e., it becomes non-operational).

    Return an array of integers representing the results of each query of type
    [1, x] in the order they appear.

    =====
    Note: The power grid preserves its structure; an offline (non‑operational)
          node remains part of its grid and taking it offline does not alter
          connectivity.
    =====

    ============================================================================================================
    FUNCTION: vector<int> processQueries(int c, vector<vector<int>>& connections, vector<vector<int>>& queries);
    ============================================================================================================

    ==========================================================================
    ================================ EXAMPLES ================================
    ==========================================================================

    --- Example 1 ---
    Input: c = 5, connections = [[1,2],[2,3],[3,4],[4,5]], queries = [[1,3],[2,1],[1,1],[2,2],[1,2]]
    Output: [3,2,3]
    Explanation:
        Initially, all stations {1, 2, 3, 4, 5} are online and form a single power grid.
        Query [1,3]: Station 3 is online, so the maintenance check is resolved by station 3.
        Query [2,1]: Station 1 goes offline. The remaining online stations are {2, 3, 4, 5}.
        Query [1,1]: Station 1 is offline, so the check is resolved by the operational station with the smallest id among {2, 3, 4, 5}, which is station 2.
        Query [2,2]: Station 2 goes offline. The remaining online stations are {3, 4, 5}.
        Query [1,2]: Station 2 is offline, so the check is resolved by the operational station with the smallest id among {3, 4, 5}, which is station 3.


    --- Example 2 ---
    Input: c = 3, connections = [], queries = [[1,1],[2,1],[1,1]]
    Output: [1,-1]
    Explanation:
        There are no connections, so each station is its own isolated grid.
        Query [1,1]: Station 1 is online in its isolated grid, so the maintenance check is resolved by station 1.
        Query [2,1]: Station 1 goes offline.
        Query [1,1]: Station 1 is offline and there are no other stations in its grid, so the result is -1.


    *** Constraints ***
    1 <= c <= 10^5
    0 <= n == connections.length <= min(10^5, c * (c - 1) / 2)
    connections[i].length == 2
    1 <= ui, vi <= c
    ui != vi
    1 <= queries.length <= 2 * 10^5
    queries[i].length == 2
    queries[i][0] is either 1 or 2.
    1 <= queries[i][1] <= c

*/

#include <queue>
#include <unordered_map>
#include <vector>
#include <queue>
using namespace std;

/*
    ------------
    --- IDEA ---
    ------------

    Messy implementation, but was done during the contest.
    Below this one will be a properly done one.

*/

/* Time  Beats: 30.25% */
/* Space Beats: 22.72% */

/* Time  Complexity: O((V + E) * Q * logV) */
/* Space Complexity: O(V^2)                */
class Solution {
public:
    vector<int> processQueries(int c, vector<vector<int>>& connections, vector<vector<int>>& queries)
    {
        const int N = connections.size();
        vector<int> result;

        unordered_map<int, vector<int>> adj_list;

        for (auto& entry : connections)
        {
            adj_list[entry[0]].push_back(entry[1]);
            adj_list[entry[1]].push_back(entry[0]);
        }

        vector<bool> visited(c+1, false);
        vector<int>   parent(c+1, -1);

        vector<bool> online(c+1, true);

        unordered_map<int, priority_queue<int, vector<int>, greater<int>>> umap;

        for (int i = 1; i <= c; i++)
        {
            if (visited[i])
                continue;

            priority_queue<int, vector<int>, greater<int>> min_heap;
            dfs(i, adj_list, visited, parent, i, min_heap);

            umap[i] = min_heap;
        }

        for (const auto& q : queries)
        {
            if (q[0] == 1)
            {
                int node = q[1];

                if (online[node])
                    result.push_back(node);
                else
                {
                    int par = parent[node];

                    int smallest = -1;
                    while ( ! umap[par].empty())
                    {
                        auto top = umap[par].top();

                        if ( ! online[top])
                        {
                            umap[par].pop();
                            continue;
                        }

                        smallest = top;
                        break;
                    }

                    // cout << "\n\tOvde sam: " << smallest;
                    result.push_back(smallest);
                }
            }
            else
            {
                online[q[1]] = false;
            }
        }

        return result;
    }

private:
    void dfs(int node,
             unordered_map<int, vector<int>>& adj_list,
             vector<bool>& visited,
             vector<int>& parent,
             int start,
             priority_queue<int, vector<int>, greater<int>>& min_heap)
    {
        visited[node] = true;
        parent[node] = start;

        min_heap.push(node);

        for (const auto& neighbor : adj_list[node])
        {
            if (visited[neighbor])
                continue;

            dfs(neighbor, adj_list, visited, parent, start, min_heap);
        }
    }
};




/*
    ------------
    --- IDEA ---
    ------------

    Even if this one is longer, this is a much more straightfowards
    implementation. It's elegant and much easier to grasp.

    It's much faster in practice, not in Big O notation. Big O is equivalent to
    the one above.

*/

/* Time  Beats: 99.07% */
/* Space Beats: 98.96% */

/* Time  Complexity: O((V + E) * Q * logV) */
/* Space Complexity: O(V^2)                */
class DSU {
public:
    vector<int> parent;

    DSU(int n)
    {
        parent.resize(n + 1);

        for (int i = 0; i <= n; ++i) // Because stations are from [1, n]
            parent[i] = i;
    }

    int find_root_node(int node)
    {
        // Get root parent
        while (node != parent[node])
        {
            // Huge Optimization (From O(n) to Amortized O(1) Time Complexity)
            // If there is no grandparent, nothing will happen
            parent[node] = parent[parent[node]];

            node = parent[node];
        }

        return node;
    }

    bool union_components(int node1, int node2)
    {
        int root1 = find_root_node(node1);
        int root2 = find_root_node(node2);

        if (root1 == root2)
            return false;

        // Make sure that to merge TOWARDS the smaller node, i.e. root1
        parent[root2] = root1;

        return true;
    }
};


class Solution_DSU {
public:
    vector<int> processQueries(int c,
                               vector<vector<int>>& connections,
                               vector<vector<int>>& queries)
    {
        vector<int> result;

        DSU dsu(c);
        vector<bool> online(c + 1, true);

        for (const auto& entry : connections)
        {
            int u = entry[0];
            int v = entry[1];

            dsu.union_components(u, v);
        }

        unordered_map<int, priority_queue<int, vector<int>, greater<int>>> component_root_to_min_heap;
        for (int station = 1; station <= c; station++)
        {
            int root = dsu.find_root_node(station);
            component_root_to_min_heap[root].push(station);
        }

        for (auto& query : queries)
        {
            int type = query[0];
            int node = query[1];

            if (type == 2)
            {
                online[node] = false;
            }
            else
            {
                if (online[node])
                {
                    result.push_back(node);
                }
                else
                {
                    int root = dsu.find_root_node(node);
                    auto& min_heap = component_root_to_min_heap[root];

                    while ( ! min_heap.empty() &&  ! online[min_heap.top()])
                        min_heap.pop();

                    result.push_back(min_heap.empty() ? -1 : min_heap.top());
                }
            }
        }

        return result;
    }
};
