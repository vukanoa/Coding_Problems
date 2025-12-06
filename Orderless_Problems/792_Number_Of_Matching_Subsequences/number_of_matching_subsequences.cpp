/*
    ==============
    === MEDIUM ===
    ==============

    ====================================
    792) Number of Matching Subsequences
    ====================================

    ============
    Description:
    ============


    Given a string s and an array of strings words, return the number of
    words[i] that is a subsequence of s.

    A subsequence of a string is a new string generated from the original
    string with some characters (can be none) deleted without changing the
    relative order of the remaining characters.

        + For example, "ace" is a subsequence of "abcde".

    =================================================================
    FUNCTION: int numMatchingSubseq(string s, vector<string>& words);
    =================================================================

    ==========================================================================
    ================================ EXAMPLES ================================
    ==========================================================================

    --- Example 1 ---
    Input: s = "abcde", words = ["a","bb","acd","ace"]
    Output: 3
    Explanation: There are three strings in words that are a subsequence of s:
                 "a", "acd", "ace".

    --- Example 2 ---
    Input: s = "dsahjpjauf", words = ["ahjpjau","ja","ahbwzgqnuk","tnmlanowax"]
    Output: 2


    *** Constraints ***
    1 <= s.length <= 5 * 10^4
    1 <= words.length <= 5000
    1 <= words[i].length <= 50
    s and words[i] consist of only lowercase English letters.

*/

#include <string>
#include <vector>
using namespace std;

/*
    ------------
    --- IDEA ---
    ------------

    TODO

*/

/* Time  Beats: 85.13% */
/* Space Beats: 35.47% */

/* Time  Complexity: O(N + sum(words_len)) */
/* Space Complexity: O(sum(words_len))     */
struct Node {
    const string& word;
    int index;

    Node(const string &word, int index) : word(word), index(index) {}
};

class Solution {
public:
    int numMatchingSubseq(const string& s, vector<string>& words)
    {
        vector<Node> buckets[26];

        for (const string& word : words)
        {
            char starting_chr = word[0];
            buckets[starting_chr - 'a'].emplace_back(word, 0);
        }

        int result = 0;
        for (const char& chr : s)
        {
            vector<Node> curr_bucket = buckets[chr - 'a'];
            buckets[chr - 'a'].clear();

            for (Node& node : curr_bucket)
            {
                node.index++;

                if (node.index == node.word.size())
                    result++;
                else
                    buckets[node.word[node.index] - 'a'].push_back(node);
            }
        }

        return result;
    }
};
