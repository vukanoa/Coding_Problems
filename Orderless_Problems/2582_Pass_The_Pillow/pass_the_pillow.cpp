#include <iostream>

/*
    ============
    === EASY ===
    ============

    ===========================
    2582) Pass The Pillow
    ===========================

    ============
    Description:
    ============

    There are n people standing in a line labeled from 1 to n. The first person
    in the line is holding a pillow initially. Every second, the person holding
    the pillow passes it to the next person standing in the line. Once the
    pillow reaches the end of the line, the direction changes, and people
    continue passing the pillow in the opposite direction.

        For example, once the pillow reaches the nth person they pass it to the
        n - 1th person, then to the n - 2th person and so on.

    Given the two positive integers n and time, return the index of the person
    holding the pillow after time seconds.

    =============================================
    FUNCTION: int passThePillow(int n, int time);
    =============================================

    ==========================================================================
    ================================ EXAMPLES ================================
    ==========================================================================

    --- Example 1 ---
    Input: n = 4, time = 5
    Output: 2
    Explanation: People pass the pillow in the following way: 1 -> 2 -> 3 -> 4 -> 3 -> 2.
    After five seconds, the 2nd person is holding the pillow.

    --- Example 2 ---
    Input: n = 3, time = 2
    Output: 3
    Explanation: People pass the pillow in the following way: 1 -> 2 -> 3.
    After two seconds, the 3rd person is holding the pillow.


    *** Constraints ***
    2 <= n <= 1000
    1 <= time <= 1000

*/

/*
    ------------
    --- IDEA ---
    ------------

    It's an intuitive idea.

    Going from starting "node" 1 to an end "node" n requires n-1 "jumps", i.e.
    time is <= n-1.

    If we only jump n-1 times or LESS then we are certainly going from left
    to right.

    If we know we are starting from "node" 1 and we have to jump n-1 times or
    LESS, then the result is:  1 + time.

    However we can also "start" at "node" 1 if the variable "time" is:

        time >= 2*(n-1) && time <= 3*(n-1)

            or

        time >= 4*(n-1) && time <= 5*(n-1)

            or

        time >= 6*(n-1) && time <= 7*(n-1)

            ...


    In order to determine at which "state" we're in, we have to DIVIDE and get
    and INTEGER. Even number means we are at "node" 1 and ODD number means we
    are at "node" n.

    That was what "integer division" did.

    Now doing the MOD operation of time, by (n-1), we are going to get the
    number of "jumps" starting at either "node" 1 or "node" n, depending on the
    result of the "integer dividion".

    And that's literally it.

*/

/* Time  Beats: 54.14% */
/* Space Beats: 71.18% */

/* Time  Complexity: O(1) */
/* Space Complexity: O(1) */
class Solution {
public:
    int passThePillow(int n, int time)
    {
        int  result;
        bool from_left = (time / (n-1)) % 2 == 0;

        if (from_left)
            result = 1 + (time % (n-1));
        else
            result = n - (time % (n-1));

        return result;
    }
};
