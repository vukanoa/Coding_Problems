#include <iostream>
#include <vector>
#include <climits>

/*
    ==============
    === MEDIUM ===
    ==============

    ===========================
    8) String to Integer (atoi)
    ===========================

    ============
    Description:
    ============

    Implement the myAtoi(string s) function, which converts a string to a
    32-bit signed integer(similar to C/C++'s atoi function).

    The algorithm for myAtoi(string s) is as follows:

    Read in and ignore any leading whitespace.

    Check if the next character(if not already at the end of the string) is
    '-' or '+'. Read this character in if it is either. This determines if the
    final result is negative or positive respectively. Assume the result is
    positive if neither is present.

    Read in next the characters until the next non-digit character or the end
    of the input is reached. The rest of the string is ignored.

    Convert these digits into an integer(i.r. "123" -> 123, "0032" -> 32). If
    no digits were read, then the integer is 0. Change the sign as necessary
    (from step 2).

    If integer is out of the 32-bit signed integer range [-2^31, 2^31 - 1],
    then clamp the integer so that it remains in the range. Specifically,
    integer less than -2^31 should be clamped to -2^31, and integers greater
    than 2^31 - 1 should be clamped to 2^31 - 1.

    Return the integer as the final result.

    =====
    Node:
    =====

    - Only the space character ' ' is considered a whitespace character.
    - Do NOT ignore any characters other than the leading whitespace or the
      rest of the string after the digits.

    ===============================
    FUNCTION: int myAtoi(string s);
    ===============================

    ==========================================================================
    ================================ EXAMPLES ================================
    ==========================================================================

    --- Example 1 ---
    Input:  s = "42"
    Output: 42

    --- Example 2 ---
    Input:  s = "    -42"
    Output: -42

    --- Example 3 ---
    Input:  s = "4193 with words"
    Output: 4193

    *** Constraints ***
    0 <= s.length <= 200
    s consists of English Letters(lower-case and upper-case), digits(0-9), ' ',
    '+', '-', and '.'.
*/


/*
    ------------
    --- IDEA ---
    ------------

    ASCII values

    48 -> 0
    49 -> 1
    50 -> 2
    51 -> 3
    52 -> 4
    53 -> 5
    54 -> 6
    55 -> 7
    56 -> 8
    57 -> 9

    If the String begins with leading whitespaces - iterate to first
    not-whitespace or to the very last element.

    check if first non-whitespace character is:
        1. Either '-'
        2. Or '+'
        4. Or digit

    If it's a '-' set flag "negative" to true and move to next character.

    While we're on a digit in the String s, fill the vector "number" with them.
    Only the first consecutive digits after:
        1. Optional leading zeroes(whitespaces)
        2. Optional arithmetic sign
        3. Consecutive digits(until we reach end or whitespace)

    Since s[i] is a character we subtract '0'(ASCII 48) from it just so we
    can push that number in std::vector<int>.

    Now we iterate until we have poccessed all the elements in number's vector.

    The part in if's is just lke the previous problem 07_Reverse_integer
    if "integer" is greater than:
        INT_MAX / 10
    then multiplying by 10 and adding any integer causes Overflow.

    On the other hand, if it is exactly:
        INT_MAX / 10
    then Overflow is caused only if number[i] > 7
    However, even if it's exactly INT_MAX or greater than INT_MAX - return
    INT_MAX in both cases.

    That means that if "integer" is greater than:
        INT_MAX / 10
    return INT_MAX

    or if "integer" is equal to exactly:
        INT_MAX / 10
    and number[i] >=7 // if it's exactly 7 then that's INT_MAX already
    returning INT_MAX either way.

    However if "integer" is less than INT_MAX / 10 then check if:
        integer >= ((INT_MAX / 10) + number[i])
    if it is then return INT_MAX.

    Check similar things but for INT_MIN.

    And at the end of our "for loop" we ask if our original number is
    negative or not and "construct the 'integer' based on previous value.
    (always tens digit)

    And at the very end just return that constructed integer.

*/

/* Time  Beats: 100% */
/* Time  Beats: 9.56% */

/* Time  Complexity: O(n) */
/* Space Complexity: O(n) */
class Solution{
public:
    int myAtoi(const std::string& s)
    {
        std::vector<int> number;

        int  integer  = 0;
        bool negative = false;

        int i = 0;
        while (s[i] == ' ')
            i++;

        if (s[i] == '-')
        {
            negative = true;
            i++;
        }
        else if (s[i] == '+')
            i++;

        // While it's a digit
        while (i < s.length() && s[i] >= 48 && s[i] <= 57)
            number.push_back(s[i++] - '0');

        for (int i = 0; i < number.size(); i++)
        {
            if ((integer > INT_MAX / 10) || (integer == INT_MAX / 10 && number[i] >= 7))
                return INT_MAX;
            else if ((integer < INT_MIN / 10) || (integer == INT_MIN / 10 && number[i] >= 8))
                return INT_MIN;

            if (negative)
                integer = integer * 10 - number[i];
            else
                integer = integer * 10 + number[i];
        }

        return integer;
    }
};

int
main()
{
    Solution sol;

    /* Example 1 */
    // string s = "42";

    /* Example 2 */
    // string s = "   42";

    /* Example 3 */
    // string s = "   -42";

    /* Example 4 */
    // string s = "   -42with words";

    /* Example 5 */
    // string s = "4193 with words";

    /* Example 6 */
    // string s = "0032";
    // int num = sol.myAtoi(s);

    /* Example 7 */
    // string s = "2147483647";

    /* Example 8 */
    // string s = "-2147483648";

    /* Example 9 */
    std::string s = "2147483646";

    int num = sol.myAtoi(s);
    std::cout << "\n\t================================";
    std::cout << "\n\t=== STRING TO INTEGER (ATOI) ===";
    std::cout << "\n\t=================================\n";

    /* Solution */
    num = sol.myAtoi(s);

    std::cout << "\n\tString \"" << s << "\" converted is " << num << "\n\n";

    return 0;
}
