/*
    ============
    === HARD ===
    ============

    ===========================
    2659) Make Array Empty
    ===========================

    ============
    Description:
    ============

    You are given an integer array nums containing distinct numbers, and you
    can perform the following operations until the array is empty:

        + If the first element has the smallest value, remove it

        + Otherwise, put the first element at the end of the array.

    Return an integer denoting the number of operations it takes to make nums
    empty.

    ===================================================================
    FUNCTION: long long countOperationsToEmptyArray(vector<int>& nums);
    ===================================================================

    ==========================================================================
    ================================ EXAMPLES ================================
    ==========================================================================

    --- Example 1 ---
    Input: nums = [3,4,-1]
    Output: 5
    Operation    Array
    1            [4, -1, 3]
    2            [-1, 3, 4]
    3            [3, 4]
    4            [4]
    5            []

    --- Example 2 ---
    Input: nums = [1,2,4,3]
    Output: 5

    Operation    Array
    1            [2, 4, 3]
    2            [4, 3]
    3            [3, 4]
    4            [4]
    5            []

    --- Example 3 ---
    Input: nums = [1,2,3]
    Output: 3

    Operation    Array
    1            [2, 3]
    2            [3]
    3            []


    *** Constraints ***
    1 <= nums.length <= 10^5
    -10^9 <= nums[i] <= 10^9
    All values in nums are distinct.

*/

#include <algorithm>
#include <vector>
using namespace std;

/*
    ------------
    --- IDEA ---
    ------------

    TODO

*/

/* Time  Beats: 58.90% */
/* Space Beats: 85.89% */

/* Time  Complexity: O(N * logN) */
/* Space Complexity: O(N)        */
class Solution {
public:
    long long countOperationsToEmptyArray(vector<int>& nums)
    {
        const int N = nums.size();

        /* Initialize Indices */
        vector<int> indices(N);

        for (int i = 0; i < N; i++)
            indices[i] = i;

        /* Sort Indices by Values */
        sort(indices.begin(), indices.end(), [&](const int& one, const int& two)
        {
            return nums[one] < nums[two];
        });

        /* Count Operations */
        int remaining_elements = N;
        long long total_operations = 0LL;

        for (int i = 1; i < N; i++)
        {
            if (indices[i - 1] > indices[i])
            {
                total_operations += remaining_elements;
                remaining_elements = N - i;
            }
        }

        total_operations += remaining_elements;

        return total_operations;
    }
};
