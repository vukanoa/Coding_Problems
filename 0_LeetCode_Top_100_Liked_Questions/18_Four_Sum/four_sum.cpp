/*
    ==============
    === MEDIUM ===
    ==============

    ===========================
    18) 4Sum
    ===========================

    ============
    Description:
    ============

    Given an array nums of n integers, return an array of all the unique
    quadruplets [nums[a], nums[b], nums[c], nums[d]] such that:
        0 <= a, b, c, d < n
        a, b, c, and d are distinct
        nums[a] + nums[b] + nums[c] + nums[d] == target

    =====
    Node: You may return the answer in any order.
    =====

    =====================================================================
    FUNCTION: vector<vector<int>> fourSum(vector<int>& nums, int target);
    =====================================================================

    ==========================================================================
    ================================ EXAMPLES ================================
    ==========================================================================

    --- Example 1 ---
    Input:  nums = [1, 0, -1, 0, -2, 2], target = 0
    Output: [[-2, -1, 1, 2], [-2, 0, 0, 2], [-1, 0, 0, 1]]

    --- Example 2 ---
    Input:  nums = [2, 2, 2, 2, 2], target = 8
    Output: [[2, 2, 2, 2]]

    *** Constraints ***
    1 <= nums.length <= 200
    -10^9 <= nums[i] <= 10^9
    -10^9 <= target  <= 10^9

*/

#include <algorithm>
#include <vector>
using namespace std;

/*
    ------------
    --- IDEA ---
    ------------

    This problem is a follow-up of 3Sum, so take a look at that problem first
    if you haven't already.

    4Sum and 3Sum are very similar; the difference is that we are looking for
    unique quadruplets instead of triplets.

    As you see, 3Sum just wraps Two Sum(Two Sum II actually) in an outer loop.
    As it iterates through each value, it finds all pairs whose sum is equal to
    "(target - v)" using one of these approaches:

        1. "Two Sum" uses a hash set to check for a matching value.
        2. "Two Sum II" uses the two pointers technique in a sorted array.

    Following a similar logic, we can implement 4Sum by wrapping 3 Sum in
    another loop.
    But wait - there is a catch. If an interviewer asks you to solve 4Sum, they
    can follow-up with: 5Sum, 6Sum, and so on. What they are really expecting
    at this point is a kSum solution. Therefore, we will focus on a generalized
    implementation here.

    Approach 1: Two Pointers Technique

    The two pointers technique requires the array to be sorted, so we do that
    first. Also, it's easier to deal with duplicates if the array is sorted:
    Repeated values are next to each other and easy to skip.

    For 3Sum, we enumerate each value in a single loop, and use the two
    pointers technique for the rest of the array. For kSum, we will have k - 2
    nested loops to enumerate all combinations of k - 2 values.

        R -----------------------------------
                                            |
        L -----------------                 |
                          |                 |
                          |                 |
                          v     Two Sum     v
                          ________^___________
    1    2    ...    5    10    15    20    25
    k   k-1          ___________ _____________
                                v
                               3Sum

    We can implement k - 2 loops using a recursion. We will pass the starting
    point and 'k' as the parameters. When k == 2, we will call two_sum_II,
    terminating the recursion.

    1. For the main function:
        + Sort the input array "nums"
        + Calls kSum with k = 4, start = 0, and "target", and return the result

    2. For kSum function:
        + Fix the k-th one and call the kSum with k=k-1
        + Once we get to k==2, we're dealing with two_sum_ii

*/

/* Time  Beats: 99.50% */
/* Space Beats: 42.89% */

/* Time  Complexity: O(N^(k-1)) */
/* Space Complexity: O(K)       */
/*
    Time  Complexity: O(N^(k - 1)), or O(N^3) for 4Sum.
*/
/*
    Space Complexity: O(logN) for sorting + O(K) for the recursion.
    k can be the same as n in the worst case for the generalized algorithm.
*/
class Solution {
private:
    vector<int> k_duplet;
    vector<vector<int>> result;

public:
    vector<vector<int>> fourSum(vector<int>& nums, int target)
    {
        /* Sort */
        sort(nums.begin(), nums.end()); // O(N * logN)

        // O(N^(k-1)) 
        k_sum(nums, target, 0, 4); 

        return result;
    }

    void k_sum(vector<int>& nums, long long target, int start, int k)
    {
        const int N = nums.size();

        if (k == 3)
        {
            three_sum(nums, target, start);
        }
        else // k >= 4
        {
            for (int i = start; i < N-k+1; i++)
            {
                if (i > start && nums[i-1] == nums[i])
                    continue;

                int new_target = target - nums[i];

                k_duplet.push_back(nums[i]);
                k_sum(nums, new_target, i+1, k-1);
                k_duplet.pop_back();
            }
        }
    }

    void three_sum(vector<int>& nums, long long target, int start)
    {
        const int N = nums.size();

        /* Three_Sum */
        int i = start;
        while (i < N-2)
        {
            long long curr_target = target - nums[i];

            int L = i + 1;
            int R = N-1;

            /* Two Sum II - Input is Sorted */
            while (L < R)
            {
                int sum = nums[L] + nums[R];

                if (sum == curr_target)
                {
                    k_duplet.push_back(nums[i]);
                    k_duplet.push_back(nums[L]);
                    k_duplet.push_back(nums[R]);

                    result.push_back(k_duplet);

                    k_duplet.pop_back();
                    k_duplet.pop_back();
                    k_duplet.pop_back();

                    // Single semantic step
                    L++;
                    while (L < R && nums[L-1] == nums[L])
                        L++;

                    // Single semantic step
                    R--;
                    while (L < R && nums[R] == nums[R+1])
                        R--;
                }
                else if (sum < curr_target)
                {
                    // Single semantic step
                    L++;
                    while (L < R && nums[L-1] == nums[L])
                        L++;
                }
                else
                {
                    // Single semantic step
                    R--;
                    while (L < R && nums[R] == nums[R+1])
                        R--;
                }
            }

            // Increment (Skip over duplicates)
            i++;
            while (i < N-2 && nums[i-1] == nums[i])
                i++;
        }
    }
};




/*
    ------------
    --- IDEA ---
    ------------

    This is specifically 4Sum implementation, not a KSum.

*/

/* Time  Beats: 73.48% */
/* Space Beats: 54.52% */

/* Time  Complexity: O(N^3) */
/* Space Complexity: O(N)   */
class Solution_Specifically_4Sum {
public:
    vector<vector<int>> fourSum(vector<int>& nums, int target)
    {
        const int N = nums.size();
        vector<vector<int>> result;

        /* Sort */
        sort(nums.begin(), nums.end()); // O(N * logN)

        // O(N^3) (entire block)
        for (int start = 0; start < N-3; start++) // O(N)
        {
            // Skip over duplicates
            if (start > 0 && nums[start-1] == nums[start])
                continue;

            long long new_target = target - nums[start];

            /* Three_Sum */
            int i = start+1;
            while (i < N-2) // O(N^2)
            {
                long long curr_target = new_target - nums[i];

                int L = i+1;
                int R = N-1;

                /* Two Sum II - Input is Sorted */
                while (L < R)
                {
                    int sum = nums[L] + nums[R];

                    if (sum == curr_target)
                    {
                        result.push_back( {nums[start], nums[i], nums[L], nums[R]} );

                        // Single semantic step
                        L++;
                        while (L < R && nums[L-1] == nums[L])
                            L++;

                        // Single semantic step
                        R--;
                        while (L < R && nums[R] == nums[R+1])
                            R--;
                    }
                    else if (sum < curr_target)
                    {
                        // Single semantic step
                        L++;
                        while (L < R && nums[L-1] == nums[L])
                            L++;
                    }
                    else
                    {
                        // Single semantic step
                        R--;
                        while (L < R && nums[R] == nums[R+1])
                            R--;
                    }
                }

                // Increment (Skip over duplicates)
                i++;
                while (i < N-2 && nums[i-1] == nums[i])
                    i++;
            }
        }

        return result;
    }
};
