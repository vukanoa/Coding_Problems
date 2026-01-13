/*
    ============
    === EASY ===
    ============

    ===========================
    344) Reverse String
    ===========================

    ============
    Description:
    ============

    Write a function that reverses a string. The input string is given as an
    array of characters s.

    You must do this by modifying the input array in-place with O(1) extra
    memory.

    ==============================================
    FUNCTION: void reverseString(vector<char>& s);
    ==============================================

    ==========================================================================
    ================================ EXAMPLES ================================
    ==========================================================================

    --- Example 1 ---
    Input: s = ["h","e","l","l","o"]
    Output: ["o","l","l","e","h"]

    --- Example 2 ---
    Input: s = ["H","a","n","n","a","h"]
    Output: ["h","a","n","n","a","H"]


    *** Constraints ***
    1 <= s.length <= 105
    s[i] is a printable ascii character.

*/

#include <vector>
using namespace std;

/*
    ------------
    --- IDEA ---
    ------------

    Self Explanatory.

*/

/* Time  Beats: 100.00% */
/* Space Beats:  50.20% */

/* Time  Complexity: O(N) */
/* Space Complexity: O(1) */
class Solution {
public:
    void reverseString(vector<char>& s)
    {
        int L = 0;
        int R = s.size() - 1;

        while (L < R)
        {
            swap(s[L], s[R]);

            L++; // Increment
            R--; // Decrement
        }
    }
};
