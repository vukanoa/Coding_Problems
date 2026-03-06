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

#include <algorithm>
#include <numeric>
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
/* Space Beats:  89.92% */

/* Time  Complexity: O(N) */
/* Space Complexity: O(1) */ // "result" is not EXTRA space
class Solutionqr {
public:
    string reorganizeString(string s)
    {
        const int N = s.size();
        string result;
        result.reserve(N);

        int freq[26] = {0}; // On the STACK
        for (const char& chr : s) // O(N)
            freq[chr - 'a']++;

        int max_freq = *max_element(begin(freq), end(freq));  // O(N)
        int sum      = accumulate(begin(freq), end(freq), 0); // O(N);

        int sum_without_max_freq = sum - max_freq;

        if (max_freq - sum_without_max_freq > 1)
            return "";

        // O(26 * log26) --> O(1)
        priority_queue<pair<int,char>> max_heap; // {freq, char}
        for (int i = 0; i < 26; i++) // O(26) --> O(1)
        {
            if (freq[i] > 0)
                max_heap.push( {freq[i], i + 'a'} ); // O(log26) -> O(1)
        }

        // O(N) (entire block)
        while ( ! max_heap.empty())
        {
            auto [frequency_one, chr_one] = max_heap.top();
            max_heap.pop();

            result += chr_one;
            frequency_one--;

            if ( ! max_heap.empty())
            {
                auto [frequency_two, chr_two] = max_heap.top();
                max_heap.pop();

                result += chr_two;
                frequency_two--;

                if (frequency_two > 0)
                    max_heap.push ( {frequency_two, chr_two} );
            }

            if (frequency_one > 0)
                max_heap.push ( {frequency_one, chr_one} );
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
