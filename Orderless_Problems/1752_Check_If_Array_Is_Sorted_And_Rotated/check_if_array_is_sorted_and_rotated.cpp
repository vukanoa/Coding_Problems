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

    TODO

*/

/* Time  Beats: 100.00% */
/* Space Beats:  82.15% */

/* Time  Complexity: O(N) */
/* Space Complexity: O(1) */
class Solution_1 {
public:
    bool check(vector<int>& nums)
    {
        const int N = nums.size();
        if (N <= 2)
            return true;

        bool found_pivot = false;
        for (int i = 0; i < N-1; i++)
        {
            if (nums[i] > nums[i+1])
            {
                if (found_pivot)
                    return false;

                found_pivot = true;
            }
        }

        return found_pivot ? nums.back() <= nums[0] : true;
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
