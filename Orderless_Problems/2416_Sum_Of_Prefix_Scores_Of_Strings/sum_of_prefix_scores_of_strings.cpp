#include <iostream>
#include <vector>

/*
    ============
    === HARD ===
    ============

    =====================================
    2416) Sum of Prefix Scores of Strings
    =====================================

    ============
    Description:
    ============

    You are given an array words of size n consisting of non-empty strings.

    We define the score of a string term as the number of strings words[i] such
    that term is a prefix of words[i].

        For example, if words = ["a", "ab", "abc", "cab"], then the score of
        "ab" is 2, since "ab" is a prefix of both "ab" and "abc".

    Return an array answer of size n where answer[i] is the sum of scores of
    every non-empty prefix of words[i].

    
    =====
    Note: Note that a string is considered as a prefix of itself. 
    =====

    =============================================================
    FUNCTION: vector<int> sumPrefixScores(vector<string>& words);
    =============================================================

    ==========================================================================
    ================================ EXAMPLES ================================
    ==========================================================================

    --- Example 1 ---
    Input: words = ["abc","ab","bc","b"]
    Output: [5,4,3,2]
    Explanation: The answer for each string is the following:
    - "abc" has 3 prefixes: "a", "ab", and "abc".
    - There are 2 strings with the prefix "a", 2 strings with the prefix "ab",
      and 1 string with the prefix "abc".
    The total is answer[0] = 2 + 2 + 1 = 5.
    - "ab" has 2 prefixes: "a" and "ab".
    - There are 2 strings with the prefix "a", and 2 strings with the prefix
      "ab".
    The total is answer[1] = 2 + 2 = 4.
    - "bc" has 2 prefixes: "b" and "bc".
    - There are 2 strings with the prefix "b", and 1 string with the prefix
      "bc".
    The total is answer[2] = 2 + 1 = 3.
    - "b" has 1 prefix: "b".
    - There are 2 strings with the prefix "b".
    The total is answer[3] = 2.

    --- Example 2 ---
    Input: words = ["abcd"]
    Output: [4]
    Explanation:
    "abcd" has 4 prefixes: "a", "ab", "abc", and "abcd".
    Each prefix has a score of one, so the total is answer[0] = 1 + 1 + 1 + 1 = 4.


    *** Constraints ***
    1 <= words.length <= 1000
    1 <= words[i].length <= 1000
    words[i] consists of lowercase English letters.

*/

/*
    ------------
    --- IDEA ---
    ------------

    TODO

*/

/* Time  Beats: 38.90% */
/* Space Beats: 17.45% */

/* Time  Complexity: O(n * w) */
/* Space Complexity: O(n * w) */
struct Node{
    int count = 0;
    Node *list[26] = {NULL};

    bool containKey(char ch)
    {
        return list[ch - 'a'] != NULL;
    }

    Node *get(char ch)
    {
        return list[ch - 'a'];
    }

    void put(char ch, Node *new_node)
    {
        list[ch - 'a'] = new_node;
    }

    void inc(char ch)
    {
        list[ch - 'a']->count += 1;
    }

    int retCount(char ch)
    {
        return list[ch - 'a']->count;
    }
};

class Solution {
private:
    Node *root;
public:
    Solution()
    {
        root = new Node;
    }

    void insert(string word)
    {
        Node *node = root;
        for (auto ch : word)
        {
            if ( ! node->containKey(ch))
            {
                node->put(ch,new Node);
            }

            node->inc(ch);
            node = node->get(ch);
        }
    }

    int search(string word)
    {
        Node *node = root;
        int pre_count = 0;

        for (auto ch : word)
        {
            pre_count += node->retCount(ch);
            node = node->get(ch);
        }

        return pre_count;
    }

    vector<int> sumPrefixScores(vector<string>& words)
    {
        // This problem can be solved using the trie data structure
        for (auto word:words)
        {
            insert(word);
        }

        int n = words.size();
        vector<int>res(n);

        for (int i = 0; i < n; i++)
        {
            int pre_count = search(words[i]);
            res[i] = pre_count;
        }

        return res;
    }
};
