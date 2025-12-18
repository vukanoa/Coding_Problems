/*
    ==============
    === MEDIUM ===
    ==============

    ===========================
    3765) Complete Prime Number
    ===========================

    ============
    Description:
    ============


    You are given an integer num. A number num is called a Complete Prime
    Number if every prefix and every suffix of num is prime.

    Return true if num is a Complete Prime Number, otherwise return false.

    Note:
        + A prefix of a number is formed by the first k digits of the number.

        + A suffix of a number is formed by the last k digits of the number.

        + Single-digit numbers are considered Complete Prime Numbers only if
          they are prime.

    ======================================
    FUNCTION: bool completePrime(int num);
    ======================================

    ==========================================================================
    ================================ EXAMPLES ================================
    ==========================================================================

    --- Example 1 ---
    Input: num = 23
    Output: true
    Explanation:
        Prefixes of num = 23 are 2 and 23, both are prime.
        Suffixes of num = 23 are 3 and 23, both are prime.
        All prefixes and suffixes are prime, so 23 is a Complete Prime Number
        and the answer is true.

    --- Example 2 ---
    Input: num = 39
    Output: false
    Explanation:
        Prefixes of num = 39 are 3 and 39. 3 is prime, but 39 is not prime.
        Suffixes of num = 39 are 9 and 39. Both 9 and 39 are not prime.
        At least one prefix or suffix is not prime, so 39 is not a Complete
        Prime Number and the answer is false.

    --- Example 3 ---
    Input: num = 7
    Output: true
    Explanation: 7 is prime, so all its prefixes and suffixes are prime and the
                 answer is true.


    *** Constraints ***
    1 <= num <= 10^9

*/

/*
    ------------
    --- IDEA ---
    ------------

    TODO

*/

/* Time  Beats: 100.00% */
/* Space Beats: 99.98% */

/* Time  Complexity: O(D^2) */ // D == number of digits in num
/* Space Complexity: O(1)   */
class Solution {
public:
    bool completePrime(int num)
    {
        int remaining_number = num;
        int curr_prefix      = 0;
        int multiplier       = 1;

        while (remaining_number > 0)
        {
            curr_prefix = multiplier * (remaining_number % 10) + curr_prefix;

            if (curr_prefix == 1 || !is_prime(curr_prefix))
                return false;

            if (remaining_number == 1 || ! is_prime(remaining_number))
                return false;

            remaining_number /= 10; 
            multiplier       *= 10;
        }   

        return true;
    }

private:
    bool is_prime(int num)
    {
        if (num <= 1)
            return false;

        for (int factor = 2; factor * factor <= num; factor++)
        {
            if (num % factor == 0)
                return false;
        }

        return true;
    }
};
