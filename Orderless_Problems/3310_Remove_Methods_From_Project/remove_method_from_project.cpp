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
#include <unordered_map>
#include <vector>
using namespace std;

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
class Solution {
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
