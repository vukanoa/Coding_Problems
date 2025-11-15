/*
    ============
    === EASY ===
    ============

    ===============================================
    1979) Find the Greatest Common Divisor of Array
    ===============================================

    ============
    Description:
    ============

    Given an integer array nums, return the greatest common divisor of the
    smallest number and largest number in nums.

    The greatest common divisor of two numbers is the largest positive integer
    that evenly divides both numbers.

    =========================================
    FUNCTION: int findGCD(vector<int>& nums);
    =========================================

    ==========================================================================
    ================================ EXAMPLES ================================
    ==========================================================================

    --- Example 1 ---
    Input: nums = [2,5,6,9,10]
    Output: 2
    Explanation:
    The smallest number in nums is 2.
    The largest number in nums is 10.
    The greatest common divisor of 2 and 10 is 2.

    --- Example 2 ---
    Input: nums = [7,5,6,8,3]
    Output: 1
    Explanation:
    The smallest number in nums is 3.
    The largest number in nums is 8.
    The greatest common divisor of 3 and 8 is 1.

    --- Example 3 ---
    Input: nums = [3,3]
    Output: 3
    Explanation:
    The smallest number in nums is 3.
    The largest number in nums is 3.
    The greatest common divisor of 3 and 3 is 3.


    *** Constraints ***
    2 <= nums.length <= 1000
    1 <= nums[i] <= 1000

*/

#include <algorithm>
#include <vector>
using namespace std;

/*
    ------------
    --- IDEA ---
    ------------

    Self-explanatory. Simulation problem.

*/

/* Time  Beats: 100.00% */
/* Space Beats:  90.41% */

/* Time  Complexity: O(N + log(min(a,b))) */
/* Space Complexity: O(log(min(a,b)))     */ // Because of recursion
class Solution {
public:
    int findGCD(vector<int>& nums)
    {
        const int N = nums.size();

        int min_elem = *min_element(nums.begin(), nums.end());
        int max_elem = *max_element(nums.begin(), nums.end());

        return my_gcd(min_elem, max_elem);
    }

private:
    int my_gcd(int a, int b)
    {
        return (b == 0) ? a : my_gcd(b, a % b);
    }
};
