/*
    ==============
    === MEDIUM ===
    ==============

    ===============================================
    211) Design Add And Search Words Data Structure
    ===============================================

    ============
    Description:
    ============

    Design a data structure that supports adding new words and finding if a
    string matches any previously added string.

    Implement the WordDictionary class:

        WordDictionary() Initializes the object.

        void addWord(word) Adds word to the data structure, it can be matched
        later.

        bool search(word) Returns true if there is any string in the data
        structure that matches word or false otherwise. word may contain dots
        '.' where dots can be matched with any letter.


    ===============================
    CLASS:
    class WordDictionary {
    public:
        WordDictionary()
        {}

        void addWord(string word)
        {}

        bool search(string word)
        {}

    private:
        struct Trie{
            std::vector<bool> letters(26, false);
            bool valid_word = false;
        };
    };
    ===============================

    ==========================================================================
    ================================ EXAMPLES ================================
    ==========================================================================

    --- Example 1 ---
    Input
    ["WordDictionary","addWord","addWord","addWord","search","search","search","search"]
    [[],["bad"],["dad"],["mad"],["pad"],["bad"],[".ad"],["b.."]]

    Output:
    [null,null,null,null,false,true,true,true]

    Explanation
    WordDictionary wordDictionary = new WordDictionary();
    wordDictionary.addWord("bad");
    wordDictionary.addWord("dad");
    wordDictionary.addWord("mad");
    wordDictionary.search("pad"); // return False
    wordDictionary.search("bad"); // return True
    wordDictionary.search(".ad"); // return True
    wordDictionary.search("b.."); // return True




    *** Constraints ***
    1 <= word.length <= 25
    word in addWord consists of lowercase English letters.
    word in search consist of '.' or lowercase English letters.
    There will be at most 2 dots in word for search queries.
    At most 104 calls will be made to addWord and search.

*/

#include <string>
using namespace std;

/*
    ------------
    --- IDEA ---
    ------------

    TODO
    Fundamental Trie problem.

*/

/* Time  Beats: 54.63% */
/* Space Beats: 30.72% */

/* Time  Complexity: O(N) */
/* Space Complexity: O(T) */
class WordDictionary {
private:
    struct TrieNode {
        TrieNode* letter[26] = {nullptr};
        bool is_end;

        TrieNode()
            : is_end(false)
        {}
    };

    TrieNode* root;

public:
    WordDictionary()
        : root(nullptr)
    {

    }

    void addWord(string word)
    {
        if (search(word)) // If it's already added
            return;

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
    
    bool search(string word)
    {
        return dfs_search(0, word, root);
    }

    bool dfs_search(int start, string word, TrieNode* node)
    {
        if ( ! root)
            return false;

        const int N = word.size();
        if (start == N && node->is_end)
            return true;

        for (int letter_idx = start; letter_idx < N; letter_idx++)
        {
            char chr = word[letter_idx];

            if (chr == '.')
            {
                for (int i = 0; i < 26; i++)
                {
                    if (node->letter[i] && dfs_search(letter_idx+1, word, node->letter[i]))
                        return true;
                }

                return false;
            }
            else
            {
                if ( ! node->letter[chr - 'a'])
                    return false;

                node = node->letter[chr - 'a'];
            }
        }

        return node->is_end;
    }
};

/**
 * Your WordDictionary object will be instantiated and called as such:
 * WordDictionary* obj = new WordDictionary();
 * obj->addWord(word);
 * bool param_2 = obj->search(word);
 */
