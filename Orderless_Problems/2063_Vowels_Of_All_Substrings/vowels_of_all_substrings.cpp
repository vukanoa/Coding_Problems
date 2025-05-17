/*
    ==============
    === MEDIUM ===
    ==============

    ==============================
    2063) Vowels of All Substrings
    ==============================

    ============
    Description:
    ============

    Given a string word, return the sum of the number of vowels
    ('a', 'e', 'i', 'o', and 'u') in every substring of word.

    A substring is a contiguous (non-empty) sequence of characters within a
    string.

    =====
    Note: Due to the large constraints, the answer may not fit in a signed
          32-bit integer. Please be careful during the calculations.
    =====

    =============================================
    FUNCTION: long long countVowels(string word);
    =============================================

    ==========================================================================
    ================================ EXAMPLES ================================
    ==========================================================================

    --- Example 1 ---
    Input: word = "aba"
    Output: 6
    Explanation:
    All possible substrings are: "a", "ab", "aba", "b", "ba", and "a".
    - "b" has 0 vowels in it
    - "a", "ab", "ba", and "a" have 1 vowel each
    - "aba" has 2 vowels in it
    Hence, the total sum of vowels = 0 + 1 + 1 + 1 + 1 + 2 = 6.

    --- Example 2 ---
    Input: word = "abc"
    Output: 3
    Explanation:
    All possible substrings are: "a", "ab", "abc", "b", "bc", and "c".
    - "a", "ab", and "abc" have 1 vowel each
    - "b", "bc", and "c" have 0 vowels each
    Hence, the total sum of vowels = 1 + 1 + 1 + 0 + 0 + 0 = 3.

    --- Example 3 ---
    Input: word = "ltcd"
    Output: 0
    Explanation: There are no vowels in any substring of "ltcd".


    *** Constraints ***
    1 <= word.length <= 10^5
    word consists of lowercase English letters.

*/

#include <string>
#include <unordered_set>
#include <vector>
using namespace std;

/*
    ------------
    --- IDEA ---
    ------------

    TODO

*/

/* Time  Beats: 48.64% */
/* Space Beats:  6.95% */

/* Time  Complexity: O(N) */
/* Space Complexity: O(N) */
class Solution {
public:
    long long countVowels(string word)
    {
        const int N = word.length();
        vector<long long> dp(N,0);

        if (is_vowel(word[0]))
            dp[0] = 1;
        else
            dp[0] = 0;


        for (int i = 1; i < N; i++)
        {
            if (is_vowel(word[i]))
                dp[i]  = 1 + dp[i-1]+i;
            else
                dp[i] = dp[i-1];
        }

        long long result = 0;
        for (int i = 0; i < N; i++)
            result += dp[i];

        return result;
    }

private:
    bool is_vowel(char& chr)
    {
        if (chr == 'a' || chr == 'e' || chr == 'i' || chr == 'o' || chr == 'u')
            return true;

        return false;
    }
};




/*
    ------------
    --- IDEA ---
    ------------

    Another way of implementing it.

*/

/* Time  Beats: 21.09% */
/* Space Beats: 33.75% */

/* Time  Complexity: O(N) */
/* Space Complexity: O(1) */
class Solution_2 {
public:
    long long countVowels(string word)
    {
        const int N = word.length();
        long long result = 0;

        unordered_set<char> vowel = {'a', 'e', 'i', 'o', 'u'};

        for (int i = 0; i < N; i++)
        {
            if (vowel.count(word[i]))
                result += (i + 1) * (word.length() - i);
        }

        return result;
    }
};
