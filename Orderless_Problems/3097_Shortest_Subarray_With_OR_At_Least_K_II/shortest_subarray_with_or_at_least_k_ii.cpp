/*
    ==============
    === MEDIUM ===
    ==============

    =============================================
    3097) Shortest Subarray With OR at Least K II
    =============================================

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
    1 <= nums.length <= 2 * 10^5
    0 <= nums[i] <= 10^9
    0 <= k <= 10^9

*/

#include <climits>
#include <vector>
using namespace std;

/*
    ------------
    --- IDEA ---
    ------------

    TODO

*/

/* Time  Beats: 51.65% */
/* Space Beats: 97.77% */

/* Time  Complexity: O(n * 32) --> O(n) */
/* Space Complexity: O(32)     --> O(1) */
class Solution {
public:
    int minimumSubarrayLength(vector<int>& nums, int k)
    {
        vector<int> count(32, 0);
        int start = 0;
        int end   = 0;

        int min_length = INT_MAX;

        while (end < nums.size())
        {
            update_bits(count, nums[end], 1);

            while (start <= end && get_val(count) >= k)
            {
                min_length = min(min_length, end - start + 1);
                update_bits(count, nums[start], -1);
                start++;
            }

            end++;
        }

        return min_length == INT_MAX ? -1 : min_length;
    }

private:
    void update_bits(vector<int>& count, int num, int val)
    {
        for (int i = 0; i < 32; i++)
        {
            if ((num >> i) & 1)
                count[i] += val;
        }
    }

    int get_val(const vector<int>& count)
    {
        int result = 0;
        for (int i = 0; i < 32; i++)
        {
            if (count[i] > 0)
                result |= (1 << i);
        }

        return result;
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
class Solution_Sliding_Window {
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
