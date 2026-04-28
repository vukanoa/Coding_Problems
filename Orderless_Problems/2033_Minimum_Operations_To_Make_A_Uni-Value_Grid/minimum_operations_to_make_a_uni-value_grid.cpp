/*
    ==============
    === MEDIUM ===
    ==============

    =================================================
    2033) Minimum Operations to Make a Uni-Value Grid
    =================================================

    ============
    Description:
    ============

    You are given a 2D integer grid of size m x n and an integer x. In one
    operation, you can add x to or subtract x from any element in the grid.

    A uni-value grid is a grid where all the elements of it are equal.

    Return the minimum number of operations to make the grid uni-value. If it
    is not possible, return -1.

    ==============================================================
    FUNCTION: int minOperations(vector<vector<int>>& grid, int x);
    ==============================================================

    ==========================================================================
    ================================ EXAMPLES ================================
    ==========================================================================

    --- Example 1 ---
    Input: grid = [[2,4],[6,8]], x = 2
    Output: 4
    Explanation: We can make every element equal to 4 by doing the following:
    - Add x to 2 once.
    - Subtract x from 6 once.
    - Subtract x from 8 twice.
    A total of 4 operations were used.

    --- Example 2 ---
    Input: grid = [[1,5],[2,3]], x = 1
    Output: 5
    Explanation: We can make every element equal to 3.

    --- Example 3 ---
    Input: grid = [[1,2],[3,4]], x = 2
    Output: -1
    Explanation: It is impossible to make every element equal.


    *** Constraints ***
    m == grid.length
    n == grid[i].length
    1 <= m, n <= 10^5
    1 <= m * n <= 10^5
    1 <= x, grid[i][j] <= 10^4

*/

#include <algorithm>
#include <climits>
#include <vector>
using namespace std;

/*
    ------------
    --- IDEA ---
    ------------

    Intuitive. Just sort it and find median. There's not much more to it.

*/

/* Time  Beats: 62.14% */
/* Space Beats: 79.84% */

/* Time  Complexity: O(N * logN) */ // Where N <==> ROWS * COLS
/* Time  Complexity: O(N)        */
class Solution {
public:
    int minOperations(vector<vector<int>>& grid, int x)
    {
        const int ROWS = grid.size();
        const int COLS = grid[0].size();

        const int N = ROWS * COLS;
        int result = 0;

        vector<int> nums;
        nums.reserve(N); // To prevent reallocations

        for (int row = 0; row < ROWS; row++)
        {
            for (int col = 0; col < COLS; col++)
            {
                nums.push_back(grid[row][col]);
            }
        }

        /* Sort */
        sort(nums.begin(), nums.end());

        int L = 0;
        int R = N - 1;

        int mid = L + (R - L + 1) / 2; // upper-mid

        int target = nums[mid];

        for (int i = 0; i < N; i++)
        {
            int diff = abs(target - nums[i]);

            if (diff % x != 0)
                return -1;

            result += diff / x;
        }

        return result;
    }
};




/*
    ------------
    --- IDEA ---
    ------------

    Instead of findiming Median, we can use "Dynamic Programming" to obtain:
        1. The least amount of steps needed for all the number to the RIGHT of
           the current number to be subtracted to the current number.

           and

        2. the least amount of steps needed for all the numbers to the LEFT of
           the current number to be added up to the current number.

    The simply go from [0, N-1] and see which sum(dp_prefix + dp_suffix) is the
    smallest.

*/

/* Time  Complexity: O(N * logN) */ // Where N <==> ROWS * COLS
/* Space Complexity: O(N)        */
class Solution_1D_DP__Prefix_Suffix {
public:
    int minOperations(vector<vector<int>>& grid, int x)
    {
        const int ROWS = grid.size();
        const int COLS = grid[0].size();

        const int N = ROWS * COLS;
        int result = INT_MAX;

        vector<int> nums;
        nums.reserve(N); // To prevent reallocations

        for (int row = 0; row < ROWS; row++)
        {
            for (int col = 0; col < COLS; col++)
            {
                nums.push_back(grid[row][col]);
            }
        }

        /* Sort */
        sort(nums.begin(), nums.end());
        
        /* Check if it's impossible */
        for (int i = 1; i < N; i++)
        {
            if ((nums[i] - nums[i-1]) % x != 0)
                return -1;
        }

        vector<int> dp_suffix(N, 0);
        vector<int> dp_prefix(N, 0);

        for (int i = N-2; i >= 0; i--)
        {
            if (nums[i] == nums[i+1])
            {
                dp_suffix[i] = dp_suffix[i+1];
                continue;
            }

            int diff = (nums[i+1] - nums[i]);

            dp_suffix[i] = diff/x * (N - (i+1)) + dp_suffix[i+1];
        }

        for (int i = 1; i < N; i++)
        {
            if (nums[i-1] == nums[i])
            {
                dp_prefix[i] = dp_prefix[i-1];
                continue;
            }

            int diff = ( nums[i] - nums[i-1]);

            dp_prefix[i] = diff/x * i + dp_prefix[i-1];
        }

        for (int i = 0; i < N; i++)
            result = min(result, dp_prefix[i] + dp_suffix[i]);

        return result;
    }
};
