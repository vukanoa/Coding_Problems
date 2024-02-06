#include <iostream>
#include <vector>
#include <algorithm>

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

/*
    ------------
    --- IDEA ---
    ------------

    Sorting will greatly simplify this problem.

        nums = [9, 3, 5, 8, 4, 1, 7], k = 3
                0  1  2  3  4  5  6

    Becomes:
        nums = [1, 3, 4, 5, 7, 8, 9], k = 3
                0  1  2  3  4  5  6
                      ^
                      |
                      |__
                        |
    We begin at index (k-2) because from that point onward we are able to
    consider previous 'k' numbers because:

        (current_index - k + 1) // +1 because indexing start at 0
         ~~~~~~~~~~~~~~~~~~~~~
                   |
                   |
                   v
        ----------------------------------------------------------
        |Gives us the leftmost element in current range of size k|
        ----------------------------------------------------------

    We know that won't be out of bounds once the i points to index k-1 or
    greater.

    That's why we, simply, begin at that index and we don't have to worry about
    anything else.
*/

/* Time  Beats: 82.29% */
/* Space Beats: 23.67% */

/* Time  Complexity: O(n * logn) */
/* Space Complexity: O(1)        */ // Depending on the Sort. Can be O(n)
class Solution_1 {
public:
    int minimumDifference(std::vector<int>& nums, int k)
    {
        if (k == 1)
            return 0;

        std::sort(nums.begin(), nums.end());
        int min_diff = INT_MAX;

        for (int i = k-1; i < nums.size(); i++)
            min_diff = std::min(min_diff, nums[i] - nums[i+1 - k]);

        return min_diff;
    }
};




/*
    ------------
    --- IDEA ---
    ------------

    Same idea, implemented using while loop where "Two Pointers" technique is
    a bit more explicit.

    Usually "Two Pointers" technique is written using "left" and "right"
    pointer, therefore I wanted to have this Implementation as well.

*/

/* Time  Beats: 82.29% */
/* Space Beats: 42.82% */

/* Time  Complexity: O(n * logn) */
/* Space Complexity: O(1)        */ // Depending on the Sort. Can be O(n)
class Solution_2 {
public:
    int minimumDifference(vector<int>& nums, int k)
    {
        if (k == 1)
            return 0;

        std::sort(nums.begin(), nums.end());
        int min_diff = INT_MAX;

        int left  = 0;
        int right = k-1;

        while (right < nums.size())
            min_diff = std::min(min_diff, nums[right++] - nums[left++]);

        return min_diff;
    }
};
