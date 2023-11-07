#include <iostream>
#include <vector>
#include <algorithm>
#include <iterator>

/*
    ==============
    === MEDIUM ===
    ==============

    ===========================================================
    34) Find First and Last Position of Element in Sorted Array
    ===========================================================

    ============
    Description:
    ============

    Given an array of integers "nums" sorted in non-decreasing order, find the
    starting and ending position of a given "target" value.

    If "target" is not found in the array, return [-1, -1].

    =====
    Node: You must write an algorithm with O(log n) runtime complexity.
    =====

    =================================================================
    FUNCTION: vector<int> searchRange(vector<int>& nums, int target);
    =================================================================

    ==========================================================================
    ================================ EXAMPLES ================================
    ==========================================================================

    --- Example 1 ---
    Input:  nums = [5, 7, 7, 8, 8, 10], target = 8
    Output: [3, 4]

    --- Example 2 ---
    Input:  nums = [5, 7, 7, 8, 8, 10], target = 6
    Output: [-1, -1]

    --- Example 3 ---
    Input:  nums = [], target = 0
    Output: [-1, -1]

    *** Constraints ***
    0 <= nums.length <= 10^5
    -10^9 <= nums[i] <= 10^9
    nums in a non-decreasing array.
    -10^9 <= target <= 10^9

*/


/*
    ------------
    --- IDEA ---
    ------------

    Since we're told to solve this problem in O(log n) runtime complexity, we
    have to use Binary search.

    However, we will divide this problem to two searches, since we have to
    return two indices anyway.
    First we search for the left index, and then, using some informaion of the
    previous search, we search for the right index as well.

    We initialize:
        low  = 0;
        high = n - 1;

    In each step we calculate "mid"(mid = (low + high) / 2).

    Left range:

    Now there are three possibilities:
        1. If nums[mid] < target, then the range must begin on the right of mid
        That is => low = mid + 1;

        2. If nums[mid] > target, then the range must begin on the left of mid
        That is => high = mid - 1;

        3. If nums[mid] == target, then the range must begin on the left or at
        the mid. That is => high = mid;

        We can merge 2nd and 3rd case in:
            2*. If nums[mid] >= target, then
                high = mid

    The while loop loops until low < high.

    After we are finished with searching for the left index, we can simply
    check if (nums[low] == target) and if that is indeed the case, then that is
    the left boundary of the range.

    If it is not, we are done. There is no number "target"in our array and we
    can return {-1, -1} immediately.


    For the right range we can use a similar logic, however there's one caveat.
    First, again, there are three possibilities:
        1. If nums[mid] > target, then the range must begin on the left of mid
        That is => high = mid - 1

        2. If nums[mid] < target, then the range must beginon the right od mif
        That is => low = mid + 1

        3. If nums[mid] == target, then the range must begin on the right of or
        at mid. That is => low = mid

    Again, we can merge 2nd and 3rd case into:
        2*. If nums[mid] <= target, then
            low = mid

    However, as I've said, there's on caveat. Consider the following case:
    nums = [5, 7], target = 5

    Now nums[mid] == 5, then according to the rule 2, we set low = mid. This
    practically does nothing because "low" is already equal to mid. As a
    result, the search range is NOT MOVED AT ALL!

    The solution is by using a small trick: instead of calculating "mid" as
        mid = (low + high) / 2

    we do:
        mid = (low + high) / 2 + 1


    Why does this work?

    When we use:
        mid = (low + high) / 2
    the "mid" is rounded down. In other words, "mid" is always "biased" towards
    the left. This means we could have:
        low == mid    when    high - low == mid

    but we NEVER have:
        high == mid

    So in order to keep the search range moving, you must make sure the new
    "low" is set to something different than "mid", otherwise we are at the
    risk that "low" gets stuck.
    But for the new "high", it is okay if we set it to "mid", since it was not
    equal to mid anyways. Our two rules in search of the left boundary happen
    to satisfy these requirements, so it works perfectly in that situation.
    Similarly, when we search for the right boundary, we must make sure "low"
    won't get stuck when we set the new "low" to:
        low = mid

    The easiest way to achieve this is by making "mid" biased to the right.
    i.e. mid = (low + high) / 2 + 1


*/


/* Time  Beats: 92.92% */
/* Space Beats: 71.26% */

/* Time  Complexity: O(log n) */
/* Space Complexity: O(1) */
class Solution{
public:
    std::vector<int>
    searchRange(std::vector<int>& nums, int target)
    {
        std::vector<int> vec_result(2, -1);

        // Base case
        if (nums.empty())
            return vec_result;

        int n = nums.size();

        int low  = 0;
        int high = n - 1;

        // Find the left one
        while (low < high)
        {
            int mid = (low + high) / 2;

            if (nums[mid] < target)
                low = mid + 1;
            else
                high = mid;
        }

        if (nums[low] != target)
            return {-1, -1};
        else
            vec_result[0] = low;


        // Find the right one
        high = n - 1; // 'i' can start where it is

        while (low < high)
        {
            int mid = (low + high) / 2 + 1; // Make mid "biased" to the right

            if (nums[mid] > target)
                high = mid - 1;
            else
                low = mid; // So that this won't make the search range stuck
        }

        vec_result[1] = high;

        return vec_result;
    }
};




/*
    ------------
    --- IDEA ---
    ------------

    Same IDEA, written in the spirit of CPP.

*/

/* Time  Beats: 91.99% */
/* Space Beats: 89.61% */

/* Time  Complexity: O(log n) */
/* Space Complexity: O(1) */
class Solution_CPP_Way {
public:
    std::vector<int> searchRange(std::vector<int>& nums, int target)
    {
        auto lower = std::lower_bound(nums.begin(), nums.end(), target);
        auto upper = std::upper_bound(nums.begin(), nums.end(), target);

        if (lower == upper)
            return {-1, -1};

        int left  = std::distance(nums.begin(), lower);
        int right = std::distance(nums.begin(), upper - 1);

        return {left, right};
    }
};


int
main()
{
    Solution         sol;
    Solution_CPP_Way sol_cpp;

    /* Example 1 */
    std::vector<int> nums = {5, 7, 7, 8, 8, 10};
    int target = 8;

    /* Example 2 */
    // std::vector<int> nums = {5, 7, 7, 8, 8, 10};
    // int target = 6;

    /* Example 3 */
    // std::vector<int> nums = {};
    // int target = 0;

    /* Example 4 */
    // std::vector<int> nums = {1, 2, 2, 4, 5, 7, 8, 8, 8, 9, 11};
    // int target = 8;

    /* Example 5 */
    // std::vector<int> nums = {1, 2, 3, 4, 8, 8, 8, 9, 9, 9, 10};
    // int target = 8;

    /* Example 6 */
    // std::vector<int> nums = {1, 8, 8, 8, 9, 9, 10, 10, 11, 12, 13};
    // int target = 8;

    /* Example 7 */
    // std::vector<int> nums = {1, 8, 8, 8, 9, 9, 10, 10, 11, 12, 13};
    // int target = 11;

    /* Example 8 */
    // std::vector<int> nums = {2, 2};
    // int target = 2;

    /* Example 9 */
    // std::vector<int> nums = {1, 4};
    // int target = 4;

    /* Example 10 */
    // std::vector<int> nums = {1};
    // int target = 1;

    /* Example 11 */
    // std::vector<int> nums = {2};
    // int target = 3;

    std::cout << "\n\t===============================================================";
    std::cout << "\n\t=== FIND FIRST AND LAST POSITION OF ELEMENT IN SORTED ARRAY ===";
    std::cout << "\n\t===============================================================\n";

    /* Write Input */
    bool first = true;
    std::cout << "\n\tArray: [";
    for (auto x: nums)
    {
        if (!first)
            std::cout << ", ";

        std::cout << x;
        first = false;
    }
    std::cout << "]";
    std::cout << "\n\tTarget: " << target << "\n";


    /* Solution */
    // std::vector<int> result = sol.searchRange(nums, target);
    std::vector<int> result = sol_cpp.searchRange(nums, target);


    /* Write Output */
    first = true;
    std::cout << "\n\tFIRST & LAST Index of Target:\n\t[";
    for (auto x: result)
    {
        if (!first)
            std::cout << ", ";

        std::cout << x;
        first = false;
    }
    std::cout << "]\n\n";

    return 0;
}
