/*
    ==============
    === MEDIUM ===
    ==============

    ====================================================
    3325) Count Substrings With K-Frequency Characters I
    ====================================================

    ============
    Description:
    ============

    Given a string s and an integer k, return the total number of substrings
    of s where at least one character appears at least k times.

    ==================================================
    FUNCTION: int numberOfSubstrings(string s, int k);
    ==================================================

    ==========================================================================
    ================================ EXAMPLES ================================
    ==========================================================================

    --- Example 1 ---
    Input: s = "abacb", k = 2
    Output: 4
    Explanation:
    The valid substrings are:
        "aba" (character 'a' appears 2 times).
        "abac" (character 'a' appears 2 times).
        "abacb" (character 'a' appears 2 times).
        "bacb" (character 'b' appears 2 times).

    --- Example 2 ---
    Input: s = "abcde", k = 1
    Output: 15
    Explanation:
    All substrings are valid because every character appears at least once.


    *** Constraints ***
    1 <= s.length <= 3000
    1 <= k <= s.length
    s consists only of lowercase English letters.

*/

#include <string>
using namespace std;

/*
    ------------
    --- IDEA ---
    ------------

    Since we have to count all the subarrays where at least on letter is
    repeating 'k' times, we don't have to go through every subarray and check
    that, instead as soon as we add one letter to the "window" and it becomes
    true that now there is at least one letter repeating 'k' times, it's true
    that from that index until the end, we are CERTAIN all those subarrays have
    some letter repeating at least k times.

    Now the only question is--How much can we "srhink" this window, from the
    left, so that at least one letter repeats k times?

    For each window where that is true, we add additional:

        N - right_idx

    While we're shrinking we're decreasing the number of occurrences of that
    letter in our Map.

    However, we cannot use a basic HashMap. We cannot even use a Red-Black Tree
    Map, we must implement our own "FrequencyChecker" class.

    Why?

    Because we can add a new letter to it in O(1) and we can, also, in O(1)
    find out if there is at least one letter repeating 'k' times.

    However, once we're removing, it can happen that we're removing the only
    letter that fulfilled the requirement for "repeating k times" and therefore
    it is true that the same letter has a max_freq in entire window, therefore
    once we decrement it, we need to find a new max_freq. That takes us O(26),
    which is essentially O(1).

    It's O(1) because we're working ONLY with lowercase English alphabet.
    Also, Space Complexity is O(1) for the same reason. It's always 26 and that
    is a constant.

*/

/* Time  Beats: 100.00% */
/* Space Beats:  80.96% */

/* Time  Complexity: O(n * 26) --> O(n) */
/* Space Complexity: O(1)               */

class FrequencyChecker {
    int freqs[26] = {0};
    int max_freq = 0;

public:
    void add(char c)
    {
        freqs[c - 'a']++;
        max_freq = max(max_freq, freqs[c - 'a']);
    }

    void remove(char c)
    {
        freqs[c - 'a']--;

        if (freqs[c - 'a'] + 1 == max_freq)
        {
            max_freq = 0;

            // Find new maximum Freqnuency
            for (int f : freqs)
                max_freq = max(max_freq, 0);
        }
    }

    bool has_frequency_k(int k)
    {
        return max_freq >= k;
    }
};

class Solution {
public:
    int numberOfSubstrings(string s, int k)
    {
        const int N = s.length();
        int result = 0;

        FrequencyChecker FC;

        int left = 0;
        int right = 0;
        while (right < N)
        {
            FC.add(s[right]);

            if (FC.has_frequency_k(k))
            {
                while (left <= right && FC.has_frequency_k(k))
                {
                    result += N - right;

                    FC.remove(s[left]);
                    left++;
                }
            }

            // Increment
            right++;
        }

        return result;
    }
};
