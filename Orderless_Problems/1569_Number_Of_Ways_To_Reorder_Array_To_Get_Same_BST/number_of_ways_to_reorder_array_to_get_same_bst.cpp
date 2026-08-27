/*
    ============
    === HARD ===
    ============

    =====================================================
    1569) Number of Ways to Reorder Array to Get Same BST
    =====================================================

    ============
    Description:
    ============

    Given an array nums that represents a permutation of integers from 1 to n.
    We are going to construct a binary search tree (BST) by inserting the
    elements of nums in order into an initially empty BST. Find the number of
    different ways to reorder nums so that the constructed BST is identical to
    that formed from the original array nums.

        + For example, given nums = [2,1,3], we will have 2 as the root, 1 as a
          left child, and 3 as a right child. The array [2,3,1] also yields the
          same BST but [3,2,1] yields a different BST.

    Return the number of ways to reorder nums such that the BST formed is
    identical to the original BST formed from nums.

    Since the answer may be very large, return it modulo 109 + 7.

    ===========================================
    FUNCTION: int numOfWays(vector<int>& nums);
    ===========================================

    ==========================================================================
    ================================ EXAMPLES ================================
    ==========================================================================

    --- Example 1 ---
    Input: nums = [2,1,3]
    Output: 1
    Explanation: We can reorder nums to be [2,3,1] which will yield the same
                 BST. There are no other ways to reorder nums which will yield
                 the same BST.

    --- Example 2 ---
    Input: nums = [3,4,5,1,2]
    Output: 5
    Explanation: The following 5 arrays will yield the same BST: 
    [3,1,2,4,5]
    [3,1,4,2,5]
    [3,1,4,5,2]
    [3,4,1,2,5]
    [3,4,1,5,2]

    --- Example 3 ---
    Input: nums = [1,2,3]
    Output: 0
    Explanation: There are no other orderings of nums that will yield the same
                 BST.


    *** Constraints ***
    1 <= nums.length <= 1000
    1 <= nums[i] <= nums.length
    All integers in nums are distinct.

*/

#include <vector>
using namespace std;

/*
    ------------
    --- IDEA ---
    ------------

    TODO

*/

/* Time  Beats: 57.35% */
/* Space Beats: 52.45% */

/* Time  Complexity: O(N^2) */
/* Space Complexity: O(N)   */
class Solution {
private:
    const long long MOD = 1e9 + 7;
    vector<vector<long long>> table;

public:
    int numOfWays(vector<int>& nums)
    {
        const int N   = nums.size();
        
        // Pascal triangle
        table.resize(N + 1);

        for (int i = 0; i < N + 1; i++)
        {
            table[i] = vector<long long>(i + 1, 1);

            for (int j = 1; j < i; j++)
                table[i][j] = (table[i-1][j-1] + table[i-1][j]) % MOD;
        }
        
        long long result = dfs(nums);

        return result % MOD - 1;
    }
    
private:
    long long dfs(vector<int>& nums)
    {
        const int N = nums.size();

        if (N <= 2)
            return 1;
        
        vector<int> left;
        vector<int> right;

        for (int i = 1; i < N; i++)
        {
            if (nums[i] < nums[0])
                left.push_back(nums[i]);
            else
                right.push_back(nums[i]);
        }
        
        // Recursion with left subtree and right subtree
        long long left_result  = dfs(left)  % MOD;
        long long right_result = dfs(right) % MOD;
        
        // Look up table and multiple them together
        int left_len = left.size(), right_len = right.size();

        return (((table[N - 1][left_len] * left_result) % MOD) * right_result) % MOD;
    }
};
