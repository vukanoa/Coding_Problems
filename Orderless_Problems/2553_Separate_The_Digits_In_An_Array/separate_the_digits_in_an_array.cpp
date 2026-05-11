/*
    ============
    === EASY ===
    ============

    =====================================
    2553) Separate the Digits in an Array
    =====================================

    ============
    Description:
    ============


    Given an array of positive integers nums, return an array answer that
    consists of the digits of each integer in nums after separating them in the
    same order they appear in nums.

    To separate the digits of an integer is to get all the digits it has in the
    same order.

        For example, for the integer 10921, the separation of its digits is:

            [1,0,9,2,1].

    ========================================================
    FUNCTION: vector<int> separateDigits(vector<int>& nums);
    ========================================================

    ==========================================================================
    ================================ EXAMPLES ================================
    ==========================================================================

    --- Example 1 ---
    Input: nums = [13,25,83,77]
    Output: [1,3,2,5,8,3,7,7]
    Explanation: 
    - The separation of 13 is [1,3].
    - The separation of 25 is [2,5].
    - The separation of 83 is [8,3].
    - The separation of 77 is [7,7].
    answer = [1,3,2,5,8,3,7,7]. Note that answer contains the separations in
                                the same order.

    --- Example 2 ---
    Input: nums = [7,1,3,9]
    Output: [7,1,3,9]
    Explanation: The separation of each integer in nums is itself.
    answer = [7,1,3,9].


    *** Constraints ***
    1 <= nums.length <= 1000
    1 <= nums[i] <= 10^5

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

/* Time  Beats: 100.00% */
/* Space Beats:  5.13% */

/* Time  Complexity: O(D) */ // Where 'D' is a total amount of digits
/* Space Complexity: O(D) */
class Solution {
public:
    vector<int> separateDigits(vector<int>& nums)
    {
        const int N = nums.size();
        vector<int> answer;
        answer.reserve(N * 6);

        for (int num : nums)
        {
            vector<int> stack;
            while (num > 0)
            {
                stack.push_back(num % 10);
                num /= 10;
            }

            while ( ! stack.empty())
            {
                answer.push_back(stack.back());
                stack.pop_back();
            }
        }

        return answer;
    }
};




/*
    ------------
    --- IDEA ---
    ------------

    TODO

*/

/* Time  Beats: 100.00% */
/* Space Beats:  99.67% */

/* Time  Complexity: O(D) */ // Where 'D' is a total amount of digits
/* Space Complexity: O(1) */ // No EXTRA Space
class Solution_2 {
private:
    int powers_of_ten[6] = {1, 10, 100, 1000, 10000, 100000};

public:
    vector<int> separateDigits(vector<int>& nums)
    {
        const int N = nums.size();

        vector<int> answer;
        answer.reserve(N*6); // To prevent reallocations

        for (int num : nums)
        {
            auto iter = upper_bound(begin(powers_of_ten), end(powers_of_ten), num);
            iter--; // Step back once

            int idx = iter - begin(powers_of_ten);

            for (int i = idx; i >= 0; i--)
            {
                auto [quotient, remainder] = div(num, powers_of_ten[i]);
                answer.push_back(quotient);

                num = remainder;
            }
        }

        return answer;
    }
};
