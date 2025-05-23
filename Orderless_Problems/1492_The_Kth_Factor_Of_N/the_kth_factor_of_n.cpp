#include <iostream>
#include <vector>
#include <cmath>

/*
    ==============
    === MEDIUM ===
    ==============

    ===========================
    1492) The kth Factor of n
    ===========================

    ============
    Description:
    ============

    You are given two positive integers n and k. A factor of an integer n is
    defined as an integer i where n % i == 0.

    Consider a list of all factors of n sorted in ascending order, return the
    kth factor in this list or return -1 if n has less than k factors.


    =================
    === Follow Up ===
    =================

        Could you solve this problem in less than O(n) complexity?



    ======================================
    FUNCTION: int kthFactor(int n, int k);
    ======================================

    ==========================================================================
    ================================ EXAMPLES ================================
    ==========================================================================

    --- Example 1 ---
    Input: n = 12, k = 3
    Output: 3
    Explanation: Factors list is [1, 2, 3, 4, 6, 12], the 3rd factor is 3.

    --- Example 2 ---
    Input: n = 7, k = 2
    Output: 7
    Explanation: Factors list is [1, 7], the 2nd factor is 7.

    --- Example 3 ---
    Input: n = 4, k = 4
    Output: -1
    Explanation: Factors list is [1, 2, 4], there is only 3 factors. We should
                 return -1.


    *** Constraints ***
    1 <= k <= n <= 1000

*/

/*
    ------------
    --- IDEA ---
    ------------

    The most intuitive idea ever.

*/

/* Time  Beats:  8.02% */
/* Space Beats: 80.85% */

/* Time  Complexity: O(n) */
/* Space Complexity: O(1) */
class Solution_Naive_Approach {
public:
    int kthFactor(int n, int k)
    {
        vector<int> factors;
        for (int i = 1; i <= n; i++)
        {
            if (n % i == 0)
                factors.push_back(i);
        }

        if (factors.size() < k)
            return -1;

        return factors[k-1];
    }
};





/*
    ------------
    --- IDEA ---
    ------------

    Short Explanation:

        Let's assume n is 12. The divisors of n are: {1, 2, 3, 4, 6, 12}. But
        now look at them from another angle:

        1 * 12 = 12
        2 * 6  = 12
        3 * 4  = 12

        If i is a divisor of n, then n / i is a divisor of n as well.
        Consequently, we can find all the divisors of n only by processing the
        numbers that are smaller or equal to the square root of n.



    Long Explanation:

        Let's divide all the divisors of n into 2 parts:

        divisors smaller than the square root of n
        divisors bigger than the square root of n. 

    Note: There's an edge case when the square root of n is an integer (for
          example when n is 9 or 16) which we'll discuss later.


    FIrst for loop

        We start at 1 and check every number to see whether or not it's a
        divisor of n. If it is, we deduct one from k (because we found one of
        the k divisors we were looking for). Then continue until we reach the
        square root of n.  If during this process k becomes 0, it means that we
        have successfully found the first k divisors of n. So we can jump for
        joy, cheer loudly, and return the current number. 



    Second for loop

        Otherwise, we will continue from the square root of n and go down to 1.
        However, this time, instead of checking if the current number (i) is a
        divisor of n (something that we have already checked), we check if n/i
        is a divisor of n. If k becomes zero, we do what we are supposed to do.
        Please don't forget to make noise.

    Note for person who will comment: "n % i == 0 and n % (n/i) == 0 has the
    same results." I know :) but it's easier to understand.


    Edge case

        When the square root of n is an integer. We want to make sure that, on
        the one hand, we don't forget to count it, and on the other hand we
        don't count it twice. 


    Here's the trick: we don't count it in the first for loop: i <
    Math.sqrt(n). 

    For the second for loop we start from: int i = (int) Math.sqrt(n).If the
    square root of n is an integer, i will be the square root. For example, if
    n is 9, i will start from 3. Otherwise, it will be floored to the first
    integer. For example, if n is 8, the square root is 2.8 so i will be 2.

    If after all those efforts k is still bigger than zero, we return -1.

*/

/* Time  Beats: 100.00% */
/* Space Beats:  45.99% */

/* Time  Complexity: O(sqrt(n)) */
/* Space Complexity: O(1)       */
class Solution_Efficient {
public:
    int kthFactor(int n, int k)
    {
        for (int i = 1; i < std::sqrt(n); ++i)
        {
            if (n % i == 0 && --k == 0)
                return i;
        }

        for (int i = static_cast<int>(std::sqrt(n)); i >= 1; --i)
        {
            if (n % (n / i) == 0 && --k == 0)
                return n / i;
        }

        return -1;
    }
};
