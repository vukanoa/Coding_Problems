#include <iostream>
#include <vector>
#include <unordered_map>
#include <unordered_set>
#include <climits>

/*
    ==============
    === MEDIUM ===
    ==============

    =================================
    2707) Extra Character In A String
    =================================

    ============
    Description:
    ============

    You are given a 0-indexed string s and a dictionary of words dictionary.
    You have to break s into one or more non-overlapping substrings such that
    each substring is present in dictionary. There may be some extra characters
    in s which are not present in any of the substrings.

    Return the minimum number of extra characters left over if you break up s
    optimally.

    ================================================================================
    FUNCTION: int minExtraChar(std::string s, std::vector<std::string>& dictionary);
    ================================================================================

    ==========================================================================
    ================================ EXAMPLES ================================
    ==========================================================================

    --- Example 1 ---
    Input: s = "leetscode", dictionary = ["leet","code","leetcode"]
    Output: 1
    Explanation: We can break s in two substrings: "leet" from index 0 to 3 and
    "code" from index 5 to 8. There is only 1 unused character (at index 4), so
    we return 1.


    --- Example 2 ---
    Input: s = "sayhelloworld", dictionary = ["hello","world"]
    Output: 3
    Explanation: We can break s in two substrings: "hello" from index 3 to 7
    and "world" from index 8 to 12. The characters at indices 0, 1, 2 are not
    used in any substring and thus are considered as extra characters. Hence,
    we return 3.


    *** Constraints ***
    1 <= s.length <= 50
    1 <= dictionary.length <= 50
    1 <= dictionary[i].length <= 50
    dictionary[i] and s consists of only lowercase English letters
    dictionary contains distinct words

*/

/* Time  Beats: 34.52% */
/* Space Beats: 36.91% */

/* Time  Complexity: O(n^3) */
/* Space Complexity: O(n) */
class Solution_Memoization {
public:
    int minExtraChar(std::string s, std::vector<std::string>& dictionary)
    {
        std::unordered_set<std::string> words(dictionary.begin(), dictionary.end());

        std::unordered_map<int, int> dp;
        dp[s.length()] = 0;

        return dfs(s, words, dp, 0);
    }

private:
    int dfs(std::string& s, std::unordered_set<std::string>& words, std::unordered_map<int, int>& dp, int start)
    {
        if (dp.find(start) != dp.end())
            return dp[start];

        int result = 1 + dfs(s, words, dp, start+1); // Skip current character

        for (int i = start; i < s.length(); i++)
        {
            std::string substr = s.substr(start, i - start + 1);
            if (words.find(substr) != words.end())
                result = std::min(result, dfs(s, words, dp, i + 1));
        }

        dp[start] = result;

        return dp[start];
    }
};




/*
    ------------
    --- IDEA ---
    ------------

    Almost equivalent to Problem: "Word Break"

*/

/* Time  Beats: 47.21% */
/* Space Beats: 43.30% */

/* Time  Complexity: O(n^3) */
/* Space Complexity: O(n) */
class Solution {
public:
    int minExtraChar(std::string s, std::vector<std::string>& dictionary)
    {
        std::unordered_set<std::string> dict(dictionary.begin(), dictionary.end());
        std::vector<int> dp(s.length() + 1, INT_MAX);

        dp[s.length()] = 0;

        // O(n)
        for (int start = s.length() - 1; start >= 0; start--)
        {
            // O(n)
            for (int i = start; i < s.length(); i++)
            {
                // O(n)
                std::string current_substr = s.substr(start, i - start + 1);

                if (dict.find(current_substr) != dict.end())
                    dp[start] = std::min(dp[start], dp[start + current_substr.length()]);
            }

            dp[start] = std::min(dp[start], 1+dp[start+1]);
        }

        return dp[0];
    }
};
