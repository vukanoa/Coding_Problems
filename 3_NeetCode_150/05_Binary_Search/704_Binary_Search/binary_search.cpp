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

#include <vector>
#include <algorithm>
using namespace std;

/*
    ------------
    --- IDEA ---
    ------------

    This is my implmementation of lower_bound.

*/

/* Time  Beats: 100.00% */
/* Space Beats:  79.67% */

/* Time  Complexity: O(logN) */
/* Space Complexity: O(1)    */
class Solution_My_Own_Lower_Bound {
public:
    int search(vector<int>& nums, int target)
    {
        const int N = nums.size();

        // Include entire range of answers(both 0 and N-1 CAN be answers)
        int low  = 0;
        int high = N-1;

        /* Lower Bound */
        while (low < high) // While loop will break ONLY once low == high
        {
            int mid = low + (high - low) / 2; // Left-leaning

            if (target > nums[mid])
                low = mid + 1; // Elems from [low, mid] are CERTAINLY NOT res.
            else
                high = mid;    // "mid" still MIGHT be the answer
        }

        return nums[low] == target ? low : -1;
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
    int search(vector<int>& nums, int target)
    {
        auto iter = upper_bound(nums.begin(), nums.end(), target);

        if (iter == nums.begin() || *(iter - 1) != target)
            return -1;

        return (iter - 1) - nums.begin();
    }
};




/*
    ------------
    --- IDEA ---
    ------------

    This Idea uses lower_bound.

    vector<int> nums = {1, 2, 4, 5, 5, 5, 5, 6, 6};
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
    int search(vector<int>& nums, int target)
    {
        auto iter = lower_bound(nums.begin(), nums.end(), target);

        if (iter == nums.end() || *iter != target)
            return -1;

        return iter - nums.begin();
    }
};
