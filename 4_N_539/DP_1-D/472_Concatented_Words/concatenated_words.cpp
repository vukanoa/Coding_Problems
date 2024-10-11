#include <iostream>
#include <vector>
#include <unordered_set>

/*
    ============
    === HARD ===
    ============

    ===========================
    472) Concatenated Words
    ===========================

    ============
    Description:
    ============

    Given an array of strings words (without duplicates), return all the
    concatenated words in the given list of words.

    A concatenated word is defined as a string that is comprised entirely of at
    least two shorter words (not necessarily distinct) in the given array.

    ================================================================================
    FUNCTION: vector<string> findAllConcatenatedWordsInADict(vector<string>& words); 
    ================================================================================

    ==========================================================================
    ================================ EXAMPLES ================================
    ==========================================================================

    --- Example 1 ---
    Input: words = ["cat","cats","catsdogcats","dog","dogcatsdog","hippopotamuses","rat","ratcatdogcat"]
    Output: ["catsdogcats","dogcatsdog","ratcatdogcat"]
    Explanation: "catsdogcats" can be concatenated by "cats", "dog" and "cats"; 
    "dogcatsdog" can be concatenated by "dog", "cats" and "dog"; 
    "ratcatdogcat" can be concatenated by "rat", "cat", "dog" and "cat".

    --- Example 2 ---
    Input: words = ["cat","dog","catdog"]
    Output: ["catdog"]


    *** Constraints ***
    1 <= words.length <= 10^4
    1 <= words[i].length <= 30
    words[i] consists of only lowercase English letters.
    All the strings of words are unique.
    1 <= sum(words[i].length) <= 10^5

*/

/*
    ------------
    --- IDEA ---
    ------------

    TODO

*/

/* Time  Beats: 72.36% */
/* Space Beats: 78.94% */

/* Time  Complexity: O(n * L^2) */
/* Space Complexity: O(n * L)   */
class Solution {
public:
    vector<string> findAllConcatenatedWordsInADict(vector<string>& words)
    {
        unordered_set<string> words_set;

        for (string word : words)
            words_set.insert(word);

        vector<string> result;
    
        for (string word : words)
        {
            int n = word.size();
            vector<int> dp(n + 1, 0);
            dp[0] = 1;

            for (int i = 0; i < n; i++)
            {
                if ( ! dp[i])
                    continue;

                for (int j = i + 1; j <= n; j++)
                {
                    if (j - i < n && words_set.count(word.substr(i, j - i)))
                        dp[j] = 1;
                }

                if (dp[n])
                {
                    result.push_back(word);
                    break;
                }
            }
        }

        return result;
    }
};
