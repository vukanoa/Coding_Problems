/*
    ============
    === EASY ===
    ============

    ===========================
    2614) Prime in Diagonal
    ===========================

    ============
    Description:
    ============

    You are given a 0-indexed two-dimensional integer array nums.

    Return the largest prime number that lies on at least one of the diagonals
    of nums. In case, no prime is present on any of the diagonals, return 0.

    Note that:

        + An integer is prime if it is greater than 1 and has no positive
          integer divisors other than 1 and itself.

        + An integer val is on one of the diagonals of nums if there exists an
          integer i for which nums[i][i] = val or an i for which
          nums[i][nums.length - i - 1] = val.

    In the above diagram, one diagonal is [1,5,9] and another diagonal is
    [3,5,7].

    =======================================================
    FUNCTION: int diagonalPrime(vector<vector<int>>& nums);
    =======================================================

    ==========================================================================
    ================================ EXAMPLES ================================
    ==========================================================================

    --- Example 1 ---
    Input: nums = [[1,2,3],[5,6,7],[9,10,11]]
    Output: 11
    Explanation: The numbers 1, 3, 6, 9, and 11 are the only numbers present
                 on at least one of the diagonals. Since 11 is the largest
                 prime, we return 11.

    --- Example 2 ---
    Input: nums = [[1,2,3],[5,17,7],[9,11,10]]
    Output: 17
    Explanation: The numbers 1, 3, 9, 10, and 17 are all present on at least
                 one of the diagonals. 17 is the largest prime, so we return 17

    *** Constraints ***
    1 <= nums.length <= 300
    nums.length == numsi.length
    1 <= nums[i][j] <= 4*106

*/

#include <cmath>
#include <vector>
using namespace std;

/*
    ------------
    --- IDEA ---
    ------------

    Self-explanatory. If you know how to write a "is_prime" functions, then
    you're done.

*/

/* Time  Beats: 50.97% */
/* Space Beats:  9.61% */

/* Time  Complexity: O(N * sqrt(max_element(nums))) */
/* Space Complexity: O(1)                           */
class Solution {
public:
    int diagonalPrime(vector<vector<int>>& nums)
    {
        const int N = nums.size();
        int result = 0;

        for (int i = 0; i < N; i++)
        {
            if (is_prime(nums[i][i]))
                result = max(result, nums[i][i]);

            if (is_prime(nums[i][N-1 - i]))
                result = max(result, nums[i][N-1 - i]);
        }

        return result;
    }

private:
    bool is_prime(int& num)
    {
        if (num == 1)
            return false;

        for (int factor = 2; factor <= sqrt(num); factor++)
        {
            if (num % factor == 0)
                return false;
        }

        return true;
    }
};
