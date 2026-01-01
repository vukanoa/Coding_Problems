#include <iostream>
#include <vector>
#include <string>
#include <unordered_map>
#include <algorithm>

/*
    ============
    === HARD ===
    ============

    ===========================
    332) Reconstruct Itinerary
    ===========================

    ============
    Description:
    ============

    You are given a list of airline tickets where tickets[i] = [fromi, toi]
    represent the departure and the arrival airports of one flight. Reconstruct
    the itinerary in order and return it.

    All of the tickets belong to a man who departs from "JFK", thus, the
    itinerary must begin with "JFK". If there are multiple valid itineraries,
    you should return the itinerary that has the smallest lexical order when
    read as a single string.

        For example, the itinerary ["JFK", "LGA"] has a smaller lexical order
        than ["JFK", "LGB"].

    You may assume all tickets form at least one valid itinerary. You must use
    all the tickets once and only once.

    ========================================================================
    FUNCTION: vector<string> findItinerary(vector<vector<string>>& tickets);
    ========================================================================

    ==========================================================================
    ================================ EXAMPLES ================================
    ==========================================================================

    --- Example 1 ---
    Input: tickets = [["MUC","LHR"],["JFK","MUC"],["SFO","SJC"],["LHR","SFO"]]
    Output: ["JFK","MUC","LHR","SFO","SJC"]

    --- Example 2 ---
    Input: tickets =
    [["JFK","SFO"],["JFK","ATL"],["SFO","ATL"],["ATL","JFK"],["ATL","SFO"]]
    Output: ["JFK","ATL","JFK","SFO","ATL","SFO"]
    Explanation: Another possible reconstruction is
    ["JFK","SFO","ATL","JFK","ATL","SFO"] but it is larger in lexical order.


    *** Constraints ***
    1 <= tickets.length <= 300
    tickets[i].length == 2
    fromi.length == 3
    toi.length == 3
    fromi and toi consist of uppercase English letters.
    fromi != toi

*/

using namespace std;

/*
    ------------
    --- IDEA ---
    ------------

    TODO

*/

/* Time  Beats: 95.01% */
/* Space Beats: 86.69% */

/* Time  Complexity: O((V + E)^2) */
/* Space Complexity: O(E^2)       */
class Solution {
public:
    vector<string> findItinerary(vector<vector<string>>& tickets)
    {
        unordered_map<string, vector<string>> adj_list;
        vector<string> result;

        for (auto& ticket : tickets)
            adj_list[ticket[0]].push_back(ticket[1]);

        for (auto& [key, value] : adj_list)
            sort(value.begin(), value.end());

        function<void(const string&)> dfs = [&](const string& src)
        {
            while (!adj_list[src].empty())
            {
                string dest = adj_list[src].front();
                adj_list[src].erase(adj_list[src].begin()); // pop the destination
                dfs(dest);
            }

            result.push_back(src);
        };

        dfs("JFK");
        reverse(result.begin(), result.end());

        if (result.size() != tickets.size() + 1)
            return {};

        return result;
    }
};
