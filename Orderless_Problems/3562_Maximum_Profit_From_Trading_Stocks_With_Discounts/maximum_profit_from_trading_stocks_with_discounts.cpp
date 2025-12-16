/*
    ============
    === HARD ===
    ============

    =======================================================
    3562) Maximum Profit from Trading Stocks with Discounts
    =======================================================

    ============
    Description:
    ============

    You are given an integer n, representing the number of employees in a
    company. Each employee is assigned a unique ID from 1 to n, and employee 1
    is the CEO. You are given two 1-based integer arrays, present and future,
    each of length n, where:

        + present[i] represents the current price at which the ith employee can
          buy a stock today.

        + future[i] represents the expected price at which the ith employee can
          sell the stock tomorrow.

    The company's hierarchy is represented by a 2D integer array hierarchy,
    where hierarchy[i] = [ui, vi] means that employee ui is the direct boss of
    employee vi.

    Additionally, you have an integer budget representing the total funds
    available for investment.

    However, the company has a discount policy: if an employee's direct boss
    purchases their own stock, then the employee can buy their stock at half
    the original price (floor(present[v] / 2)).

    Return the maximum profit that can be achieved without exceeding the given
    budget.

    ========
    NOTE:     You may buy each stock at most once. You cannot use any profit
              earned from future stock prices to fund additional investments
              and must buy only from budget.
    ========

    ======================================================================================================================
    FUNCTION: int maxProfit(int n, vector<int>& present, vector<int>& future, vector<vector<int>>& hierarchy, int budget);
    ======================================================================================================================

    ==========================================================================
    ================================ EXAMPLES ================================
    ==========================================================================

    --- Example 1 ---
    Input: n = 2, present = [1,2], future = [4,3], hierarchy = [[1,2]], budget = 3
    Output: 5
    Explanation:
    Employee 1 buys the stock at price 1 and earns a profit of 4 - 1 = 3.
    Since Employee 1 is the direct boss of Employee 2, Employee 2 gets a discounted price of floor(2 / 2) = 1.
    Employee 2 buys the stock at price 1 and earns a profit of 3 - 1 = 2.
    The total buying cost is 1 + 1 = 2 <= budget. Thus, the maximum total profit achieved is 3 + 2 = 5.

    --- Example 2 ---
    Input: n = 2, present = [3,4], future = [5,8], hierarchy = [[1,2]], budget = 4
    Output: 4
    Explanation:
    Employee 2 buys the stock at price 4 and earns a profit of 8 - 4 = 4.
    Since both employees cannot buy together, the maximum profit is 4.

    --- Example 3 ---
    Input: n = 3, present = [4,6,8], future = [7,9,11], hierarchy = [[1,2],[1,3]], budget = 10
    Output: 10
    Explanation:
    Employee 1 buys the stock at price 4 and earns a profit of 7 - 4 = 3.
    Employee 3 would get a discounted price of floor(8 / 2) = 4 and earns a profit of 11 - 4 = 7.
    Employee 1 and Employee 3 buy their stocks at a total cost of 4 + 4 = 8 <=
    budget. Thus, the maximum total profit achieved is 3 + 7 = 10.

    --- Example 4 ---
    Input: n = 3, present = [5,2,3], future = [8,5,6], hierarchy = [[1,2],[2,3]], budget = 7
    Output: 12
    Explanation:
    Employee 1 buys the stock at price 5 and earns a profit of 8 - 5 = 3.
    Employee 2 would get a discounted price of floor(2 / 2) = 1 and earns a profit of 5 - 1 = 4.
    Employee 3 would get a discounted price of floor(3 / 2) = 1 and earns a profit of 6 - 1 = 5.
    The total cost becomes 5 + 1 + 1 = 7 <= budget. Thus, the maximum total profit achieved is 3 + 4 + 5 = 12.

    *** Constraints ***
    1 <= n <= 160
    present.length, future.length == n
    1 <= present[i], future[i] <= 50
    hierarchy.length == n - 1
    hierarchy[i] == [ui, vi]
    1 <= ui, vi <= n
    ui != vi
    1 <= budget <= 160
    There are no duplicate edges.
    Employee 1 is the direct or indirect boss of every employee.
    The input graph hierarchy is guaranteed to have no cycles.

*/

#include <vector>
using namespace std;

/*
    ------------
    --- IDEA ---
    ------------

    TODO

*/

/* Time  Beats: 78.47% */
/* Space Beats: 48.61% */

/* Time  Complexity: O(N * budget^2) */
/* Space Complexity: O(N * budget)   */
class Solution {
public:
    int maxProfit(int n,
                  vector<int>& present,
                  vector<int>& future,
                  vector<vector<int>>& hierarchy,
                  int budget)
    {
        // Build an Adjacency List from hierarchy list (1-based to 0-based)
        vector<vector<int>> adj_list(n);
        for (const auto& edge : hierarchy)
            adj_list[edge[0] - 1].push_back(edge[1] - 1);

        // dp[node][parent_bought][budget]
        vector<vector<vector<int>>> dp(n, vector<vector<int>>(2, vector<int>(budget + 1, 0))
        );

        // Run DFS from root (node 0)
        dfs(0, present, future, adj_list, dp, budget);

        // Final answer: best profit at root when parent not bought
        int result = 0;
        for (int b = 0; b <= budget; b++)
            result = max(result, dp[0][0][b]);

        return result;
    }

private:
    // DFS to compute DP for subtree rooted at node u
    void dfs(int node,
             const vector<int>& present,
             const vector<int>& future,
             const vector<vector<int>>& tree,
             vector<vector<vector<int>>>& dp,
             int budget)
    {
        // Store DP results of all children:
        // first  -> child dp when parent NOT bought
        // second -> child dp when parent IS bought
        vector<pair<vector<int>, vector<int>>> child_DPs;

        // Process all children first (postorder DFS)
        for (int neighbor : tree[node])
        {
            dfs(neighbor, present, future, tree, dp, budget);
            child_DPs.emplace_back(dp[neighbor][0], dp[neighbor][1]);
        }

        // Compute dp[u][parentBought] for both cases
        for (int parent_bought = 0; parent_bought <= 1; parent_bought++)
        {
            // If parent was bought, current node gets 50% discount
            int price = parent_bought ? present[node] / 2 : present[node];

            // Profit gained if we buy this node
            int profit = future[node] - price;

            // dp array for node u with given parentBought state
            vector<int> curr(budget + 1, 0);

            // -------------------------
            // Case 1: SKIP
            // -------------------------
            vector<int> base(budget + 1, 0);

            // Merge children DP where parent is NOT bought
            for (const auto& child : child_DPs)
            {
                vector<int> next(budget + 1, 0);
                for (int b1 = 0; b1 <= budget; ++b1)
                {
                    // Skip unreachable states
                    if (base[b1] == 0 && b1 != 0)
                        continue;

                    for (int b2 = 0; b1 + b2 <= budget; b2++)
                    {
                        next[b1 + b2] = max(next[b1 + b2], base[b1] + child.first[b2]);
                    }
                }

                base = std::move(next);
            }

            // Update current dp values for "not buying node"
            for (int b = 0; b <= budget; b++)
                curr[b] = max(curr[b], base[b]);

            // ---------------------
            // Case 2: TAKE
            // ---------------------
            if (price <= budget)
            {
                vector<int> base_buy(budget + 1, 0);

                // Merge children DP where parent IS bought
                for (const auto& child : child_DPs)
                {
                    vector<int> next(budget + 1, 0);
                    for (int b1 = 0; b1 <= budget; b1++)
                    {
                        // Skip unreachable states
                        if (base_buy[b1] == 0 && b1 != 0)
                            continue;

                        for (int b2 = 0; b1 + b2 <= budget; ++b2)
                            next[b1 + b2] = max(next[b1 + b2], base_buy[b1] + child.second[b2]);
                    }
                    base_buy = std::move(next);
                }

                // Pay price of u and add its profit
                for (int b = price; b <= budget; b++)
                    curr[b] = max(curr[b], base_buy[b - price] + profit);
            }

            // Save DP result for node u
            dp[node][parent_bought] = std::move(curr);
        }
    }
};
