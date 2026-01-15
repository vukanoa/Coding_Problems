/*
    ==============
    === MEDIUM ===
    ==============

    ===========================
    189) Rotate Array
    ===========================

    ============
    Description:
    ============

    Given an integer array "nums", rotate the array to the right by "k" steps,
    where "k" is non-negative.

    Follow up:
        - Try to come up with as many solution as you can. There are at least
          three different ways to solve this problem.

        - Could you do it in-place with O(1) extra space?

    ================================================
    FUNCTION: void rotate(vector<int>& nums, int k);
    ================================================

    ==========================================================================
    ================================ EXAMPLES ================================
    ==========================================================================

    --- Example 1 ---
    Input:  nums = [1, 2, 3, 4, 5, 6, 7], k = 3
    Output: [5, 6, 7, 1, 2, 3, 4]

    --- Example 2 ---
    Input:  [-1, -100, 3, 99], k = 2
    Output: [3, 99, -1, -100]

    *** Constraints ***
    1 <= nums.length <= 10^5
    -2^31 <= nums[i] <= 2^31 - 1
    0 <= k <= 10^5

*/

#include <algorithm>
#include <vector>
using namespace std;

/*
    ------------
    --- IDEA ---
    ------------

    It's not obvious to see this, but once you see it it becomes obvious.
    The code is self-explanatory. Just go through one example.

*/

/* Time  Beats: 100.00% */
/* Space Beats:  41.12% */

/* Time  Complexity: O(N) */
/* Space Complexity: O(1) */
class Solution {
public:
    void rotate(vector<int>& nums, int k)
    {
        const int N = nums.size();
        k %= N;

        reverse(nums.begin()    , nums.end());
        reverse(nums.begin()    , nums.begin() + k);
        reverse(nums.begin() + k, nums.end());
    }
};




/*
    ------------
    --- IDEA ---
    ------------

    Go through the code with one example and I'm sure you'll have the "AHA"
    moment.

    Try with this:

        nums = [1, 2, 3, 4, 5, 6]
        k = 4

    start_idx is the first index within one CYCLE.
    In this example, there are only two cycles:

        nums = [1, 2, 3, 4, 5, 6]
                0  1  2  3  4  5
                X     X     X           // 1st Cycle
                   X     X     X        // 2nd Cycle


    We're trying to place each index at the correct position.

        Initial position: i
        Correct position: (i + k) % N

    So, once we swap 'i' to the correct index, we must remember the value that
    was at that index(i.e. at (i + k) % N).

    We remember it in "prev_val".

    Now we need to place that value at correct position.
    What is the correct position?

    It's the same thing.

        Initial position: curr_idx           // This is index of the "prev_val"
        Correct position: (curr_idx + k) % N


    You'll notice that once we put elements 1, 5 and 3 at their correct spots,
    we'll have our curr_idx == 0, which we have began with.

    Therefore, we end this do-while loop and we increment start_idx and we do
    the second "cycle" of elements.

*/

/* Time  Beats: 100.00% */
/* Space Beats:  65.51% */

/* Time  Complexity: O(N) */
/* Space Complexity: O(1) */
class Solution_Cycle {
public:
    void rotate(vector<int>& nums, int k)
    {
        const int N = nums.size();
        k %= N;

        int done = 0; // Amount of numbers put at the correct index

        int start_idx = 0; // Start of sub-cycle within "nums".
        while (done < N)
        {
            int curr_idx = start_idx;
            int prev_val = nums[start_idx];

            do {
                int next_idx = (curr_idx + k) % N;

                swap(prev_val, nums[next_idx]);

                curr_idx = next_idx;
                done++;
            } while (start_idx != curr_idx);

            // Increment
            start_idx++;
        }
    }
};
