/*
    ==============
    === MEDIUM ===
    ==============

    ==========================================
    2606) Find the Substring With Maximum Cost
    ==========================================

    ============
    Description:
    ============

    You are given a string s, a string chars of distinct characters and an
    integer array vals of the same length as chars.

    The cost of the substring is the sum of the values of each character in the
    substring. The cost of an empty string is considered 0.

    The value of the character is defined in the following way:

        + If the character is not in the string chars, then its value is its
          corresponding position (1-indexed) in the alphabet.

            + For example, the value of 'a' is 1, the value of 'b' is 2, and so
              on. The value of 'z' is 26.

        + Otherwise, assuming i is the index where the character occurs in the
          string chars, then its value is vals[i].

    Return the maximum cost among all substrings of the string s.

    ==============================================================================
    FUNCTION: int maximumCostSubstring(string s, string chars, vector<int>& vals);
    ==============================================================================

    ==========================================================================
    ================================ EXAMPLES ================================
    ==========================================================================

    --- Example 1 ---
    Input: s = "adaa", chars = "d", vals = [-1000]
    Output: 2
    Explanation: The value of the characters "a" and "d" is 1 and -1000 respectively.
    The substring with the maximum cost is "aa" and its cost is 1 + 1 = 2.
    It can be proven that 2 is the maximum cost.

    --- Example 2 ---
    Input: s = "abc", chars = "abc", vals = [-1,-1,-1]
    Output: 0
    Explanation: The value of the characters "a", "b" and "c" is -1, -1, and -1 respectively.
    The substring with the maximum cost is the empty substring "" and its cost is 0.
    It can be proven that 0 is the maximum cost.


    *** Constraints ***
    1 <= s.length <= 10^5
    s consist of lowercase English letters.
    1 <= chars.length <= 26
    chars consist of distinct lowercase English letters.
    vals.length == chars.length
    -1000 <= vals[i] <= 1000

*/

#include <string>
#include <unordered_map>
#include <vector>
using namespace std;

/*
    ------------
    --- IDEA ---
    ------------

    Classic Sliding-Window problem.

*/

/* Time  Beats: 100.00% */
/* Space Beats: 47.42% */

/* Time  Complexity: O(N) */
/* Space Complexity: O(N) */
class Solution {
public:
    int maximumCostSubstring(string s, string chars, vector<int>& vals)
    {
        const int N = s.length();
        const int M = chars.length();
        int result = 0;

        unordered_map<char,int> umap_chr_to_idx;
        for (int i = 0; i < M; i++)
            umap_chr_to_idx[chars[i]] = i;

        int L = 0;
        int R = 0;
        int curr_sum = 0;
        while (R < N)
        {
            char chr = s[R];

            if (umap_chr_to_idx.find(chr) == umap_chr_to_idx.end()) // Not found
            {
                curr_sum += (chr - 'a') + 1;
                result = max(result, curr_sum);
            }
            else
            {
                int idx = umap_chr_to_idx[chr]; 

                if (curr_sum + vals[idx] <= 0)
                {
                    curr_sum = 0;
                    L = R+1;
                }
                else
                {
                    curr_sum += vals[idx];
                    result = max(result, curr_sum);
                }
            }

            // Increment
            R++;
        }

        return result;
    }
};
