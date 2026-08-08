/*
    ==============
    === MEDIUM ===
    ==============

    ========================================================
    3302) Find the Lexicographically Smallest Valid Sequence
    ========================================================

    ============
    Description:
    ============

    You are given two strings word1 and word2.

    A string x is called almost equal to y if you can change at most one
    character in x to make it identical to y.

    A sequence of indices seq is called valid if:

        + The indices are sorted in ascending order.

        + Concatenating the characters at these indices in word1 in the same
          order results in a string that is almost equal to word2.

    Return an array of size word2.length representing the valid sequence of
    indices. If no such sequence of indices exists, return an empty array.

    =====
    Note: that the answer must represent the lexicographically smallest array,
          not the corresponding string formed by those indices. 
    =====

    ================================================================
    FUNCTION: vector<int> validSequence(string word1, string word2);
    ================================================================

    ==========================================================================
    ================================ EXAMPLES ================================
    ==========================================================================

    --- Example 1 ---
    Input: word1 = "vbcca", word2 = "abc"
    Output: [0,1,2]
    Explanation:
    The lexicographically smallest valid sequence of indices is [0, 1, 2]:
        Change word1[0] to 'a'.
        word1[1] is already 'b'.
        word1[2] is already 'c'.

    --- Example 2 ---
    Input: word1 = "bacdc", word2 = "abc"
    Output: [1,2,4]
    Explanation:
    The lexicographically smallest valid sequence of indices is [1, 2, 4]:
        word1[1] is already 'a'.
        Change word1[2] to 'b'.
        word1[4] is already 'c'.

    --- Example 3 ---
    Input: word1 = "aaaaaa", word2 = "aaabc"
    Output: []
    Explanation:
    There is no valid sequence of indices.

    --- Example 4 ---
    Input: word1 = "abc", word2 = "ab"
    Output: [0,1]


    *** Constraints ***
    1 <= word2.length < word1.length <= 3 * 10^5
    word1 and word2 consist only of lowercase English letters.

*/

#include <string>
#include <vector>
using namespace std;





/*
    ------------
    --- IDEA ---
    ------------

    --- Example 1 ---
       v b c c a    a b c
      [2 1 1 0 0]   j    
       ^
       |
       |
       ----- This means: If we substitute 'v', maximal suffix length that can
                         be matched in word2 is of size 2 (which is exactly the
                         amount we need for this example)

    --- Example 2 ---
       b a c d c     a b c
      [1 1 1 1 0]      j    


    TODO

*/

/* Time  Beats: 63.83% */
/* Space Beats: 59.57% */

/* Time  Complexity: O(N + M) */
/* Space Complexity: O(N)     */
class Solution {
public:
    vector<int> validSequence(string word1, string word2)
    {
        const int& N = word1.size();
        const int& M = word2.size();

        vector<int> result;
        result.reserve(M); // To prevent repeated reallocations

        // suffix_match_len[i] --> maximum length of the suffix of word2
        // that can be formed using word1[i+1 ... N-1]
        vector<int> suffix_match_len(N);

        int j = M-1;
        int matched_suffix_len = 0;

        for (int i = N-1; i >= 0; i--)
        {
            suffix_match_len[i] = matched_suffix_len;

            if (j >= 0 && word1[i] == word2[j])
            {
                j--;
                matched_suffix_len++;
            }
        }

        bool used_substitution = false;
        j = 0;

        for (int i = 0; i < N && j < M; i++)
        {
            if (word1[i] == word2[j])
            {
                result.push_back(i);
                j++;
            }
            else if ( ! used_substitution && suffix_match_len[i] >= M-1 - j)
            {
                result.push_back(i); // Substitutionn at this 'i' index
                j++;
                used_substitution = true;
            }
        }

        if (j == M)
            return result;

        return {};
    }
};
