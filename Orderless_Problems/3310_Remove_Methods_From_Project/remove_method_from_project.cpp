/*
    ==============
    === MEDIUM ===
    ==============

    =================================
    3310) Remove Methods From Project
    =================================

    ============
    Description:
    ============

    You are maintaining a project that has n methods numbered from 0 to n - 1.

    You are given two integers n and k, and a 2D integer array invocations,
    where invocations[i] = [ai, bi] indicates that method ai invokes method bi.

    There is a known bug in method k. Method k, along with any method invoked
    by it, either directly or indirectly, are considered suspicious and we aim
    to remove them.

    A group of methods can only be removed if no method outside the group
    invokes any methods within it.

    Return an array containing all the remaining methods after removing all the
    suspicious methods. You may return the answer in any order. If it is not
    possible to remove all the suspicious methods, none should be removed.

    =======================================================================================
    FUNCTION: vector<int> remainingMethods(int n, int k, vector<vector<int>>& invocations);
    =======================================================================================

    ==========================================================================
    ================================ EXAMPLES ================================
    ==========================================================================

    --- Example 1 ---
    Input: n = 4, k = 1, invocations = [[1,2],[0,1],[3,2]]
    Output: [0,1,2,3]
    Explanation: Method 2 and method 1 are suspicious, but they are directly
                 invoked by methods 3 and 0, which are not suspicious.
                 We return all elements without removing anything.

    --- Example 2 ---
    Input: n = 5, k = 0, invocations = [[1,2],[0,2],[0,1],[3,4]]
    Output: [3,4]
    Explanation: Methods 0, 1, and 2 are suspicious and they are not directly
                 invoked by any other method. We can remove them.

    --- Example 3 ---
    Input: n = 3, k = 2, invocations = [[1,2],[0,1],[2,0]]
    Output: []
    Explanation: All methods are suspicious. We can remove them.


    *** Constraints ***
    1 <= n <= 10^5
    0 <= k <= n - 1
    0 <= invocations.length <= 2 * 10^5
    invocations[i] == [ai, bi]
    0 <= ai, bi <= n - 1
    ai != bi
    invocations[i] != invocations[j]

*/

#include <numeric>
#include <queue>
#include <unordered_map>
#include <vector>
using namespace std;

/*
    ------------
    --- IDEA ---
    ------------

    TODO

*/

/* Time  Beats: 58.97% */
/* Space Beats: 57.24% */

/* Time  Complexity: O(E * alpha(V)  +  V * alpha(V)) */
/* Space Complexity: O(V + E)                         */
class DSU {
private:
    vector<int> parent;
    vector<int> size;

    int components;

public:
    DSU (int n)
    {
        components = n;

        size.resize(n);
        parent.resize(n);
        for (int i = 0; i < n; i++)
        {
            parent[i] = i;
            size[i]   = 1;
        }
    }

    int get_root(int node)
    {
        while (node != parent[node])
        {
            /* Inverse Ackerman function, <= 5 for all practical purposes */
            parent[node] = parent[parent[node]];

            node = parent[node];
        }

        return node;
    }

    bool union_components(int node_1, int node_2)
    {
        int root_1 = get_root(node_1);
        int root_2 = get_root(node_2);

        if (root_1 == root_2)
            return false; // We have NOT merged

        if (size[root_1] < size[root_2])
            swap(root_1, root_2);

        parent[root_2] = root_1;
        size[root_1]  += size[root_2];
        components--;

        return true; // We have performed a MERGE(union) between 2 components
    }

    bool connected_components(int node_1, int node_2)
    {
        int root_1 = get_root(node_1);
        int root_2 = get_root(node_2);

        return root_1 == root_2;
    }
};

class Solution {
public:
    vector<int> remainingMethods(int n, int k, vector<vector<int>>& invocations)
    {
        /* Construct DSU data structure */
        DSU dsu(n);

        /* Build an Adjacency List */
        vector<vector<int>> adj_list(n);

        for (const auto& edge : invocations)
        {
            const int& a = edge[0];
            const int& b = edge[1];

            adj_list[a].push_back(b);
            dsu.union_components(a, b);
        }

        vector<int> result;
        result.reserve(n);

        vector<bool> suspicious(n, false);
        dfs(-1, 0, adj_list, suspicious); // Color

        for (const auto& edge : invocations)
        {
            const int& a = edge[0];
            const int& b = edge[1];

            if ( ! suspicious[a] && suspicious[b] && dsu.connected_components(a, b))
            {
                vector<int> result(n);
                iota(result.begin(), result.end(), 0);

                return result;
            }

            if (suspicious[a] && suspicious[b])
                continue;

            result.push_back(a);
        }

        return result;
    }

    void dfs(int prev, int curr, vector<vector<int>>& adj_list, vector<bool>& suspicious)
    {
        suspicious[curr] = true;

        for (const int& neighbor : adj_list[curr])
        {
            if (neighbor == prev)
                continue;

            dfs(curr, neighbor, adj_list, suspicious);
        }
    }
};



/*
    ------------
    --- IDEA ---
    ------------

    TODO

*/

/* Time  Beats: 37.35% */
/* Space Beats: 16.70% */

/* Time  Complexity: O(V + E) */
/* Space Complexity: O(V + E) */
class Solution_DFS_and_Coloring {
public:
    vector<int> remainingMethods(int n, int k, vector<vector<int>>& invocations)
    {
        unordered_map<int, vector<int>> adj_list;

        /* Build an Adjacency List */
        for (auto& edge : invocations)
        {
            const int& a = edge[0];
            const int& b = edge[1];

            adj_list[a].push_back(b);
        }

        vector<bool> suspicious(n, false);
        dfs_contaminate(-1, k, adj_list, suspicious);

        bool all_suspicious = true;
        for (int i = 0; i < n; i++)
        {
            if ( ! suspicious[i])
            {
                all_suspicious = false;
                break;
            }
        }

        if (all_suspicious)
            return {};

        vector<bool> healthy(n, false);

        for (int node = 0; node < n; node++)
        {
            if (suspicious[node]) // Skip the suspicious nodes
                continue;

            if (healthy[node]) // Already healthy
                continue;

            if (dfs_make_healthy(-1, node, adj_list, suspicious, healthy))
            {
                vector<int> result(n);
                iota(result.begin(), result.end(), 0);

                return result;
            }
        }

        vector<int> result;

        for (int node = 0; node < n; node++)
        {
            if ( ! suspicious[node])
                result.push_back(node);
        }

        return result;
    }

private:
    void dfs_contaminate(int prev,
                         int curr,
                         unordered_map<int, vector<int>>& adj_list,
                         vector<bool>& suspicious)
    {
        suspicious[curr] = true;

        for (const int& neighbor : adj_list[curr])
        {
            if (neighbor == prev)
                continue;

            if (suspicious[neighbor])
                continue;

            dfs_contaminate(curr, neighbor, adj_list, suspicious);
        }
    }

    bool dfs_make_healthy(int prev,
                          int curr,
                          unordered_map<int, vector<int>>& adj_list,
                          vector<bool>& suspicious,
                          vector<bool>& healthy)
    {
        healthy[curr] = true;

        for (const int& neighbor : adj_list[curr])
        {
            if (neighbor == prev)
                continue;

            if (suspicious[neighbor])
                return true;

            if (healthy[neighbor])
                continue;

            if (dfs_make_healthy(curr, neighbor, adj_list, suspicious, healthy))
                return true;
        }

        return false;
    }
};




/*
    ------------
    --- IDEA ---
    ------------

    TODO

*/

/* Time  Beats: 45.57% */
/* Space Beats: 82.25% */

/* Time  Complexity: O(N + E) */
/* Space Complexity: O(N + E) */
class Solution_BFS_Coloring {
private:
    static constexpr int MAXN = 100005;

public:
    vector<int> remainingMethods(int n, int k, vector<vector<int>>& invocations)
    {
        /* Build an Adjacency List */
        vector<vector<int>> adj_list(n);

        /* Track incoming edges */
        vector<int> in_degree(n, 0);

        for (const auto& edge : invocations)
        {
            const int& a = edge[0];
            const int& b = edge[1];

            adj_list[a].push_back(b);
            in_degree[b]++;
        }


        /* BFS Color suspicious methods */
        vector<bool> suspicious(n, false);

        queue<int> queue;

        queue.push(k);
        suspicious[k] = true;

        while ( ! queue.empty())
        {
            const int curr = queue.front();
            queue.pop();

            for (const int& neighbor : adj_list[curr])
            {
                in_degree[neighbor]--;

                if ( ! suspicious[neighbor])
                {
                    suspicious[neighbor] = true;
                    queue.push(neighbor);
                }
            }
        }

        /*
            Check if all suspicious methods can be removed.

            If a non-suspicious method invokes a suspicious method,
            then removing suspicious methods is impossible.
        */
        bool can_remove_all = true;

        vector<int> result;
        result.reserve(n);

        for (int i = 0; i < n; i++)
        {
            if (suspicious[i] && in_degree[i] > 0)
            {
                can_remove_all = false;
                break;
            }

            if ( ! suspicious[i])
                result.push_back(i);
        }


        if ( ! can_remove_all)
        {
            vector<int> all_nodes(n);
            iota(all_nodes.begin(), all_nodes.end(), 0);

            return all_nodes;
        }

        return result;
    }
};
