/*
    ==============
    === MEDIUM ===
    ==============

    ===================================================
    3800) Minimum Cost to Make Two Binary Strings Equal
    ===================================================

    ============
    Description:
    ============

    You are given two binary strings s and t, both of length n, and three
    positive integers flipCost, swapCost, and crossCost.

    You are allowed to apply the following operations any number of times (in
    any order) to the strings s and t:

        + Choose any index i and flip s[i] or t[i] (change '0' to '1' or '1' to
          '0'). The cost of this operation is flipCost.

        + Choose two distinct indices i and j, and swap either s[i] and s[j] or
          t[i] and t[j]. The cost of this operation is swapCost.

        + Choose an index i and swap s[i] with t[i]. The cost of this operation
          is crossCost.

    Return an integer denoting the minimum total cost needed to make the
    strings s and t equal.

    ===============================================================================================
    FUNCTION: long long minimumCost(string s, string t, int flipCost, int swapCost, int crossCost);
    ===============================================================================================

    ==========================================================================
    ================================ EXAMPLES ================================
    ==========================================================================

    --- Example 1 ---
    Input: s = "01000", t = "10111", flipCost = 10, swapCost = 2, crossCost = 2
    Output: 16
    Explanation:
    We can perform the following operations:
        Swap s[0] and s[1] (swapCost = 2). After this operation, s = "10000" and t = "10111".
        Cross swap s[2] and t[2] (crossCost = 2). After this operation, s = "10100" and t = "10011".
        Swap s[2] and s[3] (swapCost = 2). After this operation, s = "10010" and t = "10011".
        Flip s[4] (flipCost = 10). After this operation, s = t = "10011".
    The total cost is 2 + 2 + 2 + 10 = 16.

    --- Example 2 ---
    Input: s = "001", t = "110", flipCost = 2, swapCost = 100, crossCost = 100
    Output: 6
    Explanation:
    Flipping all the bits of s makes the strings equal, and the total cost is 3 * flipCost = 3 * 2 = 6

    --- Example 3 ---
    Input: s = "1010", t = "1010", flipCost = 5, swapCost = 5, crossCost = 5
    Output: 0
    Explanation:
    The strings are already equal, so no operations are required.


    *** Constraints ***
    n == s.length == t.length
    1 <= n <= 10^5
    1 <= flipCost, swapCost, crossCost <= 10^9
    s and t consist only of the characters '0' and '1'.

*/

#include <string>
#include <vector>
using namespace std;

class Solution2{
public:
    long long minimumCost(string s, string t, int flipCost, int swapCost, int crossCost)
    {
        const int N = s.size();
        long long result = 1LL * N * flipCost;


        vector<int> a(2, 0);
        vector<int> b(2, 0);

        int required_flips = 0;
        for (int i = 0; i < N; i++)
        {
            a[0] += s[i] == '0';
            a[1] += s[i] == '1';

            b[0] += t[i] == '0';
            b[1] += t[i] == '1';
            
            if (s[i] != t[i])
                ++required_flips;
        }

        result = min(result, 1LL * required_flips * flipCost);

        if (a[0] == b[0])
        {
            int required_swaps = 0;
            for (int i = 0; i < N; i++)
            {
                if (s[i] != t[i])
                    ++required_swaps;
            }

            return min(result, 1LL * required_swaps * swapCost);
        }


        return result;
    }
};


/*
    ------------
    --- IDEA ---
    ------------

    TODO

*/

/* Time  Beats: 31.03% */
/* Space Beats: 17.24% */

/* Time  Complexity: O(N) */
/* Space Complexity: O(1) */
class Solution {
public:
    long long minimumCost(string s, string t, int flipCost, int swapCost, int crossCost)
    {
        const int N = s.size();
        long long diff[2] = {0, 0};

        for (int i = 0; i < N; i++)
        {
            if (s[i] != t[i])
                ++diff[s[i] - '0'];
        }

        long long result = (diff[0] + diff[1]) * flipCost;

        long long max_mismatch = max(diff[0], diff[1]);
        long long min_mismatch = min(diff[0], diff[1]);

        result = min(result, min_mismatch * swapCost +
                             (max_mismatch - min_mismatch) * flipCost);


        long long avg = (max_mismatch + min_mismatch) / 2;

        result = min(result, (avg - min_mismatch) * crossCost +
                             avg * swapCost +
                             (max_mismatch + min_mismatch - 2 * avg) * flipCost);

        return result;
    }
};
