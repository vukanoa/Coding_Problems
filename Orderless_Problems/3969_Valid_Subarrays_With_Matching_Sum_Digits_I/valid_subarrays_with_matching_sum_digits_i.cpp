/*
    ==============
    === MEDIUM ===
    ==============

    ================================================
    3969) Valid Subarrays With Matching Sum Digits I
    ================================================

    ============
    Description:
    ============

    You are given an integer array nums and an integer digit x.

    A subarray nums[l..r] is considered valid if the sum of its elements
    satisfies both of the following conditions:

        The first digit of the sum is equal to x.
        The last digit of the sum is equal to x.

    Return the number of valid subarrays.

    ============================================================
    FUNCTION: int countValidSubarrays(vector<int>& nums, int x);
    ============================================================

    ==========================================================================
    ================================ EXAMPLES ================================
    ==========================================================================

    --- Example 1 ---
    Input: nums = [1,100,1], x = 1
    Output: 4
    Explanation:
    The valid subarrays are:
        nums[0..0]: sum = 1
        nums[0..1]: sum = 1 + 100 = 101
        nums[1..2]: sum = 100 + 1 = 101
        nums[2..2]: sum = 1
    Thus, the answer is 4.

    --- Example 2 ---
    Input: nums = [1], x = 2
    Output: 0
    Explanation:
    The only subarray is nums[0..0] with a sum of 1, which does not satisfy the
    conditions. Thus, the answer is 0.


    *** Constraints ***
    1 <= nums.length <= 1500
    1 <= nums[i] <= 10^9
    1 <= x <= 9

*/

#include <vector>
using namespace std;

/*
    ------------
    --- IDEA ---
    ------------

    The only "tricky" thing here is to make sure to use "unsinged long long"
    for sum because each of nums[i] can be up to 10^9.

    Other than that it's a basic Brute-Force.

*/

/* Time  Beats: 48.30% */
/* Space Beats: 48.17% */

/* Time  Complexity: O(N^2) */
/* Space Complexity: O(1)   */
class Solution {
public:
    int countValidSubarrays(vector<int>& nums, int x)
    {
        const int N = nums.size();
        int result = 0;

        for (int i = 0; i < N; i++)
        {
            unsigned long long sum = 0ULL;
            for (int j = i; j < N; j++)
            {
                sum += nums[j];
                unsigned long long copy_sum = sum;

                int last_digit  = copy_sum % 10;
                while (copy_sum / 10 > 0)
                    copy_sum /= 10;

                int first_digit = copy_sum;

                if (first_digit == x && last_digit ==  x)
                    result++;
            }

        }

        return result;
    }
};
