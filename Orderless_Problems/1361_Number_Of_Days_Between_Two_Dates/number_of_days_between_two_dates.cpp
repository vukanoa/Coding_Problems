/*
    ============
    === EASY ===
    ============

    =====================================
    1361) Number of Days Between Two Days
    =====================================

    ============
    Description:
    ============

    Write a program to count the number of days between two dates.

    The two dates are given as strings, their format is YYYY-MM-DD as shown in
    the examples.

    ===========================================================
    FUNCTION: int daysBetweenDates(string date1, string date2);
    ===========================================================

    ==========================================================================
    ================================ EXAMPLES ================================
    ==========================================================================

    --- Example 1 ---
    Input: date1 = "2019-06-29", date2 = "2019-06-30"
    Output: 1

    --- Example 2 ---
    Input: date1 = "2020-01-15", date2 = "2019-12-31"
    Output: 15


    *** Constraints ***
    The given dates are valid dates between the years 1971 and 2100.

*/

#include <string>
using namespace std;

/*
    ------------
    --- IDEA ---
    ------------

    TODO
    You have to be a little bit familiar with Gregorian Calendar.

*/

/* Time  Beats: 100.00% */
/* Space Beats:  95.04% */

/* Time  Complexity: O(N) */
/* Space Complexity: O(1) */
class Solution {
public:
    int daysBetweenDates(string date1, string date2)
    {
        return abs(date_to_int(date2) - date_to_int(date1));
    }
    
private:
    int date_to_int(string s_date)
    {
        const int YEAR  = stoi(s_date.substr(0, 4));
        const int MONTH = stoi(s_date.substr(5, 2));
        const int DAY   = stoi(s_date.substr(8, 2));
        
        int date = 0;
        for (int curr_year = 1971; curr_year < YEAR; curr_year++)
        {
            date += is_leap_year(curr_year) ? 366 : 365;
        }

        for (int curr_month = 1; curr_month < MONTH; curr_month++)
        {
            date += days_in_month(curr_month, YEAR);
        }

        return date + DAY;
    }
    
    bool is_leap_year(int year)
    {
        return (year % 4  == 0 && year % 100 != 0) || year % 400 == 0;
    }
    
    int days_in_month(int m, int year)
    { 
        if (m == 1 || m == 3 || m == 5 || m == 7 || m == 8 || m == 10 || m == 12)
        {
            return 31;
        }

        if (m == 2)
            return is_leap_year(year) ? 29 : 28;

        return 30;
    }
};
