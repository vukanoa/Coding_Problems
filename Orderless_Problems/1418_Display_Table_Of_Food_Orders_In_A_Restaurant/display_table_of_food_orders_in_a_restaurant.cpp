/*
    ==============
    === MEDIUM ===
    ==============

    ==================================================
    1418) Display Table of Food Orders in a Restaurant
    ==================================================

    ============
    Description:
    ============

    Given the array orders, which represents the orders that customers have
    done in a restaurant. More specifically
    orders[i]=[customerNamei,tableNumberi,foodItemi] where customerNamei is the
    name of the customer, tableNumberi is the table customer sit at, and
    foodItemi is the item customer orders.

    Return the restaurant's “display table”. The “display table” is a table
    whose row entries denote how many of each food item each table ordered. The
    first column is the table number and the remaining columns correspond to
    each food item in alphabetical order. The first row should be a header
    whose first column is “Table”, followed by the names of the food items.
    Note that the customer names are not part of the table. Additionally, the
    rows should be sorted in numerically increasing order.

    ==============================================================================
    FUNCTION: vector<vector<string>> displayTable(vector<vector<string>>& orders);
    ==============================================================================

    ==========================================================================
    ================================ EXAMPLES ================================
    ==========================================================================

    --- Example 1 ---
    Input: orders = [["David","3","Ceviche"],["Corina","10","Beef Burrito"],["David","3","Fried Chicken"],["Carla","5","Water"],["Carla","5","Ceviche"],["Rous","3","Ceviche"]]
    Output: [["Table","Beef Burrito","Ceviche","Fried Chicken","Water"],["3","0","2","1","0"],["5","0","1","0","1"],["10","1","0","0","0"]]
    Explanation:
    The displaying table looks like:
    Table,Beef Burrito,Ceviche,Fried Chicken,Water
    3    ,0           ,2      ,1            ,0
    5    ,0           ,1      ,0            ,1
    10   ,1           ,0      ,0            ,0
    For the table 3: David orders "Ceviche" and "Fried Chicken", and Rous orders "Ceviche".
    For the table 5: Carla orders "Water" and "Ceviche".
    For the table 10: Corina orders "Beef Burrito".


    --- Example 2 ---
    Input: orders = [["James","12","Fried Chicken"],["Ratesh","12","Fried Chicken"],["Amadeus","12","Fried Chicken"],["Adam","1","Canadian Waffles"],["Brianna","1","Canadian Waffles"]]
    Output: [["Table","Canadian Waffles","Fried Chicken"],["1","2","0"],["12","0","3"]]
    Explanation:
    For the table 1: Adam and Brianna order "Canadian Waffles".
    For the table 12: James, Ratesh and Amadeus order "Fried Chicken".

    --- Example 3 ---
    Input: orders = [["Laura","2","Bean Burrito"],["Jhon","2","Beef Burrito"],["Melissa","2","Soda"]]
    Output: [["Table","Bean Burrito","Beef Burrito","Soda"],["2","1","1","1"]]


    *** Constraints ***
    1 <= orders.length <= 5 * 10^4
    orders[i].length == 3
    1 <= customerNamei.length, foodItemi.length <= 20
    customerNamei and foodItemi consist of lowercase and uppercase English letters and the space character.
    tableNumberi is a valid integer between 1 and 500.

*/

#include <algorithm>
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

/* Time  Beats: 81.93% */
/* Space Beats: 92.77% */

/* Time  Complexity: O(N^2)      */
/* Space Complexity: O(N * logN) */
class Solution {
public:
    vector<vector<string>> displayTable(vector<vector<string>>& orders)
    {
        // dish_count_by_table[table_number][dish_name] -> count
        unordered_map<string, unordered_map<string, int>> dish_count_by_table;
        unordered_map<string, int> unique_dishes;

        int N = orders.size();

        for (int row = 0; row < N; row++)
        {
            const string& table_number = orders[row][1];
            const string& dish_name    = orders[row][2];

            unique_dishes[dish_name] = 1;
            dish_count_by_table[table_number][dish_name]++;
        }

        int total_tables = dish_count_by_table.size();
        int total_dishes = unique_dishes.size();

        vector<vector<string>> result(total_tables + 1, vector<string>( total_dishes + 1, "" ));

        result[0][0] = "Table";

        int col = 1;
        for (const auto &entry : unique_dishes)
        {
            result[0][col] = entry.first;
            col++;
        }

        // Sort dish names alphabetically
        sort( result[0].begin() + 1, result[0].end() );

        // Fill rows
        int row = 1;
        for (const auto &table_entry : dish_count_by_table)
        {
            const string& table_number = table_entry.first;
            const auto&   dish_map     = table_entry.second;

            result[row][0] = table_number;

            for (int col = 1; col <= total_dishes; col++)
            {
                const string& dish_name = result[0][col];

                int count = 0;
                if ( dish_map.count( dish_name ))
                {
                    count = dish_map.at( dish_name );
                }

                result[row][col] = to_string(count);
            }

            row++;
        }

        // Sort by table number (as integer)
        sort(result.begin() + 1, result.end(), []( const vector<string>& a, const vector<string>& b) {
            return stoi(a[0]) < stoi(b[0]);
        });

        return result;
    }
};
