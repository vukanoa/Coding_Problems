/*
    ==============
    === MEDIUM ===
    ==============

    =======================================================
    2294) Partition Array Such That Maximum Difference Is K
    =======================================================

    ============
    Description:
    ============

    You are given an integer array nums and an integer k. You may partition
    nums into one or more subsequences such that each element in nums appears
    in exactly one of the subsequences.

    Return the minimum number of subsequences needed such that the difference
    between the maximum and minimum values in each subsequence is at most k.

    A subsequence is a sequence that can be derived from another sequence by
    deleting some or no elements without changing the order of the remaining
    elements.

    =======================================================
    FUNCTION: int partitionArray(vector<int>& nums, int k);
    =======================================================

    ==========================================================================
    ================================ EXAMPLES ================================
    ==========================================================================

    --- Example 1 ---
    Input: nums = [3,6,1,2,5], k = 2
    Output: 2
    Explanation:
    We can partition nums into the two subsequences [3,1,2] and [6,5].
    The difference between the maximum and minimum value in the first subsequence is 3 - 1 = 2.
    The difference between the maximum and minimum value in the second subsequence is 6 - 5 = 1.
    Since two subsequences were created, we return 2. It can be shown that 2 is
    the minimum number of subsequences needed.

    --- Example 2 ---
    Input: nums = [1,2,3], k = 1
    Output: 2
    Explanation:
    We can partition nums into the two subsequences [1,2] and [3].
    The difference between the maximum and minimum value in the first subsequence is 2 - 1 = 1.
    The difference between the maximum and minimum value in the second subsequence is 3 - 3 = 0.
    Since two subsequences were created, we return 2. Note that another optimal
    solution is to partition nums into the two subsequences [1] and [2,3].

    --- Example 3 ---
    Input: nums = [2,2,4,5], k = 0
    Output: 3
    Explanation:
    We can partition nums into the three subsequences [2,2], [4], and [5].
    The difference between the maximum and minimum value in the first subsequences is 2 - 2 = 0.
    The difference between the maximum and minimum value in the second subsequences is 4 - 4 = 0.
    The difference between the maximum and minimum value in the third subsequences is 5 - 5 = 0.
    Since three subsequences were created, we return 3. It can be shown that 3
    is the minimum number of subsequences needed.


    *** Constraints ***
    1 <= nums.length <= 10^5
    0 <= nums[i] <= 10^5
    0 <= k <= 10^5

*/

#include <algorithm>
#include <vector>
using namespace std;

/*
    ------------
    --- IDEA ---
    ------------

    Self-explanatory.

    The most basic example of a "Sort Problem".

*/

/* Time  Beats: 81.44% */
/* Space Beats: 71.13% */

/* Time  Complexity: O(N * logN) */
/* Space Complexity: O(logn)     */ // C++'s sort is taking O(logN) extra space
class Solution {
public:
    int partitionArray(vector<int>& nums, int k)
    {
        const int N = nums.size();

        sort(nums.begin(), nums.end());

        int result = 1;

        int L = 0;
        int R = 1;
        while (R < N)
        {
            if (nums[R] - nums[L] > k) // Then start a new subsequence
            {
                result++;
                L = R;
            }

            // Increment
            R++;
        }

        return result;
    }
};




/*
    ------------
    --- IDEA ---
    ------------

    Big O Time Complexiy is the same, however once we have a vector of sorted
    elements--Why not just use Binary Search to improve that part as well?

    That's what we're doing here.

*/

/* Time  Beats: 48.25% */
/* Space Beats: 39.38% */

/* Time  Complexity: O(N * logN) */
/* Space Complexity: O(logn)     */ // C++'s sort is taking O(logN) extra space
class Solution_Optimization {
public:
    static int partitionArray(vector<int>& nums, int k)
    {
        const int N = nums.size();
        int partitions = 0;

        sort(nums.begin(), nums.end());
        for (int i = 0; i < N;)
        {
            i = upper_bound(nums.begin()+i, nums.end(), nums[i]+k) - nums.begin();
            partitions++;
        }

        return partitions;
    }
};
