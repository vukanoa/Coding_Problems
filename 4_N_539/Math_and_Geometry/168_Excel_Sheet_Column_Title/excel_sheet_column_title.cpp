#include <iostream>
#include <vector>
#include <sstream>

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

/* Time  Beats:   100% */
/* Space Beats: 74.50% */

/* Time  Complexity: O(columnNumber / 26) */
/* Space Complexity: O(1) */
class Solution {
public:
    string convertToTitle(int columnNumber)
    {
        std::vector<char> letters = {'Z', 'A', 'B', 'C', 'D', 'E', 'F', 'G',
                                     'H', 'I', 'J', 'K', 'L', 'M', 'N', 'O',
                                     'P', 'Q', 'R', 'S', 'T', 'U', 'V', 'W',
                                     'X', 'Y', 'Z'};

        std::ostringstream out;
        while (columnNumber > 0)
        {
            out << letters[columnNumber % 26];

            columnNumber--;
            columnNumber /= 26;
        }

        std::string result = out.str();
        std::reverse(result.begin(), result.end());

        return result;
    }
};
