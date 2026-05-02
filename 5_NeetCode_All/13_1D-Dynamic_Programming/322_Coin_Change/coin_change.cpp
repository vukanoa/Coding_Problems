/*
    ==============
    === MEDIUM ===
    ==============

    ===========================
    322) Coin Change
    ===========================

    ============
    Description:
    ============

    You are given an integer array "coins" representing coins of different
    denominations and an integer "amount" representing a total amount of money.

    Return the fewest number of coins that you need to make up that amount. If
    that amount of money cannot be made up by any combination of the coins,
    return -1.

    You may assume that you have an infinite number of each kind of coin.

    =========================================================
    FUNCTION: int coinChange(vector<int>& coins, int amount);
    =========================================================

    ==========================================================================
    ================================ EXAMPLES ================================
    ==========================================================================

    --- Example 1 ---
    Input:  coins = [1, 2, 5], amount = 11
    Output: 3
    Explanation: 11 = 5 + 5 + 1

    --- Example 2 ---
    Input:  coins = [2], amount = 3
    Output: -1

    --- Example 3 ---
    Input:  coins = [1], amount = 0
    Output: 0

    *** Constraints ***
    1 <= coins.length <= 12
    1 <= coins[i] <= 2^31 - 1
    0 <= amount <= 10^4

*/

#include <vector>
#include <algorithm>
using namespace std;

/*
    ------------
    --- IDEA ---
    ------------

    Inuitively, at a first glance at this problem you'd probably think:
    "Is it this easy? Is it just a greedy?"

    But upon a further examination, you'll quickly find an example that
    dispproves such hypothesis.

    Consider this:

        Array: [1, 3, 4, 5]
        Amount: 7

    If you were to use a greedy algorithm, you'd quickly find that you'd need
    3 coins(5 + 1 + 1), which we know it's NOT optimal.

    So you cannot use a strategy called:

        "Pick the largest one and use it until adding one more would exceed the
         targeted amount. At that point, try a smaller denomination coin and do
         that until you have a sum of exactly 'amount'."


    The next thing that comes up to mind is: "Can this be a DFS-Backtracking?"

    Well, yes it can be. It will work, but probably will give you a TLE(Time
    Limit Exceeded) on LeetCode.

    However, if you were to draw yourself a whole tree in DFS-Backtracking
    process you would've seen that there are certain things that are
    UNNECESSARILY computed more than once.

    So a natural question arises - Can I MEMOIZE this?
    As soon as you ask this question, the answer almost always is - Yes.

    However, for this specific problem, a much more natural way of solving it
    is by using a "Bottom-Up DP" instead of "Top-Down Memoization".

    For "Dynamic Programming" problems, you can ALWAYS solve them in both ways,
    i.e. either using "Top-Down Memoization" or using "Bottom-Up Tabulation"
    technique.

    However, one is usually SUPERIOR to the other depending on the problem.

    For example, Bottom-up can be awkward or inefficient when the state
    transitions are irregular (like tree DP, graph DP with arbitrary
    dependencies, or when only reachable states are sparse), and Memoization
    can be MUCH MUCH simpler there.

    However, if you aim for an O(1) Space COmplexity or highly optimized space
    solution, "Bottom-Up" is usually the more natural and practical choice.

    So ANYTIME you need a O(1) Space DP Solution, "Bottom-Up" is the way.
    Memoization ALWAYS uses at least O(N) Space, because of the Recursion.


    So how do we solve it?

    We have to solve the subproblems of our given problem, one by one, and then
    at the very end - Solve our given problem.

    So how do we do this?
    Let's consider the previous example that crushed our "Is it greedy?"
    question.

        Array: [1, 3, 4, 5]
        Amount: 7

    We have to solve subproblems, but what ARE those subproblems?

    Since our goal is to reach 7, let's try to find an answer to:
        1, 2, 3, 4, 5
    before we try to go for our given amount 6.

    First, let's make an array dp.
    What length should it be?

    Well, since dp[0] is always 0 since we need 0 coins to get to amount of 0,
    we must have this base case solved which will make our dp of size: amount+1

    What are the values we should initialize this array with?
    It's important that we assign 0 to dp[0] and all the other states should be
    either UNATTAINABLE(i,e amount + 1, since any combination we try will be
    less than that) or INT_MAX.

    Let's go with INT_MAX. So initially our DP looks like this:

        dp = [0, INT_MAX, INT_MAX, INT_MAX, INT_MAX, INT_MAX, INT_MAX, INT_MAX]
              0     1        2        3        4        5        6        7

    Let's try to solve this problem as if the amount given is 1.

    Note that the coins DON'T have to be in sorted order, thus we MUST always
    sort it initially.
    (We can sort them because that will NOT worsen our overall Time Complexity)

    So, we're doing this:

        Array: [1, 3, 4]
        Amount: 1

    The idea is to find the minimum number of coins needed to solve all these
    subproblems and then each time we search for amount X, subtract value of
    the current coin from the current amount and then try to see what is the
    minimum number of coins for that newly calulated amount.

    Example:

        Array: [1, 3, 4]
        Amount: 6

        dp = [0, 1, 2, 1, 1, 2]  // Minimal coins in order to sum up to dp[i]
              0  1  2  3  4  5   // amounts

    So how do we find what is the minimum number of coins needed that sums up
    to 6?

    Let's iterate through all the coins:

        1) We take coin with value 1(coin at index 0)
           Amount(which is 6) minus value of current coin:

               6 - 1 = 5

           Now we try and see what is the value of dp[5] since that is the
           minimum number of coins needed to sum up to 5 and then we add 1
           more(this current coin we're trying it with)

           Previously dp[6] was INT_MAX, now it's 3.
           Let's continue


        2) We take coin with value 3(coin at index 1)

               6 - 3 = 3
               dp[3] = 1

               dp[6] = min(dp[6], 1 + dp[3])
               dp[6] = min(  3  , 1 + 1    )

            Now our dp[6] is 2.

        3) We take coin with value 4(coin at index 2)

               6 - 4 = 2
               dp[2] = 2

              dp[6] = min(dp[6], 1 + dp[2]);
              dp[6] = min(  2  , 1 +   2  );

            Since dp[6] was 2 because of the previous step, we're doing this:

              dp[6] = min(2, 1 + 2);
              dp[6] = min(2,   3  );

            Thus we WON'T update the dp[6] to 3, since 2 is smaller.

    And at the end we ask if dp[6] is INT_MAX.
    if it is INDEED INT_MAX, then we return -1 since that means we did not
    found a way to sum up to the amount value.

    Otherwise, we return the value we got.
*/

/* Time  Beats: 85.26% */
/* Space Beats: 80.50% */

/* Time  Complexity: O(N * amount) */
/* Space Complexity: O(amount)     */
class Solution_Bottom_Up {
public:
    int coinChange(vector<int>& coins, int amount)
    {
        const int N            = coins.size();
        const int UNATTAINABLE = amount + 1;

        if (amount == 0)
            return 0;

        /* Sort */
        sort(coins.begin(), coins.end());

        vector<int> dp(amount + 1, UNATTAINABLE);
        dp[0] = 0;

        for (int a = 1; a <= amount; a++) // a <==> curr_amount
        {
            for (const int& coin : coins) // coin <==> curr_coin
            {
                if (a - coin < 0)
                    break;

                dp[a] = min(dp[a], 1 + dp[a - coin]);
            }
        }

        return dp[amount] == UNATTAINABLE ? -1 : dp[amount];
    }
};
