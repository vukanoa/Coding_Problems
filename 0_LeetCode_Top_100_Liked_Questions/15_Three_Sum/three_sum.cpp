/*
    ==============
    === MEDIUM ===
    ==============

    ===========================
    15) 3Sum
    ===========================

    ============
    Description:
    ============

    Given an integer array nums, return all the triplets:
    [nums[i], nums[j], nums[k]] such that i != j, i != k, and j != k, and
    num[i] + nums[j] + nums[k] == 0.

    =====
    Node: Notice that the solution set must not contain duplicate triplets.
    =====

    ==========================================================
    FUNCTION: vector<vector<int>> threeSum(vector<int>& nums);
    ==========================================================

    ==========================================================================
    ================================ EXAMPLES ================================
    ==========================================================================

    --- Example 1 ---
    Input:  nums = [-1, 0, 1, 2, -1, -4]
    Output: [[-1, -1, 2], [-1, 0, 1]]
    Explanation:
    nums[0] + nums[1] + nums[2] = (-1) + 0 +   1  = 0
    nums[0] + nums[2] + nums[4] =   0  + 1 + (-1) = 0
    nums[i] + nums[3] + nums[4] = (-1) + 2 + (-1) = 0

    The distinct triples are [-1, 0, 1] and [-1, -1, 2].
    Notice that the order of the output and the order of the triplets
    does not matter.

    --- Example 2 ---
    Input:  nums = [0, 1, 1]
    Output: []
    Explanation: The only possible triplet does not sum up to 0.

    --- Example 3 ---
    Input: nums = [0, 0, 0]
    Output [[0, 0, 0]]
    Explanation: The only possible triplet sums up to 0

    *** Constraints ***
    3 <= nums.length <= 3000
    -10^5 <= nums[i] <= 10^5
*/

#include <algorithm>
#include <vector>
using namespace std;

/*
    ------------
    --- IDEA ---
    ------------

    Two Sum II should be done prior to this Problem. After it, the solution
    is straightforward.

    Note: "Two Sum II - Input is Sorted" is NOT the same as "Two sum".

    Make sure you do:
        Two Sum II - Input is Sorted

    First we should sort the vector "nums". Why? So that we don't have
    duplicate triplets.

    Consider this example:
        -3 3 4 -3 1 2

    First Triplet: -3, 1, 2
    That's when the first element starts with -3 at position 0.

    But a bit later, our first element is again going to start at value -3, but
    this time at position 3 and since the other two elements that sum up to 0
    are AFTER either of our two -3's, then that means we will have a duplicate
    triplet which is something we are warned about. It's something that we must
    avoid.

    So how do we fulfill this requirement?
    We sort the array and in each outer loop we only ask if 'i' is greater than
    0 and if 'i' is equal to 'i - 1'.

    We ask if 'i' is greater than 0 because if we weren't then for 0th element
    we would've asked if 0th element is equal to an element before the array
    which is some random value(out of bounds). So to avoid this we check
    if 'i' is greater than 0.

    And we ask if nums[i] == nums[i - 1] because only the very first element
    in a "chain of duplicates" in our, now sorted, array should be considered.

    So the previous example:
        -3 3 4 -3 1 2
    Now becomes
        -3 -3 1 2 3 4

    Thus the 2nd -3 won't even be considered. We are just going to skip it.

    And now this problem is divided to two:
        1. This outer for loop
        2. Two Sum II

    Two Sum II is solved using Two Pointer Technique. In the above (sorted)
    example we pick -3 for our first value, and we put two pointers to the end
    of the array and to the first non-duplicate element to the right.

    Now sum all three elements and see if it is greater than 0, lower than 0 or
    equal to 0.

    If it is greater than 0, then decrement the "right" pointer by one.
    If it is lower than 0, then increment the "left" pointer by one.
    If it is equal to 0, put all three elements in vector and push that vector
    to vector of vectors "triplets"(which we are returning).

*/

/* Time  Beats: 78.48% */
/* Space Beats: 54.64% */

/* Time  Complexity: O(N^2)  */
/* Space Complexity: O(logN))*/ // Because of C++'s Intro-Sort
class Solution {
public:
    vector<vector<int>> threeSum(vector<int>& nums)
    {
        const int N = nums.size();
        vector<vector<int>> triplets;

        // O(n * logn)
        sort(nums.begin(), nums.end());

        // O(n^2)
        for (int i = 0; i < N-2; i++)
        {
            if (i > 0 && nums[i] == nums[i - 1])
                continue;

            // Two Sum II
            int L = i+1;
            int R = N-1;
            while (L < R)
            {
                int sum = nums[i] + nums[L] + nums[R];

                if (sum < 0)
                {
                    L++;
                }
                else if (sum > 0)
                {
                    R--;
                }
                else
                {
                    triplets.push_back( {nums[i], nums[L], nums[R]} );

                    L++;
                    while (L < R && nums[L-1] == nums[L])
                        L++;
                }
            }
        }

        return triplets;
    }

};




/*
    ------------
    --- IDEA ---
    ------------

    It's the same as above, however it's implemented with a different way of
    thinking about the problem.

    Instead of trying to find sum == 0, we "fix" the leftmost value, i.e. the
    "target_idx", and then we're trying to find:

        -1 * nums[target_idx]

    Which is equivalent to "Two Sum II - Input is Sorted".
    The only difference is that here we can have multiple triplets and not just
    one single Solution.

    Thefore, once we find the correct sum, i.e. sum == target, we do NOT
    return, instead we move both "L" and "R" pointers forward and backward,
    respectively.

    One of the reason this Implementation is MORE intuitive to me is that once
    we find the correct sum, we move BOTH "L" and "R" instead of just one of
    them.

    Think about it, if we move ONLY "L" pointer forward to the next number that
    is NOT the same, we CERTAINLY will be at a point where sum > target.

    And then we'll need to decrement the sum, i.e. move the "R" pointer
    backwards.

    Since that is the case--Why not do that immediately?


    Also, in the original "Two Sum II - Input is Sorted", most implementations
    have only "L++" or "R--" and they they do the outer loop more times.

    But why would we want that? Why not just move past duplicates immediately
    as one semantic "step"?

*/

/* Time  Beats: 53.46% */
/* Space Beats: 45.30% */

/* Time  Complexity: O(N^2)  */
/* Space Complexity: O(logN))*/ // Because of C++'s Intro-Sort
class Solution_More_Intuitive_To_Me {
public:
    vector<vector<int>> threeSum(vector<int>& nums)
    {
        const int N = nums.size();
        vector<vector<int>> result;

        /* Sort */
        sort(nums.begin(), nums.end());

        int target_idx = 0;
        while (target_idx < N-2)
        {
            int target = -1 * nums[target_idx];

            int L = target_idx + 1;
            int R = N-1;

            /* Two Sum II - Input is Sorted */
            while (L < R)
            {
                int sum = nums[L] + nums[R];

                if (sum == target)
                {
                    result.push_back( {nums[target_idx], nums[L], nums[R]} );

                    L++;
                    while (L < R && nums[L-1] == nums[L])
                        L++;

                    R--;
                    while (L < R && nums[R] == nums[R+1])
                        R--;
                }
                else if (sum < target)
                {
                    L++;
                    while (L < R && nums[L-1] == nums[L])
                        L++;
                }
                else
                {
                    R--;
                    while (L < R && nums[R] == nums[R+1])
                        R--;
                }
            }

            // Increment
            target_idx++;
            while (target_idx < N-2 && nums[target_idx-1] == nums[target_idx])
                target_idx++;
        }

        return result;
    }
};
