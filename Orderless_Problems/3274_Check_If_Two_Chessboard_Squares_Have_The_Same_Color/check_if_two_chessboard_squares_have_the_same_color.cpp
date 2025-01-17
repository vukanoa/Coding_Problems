/*
    ============
    === EASY ===
    ============

    ==================================================
    3274) Check if Two Chessboards Have the Same Color
    ==================================================

    ============
    Description:
    ============

    You are given two strings, coordinate1 and coordinate2, representing the
   coordinates of a square on an 8 x 8 chessboard.

    Below is the chessboard for reference. ('X' represents a BLACK square)


        +-----+-----+-----+-----+-----+-----+-----+-----+
     8  |     |  X  |     |  X  |     |  X  |     |  X  |
        +-----+-----+-----+-----+-----+-----+-----+-----+
     7  |  X  |     |  X  |     |  X  |     |  X  |     |
        +-----+-----+-----+-----+-----+-----+-----+-----+
     6  |     |  X  |     |  X  |     |  X  |     |  X  |
        +-----+-----+-----+-----+-----+-----+-----+-----+
     5  |  X  |     |  X  |     |  X  |     |  X  |     |
        +-----+-----+-----+-----+-----+-----+-----+-----+
     4  |     |  X  |     |  X  |     |  X  |     |  X  |
        +-----+-----+-----+-----+-----+-----+-----+-----+
     3  |  X  |     |  X  |     |  X  |     |  X  |     |
        +-----+-----+-----+-----+-----+-----+-----+-----+
     2  |     |  X  |     |  X  |     |  X  |     |  X  |
        +-----+-----+-----+-----+-----+-----+-----+-----+
     1  |  X  |     |  X  |     |  X  |     |  X  |     |
        +-----+-----+-----+-----+-----+-----+-----+-----+
           a     b     c     d     e     f     g     h


    Return true if these two squares have the same color and false otherwise.

    The coordinate will always represent a valid chessboard square. The
    coordinate will always have the letter first (indicating its column), and
    the number second (indicating its row).

    ===========================================================================
    FUNCTION: bool checkTwoChessboards(string coordinate1, string coordinate2);
    ===========================================================================

    ==========================================================================
    ================================ EXAMPLES ================================
    ==========================================================================

    --- Example 1 ---
    Input: coordinate1 = "a1", coordinate2 = "c3"
    Output: true
    Explanation:
    Both squares are black.

    --- Example 2 ---
    Input: coordinate1 = "a1", coordinate2 = "h3"
    Output: false
    Explanation:
    Square "a1" is black and "h3" is white.


    *** Constraints ***
    coordinate1.length == coordinate2.length == 2
    'a' <= coordinate1[0], coordinate2[0] <= 'h'
    '1' <= coordinate1[1], coordinate2[1] <= '8'

*/

#include <string>
#include <unordered_set>
using namespace std;


/*
    ------------
    --- IDEA ---
    ------------

    The code is self-explanatory. Look at the ASCII drawing of the chessboard
    and read he code. You'll get it.

*/

/* Time  Beats: 1.54% */
/* Space Beats: 8.94% */

/* Time  Complexity: O(1) */
/* Space Complexity: O(1) */
class Solution {
public:
    bool checkTwoChessboards(string coordinate1, string coordinate2)
    {
        const int N = coordinate1.length();

        return (   is_black(coordinate1) &&    is_black(coordinate2)) ||
               ( ! is_black(coordinate1) &&  ! is_black(coordinate2));
    }

private:
    bool is_black(string coordinate)
    {
        char number_row = coordinate[1];
        char letter_col = coordinate[0];

        unordered_set<char> uset = {'a', 'c', 'e', 'g'};

        return (number_row & 1 && uset.count(letter_col)) || ( !(number_row & 1) && !uset.count(letter_col));
    }
};


/*
    ------------
    --- IDEA ---
    ------------

    c1[1] and c2[1] are both NUMBERS, i.e. "rows".

    However c1[0] and c2[0] are LETTERS. But if we treat that character as an
    ASCII integer, then look at this:

        a = 97      // Odd
        b = 98      // Even
        c = 99      // Odd
        d = 100     // Even
        e = 101     // Odd
        f = 102     // Even
        g = 103     // Odd
        h = 104     // Even

    If it's an ODD character and an ODD   number, then we'll get an EVEN result
    which is a BLACK square.

    If it's an ODD character and an EVEN  number, then we'll get an ODD  result
    which is a WHITE square.

    If it's an EVEN characer and an ODD   number, then we'll get an ODD  result
    which is a WHITE square.

    If it's an EVEN character and an EVEN number, then we'll get an EVEN result
    which is a BLACK square.

    We just need to see if they are the same square.

    So if (c[0] + c[1]) % 2 == 0, then it's an EVEN result which is BLACK.
    So if (c[0] + c[1]) % 2 != 0, then it's an ODD  result which is WHITE.

*/

/* Time  Beats: 31.28% */
/* Space Beats: 81.15% */

/* Time  Complexity: O(1) */
/* Space Complexity: O(1) */
class Solution_One_Liner {
public:
    bool checkTwoChessboards(string c1, string c2)
    {
        return (c1[0] + c1[1]) % 2 == (c2[0] + c2[1]) % 2;
    }
};
