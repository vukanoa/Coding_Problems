/*
    ==============
    === MEDIUM ===
    ==============

    ====================================
    2523) Closest Prime Numbers in Range
    ====================================

    ============
    Description:
    ============

    Given two positive integers left and right, find the two integers num1 and
    num2 such that:

        + left <= num1 < num2 <= right .

        + Both num1 and num2 are

        num2 - num1 is the minimum amongst all other pairs satisfying the above
        conditions.

    Return the positive integer array ans = [num1, num2]. If there are multiple
    pairs satisfying these conditions, return the one with the smallest num1
    value. If no such numbers exist, return [-1, -1].

    =========================================================
    FUNCTION: vector<int> closestPrimes(int left, int right);
    =========================================================

    ==========================================================================
    ================================ EXAMPLES ================================
    ==========================================================================

    --- Example 1 ---
    Input: left = 10, right = 19
    Output: [11,13]
    Explanation: The prime numbers between 10 and 19 are 11, 13, 17, and 19.
                 The closest gap between any pair is 2, which can be achieved
                 by [11,13] or [17,19]. Since 11 is smaller than 17, we return
                 the first pair.

    --- Example 2 ---
    Input: left = 4, right = 6
    Output: [-1,-1]
    Explanation: There exists only one prime number in the given range, so the
                 conditions cannot be satisfied.


    *** Constraints ***
    1 <= left <= right <= 10^6

*/

#include <climits>
#include <cmath>
#include <vector>
using namespace std;

/*
    ------------
    --- IDEA ---
    ------------

    If you know "Sieve of Eratosthenes", then this problem becomes trivial.
    Otherwise, you almost have no chance.

    So it really depends on whether you do know it.
    Here's the explanation of it.

    Sieve of Eratosthenes

    1   2   3   4   5   6                  __  2   3   _   5   _
    7   8   9  10  11  12                  7   _   _  __  11  __
    13 14  15  16  17  18                  13 __  __  __  17  __
    19 20  21  22  23  24                  19 __  __  __  23  __
    25 26  27  28  29  30                  __ __  __  __  29  __
    31 32  33  34  35  36    Cross out     31 __  __  __  __  __
    37 38  39  40  41  42    NON-primes    37 __  __  __  41  __
    43 44  45  46  47  48   ---------->    43 __  __  __  47  __
    49 50  51  52  53  54                  __ __  __  __  53  __
    55 56  57  58  59  60                  55 __  __  __  59  __
    61 62  63  64  65  66                  61 __  __  __  __  __
    67 68  69  70  71  72                  67 __  __  __  71  __
    73 74  75  76  77  78                  73 __  __  __  __  __
    79 80  81  82  83  84                  79 __  __  __  83  __
    85 86  87  88  89  90                  __ __  __  __  89  __
    91 92  93  94  95  96                  91 __  __  __  __  __
    97 98  99 100                          97 __  __ ___


    (If you group numbers in 6 columns like above, "crossing out" will be much
     easier. Try to go step-by-step through the steps in Algorithm and you'll
     see what I''m talking about)

    What is a definition of "Prime" and "Composite" number?

        Prime: A number greater than 1 that HAS EXACTLY TWO FACTORS, 1 & itself
    Composite: A number greater than 1 that HAS MORE THAN TWO factors.

    *********************************
    **** Algorithm goes like this ***
    *********************************

    1) Cross out 1 (Neither "prime", nor "composite")

    2) Cross out first non-crossed out number and cross out all of the numbers
       it divides

    3) Repeat step 2 up until SQRT(final_num)   // final_num=100 in our case



    In this example, we've used final_num=100, but we could've used ANY number.

    "Sieve of Eratosthenes" is the most efficient way to determine all the
    prime numbers up until desired final_num.

    There is no more efficient way to do this.

    In order to determine if some number is a prime or not, you would have to
    layout all the numbers from [1, desired_final_num] and then "cross out" all
    the numbers that are NOT primes.

    The efficiency comes from this fact:
    To cross out all NON-primes in range [1, desired_final_num], you do NOT
    have to go through all [1, desired_final_num] numbers, instead you can go
    only from [1, sqrt(desired_final_num)].

    This is unintuitive, but we can proove this inductively.


    Consider desired_final_num = 2017.

        44 < sqrt(2017) < sqrt(2025) < 45

    Which means that sqrt(2017) is a little bigger than 44, but less than 45.
    Now we take all the prime numbers up until 44, i.e. sqrt(final_num):

        2, 3, 5, 7, 11, 13, 17, 19, 23, 29, 31, 37, 41, 43

    Now we check if final_num=2017 is divisible by any of these PRIME numbers.
    If it is NOT, then we are CERTAIN that 2017 is a PRIME number itself.

    But how do we know we can go up to sqrt(final_num)?
    Let's proove it:


    Let's write some number "num", as d * k(i.e. "divisor" * k)

        num = d * k     (d, n/d)   where we are forcing that: d <= n/d

    Let's take some example "num", say, 12.
    We can write it in our (d, n/d) form:

        (1, 12/1) <==> (1, 12)
        (2, 12/2) <==> (2,  6)
        (3, 12/3) <==> (3,  4)

    And we stop here. Why? Because if we were to continue, we'd have:

        (4, 12/4) <==> (4,  3)

    But we've already had this "composition", this pair.
    It doesn't matter if it's:

        3 * 4 = 12, or
        4 * 3 = 12

    After we find the first pair that repeats, we don't include that repeated
    pair and we STOP because after it we would keep finding pairs that we have
    already processed:


        (4, 12/4) <==> (4,  3)
                                 // 5  is NOT a divisor of 12
        (6, 12/6) <==> (6,  2)
                                 // 7  is NOT a divisor of 12
                                 // 8  is NOT a divisor of 12
                                 // 9  is NOT a divisor of 12
                                 // 10 is NOT a divisor of 12
                                 // 11 is NOT a divisor of 12
        (12, 12/12) <==> (12, 1)

    See?
    We get pairs that we've already processed. But why is that?

    It's because:

        NUM / SMALLER_DIVISOR = GREATER_DIVISOR
        NUM / GREATER_DIVISOR = SMALLER_DIVISOR

    And since that is true, we should stop when we start getting same pairs
    over and over again.

    And when is that "focal point"?
    It's at sqrt(final_num)

    Why?
    Because:
        NUM / SAME_DIVISOR = SAME_DIVISOR

    After that it's CERTAIN that we'll have:
        NUM / GREATER_DIVISOR = SMALLER_DIVISOR

    Which we've just explained we have already processed.

    To prove it mathematically:

        num = d * k     (d, n/d)   where we are forcing that: d <= n/d

        Since: d <= n/d  --->   d^2 < n   --->   d < sqrt(n)

    And that is the precise reason we're having that.
    d will be LESS THAN sqrt(n), after that we would start having pairs that we
    have already processed and since we want to save time and not have double
    work, we stop at sqrt(n).

*/

/* Time  Beats: 77.04% */
/* Space Beats: 74.07% */

/* Time  Complexity: O(R * loglogR + R - L) */
/* Space Complexity: O(R)                   */
class Solution {
public:
    vector<int> closestPrimes(int left, int right)
    {
        vector<int> result = {-1,-1};

        vector<bool> prime(right + 1, true);
        prime[0] = false;
        prime[1] = false;

        // Sieve of Eratosthenes: O(N log log N)
        for (int num = 2; num <= sqrt(right); num++)
        {
            if (num >= left)
                break;

            if ( ! prime[num])
                continue;

            for (int i = num; i <= right; i += num)
                prime[i] = false;
        }

        int smallest_diff = INT_MAX;
        int last = -1;

        for (int num = left; num <= right; num++)
        {
            if ( ! prime[num])
                continue;

            if (last != -1)
            {
                if (num - last < smallest_diff)
                {
                    smallest_diff = num - last;

                    result[0] = last;
                    result[1] = num;
                }
            }

            last = num;
        }

        return result;
    }
};
