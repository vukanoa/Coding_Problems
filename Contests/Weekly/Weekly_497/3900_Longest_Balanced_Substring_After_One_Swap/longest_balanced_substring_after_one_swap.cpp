/*
    ==============
    === MEDIUM ===
    ==============

    ===============================================
    3900) Longest Balanced Substring After One Swap
    ===============================================

    ============
    Description:
    ============

    You are given a binary string s consisting only of characters '0' and '1'.

    A string is balanced if it contains an equal number of '0's and '1's.

    You can perform at most one swap between any two characters in s. Then, you
    select a balanced from s.

    Return an integer representing the maximum length of the balanced substring
    you can select.

    ========================================
    FUNCTION: int longestBalanced(string s);
    ========================================

    ==========================================================================
    ================================ EXAMPLES ================================
    ==========================================================================

    --- Example 1 ---
    Input: s = "100001"
    Output: 4
    Explanation:
        Swap "100001". The string becomes "101000". Select the substring
        "101000", which is balanced because it has two '0's and two '1's.

    --- Example 2 ---
    Input: s = "111"
    Output: 0
    Explanation:
        Choose not to perform any swaps.
        Select the empty substring, which is balanced because it has zero '0's
        and zero '1's.


    *** Constraints ***
    1 <= s.length <= 10^5
    s consists only of the characters '0' and '1'.

*/

#include <algorithm>
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

/* Time  Beats: 77.04% */
/* Space Beats: 67.29% */

/* Time  Complexity: O(N) */
/* Space Complexity: O(N) */
class Solution {
public:
    int longestBalanced(string s)
    {
        const int N = s.size();

        int total_0 = count(s.begin(), s.end(), '0');
        int total_1 = N - total_0;

        unordered_map<int, vector<int>> earliest;
        earliest[0] = {-1};

        int sum = 0;
        int result = 0;

        for (int i = 0; i < N; i++)
        {
            sum += (s[i] == '1' ? 1 : -1);

            for (const int& target : {sum, sum-2, sum+2})
            {
                if ( ! earliest.count(target))
                    continue;

                for (const int& L : earliest[target])
                {
                    int len  = i - L;
                    int diff = sum - target;

                    int ones  = (len + diff) / 2;
                    int zeros = len - ones;

                    if (diff ==  0                     ||
                       (diff ==  2 && total_0 > zeros) ||
                       (diff == -2 && total_1 > ones))
                    {
                        result = max(result, len);
                        break;
                    }
                }
            }

            if (earliest[sum].size() < 2)
                earliest[sum].push_back(i);
        }

        return result;
    }
};
