/*
    ============
    === HARD ===
    ============

    ===========================
    1478) Allocate Mailboxes
    ===========================

    ============
    Description:
    ============

    Given the array houses where houses[i] is the location of the ith house
    along a street and an integer k, allocate k mailboxes in the street.

    Return the minimum total distance between each house and its nearest
    mailbox.

    The test cases are generated so that the answer fits in a 32-bit integer.

    =====================================================
    FUNCTION: int minDistance(vector<int>& houses, int k;
    =====================================================

    ==========================================================================
    ================================ EXAMPLES ================================
    ==========================================================================

    --- Example 1 ---
    Input: houses = [1,4,8,10,20], k = 3
    Output: 5
    Explanation: Allocate mailboxes in position 3, 9 and 20.
    Minimum total distance from each houses to nearest mailboxes is |3-1| +
    |4-3| + |9-8| + |10-9| + |20-20| = 5 


    --- Example 2 ---
    Input: houses = [2,3,5,12,18], k = 2
    Output: 9
    Explanation: Allocate mailboxes in position 3 and 14.
    Minimum total distance from each houses to nearest mailboxes is |2-3| +
    |3-3| + |5-3| + |12-14| + |18-14| = 9.



    *** Constraints ***
    1 <= k <= houses.length <= 100
    1 <= houses[i] <= 10^4
    All the integers of houses are unique.

*/

#include <algorithm>
#include <cstring>
#include <vector>
using namespace std;

/*
    ------------
    --- IDEA ---
    ------------

    TODO

*/

/* Time  Beats: 90.11% */
/* Space Beats: 98.49% */

/* Time  Complexity: O(N^2) */
/* Space Complexity: O(N^2) */
class Solution {
private:
    const int INF = 1e9;

    int cost[100][100] = {};
    int memo[100][100] = {};

public:
    int minDistance(vector<int>& houses, int k)
    {
        const int N = houses.size();

        /* Sort */
        sort(houses.begin(), houses.end());

        /* Memset */
        memset(memo, 0xff, sizeof(memo));


        for (int i = 0; i < N; i++)
        {
            for (int j = 0; j < N; j++)
            {
                int median_pos = houses[(i + j) / 2];

                for (int m = i; m <= j; m++)
                    cost[i][j] += abs(median_pos - houses[m]);
            }
        }

        return solve(0, k, houses);
    }

    int solve(int idx, int k, vector<int>& houses)
    {
        const int N = houses.size();

        if (k == 0 && idx == N)
            return 0;

        if (k == 0 || idx == N)
            return INF;

        if (memo[k][idx] != -1)
            return memo[k][idx];

        int result = INF;

        for (int j = idx; j < N; j++)
            result = min(result, cost[idx][j] + solve(j + 1, k-1, houses));

        return memo[k][idx] = result;
    }
};
