/*
    ==============
    === MEDIUM ===
    ==============

    ================================================================
    3720) Lexicographically Smallest Permutation Greater Than Target
    ================================================================

    ============
    Description:
    ============

    You are given two strings s and target, both having length n, consisting of
    lowercase English letters.

    Return the lexicographically smallest permutation of s that is strictly
    greater than target. If no permutation of s is lexicographically strictly
    greater than target, return an empty string.

    A string a is lexicographically strictly greater than a string b (of the
    same length) if in the first position where a and b differ, string a has a
    letter that appears later in the alphabet than the corresponding letter in
    b.

    ================================================================
    FUNCTION: string lexGreaterPermutation(string s, string target);
    ================================================================

    ==========================================================================
    ================================ EXAMPLES ================================
    ==========================================================================

    --- Example 1 ---
    Input: s = "abc", target = "bba"
    Output: "bca"
    Explanation:
        The permutations of s (in lexicographical order) are "abc", "acb", "bac", "bca", "cab", and "cba".
        The lexicographically smallest permutation that is strictly greater than target is "bca".

    --- Example 2 ---
    Input: s = "leet", target = "code"
    Output: "eelt"
    Explanation:
        The permutations of s (in lexicographical order) are "eelt", "eetl", "elet", "elte", "etel", "etle", "leet", "lete", "ltee", "teel", "tele", and "tlee".
        The lexicographically smallest permutation that is strictly greater than target is "eelt".

    --- Example 3 ---
    Input: s = "baba", target = "bbaa"
    Output: ""
    Explanation:
        The permutations of s (in lexicographical order) are "aabb", "abab", "abba", "baab", "baba", and "bbaa".
        None of them is lexicographically strictly greater than target. Therefore, the answer is "".


    *** Constraints ***
    1 <= s.length == target.length <= 300
    s and target consist of only lowercase English letters.

*/

#include <algorithm>
#include <string>
#include <vector>
using namespace std;

/*
    ------------
    --- IDEA ---
    ------------

    TODO

*/

/* Time  Beats: 24.84% */
/* Space Beats: 19.11% */

/* Time  Complexity: O(N^2) */
/* Space Complexity: O(N)   */
class Solution {
public:
    string lexGreaterPermutation(string s, string target)
    {
        const int N = target.size();
        string result;

        int freq[26] = {};
        for (const char& chr : s)
            ++freq[chr - 'a'];

        for (int i = 0; i < N; i++)
        {
            int target_chr = target[i] - 'a';

            if (freq[target_chr] > 0)
            {
                --freq[target_chr];

                if (can_form_greater(freq, target, i + 1))
                {
                    result.push_back(target[i]);
                    continue;
                }

                ++freq[target_chr];
            }

            for (int j = target_chr + 1; j < 26; j++)
            {
                if (freq[j] > 0)
                {
                    --freq[j];

                    result.push_back(static_cast<char>(j + 'a'));

                    result += get_min_string(freq);
                    return result;
                }
            }

            return "";
        }

        return "";
    }

private:
    bool can_form_greater(int freq[26], const string& target, int start)
    {
        string maxStr = get_max_string(freq);
        string suffix = target.substr(start);
        return maxStr > suffix;
    }

    string get_max_string(int freq[26])
    {
        string result;
        for (int i = 25; i >= 0; i--)
            result.append(freq[i], static_cast<char>(i + 'a'));

        return result;
    }

    string get_min_string(int freq[26])
    {
        string result;
        for (int i = 0; i < 26; i++)
            result.append(freq[i], static_cast<char>(i + 'a'));

        return result;
    }
};




/*
    ------------
    --- IDEA ---
    ------------

    TODO

*/

/* Time  Beats: 57.32% */
/* Space Beats: 94.90% */

/* Time  Complexity: O(N) */
/* Space Complexity: O(N) */
class Solution_Reverse_Greedy {
public:
    string lexGreaterPermutation(string s, string target)
    {
        const int N = s.size();

        int freq[26] = {};
        for (int i = 0; i < N; i++)
        {
            ++freq[s[i]      - 'a'];
            --freq[target[i] - 'a'];
        }

        for (int i = N-1; i >= 0; i--)
        {
            int target_chr = target[i] - 'a';
            ++freq[target_chr];

            if (*min_element(begin(freq), end(freq)) < 0)
                continue;

            for (int j = target_chr + 1; j < 26; j++)
            {
                if (freq[j])
                {
                    --freq[j];

                    target[i] = static_cast<char>(j + 'a');
                    target.resize(i + 1);

                    return target + get_min_string(freq);
                }
            }
        }

        return "";
    }

    string get_min_string(int freq[26])
    {
        string result;

        for (int i = 0; i < 26; i++)
            result.append(freq[i], static_cast<char>(i + 'a'));

        return result;
    }
};
