/*
    ==============
    === MEDIUM ===
    ==============

    =============================
    1726) Tuple With Same Product
    =============================

    ============
    Description:
    ============

    Given an array nums of distinct positive integers, return the number of
    tuples (a, b, c, d) such that a * b = c * d where a, b, c, and d are
    elements of nums, and a != b != c != d.

    ==================================================
    FUNCTION: int tupleSameProduct(vector<int>& nums);
    ==================================================

    ==========================================================================
    ================================ EXAMPLES ================================
    ==========================================================================

    --- Example 1 ---
    Input: nums = [2,3,4,6]
    Output: 8
    Explanation: There are 8 valid tuples:
    (2,6,3,4) , (2,6,4,3) , (6,2,3,4) , (6,2,4,3)
    (3,4,2,6) , (4,3,2,6) , (3,4,6,2) , (4,3,6,2)

    --- Example 2 ---
    Input: nums = [1,2,4,5,10]
    Output: 16
    Explanation: There are 16 valid tuples:
    (1,10,2,5) , (1,10,5,2) , (10,1,2,5) , (10,1,5,2)
    (2,5,1,10) , (2,5,10,1) , (5,2,1,10) , (5,2,10,1)
    (2,10,4,5) , (2,10,5,4) , (10,2,4,5) , (10,2,5,4)
    (4,5,2,10) , (4,5,10,2) , (5,4,2,10) , (5,4,10,2)


    *** Constraints ***
    1 <= nums.length <= 1000
    1 <= nums[i] <= 10^4
    All elements in nums are distinct.

*/

#include <unordered_map>
#include <vector>
using namespace std;

/*
    ------------
    --- IDEA ---
    ------------

    TODO

*/

/* Time  Beats: 9.40% */
/* Space Beats: 6.27% */

/* Time  Complexity: O(N^2) */
/* Space Complexity: O(N)   */
class Solution {
public:
    int tupleSameProduct(vector<int>& nums)
    {
        const int N = nums.size();
        int result = 0;

        unordered_map<int,int> product_counter;
        unordered_map<int,int> pair_counter;

        for (int i = 0; i < N; i++)
        {
            for (int j = i+1; j < N; j++)
            {
                int product = nums[i] * nums[j];

                pair_counter[product] += product_counter[product];
                product_counter[product]++;
            }
        }

        for (const auto& [pair, cnt] : pair_counter)
            result += 8 * cnt;

        return result;
    }
};




/*
    ------------
    --- IDEA ---
    ------------

    This one uses Gaus' formula of calculating the sum of first N natural
    numbers.

*/

/* Time  Beats: 82.44% */
/* Space Beats: 45.45% */

/* Time  Complexity: O(N^2) */
/* Space Complexity: O(N)   */
class Solution_Gaus {
public:
    int tupleSameProduct(vector<int>& nums)
    {
        const int N = nums.size();
        int result = 0;

        unordered_map<int,int> product_counter;

        for (int i = 0; i < N; i++)
        {
            for (int j = i+1; j < N; j++)
            {
                int product = nums[i] * nums[j];
                product_counter[product]++;
            }
        }

        for (const auto& [product, cnt] : product_counter)
        {
            int pairs = cnt * (cnt - 1) / 2;
            result += 8 * pairs;
        }

        return result;
    }
};
