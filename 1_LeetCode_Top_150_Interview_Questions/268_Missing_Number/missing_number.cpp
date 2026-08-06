/*
    ============
    === EASY ===
    ============

    ===========================
    268) Missing Number
    ===========================

    ============
    Description:
    ============

    Given an array nums containing n distinct numbers in the range [0, n],
    return the only number in the range that is missing from the array.


    Follow up: Could you implement a solution using only O(1) extra space
    complexity and O(n) runtime complexity?

    ====================================================
    FUNCTION: int missingNumber(vector<int>& nums);
    ====================================================

    ==========================================================================
    ================================ EXAMPLES ================================
    ==========================================================================


    --- Example 1 ---
    Input: nums = [3,0,1]
    Output: 2
    Explanation: n = 3 since there are 3 numbers, so all numbers are in the
    range [0,3]. 2 is the missing number in the range since it does not appear
    in nums.


    --- Example 2 ---
    Input: nums = [0,1]
    Output: 2
    Explanation: n = 2 since there are 2 numbers, so all numbers are in the
    range [0,2]. 2 is the missing number in the range since it does not appear
    in nums.


    --- Example 3 ---
    Input: nums = [9,6,4,2,3,5,7,0,1]
    Output: 8
    Explanation: n = 9 since there are 9 numbers, so all numbers are in the
    range [0,9]. 8 is the missing number in the range since it does not appear
    in nums.


    *** Constraints ***
    n == nums.length
    1 <= n <= 104
    0 <= nums[i] <= n
    All the numbers of nums are unique.

*/

#include <numeric>
#include <vector>
using namespace std;

/*
    ------------
    --- IDEA ---
    ------------

    Since we're given an array "nums" containing n distinct numbers in the
    range [0, n] where only ONE number is missing, we can calculate the sum
    of the first n numbers(numbers from 0 to n, inclusive) and then subtract
    the elements that actually exist in the vector "nums".

    At the end, we'll end up with the missing number in variable "sum".

*/

/* Time  Beats: 94.70% */
/* Space Beats: 90.75% */

/* Time  Complexity: O(N) */
/* Space Complexity: O(1) */
class Solution_Add_Subtract {
public:
    int missingNumber(vector<int>& nums)
    {
        const int N = nums.size();

        int sum = 0;
        for (int i = 0; i <= N; i++)
            sum += i;

        for (int i = 0; i < N; i++)
            sum -= nums[i];

        return sum;
    }
};




/*
    ------------
    --- IDEA ---
    ------------

    It doesn't matter in which order you XOR elements.
    XOR: 5 ^ 5 ^ 3 is equivalent to 5 ^ 3 ^ 5 or any other combination.

    When XOR-ing two equal numbers, the result is always zero.
    When XOR-ing two numbers a ^ b, if either is 0, the result is the non-0 one

    So, since we're told that "nums" contains n distinct numbers in the
    range [0, N] where only ONE number is missing, we can XOR first N numbers
    and then additionally XOR all the numbers in the vector "nums" which will
    leave us with the missing number.

    --- Example 1 ---
    Input: nums = [3, 0, 1]
    Output: 2

    First n numbers:  [0, 1, 2, 3]
    numbers in nums:  [0, 1,  , 3]

    XOR all those numbers: (Remember, the order doesn't matter)
    0 ^ 0 = 0
    1 ^ 1 = 0
    3 ^ 3 = 0

    and when we XOR number 2(the only number of the first N numbers that we
    didn't XOR yet) with the result up to this point, which is 0. So:

        2 ^ 0 = 2

    And that is the missing number we were looking for.

*/

/* Time  Beats: 99.94% */
/* Space Beats: 47.95% */

/* Time  Complexity: O(n) */
/* Space Complexity: O(1) */
class Solution_XOR {
public:
    int missingNumber(vector<int>& nums)
    {
        const int N = nums.size();

        int sum = 0;
        for (int i = 0; i <= N; i++)
            sum ^= i;

        for (int i = 0; i < N; i++)
            sum ^= nums[i];

        return sum;
    }
};




/*
    ------------
    --- IDEA ---
    ------------

    Another way to implement. I'm including more than one way because some will
    have that "AHA" moment in one but not in other.

*/

/* Time  Beats: 100.00% */
/* Space Beats:  71.51% */

/* Time  Complexity: O(N) */
/* Space Complexity: O(1) */
class Solution_XOR_2 {
public:
    int missingNumber(vector<int>& nums)
    {
        const int N = nums.size();

        int result = N;
        for (int i = 0; i < N; i++)
            result ^= (i ^ nums[i]);

        return result;
    }
};




/*
    ------------
    --- IDEA ---
    ------------

    Same Idea, just implemented using Gaus' method for calculating first N
    numbers.

    Gaus used this method in math class to calculate sum of first 100 numbers
    by adding 1 and 99, 2 and 98, 3 and 97, ..., 49 and 51

    The sum of each of this bids is 100 and there are 49 of them. However
    we didn't add 50 which is in the middle and we didn't add 100 that is at
    the very top.

    Therefore 49 * 100 + 100 + 50 = 4900 + 100 + 50 = 5050

    And the formula is: N * (N + 1) / 2

*/

/* Time  Beats: 99.94% */
/* Space Beats: 47.95% */

/* Time  Complexity: O(N) */
/* Space Complexity: O(1) */
class Solution_Gaus {
public:
    int missingNumber(vector<int>& nums)
    {
        const int N = nums.size();
        int sum_of_first_N = N * (N + 1) / 2;

        for (int i = 0; i < N; i++)
            sum_of_first_N -= nums[i];

        return sum_of_first_N;
    }
};




/*
    ------------
    --- IDEA ---
    ------------

    Another way to implement Gaus' Solution.

*/

/* Time  Beats: 100.00% */
/* Space Beats:  71.51% */

/* Time  Complexity: O(N) */
/* Space Complexity: O(1) */
class Solution_Gaus_2 {
public:
    int missingNumber(vector<int>& nums)
    {
        const int N = nums.size();
        int sum = accumulate(nums.begin(), nums.end(), 0);

        return (N * (N+1) / 2) - sum;
    }
};




/*
    ------------
    --- IDEA ---
    ------------

    Same Idea, implemented differently.
    We add number i and subtract nums[i]. However since we're doing it until
    i < nums.size(), we have to add nums.size(). So just initialize sum with
    nums.size() at the beginning.

*/

/* Time  Beats: 94.70% */
/* Space Beats: 47.95% */

/* Time  Complexity: O(N) */
/* Space Complexity: O(1) */
class Solution_Single_Loop {
public:
    int missingNumber(vector<int>& nums)
    {
        const int N = nums.size();

        int sum = N;
        for (int i = 0; i < N; i++)
            sum += i - nums[i];

        return sum;
    }
};
