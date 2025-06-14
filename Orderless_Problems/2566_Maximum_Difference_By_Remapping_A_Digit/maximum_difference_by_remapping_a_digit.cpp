/*
    ============
    === EASY ===
    ============

    =============================================
    2566) Maximum Difference by Remapping a Digit
    =============================================

    ============
    Description:
    ============

    You are given an integer num. You know that Bob will sneakily remap one of
    the 10 possible digits (0 to 9) to another digit.

    Return the difference between the maximum and minimum values Bob can make
    by remapping exactly one digit in num.

    Notes:
        + When Bob remaps a digit d1 to another digit d2, Bob replaces all
          occurrences of d1 in num with d2.

        + Bob can remap a digit to itself, in which case num does not change.

        + Bob can remap different digits for obtaining minimum and maximum
          values respectively.

        + The resulting number after remapping can contain leading zeroes.

    ========================================
    FUNCTION: int minMaxDifference(int num);
    ========================================

    ==========================================================================
    ================================ EXAMPLES ================================
    ==========================================================================

    --- Example 1 ---
    Input: num = 11891
    Output: 99009
    Explanation:
    To achieve the maximum value, Bob can remap the digit 1 to the digit 9 to yield 99899.
    To achieve the minimum value, Bob can remap the digit 1 to the digit 0, yielding 890.
    The difference between these two numbers is 99009.

    --- Example 2 ---
    Input: num = 90
    Output: 99
    Explanation:
    The maximum value that can be returned by the function is 99 (if 0 is
    replaced by 9) and the minimum value that can be returned by the function
    is 0 (if 9 is replaced by 0).
    Thus, we return 99.


    *** Constraints ***
    1 <= num <= 10^8

*/

#include <algorithm>
#include <vector>
using namespace std;

/*
    ------------
    --- IDEA ---
    ------------

    To make a number minimal, we have to make all the occurences of digit[0],
    i.e. leftmost digit, we need to make them 0.

    Why?

    Any number you have, say:

        233455533

    No matter how many occurrences of other digits are there, you will NEVER
    have a smaller number than if you make the FIRST digit 0, because you're
    getting a number that is 10 times smaller.

        122222

        022222 is 10 times smaller than our original 122222

    If you try to make 2's 0, then you'd have this:

        100000

    So, which one is smaller?

        022222, or
        100000

    Of course, it's 022222.


    As for the maximum number, we need to find the LEFTMOST non-9 digit and
    convert all of those into 9.

    Why?

    Because if the number begins in non-9, then increasing that to 9 will
    always be the biggest number.

        1344449
        9344449 // We cannot get any bigger number

    However, if the number is:

        9992333311
           ^

    Changing the leftmost NON-9 will result in biggest number.

        9999333311
           ^

    We just do that manually in O(N) TC and O(1) Space since 10^8 means
    the biggest number will have at most 9 digits, which is O(9) which is
    considered a Constant Space.

*/

/* Time  Beats: 100.00% */
/* Space Beats: 64.15% */

/* Time  Complexity: O(N) */
/* Space Complexity: O(1) */
class Solution {
public:
    int minMaxDifference(int num)
    {
        vector<int> vec_min;
        vector<int> vec_max;

        while (num > 0)
        {
            int digit = num % 10;
            num /= 10;

            vec_min.push_back(digit);
            vec_max.push_back(digit);
        }

        reverse(vec_min.begin(), vec_min.end());
        reverse(vec_max.begin(), vec_max.end());

        int target = vec_min[0];
        for (unsigned i = 0; i < vec_min.size(); i++)
        {
            if (vec_min[i] == target)
                vec_min[i] = 0;
        }

        target = -1;
        for (unsigned i = 0; i < vec_max.size(); i++)
        {
            if (vec_max[i] != 9)
            {
                target = vec_max[i];
                break;
            }
        }

        if (target != -1) // If there's at least one NON-9 digit in vec_max
        {
            for (unsigned i = 0; i < vec_max.size(); i++)
            {
                if (vec_max[i] == target)
                    vec_max[i] = 9;
            }
        }

        int num_min = 0;
        int num_max = 0;
        for (unsigned i = 0; i < vec_min.size(); i++)
        {
            num_min *= 10;
            num_min += vec_min[i];

            num_max *= 10;
            num_max += vec_max[i];
        }

        return num_max - num_min;
    }
};
