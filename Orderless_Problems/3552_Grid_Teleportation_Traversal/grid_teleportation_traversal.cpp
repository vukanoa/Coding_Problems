/*
    ==============
    === MEDIUM ===
    ==============

    ==================================
    3552) Grid Teleportation Traversal
    ==================================

    ============
    Description:
    ============

    You are given a 2D character grid matrix of size m x n, represented as an
    array of strings, where matrix[i][j] represents the cell at the
    intersection of the ith row and jth column. Each cell is one of the
    following:

        '.' representing an empty cell.
        '#' representing an obstacle.
        An uppercase letter ('A'-'Z') representing a teleportation portal.

    You start at the top-left cell (0, 0), and your goal is to reach the
    bottom-right cell (m - 1, n - 1). You can move from the current cell to any
    adjacent cell (up, down, left, right) as long as the destination cell is
    within the grid bounds and is not an obstacle.

    If you step on a cell containing a portal letter and you haven't used that
    portal letter before, you may instantly teleport to any other cell in the
    grid with the same letter. This teleportation does not count as a move, but
    each portal letter can be used at most once during your journey.

    Return the minimum number of moves required to reach the bottom-right cell.
    If it is not possible to reach the destination, return -1.

    ===============================================
    FUNCTION: int minMoves(vector<string>& matrix);
    ===============================================

    ==========================================================================
    ================================ EXAMPLES ================================
    ==========================================================================

    --- Example 1 ---
    Input: matrix = ["A..",".A.","..."]
    Output: 2
    Explanation:
        Before the first move, teleport from (0, 0) to (1, 1).
        In the first move, move from (1, 1) to (1, 2).
        In the second move, move from (1, 2) to (2, 2).


    --- Example 2 ---
    Input: matrix = [".#...",".#.#.",".#.#.","...#."]
    Output: 13


    *** Constraints ***
    1 <= m == matrix.length <= 10^3
    1 <= n == matrix[i].length <= 10^3
    matrix[i][j] is either '#', '.', or an uppercase English letter.
    matrix[0][0] is not an obstacle.

*/

#include <deque>
#include <string>
#include <unordered_map>
#include <utility>
#include <vector>
using namespace std;

/*
    ------------
    --- IDEA ---
    ------------

    Classic BFS 0-1.

*/

/* Time  Beats: 58.04% */
/* Space Beats: 37.52% */

/* Time  Complexity: O(ROWS * COLS) */
/* Space Complexity: O(ROWS * COLS) */
class Solution {
public:

    /* Signing Cross */
    vector<pair<int, int>> directions = {{-1,0}, {1,0}, {0,-1}, {0,1}};

    int minMoves(vector<string>& matrix)
    {
        const int ROWS = matrix.size();
        const int COLS = matrix[0].size();

        if (ROWS == 0)
            return -1;

        // Map teleport letter to coordinates, i.e. {row, col} pairs.
        unordered_map<char, vector<pair<int,int>>> umap;
        for (int row = 0; row < ROWS; ++row)
        {
            for (int col = 0; col < COLS; ++col)
            {
                if (matrix[row][col] >= 'A' && matrix[row][col] <= 'Z')
                    umap[matrix[row][col]].push_back( {row, col} ); // Store coordinates of teleport letters
            }
        }

        return solve(0, 0, matrix, umap); // Start BFS from the top-left corner
    }

private:
    int solve(int row, int col, const vector<string>& grid, unordered_map<char, vector<pair<int,int>>>& umap)
    {
        const int ROWS = grid.size();
        const int COLS = grid[0].size();

        const int INF = 1e9; // Infinity constant for unreachable cells

        // Distance matrix to track minimum moves FROM cell (0, 0) TO that cell
        vector<vector<int>> dist(ROWS, vector<int>(COLS, INF));

        vector<bool> used(26, false);
        deque<pair<int,int>> deque;

        dist[row][col] = 0;            // Starting point distance is 0
        deque.push_back( {row, col} ); // Add starting point to the deque

        // BFS 0-1
        while ( ! deque.empty())
        {
            auto [curr_row, curr_col] = deque.front();
            deque.pop_front();

            int  curr_dist = dist[curr_row][curr_col];
            char curr_chr  = grid[curr_row][curr_col];

            // Teleportation if letter not used yet
            if (curr_chr >= 'A' && curr_chr <= 'Z' && ! used[curr_chr - 'A'])
            {
                used[curr_chr - 'A'] = true;

                for (const auto& [new_row, new_col] : umap[curr_chr])
                {
                    // Check if a shorter path is found
                    if (curr_dist < dist[new_row][new_col])
                    {
                        dist[new_row][new_col] = curr_dist;     // No cost for teleportation
                        deque.push_front( {new_row, new_col} ); // Add to front for zero-cost move
                    }
                }
            }

            for (const auto& dir : directions)
            {
                int new_row = curr_row + dir.first;
                int new_col = curr_col + dir.second;

                if (new_row < 0 || new_col < 0 || new_row >= ROWS || new_col >= COLS)
                    continue;

                if (grid[new_row][new_col] == '#')
                    continue;

                // Check if a shorter path is found
                if ((curr_dist + 1) < dist[new_row][new_col])
                {
                    dist[new_row][new_col] = curr_dist + 1;
                    deque.push_back( {new_row, new_col} );
                }
            }
        }

        return dist[ROWS-1][COLS-1] == INF ? -1 : dist[ROWS-1][COLS-1];
    }
};
