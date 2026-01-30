/*
    ==============
    === MEDIUM ===
    ==============

    =========================================
    153) Find Minimum in Rotated Sorted Array
    =========================================

    ============
    Description:
    ============

    Suppose an array of length "n" sorted in ascending order is rotated between
    1 and n times. For ecample, the array "nums" = [0, 1, 2, 4, 5, 6, 7] might
    become:
        [4, 5, 6, 7, 0, 1, 2] if it was rotated 4 times
        [0, 1, 2, 4, 5, 6, 7] if it was rotated 7 times

    Notice that rotating an array [a[0], a[1], a[2], ..., a[n-1]] 1 time
    results in the array [a[n-1], a[0], a[1], a[2], ..., a[n-2]].

    Given the sorted rotated array "nums" of unique elements, return the
    minimum element of this array.

    You must write an algorithm that runs in O(log n) time.

    =========================================
    FUNCTION: int findMin(vector<int>& nums);
    =========================================

    ==========================================================================
    ================================ EXAMPLES ================================
    ==========================================================================

    --- Example 1 ---
    Input:  nums = [3, 4, 5, 1, 2]
    Output: 1

    --- Example 2 ---
    Input:  nums = [4, 5, 6, 7, 0, 1, 2]
    Output: 0

    --- Example 3 ---
    Input:  [11, 13, 15, 17]
    Output: 11

    *** Constraints ***
    n = nums.length
    1 <= n <= 5000
    -5000 <= nums[i] <= 5000
    All the integers of "nums" are unique.
    "nums" is sorted and rotated between 1 and n times.

*/

#include <vector>
using namespace std;

/*
    ------------
    --- IDEA ---
    ------------

    This is how you find the Pivot in a Rotated Sorted array.
    This is by far the simplest Solution.

    Consider all the rotations from 1-7, inclusive.

        1 2 3 4 5 6 7
        7 1 2 3 4 5 6
        6 7 1 2 3 4 5
        5 6 7 1 2 3 4
        4 5 6 7 1 2 3
        3 4 5 6 7 1 2
        2 3 4 5 6 7 1

    Since we're required to write an O(logN) Solution, that means we must
    write a Binary Search.

    So let's try and see if we can find a pattern where to move based on our
    "mid".

            1 2 3 4 5 6 7
            7 1 2 3 4 5 6
            6 7 1 2 3 4 5
            5 6 7 1 2 3 4
            4 5 6 7 1 2 3
            3 4 5 6 7 1 2
            2 3 4 5 6 7 1
            ^     ^     ^
            |     |     |
            |     |     |
       low --    mid    -- high

    For all of these rotations, can we notice some pattern? How can we be SURE
    that we can remove either of the side from consideration?

    It's actually pretty simple.

    If an element in the middle of the current range is SMALLER THAN the
    element at index "high"(i.e. the right one), then we can be CERTAIN that
    NONE of the elements from [mid+1, high] will be the answer, since we're
    asked to return the SMALLEST value from the array.

    Since nums[mid] is SMALLER than nums[high], then nums[mid] is also smaller
    than:
        nums[mid+1], nums[mid+2], ..., nums[high-1], nums[high]

    Right?
    And that is because the array is SORTED and then rotated.

    So if element at the "mid" index is SMALLER than the element at the "high"
    index, then move "high" to "mid" index since element at "mid" still might
    be the actual answer.

    However, if the element at "mid" index is GREATER than the element at
    "high" index, then why would we consider element at index "mid" or any one
    BEFORE index "mid" since we know that elements BEFORE index "mid" are
    sorted and then ROTATED.

    Rotation GUARANTEES that in that case our nums[low] is certainly GREATER
    than nums[high].

    This may not be intuitive, but let's look at an example:

            1 2 3 4 5 6 7

            4 5 6 7 1 2 3   // Rotated 4 times
            ^     ^     ^
            |     |     |
            |     |     |
       low --    mid    -- high


    Once we're beginning the Binary Search, we're dealing with ALL of the
    elements and then gradually keep cutting off the ones that we're SURE are
    NOT the answer.

    In this case, since nums[mid] > nums[high], we KNOW that since that is the
    case, we also know that nums[low] > nums[high].

    This may NOT be intuitive, but remember that the array is SORTED and
    ROTATED.

    Since it's ROTATED and we see that some middle element is GREATER than the
    element at "high", that means we certianly have a ROTATION that is NOT 0
    or N, but something inbetween.

    In that case, we know that in the worst case smallest element is all the
    way at index "high" and that also means that our nums[low] is thus LARGER,
    therefore if nums[mid] > nums[high], simply cut-off elements from
    [low, mid], inclusively, by moving "low" to point at "mid + 1".


    At first this will be unintuitive, but take the time to really think about
    these examples and it will "click".

*/

/* Time  Beats: 100% */
/* Space Beats: 50.98% */

/* Time  Complexity: O(logN) */
/* Space Complexity: O(1)    */
class Solution {
public:
    int findMin(vector<int>& nums)
    {
        const int N = nums.size();

        int low  = 0;
        int high = N-1;
        while (low < high)
        {
            int mid = low + (high - low) / 2;

            if (nums[mid] < nums[high])
                high = mid;   // Element at "mid" idx still MIGHT be the answer
            else
                low = mid + 1;// Element at "mid" idx is CERTAINLY NOT answer
        }

        // We'll break the while-loop ONLY when low == high
        return nums[low]; // Or nums[high], it doesn't matter
    }
};
