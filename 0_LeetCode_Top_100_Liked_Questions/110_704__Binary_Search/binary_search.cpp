#include <iostream>
#include <vector>
#include <algorithm>

/*
    ============
    === EASY ===
    ============

    ===========================
    704) Binary Search
    ===========================

    ============
    Description:
    ============

    Given an array of integers "nums" which is sorted in ascending order, and
    an integer "target", write a function to search "target" in "nums". If
    "target" exists, then return its index. Otherwise, return -1.

    =====
    Node: You must write an algorithm with O(log n) runtime Complexity.
    =====

    ====================================================
    FUNCTION: int search(vector<int>& nums, int target);
    ====================================================

    ==========================================================================
    ================================ EXAMPLES ================================
    ==========================================================================

    --- Example 1 ---
    Input:  [-1, 0, 3, 5, 9, 12], target = 9
    Output: 4
    Explanation: 9 exists in nums and its index is 4

    --- Example 2 ---
    Input:  [-1, 0, 3, 5, 9, 12], target = 2
    Output: -1
    Explanation: 2 does not exist in nums so return -1

    *** Constraints ***
    1 <= nums.length <= 10^4
    -10^4 <= nums[i], target < 10^4
    All the integers in "nums" are unique.
    "nums" is sorted in ascending order.

*/

/*
    ------------
    --- IDEA ---
    ------------

    The most basic Binary Search. However, it's important to note it here as
    well:

        DO NOT write Binary Search like this: int mid = (left + right) / 2;
        Overflow can happen.

    Consider this:

    You have to find number: INT_MAX-3
    INT_MAX is: 2,147,483,647

    INT_MAX - 3 --> 2,147,483,647 - 3 = 2,147,483,644

    Imagine that the range we're searching this number in is: [0, INT_MAX];

    At some point in our process of Binary Search, our left bound will be
    somewhere close to INT_MAX-5 and our right bound will remain INT_MAX since
    we've always gone to the right after comparing mid with the target value.

    So now:
        left  = INT_MAX-5
        right = INT_MAX

    If we try to do this:
        int mid = (left + right) / 2

    The Overflow will happen. The computation is going to produce an invalid
    calculation because int is 32-bits(on 64-bit architecture) which means
    that the maximum positive value it can store is INT_MAX, therefore
    doing:
        int mid = (left + right) / 2

    Where:
        left  = INT_MAX-5
        right = INT_MAX

    WILL PRODUCE AN OVERFLOW!!!

    So how can we resolve this?

    Simply use this formula instead:
        int mid = left + (right - left) / 2;

    What this does is: It adds halfed current range on the left bound. That is
    guaranteed not to make a Overflow.

*/

/* Time  Beats: 95.40% */
/* Space Beats:  9.71% */

/* Time  Complexity: O(logn) */
/* Space Complexity: O(1) */
class Solution {
public:
    int search(std::vector<int>& nums, int target)
    {
        int l = 0;
        int r = nums.size() - 1;

        while (l <= r)
        {
            // DON'T write it like this: mid = (l + r) / 2; It can Overflow!!!
            int mid = l + (r - l) / 2;

            if (nums[mid] == target)
                return mid;

            if (nums[mid] < target)
                l = mid + 1;
            else
                r = mid - 1;
        }

        return -1;
    }
};




/*
    ------------
    --- IDEA ---
    ------------

    This Idea uses std::upper_bound function.

    std::upper_bound returns the first element that is GREATER than the target.
    If there is no element that is GREATER than the target, then iterator will
    point to nums.end().

    So it's important to emphasize that by using std::upper_bound function we
    will NOT find our target, but we WILL find the first element that is
    GREATER than target or nums.end().

        nums = [1, 4, 5, 7, 9], target = 6
                         ^
                         |
                         |
        iter -------------

    First, since we will find the next greater and not the target, if iterator
    points to nums.begin(), then we're 100% sure out "target" value DOES NOT
    exist in the array nums.

        nums.begin()            nums.end() // Points to right of last element
                |               _|
                |              |
                v              v
        nums = [3, 4, 6, 7, 9]         , target = 1
                0  1  2  3  4  5
                ^              ^
                |              |
                |              ------ Out of Bounds
        iter ----

    However, if that is not the case, then if we check one element to the left
    of our iterator, we can check if that is our desired "target" value.
    (If iter points to nums.begin() there is no point in checking anyway, but
     we MUST NOT check in the first place since that will be out of bounds)

           nums.begin()          nums.end() // Points to right of last element
                   |               _|
                   |              |
                   v              v
        nums =    [3, 4, 6, 7, 9]         , target = 1
               -1  0  1  2  3  4  5
                ^  ^              ^
                |  |              |
    iter-1 ------  |              |
                   |              ------ Out of Bounds
           iter ----

    Value of the element to the left of our iterator is: *(iter - 1)

    So:
        if ((*iter - 1) != target)
            // Then there is no "target" value in our array "nums".
        else
            // There IS and we want to return it's index, which is:
            (iter - 1) - nums.begin();
            ~~~~~~~~~~~~~~~~~~~~~~~~~~
                  distance


        distance = (iter - 1) - nums.begin() ==> 2 - 0 ==> 2 (index of target)

        nums = [1,  4,  8, 12, 19, 22], target = 8
                0   1   2   3   4   5
                ^       ^   ^
             ___|       |   |
             |          |   |
     nums.begin()       |   |
                        |   |
      iter - 1 ----------   |
      (target)              ----- iter


    It's important to emphasize if there are repeating elements that are the
    "first greater than target", then return the element with the lowest index.

*/

/* Time  Beats: 89.01% */
/* Space Beats: 11.00% */

/* Time  Complexity: O(logn) */
/* Space Complexity: O(1) */
class Solution_Upper_Bound {
public:
    int search(std::vector<int>& nums, int target)
    {
        auto iter = std::upper_bound(nums.begin(), nums.end(), target);

        if (iter == nums.begin() || *(iter - 1) != target)
            return -1;

        return (iter - 1) - nums.begin();
    }
};




/*
    ------------
    --- IDEA ---
    ------------

    This Idea uses std::lower_bound.

    std::vector<int> nums = {1, 2, 4, 5, 5, 5, 5, 6, 6};
                             0  1  2  3  4  5  6  7  8


    target(value)           *iter(value)
       |                     |
       |         ____________|
       |_____    |
            |    |                 iter (not dereferenced)
            |    |          ________|
            |    |          |
            v    v          v
            0 <= 1 at index 0
            1 <= 1 at index 0
            2 <= 2 at index 1
            3 <= 4 at index 2
            4 <= 4 at index 2
            5 <= 5 at index 3
            6 <= 6 at index 7
            7 <= not found    // Iter will be pointing to nums.end()

           Find the LOWEST VALUE that the target is less than or equal to.
           (If there are repeating elements, return the smallest index)


    If "iter" is nums.end(), then we are certain that there is no "target" in
    our "nums" array.

    Otherwise check:
        if (*iter != target)
            // Then there is no target in our "nums" array
        else
            return the index of "iter" by doing this: iter - nums.begin()

*/

/* Time  Beats: 93.03% */
/* Space Beats:  8.39% */

/* Time  Complexity: O(logn) */
/* Space Complexity: O(1)    */
class Solution_Lower_Bound {
public:
    int search(std::vector<int>& nums, int target)
    {
        auto iter = std::lower_bound(nums.begin(), nums.end(), target);

        if (iter == nums.end() || *iter != target)
            return -1;

        return iter - nums.begin();
    }
};

int
main()
{
    Solution             sol;
    Solution_Upper_Bound sol_upper_bound;
    Solution_Lower_Bound sol_lower_bound;


    /* Example 1 */
    std::vector<int> nums = {-1, 0, 3, 5, 9, 12};
    int target = 9;

    /* Example 2 */
    // std::vector<int> nums = {-1, 0, 3, 5, 9, 12};
    // int target = 2;


    std::cout << "\n\t=====================";
    std::cout << "\n\t=== BINARY SEARCH ===";
    std::cout << "\n\t=====================\n";


    /* Write Input */
    std::cout << "\n\tTarget: " << target;
    bool first = true;
    std::cout << "\n\tNums: [";
    for (auto x: nums)
    {
        if (!first)
            std::cout << ", ";

        std::cout << x;
        first = false;
    }
    std::cout << "]\n\n";



    /* Solution */
    // int result = sol.search(nums, target);
    // int result = sol_upper_bound.search(nums, target);
    int result = sol_lower_bound.search(nums, target);


    /* Write Output */
    if (result != -1)
        std::cout << "\n\tOutput: " << target << " exist at index " << result;
    else
        std::cout << "\n\tOutput: " << target << " does NOT exist!";
    std::cout << "\n\n";


    return 0;
}
