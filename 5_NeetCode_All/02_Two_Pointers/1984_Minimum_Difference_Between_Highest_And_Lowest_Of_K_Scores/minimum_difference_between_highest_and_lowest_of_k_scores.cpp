/*
    ============
    === EASY ===
    ============

    ===============================================================
    1984) Minimum Difference Between Highest and Lowest of K Scores
    ===============================================================

    ============
    Description:
    ============

    You are given a 0-indexed integer array nums, where nums[i] represents the
    score of the ith student. You are also given an integer k.

    Pick the scores of any k students from the array so that the difference
    between the highest and the lowest of the k scores is minimized.

    Return the minimum possible difference.

    ==========================================================
    FUNCTION: int minimumDifference(vector<int>& nums, int k);
    ==========================================================

    ==========================================================================
    ================================ EXAMPLES ================================
    ==========================================================================

    --- Example 1 ---
    Input: nums = [90], k = 1
    Output: 0
    Explanation: There is one way to pick score(s) of one student:
    - [90]. The difference between the highest and lowest score is 90 - 90 = 0.
    The minimum possible difference is 0.


    --- Example 2 ---
    Input: nums = [9,4,1,7], k = 2
    Output: 2
    Explanation: There are six ways to pick score(s) of two students:
    - [9,4,1,7]. Difference between the highest and lowest score is 9 - 4 = 5.
    - [9,4,1,7]. Difference between the highest and lowest score is 9 - 1 = 8.
    - [9,4,1,7]. Difference between the highest and lowest score is 9 - 7 = 2.
    - [9,4,1,7]. Difference between the highest and lowest score is 4 - 1 = 3.
    - [9,4,1,7]. Difference between the highest and lowest score is 7 - 4 = 3.
    - [9,4,1,7]. Difference between the highest and lowest score is 7 - 1 = 6.
    The minimum possible difference is 2.


    *** Constraints ***
    1 <= k <= nums.length <= 1000
    0 <= nums[i] <= 10^5

*/

#include <climits>
#include <vector>
#include <algorithm>
using namespace std;

/*
    ------------
    --- IDEA ---
    ------------

    Classic Two-Pointer Solution.

*/

/* Time  Beats: 42.80% */
/* Space Beats: 21.47% */

/* Time  Complexity: O(N * logN) */
/* Space Complexity: O(logN)     */ // C++'s Intro Sort
class Solution {
public:
    int minimumDifference(vector<int>& nums, int k)
    {
        const int N = nums.size();
        int result = INT_MAX;

        /* Sort */
        sort(nums.begin(), nums.end()); // O(N * logN)

        int L = 0;
        int R = k-1;

        // O(N - K) (entire block)
        while (R < N)
        {
            result = min(result, nums[R] - nums[L]);

            // Increment
            R++;
            L++;
        }

        return result;
    }
};
