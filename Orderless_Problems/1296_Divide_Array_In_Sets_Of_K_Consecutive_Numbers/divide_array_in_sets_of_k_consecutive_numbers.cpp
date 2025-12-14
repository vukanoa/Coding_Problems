/*
    ==============
    === MEDIUM ===
    ==============

    ===================================================
    1296) Divide Array in Sets of K Consecutive Numbers
    ===================================================

    ============
    Description:
    ============

    Given an array of integers nums and a positive integer k, check whether it
    is possible to divide this array into sets of k consecutive numbers.

    Return true if it is possible. Otherwise, return false.

    ==========================================================
    FUNCTION: bool isPossibleDivide(vector<int>& nums, int k);
    ==========================================================

    ==========================================================================
    ================================ EXAMPLES ================================
    ==========================================================================

    --- Example 1 ---
    Input: nums = [1,2,3,3,4,4,5,6], k = 4
    Output: true
    Explanation: Array can be divided into [1,2,3,4] and [3,4,5,6].

    --- Example 2 ---
    Input: nums = [3,2,1,2,3,4,3,4,5,9,10,11], k = 3
    Output: true
    Explanation: Array can be divided into [1,2,3] , [2,3,4] , [3,4,5] and
                 [9,10,11].

    --- Example 3 ---
    Input: nums = [1,2,3,4], k = 3
    Output: false
    Explanation: Each array should be divided in subarrays of size 3.


    *** Constraints ***
    1 <= k <= nums.length <= 10^5
    1 <= nums[i] <= 10^9

*/

#include <map>
#include <vector>
using namespace std;

/*
    ------------
    --- IDEA ---
    ------------

    TODO

*/

/* Time  Beats: 43.70% */
/* Space Beats: 21.59% */

/* Time  Complexity: O(N * logN) */
/* Space Complexity: O(N)        */
class Solution {
public:
    bool isPossibleDivide(vector<int>& nums, int k) 
    {
        const int N = nums.size();
        if (N % k != 0)
            return false;

        map<int, int> freq_map; // Sorted by the keys in ASCENDING order
        for (const int& num : nums)
            freq_map[num]++;

        for (auto it = freq_map.begin(); it != freq_map.end(); it++)
        {
            int curr_num  = it->first;
            int curr_freq = it->second;

            // If the curr_freq of smallest integer is non 0, then
            // check if next k numbers exist and have atleast same frequency
            if (curr_freq > 0)
            {
                for (int i = 0; i < k; i++) // Checks for the next k-1 numbers
                {
                    if (freq_map[curr_num + i] < curr_freq)
                        return false;

                    freq_map[curr_num + i] -= curr_freq;
                }
            }
        }

        return true;
    }
};
