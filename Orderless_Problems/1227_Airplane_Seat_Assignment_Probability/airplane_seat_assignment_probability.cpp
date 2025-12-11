/*
    ==============
    === MEDIUM ===
    ==============

    ==========================================
    1227) Airplane Seat Assignment Probability
    ==========================================

    ============
    Description:
    ============

    n passengers board an airplane with exactly n seats. The first passenger
    has lost the ticket and picks a seat randomly. But after that, the rest of
    the passengers will:

        + Take their own seat if it is still available, and
        + Pick other seats randomly when they find their seat occupied

    Return the probability that the nth person gets his own seat.

    =============================================
    FUNCTION: double nthPersonGetsNthSeat(int n);
    =============================================

    ==========================================================================
    ================================ EXAMPLES ================================
    ==========================================================================

    --- Example 1 ---
    Input: n = 1
    Output: 1.00000
    Explanation: The first person can only get the first seat.

    --- Example 2 ---
    Input: n = 2
    Output: 0.50000
    Explanation: The second person has a probability of 0.5 to get the second
                 seat (when first person gets the first seat).


    *** Constraints ***
    1 <= n <= 10^5

*/

#include <vector>
using namespace std;

/*
    ------------
    --- IDEA ---
    ------------

    TODO
    (Not very optimal, this is a mathematical problem)

*/

/* Time  Beats: 1.93% */
/* Space Beats: 7.47% */

/* Time  Complexity: O(N) */
/* Space Complexity: O(N) */
class Solution {
public:
    double nthPersonGetsNthSeat(int n)
    {
        vector<double> dp(n);
        dp[0] = 1.0;

        for (int i = 1; i < n; i++)
            dp[i] = 1.0 / (i+1) + ((i+1 - 2.0) / (i+1)) * dp[i-1];

        return dp.back();
    }
};




/*
    ------------
    --- IDEA ---
    ------------

    TODO

*/

/* Time  Beats: 100.00% */
/* Space Beats:  87.47% */

/* Time  Complexity: O(1) */
/* Space Complexity: O(1) */
class Solution_Math {
public:
    double nthPersonGetsNthSeat(int n)
    {
        if (n == 1)
            return 1.00000;

        return 0.50000;
    }
};
