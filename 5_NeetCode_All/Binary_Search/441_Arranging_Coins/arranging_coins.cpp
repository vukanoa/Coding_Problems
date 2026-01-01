#include <iostream>

/*
    ============
    === EASY ===
    ============

    ===========================
    447) Arranging Coins
    ===========================

    ============
    Description:
    ============

    You have n coins and you want to build a staircase with these coins. The
    staircase consists of k rows where the ith row has exactly i coins. The
    last row of the staircase may be incomplete.

    Given the integer n, return the number of complete rows of the staircase
    you will build.

    ==================================
    FUNCTION: int arrangeCoins(int n);
    ==================================

    ==========================================================================
    ================================ EXAMPLES ================================
    ==========================================================================

    --- Example 1 ---
                        +-----+
                     1  |  C  |
                        +-----+-----+
                     2  |  C  |  C  |
                        +-----+-----+-----+
                     3  |  C  |  C  |     |
                        +-----+-----+-----+
    Input: n = 5
    Output: 2
    Explanation: Because the 3rd row is incomplete, we return 2.

    --- Example 2 ---
                        +-----+
                     1  |  C  |
                        +-----+-----+
                     2  |  C  |  C  |
                        +-----+-----+-----+
                     3  |  C  |  C  |  C  |
                        +-----+-----+-----+-----+
                     4  |  C  |  C  |     |     |
                        +-----+-----+-----+-----+
    Input: n = 8
    Output: 3
    Explanation: Because the 4th row is incomplete, we return 3.


    *** Constraints ***
    1 <= n <= 2^31 - 1

*/

/*
    ------------
    --- IDEA ---
    ------------

    Gaus' formula for the sum of first n numbers: n/2 * (n+1)

    Consider this example:
                        +-----+
                     1  |  C  |
                        +-----+-----+
                     2  |  C  |  C  |
                        +-----+-----+-----+
                     3  |  C  |  C  |  C  |
                        +-----+-----+-----+-----+
                     4  |  C  |  C  |     |     |
                        +-----+-----+-----+-----+
    Input: n = 8
    Output: 3


    If we have "n" coins, what is the maximum number of rows, in theory?
    What is the "upper bound"?

    It's obvious that it's certainly impossible to have more than "n" rows.
    Usually, the number of rows will be much less than "n", but in general, we
    can be certain that it's impossible to have more than "n" rows given "n"
    coins.

    So the answer lays somewhere between: 1 and n.

    But why do we need Gaus' formula? What's the use of that?
    Well, with a bit of observation we can conclude that, to be able to build
    i-th row, we need: i/2 * (i+1) coins

    It's not that easy to observe that if you are seeing the problem for the
    first time, but it's not that difficult either.

    As we've concluded, our answer lays somewhere between: 1 and n.

    Now let's do a Binary Search on that range. Each time we'll work with "mid"
    value which represents the current row we're considering.

    So, how can we know if we can build "mid" row?
    (i.e. if "mid" is 4, we want to check if we can build 4-th row)

    As we've said, in order to build an i-th row(i.e. "mid" row), we need:
        (mid / 2) * (mid + 1)
    coins.

    So at each "iteration" we compute needed number of coins and we check if
    that amount of coins is greater than "n".

    However, there's a caveat here. In order to compute needed number of coins
    we have to make sure we don't do "integer division", i.e. that we do not
    floor the intermediate result.

    Let's see how we are going to compute needed number of coins for "mid" row:
        coins = (mid / 2) * (mid + 1)

    Imagine that "mid" is equal to 5.

    If we did a basic "integer division" we'd get:
        coins = 5/2 * 6
              =  2  * 6
              = 12

    Which isn't true. It's not true that we need 12 coins in order to
    successfully build full 5 rows.

                        +-----+
                     1  |  C  |
                        +-----+-----+
                     2  |  C  |  C  |
                        +-----+-----+-----+
                     3  |  C  |  C  |  C  |
                        +-----+-----+-----+-----+
                     4  |  C  |  C  |  C  |  C  |
                        +-----+-----+-----+-----+-----+
                     5  |  C  |  C  |  C  |  C  |  C  |
                        +-----+-----+-----+-----------+

    If you count all of these above, you'll see that there is a total of 15
    coins. Therefore, we conclude that in order to build a staircase of 5 rows
    we need 15 coins.

    That further indicates that our "integer division" gave us an incorrect
    result.

    So, how are we going to fix this?

    Just use "decimal division" when dividing by 2.
    (In C++ you either divide by 2.0 or you multiply by 1.0)

        coins = (mid / 2.0) * (mid + 1)
            OR
        coins = (1.0 * mid / 2) * (mid + 1)

    Again, imagine that "mid" is equal to 5.

    If we did a "decimal division" we'd get:
        coins = 5/2.0 * 6
              = 2.5   * 6
              = 15


    Now let's finish up our Example:
                        +-----+
                     1  |  C  |
                        +-----+-----+
                     2  |  C  |  C  |
                        +-----+-----+-----+
                     3  |  C  |  C  |  C  |
                        +-----+-----+-----+-----+
                     4  |  C  |  C  |     |     |
                        +-----+-----+-----+-----+
    Input: n = 8
    Output: 3


    We are doing Binary Search on a range: 1 to n=8

    left  = 1
    right = 8

    mid = left + (right - left) / 2;
    mid =  1   +    7 / 2
    mid =  1   +      3
    mid =  4

    As we've said, variable "mid" denotes the row for which we're trying to
    see if we can fully build it.

    So to calculate that we do:
        coins = 4/2.0 * (4 + 1)
        coins =  2.0  * 5
        coins = 10.0

    Now we have to see if we have that many coins.

    We ask:
        if (coins > n*1.0) // We multiply by 1.0 to make n "double", remember?
            right = mid - 1;

    Since this is true, that means this is more rows than we're practically
    able to build.

    That further indicates that we need to do our Binary Search on the
    remaining range of rows that are LESS than the current "mid" row we just
    tried.

    Therefore: right = mid - 1

    Now our range is: 1 to 3

    left  = 1
    right = 3

    mid = left + (right - left) / 2
    mid =  1   +      2 / 2
    mid =  1   +        1
    mid =  2 <------------------------------------------------
                                                             |
    Now we are trying to see if we can build 2 rows(because mid == 2).

    How many coins do we need:
        coins = (mid / 2.0) * (mid + 1)
              =     1.0     *  3
              = 4.0

    Now we have to check:
        if (coins > n*1.0) // We multiply by 1.0 to make n "double", remember?
            right = mid - 1;
        else
        {
            result = std::max(result, mid);
            left = mid + 1;
        }

    Now since the first condition is not true, we enter the "else" block.
    Since we are able to build this "mid" row, we have to ask if this is the
    biggest row we've managed to build. If it is - Update "result"(which we
    will return at the end as a result of this whole problem).
    If it's not, "result" will retain current value.

    But, why do we update our left point now to:
        left = mid + 1
    ?

    Because this row may not be the biggest row we're able to build(as is the
    case with this example. We can see, from the picture above, that the
    current row of 2 is not the biggest when we have 8 coins).

    Therefore, we continue our Binary Search, now in the range: 3 to 3

    left  = 3
    right = 3

    mid = left + (right - left) / 2
    mid =  3   +   0 / 2
    mid =  3   +   0
    mid =  3

    What is the number of coins we need in order to successfully bulid row 3?

    coins = (mid / 2.0) * (mid + 1)
          =  (3 / 2. 0) * (3 + 1)
          =    1.5      *    4
          =  6

    Again, we check:
        if (coins > n*1.0) // We multiply by 1.0 to make n "double", remember?
            right = mid - 1;
        else
        {
            res = std::max(res, mid);
            left = mid + 1;
        }

    Now we're in this state:
        left  = 4
        right = 3

    Therefore our "while" loop breaks and we return "res" which is, because of
    the last "iteration", equal to 3.

*/

/* Time  Beats: 100.00% */
/* Space Beats:  33.59% */

/* Time  Complexity: O(logn) */
/* Space Complexity: O(1) */
class Solution_1{
public:
    int arrangeCoins(int n)
    {
        int left  = 1;
        int right = n;

        int result = 0;
        while (left <= right)
        {
            int mid = left + (right - left) / 2;

            double coins = (mid / 2.0) * (mid + 1);

            if (coins > n*1.0)
                right = mid - 1;
            else
            {
                left = mid + 1;
                result = std::max(result, mid);
            }
        }

        return result;
    }
};




/*
    ------------
    --- IDEA ---
    ------------

    It's almost equivalent, but it's implemented a bit differently. This one
    makes more sense to me.

    The crux, i.e. the Math formula and the entire approach, is the same.

*/

/* Time  Beats: 100.00% */
/* Space Beats:  13.19% */

/* Time  Complexity: O(logn) */
/* Space Complexity: O(1)    */
class Solution_2 {
public:
    int arrangeCoins(int n)
    {
        int left  = 1;
        int right = n;

        while (left <= right)
        {
            int mid = left + (right - left) / 2;

            double coins = (mid / 2.0) * (mid + 1);

            if (coins == n * 1.0)
                return mid;

            if (coins < n * 1.0)
                left = mid + 1;
            else
                right = mid - 1;
        }

        return left - 1;
    }
};
