/*
    ==============
    === MEDIUM ===
    ==============

    ===========================
    788) Rotated Digits
    ===========================

    ============
    Description:
    ============

    An integer x is a good if after rotating each digit individually by 180
    degrees, we get a valid number that is different from x. Each digit must be
    rotated - we cannot choose to leave it alone.

    A number is valid if each digit remains a digit after rotation. For example:

        + 0, 1, and 8 rotate to themselves,

        + 2 and 5 rotate to each other (in this case they are rotated in a
          different direction, in other words, 2 or 5 gets mirrored),

        + 6 and 9 rotate to each other, and

        + the rest of the numbers do not rotate to any other number and become
          invalid.

    Given an integer n, return the number of good integers in the range [1, n].

    ===================================
    FUNCTION: int rotatedDigits(int n);
    ===================================

    ==========================================================================
    ================================ EXAMPLES ================================
    ==========================================================================

    --- Example 1 ---
    Input: n = 10
    Output: 4
    Explanation: There are four good numbers in the range [1, 10] : 2, 5, 6, 9.
    Note that 1 and 10 are not good numbers, since they remain unchanged after
    rotating.

    --- Example 2 ---
    Input: n = 1
    Output: 0

    --- Example 3 ---
    Input: n = 2
    Output: 1


    *** Constraints ***
    1 <= n <= 10^4

*/

/*
    ------------
    --- IDEA ---
    ------------

    Brute-Force, but completely valid Solution given the Constrints of the
    problem.

*/

/* Time  Beats: 100.00% */
/* Space Beats:  83.68% */

/* Time  Complexity: O(N) */
/* Space Complexity: O(1) */
class Solution {
public:
    int rotatedDigits(int n)
    {
        int result = 0;

        /* TYPES */
        const int SELF    = 0;
        const int INVALID = 1;
        const int MIRROR  = 2;

        int digit_type[10];
        digit_type[0] = SELF;
        digit_type[1] = SELF;
        digit_type[2] = MIRROR;
        digit_type[3] = INVALID;
        digit_type[4] = INVALID;
        digit_type[5] = MIRROR;
        digit_type[6] = MIRROR;
        digit_type[7] = INVALID;
        digit_type[8] = SELF;
        digit_type[9] = MIRROR;

        for (int i = 1; i <= n; i++)
        {
            int number = i;
            bool good = false;

            while (number > 0)
            {
                int digit = number % 10;

                if (digit_type[digit] == INVALID)
                {
                    good = false;
                    break;
                }

                if (digit_type[digit] == MIRROR)
                    good = true;

                // Divide
                number /= 10;
            }

            if (good)
                result++;
        }

        return result;
    }
};
