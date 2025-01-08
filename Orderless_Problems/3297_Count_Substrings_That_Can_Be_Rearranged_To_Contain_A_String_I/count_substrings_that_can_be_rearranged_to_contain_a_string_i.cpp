/*
    ==============
    === MEDIUM ===
    ==============

    ===================================================================
    3297) Count Substrings That Can Be Rearranged to Contain a String I
    ===================================================================

    ============
    Description:
    ============

    You are given two strings word1 and word2.

    A string x is called valid if x can be rearranged to have word2 as a
    prefix.

    Return the total number of valid substrings of word1.

    ====================================================================
    FUNCTION: long long validSubstringCount(string word1, string word2);
    ====================================================================

    ==========================================================================
    ================================ EXAMPLES ================================
    ==========================================================================

    --- Example 1 ---
    Input: word1 = "bcca", word2 = "abc"
    Output: 1
    Explanation: The only valid substring is "bcca" which can be rearranged to
                 "abcc" having "abc" as a prefix.

    --- Example 2 ---
    Input: word1 = "abcabc", word2 = "abc"
    Output: 10
    Explanation: All the substrings except substrings of size 1 and size 2 are
                 valid.

    --- Example 3 ---
    Input: word1 = "abcabc", word2 = "aaabc"
    Output: 0


    *** Constraints ***
    1 <= word1.length <= 10^5
    1 <= word2.length <= 10^4
    word1 and word2 consist only of lowercase English letters.

*/

#include <string>
#include <vector>
using namespace std;

/*
    ------------
    --- IDEA ---
    ------------

    Sliding Window Technique. You must notice one thing. Let's say we have this
    example:

        word1 = "abcabc",   word2 = "abc"
                 012345

    If we match our word2 in word1, then we don't really need to try "longer"
    windows, it is certain that it will also be a prefix.

    In other words, if "abc" is a prefix of "abc", then it will also be a
    prefix of "abca" and "abcab" and "abcabc", right?

    Therefore, if we match a prefix at some point, we don't want to simply
    increment our "result" variable by one, but by N - index_of_last_chr in
    word1 that makes it a valid prefix.

    In other words:

        word 1 = "a b c a b c"
                  0 1 2 3 4 5

    Since we need to match "abc", we'll succeed once our 'R' pointer gets to
    be at index 2, therefore, we don't want to increment result only be one,
    but by N - R, i.e. 6 - 2 = 4.

        Valid prefixes that BEGIN at index 0 are:

            1) "abc"
            2) "abca"
            3) "abcab"
            4) "abcabc"

    Once we find the prefix we add "N - R" to our result but, then, we also
    try to shrink the window from the left-side and check if that is also a
    valid prefix. If it is, we again add "N - R".

    It's difficult to imagine such case, so here it is:

        word2 = "...c c a b x y z...",    word2 = "abc"
                    3 4 5 6 7 8 9

    Imagine that our prefix window of word1 is "cca". This is NOT a valid
    window.

    Now we extend it to the right by one and it becomes: "ccab". This is indeed
    VALID!

    So we add N - R, where 'R' is the index of 'b' in this case, the last
    character in this valid prefix of word1.

    However, what happens if we SHRINK the window from the left side?

        previous_window = "ccab",   current_window = "cab".

    It seems that current_window is ALSO valid, right?

    Therefore, we add "N - R" again. Those N-R substrings represent all the
    substrings that start at index L(which is now one character to the right
    of the previous 'L' pointer) and end at this 'R' pointer or any of the
    latter indices until the end of word1, that's why we're doing N-R.

    This is important becase, at first, you'd think we would count some
    substrings twice or more times if we are adding N-R when R is NOT moved,
    but it oversees that we are moving our 'L' pointer, which solves this
    potential issue of counting some substring more than once.

*/

/* Time  Beats: 47.66% */
/* Space Beats: 55.86% */

/* Time  Complexity: O(n) */
/* Space Complexity: O(1) */
class Solution {
public:
    long long validSubstringCount(string word1, string word2)
    {
        const int N = word1.size();
        const int M = word2.size();

        vector<int> word2_counter(26, 0);
        for (int i = 0; i < M; i++)
            word2_counter[word2[i] - 'a']++;

        long long result = 0;
        int L = 0; // Left
        int R = 0; // Right

        vector<int> word1_prefix_counter(26, 0);
        while (R < N)
        {
            word1_prefix_counter[word1[R] - 'a']++;

            while (L <= R && is_valid(word1_prefix_counter, word2_counter))
            {
                result += N - R;
                word1_prefix_counter[word1[L] - 'a']--;
                L++;
            }

            R++;
        }

        return result;
    }

private:
    bool is_valid(vector<int>& word1_prefix_counter, vector<int>& word2_counter)
    {
        for (int i = 0; i < 26; i++)
        {
            if (word1_prefix_counter[i] < word2_counter[i])
                return false;
        }

        return true;
    }
};
