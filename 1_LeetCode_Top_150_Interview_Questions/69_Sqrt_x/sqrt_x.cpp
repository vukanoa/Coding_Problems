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

    We can do a basic Binary Search, however instead of "standard" use of so
    called "Left-leaning mid", we are using "Right-Leaning mid".

    That means that if we find out that the: mid * mid, i.e. mid squared is
    STRICTLY GREATER than 'x', we're certain that all the other, higher, values
    than it are also out of question, therefore we need to EXCLUDE 'mid' by
    moving our "high" pointer.

    Right-leaning mid means that we're doing this:

        mid = low + (high - low + 1) / 2; // Right-Leaning

    Instead of Left-leaning:

        mid = low + (high - low) / 2;     // Left-Leaning


    What is the difference?
    Consider any two elements.

    With the Right-leaning mid, we're always going to pick the bigger one.
    Conversely, with the Left-leaning mid we're always going to pick the
    smaller one.

    Here we're interested in the biggest one whose square is NOT bigger than
    x, therefore we need to use the "right-leaning mid".


    Also, it's important to note that both "low" and "high" MUST be of type
    "unsigned long long". Consider:

        low  = 0, and
        high = (2^31 - 1)

    in that case we'd have an OVERFLOW were "low" and "high" basic integers.
    Thta's why they ought to be "unsigned long long".

    Or we could do some intermediate conversion such as:

        mid = low + (1ULL * high - low + 1) / 2ULL;

    But I think that this way it's more emphatic.

*/

/* Time  Beats: 100.00% */
/* Space Beats:  49.43% */

/* Time  Complexity: O(logN) */
/* Space Complexity: O(1)    */
class Solution {
public:
    int mySqrt(int x)
    {
        /* Right-leaning Lower Bound */
        unsigned long long low  = 0ULL;
        unsigned long long high = x;

        while (low < high)
        {
            // Both "low" and "high" MUST be of type "unsigned long long".
            // Consider: low = 0 and high = (2^31 - 1), in that case we'd have
            // an OVERFLOW were "low" and "high" basic integers.
            unsigned long long mid = low + (high - low + 1) / 2; // Right-Leaning

            if (mid * mid > 1LL * x)
                high = mid - 1;
            else
                low = mid;
        }

        return static_cast<int>(low); // Or "high", it does NOT matter
    }
};
