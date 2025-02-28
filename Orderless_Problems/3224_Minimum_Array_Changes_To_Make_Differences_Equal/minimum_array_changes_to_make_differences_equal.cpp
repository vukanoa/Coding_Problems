/*
    ==============
    === MEDIUM ===
    ==============

    =====================================================
    3224) Minimum Array Changes to Make Differences Equal
    =====================================================

    ============
    Description:
    ============

    You are given an integer array nums of size n where n is even, and an
    integer k.

    You can perform some changes on the array, where in one change you can
    replace any element in the array with any integer in the range from 0 to k.

    You need to perform some changes (possibly none) such that the final array
    satisfies the following condition:

    There exists an integer X such that abs(a[i] - a[n - i - 1]) = X for all
    (0 <= i < n).

    Return the minimum number of changes required to satisfy the above
    condition.

    ===================================================
    FUNCTION: int minChanges(vector<int>& nums, int k);
    ===================================================

    ==========================================================================
    ================================ EXAMPLES ================================
    ==========================================================================

    --- Example 1 ---
    Input: nums = [1,0,1,2,4,3], k = 4
    Output: 2
    Explanation:
    We can perform the following changes:
        Replace nums[1] by 2. The resulting array is nums = [1,2,1,2,4,3].
        Replace nums[3] by 3. The resulting array is nums = [1,2,1,3,4,3].
    The integer X will be 2.

    --- Example 2 ---
    Input: nums = [0,1,2,3,3,6,5,4], k = 6
    Output: 2
    Explanation:
    We can perform the following operations:
        Replace nums[3] by 0. The resulting array is nums = [0,1,2,0,3,6,5,4].
        Replace nums[4] by 4. The resulting array is nums = [0,1,2,0,4,6,5,4].
    The integer X will be 4.


    *** Constraints ***
    2 <= n == nums.length <= 10^5
    n is even.
    0 <= nums[i] <= k <= 10^5

*/

#include <cstdlib>
#include <vector>
using namespace std;

/*
    ------------
    --- IDEA ---
    ------------

    Atypical Line Sweep.


    nums = {2,  9,  7,  6,  5, 12, 12,  4,  4  6,  9,  0,  1,  8,  7,  3}
            0   1   2   3   4   5   6   7   8  9  10  11  12  13  14  15

    k = 13


    0                                              14 <==> k + 1
    X----------------------------------------------X

    0  1  2  3  4  5  6  7  8  9  10  11  12  13  14

       -  +                                +
          -  +                     +
       -  +                    +
                   -  +                       +
                   -  +                           +
            -  +                              +
                      -  +                    +
    - +                            +


    We MUST assign change_count[0] = N / 2.

    Why?
    Because that is the upper bound, the most amount of time we'd need to make
    every element with the same difference.

    Now we go through this sweep_line and we add the element at each index.

    But why are we having this "-" in the front and not AFTER the range as in
    most SweepLine algorithms?

    Because that's how we're marking that we do NOT have to change ANY element.
    We already have that different at that number.

    and we do change_count[max_diff + 1] because indexing starts at 0.


    The most important thing here is to understand what does this range
    represent.
    "-" represents that we already have that difference and thus we don't need
    to do anything to have it.

    "+" means that we'd need to change ONE of two elements in order to have
    that difference.

    Example:
        [....9, ........., 7....]   k = 13

        curr_diff = abs(9 - 7) = 2
        max_diff  = max({9, 7, 13 - 9, 13 - 7})

    So, we ALREADY HAVE a difference of 2.

    However if we want to "construct" a difference of 3, or 4, or any
    difference up until 9, we'd have to change ONE element.

    But why are we, then, incrementing (9 + 1) and not 9?

    Consider this example:
        [0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0]  k = 0

    Our final output would be 9, which is incorrect, it should be 0.

    Now that we've constructed this change_count, simply do a basic SweepLine
    and update the minimum needed change.

*/

/* Time  Beats: 83.50% */
/* Space Beats: 79.13% */

/* Time  Complexity: O(N + k) */
/* Space Complexity: O(k)     */
class Solution {
public:
    int minChanges(vector<int>& nums, int k)
    {
        const int N = nums.size();

        vector<int> change_count(k + 2, 0);
        change_count[0] = N / 2;

        for (int i = 0; i < N/2; i++)
        {
            int left  = nums[i];
            int right = nums[N-1 - i];

            int curr_diff = abs(left - right);
            int max_diff  = max({left, right, k - left, k - right});

            change_count[curr_diff]--;
            change_count[curr_diff + 1]++;
            change_count[max_diff  + 1]++;
        }

        int curr_changes = 0;
        int min_changes  = N / 2;
        for (int i = 0; i < k+1; i++)
        {
            curr_changes += change_count[i];
            min_changes   = min(min_changes, curr_changes);
        }

        return min_changes;
    }
};
