/*
    ==============
    === MEDIUM ===
    ==============

    ===============================================
    1653) Minimum Deletions To Make String Balanced
    ===============================================

    ============
    Description:
    ============

    You are given a string s consisting only of characters 'a' and 'b'.

    You can delete any number of characters in s to make s balanced. s is
    balanced if there is no pair of indices (i,j) such that i < j and s[i] =
    'b' and s[j]= 'a'.

    Return the minimum number of deletions needed to make s balanced.

    =========================================
    FUNCTION: int minimumDeletions(string s);
    =========================================

    ==========================================================================
    ================================ EXAMPLES ================================
    ==========================================================================

    --- Example 1 ---
    Input: s = "aababbab"
    Output: 2
    Explanation: You can either:
    Delete the characters at 0-indexed positions 2 and 6 ("aababbab" -> "aaabbb"), or
    Delete the characters at 0-indexed positions 3 and 6 ("aababbab" -> "aabbbb").


    --- Example 2 ---
    Input: s = "bbaaaaabb"
    Output: 2
    Explanation: The only solution is to delete the first two characters.


    *** Constraints ***
    1 <= s.length <= 10^5
    s[i] is 'a' or 'b'

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

/* Time  Beats: 98.88% */
/* Space Beats: 35.25% */

/* Time  Complexity: O(N) */
/* Space Complexity: O(N) */
class Solution {
public:
    int minimumDeletions(string s)
    {
        const int N = s.length();
        int result = N;

        vector<int> count_a_to_the_right(N, 0);

        for (int i = N-2; i >= 0; i--)
        {
            count_a_to_the_right[i] = count_a_to_the_right[i + 1];

            if (s[i + 1] == 'a')
                count_a_to_the_right[i]++;
        }

        int count_b_to_the_left = 0;
        for (int i = 0; i < N; i++)
        {
            int deletions = count_b_to_the_left + count_a_to_the_right[i];
            result = min(result, deletions);

            if (s[i] == 'b')
                count_b_to_the_left++;
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

/* Time  Beats: 99.04% */
/* Space Beats: 66.99% */

/* Time  Complexity: O(N) */
/* Space Complexity: O(1) */
class Solution_Space_Efficient {
public:
    int minimumDeletions(string s)
    {
        const int N = s.size();
        int result = N;

        int a_count_right = 0;
        for (int i = 0; i < N; i++)
        {
            if (s[i] == 'a')
                a_count_right++;
        }

        int b_count_left = 0;
        for (int i = 0; i < N; i++)
        {
            if (s[i] == 'a')
                a_count_right--;

            result = min(result, b_count_left + a_count_right);

            if (s[i] == 'b')
                b_count_left++;
        }

        return result;
    }
};
