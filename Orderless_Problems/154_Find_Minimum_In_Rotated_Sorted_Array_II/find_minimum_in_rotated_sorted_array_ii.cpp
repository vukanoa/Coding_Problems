/*
    ============
    === HARD ===
    ============

    ============================================
    154) Find Minimum in Rotated Sorted Array II
    ============================================

    ============
    Description:
    ============

    Suppose an array of length n sorted in ascending order is rotated between 1
    and n times. For example, the array nums = [0,1,4,4,5,6,7] might become:

        [4,5,6,7,0,1,4] if it was rotated 4 times.  [0,1,4,4,5,6,7] if it was
        rotated 7 times.

    Notice that rotating an array [a[0], a[1], a[2], ..., a[n-1]] 1 time
    results in the array [a[n-1], a[0], a[1], a[2], ..., a[n-2]].

    Given the sorted rotated array nums that may contain duplicates, return the
    minimum element of this array.

    You must decrease the overall operation steps as much as possible.


    ---------------
    -- Follow Up --
    ---------------

       This problem is similar to "Find Minimum in Rotated Sorted Array", but
       nums may contain duplicates. Would this affect the runtime complexity?
       How and why?

    =========================================
    FUNCTION: int findMin(vector<int>& nums);
    =========================================

    ==========================================================================
    ================================ EXAMPLES ================================
    ==========================================================================

    --- Example 1 ---
    Input: nums = [1,3,5]
    Output: 1

    --- Example 2 ---
    Input: nums = [2,2,2,0,1]
    Output: 0


    *** Constraints ***
    n == nums.length
    1 <= n <= 5000
    -5000 <= nums[i] <= 5000
    nums is sorted and rotated between 1 and n times.

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
/* Space Beats:  27.34% */

/* Time  Complexity: O(N) */ // Average: O(logN)
/* Space Complexity: O(1) */
class Solution_Binary_Search_Then_Linear_scan {
public:
    int findMin(vector<int>& nums)
    {
        const int N = nums.size();

        int low  = 0;
        int high = N-1;

        while (low < high)
        {
            int mid = low + (high - low) / 2;

            if (nums[low] == nums[mid] && nums[mid] == nums[high])
            {
                for (int i = low; i <= high; i++)
                {
                    if (nums[i] < nums[low])
                        return nums[i];
                }

                return nums[low]; // Or nums[high], it does NOT matter
            }

            if (nums[mid] > nums[high])
                low = mid + 1;
            else
                high = mid;
        }


        return nums[low]; // Or nums[high], it does NOT matter
    }
};




/*
    ------------
    --- IDEA ---
    ------------

    Same as above, but written in a slightly different way. Here we FIRST do a
    linear scan to "get rid of the duplicates" and only then we perform Binary
    Search, whereas in the Solution_1(up above) we did the opposite--i.e. we
    first performed Binary Search and once we realized there are duplicates,
    we started a linear scan.

    It doesn't really matter but it's conceptually different. Depends how you
    think about it.

*/

/* Time  Beats: 100.00% */
/* Space Beats:  63.69% */

/* Time  Complexity: O(N) */ // Average: O(logN)
/* Space Complexity: O(1) */
class Solution_Linear_scan_Then_Binary_Search {
public:
    int findMin(vector<int>& nums)
    {
        const int N = nums.size();

        int last = nums[N-1];

        int low  = 0;
        int high = N-1;

        while (low < N-1 && nums[low] == last)
            low++;

        while (low < high)
        {
            int mid = low + (high - low) / 2;

            if (nums[mid] > nums[high])
                low  = mid + 1;
            else
                high = mid;
        }

        return nums[low]; // Or nums[high], it does NOT matter
    }
};




/*
    ------------
    --- IDEA ---
    ------------

    This one is the most elegant, and most efficient of all 3 in this file.

*/

/* Time  Beats: 100.00% */
/* Space Beats:  90.00% */

/* Time  Complexity: O(N) */ // Average: O(logN)
/* Space Complexity: O(1) */
class Solution_Efficient_and_Elegant {
public:
    int findMin(vector<int>& nums)
    {
        const int N = nums.size();

        int low  = 0;
        int high = N - 1;

        while (low < high)
        {
            int mid = low + (high - low) / 2;

            if (nums[mid] > nums[high])
                low = mid + 1;
            else if (nums[mid] < nums[high])
                high = mid;
            else
                high--;
        }

        return nums[low]; // Or nums[high], it does NOT matter
    }
};
