#include <iostream>
#include <vector>

/*
    ==============
    === MEDIUM ===
    ==============

    ===========================
    665) Non-decreasing Array
    ===========================

    ============
    Description:
    ============

    Given an array nums with n integers, your task is to check if it could
    become non-decreasing by modifying at most one element.

    We define an array is non-decreasing if nums[i] <= nums[i + 1] holds for
    every i (0-based) such that (0 <= i <= n - 2).

    ==============================================
    FUNCTION: checkPossibility(vector<int>& nums);
    ==============================================

    ==========================================================================
    ================================ EXAMPLES ================================
    ==========================================================================

    --- Example 1 ---
    Input: nums = [4,2,3]
    Output: true
    Explanation: You could modify the first 4 to 1 to get a non-decreasing
                 array.


    --- Example 2 ---
    Input: nums = [4,2,1]
    Output: false
    Explanation: You cannot get a non-decreasing array by modifying at most one
                 element.


    *** Constraints ***
    n == nums.length
    1 <= n <= 10^4
    -10^5 <= nums[i] <= 10^5

*/


/*
    ------------
    --- IDEA ---
    ------------

    We have variable "decreasing" because there can be at most 1 decrease in
    the entire array.

    However that's not the only thing we have to worry about. Consider these
    examples:

        [3, 4, 2, 3]

    You would think that, maybe, this can be considered valid, since there is
    only one decrease in this array. However, since the decrease happens at
    index 1(number 4), if we change it to be less than the number at index 2
    (which happens to be 2 in this case), then we would end up with:

        [3, 1, 2, 3]

    Is this array valid? No!

    So we cannot only check if there are more than 1 decreases, we must check
    if the number BEFORE the decrease(number 3 at index 0 in this case) is
    GREATER than the lower number in that decrease.

        [3, 4, 2, 3]
         B  i  x

    B - BEFORE the decrease
    i - The number we're on when we found out that we have a decrease
    x - The lower number in this found decrease

    So we have to check if 'B' is greater than 'x'.
    IF it is, then whatever we change our 'i' to, it doesn't matter, the array
    will certainly be invalid, therefore we'd return false.

    However, we must not jump to conclusion that this is all there is. Consider
    this Example:
        [5, 7, 1, 8]
         B  i  x

    'B" is greater than 'x', however we should NOT return false. Why?
    Well, we could modify 'x', instead of 'i'. What if we modified 'x' from 1
    to 7. Now we'd have:

        [5, 7, 7, 8]
         B  i  x

    Now this is valid.

    So, what additional checkup should we have if we find out that 'B' > 'x'.

        [5, 7, 1, 8]
         B  i  x

    We've explained why this is valid. We can change 7 to 1 and that would be
    valid. But why?
    This is important, because the number to the right of number 'x' is 8 which
    is greater than 7 in which we are modifying our current 'x'.

    However, we could be at the end of the array, what would we do then?

        [5, 7, 1]
         B  i  x

    Again, it's the same as if we had 8 after 'x', therefore this is valid as
    well.

    So when is an array NOT valid?

    Now check:
        1) If the current 'i' decreases at the next number.

        2) If 'B'(denoted as "prev" in the code) is greater
           than 'i'(denotes as "nums[i + 1]" in the code).

        3) If element to the right of 'x' exists AND if that element is LESS
           THAN number 'i'(denotes as "nums[i]" in the code).

    If all 3 of these conditions are true, we can say that say that it's
    impossible to make a non-decereasing array by modifying only one element.

    Also we return false if there are more than 1 decreases.

*/

/* Time  Beats: 89.59% */
/* Space Beats: 36.28% */

/* Time  Complexity: O(n) */
/* Space Complexity: O(1) */
class Solution {
public:
    bool checkPossibility(std::vector<int>& nums)
    {
        if (nums.size() == 1)
            return true;

        int prev = -1e5 - 1; // Constraints
        int decreasing = 0;
        for (int i = 0; i <= nums.size() - 2; i++)
        {
            if (nums[i] > nums[i+1])
            {
                if (prev > nums[i+1])
                {
                    if (prev > nums[i] || (i+2 < nums.size() && nums[i] > nums[i+2]))
                        return false;
                }

                decreasing++;
            }

            prev = nums[i];
        }

        return decreasing <= 1;
    }
};




/*
    ------------
    --- IDEA ---
    ------------

    TODO

*/

/* Time  Beats: 70.06% */
/* Space Beats: 10.44% */

/* Time  Complexity: O(n) */
/* Space Complexity: O(1) */
class Solution {
public:
    bool checkPossibility(vector<int>& nums)
    {
        for (int i = 0; i < nums.size()-1; i++)
        {
            if (nums[i] > nums[i+1])
            {
                if (i-1 >= 0 && nums[i-1] > nums[i+1])
                    nums[i+1] = nums[i];
                else
                    nums[i] = nums[i+1];

                break;
            }
        }

        for (int i = 0; i < nums.size()-1; i++)
        {
            if (nums[i] > nums[i+1])
                return false;
        }

        return true;
    }
};
