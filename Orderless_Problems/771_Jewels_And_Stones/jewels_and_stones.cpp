/*
    ============
    === EASY ===
    ============

    ===========================
    771) Jewels and Stones
    ===========================

    ============
    Description:
    ============

    You're given strings jewels representing the types of stones that are
    jewels, and stones representing the stones you have. Each character in
    stones is a type of stone you have. You want to know how many of the stones
    you have are also jewels.

    Letters are case sensitive, so "a" is considered a different type of stone
    from "A".

    ==============================================================
    FUNCTION: int numJewelsInStones(string jewels, string stones);
    ==============================================================

    ==========================================================================
    ================================ EXAMPLES ================================
    ==========================================================================

    --- Example 1 ---
    You're given strings jewels representing the types of stones that are
    jewels, and stones representing the stones you have. Each character in
    stones is a type of stone you have. You want to know how many of the stones
    you have are also jewels.

    Letters are case sensitive, so "a" is considered a different type of stone
    from "A".


    --- Example 2 ---
    Input: jewels = "aA", stones = "aAAbbbb"
    Output: 3

    --- Example 3 ---
    Input: jewels = "z", stones = "ZZ"
    Output: 0


    *** Constraints ***
    1 <= jewels.length, stones.length <= 50
    jewels and stones consist of only English letters.
    All the characters of jewels are unique.

*/

#include <string>
using namespace std;

/*
    ------------
    --- IDEA ---
    ------------

    Self-explanaotry.

*/

/* Time  Beats: 100.00% */
/* Space Beats:  42.15% */

/* Time  Complexity: O(N) */
/* Space Complexity: O(1) */
class Solution {
public:
    int numJewelsInStones(string jewels, string stones)
    {
        int result = 0;
        int ascii[128] = {0};

        for (const char& chr : jewels)
            ascii[chr] = 1;

        for (const char& stone : stones)
            result += ascii[stone];

        return result;
    }
};
