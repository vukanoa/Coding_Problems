#include <iostream>

/*
    ============
    === EASY ===
    ============

    ===========================
    367) Valid Perfect Square
    ===========================

    ============
    Description:
    ============

    Given a positive integer num, return true if num is a perfect square or
    false otherwise.

    A perfect square is an integer that is the square of an integer. In other
    words, it is the product of some integer with itself.

    You must not use any built-in library function, such as sqrt.

    ========================================
    FUNCTION: bool isPerfectSquare(int num);
    ========================================

    ==========================================================================
    ================================ EXAMPLES ================================
    ==========================================================================

    --- Example 1 ---
    Input: num = 16
    Output: true
    Explanation: We return true because 4 * 4 = 16 and 4 is an integer.

    --- Example 2 ---
    Input: num = 14
    Output: false
    Explanation: We return false because 3.742 * 3.742 = 14 and 3.742 is not an
                 integer.

    *** Constraints ***
    1 <= num <= 2^31 - 1

*/

/*
    ------------
    --- IDEA ---
    ------------

    "right" pointer is NON-Inclusive.

    Why did we, then, assign it to "num" and not "num + 1"?

    First, it's important to notice that, obviously "num" will never be the
    answer, meaning if we are finding which number from 1 to "num" when squared
    gives us "num".

    We cannot square "num" and get "num", right?
    There is only one edge case where that is possible: "num = 1".

    However we'll take care of that with our final return ternary operator:

        return left == 1 ? true : false;

    Now that "num = 1" is out of the way, ask yourself again - Is it possible
    to square some number from [2, num](Inclusively) that will give us a result
    of "num"?

    No, there is not.


    Second reason for not initializing our "right" pointer to "num + 1" is
    because of the "Constraints" of this problem. They clearly say:

        1 <= num <= 2^31 - 1

    So if "num" gets to be exactly 2^31 - 1, then "num + 1" will be an Overflow
    in an "int" type.

    To overcome that problem, you would think we could write this:

        unsigned left  = 1;
        unsigned right = num + 1; // This will Overflow again

    Why will this Overflow know when we are assigning it to the "unsigned"
    which can hold more than "2^31 - 1" POSITIVE values?

    Because the intermediate result is based off of the type you're adding it
    with. In this case it's type "int" because that is num's type.

    Therfore, we could overcome it like this:

        unsigned left  = 1;
        unsigned right = num;
        right++; // Now this will NOT Overflow since "right" is unsigned.

    But to avoid all of this mess, we could just assign it to "num" and not
    worry since we know that the answer will almost never be even close to
    "num".(And we've taken care of case "num = 1", remember?)

    Okay, now that is out of the way too.
    But - Is the Initial value the reason that the "right" pointer is
    NON-Inclusive?

    Great question!
    No, that is NOT the reason.

    We could also have a NON-Inclusive value at the beginning for the "left"
    pointer, but we would still, for this Solution, consider only our "right"
    pointer that is NON-Inclusive.

    Why?

    Because of the way we're calculating our "mid" pointer.

    There are 2 ways to calculate "mid" pointer:
        1. Left  leaning:   mid = left + (right - left) / 2;
        2. Right leaning:   mid = left + std::floor((right - left + 1) / 2);

    You could write "Left leaning" with std::floor as well, it wouldn't make
    any difference and it's maybe easier to visuallize the difference and
    remember it:
        1. Left  leaning:   mid = left + std::floor((right - left    ) / 2);
        2. Right leaning:   mid = left + std::floor((right - left + 1) / 2);


    Since we are using "Left leaning", that means we can decide NOT to include
    our "right" pointer's value as a possible result.

    That decision is made this way:

            if (mid * mid < num)
                left  = mid + 1;
            else
                right = mid; // Since "mid" is NOT an answer and since "right"
                             // doesn't point to a value that is a possible
                             // result, we don't have to move our "right"
                             // pointer to "mid - 1", but to "mid", since that
                             // value will not be considered as a potential
                             // result anymore.

*/

/* Time  Beats: 100.00% */
/* Space Beats:  62.03% */

/* Time  Complexity: O(logn) */
/* Space Complexity: O(1) */
class Solution {
public:
    bool isPerfectSquare(int num)
    {
        int left  = 1;
        int right = num;

        while (left < right) // Less than, because "right" is NON-Inclusive
        {
            unsigned long long mid = left + (right - left) / 2;

            if (mid * mid == num) // unsigned long long otherwise Overflow
                return true;

            if (mid * mid < num)
                left  = mid + 1;
            else
                right = mid;
        }

        return left == 1 ? true : false;
    }
};




/*
    ------------
    --- IDEA ---
    ------------

    This one is a similar idea, however this one will work for squared values
    that are even greater than "unsigned long long" since it doesn't have the
    upper bound.

    (The upper bound would is whichever type they give us for "num". The could
     use any of these and it would still work:
        #include <boost/multiprecision/cpp_int.hpp>

        using namespace boost::multiprecision;

        int128_t   num;
        uint128_t  num;
        int256_t   num;
        uint256_t  num;
        int512_t   num;
        uint512_t  num;
        int1024_t  num;
        uint1024_t num;
    )

    We are dividing "num" by "mid" and not multiplying "mid" by "mid" as
    in the previous Solution.

    Also, here, I've written a Binary Search in a slightly different way.
    Initially both "left" and "right" point to elements that COULD be answers,
    whereas the above Solution doesn't. (In the above Solution "right" pointer
    points to a value that CANNOT be a result)

    In the above Solution our range was: [left, right)
                                         ^           ^
                                         |           |
                                    Inclusive     NON-Inclusive


    However, in this Solution, both "left" and "right" point to values that
    could, in theory, be the answer we are looking for.

    Therefore, our range is always like this [left, right]
                                             ^           ^
                                             |           |
                                          Inclusive    Inclusive


    Because our range is Inclusive on both pointers, our while loop has this
    condition:

        while (left <= right) // Less than OR EQUALS TO

    The "OR EQUALS TO" part is precisely because both "left" and "right" are
    both Inclusive.

    In the above Solution, since our "right" pointer was NOT Inclusive, we had
    a while loop with this condition:

        while (left < right) // Less than, because "right" is NON-Inslusive


    One more thing differs because of our Initialization values - In this
    Solution our if-else pair looks like this:

            if (1.0*mid < num_div_mid)
                left  = mid + 1;
            else
                right = mid - 1;

    Since we either have to move our "left" or our "right" pointer and since
    BOTH "left" and "right are pointing to Inclusive values, we MUST exclude
    the "mid" value since we've just concluded that "mid" is NOT the answer.

    However, in the above Solution, we had this:

            if (mid * mid < num)
                left = mid + 1;
            else
                right = mid;     // Because "right" is NON-Inclusive


    Also, in both Solutions we are using "Left leaning" calculation of "mid"
    pointer.

    As explained above, we could calculate "mid" pointer in two ways:
        1. Left  leaning:   mid = left + (right - left) / 2;
        2. Right leaning:   mid = left + std::floor((right - left + 1) / 2);

    You could write "Left leaning" with std::floor as well, it wouldn't make
    any difference and it's maybe easier to visuallize the difference and
    remember it:
        1. Left  leaning:   mid = left + std::floor((right - left    ) / 2);
        2. Right leaning:   mid = left + std::floor((right - left + 1) / 2);

*/

/* Time  Beats: 100.00% */
/* Space Beats:  13.40% */

/* Time  Complexity: O(logn) */
/* Space Complexity: O(1)    */
class Solution_2 {
public:
    bool isPerfectSquare(int num)
    {
        int left  = 1;
        int right = num;

        while (left <= right)
        {
            int mid = left + (right - left) / 2; // Left leaning

            double num_div_mid = 1.0 * num / mid;

            if (1.0*mid == num_div_mid)
                return true;

            if (1.0*mid < num_div_mid)
                left  = mid + 1;
            else
                right = mid - 1;
        }

        return false;
    }
};
