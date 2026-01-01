#include <iostream>
#include <vector>
#include <unordered_map>

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

    Input: roads = [[1,0],[0,2],[3,1],[1,4],[5,0]]
           seats = 1

    Instead of visualizing it like this:

            3
            |
            1 -- 0 -- 2
            |    |
            4    5

    Instead, you should visualize it as a Tree:


               __1__
              /  |  \
             /   |   \
            /    |    \
           /     |     \
          /      |      \
         2       1       5
                / \
               /   \
              /     \
             4       3



    Now we have to use the "acyclicness" property of the graph, that's why we
    are only going have to check if the "next_city" is not a "prev_city".

    Everything else is taken care of by itself simply by being an acyclic
    graph.

    Since the end goal is to get at city '0', we are going to look at it as in
    the picture above(ASCII Drawing).

    Now try to go through the code and everything will be clear. There is no
    need for a detailed explanation.

    The Solution should be obvious once you consider the fact that they said in
    the Description:
        "There is a tree (i.e., a connected, undirected graph with no cycles)"

    Once you see that, if you've solved enough of Graph problems, it would and
    should be obvious.

    If it is NOT obvious, you should definitely try to solve easier ones first
    and only once you master the basics and other more "typical" Graph problems
    only then proceed to try and to this problem. Otherwise, it doesn't make
    any sense.

    It's "kind of" a specific one, in a way.(Not too specific, but enough)

    Make sure you have solved easier and "more typical" ones, after that this
    one will be fairly obvious.

*/

/* Time  Beats: 52.76% */
/* Space Beats: 30.05% */

/* Time  Complexity: O(n) */
/* Space Complexity: O(n) */
class Solution {
public:
    long long minimumFuelCost(vector<vector<int>>& roads, int seats)
    {
        std::unordered_map<int, std::vector<int>> adj_list;

        for (const auto& road : roads)
        {
            adj_list[road[0]].push_back(road[1]);
            adj_list[road[1]].push_back(road[0]);
        }

        long long fuel = 0;
        for (int& next_city : adj_list[0])
            dfs(adj_list, seats, fuel, next_city, 0);

        return fuel;
    }

private:
    int dfs(std::unordered_map<int, std::vector<int>>& adj_list,
            int& seats,
            long long& fuel,
            int& curr_city,
            int  prev_city)
    {
        int representatives = 1;

        for (int& next_city : adj_list[curr_city])
        {
            if (next_city == prev_city)
                continue;

            representatives += dfs(adj_list, seats, fuel, next_city, curr_city);
        }

        int cars = (int) std::ceil(1.0 * representatives / seats);
        fuel += cars * 1; // Or just " += cars", but it's more verbose

        return representatives;
    }
};
