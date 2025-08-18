/*
    ==============
    === MEDIUM ===
    ==============

    ========================================================
    2767) Partition String Into Minimum Beautiful Substrings
    ========================================================

    ============
    Description:
    ============

    Given a binary string s, partition the string into one or more substrings
    such that each substring is beautiful.

    A string is beautiful if:

        + It doesn't contain leading zeros.
        + It's the binary representation of a number that is a power of 5.

    Return the minimum number of substrings in such partition. If it is
    impossible to partition the string s into beautiful substrings, return -1.

    A substring is a contiguous sequence of characters in a string.

    ===================================================
    FUNCTION: int minimumBeautifulSubstrings(string s);
    ===================================================

    ==========================================================================
    ================================ EXAMPLES ================================
    ==========================================================================

    --- Example 1 ---
    Input: s = "1011"
    Output: 2
    Explanation: We can paritition the given string into ["101", "1"].
    - The string "101" does not contain leading zeros and is the binary representation of integer 51 = 5.
    - The string "1" does not contain leading zeros and is the binary representation of integer 50 = 1.
    It can be shown that 2 is the minimum number of beautiful substrings that s can be partitioned into.

    --- Example 2 ---
    Input: s = "111"
    Output: 3
    Explanation: We can paritition the given string into ["1", "1", "1"].
    - The string "1" does not contain leading zeros and is the binary representation of integer 50 = 1.
    It can be shown that 3 is the minimum number of beautiful substrings that s can be partitioned into.

    --- Example 3 ---
    Input: s = "0"
    Output: -1
    Explanation: We can not partition the given string into beautiful substrings.


    *** Constraints ***
    1 <= s.length <= 15
    s[i] is either '0' or '1'.

*/

#include <cstring>
#include <string>
#include <unordered_set>
using namespace std;

/*
    ------------
    --- IDEA ---
    ------------

    Classic Memoization Problem.
    TODO

*/

/* Time  Beats: 5.28% */
/* Space Beats: 5.86% */

/* Time  Complexity: O(N * 2^N) */
/* Space Complexity: O(N * 2^N) */
class Solution {
private:
    int memo[16][32768];
public:
    int minimumBeautifulSubstrings(string s)
    {
        if (s[0] == '0')
            return -1;

        const int LENGTH = s.length();

        memset(memo, -1, sizeof(memo));
        unordered_set<int> uset_power_of_five = {1, 5, 25, 125, 625, 3125, 15625};

        int result = solve(0, "", uset_power_of_five, s);
        
        return result >= 16 ? -1 : result;
    }

private:
    int solve(int idx, string str, unordered_set<int> uset_power_of_five, string& s)
    {
        const int LENGTH = s.length();

        if (idx >= LENGTH)
            return 0;

        str += s[idx];
        int curr_num = stoi(str, nullptr, 2);

        if (memo[idx][curr_num] != -1)
            return memo[idx][curr_num];

        int stopped_here = 16; // 16 <==> DUMMY_MAX_VALUE

        /*
          If  (it's the last index OR it's not last_idx and next digit is '1')
              AND
              (it's a power_of_five
        */
        if ((idx == LENGTH-1 || (idx < LENGTH-1 && s[idx + 1] == '1')) &&
            uset_power_of_five.count(curr_num))
        {
            stopped_here = 1 + solve(idx + 1, "", uset_power_of_five, s);
        }

        int did_not_stop = solve(idx + 1, str, uset_power_of_five, s);

        return memo[idx][curr_num] = min(stopped_here, did_not_stop == 0 ? 16 : did_not_stop);
    }
};
