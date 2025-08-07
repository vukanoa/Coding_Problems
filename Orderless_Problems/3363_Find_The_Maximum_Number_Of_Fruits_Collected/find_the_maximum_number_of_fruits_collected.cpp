/*
    ============
    === HARD ===
    ============

    =================================================
    3363) Find the Maximum Number of Fruits Collected
    =================================================

    ============
    Description:
    ============

    There is a game dungeon comprised of n x n rooms arranged in a grid.

    You are given a 2D array fruits of size n x n, where fruits[i][j]
    represents the number of fruits in the room (i, j). Three children will
    play in the game dungeon, with initial positions at the corner rooms
    (0, 0), (0, n - 1), and (n - 1, 0).

    The children will make exactly n - 1 moves according to the following rules
    to reach the room (n - 1, n - 1):

    The child starting from (0, 0) must move from their current room (i, j)
    to one of the rooms (i + 1, j + 1), (i + 1, j), and (i, j + 1) if the
    target room exists. The child starting from (0, n - 1) must move from their
    current room (i, j) to one of the rooms (i + 1, j - 1), (i + 1, j), and
    (i + 1, j +1) if the target room exists. The child starting from
    (n - 1, 0) must move from their current room (i, j) to one of the rooms
    (i - 1, j + 1), (i, j + 1), and (i + 1, j + 1) if the target room exists.

    When a child enters a room, they will collect all the fruits there. If two
    or more children enter the same room, only one child will collect the
    fruits, and the room will be emptied after they leave.

    Return the maximum number of fruits the children can collect from the
    dungeon.

    ==============================================================
    FUNCTION: int maxCollectedFruits(vector<vector<int>>& fruits);
    ==============================================================

    ==========================================================================
    ================================ EXAMPLES ================================
    ==========================================================================

    --- Example 1 ---
    nput: fruits = [[1,2,3,4],[5,6,8,7],[9,10,11,12],[13,14,15,16]]
    Output: 100
    In this example:
        + The 1st child (green) moves on the path (0,0) -> (1,1) -> (2,2) -> (3, 3).
        + The 2nd child (red) moves on the path (0,3) -> (1,2) -> (2,3) -> (3, 3).
        + The 3rd child (blue) moves on the path (3,0) -> (3,1) -> (3,2) -> (3, 3).
    In total they collect 1 + 6 + 11 + 16 + 4 + 8 + 12 + 13 + 14 + 15 = 100 fruits.


    --- Example 2 ---
    Input: fruits = [[1,1],[1,1]]
    Output: 4
    Explanation:
    In this example:
        + The 1st child moves on the path (0,0) -> (1,1).
        + The 2nd child moves on the path (0,1) -> (1,1).
        + The 3rd child moves on the path (1,0) -> (1,1).
    In total they collect 1 + 1 + 1 + 1 = 4 fruits.


    *** Constraints ***
    2 <= n == fruits.length == fruits[i].length <= 1000
    0 <= fruits[i][j] <= 1000

*/

#include <vector>
using namespace std;

/*
    ------------
    --- IDEA ---
    ------------

    TODO

*/

/* Time  Beats: 85.06% */
/* Space Beats: 91.56% */

/* Time  Complexity: O(N^2) */
/* Space Complexity: O(N)   */
class Solution {
public:
    int maxCollectedFruits(vector<vector<int>>& grid)
    {
        const int N = grid.size();
        int result = 0;

        for (int i = 0; i < N; i++)
            result += grid[i][i];

        for (int pass = 0; pass < 2; pass++)
        {
            if (pass == 1)
            {
                for (int i = 0; i < N; i++)
                {
                    for (int j = i + 1; j < N; j++)
                        swap(grid[i][j], grid[j][i]);
                }
            }

            vector<int> prev(N, -1);
            vector<int> curr(N, -1);
            prev[N - 1] = grid[0][N - 1];

            for (int row = 1; row < N - 1; row++)
            {
                fill(curr.begin(), curr.end(), -1);

                for (int i = 0; i < N; i++)
                {
                    if (prev[i] < 0)
                        continue;

                    if (i > 0) 
                        curr[i - 1] = max(curr[i - 1], prev[i] + grid[row][i - 1]);

                    if (i < N - 1) 
                        curr[i + 1] = max(curr[i + 1], prev[i] + grid[row][i + 1]);

                    curr[i] = max(curr[i], prev[i] + grid[row][i]);
                }
                swap(prev, curr);
            }

            result += prev[N - 1];
        }

        return result;
    }
};
