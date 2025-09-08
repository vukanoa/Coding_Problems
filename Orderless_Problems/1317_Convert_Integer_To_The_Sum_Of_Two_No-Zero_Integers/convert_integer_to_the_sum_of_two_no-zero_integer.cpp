/*
    ============
    === EASY ===
    ============

    ========================================================
    1317) Convert Integer to the Sum of Two No-Zero Integers
    ========================================================

    ============
    Description:
    ============

    No-Zero integer is a positive integer that does not contain any 0 in its
    decimal representation.

    Given an integer n, return a list of two integers [a, b] where:

        a and b are No-Zero integers.
        a + b = n

    The test cases are generated so that there is at least one valid solution.
    If there are many valid solutions, you can return any of them.

    ===============================================
    FUNCTION: vector<int> getNoZeroIntegers(int n);
    ===============================================

    ==========================================================================
    ================================ EXAMPLES ================================
    ==========================================================================

    --- Example 1 ---
    Input: n = 2
    Output: [1,1]
    Explanation: Let a = 1 and b = 1.
    Both a and b are no-zero integers, and a + b = 2 = n.

    --- Example 2 ---
    Input: n = 11
    Output: [2,9]
    Explanation: Let a = 2 and b = 9.
    Both a and b are no-zero integers, and a + b = 11 = n.
    Note that there are other valid answers as [8, 3] that can be accepted.


    *** Constraints ***
    2 <= n <= 10^4

*/

#include <string>
#include <vector>
using namespace std;

/*
    ------------
    --- IDEA ---
    ------------

    Self explanatory.

*/

/* Time  Beats: 8.39% */
/* Space Beats: 6.51% */

/* Time  Complexity: O(N) */ // Because each string is at max of length 5
/* Space Complexity: O(1) */ // Because each string is at max of length 5
class Solution {
public:
    vector<int> getNoZeroIntegers(int n)
    {

        for (int i = 1; i <= n/2; i++)
        {
            int one = i;
            int two = n - i;

            string str_one = to_string(one);
            string str_two = to_string(two);

            if (str_one.find("0") == string::npos &&
                str_two.find("0") == string::npos)
            {
                return {i, n - i};
            }
        }

        return {};
    }
};
