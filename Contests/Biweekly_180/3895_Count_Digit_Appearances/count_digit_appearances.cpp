/*
    ==============
    === MEDIUM ===
    ==============

    =============================
    3895) Count Digit Appearances
    =============================

    ============
    Description:
    ============

    You are given an integer array nums and an integer digit.

    Return the total number of times digit appears in the decimal
    representation of all elements in nums.

    ==================================================================
    FUNCTION: int countDigitOccurrences(vector<int>& nums, int digit);
    ==================================================================

    ==========================================================================
    ================================ EXAMPLES ================================
    ==========================================================================

    --- Example 1 ---
    Input: nums = [12,54,32,22], digit = 2
    Output: 4
    Explanation:
    The digit 2 appears once in 12 and 32, and twice in 22. Thus, the total
    number of times digit 2 appears is 4.

    --- Example 2 ---
    Input: nums = [1,34,7], digit = 9
    Output: 0
    Explanation:
    The digit 9 does not appear in the decimal representation of any element in
    nums, so the total number of times digit 9 appears is 0.


    *** Constraints ***
    1 <= nums.length <= 1000
    1 <= nums[i] <= 10^6
    0 <= digit <= 9

*/

#include <vector>
using namespace std;

/*
    ------------
    --- IDEA ---
    ------------

    Pointless problem as well.

*/

/* Time  Beats: 100.00% */
/* Space Beats: 17.94% */

/* Time  Complexity: O(N * log(nums[i])) */
/* Space Complexity: O(1)                */
class Solution {
public:
    int countDigitOccurrences(vector<int>& nums, int digit)
    {
        const int N = nums.size();
        int result = 0;

        for (int i = 0; i < N; i++)
        {
            int num = nums[i];

            while (num > 0)
            {
                int curr_digit = num % 10;

                if (curr_digit == digit)
                    ++result;

                num /= 10;
            }
        }

        return result;
    }
};
