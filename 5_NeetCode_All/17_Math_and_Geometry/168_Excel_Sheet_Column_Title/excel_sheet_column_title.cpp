/*
    ============
    === EASY ===
    ============

    =============================
    168) Excel Sheet Column Title
    =============================

    ============
    Description:
    ============

    Given an integer columnNumber, return its corresponding column title as it
    appears in an Excel sheet.

    For example:

    A -> 1
    B -> 2
    C -> 3
    ...
    Z -> 26
    AA -> 27
    AB -> 28
    ...

    ==================================================
    FUNCTION: string convertToTitle(int columnNumber);
    ==================================================

    ==========================================================================
    ================================ EXAMPLES ================================
    ==========================================================================

    --- Example 1 ---
    Input: columnNumber = 1
    Output: "A"

    --- Example 2 ---
    Input: columnNumber = 28
    Output: "AB"

    --- Example 3 ---
    Input: columnNumber = 701
    Output: "ZY"


    *** Constraints ***
    1 <= columnNumber <= 2^31 - 1

*/

#include <algorithm>
#include <string>
#include <vector>
using namespace std;

/*
    ------------
    --- IDEA ---
    ------------

    TODO

*/

/* Time  Beats: 100.00% */
/* Space Beats:  74.50% */

/* Time  Complexity: O(log(columnNumber)) */
/* Space Complexity: O(1)                 */
class Solution {
public:
    string convertToTitle(int columnNumber)
    {
        vector<char> letters = {'Z', 'A', 'B', 'C', 'D', 'E', 'F', 'G',
                                     'H', 'I', 'J', 'K', 'L', 'M', 'N', 'O',
                                     'P', 'Q', 'R', 'S', 'T', 'U', 'V', 'W',
                                     'X', 'Y', 'Z'};

        string result;
        result.reserve(4);

        while (columnNumber > 0)
        {
            result += letters[columnNumber % 26];

            columnNumber--;
            columnNumber /= 26;
        }

        /* Reverse */
        reverse(result.begin(), result.end());

        return result;
    }
};




/*
    ------------
    --- IDEA ---
    ------------

    Same idea, however here we did took care of "off by one" in another way.

*/

/* Time  Beats: 100.00% */
/* Space Beats:   1.52% */

/* Time  Complexity: O(log(columnNumber)) */
/* Space Complexity: O(1)                 */
class Solution_2 {
public:
    string convertToTitle(int columnNumber)
    {
        string result;
        result.reserve(4);

        while (columnNumber > 0)
        {
            columnNumber--;

            int offset = columnNumber % 26;
            result += ('A' + offset);

            // Divide
            columnNumber /= 26;
        }

        /* Reverse */
        reverse(result.begin(), result.end());

        return result;
    }
};
