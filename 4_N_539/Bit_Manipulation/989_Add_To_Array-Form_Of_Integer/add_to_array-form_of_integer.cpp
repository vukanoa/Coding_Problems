#include <iostream>
#include <vector>

/*
    ============
    === EASY ===
    ============

    =================================
    989) Add to Array-Form of Integer
    =================================

    ============
    Description:
    ============

    The array-form of an integer num is an array representing its digits in
    left to right order.

        For example, for num = 1321, the array form is [1,3,2,1].

    Given num, the array-form of an integer, and an integer k, return the
    array-form of the integer num + k.

    ==============================================================
    FUNCTION: vector<int> addToArrayForm(vector<int>& num, int k);
    ==============================================================

    ==========================================================================
    ================================ EXAMPLES ================================
    ==========================================================================

    --- Example 1 ---
    Input: num = [1,2,0,0], k = 34
    Output: [1,2,3,4]
    Explanation: 1200 + 34 = 1234

    --- Example 2 ---
    Input: num = [2,7,4], k = 181
    Output: [4,5,5]
    Explanation: 274 + 181 = 455

    --- Example 3 ---
    Input: num = [2,1,5], k = 806
    Output: [1,0,2,1]
    Explanation: 215 + 806 = 1021

    *** Constraints ***
    1 <= num.length <= 10^4
    0 <= num[i] <= 9
    num does not contain any leading zeros except for the zero itself.
    1 <= k <= 10^4

*/

/*
    ------------
    --- IDEA ---
    ------------

    TODO

*/

/* Time  Beats: 82.21% */
/* Space Beats: 41.33% */

/* Time  Complexity: O(n) */
/* Space Complexity: O(1) */
class Solution {
public:
    std::vector<int> addToArrayForm(std::vector<int>& nums, int k)
    {
        vector<int>result;
        int i = nums.size()-1;
        int carry = 0;

        // both number and array of same size
        while(i >= 0 && k > 0)
        {
            int left = k % 10;
            k /= 10;

            int sum = nums[i] + left + carry;
            carry = sum / 10;
            sum %= 10;

            result.push_back(sum);
            i--;
        }

        // when array is big
        while(i >= 0)
        {
            int sum = nums[i] + carry;
            carry = sum / 10;
            sum %= 10;

            result.push_back(sum);
            i--;
        }

        // when number is big
        while(k > 0)
        {
            int left = k % 10;
            k /= 10;

            int sum =  left + carry;
            carry = sum / 10;
            sum %= 10;

            result.push_back(sum);
        }

        while(carry != 0)
        {
            int sum = carry;
            carry = sum / 10;
            sum %= 10;

            result.push_back(sum);
        }

        std::reverse(result.begin(), result.end());

        return result;
    }
};




/*
    ------------
    --- IDEA ---
    ------------

    TODO

*/

/* Time  Beats: 82.21% */
/* Space Beats: 90.72% */

/* Time  Complexity: O(n) */
/* Space Complexity: O(1) */
class Solution_Concise_Efficient {
public:
    std::vector<int> addToArrayForm(vector<int> &nums, int k)
    {
        int i, size = nums.size();

        for (i = size - 1; i >= 0 && k != 0; i--)
        {
            k = k + nums[i];
            nums[i] = k % 10;
            k = k / 10;
        }

        while (k != 0)
        {
            nums.insert(nums.begin(), k % 10);
            k = k / 10;
        }

        return nums;
    }
};
