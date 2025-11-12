/*
    ==============
    === MEDIUM ===
    ==============

    ========================================================================
    2654) Minimum Number of Operations to Make All Array Elements Equal to 1
    ========================================================================

    ============
    Description:
    ============

    You are given a 0-indexed array nums consisiting of positive integers. You
    can do the following operation on the array any number of times:

        + Select an index i such that 0 <= i < n - 1 and replace either of
          nums[i] or nums[i+1] with their gcd value.

    Return the minimum number of operations to make all elements of nums equal
    to 1. If it is impossible, return -1.

    The gcd of two integers is the greatest common divisor of the two integers.

    ===============================================
    FUNCTION: int minOperations(vector<int>& nums);
    ===============================================

    ==========================================================================
    ================================ EXAMPLES ================================
    ==========================================================================

    --- Example 1 ---
    Input: nums = [2,6,3,4]
    Output: 4
    Explanation: We can do the following operations:
    - Choose index i = 2 and replace nums[2] with gcd(3,4) = 1. Now we have nums = [2,6,1,4].
    - Choose index i = 1 and replace nums[1] with gcd(6,1) = 1. Now we have nums = [2,1,1,4].
    - Choose index i = 0 and replace nums[0] with gcd(2,1) = 1. Now we have nums = [1,1,1,4].
    - Choose index i = 2 and replace nums[3] with gcd(1,4) = 1. Now we have nums = [1,1,1,1].

    --- Example 2 ---
    Input: nums = [2,10,6,14]
    Output: -1
    Explanation: It can be shown that it is impossible to make all the elements
                 equal to 1.


    *** Constraints ***
    2 <= nums.length <= 50
    1 <= nums[i] <= 10^6

*/

#include <algorithm>
#include <numeric>
#include <vector>
using namespace std;


/*
    ------------
    --- IDEA ---
    ------------

    TODO

*/

/* Time  Beats: 100.00% */
/* Space Beats:  34.03% */

/* Time  Complexity: O(N^2 * log(max(nums[i]))) */
/* Space Complexity: O(1)                       */
class Solution {
public:
    int minOperations(vector<int>& nums)
    {
        const int N = nums.size();

        // Step 1: If we already have 1's, then spread out that 1s to non-1s.
        int ones = count(nums.begin(), nums.end(), 1);
        if (ones > 0)
            return N - ones;

        // Step 2: Find shortest subarray with gcd == 1
        int min_subarray_len = N + 1;
        for (int i = 0; i < N; i++)
        {
            int curr_gcd = nums[i];
            for (int j = i+1; j < N; j++)
            {
                curr_gcd = gcd(curr_gcd, nums[j]);

                if (curr_gcd == 1)
                {
                    int curr_subarray_len = j - i + 1;
                    min_subarray_len = min(min_subarray_len, curr_subarray_len);
                    break;
                }
            }
        }

        // Step 3: If we have NOT found a subarray in entire nums with gcd == 1
        if (min_subarray_len == N + 1)
            return -1; // Then it's impossible

        // Step 4: Create 1, then spread it
        return (min_subarray_len - 1) + (N - 1);
    }

private:
    int gcd(int a, int b)
    {
        return b == 0 ? a : gcd(b, a % b);
    }
};




/*
    ------------
    --- IDEA ---
    ------------

    TODO

*/

/* Time  Beats: 100.00% */
/* Space Beats:  93.06% */

/* Time  Complexity: O(N^2 * log(max(nums[i]))) */
/* Space Complexity: O(1)                       */
class Solution_2 {
public:
    int minOperations(vector<int>& nums)
    {
        const int N = nums.size();

        int ones = count(nums.begin(), nums.end(), 1);
        if (ones > 0)
            return N - ones;

        for (int curr_subarray_len = 2; curr_subarray_len <= N; curr_subarray_len++)
        {
            for (int l = 0; l <= N - curr_subarray_len; l++)
            {
                int curr_gcd = nums[l] = gcd(nums[l], nums[l+1]);

                if (curr_gcd == 1)
                    return curr_subarray_len + N-2;
            }
        }

        return -1;
    }
};
