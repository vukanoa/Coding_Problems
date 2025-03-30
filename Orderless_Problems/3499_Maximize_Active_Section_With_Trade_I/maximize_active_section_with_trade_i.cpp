/*
    ==============
    === MEDIUM ===
    ==============

    ==========================================
    3499) Maximize Active Section With Trade I
    ==========================================

    ============
    Description:
    ============

    You are given a binary string s of length n, where:

        + '1' represents an active section.
        + '0' represents an inactive section.

    You can perform at most one trade to maximize the number of active sections
    in s. In a trade, you:

        + Convert a contiguous block of '1's that is surrounded by '0's to all
          '0's.

        + Afterward, convert a contiguous block of '0's that is surrounded by
          '1's to all '1's.

    Return the maximum number of active sections in s after making the optimal
    trade.

    =====
    Note: Treat s as if it is augmented with a '1' at both ends, forming
          t = '1' + s + '1'. The augmented '1's do not contribute to the final
          count.
    =====

    ====================================================
    FUNCTION: int maxActiveSectionsAfterTrade(string s);
    ====================================================

    ==========================================================================
    ================================ EXAMPLES ================================
    ==========================================================================

    --- Example 1 ---
    Input: s = "01"
    Output: 1
    Explanation: Because there is no block of '1's surrounded by '0's, no valid
                 trade is possible. The maximum number of active sections is 1.

    --- Example 2 ---
    Input: s = "0100"
    Output: 4
    Explanation:
        String "0100" → Augmented to "101001".
        Choose "0100", convert "101001" → "100001" → "111111".
        The final string without augmentation is "1111". The maximum number of
        active sections is 4.

    --- Example 3 ---
    Input: s = "1000100"
    Output: 7
    Explanation:
        String "1000100" → Augmented to "110001001".
        Choose "000100", convert "110001001" → "110000001" → "111111111".
        The final string without augmentation is "1111111". The maximum number
        of active sections is 7.

    --- Example 4 ---
    Input: s = "01010"
    Output: 4
    Explanation:
        String "01010" → Augmented to "1010101".
        Choose "010", convert "1010101" → "1000101" → "1111101".
        The final string without augmentation is "11110". The maximum number of
        active sections is 4.


    *** Constraints ***
    1 <= n == s.length <= 10^5
    s[i] is either '0' or '1'

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

/* Time  Beats: 35.71% */
/* Space Beats: -% */

/* Time  Complexity: O(N) */
/* Space Complexity: O(N) */
class Solution {
public:
    int maxActiveSectionsAfterTrade(string s)
    {
        const int N = s.size();
        int result = 0;

        vector<int> prefix(N, 0);
        vector<int> suffix(N, 0);

        prefix[0]   = s[0]   == '1' ? 1 : 0;
        suffix[N-1] = s[N-1] == '1' ? 1 : 0;

        for (int i = 1; i < N; i++)
        {
            prefix[i] = prefix[i-1];

            if (s[i] == '1')
                prefix[i]++;

            suffix[N-1 - i] = suffix[N-1 - i + 1];

            if (s[N-1 - i] == '1')
                suffix[N-1 - i]++;
        }

        vector<pair<int,int>> zeroes;
        int i = 0;

        int zero_start = -1;
        int zero_end   = -1;
        for (int i = 0; i < N; i++)
        {
            if (s[i] == '0')
            {
                if (zero_start != -1)
                    continue;
                else
                    zero_start = i;
            }
            else
            {
                if (zero_start != -1)
                {
                    zeroes.push_back( {zero_start, i-1} );
                    zero_start = -1;
                }
                else
                    continue;
            }
        }

        if (zero_start != -1)
            zeroes.push_back( {zero_start, N-1} );


        if (zeroes.size() < 2)
            return prefix[N-1];

        int L = 0;
        int R = 1;

        while (R < zeroes.size())
        {
            int before = zeroes[L].first  >  0  ? prefix[zeroes[L].first  - 1] : 0;
            int after  = zeroes[R].second < N-1 ? suffix[zeroes[R].second + 1] : 0;

            result = max(result, before + (zeroes[R].second - zeroes[L].first + 1) + after);

            L++;
            R++;
        }

        return result;
    }
};
