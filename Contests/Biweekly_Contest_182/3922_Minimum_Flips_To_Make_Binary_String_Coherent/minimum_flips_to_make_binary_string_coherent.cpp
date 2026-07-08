/*
    ==============
    === MEDIUM ===
    ==============

    ==================================================
    3922) Minimum Flips to Make Binary String Coherent
    ==================================================

    ============
    Description:
    ============

    You are given a binary string s.

    A string is considered coherent if it does not contain "011" or "110" as .

    In one operation, you can flip any character in s ('0' to '1' or '1' to
    '0').

    Return an integer denoting the minimum number of operations required to
    make s coherent.

    =================================
    FUNCTION: int minFlips(string s);
    =================================

    ==========================================================================
    ================================ EXAMPLES ================================
    ==========================================================================

    --- Example 1 ---
    Input: s = "1010"
    Output: 1
    Explanation:
    Flip s[0] to get "0010", which contains no "011" or "110" subsequences.

    --- Example 2 ---
    Input: s = "0110"
    Output: 1
    Explanation:
    Flip s[1] to get "0010", removing all forbidden subsequences "011" and
    "110".

    --- Example 3 ---
    Input: s = "1000"
    Output: 0
    Explanation:
    The string already has no "011" or "110" subsequences, so no flips are
    needed.


    *** Constraints ***
    1 <= s.length <= 10^5
    s[i] is either '0' or '1'.

*/

#include <string>
using namespace std;


/*
    ------------
    --- IDEA ---
    ------------

    Written during a Virtual-Contest], so it's a bit messier.

*/

/* Time  Beats: 69.79% */
/* Space Beats: 52.30% */

/* Time  Complexity: O(N) */
/* Space Complexity: O(1) */
class Solution_Messy {
public:
    int minFlips(string s)
    {
        const int N = s.size();

        if (N <= 2)
            return 0;

        if (N == 3)
            return (s == "011" || s == "110") ? 1 : 0;


        int ones   = 0;
        int zeroes = 0;

        for (const char& chr : s)
            ones += chr == '1' ? 1 : 0;

        zeroes = N - ones;

        if (zeroes == 0 || ones <= 1)
            return 0;

        int leading_ones  = 0;
        int trailing_ones = 0;
        for (int i = 0; i < N-1; i++)
        {
            leading_ones += s[i]         == '1' ? 1 : 0;
            trailing_ones+= s[(N-1) - i] == '1' ? 1 : 0;
        }

        if (leading_ones < 2 && trailing_ones < 2)
            return 0;

        return max(0, min(max(leading_ones, trailing_ones) - 1, zeroes));
    }
};




class Solution_elegant {
public:
    int minFlips(string s)
    {
        int freq[2] = {0, 0};

        /*
           character '0' is ASCII value of 48
           character '1' is ASCII value of 49 

           doing bitwise AND with 1 gives 1 for ODD number(i.e. for 49), and
           gives 0 for EVEN numbers(i.e. 48 in this case).
        */
        for (const auto &chr : s)
            freq[chr & 1]++;

        if (freq[0] == 0 || freq[1] == 0)
            return 0;

        /*
            We need to remove at least a single '1', however if both first and
            last character of s are '1', then subtract one more.

        */
                         // freq[1] - (either 1 or 2)
        return min(freq[0], freq[1] - 1 - (s.front() & s.back() & 1));
    }
};
