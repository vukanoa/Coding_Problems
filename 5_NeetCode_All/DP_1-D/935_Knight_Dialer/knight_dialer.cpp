#include <iostream>
#include <vector>

/*
    ==============
    === MEDIUM ===
    ==============

    ===========================
    935) Knight Dialer
    ===========================

    ============
    Description:
    ============

    The chess knight has a unique movement, it may move two squares vertically
    and one square horizontally, or two squares horizontally and one square
    vertically (with both forming the shape of an L). The possible movements of
    chess knight are shown in this diagram:

    A chess knight can move as indicated in the chess diagram below:

        *** Checkout the picture at LeetCode ***

    We have a chess knight and a phone pad as shown below, the knight can only
    stand on a numeric cell (i.e. blue cell).

        *** Checkout this picture at LeetCode as well ***

    Given an integer n, return how many distinct phone numbers of length n we
    can dial.

    You are allowed to place the knight on any numeric cell initially and then
    you should perform n - 1 jumps to dial a number of length n. All jumps
    should be valid knight jumps.

    As the answer may be very large, return the answer modulo 109 + 7.

    ==================================
    FUNCTION: int knightDialer(int n);
    ==================================

    ==========================================================================
    ================================ EXAMPLES ================================
    ==========================================================================

    --- Example 1 ---
    Input: n = 1
    Output: 10
    Explanation: We need to dial a number of length 1, so placing the knight
                 over any numeric cell of the 10 cells is sufficient.


    --- Example 2 ---
    Input: n = 2
    Output: 20
    Explanation: All the valid number we can dial are [04, 06, 16, 18, 27, 29,
                 34, 38, 40, 43, 49, 60, 61, 67, 72, 76, 81, 83, 92, 94]


    --- Example 3 ---
    Input: n = 3131
    Output: 136006598
    Explanation: Please take care of the mod.


    *** Constraints ***
    1 <= n <= 5000

*/

/*
    ------------
    --- IDEA ---
    ------------

    TODO

*/

/* Time  Beats: 93.28% */
/* Space Beats: 92.07% */

/* Time  Complexity: O(n) */
/* Space Complexity: O(1) */
class Solution {
public:
    // time/space: O(n)/O(1)
    int knightDialer(int n) {
        // build the graph
        const vector<vector<int>> graph = {
            {4, 6},     // 0
            {6, 8},     // 1
            {7, 9},     // 2
            {4, 8},     // 3
            {0, 3, 9},  // 4
            {},         // 5
            {0, 1, 7},  // 6
            {2, 6},     // 7
            {1, 3},     // 8
            {2, 4},     // 9
        };

        vector<int> dp0(10, 1);
        vector<int> dp1(10);

        for (int i = 2; i <= n; i++)
        {
            fill(dp1.begin(), dp1.end(), 0);

            for (int curr = 0; curr <= 9; curr++)
            {
                for (auto& next : graph[curr])
                    dp1[next] = (dp1[next] + dp0[curr]) % int(1e9 + 7);
            }

            swap(dp0, dp1);
        }

        // Summarize
        int result = 0;
        for (int cell = 0; cell <= 9; cell++)
            result = (result + dp0[cell]) % int(1e9 + 7);

        return result;
    }
};
