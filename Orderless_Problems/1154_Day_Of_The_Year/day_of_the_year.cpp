/*
    ============
    === EASY ===
    ============

    ===========================
    1154) Day of The Year
    ===========================

    ============
    Description:
    ============

    Given a string date representing a Gregorian calendar date formatted as
    YYYY-MM-DD, return the day number of the year.

    =====================================
    FUNCTION: int dayOfYear(string date);
    =====================================

    ==========================================================================
    ================================ EXAMPLES ================================
    ==========================================================================

    --- Example 1 ---
    Input: date = "2019-01-09"
    Output: 9
    Explanation: Given date is the 9th day of the year in 2019.

    --- Example 2 ---
    Input: date = "2019-02-10"
    Output: 41

    *** Constraints ***
    date.length == 10
    date[4] == date[7] == '-', and all other date[i]'s are digits
    date represents a calendar date between Jan 1st, 1900 and Dec 31st, 2019.

*/

#include <string>
#include <vector>
using namespace std;

/*
    ------------
    --- IDEA ---
    ------------

    TODO

*/

/* Time  Beats: 38.22% */
/* Space Beats:  8.01% */

/* Time  Complexity: O(1) */
/* Space Complexity: O(1) */
class Solution {
public:
    int dayOfYear(string date)
    {
        int result;

        int year = stoi(date.substr(0,4));
        int month = stoi(date.substr(5,2));
        int day = stoi(date.substr(8,2));

        vector<int> cumulative_days_non_leap_year = {0,0,31,59,90,120,151,181,212,243,273,304,334};
        vector<int> cumulative_days_leap_year     = {0,0,31,60,91,121,152,182,213,244,274,305,335};
        
        if ((year % 4 == 0 && year % 100 != 0) || (year % 400 == 0))
        {
            result = cumulative_days_leap_year[month] + day;
        }
        else
        {
            result = cumulative_days_non_leap_year[month] + day;
        }

        return result;
    }
};
