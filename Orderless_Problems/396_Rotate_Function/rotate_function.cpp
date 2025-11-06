/*
    ==============
    === MEDIUM ===
    ==============

    ===========================
    396) Rotate Function
    ===========================

    ============
    Description:
    ============

    You are given an integer array nums of length n.

    Assume arrk to be an array obtained by rotating nums by k positions
    clock-wise. We define the rotation function F on nums as follow:

        F(k) = 0 * arrk[0] + 1 * arrk[1] + ... + (n - 1) * arrk[n - 1].

    Return the maximum value of F(0), F(1), ..., F(n-1).

    The test cases are generated so that the answer fits in a 32-bit integer.

    ===================================================
    FUNCTION: int maxRotateFunction(vector<int>& nums);
    ===================================================

    ==========================================================================
    ================================ EXAMPLES ================================
    ==========================================================================

    --- Example 1 ---
    Input: nums = [4,3,2,6]
    Output: 26
    Explanation:
    F(0) = (0 * 4) + (1 * 3) + (2 * 2) + (3 * 6) = 0 + 3 + 4 + 18 = 25
    F(1) = (0 * 6) + (1 * 4) + (2 * 3) + (3 * 2) = 0 + 4 + 6 + 6 = 16
    F(2) = (0 * 2) + (1 * 6) + (2 * 4) + (3 * 3) = 0 + 6 + 8 + 9 = 23
    F(3) = (0 * 3) + (1 * 2) + (2 * 6) + (3 * 4) = 0 + 2 + 12 + 12 = 26
    So the maximum value of F(0), F(1), F(2), F(3) is F(3) = 26.

    --- Example 2 ---
    Input: nums = [100]
    Output: 0


    *** Constraints ***
    n == nums.length
    1 <= n <= 10^5
    -100 <= nums[i] <= 100

*/

#include <climits>
#include <vector>
using namespace std;

/*
    ------------
    --- IDEA ---
    ------------

    Let us do some pre-processing using basic Math:
    Let the array elements be:

            [a b c d e].

    Length of array represented by N = 5
    Sum of elements of array represented by SUM = a + b + c + d + e

    Now, as per the question:

    F(0) = (0 * a) + (1 * b) + (2 * c) + (3 * d) + (4 * e) =  0 +  b + 2c + 3d + 4e
    F(1) = (1 * a) + (2 * b) + (3 * c) + (4 * d) + (0 * e) =  a + 2b + 3c + 4d +  0
    F(2) = (2 * a) + (3 * b) + (4 * c) + (0 * d) + (1 * e) = 2a + 3b + 4c +  0 +  e

    Now subtracting 2 equations:

    F(1) - F(0) = a + b + c + d - 4e = a + b + c + d + e - 5e
    Therefore, F(1) = F(0) + a + b + c + d + e - 5e = F(0) + SUM - N*e

    F(2) - F(1) = a + b + c + e - 4d = a + b + c + d + e - 5d
    Therefore, F(2) = F(1) + a + b + c + d + e - 5d = F(1) + SUM - N*d

    Generalizing it, we get the following relation:

    F(K) = F(K-1) + SUM - N * (( K-1)th element from end of array) i.e.

    F(K) = F(K-1) + SUM - N * (array [N - 1 - (K-1)]) = F(K-1) + SUM - N * (array [N - K])

    Now it's pretty clear that we can re-use previously calculated Fx so solve
    the next until we solve all of them and find the maximum.

*/

/* Time  Beats: 44.42% */
/* Space Beats: 48.52% */

/* Time  Complexity: O(N) */
/* Space Complexity: O(1) */
class Solution {
public:
    int maxRotateFunction(vector<int>& nums)
    {
        const int N = nums.size();

        if (N == 0)
            return 0;

        long long sum = 0;
        long long F0 = 0;

        for (int i = 0; i < N; i++)
        {
            sum += nums[i];
            F0  += 1LL * i * nums[i];
        }

        long long result = F0;
        long long prev = F0;

        for (int i = 1; i < N; i++)
        {
            long long curr = prev + sum - 1LL * N * nums[N - i];

            result = max(result, curr);
            prev = curr;
        }

        return static_cast<int>(result);
    }
};
