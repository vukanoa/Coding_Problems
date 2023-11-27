#include <iostream>
#include <vector>

/*
    ==============
    === MEDIUM ===
    ==============

    ===========================================
    1525) Number of Good Ways to Split a String
    ===========================================

    ============
    Description:
    ============

    You are given a string s.

    A split is called good if you can split s into two non-empty strings sleft
    and sright where their concatenation is equal to s (i.e., sleft + sright =
    s) and the number of distinct letters in sleft and sright is the same.

    Return the number of good splits you can make in s.

    ========================================
    FUNCTION: int numSplits(std::string& s);
    ========================================

    ==========================================================================
    ================================ EXAMPLES ================================
    ==========================================================================

    --- Example 1 ---
    Input: s = "aacaba"
    Output: 2
    Explanation: There are 5 ways to split "aacaba" and 2 of them are good.
    ("a", "acaba") Left string and right string contains 1 and 3 different
    letters respectively.

    ("aa", "caba") Left string and right string contains 1 and 3 different
    letters respectively.

    ("aac", "aba") Left string and right string contains 2 and 2 different
    letters respectively (good split).

    ("aaca", "ba") Left string and right string contains 2 and 2 different
    letters respectively (good split).

    ("aacab", "a") Left string and right string contains 3 and 1 different
    letters respectively.





    --- Example 2 ---
    Input: s = "abcd"
    Output: 1
    Explanation: Split the string as follows ("ab", "cd").

    *** Constraints ***
    1 <= s.length <= 10^5
    s consists of only lowercase English letters.

*/

/* Time  Beats: 95.10% */
/* Space Beats:   100% */

/* Time  Complexity: O(n) */
/* Space Complexity: O(n) */
class Solution {
public:
    int numSplits(std::string& s)
    {
        if (s.length() <  2)
            return 0;
        else if (s.length() == 2)
            return s[0] == s[1] ? 1 : 0;

        const int N = s.length();

        std::vector<int> right_letters(26, 0);
        int right_different = 0;

        for (int i = 0; i < N; i++)
        {
            if (right_letters[s[i] - 'a'] == 0)
                right_different++;

            right_letters[s[i] - 'a']++;
        }

        std::vector<int> left_letters(26, 0);
        int left_different = 0;

        int result = 0;
        for (int i = 0; i < N-1; i++)
        {
            if (left_letters[s[i] - 'a']++ == 0)
                left_different++;

            if (--right_letters[s[i] - 'a'] == 0)
                right_different--;

            if (left_different == right_different)
                result++;
        }

        return result;
    }
};
