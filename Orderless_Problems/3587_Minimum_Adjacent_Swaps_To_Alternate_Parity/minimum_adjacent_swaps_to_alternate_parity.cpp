/*
    ==============
    === MEDIUM ===
    ==============

    ================================================
    3587) Minimum Adjacent Swaps to Alternate Parity
    ================================================

    ============
    Description:
    ============

    You are given an array nums of distinct integers.

    In one operation, you can swap any two adjacent elements in the array.

    An arrangement of the array is considered valid if the parity of adjacent
    elements alternates, meaning every pair of neighboring elements consists of
    one even and one odd number.

    Return the minimum number of adjacent swaps required to transform nums into
    any valid arrangement.

    If it is impossible to rearrange nums such that no two adjacent elements
    have the same parity, return -1.

    ==========================================
    FUNCTION: int minSwaps(vector<int>& nums);
    ==========================================

    ==========================================================================
    ================================ EXAMPLES ================================
    ==========================================================================

    --- Example 1 ---
    Input: nums = [2,4,6,5,7]
    Output: 3
    Explanation:
    Swapping 5 and 6, the array becomes [2,4,5,6,7]
    Swapping 5 and 4, the array becomes [2,5,4,6,7]
    Swapping 6 and 7, the array becomes [2,5,4,7,6]. The array is now a valid
    arrangement. Thus, the answer is 3.


    --- Example 2 ---
    Input: nums = [2,4,5,7]
    Output: 1
    Explanation:
    By swapping 4 and 5, the array becomes [2,5,4,7], which is a valid
    arrangement. Thus, the answer is 1.


    --- Example 3 ---
    Input: nums = [1,2,3]
    Output: 0
    Explanation:
    The array is already a valid arrangement. Thus, no operations are needed.

    --- Example 4 ---
    Input: nums = [4,5,6,8]
    Output: -1
    Explanation:
    No valid arrangement is possible. Thus, the answer is -1.


    *** Constraints ***
    1 <= nums.length <= 105
    1 <= nums[i] <= 109
    All elements in nums are distinct.

*/

#include <climits>
#include <cmath>
#include <cstdlib>
#include <vector>
using namespace std;

/*
    ------------
    --- IDEA ---
    ------------

    TODO

*/

/* Time  Beats: 96.40% */
/* Space Beats: 86.15% */

/* Time  Complexity: O(N) */
/* Space Complexity: O(1) */
class Solution {
public:
    int minSwaps(vector<int>& nums)
    {
        const int N = nums.size();
        long long result = 0;
        long long result2 = 0;


        long long odd  = 0;
        long long even = 0;
        for (const int& num : nums)
        {
            if (num & 1)
                odd++;
            else
                even++;
        }

        if (N & 1)
        {
            if (abs(odd - even) > 1)
                return -1;
        }
        else // Even size of N
        {
            if (odd != even)
                return -1;
        }

        bool t = true;
        for (int i = 1; i < N; i++)
        {
            if ((nums[i] % 2 == 0) && (nums[i-1] % 2 == 0) ||
                (nums[i] % 2 != 0) && (nums[i-1] % 2 != 0))
            {
                t = false;
                break;
            }
        }

        if (t)
            return 0;


        long long total = LLONG_MAX;

        if (N & 1)
        {
            if (odd > even)
            {
                long long next_odd  = 0;
                long long next_even = 1;

                for (int i = 0; i < N; i++)
                {
                    if (nums[i] & 1)
                    {
                        result += abs(i - next_odd);
                        next_odd += 2;
                    }
                    else
                    {
                        result += abs(i - next_even);
                        next_even += 2;
                    }
                }

            }
            else
            {
                long long next_odd  = 1;
                long long next_even = 0;

                for (int i = 0; i < N; i++)
                {
                    if (nums[i] & 1)
                    {
                        result += abs(i - next_odd);
                        next_odd += 2;
                    }
                    else
                    {
                        result += abs(i - next_even);
                        next_even += 2;
                    }
                }
            }
            total = min(total, static_cast<long long>(ceil(1.0 * result / 2)));
        }
        else
        {
            long long next_odd  = 0;
            long long next_even = 1;

            for (int i = 0; i < N; i++)
            {
                if (nums[i] & 1)
                {
                    result += abs(i - next_odd);
                    next_odd += 2;
                }
                else
                {
                    result += abs(i - next_even);
                    next_even += 2;
                }
            }

            total = min(total, static_cast<long long>(ceil(1.0 * result / 2)));

            next_odd  = 1;
            next_even = 0;
            result = 0;
            for (int i = 0; i < N; i++)
            {
                if (nums[i] & 1)
                {
                    result += abs(i - next_odd);
                    next_odd += 2;
                }
                else
                {
                    result += abs(i - next_even);
                    next_even += 2;
                }
            }

            total = min(total, static_cast<long long>(ceil(1.0 * result / 2)));
        }

        return static_cast<int>(total);
    }
};




/*
    ------------
    --- IDEA ---
    ------------

    This one uses Extra space, but it's a MUCH more clear and concise way of
    solving this problem.

*/

/* Time  Beats: 100.00% */
/* Space Beats: 32.07% */

/* Time  Complexity: O(N) */
/* Space Complexity: O(N) */
class Solution_2 {
public:
    int minSwaps(vector<int>& nums)
    {
        const int N = nums.size();

        vector<int> idx_of_odd_num;
        vector<int> idx_of_even_num;

        for (int i = 0; i < N; i++)
        {
            if (nums[i] % 2)
                idx_of_odd_num.push_back(i);
            else
                idx_of_even_num.push_back(i);
        }

        int odd_size  = idx_of_odd_num.size();
        int even_size = idx_of_even_num.size();

        if (abs(odd_size - even_size) > 1)
            return -1;

        int result = 0;
        if (N % 2 == 0) // Even
        {
            int swaps_when_odd_start = 0;
            for (int i = 0; i < odd_size; i++)
                swaps_when_odd_start += abs(idx_of_odd_num[i] - i*2);

            int swaps_when_even_start = 0;
            for (int i = 0; i < even_size; i++)
                swaps_when_even_start += abs(idx_of_even_num[i] - i*2);

            result = min(swaps_when_odd_start, swaps_when_even_start);
        }
        else // Odd
        {
            int swaps = 0;
            if (odd_size > even_size)
            {
                for (int i = 0; i < odd_size; i++)
                    swaps += abs(idx_of_odd_num[i] - i*2);
            }
            else
            {
                for (int i = 0; i < even_size; i++)
                    swaps += abs(idx_of_even_num[i] - i*2);
            }

            result = swaps;
        }

        return result;
    }
};
