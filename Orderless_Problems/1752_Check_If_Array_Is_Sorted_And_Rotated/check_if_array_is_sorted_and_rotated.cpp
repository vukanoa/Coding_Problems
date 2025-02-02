/*
    ============
    === EASY ===
    ============

    ==========================================
    1752) Check if Array is Sorted and Rotated
    ==========================================

    ============
    Description:
    ============

    Given an array nums, return true if the array was originally sorted in
    non-decreasing order, then rotated some number of positions
    (including zero). Otherwise, return false.

    There may be duplicates in the original array.

    =====
    Note: An array A rotated by x positions results in an array B of the same
          length such that A[i] == B[(i+x) % A.length], where % is the modulo
          operation.
    =====

    ========================================
    FUNCTION: bool check(vector<int>& nums);
    ========================================

    ==========================================================================
    ================================ EXAMPLES ================================
    ==========================================================================

    --- Example 1 ---
    Input: nums = [3,4,5,1,2]
    Output: true
    Explanation: [1,2,3,4,5] is the original sorted array.
    You can rotate the array by x = 3 positions to begin on the the element of
    value 3: [3,4,5,1,2].

    --- Example 2 ---
    Input: nums = [2,1,3,4]
    Output: false
    Explanation: There is no sorted array once rotated that can make nums.

    --- Example 3 ---
    Input: nums = [1,2,3]
    Output: true
    Explanation: [1,2,3] is the original sorted array.
    You can rotate the array by x = 0 positions (i.e. no rotation) to make nums


    *** Constraints ***
    1 <= nums.length <= 100
    1 <= nums[i] <= 100

*/

#include <vector>
using namespace std;



/*
    ------------
    --- IDEA ---
    ------------

    We begin from the back of the array and we go back until we hit an element
    that is GREATER than our current element. That inidicates a potential end
    of the rotated sorted string.

    Example:

        [1, 2, 2, 3, 4, 4, 5]

    If we rotate it:

        [3, 4, 4, 5, 1, 2, 2]
                     ^
                     |___________________________________________
                                                                |
    We'll find first GREATER, going from the back, once we're here.

    Now all we have to do is check whether elements from the beginning of the
    array, until the index from which we've found there's a GREATER element
    behind, are in NON-DECREASING order.

    In other words - Start from index 0 and check if all elements until element
    1 at index 4(excluding) are in NON-DECREASING order.

    However, there's one more thing we absolutely must check here.
    What if we had an example like this:

         0  1  2  3  4  5  6
        [3, 4, 4, 5, 2, 4, 8]


    Had we done the same approach, we'd be going from the back and we'd stop
    at element 2 since we'd found 5 is the element to the left thta is greater.

    Now we'd start from the beginning and all the elements up until 2, would
    indeed be in a NON-DECREASING order, but we should NOT return "true".

    Why?
    Because this is not a sorted-rotated array. Look:

        [3, 4, 4, 5, 2, 4, 8]
        [2, 4, 8, 3, 4, 4, 5]

    So, what should we do?

    If we've done our two steps already, simply check if the 0th element is
    GREATER THAN OR EQUALS TO the last element.

         0  1  2  3  4  5  6
        [3, 4, 4, 5, 2, 4, 8]

    Since 3 is NOT greater than or equals to 8, we'd return false.


    There's one more thing you should think about--What if all the elements are
    in NON-DECREASING order already and not rotated?

    What if we had this:

         0  1  2  3  4  5  6
        [1, 2, 2, 3, 4, 4, 5]

    In that case, since we have NOT found a GREATER element to the left while
    going backwards, we'd simply return "true".

*/

/* Time  Beats: 100.00% */
/* Space Beats:  85.59% */

/* Time  Complexity: O(n) */
/* Space Complexity: O(1) */
class Solution {
public:
    bool check(vector<int>& nums)
    {
        const int N = nums.size();

        int start = -1;
        for (int i = N-1; i >= 1; i--)
        {
            if (nums[i-1] > nums[i])
            {
                start = i;
                break;
            }
        }

        if (start == -1) // They are all in non-decreasing order already
            return true;

        if (start == 1)
            return nums[0] >= nums[N-1];

        int end = -1;
        for (int i = 0; i < start && i < N-1; i++)
        {
            if (nums[i] > nums[i+1])
            {
                end = i;
                break;
            }
        }

        return end + 1 == start && nums[0] >= nums[N-1];
    }
};





/*
    ------------
    --- IDEA ---
    ------------

    The number of "inversions" in any sorted array is 0.
    However, the number of "inversions" in any sorted but ROTATED array is 1.

    Since we can have an example where our "nums" array is sorted but NOT
    rotated, we can have 0 "inversion" and still return "true", however we
    CANNOT have more than 1 inversion and return "true".

    Now the problem becomes trivial. Scan through the array "nums" from the
    back and count "inversions".

    Also, do NOT forget to count the potential "inversion" between:

        nums[0] and nums[N-1]


    Example:
        [1, 2, 3, 3, 4, 5, 5, 6]  // No "inversions"

        [6, 5, 5, 1, 2, 3, 3, 4]  // 1 "inversion"
               ^^^^
                 |
                inversion

        [1, 2, 6, 3, 4, 4, 4, 5]  // 2 "inversions", therefore return "false"
         ^     ^^^^           ^
         |       |            |
         |      inversion     |
         |                    |
         |____________________|
                 |
                inversion between nums[0] and nums[N-1]


*/

/* Time  Beats: 100.00% */
/* Space Beats:  58.89% */

/* Time  Complexity: O(N) */
/* Space Complexity: O(1) */
class Solution_2 {
public:
    bool check(vector<int>& nums)
    {
        const int N = nums.size();

        if (N <= 1)
            return true;

        int inversion_count = 0;

        // For every pair, count the number of inversions.
        for (int i = 1; i < N; ++i)
        {
            if (nums[i-1] > nums[i])
                inversion_count++;
        }

        // Also check between the last and the first element due to rotation
        if (nums[0] < nums[N - 1])
            inversion_count++;

        return inversion_count <= 1;
    }
};
