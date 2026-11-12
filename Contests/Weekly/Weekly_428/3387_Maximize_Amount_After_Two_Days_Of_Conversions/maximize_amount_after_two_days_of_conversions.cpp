/*
    ==============
    === MEDIUM ===
    ==============

    ==================================================
    3387) Maximum Amount After Two Days of Conversions
    ==================================================

    ============
    Description:
    ============

    You are given a string initialCurrency, and you start with 1.0 of
    initialCurrency.

    You are also given four arrays with currency pairs (strings) and rates
    (real numbers):

        + pairs1[i] = [startCurrencyi, targetCurrencyi] denotes that you can
          convert from startCurrencyi to targetCurrencyi at a rate of rates1[i]
          on day 1.

        + pairs2[i] = [startCurrencyi, targetCurrencyi] denotes that you can
          convert from startCurrencyi to targetCurrencyi at a rate of rates2[i]
          on day 2.

        Also, each targetCurrency can be converted back to its corresponding
        startCurrency at a rate of 1 / rate.

    You can perform any number of conversions, including zero, using rates1 on
    day 1, followed by any number of additional conversions, including zero,
    using rates2 on day 2.

    Return the maximum amount of initialCurrency you can have after performing
    any number of conversions on both days in order.

    =====
    Note: Conversion rates are valid, and there will be no contradictions in
          the rates for either day. The rates for the days are independent of
          each other. 
    =====

    ===================================================================================================================================================================
    FUNCTION: double maxAmount(string initialCurrency, vector<vector<string>>& pairs1, vector<double>& rates1, vector<vector<string>>& pairs2, vector<double>& rates2);
    ===================================================================================================================================================================

    ==========================================================================
    ================================ EXAMPLES ================================
    ==========================================================================

    --- Example 1 ---
    Input: initialCurrency = "EUR", pairs1 = [["EUR","USD"],["USD","JPY"]], rates1 = [2.0,3.0], pairs2 = [["JPY","USD"],["USD","CHF"],["CHF","EUR"]], rates2 = [4.0,5.0,6.0]
    Output: 720.00000
    Explanation:
    To get the maximum amount of EUR, starting with 1.0 EUR:
        On Day 1:
            Convert EUR to USD to get 2.0 USD.
            Convert USD to JPY to get 6.0 JPY.
        On Day 2:
            Convert JPY to USD to get 24.0 USD.
            Convert USD to CHF to get 120.0 CHF.
            Finally, convert CHF to EUR to get 720.0 EUR.


    --- Example 2 ---
    Input: initialCurrency = "NGN", pairs1 = [["NGN","EUR"]], rates1 = [9.0], pairs2 = [["NGN","EUR"]], rates2 = [6.0]
    Output: 1.50000
    Explanation:
    Converting NGN to EUR on day 1 and EUR to NGN using the inverse rate on day 2 gives the maximum amount.


    --- Example 3 ---
    Input: initialCurrency = "USD", pairs1 = [["USD","EUR"]], rates1 = [1.0], pairs2 = [["EUR","JPY"]], rates2 = [10.0]
    Output: 1.00000
    Explanation:
    In this example, there is no need to make any conversions on either day.



    *** Constraints ***
    1 <= initialCurrency.length <= 3
    initialCurrency consists only of uppercase English letters.
    1 <= n == pairs1.length <= 10
    1 <= m == pairs2.length <= 10
    pairs1[i] == [startCurrencyi, targetCurrencyi]
    pairs2[i] == [startCurrencyi, targetCurrencyi]
    1 <= startCurrencyi.length, targetCurrencyi.length <= 3
    startCurrencyi and targetCurrencyi consist only of uppercase English letters.
    rates1.length == n
    rates2.length == m
    1.0 <= rates1[i], rates2[i] <= 10.0
    The input is generated such that there are no contradictions or cycles in the conversion graphs for either day.
    The input is generated such that the output is at most 5 * 10^10.

*/

#include <queue>
#include <string>
#include <unordered_map>
#include <vector>
using namespace std;

/*
    ------------
    --- IDEA ---
    ------------

    TODO

*/

/* Time  Beats: 44.20% */
/* Space Beats: 17.39% */

/* Time  Complexity: O(V^2)   */
/* Space Complexity: O(V + E) */
class Solution_BFS {
private:
    unordered_map<string, unordered_map<string, double>> adj_list_day1;
    unordered_map<string, unordered_map<string, double>> adj_list_day2;

public:
    double maxAmount(string initialCurrency, vector<vector<string>>& pairs1, vector<double>& rates1, vector<vector<string>>& pairs2, vector<double>& rates2) 
    {
        adj_list_day1 = build_adj_list(pairs1, rates1);
        adj_list_day2 = build_adj_list(pairs2, rates2);

        unordered_map<string, double> max_amounts_day1 = bfs_day1(initialCurrency);
        unordered_map<string, double> max_amounts_day2 = bfs_day2(initialCurrency, max_amounts_day1);

        return max_amounts_day2[initialCurrency];
    }

private:
    unordered_map<string, unordered_map<string, double>> build_adj_list(vector<vector<string>>& pairs, vector<double>& rates) 
    {
        const int E = pairs.size();
        unordered_map<string, unordered_map<string, double>> adj_list;

        for (int i = 0; i < E; i++) 
        {
            const string& start  = pairs[i][0];
            const string& target = pairs[i][1];
            const double& rate   = rates[i];

            adj_list[start ][target] = rate;
            adj_list[target][start ] = 1.0 / rate;
        }

        return adj_list;
    }

    unordered_map<string, double> bfs_day1(string start_str) 
    {
        unordered_map<string, double> max_amount;
        max_amount[start_str] = 1.0;

        queue<string> queue;
        queue.push(start_str);

        while ( ! queue.empty()) 
        {
            string curr_str = queue.front();
            queue.pop();

            double curr_amount = max_amount[curr_str];

            for (const auto& entry : adj_list_day1[curr_str]) 
            {
                const string& neighbor = entry.first;
                const double& rate     = entry.second;

                double new_amount = curr_amount * rate;

                if (new_amount > max_amount[neighbor]) 
                {
                    max_amount[neighbor] = new_amount;
                    queue.push(neighbor);
                }
            }
        }

        return max_amount;
    }

    unordered_map<string, double> bfs_day2(string start_str, unordered_map<string, double>& initialAmounts) 
    {
        unordered_map<string, double> max_amount = initialAmounts;

        queue<string> queue;
        for (const auto& pair : initialAmounts) 
            queue.push(pair.first);

        while ( ! queue.empty()) 
        {
            string curr_str = queue.front();
            queue.pop();
            double curr_amount = max_amount[curr_str];

            for (const auto& entry : adj_list_day2[curr_str]) 
            {
                const string& neighbor = entry.first;
                const double& rate     = entry.second;

                double new_amount = curr_amount * rate;

                if (new_amount > max_amount[neighbor]) 
                {
                    max_amount[neighbor] = new_amount;
                    queue.push(neighbor);
                }
            }
        }

        return max_amount;
    }
};




/*
    ------------
    --- IDEA ---
    ------------

    TODO

*/

/* Time  Beats: 84.06% */
/* Space Beats: 91.30% */

/* Time  Complexity: O(E1^2  +  E2^2) */
/* Space Complexity: O(V)             */
class Solution_Bellman_Ford {
public:
    double maxAmount(string initialCurrency, vector<vector<string>>& pairs1, vector<double>& rates1, vector<vector<string>>& pairs2, vector<double>& rates2)
    {
        unordered_map<string, double> max_amount;
        max_amount[initialCurrency] = 1.0;

        bellman_ford(max_amount, pairs1, rates1); // Day1
        bellman_ford(max_amount, pairs2, rates2); // Day2

        return max_amount[initialCurrency]; 
    }

    void bellman_ford(unordered_map<string, double>& max_amount, vector<vector<string>>& pairs, vector<double>& rates)
    {
        const int E = pairs.size();

        for (int relax_iteration = 0; relax_iteration < pairs.size(); relax_iteration++)
        {
            for (int i = 0; i < E; i++)
            {
                max_amount[pairs[i][1]] = max(max_amount[pairs[i][1]], max_amount[pairs[i][0]] * rates[i]);
                max_amount[pairs[i][0]] = max(max_amount[pairs[i][0]], max_amount[pairs[i][1]] / rates[i]);
            }
        } 
    }
};
