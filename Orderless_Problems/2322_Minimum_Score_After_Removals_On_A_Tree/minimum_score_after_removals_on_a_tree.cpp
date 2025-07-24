/*
    ============
    === HARD ===
    ============

    ============================================
    2322) Minimum Score After Removals on a Tree
    ============================================

    ============
    Description:
    ============

    There is an undirected connected tree with n nodes labeled from 0 to n - 1
    and n - 1 edges.

    You are given a 0-indexed integer array nums of length n where nums[i]
    represents the value of the ith node. You are also given a 2D integer array
    edges of length n - 1 where edges[i] = [ai, bi] indicates that there is an
    edge between nodes ai and bi in the tree.

    Remove two distinct edges of the tree to form three connected components.
    For a pair of removed edges, the following steps are defined:

        + Get the XOR of all the values of the nodes for each of the three
          components respectively.

        + The difference between the largest XOR value and the smallest XOR
          value is the score of the pair.

        For example, say the three components have the node values:
        [4,5,7], [1,9], and [3,3,3]. The three XOR values are
        4 ^ 5 ^ 7 = 6, 1 ^ 9 = 8, and 3 ^ 3 ^ 3 = 3. The largest XOR value is 8
        and the smallest XOR value is 3. The score is then 8 - 3 = 5.

    Return the minimum score of any possible pair of edge removals on the given
    tree.

    ==========================================================================
    FUNCTION: int minimumScore(vector<int>& nums, vector<vector<int>>& edges);
    ==========================================================================

    ==========================================================================
    ================================ EXAMPLES ================================
    ==========================================================================

    --- Example 1 ---
    Input: nums = [1,5,5,4,11], edges = [[0,1],[1,2],[1,3],[3,4]]
    Output: 9
    Explanation: The diagram above shows a way to make a pair of removals.
    - The 1st component has nodes [1,3,4] with values [5,4,11]. Its XOR value is 5 ^ 4 ^ 11 = 10.
    - The 2nd component has node [0] with value [1]. Its XOR value is 1 = 1.
    - The 3rd component has node [2] with value [5]. Its XOR value is 5 = 5.
    The score is the difference between the largest and smallest XOR value which is 10 - 1 = 9.
    It can be shown that no other pair of removals will obtain a smaller score than 9.

    --- Example 2 ---
    Input: nums = [5,5,2,4,4,2], edges = [[0,1],[1,2],[5,2],[4,3],[1,3]]
    Output: 0
    Explanation: The diagram above shows a way to make a pair of removals.
    - The 1st component has nodes [3,4] with values [4,4]. Its XOR value is 4 ^ 4 = 0.
    - The 2nd component has nodes [1,0] with values [5,5]. Its XOR value is 5 ^ 5 = 0.
    - The 3rd component has nodes [2,5] with values [2,2]. Its XOR value is 2 ^ 2 = 0.
    The score is the difference between the largest and smallest XOR value which is 0 - 0 = 0.
    We cannot obtain a smaller score than 0.


    *** Constraints ***
    n == nums.length
    3 <= n <= 1000
    1 <= nums[i] <= 10^8
    edges.length == n - 1
    edges[i].length == 2
    0 <= ai, bi < n
    ai != bi
    edges represents a valid tree.

*/

#include <vector>
#include <algorithm>
#include <unordered_set>
#include <climits>

using namespace std;

/*
    ------------
    --- IDEA ---
    ------------

    The Brute-force would be to build the tree using DSU(Disjoint set Union)
    for every possible removal.

    Since there are n-1 edgesm which we can consider N, in order to pick which
    two DISTINCT to remove, we know we have: "n choose k" possibilities.

    That is:

            (n)         n!
            ( ) = --------------
            (2)    2! * (n - 2)!


    This grows QUADRATICALLY, which means there are N^2 of them.


    That means we have to do our DSU which is O(N) exactly N^2 times(for each
    distinct combination of three connected components).

    That makes it O(N^3) which is unacceptable since n=1000.
    Since n is up to 1000, we know our Time Complexity target goal is O(N^2).

    The key insight is that the structure of the components is always the same
    relative to the cuts. When we cut an edge, we sever a subtree from the rest
    of the tree. If we could instantly know the XOR sum of any subtree, we
    could solve this much faster.

    This leads to a two-phase strategy:

        + Pre-computation Phase: Go through the tree once and calculate the XOR
                                 sum for every possible subtree. We'll use a
                                 single Depth First Search (DFS) for this.
                                 While we're at it, we'll also figure out which
                                 nodes belong to which subtree(the descendants)

        + Calculation Phase: Iterate through all valid pairs of edges to cut.
                             Using our pre-computed data, we can find the XOR
                             sums of the three resulting components in constant
                             O(1) time.

    Think of it like cooking: instead of running to the store for each
    ingredient while making a dish, we get everything ready on the counter
    first. Our DFS is the prep work!
*/

/* Time  Beats: 27.77% */
/* Space Beats: 18.25% */

/* Time  Complexity: O(N^2) */
/* Space Complexity: O(N^2) */
class Solution {
public:
    vector<vector<int>> adj_list;
    vector<int> subtree_xor;
    vector<unordered_set<int>> descendants;

    int minimumScore(vector<int>& nums, vector<vector<int>>& edges)
    {
        const int N = nums.size();

        adj_list.assign(N, vector<int>());
        subtree_xor.assign(N, 0);
        descendants.assign(N, unordered_set<int>());

        for (const auto& edge : edges)
        {
            /* Since the Tree has UNDIRECTED edges */
            adj_list[edge[0]].push_back(edge[1]);
            adj_list[edge[1]].push_back(edge[0]);
        }

        /* Pre-components Phase */
        dfs(0, -1, nums);

        /* Calculation Phase */
        int total_xor = subtree_xor[0];
        int result = INT_MAX;
        for (int i = 1; i < N; i++)
        {
            for (int j = i+1; j < N; j++)
            {
                int xor_i = subtree_xor[i];
                int xor_j = subtree_xor[j];

                int val1;
                int val2;
                int val3;

                if (descendants[i].count(j)) // j is in i's subtree
                {
                    val1 = xor_j;
                    val2 = xor_i ^ xor_j;
                    val3 = total_xor ^ xor_i;
                }
                else if (descendants[j].count(i)) // i is in j's subtree
                {
                    val1 = xor_i;
                    val2 = xor_j ^ xor_i;
                    val3 = total_xor ^ xor_j;
                }
                else // Independent subtrees
                {
                    val1 = xor_i;
                    val2 = xor_j;
                    val3 = total_xor ^ xor_i ^ xor_j;
                }

                int score = max( {val1, val2, val3} ) - min( {val1, val2, val3} );
                result = min(result, score);
            }
        }

        return result;
    }

private:
    void dfs(int node, int parent, const vector<int>& nums)
    {
        subtree_xor[node] = nums[node];
        descendants[node].insert(node);

        for (int neighbor : adj_list[node])
        {
            if (neighbor == parent)
                continue;

            dfs(neighbor, node, nums);
            subtree_xor[node] ^= subtree_xor[neighbor]; // XOR with the neighbor

            /* Add all of the current node's descendants as my descendants as well */
            descendants[node].insert(descendants[neighbor].begin(), descendants[neighbor].end());
        }
    }
};
