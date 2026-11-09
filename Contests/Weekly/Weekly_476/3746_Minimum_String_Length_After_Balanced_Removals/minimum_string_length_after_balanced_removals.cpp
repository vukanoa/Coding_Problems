/*
    ==============
    === MEDIUM ===
    ==============

    ===================================================
    3746) Minimum String Length After Balanced Removals
    ===================================================

    ============
    Description:
    ============

    You are given a string s consisting only of the characters 'a' and 'b'.

    You are allowed to repeatedly remove any substring where the number of 'a'
    characters is equal to the number of 'b' characters. After each removal,
    the remaining parts of the string are concatenated together without gaps.

    Return an integer denoting the minimum possible length of the string after
    performing any number of such operations.

    ===============================================
    FUNCTION: int minLengthAfterRemovals(string s);
    ===============================================

    ==========================================================================
    ================================ EXAMPLES ================================
    ==========================================================================

    --- Example 1 ---
    Input: s = "aabbab"
    Output: 0
    Explanation:
    The substring "aabbab" has three 'a' and three 'b'. Since their counts are
                  equal, we can remove the entire string directly. The minimum
                  length is 0.

    --- Example 2 ---
    Input: s = "aaaa"
    Output: 4
    Explanation: Every substring of "aaaa" contains only 'a' characters. No
                 substring can be emoved as a result, so the minimum length
                 remains 4.

    --- Example 3 ---
    Input: s = "aaabb"
    Output: 1
    Explanation: First, remove the substring "ab", leaving "aab". Next, remove
                 the new substring "ab", leaving "a". No further removals are
                 possible, so the minimum length is 1.


    *** Constraints ***
    1 <= s.length <= 10^5
    s[i] is either 'a' or 'b'.

*/

#include <algorithm>
#include <string>
using namespace std;

/*
    ------------
    --- IDEA ---
    ------------

    Self-explanatory.

*/

/* Time  Beats: 61.12% */
/* Space Beats: 88.86% */

/* Time  Complexity: O(N) */
/* Space Complexity: O(1) */
class Solution_Simply_Count_1 {
public:
    int minLengthAfterRemovals(string s)
    {
        const int N = s.length();

        int count_a = 0;
        int count_b = 0;
        for (const char& chr : s)
        {
            if (chr == 'a')
                ++count_a;
            else
                ++count_b;
        }

        return N - 2 * min(count_a, count_b);
    }
};




/*
    ------------
    --- IDEA ---
    ------------

    Another way.

*/

/* Time  Complexity: O(N) */
/* Space Complexity: O(1) */
class Solution_Simply_Count_2 {
public:
    int minLengthAfterRemovals(string s)
    {
        const int N = s.length();

        int count_a = 0;
        int count_b = 0;
        for (const char& chr : s)
        {
            if (chr == 'a')
                ++count_a;
            else
                ++count_b;
        }

        if (count_a < count_b)
            swap(count_a, count_b);

        return count_a - count_b;
    }
};




/*
    ------------
    --- IDEA ---
    ------------

    Another way.

*/

/* Time  Beats: 38.42% */
/* Space Beats: 88.32% */

/* Time  Complexity: O(N) */
/* Space Complexity: O(1) */
class Solution_Simply_Count_3 {
public:
    int minLengthAfterRemovals(string s)
    {
        int count_a = count(s.begin(), s.end(), 'a');
        int count_b = count(s.begin(), s.end(), 'b');

        if (count_a < count_b)
            swap(count_a, count_b);

        return count_a - count_b;
    }
};




/*
    ------------
    --- IDEA ---
    ------------

    We have 4 combinations for two adjacent characters:

        "aa" --> Count left 'a' as -1
        "bb" --> Count left 'b' as +1
        "ba" --> REMOVE BOTH
        "ab" --> REMOVE BOTH

    Anytime we have "ab" or "ba" we move by TWO to the right since we're going
    to remove both of them.

    If it's "aa", then the LEFT 'a' can be counted as -1.
    If it's "bb", then the LEFT 'b' can be counted as +1.

*/

/* Time  Beats: 53.27% */
/* Space Beats: 69.11% */

/* Time  Complexity: O(N) */
/* Space Complexity: O(1) */
class Solution_Another_way {
public:
    int minLengthAfterRemovals(string s)
    {
        const int N = s.size();
        int result = 0;
        
        int i = 0;
        while (i < N-1)
        {
            if (s[i] == 'a')
            {
                if (s[i+1] == 'a')
                    --result; // -1
                else
                    ++i;
            }
            else // s[i] == 'b'
            {
                if (s[i+1] == 'b')
                    ++result; // +1
                else
                    ++i;
            }

            // Increment
            ++i;
        }

        if (i == N-1)
            result += (s[N-1] == 'a') ? -1 : 1;

        return abs(result);
    }
};
