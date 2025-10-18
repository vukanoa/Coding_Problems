/*
    ============
    === EASY ===
    ============

    ============================
    2000) Reverse Prefix of Word
    ============================

    ============
    Description:
    ============

    Given a 0-indexed string word and a character ch, reverse the segment of
    word that starts at index 0 and ends at the index of the first occurrence
    of ch (inclusive). If the character ch does not exist in word, do nothing.

    For example, if word = "abcdefd" and ch = "d", then you should reverse the
    segment that starts at 0 and ends at 3 (inclusive). The resulting string
    will be "dcbaefd".

    Return the resulting string.

    =====================================================
    FUNCTION: string reversePrefix(string word, char ch);
    =====================================================

    ==========================================================================
    ================================ EXAMPLES ================================
    ==========================================================================

    --- Example 1 ---
    Input: word = "abcdefd", ch = "d"
    Output: "dcbaefd"
    Explanation: The first occurrence of "d" is at index 3. 
    Reverse the part of word from 0 to 3 (inclusive), the resulting string is
    "dcbaefd".

    --- Example 2 ---
    Input: word = "xyxzxe", ch = "z"
    Output: "zxyxxe"
    Explanation: The first and only occurrence of "z" is at index 3.
    Reverse the part of word from 0 to 3 (inclusive), the resulting string is
    "zxyxxe".

    --- Example 3 ---
    Input: word = "abcd", ch = "z"
    Output: "abcd"
    Explanation: "z" does not exist in word.
    You should not do any reverse operation, the resulting string is "abcd".


    *** Constraints ***
    1 <= word.length <= 250
    word consists of lowercase English letters.
    ch is a lowercase English letter.

*/

#include <algorithm>
#include <string>
using namespace std;

/*
    ------------
    --- IDEA ---
    ------------

    TODO

*/

/* Time  Beats: 100.00% */
/* Space Beats:  66.61% */

/* Time  Complexity: O(N) */
/* Space Complexity: O(N) */
class Solution {
public:
    string reversePrefix(string word, char ch)
    {
        const int N = word.length();

        int idx = word.find(ch);
        if (idx == string::npos)
            return word;

        string result;
        result.reserve(N); // To prevent reallocation

        string prefix = word.substr(0, idx+1);
        reverse(prefix.begin(), prefix.end());

        result.insert(result.end(), prefix.begin(), prefix.end());
        result += word.substr(idx+1);

        return result;
    }
};




/*
    ------------
    --- IDEA ---
    ------------

    TODO

*/

/* Time  Beats: 100.00% */
/* Space Beats:  35.82% */

/* Time  Complexity: O(N) */
/* Space Complexity: O(1) */
class Solution_Concise {
public:
    string reversePrefix(string word, char ch)
    {
        int idx = word.find(ch);

        if (idx != string::npos)
            reverse(word.begin(), word.begin() + idx + 1);

        return word;
    }
};
