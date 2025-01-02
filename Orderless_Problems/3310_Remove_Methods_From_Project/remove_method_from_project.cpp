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
#include <unordered_set>
#include <vector>
using namespace std;

/*
    ------------
    --- IDEA ---
    ------------

    This one is not difficult if you know how to create an Adjacency List and
    know how to do a basic DFS.

    First, we need to "mark", or as I've put it "contaminate", all the sus ones
    by starting from k-th method which is initially the only "suspicious' one.

    After doing that, we have all the "suspicious" ones in HashSet "sus".
    If the size of it is equal to 'n', then that means that all of the methods
    are suspicious now and therefore we can remove all of them, thus we return
    an empty vector.

    However, if not all of them are "sus", then start from healthy ones, i.e.
    ones that are not present int HashSet "sus" and iterate through "sus"
    neighbors of those healthy ones and "heal"(i.e. make healthy) all of those
    "sus" nodes which are pointed by the healthy node.

    At the end we are checking:

        if (n - healthy.size() < sus.size())
            Then it's true that some "sus" node is pointing at the healthy one
            and therefore we are NOT allowed to remove it, therefore since we
            are not able to remove ALL of the "sus" methods, we should return
            all 'n' ones as a result. (We are using "iota" function for
           convenience, even if it's not required of us to return the methods in
           order)


        else
            we return all the healthy ones as a result, since we can indeed
            remove all of the "sus" ones.

*/

/* Time  Beats: 37.35% */
/* Space Beats: 16.70% */

/* Time  Complexity: O(V + E) */
/* Space Complexity: O(V + E) */
class Solution {
public:
    vector<int> remainingMethods(int n, int k, vector<vector<int>>& invocations)
    {
        std::unordered_map<int, std::vector<int>> adj_list;

        /* Create an Adjacency List */
        for (auto& entry : invocations)
            adj_list[entry[0]].push_back(entry[1]);

        unordered_set<int> sus;
        sus.insert(k); // The initially suspicious one

        dfs_contaminate(adj_list, sus, k, -1);

        if (sus.size() == n)
            return {};

        unordered_set<int> healthy;
        for (int method = 0; method < n; method++)
        {
            if (sus.count(method) || healthy.count(method))
                continue; // Skip "contaminated"(i.e. suspicious) ones

            dfs_make_healthy(adj_list, sus, healthy, method, -1);
        }

        if (n - healthy.size() < sus.size())
        {
            vector<int> result(n);
            iota(result.begin(), result.end(), 0);

            return result;
        }

        vector<int> result(healthy.begin(), healthy.end());
        return result;
    }

private:
    void dfs_contaminate(unordered_map<int, vector<int>>& adj_list, unordered_set<int>& sus, int curr_method, int prev_method)
    {
        for (const int& neighbor : adj_list[curr_method])
        {
            if (neighbor == prev_method)
                continue; 

            if (sus.count(neighbor))
                continue;

            sus.insert(neighbor);
            dfs_contaminate(adj_list, sus, neighbor, curr_method);
        }
    }

    void dfs_make_healthy(unordered_map<int, vector<int>>& adj_list, unordered_set<int>& sus,  unordered_set<int>& healthy, int curr_method, int prev_method)
    {
        if (healthy.count(curr_method))
            return;

        healthy.insert(curr_method);

        for (const int& neighbor : adj_list[curr_method])
        {
            if (neighbor == prev_method)
                continue; 

            if (healthy.count(neighbor))
                continue; // Skip this healthy one

            if (sus.count(neighbor))
                dfs_make_healthy(adj_list, sus, healthy, neighbor, curr_method);
        }
    }
};
