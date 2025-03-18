/*
    ==============
    === MEDIUM ===
    ==============

    ===========================
    2401) Longest Nice Subarray
    ===========================

    ============
    Description:
    ============

    You are given an array nums consisting of positive integers.

    We call a subarray of nums nice if the bitwise AND of every pair of
    elements that are in different positions in the subarray is equal to 0.

    Return the length of the longest nice subarray.

    A subarray is a contiguous part of an array.

    =====
    Note: that subarrays of length 1 are always considered nice.
    =====

    =====================================================
    FUNCTION: int longestNiceSubarray(vector<int>& nums);
    =====================================================

    ==========================================================================
    ================================ EXAMPLES ================================
    ==========================================================================

    --- Example 1 ---
    Input: nums = [1,3,8,48,10]
    Output: 3
    Explanation: The longest nice subarray is [3,8,48]. This subarray satisfies
                 the conditions:
    - 3 AND 8 = 0.
    - 3 AND 48 = 0.
    - 8 AND 48 = 0.
    It can be proven that no longer nice subarray can be obtained, so we return
    3.


    --- Example 2 ---
    Input: nums = [3,1,5,11,13]
    Output: 1
    Explanation: The length of the longest nice subarray is 1. Any subarray of
                 length 1 can be chosen.


    *** Constraints ***
    1 <= nums.length <= 10^5
    1 <= nums[i] <= 10^9

*/

#include <string>
#include <vector>
#include <sstream>
using namespace std;

/*
    ------------
    --- IDEA ---
    ------------

    Classic Sliding-Window + Basic bitwise manipulation.

*/

/* Time  Beats: 5.04% */
/* Space Beats: 5.04% */

/* Time  Complexity: O(N) */
/* Space Complexity: O(N) */
class Solution {
public:
    int longestNiceSubarray(vector<int>& nums)
    {
        const int N = nums.size();
        int result = 1;

        vector<string> string_bin_rep(N);

        for (int i = 0; i < N; i++)
        {
            int x = nums[i];

            ostringstream out;
            for (int i = 31; i >= 0; i--)
            {
                if (x & (1 << i))
                    out << 1;
                else
                    out << 0;
            }

            string_bin_rep[i] = out.str();

            // Reset
            out.str("");
            out.clear();
        }

        vector<bool> window_bin_rep(32, false);

        for (int i = 31; i >= 0; i--)
            window_bin_rep[i] = string_bin_rep[0][i] == '1' ? true : false;

        int L = 0;
        int R = 1;

        /* Sliding Window */
        while (R < N)
        {
            while (L < R && ! equal_zero(window_bin_rep, string_bin_rep[R]))
            {
                take_off_leftmost_num(window_bin_rep, string_bin_rep[L]);
                L++;
            }

            add_num_to_window(window_bin_rep, string_bin_rep[R]);

            result = max(result, R - L + 1);

            // Increment
            R++;
        }

        return result;
    }

private:
    bool equal_zero(vector<bool>& window_bin_rep, string& str_bin)
    {
        for (int i = 31; i >= 0; i--)
        {
            if (window_bin_rep[i] == true && str_bin[i] == '1')
                return false;
        }

        return true;
    }

    void take_off_leftmost_num(vector<bool>& window_bin_rep, string& leftmost_num)
    {
        for (int i = 31; i >= 0; i--)
        {
            if (leftmost_num[i] == '1')
                window_bin_rep[i] = false;
        }
    }

    void add_num_to_window(vector<bool>& window_bin_rep, string& str_bin)
    {
        for (int i = 31; i >= 0; i--)
        {
            if (str_bin[i] == '1')
                window_bin_rep[i] = true;
        }
    }
};
