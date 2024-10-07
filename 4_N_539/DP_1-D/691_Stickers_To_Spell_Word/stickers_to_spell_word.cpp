#include <iostream>
#include <vector>
#include <queue>
#include <unordered_set>

/*
    ============
    === HARD ===
    ============

    ===========================
    691) Stickers to Spell Word
    ===========================

    ============
    Description:
    ============

    We are given n different types of stickers. Each sticker has a lowercase
    English word on it.

    You would like to spell out the given string target by cutting individual
    letters from your collection of stickers and rearranging them. You can use
    each sticker more than once if you want, and you have infinite quantities
    of each sticker.

    Return the minimum number of stickers that you need to spell out target. If
    the task is impossible, return -1.

    =====
    Note: In all test cases, all words were chosen randomly from the 1000 most
          common US English words, and target was chosen as a concatenation of
          two random words.
    =====

    ===================================================================
    FUNCTION: int minStickers(vector<string>& stickers, string target);
    ===================================================================

    ==========================================================================
    ================================ EXAMPLES ================================
    ==========================================================================

    --- Example 1 ---
    Input: stickers = ["with","example","science"], target = "thehat"
    Output: 3
    Explanation:
    We can use 2 "with" stickers, and 1 "example" sticker.
    After cutting and rearrange the letters of those stickers, we can form the
    target "thehat".  Also, this is the minimum number of stickers necessary to
    form the target string.


    --- Example 2 ---
    Input: stickers = ["notice","possible"], target = "basicbasic"
    Output: -1
    Explanation:
    We cannot form the target "basicbasic" from cutting letters from the given
    stickers.


    *** Constraints ***
    n == stickers.length
    1 <= n <= 50
    1 <= stickers[i].length <= 10
    1 <= target.length <= 15
    stickers[i] and target consist of lowercase English letters.

*/

/*
    ------------
    --- IDEA ---
    ------------

    TODO

*/

/* Time  Beats: 78.21% */
/* Space Beats: 45.72% */

/* Time  Complexity: O(2^m * n * m)  */ // m - target.lenght()
/* Space Complexity: O(2^m + n * 26) */
class Solution {
public:
    int minStickers(vector<string>& stickers, string& target)
    {
        const int n = stickers.size();

        unordered_set<string> visited;

        // Reorganize stickers argument in frequencies
        vector<vector<int>> s_frequencies(n, vector<int>(26, 0));
        for (int i = 0; i < n; i++)
        {
            for (auto& c : stickers[i])
                s_frequencies[i][c - 'a']++;
        }
 
        // Reorganize target argument in frequency
        vector<int> t_frequency(26, 0);
        for (auto& c : target)
            t_frequency[c - 'a']++;

        queue<vector<int>> queue;
        queue.push(t_frequency);

        for (int res = 0; queue.size(); res++)
        {
            for (int k = queue.size(); k > 0; k--)
            {
                auto t_freq = queue.front();
                queue.pop();

                // Reconstruct string based on frequency
                string t_str;
                for (int i = 0; i < 26; i++)
                {
                    if (t_freq[i] > 0)
                        t_str += string(t_freq[i], i);
                }

                if (t_str == "")
                    return res;

                if (visited.count(t_str))
                    continue;

                visited.insert(t_str);

                char seeking = t_str[0];
                for (auto& v : s_frequencies)
                {
                    // Optimize by checking for first letter
                    if (v[seeking] > 0)
                    {
                        queue.push(t_freq); // Push first to copy t_freq

                        for (int i = 0; i < 26; ++i)
                            queue.back()[i] -= v[i];
                    }
                }
            }
        }

        return -1;
    }
};
