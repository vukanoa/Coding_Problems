#include <iostream>
#include <vector>
#include <algorithm>

/*
    ==============
    === MEDIUM ===
    ==============

    ===========================
    162) Find Peak Element
    ===========================

    ============
    Description:
    ============

    A peak element is an element that is strictly greater than its neighbors.

    Given a 0-indexed integer array nums, find a peak element, and return its
    index. If the array contains multiple peaks, return the index to any of the
    peaks.

    You may imagine that nums[-1] = nums[n] = -∞. In other words, an element is
    always considered to be strictly greater than a neighbor that is outside
    the array.

    You must write an algorithm that runs in O(log n) time.

    =================================================
    FUNCTION: int findPeakElement(vector<int>& nums);
    =================================================

    ==========================================================================
    ================================ EXAMPLES ================================
    ==========================================================================

    --- Example 1 ---
    Input: nums = [1,2,3,1]
    Output: 2
    Explanation: 3 is a peak element and your function should return the index
    number 2.

    --- Example 2 ---
    Input: nums = [1,2,1,3,5,6,4]
    Output: 5
    Explanation: Your function can return either index number 1 where the peak
    element is 2, or index number 5 where the peak element is 6.

    *** Constraints ***
    1 <= nums.length <= 1000
    -2^31 <= nums[i] <= 2^31 - 1
    nums[i] != nums[i + 1] for all valid i.

*/

/*
    ------------
    --- IDEA ---
    ------------

    First important consideration:

        [1, 2, 9, 2, 1, 2, 4  1, 3, 5, 6, 4]
         0  1  2  3  4  5  6  7  8  9 10 11

    Would I be able to return number 6(index 10) as a result?
    Yes!
    It DOESN'T necessarily have to be the biggest element in the entire array.

    It ONLY has to be a "peak".

    What's a peak?

    This is a peak(It's greater than both neighbors).
                |
                |
          ______|
          |
          v
          x
         / \
        x   x


    It's important to note that it's POSSIBLE that there are multiple peaks.
    We can return ANY of them. It doesn't have to be the greatest one. It can
    literally by any of them.

    Now, what if our array looks like this:
        [3, 2, 1]

    At first glance, it seems as if there are no peaks, right?

    3 is greater than its right neighbor, but it doesn't have the left
    neighbor. So can this be a peak element?

    The way they define peak elements:

        "You may imagine that nums[-1] = nums[n] = -∞. In other words, an
        element is always considered to be strictly greater than a neighbor
        that is outside the array"

    So the answer is - yes. 3 can be a peak element.
    Any value at the beginning of the array is implicitly assumed to be greater
    than its left element, since his left neighbor "doesn't exist".

    Similar is also true of the very last element in the array(i.e. 1 in our
    example).
    It's implicitly assumed for that element to be greater than its right
    neighbor, since his right neighbor "doesn't exist".

    (However 1 is not greater than its left neighbor, so it's not a peak
    element)

    Given these fact we're guaranteed that there is going to be a peak element
    in this array.

    It'd be pretty easy to find it using a linear scan, but they explicitly
    told us that we need to do it in O(log2(n)) which strongly indicated that
    we should be using a Binary Search.

    But, is it even possible to run a Binary Search on this problem?

    Well, let's go back to the first example and see what a Binary Search is as
    an algorithm.

        [1, 2, 3, 1]
         L        R

    Usually we have Left(L) and Right(R) pointer.
    We count the mid pointer with:
        M = (L + R) / 2;

    In this case:
        M = 2, but for purposes of demonstration let's say that it's: 1.

        [1, 2, 3, 1]
         L  M     R

    Is 2 greater than it's left neighbor?
        Yes.

    Is 2 greater than it's right neighbor?
        No!

    So we know for sure that this 2(at this position, maybe there are other 2's
    in the array that indeed are peak elements) isn't a peak element.

    But the idea behind a Binary Search is that we should be able to eliminate
    half of the search space every single time.

    We should be able to either say:"We know for sure that there is no solution
    on the right side of the mid pointer, so we're going to continue on the
    left side of mid pointer"

    Or we should be able to say the opposite:"We know for sure that there is no
    solution on the left side of the mid pointer, so we're going to continue on
    the right side of mid pointer"

    But we can't really say either of those things. There could be a solution
    on the left, but there could be a solution on the right or there could be
    a solution on both sides at the same time.

    So let me say this slowly:
    This is going to be a modified Binary Search, where we don't necessarily
    have to eliminate half of the search space every single time. We're just
    looking for the single peak element.

    So we just have to be sure that the side we decide to search on, whichever
    side we continue, we have to be sure that the side DOES have the peak
    element.

    Maybe there is a peak element on both sides - It doesn't matter. We JUST
    have to be sure that the side we continue on surely have at least one peak
    element.

        [1, 2, 3, 1]
         L  M     R

    So if nums[M] is NOT a peak element, how do we know which side is
    guaranteed to have a peak element?

    Let me show you a very simple example. Let's suppose that our array was
    monotonicly increasing.

    These points represent the values of our array:


                x <----------------------------------
             x <-------------------------------     |
          x < -----------------------         |     |
        x                           |         |     |
        ^                           |         |     |
        |                           |         |     |
    Is this a peak element? No.     |         |     |
                                    |         |     |
                                    |         |     |
                                    |         |     |
        ____________________________|         |     |
        |                                     |     |
    Is this a peak element? No.               |     |
                                              |     |
                                              |     |
        ______________________________________|     |
        |                                           |
    Is this a peak element? No.                     |
                                                    |
        ____________________________________________|
        |
    Is this a peak element? Yes, because it's greater than its left neighbor
                            and it doesn't have a right neighbor.

    So if we were to do a Binary Search on this array, the 2nd(at index 1)
    wouldn't be a peak element. So where do we continue? On the left or on the
    right?

    We are going to go on the righ side because even though we can't see the
    entire array(from a position of mid), we see that its right neighbor is
    greater than it, so maybe that is a peak if 4th element(index 3) is less
    than 3rd element(index 2).

    But EVEN if that is not true we're sure that at some point there HAS to be
    a peak.

    How did we conclude that?

    Okay, so mid point is NOT a peak, but its right is greater than the mid,
    okay?

    Fine, now what are the possibilities?
    1. That right's element right neighbor is less than it, therefore its a
       peak element.(Left neighbor is the mid point from which we got here).

    2. That right's element right neighbor is also greater. In that case it's
       not a peak element, but we're SURE that if we continue on the right
       there will be a peak element there.

       It's either a monotonic increasing sequence, which means that the very
       last element is a peak OR that at some point in this increasing sequence
       the right neighbor of some element is also going to be less than it.
       (left neighbor is always less than the current element in an increasing
       order).

    Try to draw out a few examples for yourself and you'll get it.

    It's important to emphasize that you DON'T have to return the BIGGEST peak
    element. It kind of "pushes" you to think like that since it has the word
    "peak" in the name of the problem. At least that was the case with me.

    So you can return ANY peak element.

*/

/* Time  Beats: 100% */
/* Space Beats: 54.62% */

/* Time  Complexity: O(log2(n)) */
/* Space Complexity: O(1) */
class Solution {
public:
    int findPeakElement(std::vector<int>& nums)
    {
        int left  = 0;
        int right = nums.size() - 1;

        while (left <= right)
        {
            // Guaranteed not to get an Overflow
            int mid = left + ((right - left) / 2);

            // Left neighbor greater
            if (mid > 0 && nums[mid] < nums[mid - 1])
                right = mid - 1;
            // Right neighbor greater
            else if (mid < nums.size() - 1 && nums[mid] < nums[mid + 1])
                left = mid + 1;
            else
                return mid;
        }

        return -1;
    }
};




/*
    ------------
    --- IDEA ---
    ------------

    Equivalent idea, but written in a more explicit, verbose way.
    It's much easier to grasp this Implementation.

*/

/* Time  Beats: 100.00% */
/* Space Beats: 35.29% */

/* Time  Complexity: O(log2(n)) */
/* Space Complexity: O(1) */
class Solution_Verbose {
public:
    int findPeakElement(vector<int>& nums)
    {
        int n = nums.size();

        int left  = 0;
        int right = n-1;

        while (left <= right)
        {
            int mid = left + (right - left) / 2;

            bool left_is_smaller  = mid-1 == -1 || nums[mid-1] < nums[mid];
            bool right_is_smaller = mid+1 ==  n || nums[mid]   > nums[mid+1];

            if (left_is_smaller && right_is_smaller)
                return mid;
            else if (left_is_smaller) // Go to the right
                left  = mid + 1;
            else // If none is smaller or the right one is smaller - Go to the left
                right = mid -1;
        }

        return -1;
    }
};




/*
    ------------
    --- IDEA ---
    ------------

    Same idea, just written a bit simpler.

*/

/* Time  Beats:  100% */
/* Space Beats: 9.30% */

/* Time  Complexity: O(log2(n)) */
/* Space Complexity: O(1) */
class Solution_Simpler_Code {
public:
    int findPeakElement(std::vector<int>& nums)
    {
        int left  = 0;
        int right = nums.size() - 1;
        int mid;

        while (left < right)
        {
            mid = (left + right) / 2;

            if (nums[mid] < nums[mid + 1])
                left  = mid + 1;
            else
                right = mid;
        }

        return left;
    }
};
