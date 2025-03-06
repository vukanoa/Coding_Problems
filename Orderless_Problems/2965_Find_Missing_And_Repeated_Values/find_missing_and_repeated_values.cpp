/*
    ============
    === EASY ===
    ============

    ======================================
    2965) Find Missing and Repeated Values
    ======================================

    ============
    Description:
    ============

    You are given a 0-indexed 2D integer matrix grid of size n * n with values
    in the range [1, n2]. Each integer appears exactly once except a which
    appears twice and b which is missing. The task is to find the repeating and
    missing numbers a and b.

    Return a 0-indexed integer array ans of size 2 where ans[0] equals to a and
    ans[1] equals to b.

    ==============================================================================
    FUNCTION: vector<int> findMissingAndRepeatedValues(vector<vector<int>>& grid);
    ==============================================================================

    ==========================================================================
    ================================ EXAMPLES ================================
    ==========================================================================

    --- Example 1 ---
    Input: grid = [[1,3],[2,2]]
    Output: [2,4]
    Explanation: Number 2 is repeated and number 4 is missing so the answer is [2,4].

    --- Example 2 ---
    Input: grid = [[9,1,7],[8,9,2],[3,4,6]]
    Output: [9,5]
    Explanation: Number 9 is repeated and number 5 is missing so the answer is [9,5].


    *** Constraints ***
    2 <= n == grid.length == grid[i].length <= 50
    1 <= grid[i][j] <= n * n
    For all x that 1 <= x <= n * n there is exactly one x that is not equal to any of the grid members.
    For all x that 1 <= x <= n * n there is exactly one x that is equal to exactly two of the grid members.
    For all x that 1 <= x <= n * n except two of them there is exatly one pair of i, j that 0 <= i, j <= n - 1 and grid[i][j] == x.

*/

#include <vector>
using namespace std;

/*
    ------------
    --- IDEA ---
    ------------

    Self-explanatory. Most obvious and intuitive Solution ever.

*/

/* Time  Beats: 74.78% */
/* Space Beats:  5.79% */

/* Time  Complexity: O(N^2) */
/* Space Complexity: O(N^2) */
class Solution {
public:
    vector<int> findMissingAndRepeatedValues(vector<vector<int>>& grid)
    {
        const int N = grid.size();
        vector<int> result = {-1, -1};

        vector<int> uset(2601, 0);
        for (int row = 0; row < N; row++)
        {
            for (int col = 0; col < N; col++)
                uset[grid[row][col]]++;
        }

        for (int i = 1; i <= N*N; i++) // starts at 1
        {
            if (uset[i] == 2)
                result[0] = i;
            else if (uset[i] == 0)
                result[1] = i;
        }

        return result;
    }
};




/*
    ------------
    --- IDEA ---
    ------------


    At first glance, this problem might seem to require tracking frequencies,
    but there's a more elegant mathematical approach. In a perfect sequence
    from 1 to n2, every number appears exactly once. However, in our given
    sequence, one number appears twice, and another number is missing.

    Let’s define the repeated number as x and the missing number as y.

    Instead of explicitly counting occurrences, we can leverage basic
    mathematical properties of numbers. The sum of all numbers in a proper
    sequence from 1 to n2 can be computed using the formula:

        perfectSum   = n^2 * (n^2 + 1) / 2;

    Similarly, the sum of the squares of these numbers follows this formula:

        perfect_sqrt_sum = n^2 * (n^2 + 1) * (2 * n^2 + 1) / 6

    Now, if we compute the sum of numbers in our given grid (sum) and compare
    it with perfectSum, we can express their relationship as:

        sum  = perfect_sum + x - y

    This tells us that the difference between the actual sum and the perfect
    sum gives us:

        sum_diff = x - y

    Similarly, if we compute the sum of squares from our grid (sqrSum) and
    compare it with perfectSqrSum, we get:

        sqr_diff = x^2 - y^2

    Now, we recall a fundamental algebraic identity:

        x^2 − y^2 = (x + y) * (x − y)

    Since we already know x−y from sumDiff, we can substitute it into the
    equation:

        sqr_diff = (x + y) * sum_diff

    Rearranging this equation, we can solve for x + y:

        x + y = sqr_diff / sum_diff

    Now, we have two simple equations:

        x - y = sum_diff
        x + y = sqr_diff / sum_diff

    Solving for x and y:

        x = (sqrt_diff / sum_diff + sum_diff) / 2
        y = (sqrt_diff / sum_diff - sum_diff) / 2

    This mathematical derivation translates directly into our code. We first
    calculate the actual sums from our grid and then compute the perfect sums
    using the formulas. The differences between these give us sumDiff and
    squareDifference, which we can plug into our final formulas to get the
    repeating and missing numbers.

    Note: One important implementation detail is the use of long instead of int
    for our calculations. This is crucial because when we're dealing with
    squares of numbers, we can easily exceed the integer range.

*/

/* Time  Beats: 100.00% */
/* Space Beats:  95.09% */

/* Time  Complexity: O(N^2) */
/* Space Complexity: O(1)   */
class Solution_Math {
public:
    vector<int> findMissingAndRepeatedValues(vector<vector<int>>& grid)
    {
        const long long N     = grid.size();
        const long long TOTAL = N * N;

        long long sum = 0;
        long long sqr_sum = 0;

        for (int row = 0; row < N; row++)
        {
            for (int col = 0; col < N; col++)
            {
                sum     += 1LL * grid[row][col];
                sqr_sum += 1LL * grid[row][col] * grid[row][col];
            }
        }

        // Calculate differences from expected sums
        // Expected sum:        n(n+1)/2,
        // Expected square sum: n(n+1)(2n+1)/6
        long long sum_diff = sum     - TOTAL * (TOTAL + 1) / 2;
        long long sqr_diff = sqr_sum - TOTAL * (TOTAL + 1) * (2 * TOTAL + 1) / 6;

        // Using math: If x is repeated and y is missing
        // sumDiff = x   - y
        // sqrDiff = x^2 - y^2
        int repeat  = (sqr_diff / sum_diff + sum_diff) / 2;
        int missing = (sqr_diff / sum_diff - sum_diff) / 2;

        return {repeat, missing};
    }
};
