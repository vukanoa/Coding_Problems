/*
    ==============
    === MEDIUM ===
    ==============

    ====================================================
    3998) Transform Binary String Using Subsequence Sort
    ====================================================

    ============
    Description:
    ============

    You are given a binary string s.

    You are also given an array of strings strs, where each strs[i] has the
    same length as s and consists of characters '0', '1', and '?'. Each '?' can
    be replaced by either '0' or '1'.

    You may perform the following operation any number of times (including zero):

        + Choose any subsequence sub of s.

        + Sort sub in non-decreasing order.

        + Replace the chosen subsequence in s with the sorted sub, keeping all
          other characters unchanged.

    Return a boolean array ans, where ans[i] is true if it's possible to
    replace all '?' in strs[i] with '0' or '1' and transform s into the
    resulting string using the allowed operation above, otherwise return false.

    ====================================================================
    FUNCTION: vector<bool> transformStr(string s, vector<string>& strs);
    ====================================================================

    ==========================================================================
    ================================ EXAMPLES ================================
    ==========================================================================

    --- Example 1 ---
    Input: s = "101", strs = ["1?1","0?1","0?0"]
    Output: [true,true,false]
    Explanation:

    | i | strs[i] | Replacement | Result strs[i] | Operation(s)             | Result |
    |---+---------+-------------+----------------+--------------------------+--------|
    | 0 | "1?1"   | ? -> 0      | "101"          | Matches s.               | true   |
    | 1 | "0?1"   | ? -> 1      | "011"          | Select subsequence       | true   |
    |   |         |             |                | at indices [0..2] of s   |        |
    |   |         |             |                | -> "101". Sort "101"     |        |
    |   |         |             |                | to get "011" = strs[i].  |        |
    | 2 | "0?0"   | ? -> 0 or 1 | "000" or "010"  | Not feasible.           | false  |

    Thus, ans = [true, true, false].



    --- Example 2 ---
    Input: s = "1100", strs = ["0011","11?1","1?1?"]
    Output: [true,false,true]
    Explanation:

    | i | strs[i] | Replacement        | Result strs[i] | Operation(s)                  | Result |
    |---+---------+--------------------+----------------+-------------------------------+--------|
    | 0 | "0011"  | -                  | "0011"         | Select subsequence at         | true   |
    |   |         |                    |                | indices [0..3] of s -> "1100".|        |
    |   |         |                    |                | Sort "1100" -> "0011"         |        |
    |   |         |                    |                | = strs[i].                    |        |
    | 1 | "11?1"  | ? -> 0             | "1101"         | Not feasible.                 | false  |
    | 2 | "1?1?"  | First ? -> 0       | "1010"         | Select subsequence at         | true   |
    |   |         | Second ? -> 0      |                | indices [1, 2] of s -> "10".  |        |
    |   |         |                    |                | Sort "10" -> "01", so         |        |
    |   |         |                    |                | s = "1010".                   |        |
    Thus, ans = [true, false, true].



    --- Example 3 ---
    Input: s = "1010", strs = ["0011"]
    Output: [true]
    Explanation:

    | i | strs[i] | Replacement | Result strs[i] | Operation(s)                  | Result |
    |---+---------+-------------+----------------+-------------------------------+--------|
    | 0 | "0011"  | -           | "0011"         | Select subsequence at         | true   |
    |   |         |             |                | indices [0,2,3] of s -> "110".|        |
    |   |         |             |                | Sort "110" -> "011", so       |        |
    |   |         |             |                | s = "0011" = strs[i].         |        |

    Thus, ans = [true].


    *** Constraints ***
    1 <= n == s.length <= 2000
    s[i] is either '0' or '1'.
    1 <= strs.length <= 2000
    strs[i].length == n
    strs[i] is either '0', '1', or '?'

*/

#include <string>
#include <unordered_map>
#include <vector>
using namespace std;

/*
    ------------
    --- IDEA ---
    ------------

    TODO

*/

/* Time  Beats:  9.72% */
/* Space Beats: 64.92% */

/* Time  Complexity: O(N * M) */
/* Space Complexity: O(M)     */
class Solution {
public:
    vector<bool> transformStr(string s, vector<string>& strs)
    {
        const int N = s.size();
        const int M = strs.size();
        vector<bool> ans(M, false);

        unordered_map<char,int> orig_freq;
        for (const char& chr : s)
            ++orig_freq[chr];

        for (int i = 0; i < M; i++)
        {
            unordered_map<char,int> freq;


            for (auto& chr : strs[i])
                ++freq[chr];
          
            if (freq['0'] > orig_freq['0'] || freq['1'] > orig_freq['1'])
            {
                ans[i] = false;
            }
            else
            {
                int diff_zeroes = orig_freq['0'] - freq['0'];
                int diff_ones   = orig_freq['1'] - freq['1'];
                
                for (int j = 0; j < N; j++)
                {
                    if (strs[i][j] != '?')
                        continue;

                    if (diff_zeroes > 0)
                    {
                        strs[i][j] = '0';
                        --diff_zeroes;
                    }
                    else
                    {
                        strs[i][j] = '1';
                        --diff_ones;
                    }
                }
                
                int left_ones = 0;
                bool can_transform = true;
                for (int j = 0; j < N; j++)
                {
                    if (s[j]       == '1') ++left_ones;
                    if (strs[i][j] == '1') --left_ones;
                    
                    if (left_ones < 0)
                    {
                        can_transform = false;
                        break;
                    }
                }

                ans[i] = can_transform;
            }
        }

        return ans;
    }
};
