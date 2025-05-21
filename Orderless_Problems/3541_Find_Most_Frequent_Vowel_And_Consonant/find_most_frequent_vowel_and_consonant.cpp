/*
    ============
    === EASY ===
    ============

    ============================================
    3541) Find Most Frequent Vowel and Consonant
    ============================================

    ============
    Description:
    ============

    You are given a string s consisting of lowercase English letters
    ('a' to 'z').

    Your task is to:

        + Find the vowel (one of 'a', 'e', 'i', 'o', or 'u') with the maximum
          frequency.

        + Find the consonant (all other letters excluding vowels) with the
          maximum frequency.

    Return the sum of the two frequencies.

    Note: If multiple vowels or consonants have the same maximum frequency, you
    may choose any one of them. If there are no vowels or no consonants in the
    string, consider their frequency as 0.

    The frequency of a letter x is the number of times it occurs in the string.

    ===================================
    FUNCTION: int maxFreqSum(string s);
    ===================================

    ==========================================================================
    ================================ EXAMPLES ================================
    ==========================================================================

    --- Example 1 ---
    Input: s = "successes"
    Output: 6
    Explanation:
        The vowels are: 'u' (frequency 1), 'e' (frequency 2). The maximum
        frequency is 2.
        The consonants are: 's' (frequency 4), 'c' (frequency 2). The maximum
        frequency is 4.
        The output is 2 + 4 = 6.

    --- Example 2 ---
    Input: s = "aeiaeia"
    Output: 3
    Explanation:
        The vowels are: 'a' (frequency 3), 'e' ( frequency 2), 'i' (frequency 2)
        The maximum frequency is 3. There are no consonants in s. Hence,
        maximum consonant frequency = 0.
        The output is 3 + 0 = 3.


    *** Constraints ***
    1 <= s.length <= 100
    s consists of lowercase English letters only.

*/

#include <string>
#include <unordered_set>
#include <vector>
using namespace std;

/*
    ------------
    --- IDEA ---
    ------------

    Self-explanatory.

*/

/* Time  Beats: 18.31% */
/* Space Beats: 31.62% */

/* Time  Complexity: O(N) */
/* Space Complexity: O(1) */
class Solution {
public:
    int maxFreqSum(string s)
    {
        const int N = s.size();
        int result = 0;

        vector<int> counter(26, 0);
        for (const char& chr : s)
            counter[chr - 'a']++;

        int vow = 0;
        int con = 0;

        unordered_set<char> vowels = {'a', 'e', 'i', 'o', 'u'};
        for (int i = 0; i < 26; i++)
        {
            if (vowels.find(char(i + 'a')) != vowels.end())
            {
                vow = max(vow, counter[i]);
            }
            else
            {
                con = max(con, counter[i]);
            }
        }

        return vow + con;
    }
};
