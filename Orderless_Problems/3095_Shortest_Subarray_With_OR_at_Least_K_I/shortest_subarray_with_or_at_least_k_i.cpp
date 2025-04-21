/*
    ============
    === EASY ===
    ============

    ============================================
    3095) Shortest Subarray With OR at Least K I
    ============================================

    ============
    Description:
    ============

    You are given an array nums of non-negative integers and an integer k.

    An array is called special if the bitwise OR of all of its elements is at
    least k.

    Return the length of the shortest special non-empty subarray of nums, or
    return -1 if no special subarray exists.

    ==============================================================
    FUNCTION: int minimumSubarrayLength(vector<int>& nums, int k);
    ==============================================================

    ==========================================================================
    ================================ EXAMPLES ================================
    ==========================================================================

    --- Example 1 ---
    Input: nums = [1,2,3], k = 2
    Output: 1
    Explanation:
    The subarray [3] has OR value of 3. Hence, we return 1.
    Note that [2] is also a special subarray.

    --- Example 2 ---
    Input: nums = [2,1,8], k = 10
    Output: 3
    Explanation:
    The subarray [2,1,8] has OR value of 11. Hence, we return 3.

    --- Example 3 ---
    Input: nums = [1,2], k = 0
    Output: 1
    Explanation:
    The subarray [1] has OR value of 1. Hence, we return 1.


    *** Constraints ***
    1 <= nums.length <= 50
    0 <= nums[i] <= 50
    0 <= k < 64

*/

#include <climits>
#include <vector>
using namespace std;

/*
    ------------
    --- IDEA ---
    ------------

    Brute-Force.

*/

/* Time  Beats: 100.00% */
/* Space Beats: 80.80% */

/* Time  Complexity: O(N^2) */
/* Space Complexity: O(1)   */
class Solution {
public:
    int minimumSubarrayLength(vector<int>& nums, int k)
    {
        const int N = nums.size();

        int min_len = -1;
        for(const int& num : nums)
        {
            if (num >= k)
                min_len = 1;
        }

        for (int i = 0; i < N; i++)
        {
            int bitwise = nums[i];

            for (int j = i + 1; j < N; j++)
            {
                bitwise |= nums[j];

                if (bitwise >= k)
                {
                    int x = j-i +1;

                    if (min_len == -1)
                        min_len = x;
                    else
                        min_len = min(min_len, x);
                }
            }
        }

        return  min_len;
    }
};




/*
    ------------
    --- IDEA ---
    ------------

    This one uses Sliding-Window technique on vectors of bits of size 64.

    However, LeetCode "rates" this Solution worse because the purpose of this
    one is to be solved using Brute-Force.

    However there's a 2nd version of this exact same problem, the only
    difference is the given Constraints.

    This Solution solves both.

*/

/* Time  Beats: 6.25% */
/* Space Beats: 5.80% */

/* Time  Complexity: O(N * 64) ---> O(N * 1) ---> O(N) */
/* Space Complexity: O(N * 64) ---> O(N * 1) ---> O(N) */
class Solution_Optimized {
public:
    int minimumSubarrayLength(vector<int>& nums, int k)
    {
        const int N = nums.size();
        long long result = LLONG_MAX;

        if (k == 0)
            return 1;

        vector<vector<long long>> bits(N, vector<long long>(64, 0));
        vector<long long> k_bits(64, 0);

        int i = 0;
        while (k > 0)
        {
            k_bits[63 - i] = k & 0x1;

            k >>= 1;
            i++;
        }

        for (i = 0; i < N; i++)
        {
            long long pos = 0;
            while (nums[i] > 0)
            {
                bits[i][63 - pos] = nums[i] & 0x1;

                nums[i] >>= 1;
                pos++;
            }

        }

        long long L = 0;
        long long R = 0;
        vector<long long> tmp(64, 0);
        while (R < N)
        {
            tmp = add(tmp, bits[R]);

            while (GE(tmp, k_bits))
            {
                result = min(result, R - L + 1);
                sub(tmp, bits[L]);
                L++;
            }

            // Increment
            R++;
        }

        return result == LLONG_MAX ? -1 : result;
    }

private:
    bool GE(vector<long long>& bits, vector<long long>& k_bits)
    {
        int left  = 64;
        int right = 64;
        for (long long i = 0; i < 64; i++)
        {
            if (bits[i] >= 1 && k_bits[i] >= 1)
                continue;

            if (bits[i] >= 1 && k_bits[i] == 0)
                return true;

            if (bits[i] == 0 && k_bits[i] >= 1)
                return false;
        }

        return true;
    }

    vector<long long> add(vector<long long>& one, vector<long long>& two)
    {
        vector<long long> tmp(64, 0);

        for (long long i = 0; i < 64; i++)
        {
            tmp[i] = one[i] + two[i];
        }

        return tmp;
    }

    void sub(vector<long long>& one, vector<long long>& two)
    {
        for (long long i = 0; i < 64; i++)
        {
            if (two[i] == 1)
                one[i]--;
        }
    }
};
