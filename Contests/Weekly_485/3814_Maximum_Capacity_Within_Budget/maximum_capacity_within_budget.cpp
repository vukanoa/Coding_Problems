/*
    ==============
    === MEDIUM ===
    ==============

    ====================================
    3814) Maximum Capacity Within Budget
    ====================================

    ============
    Description:
    ============

    You are given two integer arrays costs and capacity, both of length n,
    where costs[i] represents the purchase cost of the ith machine and
    capacity[i] represents its performance capacity.

    You are also given an integer budget.

    You may select at most two distinct machines such that the total cost of
    the selected machines is strictly less than budget.

    Return the maximum achievable total capacity of the selected machines.

    =================================================================================
    FUNCTION: int maxCapacity(vector<int>& costs, vector<int>& capacity, int budget);
    =================================================================================

    ==========================================================================
    ================================ EXAMPLES ================================
    ==========================================================================

    --- Example 1 ---
    Input: costs = [4,8,5,3], capacity = [1,5,2,7], budget = 8
    Output: 8
    Explanation:
        Choose two machines with costs[0] = 4 and costs[3] = 3.
        The total cost is 4 + 3 = 7, which is strictly less than budget = 8.
        The maximum total capacity is capacity[0] + capacity[3] = 1 + 7 = 8.

    --- Example 2 ---
    Input: costs = [3,5,7,4], capacity = [2,4,3,6], budget = 7
    Output: 6
    Explanation:
        Choose one machine with costs[3] = 4.
        The total cost is 4, which is strictly less than budget = 7.
        The maximum total capacity is capacity[3] = 6.

    --- Example 3 ---
    Input: costs = [2,2,2], capacity = [3,5,4], budget = 5
    Output: 9
    Explanation:
        Choose two machines with costs[1] = 2 and costs[2] = 2.
        The total cost is 2 + 2 = 4, which is strictly less than budget = 5.
        The maximum total capacity is capacity[1] + capacity[2] = 5 + 4 = 9.


    *** Constraints ***
    1 <= n == costs.length == capacity.length <= 10^5
    1 <= costs[i], capacity[i] <= 10^5
    1 <= budget <= 2 * 10^5

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

/* Time  Beats: 93.68% */
/* Space Beats: 82.61% */

/* Time  Complexity: O(N * logN) */
/* Space Complexity: O(N)        */
class Solution {
public:
    int maxCapacity(vector<int>& costs, vector<int>& capacities, int budget)
    {
        const int N = costs.size();
        int result = 0;

        vector<pair<int, int>> machines(N);
        for (int i = 0; i < N; i++)
            machines[i] = {costs[i], capacities[i]};

        /* Sort by COST in ASCENDING order */
        sort(machines.begin(), machines.end());

        vector<int> dp(N); // Best so far
        dp[0] = machines[0].second;

        /* Using only ONE machine */
        for (int i = 1; i < N; i++)
            dp[i] = max(dp[i - 1], machines[i].second);

        /* Using TWO machines (Two pointer technique) */
        int right  = N - 1;
        for (int left = 0; left < N; left++)
        {
            const int& cost     = machines[left].first;
            const int& capacity = machines[left].second;

            // Can we afford this machine alone?
            if (cost < budget)
                result = max(result, capacity);

            // Shrink j until the pair is STRICTLY LESS THAN budget
            while (right >= 0 && cost + machines[right].first >= budget)
                --right;

            // Ensure we DON'T select the current machine twice
            int partner_idx = min(left - 1, right);

            if (partner_idx >= 0)
                result = max(result, capacity + dp[partner_idx]);
        }

        return result;
    }
};




/*
    ------------
    --- IDEA ---
    ------------

    Same as above, thought this one uses Binary Search instead of TWo Pointers.
    Bottleneck is Sorting so there is no difference in Big O Time Complexity.

*/

/* Time  Beats: 47.83% */
/* Space Beats: 71.54% */

/* Time  Complexity: O(N * logN) */
/* Space Complexity: O(N)        */
class Solution_Binary_Search {
public:
    int maxCapacity(vector<int>& costs, vector<int>& capacity, int budget)
    {
        const int N = costs.size();
        int result = 0;

        vector<pair<int, int>> machines(N);
        for (int i = 0; i < N; i++)
            machines[i] = {costs[i], capacity[i]};

        /* Sort by COST in ASCENDING order */
        sort(machines.begin(), machines.end());

        vector<int> costs_sorted(N);
        for (int i = 0; i < N; i++)
            costs_sorted[i] = machines[i].first;

        /* Best capacity using ONE machine */
        vector<int> dp(N);
        dp[0] = machines[0].second;

        for (int i = 1; i < N; i++)
            dp[i] = max(dp[i - 1], machines[i].second);

        /* Using TWO machines */
        for (int i = 0; i < N; i++)
        {
            const int& cost     = machines[i].first;
            const int& capacity = machines[i].second;

            const int remaining_budget = budget - cost;

            if (remaining_budget <= 0)
                continue;

            // Can we afford this machine alone?
            if (cost < budget)
                result = max(result, capacity);

            // Find the largest cost STRICTLY LESS THAN remaining_budget
            auto it = lower_bound(costs_sorted.begin(), costs_sorted.end(), remaining_budget);
            const int j = it - costs_sorted.begin() - 1;

            // Ensure we DON'T select the current machine twice
            const int partner_idx = min(i-1, j);

            if (partner_idx >= 0)
                result = max(result, capacity + dp[partner_idx]);
        }

        return result;
    }
};
