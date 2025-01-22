/*
    ==============
    === MEDIUM ===
    ==============

    ======================================================
    3291) Minimum Number of Valid Strings to Form Target I
    ======================================================

    ============
    Description:
    ============

    You are given an array of strings words and a string target.

    A string x is called valid if x is a prefix of any string in words.

    Return the minimum number of valid strings that can be concatenated to form
    target. If it is not possible to form target, return -1.

    ====================================================================
    FUNCTION: int minValidStrings(vector<string>& words, string target);
    ====================================================================

    ==========================================================================
    ================================ EXAMPLES ================================
    ==========================================================================

    --- Example 1 ---
    Input: words = ["abc","aaaaa","bcdef"], target = "aabcdabc"
    Output: 3
    Explanation:
    The target string can be formed by concatenating:
        Prefix of length 2 of words[1], i.e. "aa".
        Prefix of length 3 of words[2], i.e. "bcd".
        Prefix of length 3 of words[0], i.e. "abc".


    --- Example 2 ---
    Input: words = ["abababab","ab"], target = "ababaababa"
    Output: 2
    Explanation:
    The target string can be formed by concatenating:
        Prefix of length 5 of words[0], i.e. "ababa".
        Prefix of length 5 of words[0], i.e. "ababa".


    --- Example 3 ---
    Input: words = ["abcdef"], target = "xyz"
    Output: -1


    *** Constraints ***
    1 <= words.length <= 100
    1 <= words[i].length <= 5 * 10^3
    The input is generated such that sum(words[i].length) <= 10^5.
    words[i] consists only of lowercase English letters.
    1 <= target.length <= 5 * 10^3
    target consists only of lowercase English letters.

*/

#include <climits>
#include <string>
#include <vector>
using namespace std;

// This is similar to Word-Break, but this Solution gives us a TLE
class Solution_TLE {
public:
    int minValidStrings(vector<string>& words, string target)
    {
        std::vector<bool> dp(target.length() + 1, false);
        std::vector<int> needed_valid_strings(target.length() + 1, INT_MAX);

        dp[target.length()] = true;
        needed_valid_strings[target.length()] = 0;

        for (int start = target.length() - 1; start >= 0; start--)
        {
            for (int i = target.length()-1; i >= start; i--)
            {
                std::string current_substr = target.substr(start, i - start + 1);

                for (const string& word : words)
                {
                    if (word.find(current_substr) == 0 && dp[i + 1])
                    {
                        dp[start] = true;
                        needed_valid_strings[start] = min(needed_valid_strings[start], 1 + needed_valid_strings[i + 1]);
                    }
                }
            }
        }

        return dp[0] ? needed_valid_strings[0] : -1;
    }
};






/*
    ------------
    --- IDEA ---
    ------------

    First, we have to make a Trie. It's important to note this part in "insert"
    function:

    void insert(const string& word)
    {
        Node* node = root;

        for (const char chr : word)
        {
            if ( ! node->letters[chr - 'a'])
                node->letters[chr - 'a'] = new Node();

            node = node->letters[chr - 'a'];
            node->is_word_end = true; // <---------------- This one!
        }
    }

    Why are we marking that EVERY CHARACTER is an end of the word?

    Because we ought to find ANY PREFIX! Therefore, every prefix in words MUST
    be considered a valid word, so that we could find each and every prefix we
    want.


    Now we'll have a "dp" vector. It will represent, for dp[i], how many
    strings, minimally, is required to form that string ending at 'i' character
    0-based in target string.

    For example:

        "agk"
         012

    dp = [INT_MAX, INT_MAX, INT_MAX, INT_MAX]
             0        1        2        3


    dp[2] is what we need. We want to to see what is the LEAST amount of
    strings we can concatenate in order to form "agk" string.


    Once we form a Trie, we'll push all the words from "words" and we'll mark
    every prefix in every word, through Trie, as if that's a valid string.

    Then, we'll go through all the target characters, starting at each
    character to see how many prefixes starting at that character are.

    Then, once we see that, strating from that idx in target, we'll update
    the amount of needed strings in order to make certain prefixes in target.

    At the end we check if we could at all concatenate any number of strings in
    order to create the target string.

    We are checking that like this:

        return dp[N] == INT_MAX ? -1 : dp[N];


    The best advice for Trie type of problems is to Draw a Trie and go through
    the code. It's difficult to see the reason behind some lines if you don't
    actually go line-by-line and look at the drawing of the Trie.

*/

/* Time  Beats: 18.00% */
/* Space Beats:  5.67% */

/* Time  Complexity: O(N * max(len(words[i]))) */
/* Space Complexity: O(N)                      */
class Node {
public:
    Node* letters[26];
    bool is_word_end = false;

};

class Trie {
public:
    Node* root;

    Trie()
    {
        root = new Node();
    }

    void insert(const string& word)
    {
        Node* node = root;

        for (const char chr : word)
        {
            if ( ! node->letters[chr - 'a'])
                node->letters[chr - 'a'] = new Node();

            node = node->letters[chr - 'a'];
            node->is_word_end = true;
        }
    }


    vector<int> search(const string& target, int start)
    {
        vector<int> valid_lengths;
        Node* node = root;

        for (int i = start; i < target.length(); i++)
        {
            if ( ! node->letters[target[i] - 'a'])
                break;

            node = node->letters[target[i] - 'a'];

            if (node->is_word_end)
                valid_lengths.push_back(i - start + 1);
        }

        return valid_lengths;
    }
};

class Solution {
public:
    int minValidStrings(vector<string>& words, string target)
    {
        const int N = target.length();

        Trie trie;

        for (const string& word : words)
            trie.insert(word);

        vector<int> dp(N + 1, INT_MAX);
        dp[0] = 0;

        for (int i = 0; i < N; i++)
        {
            if (dp[i] == INT_MAX)
                continue;

            vector<int> lengths = trie.search(target, i);

            for (const int& len : lengths)
                dp[i + len] = min(dp[i + len], dp[i] + 1);
        }

        return dp[N] == INT_MAX ? -1 : dp[N];
    }
};
