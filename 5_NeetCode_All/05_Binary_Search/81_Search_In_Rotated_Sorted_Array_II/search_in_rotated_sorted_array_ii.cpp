/*
    ==============
    === MEDIUM ===
    ==============

    =====================================
    81) Search in Rotated Sorted Array II
    =====================================

    ============
    Description:
    ============

    There is an integer array nums sorted in non-decreasing order (not
    necessarily with distinct values).

    Before being passed to your function, nums is rotated at an unknown pivot
    index k (0 <= k < nums.length) such that the resulting array is [nums[k],
    nums[k+1], ..., nums[n-1], nums[0], nums[1], ..., nums[k-1]] (0-indexed).
    For example, [0,1,2,4,4,4,5,6,6,7] might be rotated at pivot index 5 and
    become [4,5,6,6,7,0,1,2,4,4].

    Given the array nums after the rotation and an integer target, return true
    if target is in nums, or false if it is not in nums.

    You must decrease the overall operation steps as much as possible.

    Follow up: This problem is similar to Search in Rotated Sorted Array, but
               nums may contain duplicates. Would this affect the runtime
               complexity? How and why?

    =====================================================
    FUNCTION: bool search(vector<int>& nums, int target);
    =====================================================

    ==========================================================================
    ================================ EXAMPLES ================================
    ==========================================================================

    --- Example 1 ---
    Input: nums = [2,5,6,0,0,1,2], target = 0
    Output: true

    --- Example 2 ---
    Input: nums = [2,5,6,0,0,1,2], target = 3
    Output: false


    *** Constraints ***
    1 <= nums.length <= 5000
    -10^4 <= nums[i] <= 10^4
    nums is guaranteed to be rotated at some pivot.
    -10^4 <= target <= 10^4

*/

#include <vector>
using namespace std;

/*
    ------------
    --- IDEA ---
    ------------


    This one is O(N) in the WORST case, however we have still minimized the
    total number of operations by using Binary Search whenever we could.

    This is the type of Input that makes the problem:

        nums = [1,1,1,1,1,1,1,1,1,1,1,1,1,2,1,1,1,1,1]  target = 2
                                          ^
                                          |
                                          |

    The idea is to try and determine which side is sorted. If we CANNOT do that
    then simply increment "low" and decrement "high" and continue.

    This way we're making the Worst Time Complexity be: O(N), however we're
    also reducing the total number of operations by using Binary Search
    whenever we can.




    You must begin similarly to how you've approached and solved the 1st
    version of this problem - Search in Rotated Sorted Array.

    Examples that show why this problem isn't possible to do in the same way
    as the first version of this problem.

                L                       M                       R
        nums = [0,  5,  6,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0], target = 6
                0   1   2   3   4   5   6   7   8   9  10  11  12      |
                        ^                                              |
                        |______________________________________________|



                L                       M                       R
        nums = [1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  2,  1,  1], target = 2
                0   1   2   3   4   5   6   7   8   9  10  11  12      |
                                                        ^              |
                                                        |______________|



                L                       M                       R
        nums = [1,  1,  1,  3,  1,  1,  1,  1,  1,  1,  1,  1,  1], target = 3
                0   1   2   3   4   5   6   7   8   9  10  11  12      |
                            ^                                          |
                            |__________________________________________|



                L     M        R
        nums = [2, 2, 2, 1, 2, 2], target = 1
                0  1  2  3  4  5      |
                         ^            |
                         |____________|



                L     M        R
        nums = [2, 1, 2, 2, 2, 2], target = 1
                0  1  2  3  4  5      |
                   ^                  |
                   |__________________|


        Or even this:
        [8, 8, 8, 8, 8, 8] // All elements are the same and target is, say, 4.


    So, how should we approach it, then?

    This one is pretty difficult if you haven't seen it already. At the end,
    it comes down, partially, to a linear scan.

    It's important to emphasize one word in the above sentence - PARTIALLY.

    We won't have a flat O(n) Solution, we'll mostly have Time Complexity of
    O(logn), however that **won't** always be the case, therefore we must say
    our Solution is O(n) since that is the worst possible situation.

    Anyway, it will be faster, on average, than a flat O(n) Solution.


    Okay, now that we have that out of the way - How shall we approach it?

    There is another important difference with regards to the first version of
    this problem. Here we are NOT guaranteed there is a target and not only
    that, but this problem's point is to check whether there is a given target
    or not.

    Since that is the case, we won't be using a Binary Search until the "while
    loop" condition is broken and then just return the element at "left" or
    "right" pointer.

    Instead, at each calculation of "mid", i.e. at every iteration, the very
    first thing we'll always check is whether nums[mid] is equal to our desired
    target value.

    If that is NOT the case, then we need to think.

    In the first version of this problem we've been checking whether we are in
    the left or in the right part of the rotated sorted array.

    We've been checking that with:

        *** If to the left of index "mid" is the LOWER part of the rotation ***
        if (nums[left] < nums[mid])

        (Actually we did if (nums[mid] > nums[right]), but it doesn't make much
         difference which do you check first. This (nums[mid] > nums[right])
         checks if to the right of "mid" is the LOWER part of the rotation)



        *** If to the left of index "mid" is the UPPER part of the rotation ***
        else if (nums[left] > nums[mid])

        (In 1st version, this was just an "else" branch, but here we must be
         explicit, you'll see why)


    First, let's consider that the left of index "mid" is the LOWER part of the
    rotation. (Notice that that DOESN'T mean that the left part starts with a
    pivot)

        Examples:
                    L        M        R
            nums = [4, 5, 6, 7, 1, 2, 2] // Left of "mid" is LOWER part
                    0  1  2  3  4  5  6

                    L        M        R
            nums = [2, 4, 5, 6, 7, 1, 2] // Left of "mid" is LOWER part
                    0  1  2  3  4  5  6

            Neither of these two examples, as you can see, guarantees that the
            LOWER part starts with the pivot(the lowest element BEFORE the
            rotation).

            However it means that left of "mid" all the elements are in
            non-decreasing order.

            For the sake of simplicity, I like to think of non-decreasing as:
                "Increasing with some, or all, duplicate values"

            I don't know why, but it's much easier for me to visualize what's
            going on.

            It's important to say that the left part of "mid" CAN start with
            the pivot, however since that is NOT guaranteed, we cannot rely on
            that.


    Now, let's say this is our example:
                    L        M        R
            nums = [3, 5, 6, 7, 1, 2, 2] // Left of "mid" is LOWER part
                    0  1  2  3  4  5  6

            target = 4

    Since left of "mid" is the LOWER part of the rotation, we can check if our
    desired "target" is between [nums[left], nums[mid])
                                ^                     ^
                                |                     |
                                |                     |
                             Inclusive            NON-Inclusive

    "nums[mid]" is NON-Inclusive because if the target was equal to nums[mid],
    we would've returned true since, as you may remember or not, we've said
    the very first thing we'll ALWAYS do is check if(nums[mid] == target).

    If that was NOT the case, then, now, we don't have to include "nums[mid]".

    If our "target" is indeed within this value range:

                               [nums[left], nums[mid])
                               ^                     ^
                               |                     |
                               |                     |
                            Inclusive            NON-Inclusive

    Then we should move "right" pointer to mid-1.
    Else we should move "left"  pointer to mid+1.



    However, if the left part of "mid" was not LOWER, but UPPER part of the
    rotation, then we'd do something very similar. First, we'd check if our
    target is within this range:

                               (nums[mid], nums[right]]
                               ^                      ^
                               |                      |
                               |                      |
                            NON-Inclusive          Inclusive

    (It's the opposite value range)

    If target is indeed within that range then move "left"  pointer to mid+1.
    If target is NOT    within that range then move "right" pointer to mid-1.


    However, this is the CRUX of this Solution, IF WE ARE NOT ABLE TO TELL
    WHETHER THE LEFT SIDE OF "MID" IS THE LOWER OR THE UPPER PART OF THE
    ROTATION, THEN WE MUST MOVE OUR "left" POINTER TO THE RIGHT BY ONE.
    (This is what makes is Linear, i.e. O(n))

    else
    {
        left++;
    }

    Example:

                L                       M                       R
        nums = [1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  2,  1,  1], target = 2
                0   1   2   3   4   5   6   7   8   9  10  11  12      |
                                                        ^              |
                                                        |______________|


        if (nums[mid] == target) // NOT true

        if (nums[left] < nums[mid]) // NOT true

        if (nums[left] > nums[mid]) // NOT true

    So, what do we do then?

    WE INCREMENT OUR "left" POINTER BY 1.

         else
             left++;

    That is exactly what makes this Solution O(n) in the worst time. However,
    that will NOT always be the case, therefore it's still efficient since it
    will run O(logn) in many cases.

*/

/* Time  Beats: 100.00% */
/* Space Beats:  72.82% */

/* Time  Complexity: O(N) */ // O(logn) on average
/* Space Complexity: O(1) */
class Solution {
public:
    bool search(vector<int>& nums, int target)
    {
        const int N = nums.size();

        int low  = 0;
        int high = N - 1;

        while (low <= high)
        {
            int mid = low + (high - low) / 2;

            if (target == nums[mid])
                return true;

            if (nums[low] < nums[mid])
            {
                if (nums[low] <= target && target < nums[mid])
                    high = mid - 1;
                else
                    low  = mid + 1;
            }
            else if (nums[low] > nums[mid])
            {
                if (nums[mid] < target && target <= nums[high])
                    low  = mid + 1;
                else
                    high = mid - 1;
            }
            else
                low++; // This makes it O(N)
        }

        return false;
    }
};




/*
    ------------
    --- IDEA ---
    ------------

    This is absolutely equivalent to the above Solution, however in these types
    of problems where it's "touchy", it's always beneficial to look at the
    problem(and implementations) from slightly different angles.

    It's much better to see at least 2 Solutions than to the see only the one
    "perfect" one from the outset, especially if you didn't know how to do it.


    Also, both Solutions are indeed O(N), however we have still reduced the
    total number of operations since we're doing a Binary Search whenever we
    can.

    This is the type of Input that makes the problem:

        nums = [1,1,1,1,1,1,1,1,1,1,1,1,1,2,1,1,1,1,1]  target = 2
                                          ^
                                          |
                                          |

    The idea is to try and determine which side is sorted. If we CANNOT do that
    then simply increment "low" and decrement "high" and continue.

    This way we're making the Worst Time Complexity be: O(N), however we're
    also reducing the total number of operations by using Binary Search
    whenever we can.

*/

/* Time  Beats: 100.00% */
/* Space Beats:  89.60% */

/* Time  Complexity: O(N) */ // O(logn) on average
/* Space Complexity: O(1) */
class Solution_2 {
public:
    bool search(vector<int>& nums, int target)
    {
        const int N = nums.size();
        
        int low  = 0;
        int high = N-1;
        
        while (low <= high)
        {
            int mid = low + (high - low) / 2;
            
            if (nums[mid] == target)
                return true;
            
            // If we CANNOT determine which side is sorted
            if (nums[low] == nums[mid] && nums[mid] == nums[high])
            {
                low++;  // Increment
                high--; // Decrement

                continue;
            }
            
            if (nums[low] <= nums[mid]) // Left side is sorted
            {
                if (nums[low] <= target && target < nums[mid])
                    high = mid - 1;  // Target is in sorted left half
                else
                    low  = mid + 1; // Target is in right half
            }
            else // Right side is sorted
            {
                if (nums[mid] < target && target <= nums[high])
                    low  = mid + 1; // Target is in sorted right half
                else
                    high = mid - 1; // Target is in left half
            }
        }
        
        return false;
    }
};
