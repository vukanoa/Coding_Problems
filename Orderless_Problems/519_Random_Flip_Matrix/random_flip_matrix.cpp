/*
    ==============
    === MEDIUM ===
    ==============

    ===========================
    519) Random Flip Matrix
    ===========================

    ============
    Description:
    ============


    There is an m x n binary grid matrix with all the values set 0 initially.
    Design an algorithm to randomly pick an index (i, j) where matrix[i][j] ==
    0 and flips it to 1. All the indices (i, j) where matrix[i][j] == 0 should
    be equally likely to be returned.

    Optimize your algorithm to minimize the number of calls made to the
    built-in random function of your language and optimize the time and space
    complexity.

    Implement the Solution class:

        + Solution(int m, int n) Initializes the object with the size of the
          binary matrix m and n.

        + int[] flip() Returns a random index [i, j] of the matrix where
          matrix[i][j] == 0 and flips it to 1.

        + void reset() Resets all the values of the matrix to be 0.

    ===============================
    CLASS:
    class Solution {
    public:
        Solution(int m, int n) {
            
        }
        
        vector<int> flip() {
            
        }
        
        void reset() {
            
        }
    };
    ===============================

    ==========================================================================
    ================================ EXAMPLES ================================
    ==========================================================================

    --- Example 1 ---
    Input
    ["Solution", "flip", "flip", "flip", "reset", "flip"]
    [[3, 1], [], [], [], [], []]
    Output
    [null, [1, 0], [2, 0], [0, 0], null, [2, 0]]

    Explanation
    Solution solution = new Solution(3, 1);
    solution.flip();  // return [1, 0], [0,0], [1,0], and [2,0] should be
                      // equally likely to be returned.
    solution.flip();  // return [2, 0], Since [1,0] was returned, [2,0] and
                      // [0,0]
    solution.flip();  // return [0, 0], Based on the previously returned
                      // indices, only [0,0] can be returned.
    solution.reset(); // All the values are reset to 0 and can be returned.
    solution.flip();  // return [2, 0], [0,0], [1,0], and [2,0] should be
                      // equally likely to be returned.


    *** Constraints ***
    1 <= m, n <= 10^4
    There will be at least one free cell for each call to flip.
    At most 1000 calls will be made to flip and reset.

*/

#include <vector>
using namespace std;

/*
    ------------
    --- IDEA ---
    ------------

    TODO

*/

/* Time  Beats: 51.19% */
/* Space Beats: 91.97% */

/* Time  Complexity: O(1) */
/* Space Complexity: O(1) */
class Solution {
private:
    int curr_row;
    int curr_col;
    int row_count;
    int col_count;

public:
    Solution(int m, int n)
    {
        curr_row = 0;
        curr_col = 0;

        row_count = m;
        col_count = n;
    }
    
    vector<int> flip()
    {
        vector<int> flipped_cell = {curr_row, curr_col};

        curr_col++;
        if (curr_col == col_count)
        {
            curr_col = 0;
            curr_row++;

            if (curr_row == row_count)
                curr_row = 0;
        }

        return flipped_cell;
    }
    
    void reset()
    {
        // Intentionally left empty because it matches original behavior
    }
};
