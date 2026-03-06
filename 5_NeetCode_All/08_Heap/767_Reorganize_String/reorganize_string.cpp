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

#include <queue>
#include <string>
#include <unordered_map>
using namespace std;

/*
    ------------
    --- IDEA ---
    ------------

    TODO

*/

/* Time  Beats: 100.00% */
/* Space Beats:  53.38% */

/* Time  Complexity: O(N) */
/* Space Complexity: O(1) */ // 's' is passed as a copy, so we can change it
class Solution_Greedy {
public:
    string reorganizeString(string s)
    {
        int N = s.size();
        unordered_map<char, int> freq;

        for (const auto& chr : s)
            freq[chr]++;

        priority_queue<pair<int, char>> max_heap;

        for (const auto& [chr, frequency] : freq)
            max_heap.push( {frequency, chr} );

        // Make sure you understand this condition
        if (max_heap.top().first > (N + 1) / 2)
            return "";

        int idx = 0;
        while ( ! max_heap.empty())
        {
            auto [frequency, character] = max_heap.top();
            max_heap.pop();

            while (frequency-- > 0)
            {
                if (idx >= N)
                    idx = 1;

                s[idx] = character;
                idx += 2;
            }
        }

        return s;
    }
};
