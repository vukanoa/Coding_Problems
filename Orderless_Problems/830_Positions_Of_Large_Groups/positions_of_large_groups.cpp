/*
    ============
    === EASY ===
    ============

    ==============================
    830) Positions of Large Groups
    ==============================

    ============
    Description:
    ============

    In a string s of lowercase letters, these letters form consecutive groups
    of the same character.

    For example, a string like s = "abbxxxxzyy" has the groups:

        "a", "bb", "xxxx", "z", and "yy".

    A group is identified by an interval [start, end], where start and end
    denote the start and end indices (inclusive) of the group. In the above
    example, "xxxx" has the interval [3,6].

    A group is considered large if it has 3 or more characters.

    Return the intervals of every large group sorted in increasing order by
    start index.

    ============================================================
    FUNCTION: vector<vector<int>> largeGroupPositions(string s);
    ============================================================

    ==========================================================================
    ================================ EXAMPLES ================================
    ==========================================================================

    --- Example 1 ---
    Input: s = "abbxxxxzzy"
    Output: [[3,6]]
    Explanation: "xxxx" is the only large group with start index 3 and end index 6.

    --- Example 2 ---
    Input: s = "abc"
    Output: []
    Explanation: We have groups "a", "b", and "c", none of which are large groups.

    --- Example 3 ---
    Input: s = "abcdddeeeeaabbbcd"
    Output: [[3,5],[6,9],[12,14]]
    Explanation: The large groups are "ddd", "eeee", and "bbb".


    *** Constraints ***
    1 <= s.length <= 1000
    s contains lowercase English letters only.

*/

#include <string>
#include <vector>
using namespace std;

/*
    ------------
    --- IDEA ---
    ------------

    Self-explanatory.

*/

/* Time  Beats: 100.00% */
/* Space Beats:  92.08% */

/* Time  Complexity: O(N) */
/* Space Complexity: O(1) */
class Solution {
public:
    vector<vector<int>> largeGroupPositions(string s)
    {
        const int N = s.length();
        vector<vector<int>> result;

        s += "."; // So tha we don't have to cover the special case at the end

        int start = 0;
        int end   = 0;

        while (end < N+1)
        {
            if (s[start] != s[end])
            {
                int len = end - start; // because "end" is one AFTER the group

                if (len >= 3)
                    result.push_back( {start, end-1});

                start = end;
            }

            // Increment
            end++;
        }

        return result;
    }
};
