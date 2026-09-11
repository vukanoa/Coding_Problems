/*
    ==============
    === MEDIUM ===
    ==============

    ==============================================
    2850) Minimum Moves to Spread Stones Over Grid
    ==============================================

    ============
    Description:
    ============

    You are given a 0-indexed 2D integer matrix grid of size 3 * 3,
    representing the number of stones in each cell. The grid contains exactly 9
    stones, and there can be multiple stones in a single cell.

    In one move, you can move a single stone from its current cell to any other
    cell if the two cells share a side.

    Return the minimum number of moves required to place one stone in each
    cell.

    ======================================================
    FUNCTION: int minimumMoves(vector<vector<int>>& grid);
    ======================================================

    ==========================================================================
    ================================ EXAMPLES ================================
    ==========================================================================

    --- Example 1 ---
    Input: grid = [[1,1,0],[1,1,1],[1,2,1]]
    Output: 3
    Explanation: One possible sequence of moves to place one stone in each cell is: 
    1- Move one stone from cell (2,1) to cell (2,2).
    2- Move one stone from cell (2,2) to cell (1,2).
    3- Move one stone from cell (1,2) to cell (0,2).
    In total, it takes 3 moves to place one stone in each cell of the grid.
    It can be shown that 3 is the minimum number of moves required to place one stone in each cell.

    --- Example 2 ---
    Input: grid = [[1,3,0],[1,0,0],[1,0,3]]
    Output: 4
    Explanation: One possible sequence of moves to place one stone in each cell is:
    1- Move one stone from cell (0,1) to cell (0,2).
    2- Move one stone from cell (0,1) to cell (1,1).
    3- Move one stone from cell (2,2) to cell (1,2).
    4- Move one stone from cell (2,2) to cell (2,1).
    In total, it takes 4 moves to place one stone in each cell of the grid.
    It can be shown that 4 is the minimum number of moves required to place one stone in each cell.


    *** Constraints ***
    grid.length == grid[i].length == 3
    0 <= grid[i][j] <= 9
    Sum of grid is equal to 9.

*/

#include <queue>
#include <set>
#include <vector>
using namespace std;

/*
    ------------
    --- IDEA ---
    ------------

    TODO

*/

/* Time  Beats: 5.20% */
/* Space Beats: 5.20% */

/* Time  Complexity: O(S * 9 * 4) */ // S is the number of distinct grid states
/* Space Complexity: O(S * 9    ) */
class Solution {
private:
    vector<int> get_adjacent(int index)
    {
        vector<int> adjacent;

        if (index % 3 != 0) adjacent.push_back(index - 1);
        if (index % 3 != 2) adjacent.push_back(index + 1);
        if (index / 3 != 0) adjacent.push_back(index - 3);
        if (index / 3 != 2) adjacent.push_back(index + 3);

        return adjacent;
    }

public:
    int minimumMoves(vector<vector<int>>& grid)
    {
        vector<int> start(9);

        for (int i = 0; i < 3; i++)
        {
            for (int j = 0; j < 3; j++)
            {
                start[i * 3 + j] = grid[i][j];
            }
        }

        vector<int> target = {1, 1, 1, 1, 1, 1, 1, 1, 1};

        queue<vector<int>> queue;
        set<vector<int>> visited;

        queue.push(start);
        visited.insert(start);

        int moves = 0;
        while ( ! queue.empty())
        {
            const int SIZE = queue.size();

            for (int i = 0; i < SIZE; i++)
            {
                vector<int> curr = queue.front();
                queue.pop();

                if (curr == target)
                    return moves;

                for (int j = 0; j < 9; j++)
                {
                    if (curr[j] > 1)
                    {
                        for (int next : get_adjacent(j))
                        {
                            vector<int> new_state = curr;
                            --new_state[j];
                            ++new_state[next];

                            if (!visited.count(new_state))
                            {
                                visited.insert(new_state);
                                queue.push(new_state);
                            }
                        }
                    }
                }
            }

            ++moves;
        }

        return -1;
    }
};
