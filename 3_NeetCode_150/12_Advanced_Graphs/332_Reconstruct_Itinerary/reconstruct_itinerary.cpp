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

#include <functional>
#include <queue>
#include <vector>
#include <string>
#include <unordered_map>
#include <algorithm>
using namespace std;

/*
    ------------
    --- IDEA ---
    ------------

    TODO

*/

/* Time  Beats: 90.01% */
/* Space Beats:  5.50% */

/* Time  Complexity: O(E * logD) */ // Where D is max-out degree
/* Space Complexity: O(E)        */
class Solution_Min_Heap {
private:
    unordered_map<string, priority_queue<string, vector<string>, greater<string>>> adj_list;
public:
    vector<string> findItinerary(vector<vector<string>>& tickets)
    {
        const int V = tickets.size();

        /* If self-loops are ALLOWED, then E = V*V, otherwise E = V * (V-1) */
        vector<string> result;
        result.reserve(V * V);

        unordered_map<string, priority_queue<string, vector<string>, greater<string>>> adj_list;
        for (const auto& ticket : tickets)
        {
            const string& from = ticket[0];
            const string& to   = ticket[1];

            adj_list[from].push(to);
        }

        /* Postorder DFS */
        postorder_dfs("JFK", result, adj_list);

        /* Reverse the result since we've done a POSTORDER dfs */
        reverse(result.begin(), result.end());

        return result;
    }

private:
    void postorder_dfs(string node,
                       vector<string>& result,
                       unordered_map<string, priority_queue<string, vector<string>, greater<string>>>& adj_list)
    {
        while ( ! adj_list[node].empty())
        {
            string neighbor = adj_list[node].top();
            adj_list[node].pop();

            postorder_dfs(neighbor, result, adj_list);
        }

        /* Postorder DFS */
        result.push_back(node);
    }
};
