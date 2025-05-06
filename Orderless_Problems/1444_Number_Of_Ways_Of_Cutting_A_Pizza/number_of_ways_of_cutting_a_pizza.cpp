/*
    ============
    === HARD ===
    ============

    =======================================
    1444) Number of Ways of Cutting a Pizza
    =======================================

    ============
    Description:
    ============

    Given a rectangular pizza represented as a rows x cols matrix containing
    the following characters: 'A' (an apple) and '.' (empty cell) and given the
    integer k. You have to cut the pizza into k pieces using k-1 cuts.

    For each cut you choose the direction: vertical or horizontal, then you
    choose a cut position at the cell boundary and cut the pizza into two
    pieces. If you cut the pizza vertically, give the left part of the pizza to
    a person. If you cut the pizza horizontally, give the upper part of the
    pizza to a person. Give the last piece of pizza to the last person.

    Return the number of ways of cutting the pizza such that each piece
    contains at least one apple. Since the answer can be a huge number, return
    this modulo 10^9 + 7.

    =================================================
    FUNCTION: int ways(vector<string>& pizza, int k);
    =================================================

    ==========================================================================
    ================================ EXAMPLES ================================
    ==========================================================================

    --- Example 1 ---
    Input: pizza = ["A..","AAA","..."], k = 3
    Output: 3
    Explanation: The figure above shows the three ways to cut the pizza. Note
                 that pieces must contain at least one apple.

    --- Example 2 ---
    Input: pizza = ["A..","AA.","..."], k = 3
    Output: 1

    --- Example 3 ---
    Input: pizza = ["A..","A..","..."], k = 1
    Output: 1


    *** Constraints ***
    1 <= rows, cols <= 50
    rows == pizza.length
    cols == pizza[i].length
    1 <= k <= 10
    pizza consists of characters 'A' and '.' only.

*/

#include <cstring>
#include <string>
#include <vector>
using namespace std;

/*
    ------------
    --- IDEA ---
    ------------

    In such DP problems one first needs to consider how can we find the state
    variables that uniquely describe the state of the problem. What can these
    state variables in this problem likely be?

    Let's consider a ROWS * COLS matrix. If we were to make any horizontal or
    vertical cut, we would be left with a matrix that has lesser rows (or)
    columns. That fact is established. We also are now only concerned only with
    this smaller rectangle.

    Also as per the problem description, it's clear that this smaller
    rectangle's bottom right corner will coincide with the bigger matrix's
    bottom right corner.

    So this gives us a clue that maybe the top left coordinate of the remaining
    rectangle must be helpful in deciding the state. One can however arrive at
    this top left coordinate as a state after variable cuts.

    So combining the top left coordinate along with the number of cuts k made
    so far, we can uniquely describe a state.

    Now while making a cut, we need to take care of another important fact as
    well--the new partitions made should contain an apple!

    So we need to ensure that any cuts that we make abide by this rule. We can
    perform this check easily if we precompute the number of apples in a
    sub-matrix whose top left coordinate can be [i][j] with 0<=i<n && 0<=j<m.

    Now we can perform either a horizontal cut or a vertical cut. We can cut at
    any horizontal line below the current top left box and and any vertical
    line to the right of the top-left box.


    Store the subproblem results in order to make calculations faster. Here's
    the code.

*/

/* Time  Beats: 90.15% */
/* Space Beats: 98.91% */

/* Time  Complexity: O(K * ROWS * COLS * (ROWS + COLS)) */
/* Space Complexity: O(K * ROWS * COLS)                 */
class Solution {
    // For storing cummulative sum till bottom right
    int apples_in_submatrix[51][51];
    int memo[51][51][11];

    const int MOD = 1e9 + 7;

public:
    int ways(vector<string>& pizza, int K)
    {
        const int ROWS = pizza.size();
        const int COLS = pizza[0].size();

        memset(apples_in_submatrix, 0, sizeof(apples_in_submatrix));
        memset(memo, -1, sizeof(memo));

        // Fill cumulative_sum
        for (int row = ROWS-1; row >= 0; row--)
        {
            for (int col = COLS-1; col >= 0; col--)
            {
                apples_in_submatrix[row][col] = apples_in_submatrix[row+1][col] + apples_in_submatrix[row][col+1] - apples_in_submatrix[row+1][col+1];
                apples_in_submatrix[row][col] += pizza[row][col] == 'A' ? 1 : 0;

                // Base case
                if (apples_in_submatrix[row][col] > 0)
                    memo[row][col][K-1] = 1;
            }
        }

        // If there are no apples whatsoever, then we can't cut it even once
        if (apples_in_submatrix[0][0] == 0)
            return 0;

        return solve(0, 0, 0, ROWS, COLS, K);

    }

    int solve(int curr_row, int curr_col, int used_cuts, const int& ROWS, const int& COLS, int& K)
    {
        if (used_cuts == K-1)
            return 1;

        if (memo[curr_row][curr_col][used_cuts] != -1)
            return memo[curr_row][curr_col][used_cuts];

        // Check if there are 0 apples in this submatrix
        if (apples_in_submatrix[curr_row][curr_col] == 0)
            return 0;

        int ways_to_cut = 0;

        // Horizontal cuts
        for (int row = curr_row+1; row < ROWS; row++)
        {
            // Check if cut is valid
            if (apples_in_submatrix[curr_row][curr_col] - apples_in_submatrix[row][curr_col])
            {
                ways_to_cut += solve(row, curr_col, used_cuts+1, ROWS, COLS, used_cuts);
                ways_to_cut %= MOD;
            }
        }

        // Vertical cuts
        for (int col = curr_col+1; col < COLS; col++)
        {
            // Check if cut is valid
            if (apples_in_submatrix[curr_row][curr_col] - apples_in_submatrix[curr_row][col])
            {
                ways_to_cut += solve(curr_row, col, used_cuts+1, ROWS, COLS, used_cuts);
                ways_to_cut %= MOD;
            }
        }

        return memo[curr_row][curr_col][used_cuts] = ways_to_cut;
    }
};
