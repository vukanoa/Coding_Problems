/*
    ==============
    === MEDIUM ===
    ==============

    ===========================
    139) Word Break
    ===========================

    ============
    Description:
    ============

    Given a string 's' and a dictionary of strings "wordDict", return true
    if 's' can be segmented a space-separated sequence of one or more
    dictrionary words.

    =====
    Node: The same word in the dictionary may be reused multiple times in the
    ===== segmentation.

    =============================================================
    FUNCTION: bool wordBreak(string s, vector<string>& wordDict);
    =============================================================

    ==========================================================================
    ================================ EXAMPLES ================================
    ==========================================================================

    --- Example 1 ---
    Input:  s = "leetcode", wordDict = ["leet", "code"]
    Output: true

    --- Example 2 ---
    Input:  s = "applepenapple", wordDict = ["apple", "pen"]
    Output: pen

    --- Example 3 ---
    Input:  s = "catsandog", wordDict = ["cats", "dog", "sand", "and", "cat"]
    Output: false

    *** Constraints ***
    1 <= s.length <= 300
    1 <= wordDict.length <= 1000
    1 <= wordDict[i].length <= 20
    s and wordDict[i] consist of only lowercase English letters.
    All the strings of wordDict are unique.

*/


#include <cstring>
#include <string>
#include <unordered_set>
#include <vector>
using namespace std;

/*
    ------------
    --- IDEA ---
    ------------

    --- Example 1 ---

    Input:  s = "leetcode", wordDict = ["leet", "code"]
    Output: true


    1) 'e' // start: 7
                                      0  1  2  3  4  5  6  7  8  9
        j = 7   "e"             dp = [_  _  _  _  _  _  _  _  _  T]



    2) 'd' // start: 6
                                      0  1  2  3  4  5  6  7  8  9
        j = 6   "d"             dp = [_  _  _  _  _  _  _  _  _  T]
        j = 7   "de"            dp = [_  _  _  _  _  _  _  _  _  T]



    3) 'o' // start: 5
                                     0  1  2  3  4  5  6  7  8  9
        j = 5   "o"            dp = [_  _  _  _  _  _  _  _  _  T]
        j = 6   "od"           dp = [_  _  _  _  _  _  _  _  _  T]
        j = 7   "ode"          dp = [_  _  _  _  _  _  _  _  _  T]



    4) 'c' // start: 4
                                     0  1  2  3  4  5  6  7  8  9
        j = 4   "c"            dp = [_  _  _  _  _  _  _  _  _  T]
        j = 5   "co"           dp = [_  _  _  _  _  _  _  _  _  T]
        j = 6   "cod"          dp = [_  _  _  _  _  _  _  _  _  T]
        j = 7   "code"         dp = [_  _  _  _  T  _  _  _  _  T]
                                                 ^
                                                 |
                                              changed


    5. 't' // start: 3
                                     0  1  2  3  4  5  6  7  8  9
    j = 3   "t"                dp = [_  _  _  _  T  _  _  _  _  T] 
    j = 4   "tc"               dp = [_  _  _  _  T  _  _  _  _  T]
    j = 5   "tco"              dp = [_  _  _  _  T  _  _  _  _  T]
    j = 6   "tcod"             dp = [_  _  _  _  T  _  _  _  _  T]
    j = 7   "tcode"            break because it's LONGER than longest_word_len



    6. 'e' // start: 2
                                     0  1  2  3  4  5  6  7  8  9
    j = 2   "e"                dp = [_  _  _  _  T  _  _  _  _  T]
    j = 3   "et"               dp = [_  _  _  _  T  _  _  _  _  T]
    j = 4   "etc"              dp = [_  _  _  _  T  _  _  _  _  T]
    j = 5   "etco"             dp = [_  _  _  _  T  _  _  _  _  T]
    j = 6   "etcod"            break because it's LONGER than longest_word_len
    j = 7   "etcode"           break because it's LONGER than longest_word_len



    7. 'e' // start: 1
                                     0  1  2  3  4  5  6  7  8  9
    j = 1   "e"               dp = [_  _  _  _  T  _  _  _  _  T]
    j = 2   "ee"              dp = [_  _  _  _  T  _  _  _  _  T]
    j = 3   "eet"             dp = [_  _  _  _  T  _  _  _  _  T]
    j = 4   "eetc"            dp = [_  _  _  _  T  _  _  _  _  T]
    j = 5   "eetco"           break because it's LONGER than longest_word_len
    j = 6   "eetcod"          break because it's LONGER than longest_word_len
    j = 7   "eetcode"         break because it's LONGER than longest_word_len



    8. 'l' // start: 0
                                     0  1  2  3  4  5  6  7  8  9
    j = 0   "l"                dp = [_  _  _  _  T  _  _  _  _  T]
    j = 1   "le"               dp = [_  _  _  _  T  _  _  _  _  T]
    j = 2   "lee"              dp = [_  _  _  _  T  _  _  _  _  T]
    j = 3   "leet"             dp = [T  _  _  _  T  _  _  _  _  T]
                                     ^
                                     |
                                  changed

    At the end simply return dp[0].

*/

/* Time  Beats: 100.00% */
/* Space Beats:  78.21% */

/* Time  Complexity: O(N^3)                    */
/* Space Complexity: O(N + total_dict_chars)   */
class Solution_Bottom_Up___Tabulation {
public:
    bool wordBreak(string s, vector<string>& wordDict)
    {
        const int N = s.size();
        const int D = wordDict.size();

        /* Bottom-Up DP vector */
        vector<bool> dp(N+1, false);
        dp[N] = true; // Empty string can ALWAYS be matched

        /* Transform to HashSet */
        unordered_set<string> uset(wordDict.begin(), wordDict.end());

        /* Find Length of the LONGEST word in wordDict */
        unsigned long longest_word_len = 0;
        for (const string& word : wordDict)
            longest_word_len = max(longest_word_len, word.size());

        // O(N^3) (entire block)
        for (int start = N-1; start >= 0; start--) // O(N)
        {
            int substr_size = 0;
            string substr;
            substr.reserve(N - start); // To prevent reallocations

            for (int j = start; j < N; j++) // O(N)
            {
                substr += s[j];
                substr_size++;

                if (substr_size > longest_word_len)
                    break;

                // uset.count(substr) takes O(N) because of Hashing
                if (uset.count(substr) && dp[start + substr_size])
                {
                    dp[start] = true;
                    break;
                }
            }
        }

        return dp[0];
    }
};




/*
    ------------
    --- IDEA ---
    ------------

    Classic Memoization approach.
    Can be considered a simpler one since it's only 1D.

*/

/* Time  Beats: 76.16% */
/* Space Beats: 74.07% */

/* Time  Complexity: O(N^3)   */
/* Space Complexity: O(N + M) */
class Solution_Top_Down___Memoization {
private:
    int memo[301];

public:
    bool wordBreak(string s, vector<string>& wordDict)
    {
        /* Memset */
        memset(memo, -1, sizeof(memo));
        unordered_set<string> uset(wordDict.begin(), wordDict.end());

        return solve(0, s, uset);
    }

private:
    bool solve(int start, string& s, unordered_set<string>& uset)
    {
        const int N = s.length();

        if (start == N)
            return true;

        if (memo[start] != -1)
            return memo[start];

        bool can_match_from_here = false;

        string substr;
        substr.reserve(N - start); // To prevent reallocations

        for (int i = start; i < N; i++)
        {
            substr += s[i];

            if (uset.count(substr)) // O(N) because of Hashing
            {
                can_match_from_here = solve(i + 1, s, uset);;

                if (can_match_from_here)
                    break;
            }
        }

        return memo[start] = can_match_from_here;
    }
};




/*
    ------------
    --- IDEA ---
    ------------

    TODO

*/

/* Time  Beats: 76.15% */
/* Space Beats: 64.39% */

/* Time  Complexity: O(N^3)                  */
/* Space Complexity: O(N + total_dict_chars) */
struct TrieNode {
    TrieNode* letter[26] = {nullptr};
    bool is_end;

    TrieNode()
        : is_end(false)
    {}

    ~TrieNode()
    {
        for (int i = 0; i < 26; i++)
            delete letter[i];
    }
};

class Trie {
private:
    TrieNode* root;

public:
    Trie()
    {
        root = new TrieNode();
    }

    ~Trie()
    {
        delete root;
    }

    void insert(const string& word)
    {
        TrieNode* node = root;

        for (const char& chr : word)
        {
            if ( ! node->letter[chr - 'a'])
                node->letter[chr - 'a'] = new TrieNode();

            node = node->letter[chr - 'a'];
        }

        node->is_end = true;
    }

    bool search(const string& word, bool find_prefix=false)
    {
        TrieNode* node = root;

        for (const char& chr : word)
        {
            if ( ! node->letter[chr - 'a'])
                return false;

            node = node->letter[chr - 'a'];
        }

        return find_prefix ? true : node->is_end;
    }

    bool starts_with(const string& prefix)
    {
        return search(prefix, true);
    }

    bool search_range(const string& word, int i, int j)
    {
        TrieNode* node = root;

        for (int idx = i; idx <= j; idx++)
        {
            char chr = word[idx];

            if ( ! node->letter[chr - 'a'])
                return false;

            node = node->letter[chr - 'a'];
        }

        return node->is_end;
    }
};

class Solution_Bottom_Up_Tabulation_using_Trie {
public:
    bool wordBreak(string s, vector<string>& wordDict)
    {
        const int N = s.size();
        const int D = wordDict.size();

        vector<bool> dp(N + 1, false);
        dp[N] = true;

        Trie trie;

        unsigned long longest_word_len = 0;
        for (const string& word : wordDict)
        {
            trie.insert(word);
            longest_word_len = max(longest_word_len, word.size());
        }

        for (int i = N-1; i >= 0; i--)
        {
            for (int j = i; j < N; j++)
            {
                int curr_substr_len = j - i + 1;

                if (curr_substr_len > longest_word_len)
                    continue;

                if (trie.search_range(s, i, j) && dp[j + 1])
                {
                    dp[i] = true;
                    break;
                }
            }
        }

        return dp[0];
    }
};
