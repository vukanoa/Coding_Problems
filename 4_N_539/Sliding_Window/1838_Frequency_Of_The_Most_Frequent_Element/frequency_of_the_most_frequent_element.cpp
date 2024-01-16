#include <iostream>
#include <vector>
#include <algorithm>

/*
    ==============
    === MEDIUM ===
    ==============

    ============================================
    1838) Frequency of the Most Frequent Element
    ============================================

    ============
    Description:
    ============

    The frequency of an element is the number of times it occurs in an array.

    You are given an integer array nums and an integer k. In one operation, you
    can choose an index of nums and increment the element at that index by 1.

    Return the maximum possible frequency of an element after performing at
    most k operations.

    =====================================================
    FUNCTION: int maxFrequency(vector<int>& nums, int k);
    =====================================================

    ==========================================================================
    ================================ EXAMPLES ================================
    ==========================================================================

    --- Example 1 ---
    Input: nums = [1,2,4], k = 5
    Output: 3
    Explanation: Increment the first element three times and the second element
                 two times to make nums = [4,4,4].  4 has a frequency of 3.


    --- Example 2 ---
    Input: nums = [1,4,8,13], k = 5
    Output: 2
    Explanation: There are multiple optimal solutions:
    - Increment the first element three times to make nums = [4,4,8,13]. 4 has
      a frequency of 2.
    - Increment the second element four times to make nums = [1,8,8,13]. 8 has
      a frequency of 2.
    - Increment the third element five times to make nums = [1,4,13,13]. 13 has
      a frequency of 2.


    --- Example 3 ---
    Input: nums = [3,9,6], k = 2
    Output: 1


    *** Constraints ***
    1 <= nums.length <= 10^5
    1 <= nums[i] <= 10^5
    1 <= k <= 10^5

*/

/*
    ------------
    --- IDEA ---
    ------------

    Let's consider this example:
        nums = [1, 4, 2, 1, 2, 1], k = 2
                0  1  2  3  4  5

    How can we even begin to solve this problem?
    Well, the very first, but obvious, thing to notice is this - We CANNOT
    decrease values.

    As I've said, that seems obvious, but why did I bring it up?

    We know that to find a Solution, we need to check how many elements can we
    "convert" to a current element for which we're checking that.

    By "convert" I mean increase and that is the precise reason I said:"We
    CANNOT decrease values".

    So, now we know two things:
        1. We are going to check, for each element in the array individually,
           how many of the remaining elements can we increase to match the
           current element.

        2. We CANNOT decrease elements.


    Let's say that, currently, we're checking the element 2 at index 4.
                                                                 |
                            --------------------------------------
                            |
                            V
        nums = [1, 4, 2, 1, 2, 1], k = 2
                0  1  2  3  4  5

    All the other elements are "the remaining elements".
    (Once we exclude the curent one from the entire array, all the rest are
    considered remaining)

    In the for loop, when checking the current element, we have to consider all
    the remaining ones and see how many can we increase to match the current
    element we're checking.

    If we do that in a Brute Force way, we'd end up with O(n^2) Time Complexity
    Solution, which is inefficient.

    That's another reason why I brought up that we CANNOT decrease values.
    Since we CANNOT decrease values, we, technically, don't even need to check
    the remaining elements that are greater than the element for which we are
    doing this check-up, aka "the current element".

    Since we DO NOT have to even consider elements that are greater than the
    "current element", the important question is this - Is there a way we can
    exclude elements that are greater than the "current element"?

    Yes, there is. By sorting the elements we can just not consider the
    elements to the right of the "current element", for which we are doing this
    check-up.


    Now that we have that out of the way, let's try to determine how can we
    know what is the maximum subarray(well, subset really, but since we've
    sorted the array, now we're checking subarrays) that we can "make"
    considering the given value k which represents the permissible extent of
    increments we can undertake in order to match the "current element".

    (Again, remember that we do not consider the elements greater than the
    "current element", i.e. elements to the right, because we CANNOT decrease
    elements)

    Since we do NOT consider elements to the right, that means we only check
    the remaining elements that are left of the "current element".

    After sorting, our original example looks like this:
        nums = [1, 1, 1, 2, 2, 4], k = 2
                0  1  2  3  4  5

    If the "current element" was element 2 at index 3, we are checking how many
    elements to the left can we convert(increase) to match "the current
    element" i.e. value 2.

    How can we check that?

    We are going to be using a "Sliding Window" technique.

        nums = [1, 1, 1, 2, 2, 4], k = 2
                0  1  2  3  4  5
                L        R

    As long as this window is INVALID, we are going to keep moving the "left"
    pointer to the right.

    How can we know if a certain window is valid?

    Since we want to make all the elements in this window equal to the "current
    element", i.e. value 2, then we want to see if it is possible to "increase"
    all the remaining ones within the window to match value "current element".

    (in other words we want to see if it is possible to "increase" all the
     elements left of the "current element" to match the value "current
     element")

    We must NOT forget that we can only "increase" at max k times.

    So for window to be valid we need to have the entire window be consisted of
    the "current element" values, in other words - the sum of the current
    window will be "current element"(value 2) * the size of the current window.

    We want to turn this:

                |           |
                |           |
        nums = [|1, 1, 1, 2,| 2, 4], k = 2
                |0  1  2  3 | 4  5
                |L        R |
                |           |
    to this:    |           |
                |           |
        nums = [|2, 2, 2, 2,| 2, 4], k = 2
                |0  1  2  3 | 4  5
                |L        R |
                |           |

    And the question is - Is that possible? Can we do that? Do we have enough
                          "patches"? Is k big enough?

    Let me get to the point - In order for our window to be valid, we want to
    be able to make sum of:

        window_len * current_element.

    Currently, the sum of our window is: 1 + 1 + 1 + 2 = 5
    And, additionally, we have k "patches".

    In order to say that our window is valid, we have to be able to make our
    window sum up to: window_len * current_element.

    Currently, our window sum is 5, but we can "patch" k more, which gives us:
        5 + 2 = 7

    Is ((2 * 4) < (5 + 2))?
    Is (8 < 7)?

    No, it's not.

    That means our window is INVALID.
    To make it valid, we have to move our "left" pointer and, again, check if
    this condition is true.

    However, before we move our "left" pointer to the right, we must decrease
    the sum of our current window by nums[left] since now our window is
    shrinked. It doesn't contain the "left" element anymore.

    Now we check again:

    Can we turn this:

                  |         |
                  |         |
        nums = [1,| 1, 1, 2,| 2, 4], k = 2
                0 | 1  2  3 | 4  5
                  | L     R |
                  |         |
    to this:      |         |
                  |         |
        nums = [1,| 2, 2, 2,| 2, 4], k = 2
                0 | 1  2  3 | 4  5
                  | L     R |
                  |         |


    Is ((2 * 3) <= (4 + 2))?
    Is (6 <= 6)?

    Yes, it is. Therefore, our window is VALID.

    Since our window is VALID, we can try to see if this window_len is the new
    maximum length:

            max_freq = std::max(max_freq, right - left + 1);

    // window_len = right - left + 1;


    We begin by having both "left" and "right" pointers initialized at 0 and if
    the current window is VALID, then just do this:

        max_freq = std::max(max_freq, right - left + 1);

    and move "right" pointer by one:

        right++;


    If it is INVALID, then keep shinkring the window until it becomes VALID,
    again.

    When shrinking the window, you MUST decrease sum of the currnet window by
    the leftmost element of the current window.

    As you can see, we need "sum of the current window" in every iteration,
    thus we'll have a variable "curr_window_sum" to represent exactly that.

    Once the window becomes VALID again, do this:

        max_freq = std::max(max_freq, right - left + 1);

    and move "right" pointer by one:

        right++;


    As you can see, we're doing these last two lines at each iteration.

    ***************
    *** SUMMARY ***
    ***************

    window_len = right - left + 1;

    Valid Window:
        (nums[right] * (right - left + 1)) <= (curr_window_sum + k)

    Invalid Window:
        (nums[right] * (right - left + 1)) >  (curr_window_sum + k)

*/

/* Time  Beats: 74.28% */
/* Space Beats: 77.02% */

/* Time  Complexity: O(n * logn) */
/* Space Complexity: O(1)        */ // Or O(n) depending on the sort

using ULL = unsigned long long;

class Solution {
public:
    int maxFrequency(std::vector<int>& nums, int k)
    {
        std::sort(nums.begin(), nums.end());
        int max_freq = 0;

        int left  = 0;
        int right = 0;

        unsigned long long curr_window_sum = 0;
        while (right < nums.size())
        {
            curr_window_sum += nums[right];

            while ((ULL)((ULL)nums[right] * (ULL)(right - left + 1)) > (ULL)(curr_window_sum + k)) // while Invalid Window
                curr_window_sum -= nums[left++];

            max_freq = std::max(max_freq, right - left + 1);
            right++;
        }

        return max_freq;
    }
};
