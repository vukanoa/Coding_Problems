/*
    ============
    === EASY ===
    ============

    ========================================
    2185) Counting Words with a Given Prefix
    ========================================

    ============
    Description:
    ============

    You are given an array of strings words and a string pref.

    Return the number of strings in words that contain pref as a prefix.

    A prefix of a string s is any leading contiguous substring of s.

    ==============================================================
    FUNCTION: int prefixCount(vector<string>& words, string pref);
    ==============================================================

    ==========================================================================
    ================================ EXAMPLES ================================
    ==========================================================================

    --- Example 1 ---
    Input: words = ["pay","attention","practice","attend"], pref = "at"
    Output: 2
    Explanation: The 2 strings that contain "at" as a prefix are: "attention"
                 and "attend".

    --- Example 2 ---
    Input: words = ["leetcode","win","loops","success"], pref = "code"
    Output: 0
    Explanation: There are no strings that contain "code" as a prefix.


    *** Constraints ***
    1 <= words.length <= 100
    1 <= words[i].length, pref.length <= 100
    words[i] and pref consist of lowercase English letters.

*/

#include <string>
#include <vector>
using namespace std;

/*
    ------------
    --- IDEA ---
    ------------

    Simple Brute-Force. If you know about the built-in function "find", then
    this becomes even simpler and more efficient.

    if function "find" finds a prefix within the parentheses in the string,
    it will return a starting index. Otherwise it will return "string::npos",
    i.e. -1.

    However, since we're looking for a PREFIX, it MUST begin at index 0. Thus,
    if our "find" funciton returns anything other than 0, we know we did NOT
    find our prefix.

    We could, also, use functions:
        1) std::string::substr(pos, how_many), and
        2) std::mismatch(substr, pref)

    To determine if there if a pref prefix in current word.

*/

/* Time  Beats: 100.00% */
/* Space Beats:  85.23% */

/* Time  Complexity: O(n * m) */
/* Space Complexity: O(1)     */
class Solution_Efficient {
public:
    int prefixCount(vector<string>& words, string pref)
    {
        const int N = words.size();
        int result = 0;

        for (const string& word : words)
        {
            if (pref.length() <= word.length() && word.find(pref) == 0)
                result++;
        }

        return result;
    }
};




/*
    ------------
    --- IDEA ---
    ------------

    This one uses a Trie just to show how Tries work and that you can do it
    this way as well. However, it is more efficient to use the Solution above.

*/

/* Time  Beats: 5.04% */
/* Space Beats: 5.04% */

/* Time  Complexity: O(n * l + m) */ // Where 'l' is maximum length of a word
/* Space Complexity: O(n * l)     */
class Solution_Trie {
public:
    int prefixCount(vector<string>& words, string pref)
    {
        Trie trie;

        // Add all words to the Trie
        for (string& word : words)
            trie.add_word(word);

        return trie.count_prefix(pref);
    }

private:
    class Trie {
        // Node class represents each character in Trie
        struct Node {
            vector<Node*> links; // Links to child nodes
            int count; // Number of strings having prefix till this node

            Node() : links(26, nullptr), count(0) {}
        };

        Node* root;

    public:
        Trie() {
            root = new Node();
        }

        // Add word to trie and update prefix counts
        void add_word(string& word)
        {
            Node* curr = root;

            for (const char chr : word)
            {
                if (curr->links[chr - 'a'] == nullptr)
                    curr->links[chr - 'a'] = new Node();

                curr = curr->links[chr - 'a'];
                curr->count++; // Increment count for this prefix
            }
        }

        // Return count of strings having pref as prefix
        int count_prefix(string& pref)
        {
            Node* curr = root;

            for (const char chr : pref)
            {
                if (curr->links[chr - 'a'] == nullptr)
                    return 0; // Prefix not found

                curr = curr->links[chr - 'a'];
            }

            return curr->count; // Return count at last node
        }
    };
};
