/*
    ==============
    === MEDIUM ===
    ==============

    =============================================
    462) Minimum_Moves_To_Equal_Array_Elements_II
    =============================================

    ============
    Description:
    ============

    Given an integer array nums of size n, return the minimum number of moves
    required to make all array elements equal.

    In one move, you can increment or decrement an element of the array by 1.

    Test cases are designed so that the answer will fit in a 32-bit integer.

    ===========================================
    FUNCTION: int minMoves2(vector<int>& nums);
    ===========================================

    ==========================================================================
    ================================ EXAMPLES ================================
    ==========================================================================

    --- Example 1 ---
    Input: nums = [1,2,3]
    Output: 2
    Explanation:
    Only two moves are needed (remember each move increments or decrements one
    element):
    [1,2,3]  =>  [2,2,3]  =>  [2,2,2]

    --- Example 2 ---
    Input: nums = [1,10,2,9]
    Output: 16


    *** Constraints ***
    n == nums.length
    1 <= nums.length <= 10^5
    -10^9 <= nums[i] <= 10^9

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

/* Time  Beats: 33.45% */
/* Space Beats: 51.89% */

/* Time  Complexity: O(N * logN) */
/* Space Complexity: O(logN)     */ // Because of C++"s Intro Sort
class Solution {
public:
    int minMoves2(vector<int>& nums)
    {
        const int N = nums.size();
        int result = 0;

        /* Sort */
        sort(nums.begin(), nums.end());

        int median = nums[N/2];

        for (int i = 0; i < N; i++)
            result += abs(nums[i] - median); // Adding absolute difference

        return result;
    }
};




/*
    ------------
    --- IDEA ---
    ------------

    TODO

*/

/* Time  Beats: 100.00% */
/* Space Beats:  51.89% */

/* Time  Complexity: O(N * logN) */
/* Space Complexity: O(logN)     */ // Because of C++"s Intro Sort
class Solution_2 {
public:
    int minMoves2(vector<int>& nums)
    {
        const int N = nums.size();
        int result = 0;

        /* Sort */
        sort(nums.begin(), nums.end());

        int median = nums[N/2];

        for (int i = 0; i < N/2; i++)
            result += nums[N-1 - i] - nums[i]; // Adding difference

        return result;
    }
};




/*
    ------------
    --- IDEA ---
    ------------

    It's important to know this function if you're using C++. But even if you
    are not, this is a handy "trick" and technique.

*/

/* Time  Beats: 100.00% */
/* Space Beats:  13.54% */

/* Time  Complexity: O(N) average */
/* Space Complexity: O(1)         */
class Solution_Average_Linear {
public:
    int minMoves2(vector<int>& nums)
    {
        const int N = nums.size();
        int result = 0;

        // Fixing ths median element
        nth_element(nums.begin(), nums.begin() + (N/2), nums.end());

        int median = nums[N/2];

        for (int i = 0; i < N; i++)
            result += abs(nums[i] - median); // Adding absolute difference

        return result;
    }
};
