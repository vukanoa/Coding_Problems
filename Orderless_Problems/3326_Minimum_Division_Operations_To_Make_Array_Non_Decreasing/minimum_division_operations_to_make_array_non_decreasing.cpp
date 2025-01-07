/*
    ==============
    === MEDIUM ===
    ==============

    ==============================================================
    3326) Minimum Division Operations to Make Array Non Decreasing
    ==============================================================

    ============
    Description:
    ============

    You are given an integer array nums.

    Any positive divisor of a natural number x that is strictly less than x is
    called a proper divisor of x. For example, 2 is a proper divisor of 4,
    while 6 is not a proper divisor of 6.

    You are allowed to perform an operation any number of times on nums, where
    in each operation you select any one element from nums and divide it by its
    greatest proper divisor.

    Return the minimum number of operations required to make the array
    non-decreasing.

    If it is not possible to make the array non-decreasing using any number of
    operations, return -1.

    ===============================================
    FUNCTION: int minOperations(vector<int>& nums);
    ===============================================

    ==========================================================================
    ================================ EXAMPLES ================================
    ==========================================================================

    --- Example 1 ---
    Input: nums = [25,7]
    Output: 1
    Explanation:
    Using a single operation, 25 gets divided by 5 and nums becomes [5, 7].

    --- Example 2 ---
    Input: nums = [7,7,6]
    Output: -1

    --- Example 3 ---
    Input: nums = [1,1,1,1]
    Output: 0


    *** Constraints ***
    1 <= nums.length <= 10^5
    1 <= nums[i] <= 10^6

*/

#include <vector>
using namespace std;




/*
    ------------
    --- IDEA ---
    ------------

    TODO

*/

/* Time  Beats: 88.96% */
/* Space Beats: 19.32% */

/* Time  Complexity: O(n) */
/* Space Complexity: O(1) */
class Solution {
private:

const int primes[168] = {
    2, 3, 5, 7, 11, 13, 17, 19, 23, 29, 31, 37, 41, 43, 47, 53, 59, 61, 67, 71,
    73, 79, 83, 89, 97, 101, 103, 107, 109, 113, 127, 131, 137, 139, 149, 151,
    157, 163, 167, 173, 179, 181, 191, 193, 197, 199, 211, 223, 227, 229, 233,
    239, 241, 251, 257, 263, 269, 271, 277, 281, 283, 293, 307, 311, 313, 317,
    331, 337, 347, 349, 353, 359, 367, 373, 379, 383, 389, 397, 401, 409, 419,
    421, 431, 433, 439, 443, 449, 457, 461, 463, 467, 479, 487, 491, 499, 503,
    509, 521, 523, 541, 547, 557, 563, 569, 571, 577, 587, 593, 599, 601, 607,
    613, 617, 619, 631, 641, 643, 647, 653, 659, 661, 673, 677, 683, 691, 701,
    709, 719, 727, 733, 739, 743, 751, 757, 761, 769, 773, 787, 797, 809, 811,
    821, 823, 827, 829, 839, 853, 857, 859, 863, 877, 881, 883, 887, 907, 911,
    919, 929, 937, 941, 947, 953, 967, 971, 977, 983, 991, 997
};

int dp[1000001] = {};

public:
    int minOperations(vector<int>& nums)
    {
        const int N = nums.size();
        int result = 0;

        for (int i = N-2; i >= 0; --i)
        {
            if (nums[i] > nums[i + 1])
            {
                if (dp[nums[i]] == 0)
                {
                    dp[nums[i]] = nums[i];

                    for (int p = 0; primes[p] * primes[p] <= nums[i]; p++)
                    {
                        if (nums[i] % primes[p] == 0)
                        {
                            dp[nums[i]] = primes[p];
                            break;
                        }
                    }
                }
                nums[i] = dp[nums[i]];

                if (nums[i] > nums[i + 1])
                    return -1;

                result++;
            }

        }

        return result;
    }
};
