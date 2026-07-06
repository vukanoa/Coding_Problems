/*
    ============
    === EASY ===
    ============

    ==============================================
    3982) Sum of Integers with Maximum Digit Range 
    ==============================================

    ============
    Description:
    ============

    You are given an integer array nums.

    The digit range of an integer is defined as the difference between its
    largest digit and smallest digit.

    For example, the digit range of 5724 is 7 - 2 = 5.

    Return the sum of all integers in nums whose digit range is equal to the
    maximum digit range among all integers in the array.

    ===============================================
    FUNCTION: int maxDigitRange(vector<int>& nums);
    ===============================================

    ==========================================================================
    ================================ EXAMPLES ================================
    ==========================================================================

    --- Example 1 ---
    Input: nums = [5724,111,350]
    Output: 6074

    --- Example 2 ---
    Input: nums = [90,900]
    Output: 990


    *** Constraints ***
    1 <= nums.length <= 100
    10 <= nums[i] <= 10^5

*/

#include <climits>
#include <unordered_map>
#include <vector>
using namespace std;

/*
    ------------
    --- IDEA ---
    ------------

    Simulation problem.

*/

/* Time  Beats: 100.00% */
/* Space Beats:  00.00% */

/* Time  Complexity: O(N * D) */
/* Space Complexity: O(N)     */
class Solution {
public:
    int maxDigitRange(vector<int>& nums)
    {
        const int N = nums.size();
        int max_digit_range = INT_MIN;

        unordered_map<int,int> umap;

        for (int i = 0; i < N; i++)
        {
            int num = nums[i];

            int min_digit = INT_MAX;
            int max_digit = INT_MIN;
            while (num > 0)
            {
                int digit = num % 10;

                min_digit = min(min_digit, digit);
                max_digit = max(max_digit, digit);

                num /= 10;
            }

            max_digit_range = max(max_digit_range, max_digit - min_digit);

            umap[nums[i]] = max_digit - min_digit;
        }

        int result = 0;
        for (int i = 0; i < N; i++)
        {
            if (umap[nums[i]] == max_digit_range)
                result += nums[i];
        }

        return result;
    }
};
