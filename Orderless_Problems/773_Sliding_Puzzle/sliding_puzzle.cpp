#include <iostream>
#include <vector>
#include <string>
#include <queue>
#include <unordered_set>
#include <algorithm>

/*
    ============
    === HARD ===
    ============

    ===========================
    774) Sliding Puzzle
    ===========================

    ============
    Description:
    ============

    On an 2 x 3 board, there are five tiles labeled from 1 to 5, and an empty
    square represented by 0. A move consists of choosing 0 and a
    4-directionally adjacent number and swapping it.

    The state of the board is solved if and only if the board is
    [[1,2,3],[4,5,0]].

    Given the puzzle board board, return the least number of moves required so
    that the state of the board is solved. If it is impossible for the state of
    the board to be solved, return -1.

    =======================================================
    FUNCTION int slidingPuzzle(vector<vector<int>>& board);
    =======================================================

    ==========================================================================
    ================================ EXAMPLES ================================
    ==========================================================================

    --- Example 1 ---
    +-----+-----+-----+
    |     |     |     |
    +-----+-----+-----+
    |     |     |     |
    +-----+-----+-----+
    Input: board = [[1,2,3],[4,0,5]]
    Output: 1
    Explanation: Swap the 0 and the 5 in one move.


    --- Example 2 ---
    +-----+-----+-----+
    |     |     |     |
    +-----+-----+-----+
    |     |     |     |
    +-----+-----+-----+

    Input: board = [[1,2,3],[5,4,0]]
    Output: -1
    Explanation: No number of moves will make the board solved.


    --- Example 3 ---
    Input: board = [[4,1,2],[5,0,3]]
    Output: 5
    Explanation: 5 is the smallest number of moves that solves the board.
    An example path:
    After move 0: [[4,1,2],[5,0,3]]
    After move 1: [[4,1,2],[0,5,3]]
    After move 2: [[0,1,2],[4,5,3]]
    After move 3: [[1,0,2],[4,5,3]]
    After move 4: [[1,2,0],[4,5,3]]
    After move 5: [[1,2,3],[4,5,0]]

    *** Constraints ***
    board.length == 2
    board[i].length == 3
    0 <= board[i][j] <= 5
    Each value board[i][j] is unique.

*/

using namespace std;

/*
    ------------
    --- IDEA ---
    ------------

    TODO

*/

/* Time  Beats: 92.19% */
/* Space Beats: 44.55% */

/* Time  Complexity: O((m + n) * (m + n)!) */
/* Space Complexity: O(m + n)              */
class Solution {
public:
    int slidingPuzzle(std::vector<std::vector<int>>& board)
    {
        // Target state and initial state
        std::string target = "123450";
        std::string start;
        for (const auto& row : board)
        {
            for (int num : row)
                start += std::to_string(num);
        }

        // Neighbors map for each index in the 1D representation of the board
        std::vector<std::vector<int>> neighbors = {
            {1, 3},    // Neighbors of index 0
            {0, 2, 4}, // Neighbors of index 1
            {1, 5},    // Neighbors of index 2
            {0, 4},    // Neighbors of index 3
            {1, 3, 5}, // Neighbors of index 4
            {2, 4}     // Neighbors of index 5
        };

        // BFS setup
        std::queue<std::pair<std::string, int>> queue; // (state, moves)
        std::unordered_set<std::string> visited;      // To track visited states
        queue.push({start, 0});
        visited.insert(start);

        while ( ! queue.empty())
        {
            auto [state, moves] = queue.front();
            queue.pop();

            // Check if we've reached the target
            if (state == target)
                return moves;

            // Find the index of zero
            int zero_index = state.find('0');

            // Generate new states by swapping '0' with its neighbors
            for (int neighbor : neighbors[zero_index])
            {
                // Swap '0' with the neighbor
                std::string new_state = state;
                std::swap(new_state[zero_index], new_state[neighbor]);

                // If this new state hasn't been visited, add it to the queue
                if (visited.find(new_state) == visited.end())
                {
                    visited.insert(new_state);
                    queue.push({new_state, moves + 1});
                }
            }
        }

        // If we exhaust the queue without finding the target
        return -1;
    }
};
