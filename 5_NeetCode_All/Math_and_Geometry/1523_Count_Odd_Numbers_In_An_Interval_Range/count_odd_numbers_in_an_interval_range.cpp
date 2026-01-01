#include <iostream>

/*
    ==============
    === MEDIUM ===
    ==============

    ============================================
    1523) Count Odd Numbers in an Interval Range
    ============================================

    ============
    Description:
    ============

    Given two non-negative integers low and high. Return the count of odd
    numbers between low and high (inclusive).

    ===========================================
    FUNCTION: int countOdds(int low, int high);
    ===========================================

    ==========================================================================
    ================================ EXAMPLES ================================
    ==========================================================================

    --- Example 1 ---
    Input: low = 3, high = 7
    Output: 3
    Explanation: The odd numbers between 3 and 7 are [3,5,7].

    --- Example 2 ---
    Input: low = 8, high = 10
    Output: 1
    Explanation: The odd numbers between 8 and 10 are [9].

    *** Constraints ***
    0 <= low <= high <= 10^9

*/

/*
    ------------
    --- IDEA ---
    ------------

    *****************
    *** Intuition ***
    *****************

    Ask yourself - How many odd numbers are there in a given range?

    You'll quickly realize that, obviously, it depends. But what does it depend
    on?

    Let's pick a random range and start from there.

    3 - 7 (i.e. {3, 4, 5, 6, 7})     There are 3 Odd numbers
    2 - 6 (i.e. {2, 3, 4, 5, 6})     There are 2 Odd numbers
    1 - 4 (i.e. {1, 2, 3, 4})        There are 2 Odd numbers
    2 - 5 (i.e. {2, 3, 4, 5})        There are 2 Odd numbers


    Is there any pattern we can notice so that we don't have to go through all
    the elements?

    The thing that makes this tricky is that we're starting at arbitrary point
    and we're ending at arbitrary point.

    Look at these first two examples:

    // Odd number of total elements
    3 - 7 (i.e. {3, 4, 5, 6, 7})     There are 3 Odd numbers
    2 - 6 (i.e. {2, 3, 4, 5, 6})     There are 2 Odd numbers

    There are 5 elements in each case, however there is one more Odd number in
    the first range. Why is that the case?

    That's the case because both starting and the ending point is an Odd number
    and the total number of elements is odd.

    In the second case, we also have odd number of total elements, however this
    time both starting an the ending point is an even number.

    // Even number of total elements
    1 - 4 (i.e. {1, 2, 3, 4})        There are 2 Odd numbers
    2 - 5 (i.e. {2, 3, 4, 5})        There are 2 Odd numbers

    Here, no matter if we start at Odd or Even, number, we'll always have even
    number of Odd elements, i.e. we can just take the total amount of elements
    and divide by 2 and get the result.

    So, to summarize:
        If the total amount of elements in the range:
            i.e. (high - low + 1)
        is an EVEN number, then all we have to do is divide that number by 2.

        Check if yourself. Take any range with EVEN number of elements in it
        and count the Odd numbers, you'll always see that there are EVEN number
        of Odd elements.


        However, on the other hand, if there are ODD number of elements, then
        we must check if the starting element(i.e. the first element in the
        range) is either Odd or Even element.

        If it's an Odd starting element, we have to add 1 to the previously
        calculated: total_number_of_elements / 2.

        If it's an Even starting element, we don't have to do anything, we can
        just return previously calculated: total_number_of_elements / 2.


    Also, don't overlook the fact that the total number of elements is always:
        high - low + 1

    Do NOT forget "+ 1", otherwise you won't consider all the elements.

    If, say, the range is 3 - 7, if you count the total number of elements as:
        high - low

    and forget the "+ 1", then you'd consider only these:

    You WOULDN'T consider this one
        _______________________|
        |
        |
        |
        |
        |  ______________
        v  |
        3, | 4, 5, 6, 7
           |_____________
                    ^
                    |
                    |__________
                              |
                              |
    You would consider only THESE


    To fix this problem, you must add "+ 1", i.e. total number of elements is:
        high - low + 1


        ________________
        |
        | 3, 4, 5, 6, 7
        |_______________
               ^
               |
               |_________________
                                |
                                |
    Now you'd consider all of them

*/

/* Time  Beats: 100.00% */
/* Space Beats: 18.37%  */

/* Time  Complexity: O(1) */
/* Space Complexity: O(1) */
class Solution {
public:
    int countOdds(int low, int high)
    {
        int length = high - low + 1;
        int result = length / 2;

        if (length & 1 && low & 1)
            result++;

        return result;
    }
};
