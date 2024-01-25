#include <iostream>
#include <vector>
#include <algorithm>

/*
    ============
    === EASY ===
    ============

    ===========================
    35) Search Insert Position
    ===========================

    ============
    Description:
    ============

    Given a sorted array of distinct integers and a target value, return the
    index if the target is found. If not, return the index where it would be if
    it were inserted in order.

    =====
    Node: You must write an algorithm with O(log n) runtime complexity.
    =====

    ==========================================================
    FUNCTION: int searchInsert(vector<int>& nums, int target);
    ==========================================================

    ==========================================================================
    ================================ EXAMPLES ================================
    ==========================================================================

    --- Example 1 ---
    Input:  nums = [1, 3, 5, 6], target = 5
    Output: 2

    --- Example 2 ---
    Input:  nums = [1, 3, 5, 6], target = 2
    Output: 1

    --- Example 3 ---
    Input: nums = [1, 3, 5, 6], target = 7
    Output: 4

    *** Constraints ***
    1 <= nums.length <= 10^4
    -10^4 <= nums[i] <= 10^4
    nums contains distinct values sorted in ascending order.
    -10^4 <= target <= 10^4

*/




/*
    ------------
    --- IDEA ---
    ------------

    Since we're told we must have a runtime complexity of O(log n), that means
    we have to use a Binary Search.

    It's a basic Binary Search. There's only one thing that is important to be
    explained here.

    Why are we returning the "left" pointer after the while loop?

~~~~~~~~~~~~~~
~~ Smaller ~~~ (target smaller than the last we're checking in the while loop)
~~~~~~~~~~~~~~

    Consider this example:
        nums = [2]
    indexes:    0

    target = 1;

    At the beginning of the while loop, both "left" and "right" are at index 0.
    "mid" is also going to be 0.

               mid
                R
                L
        nums = [2]
    indexes:    0


    Now since nums[mid] != target, we have to update either our "left" or our
    "right" pointer.

    target < nums[mid]
      1   <   2

    Therefore we have to update our "right" pointer to mid - 1.

    Once we do that, our "right" becomes less than "left" which breaks our
    while loop.

    Now we're in this position:

                    R  L
            nums =    [2]
        indexes:   -1  0
                    ^
out of bounds ______|

    Look at the above "picture". Let's ask a question - Where should we place
    our target(1)?
    Well, at position 0, where our "left" pointer points.



    Now let's consider a target which is greater than the last item we're
    checking.


~~~~~~~~~~~~~~
~~ Greater ~~~ (target greater than the last we're checking in the while loop)
~~~~~~~~~~~~~~

    Consider this example: (Same example, different target)
        nums = [2]
    indexes:    0

    target = 3;

    At the beginning both "left and "right" are at index 0, and "mid" as well.

               mid
                R
                L
        nums = [2]
    indexes:    0

    Now since:
        target > nums[mid]
            L = mid + 1;

    We update our "left" pointer and we're in this situation:

                    R  L
            nums = [2]
        indexes:    0  1
                       ^
out of bounds _________|

    Again, let's ask ourselves the same question - At which index should our
    target(3) be inserted?
    Well, at index 1. Which pointer points to index 1?
    The "left" one again!
~~~~~~~

    That's the whole "trick" of this problem.

*/


/* Time  Beats: 100% */
/* Space Beats: 35.98% */

/* Time  Complexity: O(logn) */
/* Space Complexity: O(1) */
class Solution{
public:
    int searchInsert(std::vector<int>& nums, int target)
    {
        int n = nums.size();

        int left  = 0;
        int right = n - 1;

        while (left <= right)
        {
            int mid = (left + right) / 2;

            if (target == nums[mid])
                return mid;

            if (target < nums[mid])
                right = mid - 1;
            else
                left = mid + 1;
        }

        return left;
    }
};




/*
    ------------
    --- IDEA ---
    ------------

    std::upper_bound function does exactly what this problem asks us to do.
    They ask us to:"... return the index if the target is found. If not, RETURN
    THE INDEX WHERE IT WOULD BE IF IT WERE INSERTED IN ORDER".

    The uppercase part is EXACTLY what std::upper_bound does.

    Therefore, since we do not need to, solely, implement the uppercase part,
    we must tweak std::upper_bound result a bit.

    Anytime you look at a sorted array and wonder what is std::upper_bound
    going to return, just ask the same uppercase part to yourself: "RETURN THE
    INDEX WHERE IT WOULD BE IF IT WERE INSERTED IN ORDER"

    Let's consider a few examples:

    First, let's see some "standard" examples where the std::upper_bound does
    the job alone. No need for any tweaks.

    ***********************************************************************
    ******************************* STANDARD ******************************
    ***********************************************************************

    --- Example 1 ---
    nums = [1, 3, 5, 6, 8], target = 4
            0  1  2  3  4

    // std::upper_bound will return element 5, which is at index 2
    Output: 2



    --- Example 2 ---
    nums = [3, 4, 5, 7, 8, 9], target = 6
            0  1  2  3  4  5

    // std::upper_bound will return element 6, which is at index 3
    Output: 1


    ***********************************************************************
    ********************************* FOUND *******************************
    ***********************************************************************

    --- Example 3 ---
    nums = [1, 3, 5, 6, 9], target = 6
            0  1  2  3  4

    // std::upper_bound will return element 9 at index 4, however we need to
    // check if *(iter-1), i.e. element to the left of 9, is EQUAL to target
    // If that is the case, then we return that index instead
    // Here that's exactly the case, therefore, we return index 3
    Output: 3


    ***********************************************************************
    ****************************** EDGE-CASES *****************************
    ***********************************************************************

    --- Example 4 ---
    nums = [3, 4, 5, 7, 8, 9], target = 1
            0  1  2  3  4  5

    // Since element 1 doesn't exist, the next greater is element 3 at index 0.
    // Since index 0 is at nums.begin() we CANNOT check:
    //     if (*(iter-1) == target)
    // because that would be Out of Bounds. Therefore, we must think of another
    // way of handling this.
    // You can notice something interesting here - If "iter" is at index 0, it
    // DOESN'T matter if that element is greater than or exactly the desired
    // value "target".
    // Think about it. Here we needed to see where is element 1 or if there is
    // no any element 1, then wwhere would we insert it.
    // a) THere is   NO   element 1, therefore return iter, i.e. nums.begin()
    // b) There is INDEED element 1, therefore return iter, i.e. nums.begin()
    // Therefore, if "iter" is at nums.begin() we ALWAYS return that index
    Output: 0


    --- Example 5 ---
    nums = [1, 4, 5, 7, 8, 9], target = 1
            0  1  2  3  4  5

    // Here we will, again, return index 0 because if "iter" is nums.begin() it
    // DOESN'T matter if *iter is greater or equal to target. We ALWAYS return
    // that index 0, i.e. nums.begin()
    Output: 0



    --- Example 6 ---
    nums = [2, 2, 5, 6, 8], target = 9
            0  1  2  3  4

    // Here it's important to note that if there is no target and if there is
    // no any element greater than target, then std::upper_bound will return
    // nums.end().
    // However, that is just fine because (nums.end() - nums.begin()) will give
    // us exactly what we want.
    Output: index 5, i.e. nums.end()

*/

/* Time  Beats: 100.00% */
/* Space Beats:  7.76% */

/* Time  Complexity: O(logn) */
/* Space Complexity: O(1)    */
class Solution_Upper_Bound {
public:
    int searchInsert(std::vector<int>& nums, int target)
    {
        auto iter = std::upper_bound(nums.begin(), nums.end(), target);
        int  idx  = iter - nums.begin();

        if (iter == nums.begin())
            return 0;

        if (*(iter-1) == target)
            return idx - 1;

        return idx;
    }
};


int
main()
{
    Solution             sol;
    Solution_Upper_Bound sol_upper_bound;

    /* Example 1 */
    std::vector<int> nums = {1, 3, 5, 6};
    int target = 5;

    /* Example 2 */
    // std::vector<int> nums = {1, 3, 5, 6};
    // int target = 2;

    /* Example 3 */
    // std::vector<int> nums = {1, 3, 5, 6};
    // int target = 7;

    /* Example 4 */
    // std::vector<int> nums = {1, 3, 5, 6};
    // int target = 4;

    /* Example 5 */
    // std::vector<int> nums = {1, 3, 5, 6};
    // int target = 0;

    /* Example 6 */
    // std::vector<int> nums = {1, 3, 5, 6};
    // int target = 10;

    /* Example 7 */
    // std::vector<int> nums = {1};
    // int target = 1;

    /* Example 8 */
    // std::vector<int> nums = {1};
    // int target = -7;


    std::cout << "\n\t==============================";
    std::cout << "\n\t=== SEARCH INSERT POSITION ===";
    std::cout << "\n\t==============================\n";


    /* Write Input */
    bool first = true;
    std::cout << "\n\tInput: [";
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
    // int output = sol.searchInsert(nums, target);
    int output = sol_upper_bound.searchInsert(nums, target);


    /* Write Output */
    std::cout << "\n\tInsert at index: " << output << "\n\n";

    return 0;
}
