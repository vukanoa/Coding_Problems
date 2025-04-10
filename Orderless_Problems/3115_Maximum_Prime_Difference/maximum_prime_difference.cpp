/*
    ==============
    === MEDIUM ===
    ==============

    ==============================
    3115) Maximum Prime Difference
    ==============================

    ============
    Description:
    ============

    You are given an integer array nums.

    Return an integer that is the maximum distance between the indices of two
    (not necessarily different) prime numbers in nums.

    ========================================================
    FUNCTION: int maximumPrimeDifference(vector<int>& nums);
    ========================================================

    ==========================================================================
    ================================ EXAMPLES ================================
    ==========================================================================

    --- Example 1 ---
    Input: nums = [4,2,9,5,3]
    Output: 3
    Explanation: nums[1], nums[3], and nums[4] are prime. So the answer is
    |4 - 1| = 3.


    --- Example 2 ---
    Input: nums = [4,8,2,8]
    Output: 0
    Explanation: nums[2] is prime. Because there is just one prime number, the
    answer is |2 - 2| = 0.


    *** Constraints ***
    1 <= nums.length <= 3 * 10^5
    1 <= nums[i] <= 100
    The input is generated such that the number of prime numbers in the nums is
    at least one.

*/

#include <cmath>
#include <vector>
using namespace std;

/*
    ------------
    --- IDEA ---
    ------------

    TODO

*/

/* Time  Beats: 73.65% */
/* Space Beats: 10.37% */

/* Time  Complexity: O(N + M * log(logM)) */ // N = nums.size(), M = final_num
/* Space Complexity: O(M)                 */
class Solution {
public:
    int maximumPrimeDifference(vector<int>& nums)
    {
        const int N = nums.size();
        int result = 0;

        int final_num = 100;
        vector<bool> prime(final_num + 1, true);

        prime[0] = false;  // 0 is not prime
        prime[1] = false;  // 1 is not prime

        // Sieve of Eratosthenes: O(N * log(log N))
        for (int num = 2; num * num <= final_num; num++)
        {
            if ( ! prime[num])
                continue;

            for (int i = num * num; i <= final_num; i += num)
                prime[i] = false;
        }


        vector<int> indices;
        for (int i = 0; i < N; i++)
        {
            int num = nums[i];

            if (prime[num])
                indices.push_back(i);
        }

        return indices.back() - indices[0];
    }
};
