#include <iostream>
#include <climits>

/*
    ==============
    === MEDIUM ===
    ==============

    ==================
    7) Reverse Integer
    ==================

    ============
    Description:
    ============

    Given a signed 32-bit integer x, return x with its digits reversed.
    If reversing x causes the value to go outside the signed 32-bit integer
    range [-2^31, 2^31 - 1], then return 0;

    =====
    Note: Assume the environment does not allow you to store 64-bit integers (signed or unsigned)
    =====

    ==========================================================================
    ================================ EXAMPLES ================================
    ==========================================================================

    --- Example 1 ---
    Input: x = 123
    Output: 321

    --- Example 2 ---
    Input: x = -123
    Ouput: -321

    --- Example 3 ---
    Input: x = 120
    Output: 21

    *** Constraints ***
    -2^31 <= x <= 2^31 - 1
*/


/*
    INT_MAX =  2147483647
    INT_MIN = -2147483648
*/


/*
    ------------
    --- IDEA ---
    ------------

    It is self-explanatory for cases other than edge cases.

    Conisder this:

    x = 2147483647 // INT_MAX

    We'll have this:

  1   |      x       |      tmp     |     result     |
  2   |  2147483647  |  0           |  0             |
  3   |  214748364   |  7           |  7             |
  4   |  21474836    |  74          |  74            |
  5   |  2147483     |  746         |  746           |
  6   |  214748      |  7463        |  7463          |
  7   |  21474       |  74638       |  74638         |
  8   |  2147        |  746384      |  746384        |
  9   |  214         |  7463847     |  7463847       |
  10  |  21          |  74638474    |  74638474      |
  11  |  2           |  746384741   |  746384741     |
  12  |              |  5555555555  |                |
                        ^
                        |
    random value --------

  So when we are at Iteration 11:
    tmp = 746384741

  If we multiply by 10 and add last_digit, it will Overflow. So how do we
  check that?

  Since result variable has the same values in each iteration as variable "tmp"
  once we do multiply by 10 and add last_digit(of x) we then check if
  doing mirror operations('-' for '+', '/' for '*') on variable "tmp", that is:
    (tmp - last_digit) and then DIVIDE by 10

  If it's the same value as in the varible "result" then there is no Overflow.
  On the other hand, if simply doing mirror operations gives us another
  value then that certainly means an Overflow happened so we return 0.

*/

/* Time  Complexity: O(n) */
/* Space Complexity: O(1) */
class Solution{
public:
    int reverse(int x)
    {
        int tmp    = 0;
        int result = 0;

        while (x != 0)
        {
            int last_digit = x % 10;
            tmp = result * 10 + last_digit; // This

            /* Checking for the Overflow */
            // Doing a reverse operation from the previous(This) line
            if ((tmp - last_digit) / 10 != result)
                return 0;

            result = tmp;
            x = x / 10;
        }

        return result;
    }
};




/*
    ------------
    --- IDEA ---
    ------------

    --- Solution ---
    It is self-explanatory for cases other than edge cases.

    Consider this:

    x = 2147483647 // INT_MAX

    Only this part is important:
        // Exceeded 32-bit range
        if (rev > (INT_MAX / 10) || rev > ((INT_MAX / 10) + number % 10))
            return 0;

    So, why are we doing this? Or how exactly and why this works?

    INT_MAX =  2147483647

    and we check if out reversed integer variable "rev":
        if (rev > (INT_MAX) / 10)

    Why?
    (INT_MAX) / 10 = 214748364;

    Imagine if rev was greater than this value.
    Imagine:
        rev = 2147483642;

    If we werent' to return 0 because of an upcoming Overflow, what would've
    happened?

    Well, Overflow, of course, but how?

    2147483642 * 10 + ANY_NUMBER is GUARANTEED to be overflowed.

    Simply multiplying 2147483642 by 10 is already an Overflow.

    However if "rev" is not bigger than 2147483642 then, assume we have this:
        rev = 214748363

    rev * 10 = 214783630 which is still less than INT_MAX
    and adding ANY_DIGIT is guaranteed not to cause an Overflow.

    However if our "rev" is EXACTLY (INT_MAX / 10), meaning:
        rev = 21474864

    Then we have to check if the last_digit + rev is going to be greater
    than:
        INT_MAX % 10

    INT_MAX % 10 == 7

    so if our variable "rev":
        rev = 21474864
    and we add either {0, 1, 2, 3, 4, 5, 6, 7} then we're good. There is no
    Overflow.

    If last_digit is greater than 7 and "rev" is 21474864 then that will
    cause an Overflow.

*/


/* Time  Beats: 100% */
/* Space Beats: 65.36% */
/* Time  Complexity: O(n) */
/* Space Complexity: O(1) */
class Solution_Efficient {
public:
    int reverse(int x)
    {
        // If it was 1Byte then -8 can exist, but 8 cannot
        if (x == INT_MIN)
            return 0;

        bool neg = x < 0;
        if (neg)
            x *= -1;

        int rev = 0;
        while (x != 0)
        {
            // Exceeded 32-bit range
            if (rev > INT_MAX / 10 || ( (rev == INT_MAX) && (rev > 7) ) )
                return 0;

            rev = rev * 10 + x % 10;
            x /= 10;
        }

        return neg ? -1 * rev : rev;
    }
};


int
main()
{
    Solution sol;
    Solution_Efficient sol_efficient;

    // int number =  123;
    // int number = -123;
    // int number =  120;
    // int number = -120;
    int number = -2147483412;
    // int number =  2147483647; // INT_MAX
    // int number = -2147483648; // INT_MIN

    std::cout << "\n\t=======================";
    std::cout << "\n\t=== REVERSE INTEGER ===";
    std::cout << "\n\t=======================\n";


    /* Write Input */
    std::cout << "\n\tOriginal number: " << number << "\n";

    /* Solution */
    // int rev = sol.reverse(number);
    int rev = sol_efficient.reverse(number);

    /* Write Output */
    std::cout << "\n\tReversed number: " << rev << "\n\n";

    return 0;
}
