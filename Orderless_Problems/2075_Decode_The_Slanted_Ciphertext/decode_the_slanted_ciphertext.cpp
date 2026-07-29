/*
    ==============
    === MEDIUM ===
    ==============

    ===================================
    2075) Decode the Slanted Ciphertext
    ===================================

    ============
    Description:
    ============

    A string originalText is encoded using a slanted transposition cipher to a
    string encodedText with the help of a matrix having a fixed number of rows
    rows.

    originalText is placed first in a top-left to bottom-right manner.


        # Check out the picture at LeetCode.


    The blue cells are filled first, followed by the red cells, then the yellow
    cells, and so on, until we reach the end of originalText. The arrow
    indicates the order in which the cells are filled. All empty cells are
    filled with ' '. The number of columns is chosen such that the rightmost
    column will not be empty after filling in originalText.

    encodedText is then formed by appending all characters of the matrix in a
    row-wise fashion.

        # Again--Check out the picture at LeetCode.

    The characters in the blue cells are appended first to encodedText, then
    the red cells, and so on, and finally the yellow cells. The arrow indicates
    the order in which the cells are accessed.

    For example, if originalText = "cipher" and rows = 3, then we encode it in
    the following manner:

        # Again--Check out the picture at LeetCode.

    The blue arrows depict how originalText is placed in the matrix, and the
    red arrows denote the order in which encodedText is formed. In the above
    example, encodedText = "ch ie pr".

    Given the encoded string encodedText and number of rows rows, return the
    original string originalText.

    =====
    Note: originalText does not have any trailing spaces ' '. The test cases
          are generated such that there is only one possible originalText. 
    =====

    ================================================================
    FUNCTION: string decodeCiphertext(string encodedText, int rows);
    ================================================================

    ==========================================================================
    ================================ EXAMPLES ================================
    ==========================================================================

    --- Example 1 ---
    Input: encodedText = "ch   ie   pr", rows = 3
    Output: "cipher"
    Explanation: This is the same example described in the problem description.

    --- Example 2 ---
    Input: encodedText = "iveo    eed   l te   olc", rows = 4
    Output: "i love leetcode"
    Explanation: The figure above denotes the matrix that was used to encode
    originalText. The blue arrows show how we can find originalText from
    encodedText.

    --- Example 3 ---
    Input: encodedText = "coding", rows = 1
    Output: "coding"
    Explanation: Since there is only 1 row, both originalText and encodedText
                 are the same.


    *** Constraints ***
    0 <= encodedText.length <= 10^6
    encodedText consists of lowercase English letters and ' ' only.
    encodedText is a valid encoding of some originalText that does not have
    trailing spaces.
    1 <= rows <= 1000
    The testcases are generated such that there is only one possible
    originalText.

*/

#include <string>
using namespace std;

/*
    ------------
    --- IDEA ---
    ------------

    TODO

*/

/* Time  Beats: 98.03% */
/* Space Beats: 93.84% */

/* Time  Complexity: O(N) */
/* Space Complexity: O(N) */
class Solution {
public:
    string decodeCiphertext(string encodedText, int rows)
    {
        if (rows == 1)
            return encodedText;

        const int N = encodedText.size();
        const int COLS = N / rows;

        string original_text;
        original_text.reserve(N);


        for (int col = 0; col < COLS; col++)
        {
            int j   = 0;
            int row = 0;
            while (row < rows && (col + j) < COLS)
            {
                original_text += encodedText[row * COLS + (col + j)];

                row++;
                j++;
            }
        }

        // "   a"
        //  0123
        // rows = 2
        while ( ! original_text.empty() && original_text.back() == ' ')
            original_text.pop_back();

        return original_text;
    }
};
