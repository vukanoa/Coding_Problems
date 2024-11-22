#include <iostream>
#include <vector>
#include <unordered_map>

/*
    ==============
    === MEDIUM ===
    ==============

    ===================================================
    1072) Flip Columns for Maximum Number of Equal Rows
    ===================================================

    ============
    Description:
    ============

    You are given an m x n binary matrix matrix.

    You can choose any number of columns in the matrix and flip every cell in
    that column (i.e., Change the value of the cell from 0 to 1 or vice versa).

    Return the maximum number of rows that have all values equal after some
    number of flips.

    ==================================================================
    FUNCTION: int maxEqualRowsAfterFlips(vector<vector<int>>& matrix);
    ==================================================================

    ==========================================================================
    ================================ EXAMPLES ================================
    ==========================================================================

    --- Example 1 ---
    Input: matrix = [[0,1],[1,1]]
    Output: 1
    Explanation: After flipping no values, 1 row has all values equal.

    --- Example 2 ---
    Input: matrix = [[0,1],[1,0]]
    Output: 2
    Explanation: After flipping values in the first column, both rows have
                 equal values.

    --- Example 3 ---
    Input: matrix = [[0,0,0],[0,0,1],[1,1,0]]
    Output: 2
    Explanation: After flipping values in the first two columns, the last two
                 rows have equal values.


    *** Constraints ***
    m == matrix.length
    n == matrix[i].length
    1 <= m, n <= 300
    matrix[i][j] is either 0 or 1.

*/

/*
    ------------
    --- IDEA ---
    ------------

    You have to try and observe as many trivial things as possible. It sounds
    unintuitive, but that's the only hope for anyone to solve this problem for
    the first time.

    Key observation here that is used as a big Hint is this:

        001 and 110 are "the same".

    If you try to go down the path of some big complicated example, you will
    probably fail.

    Once you realize that 001 and 110 are the same, then maybe you get the idea
    of how to actually approach this.

    We need to count as many of the "same" rows. (Remember that 001 and 110 are
    considered EQUIVALENT, because if you flip same columns in both to create
    the same row consisted of a single bit, then you'll end up with such rows
    in this case. If you make one, you'll make the other one as well)

    Since we want to count the same rows and their frequency, we need to use a
    HashMap.

    To use that, we cannot push an entire vector<int> as a Key to a HashMap,
    however what we can do is convert that vector<int> to a "string" and then
    use that as a key.

    But the thing is, if we simply convert them to strings and insert in the
    HashMap, how actually are we going to know that 001 and 110 are the same?

    That's where the final key "trick" comes into place - You have to pick what
    do you want your keys, in general, to start with: either 0 or 1?

    In the code, we've picked 0, therefore anytime we stumble upon a row that
    begins with 0, wi simply convert it to stirng and put in the Hashmap.
    However, once we stumble upon a row that begins with a 1, we create an
    INVERTED string of that row.

        110 ---> "001"

        Now 001 and 110 are both saved as a key "001", and the value is 2 now.

    After we've done processing each row, we simply take the maximum value in
    the HashMap and return that as a result.

*/

/* Time  Beats: 32.61% */
/* Space Beats: 59.70% */

/* Time  Complexity: O(m * n) */
/* Space Complexity: O(m * n) */
class Solution {
public:
    int maxEqualRowsAfterFlips(vector<vector<int>>& matrix)
    {
        const int ROWS = matrix.size();
        const int COLS = matrix[0].size();

        int result = 0;

        unordered_map<string, int> counter;

        for (int i = 0; i < ROWS; i++)
        {
            ostringstream out_key;
            for (int j = 0; j < COLS; j++)
            {
                if (matrix[i][0] == 1)
                    out_key << (matrix[i][j] == 1 ? 0 : 1);
                else
                    out_key << matrix[i][j];

            }
            counter[out_key.str()]++;

            result = max(result, counter[out_key.str()]);
        }

        return result;
    }
};
