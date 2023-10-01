#include <iostream>

/*
    ==============
    === MEDIUM ===
    ==============

    ============================================
    424) Longest Repeating Character Replacement
    ============================================

    ============
    Description:
    ============

    You are given a string s and an integer k. You can choose any character of
    the string and change it to any other uppercase English character. You can
    perform this operation at most k times.

    Return the length of the longest substring containing the same letter you
    can get after performing the above operations.

    ====================================================
    FUNCTION: int characterReplacement(string s, int k);
    ====================================================

    ==========================================================================
    ================================ EXAMPLES ================================
    ==========================================================================

    --- Example 1 ---
    Input: s = "ABAB", k = 2
    Output: 4
    Explanation: Replace the two 'A's with two 'B's or vice versa.


    --- Example 2 ---
    Input: s = "AABABBA", k = 1
    Output: 4
    Explanation: Replace the one 'A' in the middle with 'B' and form "AABBBBA".
    The substring "BBBB" has the longest repeating letters, which is 4.
    There may exists other ways to achive this answer too.


    *** Constraints ***
    1 <= s.length <= 10^5
    s consists of only uppercase English letters.
    0 <= k <= s.length

*/

/*
    ------------
    --- IDEA ---
    ------------

    TODO

*/

/* Time  Beats: 83.15% */
/* Space Beats: 70.87% */

/*
    Time  Complexity: O(n)
    It's O(26 * n) --> O(1 * n) --> O(n)
*/
/*
    Space Complexity: O(1)
*/
class Solution {
public:
    int characterReplacement(std::string s, int k)
    {
        std::vector<int> letters(26, 0);

        int left = 0;
        int right = 0;

        int longest = 0;
        while (right < s.length())
        {
            letters[s[right] - 'A']++;

            // O(26) -> constant -> O(1)
            int max_freq = *std::max_element(letters.begin(), letters.end());

            // current_window_length = right - left + 1
            if ((right - left + 1) - max_freq > k)
            {
                letters[s[left] - 'A']--;
                left++;
            }

            // current_window_length = right - left + 1
            longest = std::max(longest, right - left + 1);

            right++;
        }

        return longest;
    }
};




/*
    ------------
    --- IDEA ---
    ------------

    We can notice that if we don't decrease max_freq, once its reached some
    value, the Solution will still work since we're Overestimating.

    If and only if we find a max_freq that is greater than the previous value,
    only then can we increase the size of the longest substring, thus we don't
    have to keep finding the max_freq for each current window.

    // TODO: Explain this better

*/

/* Time  Beats: 98.55% */
/* Space Beats: 70.87% */

/* Time  Complexity: O(n) */
/* Space Complexity: O(1) */
class Solution_Flat_O_of_n {
public:
    int characterReplacement(std::string s, int k)
    {
        std::vector<int> letters(26, 0);

        int left  = 0;
        int right = 0;
        int max_freq = 0;

        int longest = 0;
        while (right < s.length())
        {
            letters[s[right] - 'A']++;

            // This is the optimization.
            max_freq = std::max(max_freq, letters[s[right] - 'A']);

            // current_window_length = right - left + 1
            if ((right - left + 1) - max_freq > k)
            {
                letters[s[left] - 'A']--;
                left++;
            }

            // current_window_length = right - left + 1
            longest = std::max(longest, right - left + 1);

            right++;
        }

        return longest;
    }
};
