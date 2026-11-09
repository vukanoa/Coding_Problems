/*
    ==============
    === MEDIUM ===
    ==============

    =========================================
    3843) First Element with Unique Frequency
    =========================================

    ============
    Description:
    ============

    You are given an integer array nums.

    Return an integer denoting the first element (scanning from left to right)
    in nums whose frequency is unique. That is, no other integer appears the
    same number of times in nums. If there is no such element, return -1.

    =================================================
    FUNCTION: int firstUniqueFreq(vector<int>& nums);
    =================================================

    ==========================================================================
    ================================ EXAMPLES ================================
    ==========================================================================

    --- Example 1 ---
    Input: nums = [20,10,30,30]
    Output: 30
    Explanation:
        20 appears once.
        10 appears once.
        30 appears twice.
        The frequency of 30 is unique because no other integer appears exactly
        twice.


    --- Example 2 ---
    Input: nums = [20,20,10,30,30,30]
    Output: 20
    Explanation:
        20 appears twice.
        10 appears once.
        30 appears 3 times.
        The frequency of 20, 10, and 30 are unique. The first element that has
        unique frequency is 20.


    --- Example 3 ---
    Input: nums = [10,10,20,20]
    Output: -1
    Explanation:
        10 appears twice.
        20 appears twice.
        No element has a unique frequency.


    *** Constraints ***
    1 <= nums.length <= 10^5
    1 <= nums[i] <= 10^5

*/

#include <unordered_map>
#include <vector>
using namespace std;

/*
    ------------
    --- IDEA ---
    ------------

    TODO

*/

/* Time  Beats: 92.64% */
/* Space Beats: 78.88% */

/* Time  Complexity: O(N) */
/* Space Complexity: O(N) */
class Solution {
public:
    int firstUniqueFreq(vector<int>& nums)
    {
        unordered_map<int,int> freq;
        for (const int& num : nums)
            ++freq[num];

        unordered_map<int,int> freq_count; // Number of elements with that freq
        for (const auto& [num, frequency] : freq)
            ++freq_count[frequency]; 

        for (const int& num : nums)
        {
            if (freq_count[ freq[num] ] == 1)
                return num;
        }

        return -1;
    }
};
