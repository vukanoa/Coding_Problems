/*
    ==============
    === MEDIUM ===
    ==============

    ===========================================
    1304) Find N Unique Integers Sum Up To Zero
    ===========================================

    ============
    Description:
    ============

    Given an integer n, return any array containing n unique integers such that
    they add up to 0.

    =====================================
    FUNCTION: vector<int> sumZero(int n);
    =====================================

    ==========================================================================
    ================================ EXAMPLES ================================
    ==========================================================================

    --- Example 1 ---
    Input: n = 5
    Output: [-7,-1,1,3,4]
    Explanation: These arrays also are accepted [-5,-1,1,2,3] , [-3,-1,2,-2,4].

    --- Example 2 ---
    Input: n = 3
    Output: [-1,0,1]

    --- Example 3 ---
    Input: n = 1
    Output: [0]

    *** Constraints ***
    1 <= n <= 1000

*/

#include <numeric>
#include <vector>
using namespace std;

/*
    ------------
    --- IDEA ---
    ------------

    Since elements do NOT have to to be sorted, we add:
        1. One positive
        2. One negative(opposite of the positive)

    If the 'n' is ODD, then we need to push an additional 0.

*/

/* Time  Beats: 100% */
/* Space Beats: 14.57% */

/* Time  Complexity: O(N) */
/* Space Complexity: O(N) */ // Auxiliary Space Complexity O(1)
class Solution {
public:
    vector<int> sumZero(int n)
    {
        vector<int> result;
        for (int i = 0; i < n/2; i++)
        {
            result.push_back(i + 1);
            result.push_back(-1 * (i + 1));
        }

        if (n & 1)
            result.push_back(0);

        return result;
    }
};




/*
    ------------
    --- IDEA ---
    ------------

    Begin from -(n/2) and go up until, including, n/2.

    If 'n' is an EVEN number, then skip adding 0 along the way.

*/

/* Time  Beats: 100.00% */
/* Space Beats:  83.69% */

/* Time  Complexity: O(N) */
/* Space Complexity: O(N) */ // Auxiliary Space Complexity O(1)
class Solution_2 {
public:
    vector<int> sumZero(int n)
    {
        if (n == 1)
            return {0};

        vector<int> result;
        for (int i = -1 * (n/2); i <= n/2; i++)
        {
            if (i == 0 && n % 2 == 0)
                continue;

            result.push_back(i);
        }

        return result;
    }
};




/*
    ------------
    --- IDEA ---
    ------------

    Almost equivalent to the above Solution_2, however implemented using C++'s
    IOTA function.

    If you're not familiar with ti:

        iota(result.begin(), result.end(), 0); // Produces: [0, 1, 2, ... n-1]
        iota(result.begin(), result.end(), 1); // Produces: [1, 1, 2, ... n  ]

    Therefore, we fill first n/2 elements starting from -(n/2).
    Then we will the second half, i.e. from (n/2)th element, starting from 1.

*/

/* Time  Beats: 100.00% */
/* Space Beats:  83.69% */

/* Time  Complexity: O(N) */
/* Space Complexity: O(N) */ // Auxiliary Space Complexity O(1)
class Solution_IOTA {
public:
    vector<int> sumZero(int n)
    {
        vector<int> result(n);

        if (n % 2 == 0) // Even case
        {
            iota(result.begin()      , result.begin() + n/2, -n/2);
            iota(result.begin() + n/2, result.end()        ,   1 );
        }
        else // Odd case: put 0 in the middle
        {
            result[n / 2] = 0;

            iota(result.begin()          , result.begin() + n/2, -n/2);
            iota(result.begin() + n/2 + 1, result.end()        ,   1 );
        }

        return result;
    }
};




/*
    ------------
    --- IDEA ---
    ------------

    Same as above, but this one is MUCH more concise. We're taking care of the
    ODD case by initializing "result" with all 0s.

    The once we get to filling the second half, we do that by only doing the
    last n/2 elements, and starting from 1.

    That way we don't have to take care of Odd and Even case separate.y

*/

/* Time  Beats: 100.00% */
/* Space Beats:  83.69% */

/* Time  Complexity: O(N) */
/* Space Complexity: O(N) */ // Auxiliary Space Complexity O(1)
class Solution_IOTA_Concise {
public:
    vector<int> sumZero(int n)
    {
        vector<int> result(n, 0); // Important for ODD values of 'n'

        iota(result.begin()    , result.begin() + n/2, -n/2); // First  n/2
        iota(result.end() - n/2, result.end()        ,    1); // Second n/2

        return result;
    }
};
