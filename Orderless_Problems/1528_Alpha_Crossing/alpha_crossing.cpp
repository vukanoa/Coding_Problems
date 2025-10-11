/*
    ============
    === EASY ===
    ============

    ===========================
    1528) Alpha Crossing
    ===========================

    ============
    Description:
    ============

    You are given a string s and an integer array indices of the same length.
    The string s will be shuffled such that the character at the ith position
    moves to indices[i] in the shuffled string.

    Return the shuffled string.

    ===============================================================
    FUNCTION: string restoreString(string s, vector<int>& indices);
    ===============================================================

    ==========================================================================
    ================================ EXAMPLES ================================
    ==========================================================================

    --- Example 1 ---
    Input: s = "codeleet", indices = [4,5,6,7,0,2,1,3]
    Output: "leetcode"
    Explanation: As shown, "codeleet" becomes "leetcode" after shuffling.

    --- Example 2 ---
    Input: s = "abc", indices = [0,1,2]
    Output: "abc"
    Explanation: After shuffling, each character remains in its position.


    *** Constraints ***
    s.length == indices.length == n
    1 <= n <= 100
    s consists of only lowercase English letters.
    0 <= indices[i] < n
    All values of indices are unique.

*/

#include <string>
#include <vector>
using namespace std;

/*
    ------------
    --- IDEA ---
    ------------

    Simulation problem.

*/

/* Time  Beats: 100.00% */
/* Space Beats: 75.81% */

/* Time  Complexity: O(N) */
/* Space Complexity: O(1) */
class Solution {
public:
    string restoreString(string s, vector<int>& indices)
    {
        const int N = s.length();
        string result;
        result.resize(N);

        for (int i = 0; i < N; i++)
        {
            result[indices[i]] = s[i];
        }

        return result;
    }
};
