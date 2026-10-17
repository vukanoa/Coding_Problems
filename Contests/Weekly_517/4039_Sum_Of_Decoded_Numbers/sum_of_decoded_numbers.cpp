/*
    ==============
    === MEDIUM ===
    ==============

    ============================
    4039) Sum of Decoded Numbers
    ============================

    ============
    Description:
    ============

    You are given an integer array nums.

    Each nums[i] is an encoded integer representing two positive integers xi
    and yi. To decode nums[i], define:

        + widthi = nums[i] % 10.

        + di = floor(nums[i] / 10).

        + xi as the integer formed by the first widthi digits of the decimal
          representation of di.

        + yi as the integer formed by all remaining digits of the decimal
          representation of di.

    It is guaranteed that the decimal representation of di contains more than
    widthi digits. Therefore, both xi and yi contain at least one digit.

    The decoded value of nums[i] is xiyi.

    Return the sum of the decoded values of all elements in nums, modulo 109 + 7.

    The floor() function returns the integer part of the division.

    ==================================================
    FUNCTION: int sumDecoded(vector<long long>& nums);
    ==================================================

    ==========================================================================
    ================================ EXAMPLES ================================
    ==========================================================================

    --- Example 1 ---
    Input: nums = [231]
    Output: 8
    Explanation:
        For 231, we have width = 1, d = 23, x = 2, and y = 3.
        The decoded value of 231 is 23 = 8.
        Since there is only one element in nums, the sum of the decoded values
        is 8.

    --- Example 2 ---
    Input: nums = [2522,2101]
    Output: 1649
    Explanation:
        For 2522, we have width = 2, d = 252, x = 25, and y = 2.
        The decoded value of 2522 is 252 = 625.
        For 2101, we have width = 1, d = 210, x = 2, and y = 10.
        The decoded value of 2101 is 210 = 1024.
        The sum of the decoded values is 625 + 1024 = 1649.

    --- Example 3 ---
    Input: nums = [2301]
    Output: 73741817
    Explanation:
        For 2301, we have width = 1, d = 230, x = 2, and y = 30.
        The decoded value is 230 = 1073741824.
        Therefore, the answer is 1073741824 modulo (109 + 7) = 73741817.


    *** Constraints ***
    1 <= nums.length <= 10^5
    100 < nums[i] < 10^15
    1 <= widthi <= 9
    1 <= xi, yi < 10^9
    The digit sequences used to form xi and yi do not have leading zeros.
    It is guaranteed that every element in nums is a valid encoded integer.

*/

#include <cmath>
#include <vector>
using namespace std;

/*
    ------------
    --- IDEA ---
    ------------

    TODO

*/

/* Time  Beats: 82.96% */
/* Space Beats: 81.23% */

/* Time  Complexity: O(N * logM) */ // M --> max value of y across all nums
/* Space Complexity: O(1)        */
class Solution {
private:
    const int MOD = 1e9 + 7;
    
public:
    int sumDecoded(vector<long long>& nums)
    {
        const int N = nums.size();
        long long result = 0LL;

        for (int i = 0; i < N; i++)
        {
            long long width = nums[i] % 10;
            long long d     = nums[i] / 10;

            long long total_digits = 0;
            long long num = d;
            while (num > 0)
            {
                ++total_digits;
                num /= 10;
            }

            long long power = pow(10, total_digits - width);

            long long x = d / power;
            long long y = d % power;

            long long decoded_val = binary_exponentiation(x, y);

            result = (result + decoded_val) % MOD;
        }

        return static_cast<int>(result);
    }

private:
    long long binary_exponentiation(long long base, long long exp)
    {
        base %= MOD;

        if (exp == 0)
            return 1;

        int result = 1;
        while (exp > 0) // e.g. exp=19 --> 0001 0011 --> (1 + 2 + 16)
        {
            if (exp & 1)
                result = (result * base) % MOD;

            base = (base * base) % MOD;
            exp >>= 1;
        }

        return result;
    }
};
