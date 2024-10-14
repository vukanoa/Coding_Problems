#include <iostream>
#include <vector>

/*
    ==============
    === MEDIUM ===
    ==============

    =============================
    368) Largest Divisible Subset
    =============================

    ============
    Description:
    ============

    Given a set of distinct positive integers nums, return the largest subset
    answer such that every pair (answer[i], answer[j]) of elements in this
    subset satisfies:

        answer[i] % answer[j] == 0, or
        answer[j] % answer[i] == 0

    If there are multiple solutions, return any of them.

    ================================================================
    FUNCTION: vector<int> largestDivisibleSubset(vector<int>& nums); 
    ================================================================

    ==========================================================================
    ================================ EXAMPLES ================================
    ==========================================================================

    --- Example 1 ---
    Input: nums = [1,2,3]
    Output: [1,2]
    Explanation: [1,3] is also accepted.

    --- Example 2 ---
    Input: nums = [1,2,4,8]
    Output: [1,2,4,8]


    *** Constraints ***
    1 <= nums.length <= 1000
    1 <= nums[i] <= 2 * 10^9
    All the integers in nums are unique.

*/

/*
    ------------
    --- IDEA ---
    ------------

    TODO

*/

/* Time  Beats: 16.09% */
/* Space Beats:  9.71% */

/* Time  Complexity: O(n^2) */
/* Space Complexity: O(n^2) */
class Solution {
public:
    vector<int> largestDivisibleSubset(vector<int>& nums)
    {
        int size = nums.size();
        sort(nums.begin(), nums.end(), [](const int val1, const int val2)->bool{
            return val1 > val2;
        });

        vector<vector<int>> mult_chain(size);
        int max_chain_size = 0;

        for (int curr_idx = 0; curr_idx < size; curr_idx++)
        {
            vector<int> curr_chain = {nums[curr_idx]};

            int max_prev_chain_size = 0;
            int max_prev_chain_idx = -1;

            for (int prev_idx = curr_idx - 1; prev_idx > -1; prev_idx--)
            {
                int curr_chain_size = mult_chain[prev_idx].size();

                if (max_prev_chain_size <  curr_chain_size && nums[prev_idx] % nums[curr_idx] == 0)
                {
                      max_prev_chain_size  = curr_chain_size;
                      max_prev_chain_idx = prev_idx;
                }
            }

            if (max_prev_chain_idx != -1)
            {
                for (auto mult : mult_chain[max_prev_chain_idx])
                    curr_chain.push_back(mult);
            }

            mult_chain[curr_idx] = curr_chain;
            max_chain_size = max(max_chain_size, (int)curr_chain.size());
        }

        for (auto &curr_chain : mult_chain)
        {
            if (max_chain_size == curr_chain.size())
                return curr_chain;
        }

        return {};
    }    
};
