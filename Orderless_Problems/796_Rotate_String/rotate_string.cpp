/*
    ============
    === EASY ===
    ============

    ===========================
    796) Rotate String
    ===========================

    ============
    Description:
    ============

    Given two strings s and goal, return true if and only if s can become goal
    after some number of shifts on s.

    A shift on s consists of moving the leftmost character of s to the
    rightmost position.

        For example, if s = "abcde", then it will be "bcdea" after one shift.

    ===================================================
    FUNCTION: bool rotateString(string s, string goal);
    ===================================================

    ==========================================================================
    ================================ EXAMPLES ================================
    ==========================================================================

    --- Example 1 ---
    Input: s = "abcde", goal = "cdeab"
    Output: true

    --- Example 2 ---
    Input: s = "abcde", goal = "abced"
    Output: false


    *** Constraints ***
    1 <= s.length, goal.length <= 100
    s and goal consist of lowercase English letters.

*/

#include <bits/stdc++.h>
using namespace std;

/*
    ------------
    --- IDEA ---
    ------------

    Self-explanatory

*/

/* Time  Beats: 100.00% */
/* Space Beats:  61.66% */

/* Time  Complexity: O(N^2) */
/* Space Complexity: O(N)   */
class Solution_Brute_Force {
public:
    bool rotateString(string s, string goal)
    {
        const int N = s.size();
        const int M = goal.size();

        if (N != M)
            return false;

        s += s; // Append s to itself
        for (int i = 0; i < N; i++)
        {
            bool same = true;
            for (int j = 0; j < N; j++)
            {
                if (s[i + j] != goal[j])
                {
                    same = false;
                    break;
                }
            }

            if (same)
                return true;
        }

        return false;
    }
};




/*
    ------------
    --- IDEA ---
    ------------

    We don't actually have to literally rotate as that would take way too much
    time.

    Instead we can concatenate string s to itself and the simply use the "find"
    function to see if there is a substring goal anywhere in that new string
    composed of two s strings concatenated.

    Example:
        Input: s = "abcde", goal = "cdeab"

        new_str = s + s;
        // new_str = "abcdeabcde" 

        Can you match string goal="cdeab" as a substring in this new_str?
        The answer is---Yes!

        // new_str = "abcdeabcde" 
                        ^^^^^
                        |||||
                        |||||
        //    goal =    cdeab


    function "find" uses a an optimized approach thus it will reduce the
    Time Complexity from:

        O(N * M) down to O(N + M)

    which is huge.

    The "find" function does NOT necessarily use KMP, it uses a mix of:

        + memchr/memcmp optimized scanning
        + Two-Way string matching algorithm
        + Boyer-Moore
        + Boyer-Moore-Horspool
        + SIMD/vectorized byte comparisons
        + Small-string specialized loops

    depending on the Input.

*/

/* Time  Beats: 100.00% */
/* Space Beats:  55.81% */

/* Time  Complexity: O(N + M) */
/* Space Complexity: O(N)     */
class Solution_Elegant {
public:
    bool rotateString(string s, string goal)
    {
        if (s.length() != goal.length())
            return false;

        return (s + s).find(goal) != string::npos;
    }
};




/*
    ------------
    --- IDEA ---
    ------------

    This one uses a KMP algorithm for string matching, thus reducing the
    Time Complexity from O(N * M) down to O(N + M), which is huge.

*/

/* Time  Beats: 100.00% */
/* Space Beats:  24.54% */

/* Time  Complexity: O(N + M) */
/* Space Complexity: O(M)     */
class KMP {
public:
    bool kmp_algo(string s, string pattern)
    {
        const int N = s.size();
        const int M = pattern.size();

        /* Populate LPS */
        vector<int> LPS = calculate_LPS(pattern);

        int i = 0;
        int j = 0;

        while (i < N && j < M)
        {
            if (s[i] == pattern[j])
            {
                i++;
                j++;
            }
            else
            {
                if (j > 0)
                    j = LPS[j - 1];
                else
                    i++;
            }
        }

        return j == M;
    }

private:
    //       a b c d a b c y
    //       0 1 2 3 4 5 6 7
    // LPS = 0 0 0 0 1 2 3 0
    //
    vector<int> calculate_LPS(string& pattern)
    {
        const int M = pattern.size();

        /* Initialize with zeroes */
        vector<int> LPS(M, 0);

        int prefix_len = 0;
        int i          = 1;
        while (i < M)
        {
            if (pattern[prefix_len] != pattern[i])
            {
                if (prefix_len > 0)
                    prefix_len = LPS[prefix_len - 1];
                else
                    i++;
            }
            else
            {
                LPS[i] = prefix_len + 1;
                prefix_len++;

                i++;
            }
        }

        return LPS;
    }
};

class Solution {
public:
    bool rotateString(string s, string goal)
    {
        const int N = s.size();
        const int M = goal.size();

        if (N != M)
            return false;

        s += s; // Append s to itself
        KMP kmp;

        return kmp.kmp_algo(s, goal);
    }
};
