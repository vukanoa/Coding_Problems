/*
    ==============
    === MEDIUM ===
    ==============

    ===========================================
    3255) Find the Power of K-Size Subarrays II
    ===========================================

    ============
    Description:
    ============

    You are given an array of integers nums of length n and a positive integer
    k.

    The power of an array is defined as:

        + Its maximum element if all of its elements are consecutive and sorted
          in ascending order.

        -1 otherwise.

    You need to find the power of all subarrays of nums of size k.

    Return an integer array results of size n - k + 1, where results[i] is the
    power of nums[i..(i + k - 1)].

    =============================================================
    FUNCTION: vector<int> resultsArray(vector<int>& nums, int k);
    =============================================================

    ==========================================================================
    ================================ EXAMPLES ================================
    ==========================================================================

    --- Example 1 ---
    Input: nums = [1,2,3,4,3,2,5], k = 3
    Output: [3,4,-1,-1,-1]
    Explanation:
    There are 5 subarrays of nums of size 3:
        [1, 2, 3] with the maximum element 3.
        [2, 3, 4] with the maximum element 4.
        [3, 4, 3] whose elements are not consecutive.
        [4, 3, 2] whose elements are not sorted.
        [3, 2, 5] whose elements are not consecutive.


    --- Example 2 ---
    Input: nums = [2,2,2,2,2], k = 4
    Output: [-1,-1]


    --- Example 3 ---
    Input: nums = [3,2,3,2,3,2], k = 2
    Output: [-1,3,-1,3,-1]


    *** Constraints ***
    1 <= n == nums.length <= 10^5
    1 <= nums[i] <= 10^6
    1 <= k <= n

*/

#include <vector>
using namespace std;

/*
    ------------
    --- IDEA ---
    ------------

    First, note that if N == 1, then k MUST be 1 as well, due to the given
    Constraints.

    Also, if k == 1, then we should just return our Input "nums" as a result,
    since longest subarray starting at each index is going to be, both
    minimally and maximally, of size 1.

    Variable 'L' represents the beginning of a subarray that is consecutive
    and sorted in ascending order. Also L must update if either:

        1) Current window, i.e. (R - L) gets bigger than k, or

        2) Current element is NOT a consecutive ascending successor of the
           previous one.


    It's much easier if you take a look at an example:

        Input: nums = [1,2,3,4,3,2,5], k = 3

    Until the window becomes size k, only check if the current element is the
    consectuive sorted successor of the previous.

    If it is INDEED, then do nothing.
    It it is NOT   , then say L = R. Why? Because we certainly will NOT have
    a window of size k BEFORE the one that starts at the current index.

    Look at this example:

        Input: nums = [7,8,9,2,3,4,5,6,7], k = 6
                       0 1 2 3 4 5 6 7 8
                       L     R

    Once R gets to be 3, we still don't have a window of size k, right?
    (Because R - L + 1 is (3 - 0 + 1) = 4)

    However, we can see that the current element is NOT the successor of the
    one before it, therefore there's not POINT in checking these next few
    windows:

        Input: nums = [7,8,9,2,3,4,5,6,7], k = 6
                       0 1 2 3 4 5 6 7 8
                         L         R                // This one [1,6]

        Input: nums = [7,8,9,2,3,4,5,6,7], k = 6
                       0 1 2 3 4 5 6 7 8
                           L         R              // And this one [2,7]

    Why is there no point in checking these?
    Because we know that somewhere in the middle we will 100% have an
    infringement of the required conditions--We won't have consecutive
    sortedness because we saw that element 2 at index 3 is NOT the consecutive
    successor of 9 at index 2, THEREFORE ANY WINDOW THAT CONTAINTS BOTH
    9 and 2 WILL CERTAINLY NOT FULFILL OUR REQUIRED CONDITIONS!

    The FIRST window that is NOT going to contain BOTH 9 and 2 is the window
    that BEGINS at element 2(index 3).

    That's why we're IMMEDIATELY setting our 'L' pointer to point at element 2
    at index 3.

    We know that until we have a window of size k, beginning at index 3, we
    CERTAINLY won't be able to fulfill our requirements.

    Maybe we won't fulfill it even if we begin at index 3, but we just don't
    know yet.

    However, we DO know that we CERTAINLY will NOT be able to fulfill all of
    the requirements if both 9 and 2 are included.

    This is the absolute crux. Once you understand this, the code becomes
    painfully obvious.

*/

/* Time  Beats: 86.79% */
/* Space Beats: 31.76% */

/* Time  Complexity: O(N) */
/* Space Complexity: O(1) */
class Solution {
public:
    vector<int> resultsArray(vector<int>& nums, int k)
    {
        const int N = nums.size();
        vector<int> results;

        if (k == 1)
            return nums;

        int L = 0;
        int R = 1;
        while (R < N)
        {
            if (R < k-1)
            {
                if (((nums[R-1] + 1 != nums[R])))
                    L = R;
            }
            else
            {
                if ((L == (R - k+1)) && ((nums[R-1] + 1) == nums[R]))
                {
                    L++;
                    results.push_back(nums[R]);
                }
                else
                {
                    if (((nums[R-1] + 1 != nums[R])))
                        L = R;

                    results.push_back(-1);
                }
            }

            // Increment
            R++;
        }

        return results;
    }
};
