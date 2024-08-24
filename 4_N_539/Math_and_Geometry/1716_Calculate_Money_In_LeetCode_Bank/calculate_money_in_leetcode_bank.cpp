#include <iostream>

/*
    ============
    === EASY ===
    ============

    ======================================
    1716) Calculate Money in LeetCode Bank
    ======================================

    ============
    Description:
    ============

    Hercy wants to save money for his first car. He puts money in the Leetcode
    bank every day.

    He starts by putting in $1 on Monday, the first day. Every day from Tuesday
    to Sunday, he will put in $1 more than the day before. On every subsequent
    Monday, he will put in $1 more than the previous Monday.

    Given n, return the total amount of money he will have in the Leetcode bank
    at the end of the nth day.

    ===============================
    FUNCTION: int totalMoney(int n);
    ===============================

    ==========================================================================
    ================================ EXAMPLES ================================
    ==========================================================================

    --- Example 1 ---
    Input: n = 4
    Output: 10
    Explanation: After the 4th day, the total is 1 + 2 + 3 + 4 = 10.


    --- Example 2 ---
    Input: n = 10
    Output: 37
    Explanation: After the 10th day, the total is (1 + 2 + 3 + 4 + 5 + 6 + 7) +
                 (2 + 3 + 4) = 37. Notice that on the 2nd Monday, Hercy only
                 puts in $2.


    --- Example 3 ---
    Input: n = 20
    Output: 96
    Explanation: After the 20th day, the total is (1 + 2 + 3 + 4 + 5 + 6 + 7) +
                 (2 + 3 + 4 + 5 + 6 + 7 + 8) + (3 + 4 + 5 + 6 + 7 + 8) = 96


    *** Constraints ***
    1 <= n <= 1000

*/

using namespace std;

/*
    ------------
    --- IDEA ---
    ------------

    TODO

*/

/* Time  Beats: 28.12% */
/* Space Beats:  7.00% */

/* Time  Complexity: O(n) */
/* Space Complexity: O(1) */
class Solution {
public:
    int totalMoney(int n)
    {
        // 1 + 2 + 3 + 4 + 5 + 6 + 7 = 28
        // 2 + 3 + 4 + 5 + 6 + 7 + 8 = 28 + 7 = 35
        // 3 + 4 + 5 + 6 + 7 + 8 + 9 = 35 + 7 = 42

        int day = 0;
        int deposit = 1;
        int result = 0;

        while (day < n)
        {
            result += deposit;

            deposit++;
            day++;

            if (day % 7 == 0)
                deposit = day / 7 + 1;
        }

        return result;
    }
};




/*
    ------------
    --- IDEA ---
    ------------

    TODO

*/

/* Time  Beats: 28.12% */
/* Space Beats: 71.44% */

/* Time  Complexity: O(1) */
/* Space Complexity: O(1) */
class Solution_Formula {
public:
    int totalMoney(int n)
    {
        int weeks = n / 7;

        int low  = 28;
        int high = 28 + 7 * (weeks - 1);

        int result = weeks * (low + high) / 2;

        for (int i = 0; i < n % 7; i++)
            result += i + (weeks + 1);

        return result;
    }
};
