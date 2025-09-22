/*
    ============
    === EASY ===
    ============

    ===========================================
    3005) Count Elements with Maximum Frequency
    ===========================================

    ============
    Description:
    ============

    You are given an array nums consisting of positive integers.

    Return the total frequencies of elements in nums such that those elements
    all have the maximum frequency.

    The frequency of an element is the number of occurrences of that element in
    the array.

    ======================================================
    FUNCTION: int maxFrequencyElements(vector<int>& nums);
    ======================================================

    ==========================================================================
    ================================ EXAMPLES ================================
    ==========================================================================

    --- Example 1 ---
    Input: nums = [1,2,2,3,1,4]
    Output: 4
    Explanation: The elements 1 and 2 have a frequency of 2 which is the
                 maximum frequency in the array. So the number of elements in
                 the array with maximum frequency is 4.

    --- Example 2 ---
    Input: nums = [1,2,3,4,5]
    Output: 5
    Explanation: All elements of the array have a frequency of 1 which is the
                 maximum. So the number of elements in the array with maximum
                 frequency is 5.


    *** Constraints ***
    1 <= nums.length <= 100
    1 <= nums[i] <= 100

*/

#include <unordered_map>
#include <vector>
using namespace std;

/*
    ------------
    --- IDEA ---
    ------------

    Self-explanatory.

*/

/* Time  Beats: 100.00% */
/* Space Beats:  36.33% */

/* Time  Complexity: O(N) */
/* Space Complexity: O(N) */
class Solution {
public:
    int maxFrequencyElements(vector<int>& nums)
    {
        const int N = nums.size();
        int result = 0;
        int max_freq = 0;

        unordered_map<int, int> freq;
        for (const int& num : nums)
        {
            freq[num]++;

            if (freq[num] > max_freq)
                max_freq = freq[num];
        }

        for (const auto& entry : freq)
        {
            if (entry.second == max_freq)
                result += max_freq;

        }

        return result;
    }
};




/*
    ------------
    --- IDEA ---
    ------------

    Instead of having to pass once through "nums" and once through "freq"
    HashMap, we can just pass once through "nums" and each time we stumble upon
    a new maximum frequency, we update both result and max_freq.

    However, if some further element is NOT a max, but has a currently max_freq
    then we count those numbers in "result".

    That's a nice litle optimization we can do here.

*/

/* Time  Beats: 100.00% */
/* Space Beats:  89.81% */

/* Time  Complexity: O(N) */
/* Space Complexity: O(N) */
class Solution_Single_Pass {
public:
    int maxFrequencyElements(vector<int>& nums)
    {
        int result = 0;

        unordered_map<int, int> freq;
        int max_freq = 0;

        for (const int& num : nums)
        {
            freq[num]++;

            if (freq[num] > max_freq)
            {
                max_freq = freq[num];
                result   = freq[num];
            }
            else if (freq[num] == max_freq)
            {
                result += freq[num];
            }
        }

        return result;
    }
};
