/*
    ============
    === EASY ===
    ============

    =====================================
    3042) Count Prefix and Suffix Pairs I
    =====================================

    ============
    Description:
    ============

    You are given a 0-indexed string array words.

    Let's define a boolean function isPrefixAndSuffix that takes two strings,
    str1 and str2:

        isPrefixAndSuffix(str1, str2) returns true if str1 is both a prefix and
        a suffix of str2, and false otherwise.

    For example, isPrefixAndSuffix("aba", "ababa") is true because "aba" is a
    prefix of "ababa" and also a suffix, but isPrefixAndSuffix("abc", "abcd")
    is false.

    Return an integer denoting the number of index pairs (i, j) such that
    i < j, and isPrefixAndSuffix(words[i], words[j]) is true.

    ============================================================
    FUNCTION: int countPrefixSuffixPairs(vector<string>& words);
    ============================================================

    ==========================================================================
    ================================ EXAMPLES ================================
    ==========================================================================

    --- Example 1 ---
    Input: words = ["a","aba","ababa","aa"]
    Output: 4
    Explanation: In this example, the counted index pairs are:
    i = 0 and j = 1 because isPrefixAndSuffix("a", "aba") is true.
    i = 0 and j = 2 because isPrefixAndSuffix("a", "ababa") is true.
    i = 0 and j = 3 because isPrefixAndSuffix("a", "aa") is true.
    i = 1 and j = 2 because isPrefixAndSuffix("aba", "ababa") is true.
    Therefore, the answer is 4.

    --- Example 2 ---
    Input: words = ["pa","papa","ma","mama"]
    Output: 2
    Explanation: In this example, the counted index pairs are:
    i = 0 and j = 1 because isPrefixAndSuffix("pa", "papa") is true.
    i = 2 and j = 3 because isPrefixAndSuffix("ma", "mama") is true.
    Therefore, the answer is 2.

    --- Example 3 ---
    Input: words = ["abab","ab"]
    Output: 0
    Explanation: In this example, the only valid index pair is i = 0 and j = 1, and isPrefixAndSuffix("abab", "ab") is false.
    Therefore, the answer is 0.

    *** Constraints ***
    1 <= words.length <= 50
    1 <= words[i].length <= 10
    words[i] consists only of lowercase English letters.

*/

#include <string>
#include <vector>
using namespace std;

/*
    ------------
    --- IDEA ---
    ------------

    Constraints allows us to perform a basic Brute-Force. However, the only
    part that is remotely difficult is "isPrefixAndSuffix".

    To make it easier, we can use built-in function "std::find" from C++ to
    check if there is a prefix.

        string.std::find(potential_substr)

    if it matched a prefix, it mached the "leftmost" prefix. For example:

        string = "abacabacggg"
        potential_substr = "abac"

    Function "find" would return the leftmost index from which you can match a
    prefix, i.e. the index of starting character.

    If function "std::find" returns anything OTHER than 0, then that means we
    either:
        1) didn't match word1 anywhere in word2, or
        2) We did match word1 in word2, but it's NOT a prefix

    In both cases, we immediately ought to return "false".

    If we did match it and it's a prefix, then we have to match it as a suffix
    as well.

    We do that by iterateing word1.length() times and we match last characters
    of both word1 and word2. If they don't match, we return "fasle".

    If they do match, we try second letters from the back, and so on.
    If we're done with the loop and we did NOT return "false", then that means
    word1 is indeed both a prefix and a suffix of word2, therefore we return
    "true".

*/

/* Time  Beats: 100.00% */
/* Space Beats:  78.18% */

/* Time  Complexity: O(n^2) */
/* Space Complexity: O(1)   */
class Solution {
public:
    int countPrefixSuffixPairs(vector<string>& words)
    {
        const int N = words.size();
        int result = 0;

        for (int i = 0; i < N; i++)
        {
            for (int j = i+1; j < N; j++)
            {
                if (isPrefixAndSuffix(words[i], words[j]))
                    result++;
            }
        }

        return result;
    }

private:
    int isPrefixAndSuffix(string& word1, string& word2)
    {
        if (word1.length() > word2.length())
            return false;

        if (word2.find(word1) != 0)
            return false;

        for (int i = 0; i < word1.length(); i++)
        {
            if (word1[word1.length() - 1 - i] != word2[word2.length() - 1 - i])
                return false;
        }

        return true;
    }
};
