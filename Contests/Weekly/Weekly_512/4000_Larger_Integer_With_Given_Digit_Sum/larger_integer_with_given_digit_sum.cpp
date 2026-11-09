/*
    ============
    === EASY ===
    ============

    =========================================
    4000) Larger Integer With Given Digit Sum
    =========================================

    ============
    Description:
    ============

    You are given two non-negative integers n and s.

    Return the largest integer that has at most n digits and whose sum of
    digits is s. If no such integer exists, return -1.

    ===========================================
    FUNCTION: int largestInteger(int n, int s);
    ===========================================

    ==========================================================================
    ================================ EXAMPLES ================================
    ==========================================================================

    --- Example 1 ---
    Input: n = 2, s = 9
    Output: 90
    Explanation:
    The largest integer with at most 2 digits that has a sum of digits of 9 is
    90.

    --- Example 2 ---
    Input: n = 2, s = 19
    Output: -1
    Explanation:
    There is no integer with at most 2 digits that has a sum of digits of 19,
    so the answer is -1.

    --- Example 3 ---
    Input: n = 5, s = 0
    Output: 0
    Explanation:
    The only non-negative integer whose digits sum to 0 is 0.


    *** Constraints ***
    1 <= n <= 5
    0 <= s <= 100

*/

#include <cmath>
#include <string>
using namespace std;

/*
    ------------
    --- IDEA ---
    ------------

    Allowed by the Constraints.

*/

/* Time  Beats: 14.76% */
/* Space Beats: 12.02% */

/* Time  Complexity: O(10^n * n) */
/* Space Complexity: O(1)        */
class Solution {
public:
    int largestInteger(int n, int s)
    {
        int result = pow(10, n) - 1;

        while (result >= 0)
        {
            int tmp = result;

            int sum = 0;
            while (tmp > 0)
            {
                int digit = tmp % 10;
                sum += digit;
                
                tmp /= 10;
            }

            if (sum == s)
                return result;

            --result;
        }

        return -1;
    }
};




/*
    ------------
    --- IDEA ---
    ------------

    TODO

*/

/* Time  Beats: 100.00% */
/* Space Beats:  79.64% */

/* Time  Complexity: O(n) */
/* Space Complexity: O(n) */
class Solution_Greedy {
public:
    int largestInteger(int n, int s)
    {
        if (9*n < s)
            return -1;

        if (s == 0)
            return 0;

        string str = "";

        while (n > 0)
        {
            int digit = min(9, s);
            str += static_cast<char>(digit + '0');

            s -= digit;

            // Decrement
            --n;
        }

        return stoi(str);
    }
};




/*
    ------------
    --- IDEA ---
    ------------

    TODO

*/

/* Time  Beats: 100.00% */
/* Space Beats:  79.64% */

/* Time  Complexity: O(n) */
/* Space Complexity: O(1) */
class Solution_Greedy_2 {
public:
    int largestInteger(int n, int s)
    {
        int result = 0;

        while (n > 0)
        {
            int digit = min(9, s);
            s -= digit;

            result = result*10 + digit;

            // Decrement
            --n;
        }

        if (s > 0)
            return -1;

        return result;
    }
};




/*
    ------------
    --- IDEA ---
    ------------

    TODO

*/

/* Time  Beats: 100.00% */
/* Space Beats:  53.84% */

/* Time  Complexity: O(1) */
/* Space Complexity: O(1) */
class Solution_Constant {
private:
    static constexpr int pow[] = {0, 1, 10, 100, 1000, 10000, 100000};

public:
    int largestInteger(int n, int s)
    {
        if (n*9 < s)
            return -1;

        auto [quotient, remainder] = div(s, 9);        
        return pow[n + 1] - pow[n - quotient + 1] + remainder * pow[n - quotient];
    }
};
