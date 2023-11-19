#include <iostream>
#include <vector>
#include <queue>
#include <cstring>
#include <sstream>
#include <cmath>

/*
    ==============
    === MEDIUM ===
    ==============

    ===========================
    767) Reorganize String
    ===========================

    ============
    Description:
    ============

    Given a string s, rearrange the characters of s so that any two adjacent
    characters are not the same.

    Return any possible rearrangement of s or return "" if not possible.

    ============================================
    FUNCTION: string reorganizeString(string s);
    ============================================

    ==========================================================================
    ================================ EXAMPLES ================================
    ==========================================================================

    --- Example 1 ---
    Input: s = "aab"
    Output: "aba"

    --- Example 2 ---
    Input: s = "aaab"
    Output: ""


    *** Constraints ***
    1 <= s.length <= 500
    s consists of lowercase English letters.

*/

/* Time  Beats: 100.00% */
/* Space Beats: 45.90% */

/* Time  Complexity: O(log n) */
/* Space Complexity: O(1) */
class Solution {
public:
    std::string reorganizeString(std::string s)
    {
        int max_possible_repeat = (int) std::ceil((double) 1.0 * s.size() / 2);
        int letters[26];

        memset(letters, 0, sizeof(letters));

        for (char& c : s)
            letters[c - 'a']++;

        std::priority_queue<std::pair<int, char>> max_heap;
        for (int i = 0; i < 26; i++)
        {
            if (letters[i] > max_possible_repeat)
                return "";

            if (letters[i] > 0)
                max_heap.push(std::make_pair(letters[i], i + 'a'));
        }

        std::ostringstream out;

        while (!max_heap.empty())
        {
            std::pair<int, char> first = max_heap.top();
            max_heap.pop();

            if (max_heap.empty() && first.first > 1)
                return "";

            if (!max_heap.empty())
            {
                std::pair<int, char> second = max_heap.top();
                max_heap.pop();

                out << first.second << second.second;
                first.first--;
                second.first--;

                if (first.first > 0)
                    max_heap.push(first);

                if (second.first > 0)
                    max_heap.push(second);
            }
            else
            {
                out << first.second;
                first.first--;

                if (first.first > 0)
                    max_heap.push(first);
            }
        }

        std::string result_str = out.str();
        for (int i = 1; i < result_str.length(); i++)
        {
            if (result_str[i-1] == result_str[i])
                return "";
        }

        return result_str;
    }
};