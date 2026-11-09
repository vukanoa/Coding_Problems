/*
    ==============
    === MEDIUM ===
    ==============

    =======================================
    3839) Number of Prefix Connected Groups
    =======================================

    ============
    Description:
    ============


    You are given an array of strings words and an integer k.

    Two words a and b at distinct indices are prefix-connected if:

        a[0..k-1] == b[0..k-1].

    A connected group is a set of words such that each pair of words is
    prefix-connected.

    Return the number of connected groups that contain at least two words,
    formed from the given words.

    =====
    Note: Words with length less than k cannot join any group and are ignored.
          Duplicate strings are treated as separate words.
    =====

    ============================================================
    FUNCTION: int prefixConnected(vector<string>& words, int k);
    ============================================================

    ==========================================================================
    ================================ EXAMPLES ================================
    ==========================================================================

    --- Example 1 ---
    Input: words = ["apple","apply","banana","bandit"], k = 2
    Output: 2
    Explanation:
    Words sharing the same first k = 2 letters are grouped together:
        words[0] = "apple" and words[1] = "apply" share prefix "ap".
        words[2] = "banana" and words[3] = "bandit" share prefix "ba".
    Thus, there are 2 connected groups, each containing at least two words.


    --- Example 2 ---
    Input: words = ["car","cat","cartoon"], k = 3
    Output: 1
    Explanation:
    Words are evaluated for a prefix of length k = 3:
        words[0] = "car" and words[2] = "cartoon" share prefix "car".
        words[1] = "cat" does not share a 3-length prefix with any other word.
    Thus, there is 1 connected group.


    --- Example 3 ---
    Input: words = ["bat","dog","dog","doggy","bat"], k = 3
    Output: 2
    Explanation:
    Words are evaluated for a prefix of length k = 3:
        words[0] = "bat" and words[4] = "bat" form a group.
        words[1] = "dog", words[2] = "dog" and words[3] = "doggy" share prefix
                   "dog".
    Thus, there are 2 connected groups, each containing at least two words.


    *** Constraints ***
    1 <= words.length <= 5000
    1 <= words[i].length <= 100
    1 <= k <= 100
    All strings in words consist of lowercase English letters.

*/

#include <string>
#include <unordered_map>
#include <unordered_set>
#include <vector>
using namespace std;

/*
    ------------
    --- IDEA ---
    ------------

    TODO

*/

/* Time  Beats: 5.24% */
/* Space Beats: 5.24% */

/* Time  Complexity: O(S) */ // S = total number of characters across ALL words
/* Space Complexity: O(S) */
class TrieNode {
public:
    TrieNode* letter[26] = {};
    bool      is_end     = false;

    ~TrieNode()
    {
        for (int i = 0; i < 26; i++)
        {
            delete letter[i];
        }
    }
};

class Trie {
private:
    TrieNode* root = nullptr;

public:
    Trie(const Trie& other) = delete;      // no copy constructor
    Trie& operator=(const Trie&) = delete; // no copy assignment

    Trie()
    {
        root = new TrieNode();
    }

    ~Trie()
    {
        delete root;
    }

    void add_word(const string& word, int curr_k, int k, unordered_set<string>& groups)
    {
        const int N = word.size();
        if (N < k)
            return;

        TrieNode* node = root;
        bool prefix_connected = true;

        for (const char& chr : word)
        {
            if (node->letter[chr - 'a'] == nullptr)
            {
                if (curr_k < k)
                    prefix_connected = false;

                node->letter[chr - 'a'] = new TrieNode();
            }

            ++curr_k;

            node = node->letter[chr - 'a'];
        }
        node->is_end = true;

        if (prefix_connected == true)
            groups.insert(word.substr(0, k));
    }
};

class Solution {
public:
    int prefixConnected(vector<string>& words, int k)
    {
        unordered_set<string> groups;
        Trie trie;

        for (const string& word : words)
            trie.add_word(word, 0, k, groups);

        return groups.size();
    }
};




/*
    ------------
    --- IDEA ---
    ------------

    TODO

*/

/* Time  Beats: 72.93% */
/* Space Beats: 61.57% */

/* Time  Complexity: O(S)     */
/* Space Complexity: O(U + K) */ // U = Number of UNIQUE k-length prefixes
class Solution_Hash_Map {
public:
    int prefixConnected(vector<string>& words, int k)
    {
        const int N = words.size();
        unordered_map<string, int> umap;

        for (int i = 0; i < N; i++)
        {
            if (words[i].size() >= k)
                ++umap[words[i].substr(0, k)];
        }

        int groups = 0;
        for (auto [k_len_prefix, frequency] : umap)
        {
            if (frequency >= 2)
                ++groups;
        }

        return groups;
    }
};
