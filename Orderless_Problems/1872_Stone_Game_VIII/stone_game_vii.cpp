/*
    ============
    === HARD ===
    ============

    ===========================
    1872) Stone Game VII
    ===========================

    ============
    Description:
    ============

    Alice and Bob take turns playing a game, with Alice starting first.

    There are n stones arranged in a row. On each player's turn, while the
    number of stones is more than one, they will do the following:

        + Choose an integer x > 1, and remove the leftmost x stones from the
          row.

        + Add the sum of the removed stones' values to the player's score.

        + Place a new stone, whose value is equal to that sum, on the left side
          of the row.

    The game stops when only one stone is left in the row.

    The score difference between Alice and Bob is (Alice's score - Bob's
    score). Alice's goal is to maximize the score difference, and Bob's goal is
    the minimize the score difference.

    Given an integer array stones of length n where stones[i] represents the
    value of the ith stone from the left, return the score difference between
    Alice and Bob if they both play optimally.

    =================================================
    FUNCTION: int stoneGameVIII(vector<int>& stones);
    =================================================

    ==========================================================================
    ================================ EXAMPLES ================================
    ==========================================================================

    --- Example 1 ---
    Input: stones = [-1,2,-3,4,-5]
    Output: 5
    Explanation:
    + Alice removes the first 4 stones, adds (-1) + 2 + (-3) + 4 = 2 to her
      score, and places a stone of value 2 on the left. stones = [2,-5].

    + Bob removes the first 2 stones, adds 2 + (-5) = -3 to his score, and
      places a stone of value -3 on the left. stones = [-3].

    The difference between their scores is 2 - (-3) = 5.


    --- Example 2 ---
    Input: stones = [7,-6,5,10,5,-2,-6]
    Output: 13
    Explanation:
    + Alice removes all stones, adds 7 + (-6) + 5 + 10 + 5 + (-2) + (-6) = 13
      to her score, and places a stone of value 13 on the left. stones = [13].

    The difference between their scores is 13 - 0 = 13.


    --- Example 3 ---
    Input: stones = [-10,-12]
    Output: -22
    Explanation:
    + Alice can only make one move, which is to remove both stones. She adds
      (-10) + (-12) = -22 to her score and places a stone of value -22 on the
      left. stones = [-22].

    The difference between their scores is (-22) - 0 = -22.


    *** Constraints ***
    n == stones.length
    2 <= n <= 10^5
    -10^4 <= stones[i] <= 10^4

*/

#include <cstring>
#include <numeric>
#include <vector>
using namespace std;

/*
    ------------
    --- IDEA ---
    ------------

    TODO

*/

/* Time  Beats: 29.82% */
/* Space Beats: 23.19% */

/* Time  Complexity: O(N) */
/* Space Complexity: O(N) */
class Solution_Top_Down__Memoization {
private:
    static constexpr int MAX_N = 1e5;
    int memo[MAX_N];

public:
    int stoneGameVIII(vector<int>& stones)
    {
        const int N = stones.size();

        /* Memset */
        memset(memo, 0xff, sizeof(memo));

        vector<int> prefix_sum(N);
        prefix_sum[0] = stones[0];

        for (int i = 1; i < N; i++)
            prefix_sum[i] = prefix_sum[i - 1] + stones[i];

        return max_diff(1, prefix_sum);
    }

private:
    int max_diff(int idx, vector<int>& prefix_sum)
    {
        const int N = prefix_sum.size();

        if (idx == N-1)
            return prefix_sum[N-1];

        if (memo[idx] != -1)
            return memo[idx];

        int next_diff = max_diff(idx + 1, prefix_sum);

        return memo[idx] = max(prefix_sum[idx] - next_diff, next_diff);
    }
};




/*
    ------------
    --- IDEA ---
    ------------

    TODO

*/

/* Time  Beats: 89.73% */
/* Space Beats: 63.79% */

/* Time  Complexity: O(N) */
/* Space Complexity: O(N) */
class Solution_Bottom_up__Tabulation {
public:
    int stoneGameVIII(vector<int>& stones)
    {
        const int N = stones.size();

        /* Prefix Sum */
        vector<int> prefix_sum(N);
        prefix_sum[0] = stones[0];

        for (int i = 1; i < N; i++)
            prefix_sum[i] = prefix_sum[i-1] + stones[i];

        /* Compute Result */
        int result = prefix_sum[N-1];
        for (int i = N-2; i > 0; i--)
            result = max(result, prefix_sum[i] - result);

        return result;
    }
};




/*
    ------------
    --- IDEA ---
    ------------

    Same as above, however here we're using "partial_sum" function from STD &
    we're using utility "back_inserted".

    It is really handy to know these, so I wanted to include it separately.

*/

/* Time  Beats: 61.69% */
/* Space Beats: 23.91% */

/* Time  Complexity: O(N) */
/* Space Complexity: O(N) */
class Solution_Bottom_up__Tabulation__using_Partial_Sum_and_Back_Inserter {
public:
    int stoneGameVIII(vector<int>& stones)
    {
        const int N = stones.size();

        /* Prefix Sum */
        vector<int> prefix_sum;
        prefix_sum.reserve(N); // To prevent repeated reallocations
        std::partial_sum(stones.begin(), stones.end(), std::back_inserter(prefix_sum));

        /* Compute Result */
        int result = prefix_sum[N-1];
        for (int i = N-2; i > 0; i--)
            result = max(result, prefix_sum[i] - result);

        return result;
    }
};




/*
    ------------
    --- IDEA ---
    ------------

    TODO

*/

/* Time  Beats: 45.51% */
/* Space Beats: 63.79% */

/* Time  Complexity: O(N) */
/* Space Complexity: O(N) */
class Solution_Bottom_up__Tabulation__using_Partial_Sum_without_Back_Inserter {
public:
    int stoneGameVIII(vector<int>& stones)
    {
        const int N = stones.size();

        /* Prefix Sum */
        vector<int> prefix_sum(N);
        std::partial_sum(stones.begin(), stones.end(), prefix_sum.begin());

        /* Compute Result */
        int result = prefix_sum[N-1];
        for (int i = N-2; i > 0; i--)
            result = max(result, prefix_sum[i] - result);

        return result;
    }
};
