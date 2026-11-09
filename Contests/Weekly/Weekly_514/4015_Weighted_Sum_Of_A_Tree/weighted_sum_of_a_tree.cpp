/*
    ==============
    === MEDIUM ===
    ==============

    ============================
    4015) Weighted Sum of a Tree
    ============================

    ============
    Description:
    ============

    You are given an integer array parent of length n representing a rooted
    tree with nodes labeled from 0 to n - 1.

    The tree is rooted at node 0, so parent[0] = -1. For each node i where 1 <=
    i <= n - 1, parent[i] denotes the parent of node i.

    You are also given an integer array nums of length n, where nums[i] denotes
    the value of node i.

    The weight of a node i at depth d is nums[i] * (h - d + 1), where h is the
    height of the tree.

    Return the sum of the weights of all nodes in the tree.

    The depth of a node is the number of nodes on the path from the root to
    that node, inclusive, with the root having depth 1.

    The height of the tree is the maximum depth among all nodes in the tree.

    ========================================================================
    FUNCTION: long long weightedSum(vector<int>& parent, vector<int>& nums);
    ========================================================================

    ==========================================================================
    ================================ EXAMPLES ================================
    ==========================================================================

    --- Example 1 ---
    Input: parent = [-1,0,0,0,2,2], nums = [5,2,3,1,4,6]
    Output: 37

    --- Example 2 ---
    Input: parent = [-1,0,1,2], nums = [1,2,3,4]
    Output: 20


    *** Constraints ***
    1 <= n <= 10^5
    n == parent.length == nums.length
    parent[0] == -1
    0 <= parent[i] <= n - 1 for all i in [1, n - 1]
    1 <= nums[i] <= 10^6
    The input is generated such that the array parent represents a valid tree
    rooted at node 0.

*/

#include <algorithm>
#include <vector>
using namespace std;

/*
    ------------
    --- IDEA ---
    ------------

    TODO

*/

/* Time  Beats: 90.39% */
/* Space Beats: 98.89% */

/* Time  Complexity: O(N) */
/* Space Complexity: O(N) */
class Solution {
public:
    long long weightedSum(vector<int>& parent, vector<int>& nums)
    {
        const int N = nums.size();
        long long result = 0LL;

        vector<int> depth(N, -1);
        depth[0] = 1;
        for (int i = 1; i < N; i++)
            get_depths(i, depth, parent);

        int height = *max_element(depth.begin(), depth.end());

        for (int i = 0; i < N; i++)
            result += 1LL * nums[i] * (height - depth[i] + 1);

        return result;
    }

private:
    int get_depths(int idx, vector<int>& depth, vector<int>& parent)
    {
        if (depth[idx] != -1)
            return depth[idx];

        return depth[idx] = 1 + get_depths(parent[idx], depth, parent);
    }
};
