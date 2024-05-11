#include <iostream>
#include <vector>
#include <queue>
#include <algorithm>

/*
    ============
    === HARD ===
    ============

    ===================================
    857) Minimum Cost To Hire K Workers
    ===================================

    ============
    Description:
    ============

    There are n workers. You are given two integer arrays quality and wage
    where quality[i] is the quality of the ith worker and wage[i] is the
    minimum wage expectation for the ith worker.

    We want to hire exactly k workers to form a paid group. To hire a group of
    k workers, we must pay them according to the following rules:

        Every worker in the paid group must be paid at least their minimum wage
        expectation.  In the group, each worker's pay must be directly
        proportional to their quality. This means if a worker’s quality is
        double that of another worker in the group, then they must be paid
        twice as much as the other worker.

    Given the integer k, return the least amount of money needed to form a paid
    group satisfying the above conditions. Answers within 10-5 of the actual
    answer will be accepted.

    ======================================================================================
    FUNCTION: double mincostToHireWorkers(vector<int>& quality, vector<int>& wage, int k);
    ======================================================================================

    ==========================================================================
    ================================ EXAMPLES ================================
    ==========================================================================

    --- Example 1 ---
    Input: quality = [10,20,5], wage = [70,50,30], k = 2
    Output: 105.00000
    Explanation: We pay 70 to 0th worker and 35 to 2nd worker.

    --- Example 2 ---
    Input: quality = [3,1,10,10,1], wage = [4,8,2,2,7], k = 3
    Output: 30.66667
    Explanation: We pay 4 to 0th worker, 13.33333 to 2nd and 3rd workers
                 separately.


    *** Constraints ***
    n == quality.length == wage.length
    1 <= k <= n <= 10^4
    1 <= quality[i], wage[i] <= 10^4

*/

/*
    ------------
    --- IDEA ---
    ------------

    TODO

*/

/* Time  Beats: 96.93% */
/* Space Beats: 32.68% */

/* Time  Complexity: O(n * logn) */
/* Space Complexity: O(n) */
class Solution {
public:
    double mincostToHireWorkers(std::vector<int>& quality, std::vector<int>& wage, int k)
    {
        ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0); // Accelerates

        const int N = quality.size();
        std::vector<std::pair<double, int>> ratio;

        for (int i = 0; i < N; ++i)
            ratio.push_back( {static_cast<double>(wage[i]) / quality[i], i} );

        // Sorto by ratio
        std::sort(ratio.begin(), ratio.end());

        std::priority_queue<int> max_heap;
        int quality_sum = 0;
        double max_rate = 0.0;

        for (int i = 0; i < k; i++)
        {
            quality_sum += quality[ratio[i].second];
            max_rate = std::max(max_rate, ratio[i].first);

            max_heap.push(quality[ratio[i].second]);
        }

        double result = max_rate * quality_sum;
        for (int i = k; i < N; i++)
        {
            max_rate = max(max_rate, ratio[i].first);
            quality_sum -= max_heap.top();
            max_heap.pop();

            quality_sum += quality[ratio[i].second];
            max_heap.push(quality[ratio[i].second]);
            result = std::min(result, max_rate * quality_sum);
        }

        return result;
    }
};
