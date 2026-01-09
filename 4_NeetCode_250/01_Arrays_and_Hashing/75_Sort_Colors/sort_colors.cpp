/*
    ==============
    === MEDIUM ===
    ==============

    ===========================
    75) Sort Colors
    ===========================

    ============
    Description:
    ============

    Given an array "nums" with 'n' objects colored red, white or blue, sort
    them in-place so that objects of the same color are adjacent, with the
    colors in the order red, white and blue.

    We will use the integers 0, 1 and 2 to represent the color red, white and
    blue, respectively.

    You must solve this problem without using the library's sort function.

    =============================================
    FUNCTION: void sortColors(vector<int>& nums);
    =============================================

    ==========================================================================
    ================================ EXAMPLES ================================
    ==========================================================================

    --- Example 1 ---
    Input:  nums = [2, 0, 2, 1, 1, 0]
    Output: nums = [0, 0, 1, 1, 2, 2]

    --- Example 2 ---
    Input:  nums = [2, 0, 1]
    Output: [0, 1, 2]

    --- Example 3 ---
    Input:  nums = [2, 0, 1, 2, 0, 2, 2, 1, 2, 1, 1, 2, 0]
    Output: [0, 0, 0, 1, 1, 1, 1, 2, 2, 2, 2, 2, 2]

    *** Constraints ***
    n == nums.length
    1 <= n <= 300
    nums[i] is either 0, 1 or 2.

*/

#include <vector>
using namespace std;

/*
    ------------
    --- IDEA ---
    ------------

    Basic Counting-Sort. Trivial when there are only 3 different values.

*/

/* Time  Beats: 100.00% */
/* Space Beats:  77.19% */

/* Time  Complexity: O(N) */ // Two Passes
/* Space Complexity: O(1) */
class Solution {
public:
    void sortColors(vector<int>& nums)
    {
        const int N = nums.size();

        /* Counting Sort */
        int count[3] = {0};
        for (int i = 0; i < N; i++)
            count[nums[i]]++;

        int index = 0;
        for (int color = 0; color < 3; color++)
        {
            while (count[color] > 0)
            {
                nums[index] = color;
                index++;

                // Decrement
                count[color]--;
            }
        }
    }
};




/*
    ------------
    --- IDEA ---
    ------------

    TODO

*/

/* Time  Beats: 100.00% */
/* Space Beats:  77.19% */

/* Time  Complexity: O(N) */
/* Space Complexity: O(1) */
class Solution_One_Pass {
public:
    void sortColors(vector<int>& nums)
    {
        const int N = nums.size();

        int L = 0;
        int R = N-1;

        int i = 0;
        while (i <= R)
        {
            if (nums[i] == 0)
            {
                swap(nums[L++], nums[i]);
            }
            else if (nums[i] == 2)
            {
                swap(nums[i], nums[R--]);
                i--; // To cancel out the increment of 'i'
            }

            // Increment
            i++;
        }
    }
};
