/*
    ============
    === EASY ===
    ============

    ===========================
    942) DI String Match
    ===========================

    ============
    Description:
    ============

    A permutation perm of n + 1 integers of all the integers in the range
    [0, n] can be represented as a string s of length n where:

        s[i] == 'I' if perm[i] < perm[i + 1], and
        s[i] == 'D' if perm[i] > perm[i + 1].

    Given a string s, reconstruct the permutation perm and return it. If there
    are multiple valid permutations perm, return any of them.

    ==============================================
    FUNCTION: vector<int> diStringMatch(string s);
    ==============================================

    ==========================================================================
    ================================ EXAMPLES ================================
    ==========================================================================

    --- Example 1 ---
    Input: s = "IDID"
    Output: [0,4,1,3,2]

    --- Example 2 ---
    Input: s = "III"
    Output: [0,1,2,3]

    --- Example 3 ---
    Input: s = "DDI"
    Output: [3,2,0,1]

    *** Constraints ***
    1 <= s.length <= 10^5
    s[i] is either 'I' or 'D'.

*/

#include <string>
#include <vector>
using namespace std;

/*
    ------------
    --- IDEA ---
    ------------

    Literally just code it up.

*/

/* Time  Beats: 28.85% */
/* Space Beats: 55.09% */

/* Time  Complexity: O(N) */
/* Space Complexity: O(1) */ // "result" is not considered "extra" space
class Solution {
public:
    vector<int> diStringMatch(string s)
    {
        const int N = s.length();
        vector<int> result;

        int L = 0;
        int R = N;

        for (const char& chr : s)
        {
            if (chr == 'I')
            {
                result.push_back(L);
                L++;
            }
            else
            {
                result.push_back(R);
                R--;
            }
        }
        result.push_back(L); // or R, it's the same

        return result;
    }
};
