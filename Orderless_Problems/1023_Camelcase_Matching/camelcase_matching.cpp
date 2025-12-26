/*
    ==============
    === MEDIUM ===
    ==============

    ===========================
    1023) Cameelcase Matching
    ===========================

    ============
    Description:
    ============

    Given an array of strings queries and a string pattern, return a boolean
    array answer where answer[i] is true if queries[i] matches pattern, and
    false otherwise.

    A query word queries[i] matches pattern if you can insert lowercase English
    letters into the pattern so that it equals the query. You may insert a
    character at any position in pattern or you may choose not to insert any
    characters at all.

    ===========================================================================
    FUNCTION: vector<bool> camelMatch(vector<string>& queries, string pattern);
    ===========================================================================

    ==========================================================================
    ================================ EXAMPLES ================================
    ==========================================================================

    --- Example 1 ---
    Input: queries = ["FooBar","FooBarTest","FootBall","FrameBuffer","ForceFeedBack"], pattern = "FB"
    Output: [true,false,true,true,false]
    Explanation: "FooBar" can be generated like this "F" + "oo" + "B" + "ar".
    "FootBall" can be generated like this "F" + "oot" + "B" + "all".
    "FrameBuffer" can be generated like this "F" + "rame" + "B" + "uffer".

    --- Example 2 ---
    Input: queries = ["FooBar","FooBarTest","FootBall","FrameBuffer","ForceFeedBack"], pattern = "FoBa"
    Output: [true,false,true,false,false]
    Explanation: "FooBar" can be generated like this "Fo" + "o" + "Ba" + "r".
    "FootBall" can be generated like this "Fo" + "ot" + "Ba" + "ll".

    --- Example 3 ---
    Input: queries = ["FooBar","FooBarTest","FootBall","FrameBuffer","ForceFeedBack"], pattern = "FoBaT"
    Output: [false,true,false,false,false]
    Explanation: "FooBarTest" can be generated like this "Fo" + "o" + "Ba" + "r" + "T" + "est".


    *** Constraints ***
    1 <= pattern.length, queries.length <= 100
    1 <= queries[i].length <= 100
    queries[i] and pattern consist of English letters.

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

/* Time  Beats: 100.00% */
/* Space Beats:   8.08% */

/* Time  Complexity: O(N + M) */
/* Space Complexity: O(M)     */
class Trie {
public:
    struct TrieNode
    {
        TrieNode* child[52];
        bool is_leaf_node;
    };

    TrieNode* root;

    Trie()
    {
        root = get_trie_node();
    }

    TrieNode* get_trie_node()
    {
        TrieNode* node = new TrieNode();

        for (int i = 0; i < 52; i++)
            node->child[i] = nullptr;

        node->is_leaf_node = false;
        return node;
    }

    int char_to_index(char chr)
    {
        if (chr >= 'a' && chr <= 'z')
            return chr - 'a';

        return (chr - 'A') + 26;
    }

    void insert(const string& pattern)
    {
        TrieNode* node = root;

        for (char chr : pattern)
        {
            int idx = char_to_index(chr);

            if ( ! node->child[idx])
                node->child[idx] = get_trie_node();

            node = node->child[idx];
        }

        node->is_leaf_node = true;
    }

    bool search(const string& query)
    {
        return search_recursive(root, query, 0);
    }

private:
    bool search_recursive(TrieNode* node, const string& query, int idx)
    {
        if (idx == query.size())
            return node->is_leaf_node;

        char chr = query[idx];

        // Lowercase letters may be skipped
        if (chr >= 'a' && chr <= 'z')
        {
            int idx = char_to_index(chr);

            if (node->child[idx])
            {
                if (search_recursive(node->child[idx], query, idx + 1))
                    return true;
            }

            return search_recursive(node, query, idx + 1);
        }
        else
        {
            // Uppercase letters must match exactly
            int idx = char_to_index(chr);

            if ( ! node->child[idx])
                return false;

            return search_recursive(node->child[idx], query, idx + 1);
        }
    }
};

class Solution {
public:
    vector<bool> camelMatch(vector<string>& queries, string pattern)
    {
        Trie trie;
        trie.insert(pattern);

        vector<bool> result;
        result.reserve(queries.size());

        for (const string& query : queries)
            result.push_back(trie.search(query));

        return result;
    }
};
