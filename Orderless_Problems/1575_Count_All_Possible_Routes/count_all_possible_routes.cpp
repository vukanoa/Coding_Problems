#include <iostream>
#include <vector>

/*
    ============
    === HARD ===
    ============

    ===============================
    1575) Count All Possible Routes
    ===============================

    ============
    Description:
    ============

    You are given an array of distinct positive integers locations where
    locations[i] represents the position of city i. You are also given integers
    start, finish and fuel representing the starting city, ending city, and the
    initial amount of fuel you have, respectively.

    At each step, if you are at city i, you can pick any city j such that j !=
    i and 0 <= j < locations.length and move to city j. Moving from city i to
    city j reduces the amount of fuel you have by |locations[i] -
    locations[j]|. Please notice that |x| denotes the absolute value of x.

    Notice that fuel cannot become negative at any point in time, and that you
    are allowed to visit any city more than once (including start and finish).

    Return the count of all possible routes from start to finish. Since the
    answer may be too large, return it modulo 109 + 7.

    ===================================================================================
    FUNCTION: int countRoutes(vector<int>& locations, int start, int finish, int fuel); 
    ===================================================================================

    ==========================================================================
    ================================ EXAMPLES ================================
    ==========================================================================

    --- Example 1 ---
    Input: locations = [2,3,6,8,4], start = 1, finish = 3, fuel = 5
    Output: 4
    Explanation: The following are all possible routes, each uses 5 units of fuel:
    1 -> 3
    1 -> 2 -> 3
    1 -> 4 -> 3
    1 -> 4 -> 2 -> 3


    --- Example 2 ---
    Input: locations = [4,3,1], start = 1, finish = 0, fuel = 6
    Output: 5
    Explanation: The following are all possible routes:
    1 -> 0, used fuel = 1
    1 -> 2 -> 0, used fuel = 5
    1 -> 2 -> 1 -> 0, used fuel = 5
    1 -> 0 -> 1 -> 0, used fuel = 3
    1 -> 0 -> 1 -> 0 -> 1 -> 0, used fuel = 5


    --- Example 3 ---
    Input: locations = [5,2,1], start = 0, finish = 2, fuel = 3
    Output: 0
    Explanation: It is impossible to get from 0 to 2 using only 3 units of fuel
                 since the shortest route needs 4 units of fuel


    *** Constraints ***
    2 <= locations.length <= 100
    1 <= locations[i] <= 10^9
    All integers in locations are distinct.
    0 <= start, finish < locations.length
    1 <= fuel <= 200

*/

/*
    ------------
    --- IDEA ---
    ------------

    TODO

*/

/* Time  Beats: 32.64% */
/* Space Beats: 30.55% */

/* Time  Complexity: O(n^2 * fuel) */
/* Space Complexity: O(n * fuel)   */
class Solution {
public:
    const int MOD = 1e9+7;
    
    int countRoutes(std::vector<int>& locations, int start, int finish, int fuel)
    {
        const int n = locations.size();
        std::vector<std::vector<int>> dp(n, std::vector(fuel+1, -1));

        return dfs(dp, locations, start, finish, fuel);
    }

private:
    int dfs(std::vector<std::vector<int>>& dp,
            std::vector<int>& locations,
            int start,
            int finish,
            int fuel)
    {
        const int n = locations.size();

        if (fuel < 0)
            return 0;

        if (dp[start][fuel] != -1)
            return dp[start][fuel];

        int result = 0;
        if (start == finish)
            result++;

        for(int j = 0; j < n; j++)
        {
            if (j == start)
                continue;

            int new_fuel = fuel - std::abs(locations[start] - locations[j]);

            result = (result + dfs(dp, locations, j, finish, new_fuel)) % MOD;
        }

        return  dp[start][fuel] = result;
    }
};
