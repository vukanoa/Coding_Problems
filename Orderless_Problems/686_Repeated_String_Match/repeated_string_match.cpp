/*
    ==============
    === MEDIUM ===
    ==============

    ===========================
    686) Repeated String Match
    ===========================

    ============
    Description:
    ============

    Given two strings a and b, return the minimum number of times you should
    repeat string a so that string b is a substring of it. If it is impossible
    for b to be a substring of a after repeating it, return -1.

    =====
    Note: string "abc" repeated 0 times is "", repeated 1 time is "abc" and
          repeated 2 times is "abcabc". 
    =====

    ======================================================
    FUNCTION: int repeatedStringMatch(string a, string b);
    ======================================================

    ==========================================================================
    ================================ EXAMPLES ================================
    ==========================================================================

    --- Example 1 ---
    Input: a = "abcd", b = "cdabcdab"
    Output: 3
    Explanation: We return 3 because by repeating a three times "abcdabcdabcd",
                 b is a substring of it.

    --- Example 2 ---
    Input: a = "a", b = "aa"
    Output: 2


    *** Constraints ***
    1 <= a.length, b.length <= 10^4
    a and b consist of lowercase English letters.

*/

#include <string>
#include <vector>
using namespace std;

/*
    ------------
    --- IDEA ---
    ------------

    TODO

*/

/* Time  Beats: 24.86% */
/* Space Beats: 84.20% */

/* Time  Complexity: O(N + M) */
/* Space Complexity: O(1)     */
class Solution {
public:
    int repeatedStringMatch(string a, string b)
    {
        int repetitions = 1;

        string repeated_a = a;
        while (repeated_a.size() < b.size())
        {
            repeated_a += a;
            repetitions++;
        }

        if (repeated_a.find(b) != string::npos)
            return repetitions;

        repeated_a += a;

        if (repeated_a.find(b) != string::npos)
            return repetitions + 1;

        return -1;
    }
};




/*
    ------------
    --- IDEA ---
    ------------

    Same as above, however instead brute-forcely trying to match, we can simply
    use a KMP for that part and thus have an optimized Solution.

    However, this is not actually an optimization in practice because std::find
    is optimized, however it's always good to practice writing your own
    functions instead.

*/

/* Time  Complexity: O(N + M) */
/* Space Complexity: O(M)     */
class Solution_General_KMP {
public:
    bool kmp_algorithm(string s, string pattern)
    {
        const int N = s.length();
        const int M = pattern.length();

        vector<int> LPS = compute_LPS(pattern);

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
                {
                    j = LPS[j - 1];
                }
                else
                {
                    i++;
                }
            }
        }

        return j == M;
    }

private:
    vector<int> compute_LPS(string pattern)
    {
        const int M = pattern.length();
        vector<int> LPS(M);

        int prefix_len = 0;
        int i = 1;
        while (i < M)
        {
            if (pattern[prefix_len] == pattern[i])
            {
                LPS[i] = prefix_len + 1;
                prefix_len++;
                i++;
            }
            else
            {
                if (prefix_len > 0)
                {
                    prefix_len = LPS[prefix_len - 1];
                }
                else
                {
                    LPS[i] = 0;
                    i++;
                }
            }
        }

        return LPS;
    }
};


/* Time  Beats: 100.00% */
/* Space Beats:  21.14% */

/* Time  Complexity: O(N + M) */
/* Space Complexity: O(M)     */
/* Repeated String Match using the above KMP class */
class Solution_KMP {
public:
    int repeatedStringMatch(string A, string B)
    {
        Solution_General_KMP kmp;

        string builder;
        int repetitions = 0;

        while (builder.length() < B.length())
        {
            builder += A;
            repetitions++;
        }

        if (kmp.kmp_algorithm(builder, B))
            return repetitions;

        builder += A;

        if (kmp.kmp_algorithm(builder, B))
        {
            return repetitions + 1;
        }

        return -1;
    }
};
