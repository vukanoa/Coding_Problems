/*
    ==============
    === MEDIUM ===
    ==============

    ================================
    1641) Count Sorted Vowel Strings
    ================================

    ============
    Description:
    ============

    Given an integer n, return the number of strings of length n that consist
    only of vowels (a, e, i, o, u) and are lexicographically sorted.

    A string s is lexicographically sorted if for all valid i, s[i] is the same
    as or comes before s[i+1] in the alphabet.

    =======================================
    FUNCTION: int countVowelStrings(int n);
    =======================================

    ==========================================================================
    ================================ EXAMPLES ================================
    ==========================================================================

    --- Example 1 ---
    Input: n = 1
    Output: 5
    Explanation: The 5 sorted strings that consist of vowels only are
    ["a","e","i","o","u"].

    --- Example 2 ---
    Input: n = 2
    Output: 15
    Explanation: The 15 sorted strings that consist of vowels only are
    ["aa","ae","ai","ao","au","ee","ei","eo","eu","ii","io","iu","oo","ou","uu"].
    Note that "ea" is not a valid string since 'e' comes after 'a' in the alphabet.

    --- Example 3 ---
    Input: n = 33
    Output: 66045


    *** Constraints ***
    1 <= n <= 50

*/

#include <vector>
using namespace std;

/*
    ------------
    --- IDEA ---
    ------------

    TODO

*/

/* Time  Beats: 100.00% */
/* Space Beats:  12.16% */

/* Time  Complexity: O(N * K) */
/* Space Complexity: O(N      */
class Solution_2D__DP {
public:
    int countVowelStrings(int n)
    {
        vector<vector<int>>dp (n + 1, vector<int>(6));
        for (int i = 1; i <= n; i++)
        {
            for (int k = 1; k <= 5; ++k)
                dp[i][k] = dp[i][k - 1] + (i > 1 ? dp[i - 1][k] : 1);
        }

        return dp[n][5];
    }
};




/*
    ------------
    --- IDEA ---
    ------------

    TODO

*/

/* Time  Beats: 100.00% */
/* Space Beats:  62.24% */

/* Time  Complexity: O(N * K) */
/* Space Complexity: O(N      */
class Solution_1D__DP {
public:
    int countVowelStrings(int n)
    {
        vector<int> dp = {0,1,1,1,1,1};

        for (int i = 1; i <= n; ++i)
        {
            for (int k = 1; k <= 5; ++k)
                dp[k] += dp[k - 1];
        }

        return dp[5];
    }
};

/*
    ------------
    --- IDEA ---
    ------------

    This article:
    https://math.libretexts.org/Courses/Monroe_Community_College/MTH_220_Discrete_Math/7%3A_Combinatorics/7.5%3A_Combinations_WITH_Repetitions

    explains the concept of combinations with repetitions, and it
    helps tremendously.

    Following the lead from the article mentioned above, the problem asks us to
    pick n letters with repetition from "a, e, i, o, u" without permutation
    (without permutation is because the pick must be in order). Let's say n = 3
    it can be:

        a | e | i | o | u
        1 | 1 | 1 |   |

    or

        a | e | i | o | u
          | 2 |   | 1 |

    Notice the use of | as separators between letters. If we use a generic "x"
    to indicate the position a letter is picked, and also give all the |
    separators positions as well, the two options shown above can be written
    as:

        x | x | x | |
        _ _ _ _ _ _ _


    and

        | x x | | x |
        _ _ _ _ _ _ _

    Essentially, we have transformed the problem into finding how many ways we
    can put three "x" in seven positions. Extending this idea further, the
    original question is equivalent to asking how many ways we can put n "x" in
    n + 5 - 1 positions (think of 5 - 1 as the number of positions for
    separators and n is the number of positions for "x"). The solution is
    simple: (n + 4) choose 4.

*/

/* Time  Beats: 100.00% */
/* Space Beats:  83.89% */

/* Time  Complexity: O(1) */
/* Space Complexity: O(1) */
class Solution_Combinatorics {
public:
    int countVowelStrings(int n)
    {
        return (n + 1) * (n + 2) * (n + 3) * (n + 4) / 24;
    }
};
