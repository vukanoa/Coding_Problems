/*
    ==============
    === MEDIUM ===
    ==============

    ===============================
    720) Longest Word in Dictionary
    ===============================

    ============
    Description:
    ============

    Given an array of strings words representing an English Dictionary, return
    the longest word in words that can be built one character at a time by
    other words in words.

    If there is more than one possible answer, return the longest word with the
    smallest lexicographical order. If there is no answer, return the empty
    string.

    =====
    Note: that the word should be built from left to right with each additional
          character being added to the end of a previous word. 
    =====

    ====================================================
    FUNCTION: string longestWord(vector<string>& words);
    ====================================================

    ==========================================================================
    ================================ EXAMPLES ================================
    ==========================================================================

    --- Example 1 ---
    Input: words = ["w","wo","wor","worl","world"]
    Output: "world"
    Explanation: The word "world" can be built one character at a time by
                 "w", "wo", "wor", and "worl".

    --- Example 2 ---
    Input: words = ["a","banana","app","appl","ap","apply","apple"]
    Output: "apple"
    Explanation: Both "apply" and "apple" can be built from other words in the
                 dictionary. However, "apple" is lexicographically smaller than
                 "apply".


    *** Constraints ***
    1 <= words.length <= 1000
    1 <= words[i].length <= 30
    words[i] consists of lowercase English letters.

*/

#include <string>
#include <vector>
#include <unordered_set>
#include <string>
#include <vector>
#include <unordered_map>
#include <stack>
using namespace std;

/*
    ------------
    --- IDEA ---
    ------------

    TODO
    (Brute-force)

*/

/* Time  Beats: 93.91% */
/* Space Beats: 97.93% */

/* Time  Complexity: O(N * L^2) */ // L is the avg. length of the word in words
/* Space Complexity: O(N * L )  */
class Solution {
public:
    string longestWord(vector<string> &words)
    {
        string result = "";

        unordered_set<string> use_words(words.begin(), words.end());

        for (const string &word : words)
        {
            if (word.length() > result.length()   ||   (word.length() == result.length() && word < result))
            {
                bool is_good = true;

                for (int k = 1; k < (int)word.length(); ++k)
                {
                    if (use_words.find(word.substr(0, k)) == use_words.end())
                    {
                        is_good = false;
                        break;
                    }
                }

                if (is_good)
                    result = word;
            }
        }

        return result;
    }
};




/*
    ------------
    --- IDEA ---
    ------------

    TODO

*/

/* Time  Beats: 28.91% */
/* Space Beats: 38.43% */

/* Time  Complexity: O(N * L) */ // L is the avg. lngth of the word in words
/* Space Complexity: O(N * L) */
class Node {
public:
    char chr;
    unordered_map<char, Node *> children;
    int end;

    Node(char c) : chr(c), end(0)
    {

    }
};

class Trie {
public:
    Node *root;
    vector<string> words;

    Trie()
    {
        root = new Node('0');
    }

    void insert(const string &word, int index)
    {
        Node *cur = root;
        for (const char &c : word)
        {
            if (cur->children.find(c) == cur->children.end())
            {
                cur->children[c] = new Node(c);
            }

            cur = cur->children[c];
        }

        cur->end = index;
    }

    string dfs ()
    {
        string result = "";
        stack<Node *> node_stack;
        node_stack.push(root);

        while ( ! node_stack.empty())
        {
            Node *node = node_stack.top();
            node_stack.pop();

            if (node->end > 0 || node == root)
            {
                if (node != root)
                {
                    const string &word = words[node->end - 1];
                    if (word.length() > result.length() ||
                        (word.length() == result.length() && word < result))
                    {
                        result = word;
                    }
                }

                for (auto &[_, child_node] : node->children)
                {
                    node_stack.push(child_node);
                }
            }
        }

        return result;
    }

    ~Trie()
    {
        // Optional: add a destructor to free nodes if needed
        free_node(root);
    }

private:
    void free_node(Node *node)
    {
        for (auto &[_, child_node] : node->children)
        {
            free_node(child_node);
        }
        delete node;
    }
};

class Solution_Trie {
public:
    string longestWord(vector<string> &words)
    {
        Trie trie;
        int index = 0;

        for (const string &word : words)
        {
            trie.insert(word, ++index);
        }
        trie.words = words;

        return trie.dfs();
    }
};
