#include <iostream>
#include <vector>
#include <unordered_map>

/*
    ============
    === EASY ===
    ============

    ===========================
    1512) Number of Good Pairs
    ===========================

    ============
    Description:
    ============

    Given an array of integers nums, return the number of good pairs.

    A pair (i, j) is called good if nums[i] == nums[j] and i < j.

    ===================================================
    FUNCTION: int numIdenticalPairs(vector<int>& nums);
    ===================================================

    ==========================================================================
    ================================ EXAMPLES ================================
    ==========================================================================

    --- Example 1 ---
    Input: nums = [1,2,3,1,1,3]
    Output: 4
    Explanation: There are 4 good pairs (0,3), (0,4), (3,4), (2,5) 0-indexed.

    --- Example 2 ---
    Input: nums = [1,1,1,1]
    Output: 6
    Explanation: Each pair in the array are good.

    --- Example 3 ---
    Input: nums = [1,2,3]
    Output: 0

    *** Constraints ***
    1 <= nums.length <= 100
    1 <= nums[i] <= 100

*/

using namespace std;

/*
    ------------
    --- IDEA ---
    ------------

    If you have X amount of same characters, how many different pairs is there?

        2 - 1
        3 - 3
        4 - 6
        5 - 10
        6 - 15
        7 - 21

        ...

    Formula is: num_of_pairs[i] = i-1 + num_of_pairs[i-1];

*/

/* Time  Beats: 100.00% */
/* Space Beats:   7.73% */

/* Time  Complexity: O(n) */
/* Space Complexity: O(n) */
class Solution {
public:
    int numIdenticalPairs(vector<int>& nums)
    {
        int result = 0;

        vector<int> num_of_pairs(101, 0);
        num_of_pairs[2] = 1;

        for (int i = 3; i < 101; i++)
            num_of_pairs[i] = i-1 + num_of_pairs[i-1];

        unordered_map<int, int> umap;
        for (const int& num : nums)
            umap[num]++;

        for (const auto& entry : umap)
        {
            int number = entry.first;
            int freq   = entry.second;

            if (freq > 1)
                result += num_of_pairs[freq];
        }

        return result;
    }
};
