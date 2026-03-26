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

    =================================================================
    FUNCTION: int minExtraChar(string s, vector<string>& dictionary);
    =================================================================

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

#include <string>
#include <unordered_set>
#include <vector>
#include <unordered_map>
#include <climits>
using namespace std;

/*
    ------------
    --- IDEA ---
    ------------

    TODO

*/

/* Time  Beats: 68.86% */
/* Space Beats: 73.86% */

/* Time  Complexity: O(N^3)                           */
/* Space Complexity: O(N + total_chars_in_dictionary) */
class Solution_Memoization {
private:
        unordered_map<int, int> memo;

public:
    int minExtraChar(string s, vector<string>& dictionary)
    {
        const int N = s.size();
        unordered_set<string> words(dictionary.begin(), dictionary.end());

        memo[N] = 0; // Initialize

        return solve(0, s, words);
    }

private:
    int solve(int start, string& s, unordered_set<string>& words)
    {
        if (memo.find(start) != memo.end())
            return memo[start];

        const int N = s.size();

        int skip = 1 + solve(start + 1, s, words);
        int take = INT_MAX;

        string substr;
        substr.reserve(N-1 - start + 1);

        /* Take */
        for (int idx = start; idx < N; idx++)
        {
            substr += s[idx];

            if (words.find(substr) != words.end()) // O(L) for Hashing
                take = min(take, solve(idx + 1, s, words));
        }

        return memo[start] = min(take, skip);
    }
};




/*
    ------------
    --- IDEA ---
    ------------

    Almost equivalent to Problem: "Word Break"

*/

/* Time  Beats: 32.71% */
/* Space Beats: 51.58% */

/* Time  Complexity: O(N^3)                           */
/* Space Complexity: O(N + total_chars_in_dictionary) */
class Solution {
public:
    int minExtraChar(string s, vector<string>& dictionary)
    {
        const int N = s.size();

        vector<int> dp(51, INT_MAX);
        dp[N] = 0;

        unordered_set<string> uset(dictionary.begin(), dictionary.end());

        for (int i = N-1; i >= 0; i--)
        {
            string substr;
            substr.reserve(N-1 - i + 1);

            for (int j = i; j < N; j++)
            {
                substr += s[j];

                if (uset.count(substr)) // O(N) to hash + O(1) for comparison
                    dp[i] = min(dp[i], dp[i + (j - i + 1)]);
            }

            dp[i] = min(dp[i], 1 + dp[i+1]);
        }

        return dp[0];
    }
};




/*
    ------------
    --- IDEA ---
    ------------

    Here, by using Trie data structure, we've managed to recude the Time
    Compleixty from O(N^3) down to O(N^2) which is HUGE in a general case.

*/

/* Time  Beats: 84.82% */
/* Space Beats: 26.92% */

/* Time  Complexity: O(N^2)                           */
/* Space Complexity: O(N + total_chars_in_dictionary) */
class Solution_Optimal_Using_Trie {
private:
    struct TrieNode {
        TrieNode* letter[26] = {nullptr};
        bool is_end;

        TrieNode()
            : is_end(false)
        {}
    };

    TrieNode* root = nullptr;

public:
    int minExtraChar(string s, vector<string>& dictionary)
    {
        const int N = s.size();

        vector<int> dp(51, INT_MAX);
        dp[N] = 0;

        /* Insert words to Trie */
        for (const string& word : dictionary)
            insert(word);

        for (int i = N-1; i >= 0; i--)
        {
            TrieNode* node = root;

            for (int j = i; j < N; j++)
            {
                char chr = s[j];

                if ( ! node || ! node->letter[chr - 'a'])
                    break;

                node = node->letter[chr - 'a'];

                if (node->is_end)
                    dp[i] = min(dp[i], dp[i + (j - i + 1)]);
            }

            dp[i] = min(dp[i], 1 + dp[i+1]);
        }

        return dp[0];
    }

private:
    void insert(const string& word)
    {
        if ( ! root)
            root = new TrieNode();

        TrieNode* node = root;
        for (const char& chr : word)
        {
            if ( ! node->letter[chr - 'a'])
                node->letter[chr - 'a'] = new TrieNode();

            node = node->letter[chr - 'a'];
        }

        node->is_end = true;
    }
};
