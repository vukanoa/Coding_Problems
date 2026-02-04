/*
    ============
    === EASY ===
    ============

    ===========================
    69) Sqrt(x)
    ===========================

    ============
    Description:
    ============

    Given a non-negative integer x, return the square root of x rounded down to
    the nearest integer. The returned integer should be non-negative as well.

    You must not use any built-in exponent function or operator.

    For example, do not use pow(x, 0.5) in c++ or x ** 0.5 in python.


    ============================
    FUNCTION: int mySqrt(int x);
    ============================

    ==========================================================================
    ================================ EXAMPLES ================================
    ==========================================================================

    --- Example 1 ---
    Input: x = 4
    Output: 2
    Explanation: The square root of 4 is 2, so we return 2.

    --- Example 2 ---
    Input: x = 8
    Output: 2
    Explanation: The square root of 8 is 2.82842..., and since we round it down
                 to the nearest integer, 2 is returned.


    *** Constraints ***
    1 <= x <= 2^31

*/

using namespace std;

/*
    ------------
    --- IDEA ---
    ------------

    Once we find that some number squared is greater than or equal to 'x', we
    are done.

    If squared number is exactly equal to x, then:
        return that number.

    If it's greater than x, then:
        return that number - 1;

    If x is 0, then:
        return 0.

    But it would be inefficient to start from 1 and try until we get a number
    that it's square is greater or equal to x.

    That would be O(n). That's what we've done in the Solution above.

    However, to find that "sweet spot", we can use Binary Search.

    Initialize:
        first to 1
        last  to x

    While first is less than or equal to last, do the following:

        1) Compute mid as first + (last - first) / 2.

        2) If mid * mid equals x, return mid.

        3) If mid * mid is greater than x, update last to mid - 1.

        4) If mid * mid is less than x, update first to mid + 1.

    Return last.

    Intuition behind returning last instead of first is that we didn't found
    any value that is perfect square which means now we have to return a value
    which is round of sqrt(x).

    So, we have two options :
        1. Start which is equal to mid+1 (in last iteration of while loop)
        2. Last  which is equal to mid-1 (in last iteration of while loop)

    Therefore, last is the largest integer value whose square is less than or
    equal to x, which is the closest possible approximation to the integer
    square root.

*/

/* Time  Beats:  100.00% */
/* Space Beats:   93.57% */

/* Time  Complexity: O(logN) */
/* Space Complexity: O(1) */
class Solution {
public:
    int mySqrt(int x) {
        if (x == 0)
            return 0;

        int first = 1;
        int last  = x;

        while (first <= last)
        {
            int mid = first + (last - first) / 2;

            if (mid == x / mid)
                return mid;

            if (mid > x / mid)
                last = mid - 1;
            else
                first = mid + 1;
        }

        return last;
    }
};
