/*
    ==============
    === MEDIUM ===
    ==============

    ===========================================
    3153) Sum of Digit Differences of All Pairs
    ===========================================

    ============
    Description:
    ============

    You are given an array nums consisting of positive integers where all
    integers have the same number of digits.

    The digit difference between two integers is the count of different digits
    that are in the same position in the two integers.

    Return the sum of the digit differences between all pairs of integers in
    nums.

    ===========================================================
    FUNCTION: long long sumDigitDifferences(vector<int>& nums);
    ===========================================================

    ==========================================================================
    ================================ EXAMPLES ================================
    ==========================================================================

    --- Example 1 ---
    Input: nums = [13,23,12]
    Output: 4
    Explanation:
    We have the following:
    - The digit difference between 13 and 23 is 1.
    - The digit difference between 13 and 12 is 1.
    - The digit difference between 23 and 12 is 2.
    So the total sum of digit differences between all pairs of integers is
    1 + 1 + 2 = 4.


    --- Example 2 ---
    Input: nums = [10,10,10,10]
    Output: 0
    Explanation: All the integers in the array are the same. So the total sum
                 of digit differences between all pairs of integers will be 0.


    *** Constraints ***
    2 <= nums.length <= 10^5
    1 <= nums[i] < 10^9
    All integers in nums have the same number of digits.

*/

#include <algorithm>
#include <iostream>
#include <vector>
using namespace std;

/*
    ------------
    --- IDEA ---
    ------------

    TODO

*/

/* Time  Beats: 15.03% */
/* Space Beats:  5.56% */

/* Time  Complexity: O(N * logN) */
/* Space Complexity: O(N)        */
class Solution {
public:
    long long sumDigitDifferences(vector<int>& nums)
    {
        ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0); // Accelerates

        const int N = nums.size();
        long long result = 0;

        while (nums[0] > 0) // O(10)
        {
            vector<int> digits;
            for (int i = 0; i < N; i++)
            {
                digits.push_back(nums[i] % 10);
                nums[i] /= 10;
            }

            /* Sort */
            sort(digits.begin(), digits.end());

            int L = 0;
            int R = 1;
            while (R < digits.size())
            {
                if (digits[L] != digits[R])
                {
                    result += ((R - L) * 1LL * (N - R));
                    L = R;
                }

                // Increment
                R++;
            }
        }


        return result;
    }
};
