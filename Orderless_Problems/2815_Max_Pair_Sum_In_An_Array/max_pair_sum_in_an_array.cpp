/*
    ============
    === EASY ===
    ============

    ==============================
    2815) Max Pair Sum in an Array
    ==============================

    ============
    Description:
    ============

    You are given an integer array nums. You have to find the maximum sum of a
    pair of numbers from nums such that the largest digit in both numbers is
    equal.

    For example, 2373 is made up of three distinct digits: 2, 3, and 7, where 7
    is the largest among them.

    Return the maximum sum or -1 if no such pair exists.

    ========================================
    FUNCTION: int maxSum(vector<int>& nums);
    ========================================

    ==========================================================================
    ================================ EXAMPLES ================================
    ==========================================================================

    --- Example 1 ---
    Input: nums = [112,131,411]
    Output: -1
    Explanation:
    Each numbers largest digit in order is [2,3,4].

    --- Example 2 ---
    Input: nums = [2536,1613,3366,162]
    Output: 5902
    Explanation:
    All the numbers have 6 as their largest digit, so the answer is 2536 + 3366
    = 5902.

    --- Example 3 ---
    Input: nums = [51,71,17,24,42]
    Output: 88
    Explanation:
    Each number's largest digit in order is [5,7,7,4,4].
    So we have only two possible pairs, 71 + 17 = 88 and 24 + 42 = 66.


    *** Constraints ***
    2 <= nums.length <= 100
    1 <= nums[i] <= 10^4

*/

#include <cstring>
#include <vector>
using namespace std;

/*
    ------------
    --- IDEA ---
    ------------

    We only need to keep track of the two biggest numbers for each of the
    possible maximum digits in a number, which are obviously [0, 9].

    That's why this solves the entire problem.

        int numbers_with_largest[10][2]; // {2nd_biggest, biggest}
        
        // Memset with 0xff <==> -1
        memset(numbers_with_largest, 0xff, sizeof(numbers_with_largest));

*/

/* Time  Beats: 100.00% */
/* Space Beats:  74.44% */

/* Time  Complexity: O(N * logM) */
/* Space Complexity: O(1)        */
class Solution {
public:
    int maxSum(vector<int>& nums)
    {
        const int N = nums.size();
        int result = -1;

        int numbers_with_largest[10][2]; // {2nd_biggest, biggest}
        
        /* Memset with 0xff <==> -1 */
        memset(numbers_with_largest, 0xff, sizeof(numbers_with_largest));

        for (int i = 0; i < N; i++)
        {
            int digit = largest_digit(nums[i]);

            if (nums[i] >= numbers_with_largest[digit][1])
            {
                numbers_with_largest[digit][0] = numbers_with_largest[digit][1];
                numbers_with_largest[digit][1] = nums[i]; // New biggest
            }
            else if (nums[i] > numbers_with_largest[digit][0])
            {
                numbers_with_largest[digit][0] = nums[i]; // 2nd_biggest
            }
        }

        for (int digit = 0; digit <= 9; digit++)
        {
            if (numbers_with_largest[digit][0] != -1 &&
                numbers_with_largest[digit][1] != -1)
            {
                result = max(result, numbers_with_largest[digit][0] +
                                     numbers_with_largest[digit][1]);
            }
        }

        return result;
    }

private:
    int largest_digit(int number)
    {
        int largest = 0;
        while (number > 0)
        {
            largest = max(largest, number % 10);
            number /= 10;
        }

        return largest;
    }
};




/*
    ------------
    --- IDEA ---
    ------------

    A slightly faster implementation, though a lot less verbose and less
    readable.

*/

/* Time  Complexity: O(N * logM) */
/* Space Complexity: O(1)        */
class Solution_Terse {
public:
    int maxSum(vector<int>& nums)
    {
        int result = -1;
        int max_num[10] = {0};

        // O(N * logM) (entire block)
        for (const int& num : nums) // O(N)
        {
            int largest_digit = 0;

            // O(logM) (entire block)
            for (int num_copy = num; num_copy; num_copy /= 10)
                largest_digit = max(largest_digit, num_copy % 10);

            if (max_num[largest_digit])
                result = max(result, max_num[largest_digit] + num);

            max_num[largest_digit] = max(max_num[largest_digit], num);
        }

        return result;
    }
};
