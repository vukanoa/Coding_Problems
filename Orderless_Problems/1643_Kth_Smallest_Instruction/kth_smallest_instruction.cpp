/*
    ============
    === HARD ===
    ============

    ==============================
    1643) Kth Smallest Instruction
    ==============================

    ============
    Description:
    ============

    Bob is standing at cell (0, 0), and he wants to reach destination: (row,
    column). He can only travel right and down. You are going to help Bob by
    providing instructions for him to reach destination.

    The instructions are represented as a string, where each character is
    either:

        + 'H', meaning move horizontally (go right), or
        + 'V', meaning move vertically (go down).

    Multiple instructions will lead Bob to destination. For example, if
    destination is (2, 3), both "HHHVV" and "HVHVH" are valid instructions.

    However, Bob is very picky. Bob has a lucky number k, and he wants the kth
    lexicographically smallest instructions that will lead him to destination.
    k is 1-indexed.

    Given an integer array destination and an integer k, return the kth
    lexicographically smallest instructions that will take Bob to destination.

    ==================================================================
    FUNCTION: string kthSmallestPath(vector<int>& destination, int k);
    ==================================================================

    ==========================================================================
    ================================ EXAMPLES ================================
    ==========================================================================

    --- Example 1 ---
    Input: destination = [2,3], k = 1
    Output: "HHHVV"
    Explanation: All the instructions that reach (2, 3) in lexicographic order are as follows:
    ["HHHVV", "HHVHV", "HHVVH", "HVHHV", "HVHVH", "HVVHH", "VHHHV", "VHHVH", "VHVHH", "VVHHH"].

    --- Example 2 ---
    Input: destination = [2,3], k = 2
    Output: "HHVHV"

    --- Example 3 ---
    Input: destination = [2,3], k = 3
    Output: "HHVVH"


    *** Constraints ***
    destination.length == 2
    1 <= row, column <= 15
    1 <= k <= nCr(row + column, row), where nCr(a, b) denotes a choose b.

*/

#include <string>
#include <vector>
using namespace std;

/* Time  Beats: 100.00% */
/* Space Beats:  84.81% */

/* Time  Complexity: O((H + V)^2) */
/* Space Complexity: O(1)         */
class Solution {
private:
    int combination(int total, int choose)
    {
        long long result = 1;

        for (int divisor = 1, multiplier = total - choose + 1; divisor <= choose; divisor++, multiplier++)
        {
            result = result * multiplier / divisor;
        }

        return static_cast<int>(result);
    }

public:
    string kthSmallestPath(vector<int>& destination, int k)
    {
        int horizontal_moves = destination[1];
        int vertical_moves   = destination[0];
        int total_moves      = horizontal_moves + vertical_moves;

        string path;

        for (int step = 0; step < total_moves; step++)
        {
            if (horizontal_moves > 0)
            {
                // Number of paths if we choose 'H' at this position
                int paths_starting_with_H = combination(horizontal_moves - 1 + vertical_moves, vertical_moves);

                if (k <= paths_starting_with_H)
                {
                    path.push_back('H');
                    horizontal_moves--;
                }
                else
                {
                    k -= paths_starting_with_H;
                    path.push_back('V');
                    vertical_moves--;
                }
            }
            else
            {
                // No horizontal moves left, must take vertical
                path.push_back('V');
                vertical_moves--;
            }
        }

        return path;
    }
};
