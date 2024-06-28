#include <iostream>
#include <vector>
#include <algorithm>

/*
    ==============
    === MEDIUM ===
    ==============

    =======================================
    2285) Maximum Total Importance of Roads
    =======================================

    ============
    Description:
    ============

    You are given an integer n denoting the number of cities in a country. The
    cities are numbered from 0 to n - 1.

    You are also given a 2D integer array roads where roads[i] = [ai, bi]
    denotes that there exists a bidirectional road connecting cities ai and bi.

    You need to assign each city with an integer value from 1 to n, where each
    value can only be used once. The importance of a road is then defined as
    the sum of the values of the two cities it connects.

    Return the maximum total importance of all roads possible after assigning
    the values optimally.

    =========================================================================
    FUNCTION: long long maximumImportance(int n, vector<vector<int>>& roads); 
    =========================================================================

    ==========================================================================
    ================================ EXAMPLES ================================
    ==========================================================================

    --- Example 1 ---
    Input: n = 5, roads = [[0,1],[1,2],[2,3],[0,2],[1,3],[2,4]]
    Output: 43
    Explanation: The figure above shows the country and the assigned values of [2,4,5,3,1].
    - The road (0,1) has an importance of 2 + 4 = 6.
    - The road (1,2) has an importance of 4 + 5 = 9.
    - The road (2,3) has an importance of 5 + 3 = 8.
    - The road (0,2) has an importance of 2 + 5 = 7.
    - The road (1,3) has an importance of 4 + 3 = 7.
    - The road (2,4) has an importance of 5 + 1 = 6.
    The total importance of all roads is 6 + 9 + 8 + 7 + 7 + 6 = 43.
    It can be shown that we cannot obtain a greater total importance than 43.


    --- Example 2 ---
    Input: n = 5, roads = [[0,3],[2,4],[1,3]]
    Output: 20
    Explanation: The figure above shows the country and the assigned values of [4,3,2,5,1].
    - The road (0,3) has an importance of 4 + 5 = 9.
    - The road (2,4) has an importance of 2 + 1 = 3.
    - The road (1,3) has an importance of 3 + 5 = 8.
    The total importance of all roads is 9 + 3 + 8 = 20.
    It can be shown that we cannot obtain a greater total importance than 20.


    *** Constraints ***
    2 <= n <= 5 * 10^4
    1 <= roads.length <= 5 * 10^4
    roads[i].length == 2
    0 <= ai, bi <= n - 1
    ai != bi
    There are no duplicate roads.

*/

/*
    ------------
    --- IDEA ---
    ------------

    TODO

*/

/* Time  Beats: 99.83% */
/* Space Beats: 84.31% */

/* Time  Complexity: O(n * logn + m) */
/* Space Complexity: O(n)            */
class Solution {
public:
    long long maximumImportance(int n, std::vector<std::vector<int>>& roads)
    {
        ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0); // Accelerates
        
        std::vector<long long> degree(n, 0);
        for (auto &pair_cities : roads)
        {
            degree[pair_cities[0]]++;
            degree[pair_cities[1]]++;
        }

        std::sort(degree.begin(), degree.end());

        long long result = 0;
        for (long long i = 0; i < n; i++)
            result += ( (i+1) * degree[i] );

        return result;
    }
};
