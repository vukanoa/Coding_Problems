#include <iostream>

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

/*
    ------------
    --- IDEA ---
    ------------

    TODO

*/

/* Time  Beats: 98.88% */
/* Space Beats: 35.25% */

/* Time  Complexity: O(n) */
/* Space Complexity: O(n) */
class Solution {
public:
    int minimumDeletions(string s)
    {
        ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0); // Accelerates

        const int N = s.length();
        vector<int> count_a_to_the_right(N, 0);

        for (int i = N-2; i >= 0; i--)
        {
            count_a_to_the_right[i] = count_a_to_the_right[i + 1];

            if (s[i + 1] == 'a')
                count_a_to_the_right[i]++;
        }

        int result = INT_MAX;
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
