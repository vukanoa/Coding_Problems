#include <iostream>

/*
    ==============
    === MEDIUM ===
    ==============

    ================================================
    2477) Minimum Fuel Cost to Report to the Capital
    ================================================

    ============
    Description:
    ============

    There is a tree (i.e., a connected, undirected graph with no cycles)
    structure country network consisting of n cities numbered from 0 to n - 1
    and exactly n - 1 roads. The capital city is city 0. You are given a 2D
    integer array roads where roads[i] = [ai, bi] denotes that there exists a
    bidirectional road connecting cities ai and bi.

    There is a meeting for the representatives of each city. The meeting is in
    the capital city.

    There is a car in each city. You are given an integer seats that indicates
    the number of seats in each car.

    A representative can use the car in their city to travel or change the car
    and ride with another representative. The cost of traveling between two
    cities is one liter of fuel.

    Return the minimum number of liters of fuel to reach the capital city.

    ===========================================================================
    FUNCTION: long long minimumFuelCost(vector<vector<int>>& roads, int seats);
    ===========================================================================

    ==========================================================================
    ================================ EXAMPLES ================================
    ==========================================================================

    --- Example 1 ---

              2
             /
            0
           / \
          1   3

    Input: roads = [[0,1],[0,2],[0,3]], seats = 5
    Output: 3
    Explanation:
    - Representative1 goes directly to the capital with 1 liter of fuel.
    - Representative2 goes directly to the capital with 1 liter of fuel.
    - Representative3 goes directly to the capital with 1 liter of fuel.
    It costs 3 liters of fuel at minimum.
    It can be proven that 3 is the minimum number of liters of fuel needed.


    --- Example 2 ---

              3
             / \
            1   2
             \
              0
             / \
            4   5
           /
          6

    Input: roads = [[3,1],[3,2],[1,0],[0,4],[0,5],[4,6]], seats = 2
    Output: 7
    Explanation:
    - Representative2 goes directly to city 3 with 1 liter of fuel.
    - Representative2 and representative3 go together to city 1 with 1 liter of
      fuel.
    - Representative2 and representative3 go together to the capital with 1
      liter of fuel.
    - Representative1 goes directly to the capital with 1 liter of fuel.
    - Representative5 goes directly to the capital with 1 liter of fuel.
    - Representative6 goes directly to city 4 with 1 liter of fuel.
    - Representative4 and representative6 go together to the capital with 1
      liter of fuel.
    It costs 7 liters of fuel at minimum.
    It can be proven that 7 is the minimum number of liters of fuel needed.



    --- Example 3 ---
    Input: roads = [], seats = 1
    Output: 0
    Explanation: No representatives need to travel to the capital city.


    *** Constraints ***
    1 <= n <= 10^5
    roads.length == n - 1
    roads[i].length == 2
    0 <= ai, bi < n
    ai != bi
    roads represents a valid tree.
    1 <= seats <= 10^5

*/

/*
    ------------
    --- IDEA ---
    ------------

    TODO

*/

/* Time  Beats: 46.46% */
/* Space Beats: 16.74% */

/* Time  Complexity: O(n) */
/* Space Complexity: O(n) */
class Solution {
public:
    long long minimumFuelCost(vector<vector<int>>& roads, int seats)
    {
        std::unordered_map<int, std::vector<int>> adj;

        for (int i = 0; i < roads.size(); i++)
        {
            adj[roads[i][0]].push_back(roads[i][1]);
            adj[roads[i][1]].push_back(roads[i][0]);
        }

        long long fuel = 0;
        for (int& next_city : adj[0])
            dfs(adj, next_city, 0, seats, fuel);

        return fuel;
    }

private:
    int dfs(std::unordered_map<int, std::vector<int>>& adj, int& curr_city, int prev_city, int& seats, long long& fuel)
    {
        int representatives = 1;

        for (int& next_city : adj[curr_city])
        {
            if (next_city == prev_city)
                continue;

            representatives += dfs(adj, next_city, curr_city, seats, fuel);
        }

        int cars = std::ceil(representatives * 1.0 / seats);
        fuel += cars * 1; // Or just " += cars", but it's more verbose

        return representatives;
    }
};
