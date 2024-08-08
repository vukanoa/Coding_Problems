#include <iostream>
#include <vector>

/*
    ==============
    === MEDIUM ===
    ==============

    ====================================
    442) Find All Duplicates In An Array
    ====================================

    ============
    Description:
    ============

    Given an integer array nums of length n where all the integers of nums are
    in the range [1, n] and each integer appears once or twice, return an array
    of all the integers that appears twice.

    You must write an algorithm that runs in O(n) time and uses only constant
    extra space.

    ========================================================
    FUNCTION: vector<int> findDuplicates(vector<int>& nums); 
    ========================================================

    ==========================================================================
    ================================ EXAMPLES ================================
    ==========================================================================

    --- Example 1 ---
    Input: nums = [4,3,2,7,8,2,3,1]
    Output: [2,3]

    --- Example 2 ---
    Input: nums = [1,1,2]
    Output: [1]

    --- Example 3 ---
    Input: nums = [1]
    Output: []


    *** Constraints ***
    n == nums.length
    1 <= n <= 10^5
    1 <= nums[i] <= n
    Each element in nums appears once or twice.

*/

/*
    ------------
    --- IDEA ---
    ------------

    TODO

*/

/* Time  Beats: 99.19% */
/* Space Beats: 77.32% */

/* Time  Complexity: O(n) */
/* Space Complexity: O(1) */
class Solution {
public:
    vector<int> findDuplicates(vector<int>& nums)
    {
        ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0); // Accelerates
        
        const int n = nums.size();
        vector<int> results;

        for (int i = 0; i < n; i++)
        {
            if (nums[abs(nums[i]) - 1] < 0)
                results.push_back(abs(nums[i]));
            else
                nums[abs(nums[i]) - 1] *= -1;
        }
    
        return results;
    }
};
