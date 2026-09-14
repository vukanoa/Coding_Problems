/*
    ============
    === HARD ===
    ============

    ===========================
    1728) Cat and Mouse II
    ===========================

    ============
    Description:
    ============

    A game is played by a cat and a mouse named Cat and Mouse.

    The environment is represented by a grid of size rows x cols, where each
    element is a wall, floor, player (Cat, Mouse), or food.

        Players are represented by the characters 'C'(Cat),'M'(Mouse).
        Floors are represented by the character '.' and can be walked on.
        Walls are represented by the character '#' and cannot be walked on.
        Food is represented by the character 'F' and can be walked on.
        There is only one of each character 'C', 'M', and 'F' in grid.

    Mouse and Cat play according to the following rules:

        Mouse moves first, then they take turns to move.
        During each turn, Cat and Mouse can jump in one of the four directions (left, right, up, down). They cannot jump over the wall nor outside of the grid.
        catJump, mouseJump are the maximum lengths Cat and Mouse can jump at a time, respectively. Cat and Mouse can jump less than the maximum length.
        Staying in the same position is allowed.
        Mouse can jump over Cat.

    The game can end in 4 ways:

        If Cat occupies the same position as Mouse, Cat wins.
        If Cat reaches the food first, Cat wins.
        If Mouse reaches the food first, Mouse wins.
        If Mouse cannot get to the food within 1000 turns, Cat wins.

    Given a rows x cols matrix grid and two integers catJump and mouseJump,
    return true if Mouse can win the game if both Cat and Mouse play optimally,
    otherwise return false.

    =============================================================================
    FUNCTION: bool canMouseWin(vector<string>& grid, int catJump, int mouseJump);
    =============================================================================

    ==========================================================================
    ================================ EXAMPLES ================================
    ==========================================================================

    --- Example 1 ---
    Input: grid = ["####F","#C...","M...."], catJump = 1, mouseJump = 2
    Output: true
    Explanation: Cat cannot catch Mouse on its turn nor can it get the food
                 before Mouse.

    --- Example 2 ---
    Input: grid = ["M.C...F"], catJump = 1, mouseJump = 4
    Output: true

    --- Example 3 ---
    Input: grid = ["M.C...F"], catJump = 1, mouseJump = 3
    Output: false


    *** Constraints ***
    rows == grid.length
    cols = grid[i].length
    1 <= rows, cols <= 8
    grid[i][j] consist only of characters 'C', 'M', 'F', '.', and '#'.
    There is only one of each character 'C', 'M', and 'F' in grid.
    1 <= catJump, mouseJump <= 8

*/

#include <string>
#include <utility>
#include <vector>
using namespace std;

/*
    ------------
    --- IDEA ---
    ------------

    TODO

*/

/* Time  Beats: 21.70% */
/* Space Beats: 10.08% */

/* Time  Complexity: O((ROWS * COLS)^2  *  max(catJump, mouseJump)) */
/* Space Complexity: O((ROWS * COLS)^3                            ) */
class Solution {
public:
    int ROWS, COLS;
    int food;
    int cat;
    int mouse;
    int mouse_jump;
    int cat_jump;

    vector<int8_t> memo;
    vector<vector<bool>> walls;

    bool canMouseWin(vector<string>& grid, int catJump, int mouseJump)
    {
        ROWS = grid.size();
        COLS = grid[0].size();

        cat_jump   = catJump;
        mouse_jump = mouseJump;

        walls.assign(ROWS, vector<bool>(COLS, false));

        for (int row = 0; row < ROWS; row++)
        {
            for (int col = 0; col < COLS; col++)
            {
                if (grid[row][col] == 'F')
                {
                    food = row * COLS + col;
                }
                else if (grid[row][col] == 'C')
                {
                    cat = row * COLS + col;
                }
                else if (grid[row][col] == 'M')
                {
                    mouse = row * COLS + col;
                }
                else if (grid[row][col] == '#')
                {
                    walls[row][col] = true;
                }
            }
        }

        const int CELLS = ROWS * COLS;
        memo.assign(CELLS * CELLS * CELLS * 2, -1);

        return solve(cat, mouse, 0);
    }

private:
    int get_index(int cat, int mouse, int turn)
    {
        const int CELLS = ROWS * COLS;

        return ((cat * CELLS + mouse) * (CELLS * 2)) + turn;
    }

    bool solve(int cat, int mouse, int turn)
    {
        if (cat == food || cat == mouse)
            return false;

        if (mouse == food)
            return true;

        if (turn >= ROWS * COLS * 2)
            return false;

        int state = get_index(cat, mouse, turn);

        if (memo[state] != -1)
            return memo[state];

        /* Signing Cross */
        vector<pair<int, int>> directions = {{-1, 0}, {1, 0}, {0, -1}, {0, 1}};

        if ( ! (turn & 1)) // Mouse's turn
        {
            int x = mouse / COLS;
            int y = mouse % COLS;

            for (const auto& dir : directions)
            {
                for (int jump = 0; jump <= mouse_jump; jump++)
                {
                    int new_x = x + jump * dir.first;
                    int new_y = y + jump * dir.second;

                    if (new_x < 0 || new_y < 0 || new_x >= ROWS || new_y >= COLS)
                        break;

                    if (walls[new_x][new_y])
                        break;

                    int next_mouse = new_x * COLS + new_y;

                    if (solve(cat, next_mouse, turn + 1))
                        return memo[state] = true;
                }
            }

            return memo[state] = false;
        }
        else // Cat's turn
        {
            int x = cat / COLS;
            int y = cat % COLS;

            for (const auto& dir : directions)
            {
                for (int jump = 0; jump <= cat_jump; jump++)
                {
                    int new_x = x + jump * dir.first;
                    int new_y = y + jump * dir.second;

                    if (new_x < 0 || new_y < 0 || new_x >= ROWS || new_y >= COLS)
                        break;

                    if (walls[new_x][new_y])
                        break;

                    int next_cat = new_x * COLS + new_y;

                    if ( ! solve(next_cat, mouse, turn + 1))
                        return memo[state] = false;
                }
            }

            return memo[state] = true;
        }
    }
};
