/*
    ============
    === EASY ===
    ============

    ================================
    2404) Most Frequent Even Element
    ================================

    ============
    Description:
    ============

    Given an integer array nums, return the most frequent even element.

    If there is a tie, return the smallest one. If there is no such element,
    return -1.

    ==================================================
    FUNCTION: int mostFrequentEven(vector<int>& nums);
    ==================================================

    ==========================================================================
    ================================ EXAMPLES ================================
    ==========================================================================

    --- Example 1 ---
    Input: nums = [0,1,2,2,4,4,1]
    Output: 2
    Explanation:
    The even elements are 0, 2, and 4. Of these, 2 and 4 appear the most.
    We return the smallest one, which is 2.

    --- Example 2 ---
    Input: nums = [4,4,4,9,2,4]
    Output: 4
    Explanation: 4 is the even element appears the most.

    --- Example 3 ---
    Input: nums = [29,47,21,41,13,37,25,7]
    Output: -1
    Explanation: There is no even element.



    *** Constraints ***
    1 <= nums.length <= 2000
    0 <= nums[i] <= 10^5

*/

#include <climits>
#include <unordered_map>
#include <vector>
using namespace std;

/*
    ------------
    --- IDEA ---
    ------------

    Self-explanatory.

*/

/* Time  Beats: 94.37% */
/* Space Beats: 43.95% */

/* Time  Complexity: O(N) */
/* Space Complexity: O(N) */
class Solution {
public:
    int mostFrequentEven(vector<int>& nums)
    {
        const int N = nums.size();
        unordered_map<int,int> freq;

        for (int i = 0; i < N; i++)
        {
            if (nums[i] & 1) // If it's odd
                continue;

            freq[nums[i]]++;
        }

        int result = INT_MAX;
        int count  = 0;
        for (const auto& entry : freq)
        {
            if (entry.second > count)
            {
                count  = entry.second;
                result = entry.first;
            }
            else if (entry.second == count && entry.first < result)
            {
                result = entry.first;
            }
        }

        return result == INT_MAX ? -1 : result;
    }
};
