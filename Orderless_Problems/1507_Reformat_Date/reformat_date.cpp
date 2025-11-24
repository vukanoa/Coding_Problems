/*
    ============
    === EASY ===
    ============

    ===========================
    1507) Reformat Date
    ===========================

    ============
    Description:
    ============

    Given a date string in the form Day Month Year, where:

        Day is in the set {"1st", "2nd", "3rd", "4th", ..., "30th", "31st"}.
        Month is in the set {"Jan", "Feb", "Mar", "Apr", "May", "Jun", "Jul", "Aug", "Sep", "Oct", "Nov", "Dec"}.
        Year is in the range [1900, 2100].

    Convert the date string to the format YYYY-MM-DD, where:

        YYYY denotes the 4 digit year.
        MM denotes the 2 digit month.
        DD denotes the 2 digit day.

    ===========================================
    FUNCTION: string reformatDate(string date);
    ===========================================

    ==========================================================================
    ================================ EXAMPLES ================================
    ==========================================================================

    --- Example 1 ---
    Input: date = "20th Oct 2052"
    Output: "2052-10-20"

    --- Example 2 ---
    Input: date = "6th Jun 1933"
    Output: "1933-06-06"

    --- Example 3 ---
    Input: date = "26th May 1960"
    Output: "1960-05-26"


    *** Constraints ***
    The given dates are guaranteed to be valid, so no error handling is
    necessary.

*/

#include <string>
#include <sstream>
#include <unordered_map>
#include <cstdio>
using namespace std;

/*
    ------------
    --- IDEA ---
    ------------

    TODO

*/

/* Time  Beats: 100.00% */
/* Space Beats:  15.41% */

/* Time  Complexity: O(N) */
/* Space Complexity: O(N) */
class Solution {
public:
    string reformatDate(string date)
    {
        unordered_map<string, int> month_map = {
            {"Jan", 1}, {"Feb", 2},  {"Mar", 3},  {"Apr", 4},
            {"May", 5}, {"Jun", 6},  {"Jul", 7},  {"Aug", 8},
            {"Sep", 9}, {"Oct", 10}, {"Nov", 11}, {"Dec", 12}
        };

        istringstream iss(date);

        string day_str;
        string month_str;
        string year_str;

        // Read three parts
        iss >> day_str >> month_str >> year_str;

        int day = 0;
        int i = 0;
        while (isdigit(day_str[i]))
        {
            day = day * 10 + (day_str[i] - '0');
            i++;
        }

        int month = month_map[month_str];
        int year  = stoi(year_str);

        char buffer[11];
        sprintf(buffer, "%04d-%02d-%02d", year, month, day);

        return string(buffer);
    }
};
