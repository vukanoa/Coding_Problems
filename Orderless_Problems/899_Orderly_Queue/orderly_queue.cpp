/*
    ============
    === HARD ===
    ============

    ===========================
    899) Orderly Queue
    ===========================

    ============
    Description:
    ============

    You are given a string s and an integer k. You can choose one of the first
    k letters of s and append it at the end of the string.

    Return the lexicographically smallest string you could have after applying
    the mentioned step any number of moves.

    ===============================================
    FUNCTION: string orderlyQueue(string s, int k);
    ===============================================

    ==========================================================================
    ================================ EXAMPLES ================================
    ==========================================================================

    --- Example 1 ---
    Input: s = "cba", k = 1
    Output: "acb"
    Explanation: 
    In the first move, we move the 1st character 'c' to the end, obtaining the
    string "bac".
    In the second move, we move the 1st character 'b' to the end, obtaining the
    final result "acb".

    --- Example 2 ---
    Input: s = "baaca", k = 3
    Output: "aaabc"
    Explanation: 
    In the first move, we move the 1st character 'b' to the end, obtaining the
    string "aacab".
    In the second move, we move the 3rd character 'c' to the end, obtaining the
    final result "aaabc".


    *** Constraints ***
    1 <= k <= s.length <= 1000
    s consist of lowercase English letters.

*/

#include <algorithm>
#include <string>
using namespace std;

/*
    ------------
    --- IDEA ---
    ------------

    TODO

*/

/* Time  Beats: 61.66% */
/* Space Beats: 30.38% */

/* Time  Complexity: O(N * logN) */
/* Space Complexity: O(logN)     */ // Because of the C++'s Intro Sort
class Solution {
public:
    string orderlyQueue(string s, int k)
    {
        if (k > 1)
        {
            sort(s.begin(), s.end());
            return s;
        }

        const int N = s.length();

        string result = s;
        for (int i = 1; i < N; i++)
            result = min(result, s.substr(i) + s.substr(0, i));

        return result;
    }
};
