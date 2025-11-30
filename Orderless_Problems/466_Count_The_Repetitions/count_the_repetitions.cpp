/*
    ============
    === HARD ===
    ============

    ===========================
    466) Count the Repetitions
    ===========================

    ============
    Description:
    ============

    We define str = [s, n] as the string str which consists of the string s
    concatenated n times.

        For example, str == ["abc", 3] =="abcabcabc".

    We define that string s1 can be obtained from string s2 if we can remove
    some characters from s2 such that it becomes s1.

        For example, s1 = "abc" can be obtained from s2 = "abdbec" based on our
        definition by removing the bolded underlined characters.

    You are given two strings s1 and s2 and two integers n1 and n2. You have
    the two strings str1 = [s1, n1] and str2 = [s2, n2].

    Return the maximum integer m such that str = [str2, m] can be obtained from
    str1.

    ======================================================================
    FUNCTION: int getMaxRepetitions(string s1, int n1, string s2, int n2);
    ======================================================================

    ==========================================================================
    ================================ EXAMPLES ================================
    ==========================================================================

    --- Example 1 ---
    Input: s1 = "acb", n1 = 4, s2 = "ab", n2 = 2
    Output: 2

    --- Example 2 ---
    Input: s1 = "acb", n1 = 1, s2 = "acb", n2 = 1
    Output: 1


    *** Constraints ***
    1 <= s1.length, s2.length <= 100
    s1 and s2 consist of lowercase English letters.
    1 <= n1, n2 <= 10^6

*/

#include <string>
#include <vector>
using namespace std;

/*
    ------------
    --- IDEA ---
    ------------

    TODO

*/

/* Time  Beats: 25.70% */
/* Space Beats:  8.10% */

/* Time  Complexity: O(|N| * n1) */
/* Space Complexity: O(n1)       */
class Solution {
public:
    int getMaxRepetitions(const string& s1, int n1, const string& s2, int n2)
    {
        const int N = s1.size();
        const int M = s2.size();

        vector<int> repeat_count(n1 + 1, 0);
        vector<int> next_index(n1 + 1, 0);

        int s2_index = 0;
        int s2_count = 0;

        for (int s1_iter = 1; s1_iter <= n1; ++s1_iter)
        {
            for (int char_idx = 0; char_idx < N; ++char_idx)
            {
                if (s1[char_idx] == s2[s2_index])
                {
                    s2_index++;
                    if (s2_index == M)
                    {
                        s2_index = 0;
                        s2_count++;
                    }
                }
            }

            repeat_count[s1_iter] = s2_count;
            next_index[s1_iter]   = s2_index;

            for (int start_iter = 0; start_iter < s1_iter; start_iter++)
            {
                if (next_index[start_iter] == s2_index)
                {
                    int prefix_count  = repeat_count[start_iter];
                    int pattern_count = (n1 - start_iter) / (s1_iter - start_iter) * (repeat_count[s1_iter]  - prefix_count);
                    int suffix_count = repeat_count[start_iter + (n1 - start_iter) % (s1_iter - start_iter)] - prefix_count;

                    return (prefix_count + pattern_count + suffix_count) / n2;
                }
            }
        }

        return repeat_count[n1] / n2;
    }
};
