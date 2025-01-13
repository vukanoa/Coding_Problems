/*
    ============
    === EASY ===
    ============

    ============================
    3280) Convert Date to Binary
    ============================

    ============
    Description:
    ============

    You are given a string date representing a Gregorian calendar date in the
    yyyy-mm-dd format.

    date can be written in its binary representation obtained by converting
    year, month, and day to their binary representations without any leading
    zeroes and writing them down in year-month-day format.

    Return the binary representation of date.

    ==================================================
    FUNCTION: string convertDateToBinary(string date);
    ==================================================

    ==========================================================================
    ================================ EXAMPLES ================================
    ==========================================================================

    --- Example 1 ---
    Input: date = "2080-02-29"
    Output: "100000100000-10-11101"
    Explanation: 100000100000, 10, and 11101 are the binary representations of
                 2080, 02, and 29 respectively.

    --- Example 2 ---
    Input: date = "1900-01-01"
    Output: "11101101100-1-1"
    Explanation: 11101101100, 1, and 1 are the binary representations of 1900,
                 1, and 1 respectively.


    *** Constraints ***
    date.length == 10
    date[4] == date[7] == '-', and all other date[i]'s are digits.
    The input is generated such that date represents a valid Gregorian calendar date between Jan 1st, 1900 and Dec 31st, 2100 (both inclusive).

*/

#include <string>
using namespace std;

/*
    ------------
    --- IDEA ---
    ------------

    TODO

*/

/* Time  Beats: 100.00% */
/* Space Beats:  52.56% */

/* Time  Complexity: O(n) */
/* Space Complexity: O(n) */
class Solution {
public:
    string convertDateToBinary(string date)
    {
        const int N = date.length();
        string result = "";

        string year_str  = date.substr(0, 4);
        string month_str = date.substr(5, 2);
        string day_str   = date.substr(8, 2);

        int year_num  = stoi(year_str);
        int month_num = stoi(month_str);
        int day_num   = stoi(day_str);

        string year_bin_str;
        string month_bin_str;
        string day_bin_str;

        for (int i = 31; i >= 0; i--)
        {
            // Year
            if (year_num & (1 << i))
                year_bin_str += "1";
            else
                year_bin_str += "0";

            // Month
            if (month_num & (1 << i))
                month_bin_str += "1";
            else
                month_bin_str += "0";

            // Day
            if (day_num & (1 << i))
                day_bin_str += "1";
            else
                day_bin_str += "0";
        }

        int i = 0;
        for (i = 0; i < 32; i++)
        {
            if (year_bin_str[i] == '1')
                break;
        }
        result += year_bin_str.substr(i);
        result += "-";

        i = 0;
        for (i = 0; i < 32; i++)
        {
            if (month_bin_str[i] == '1')
                break;
        }
        result += month_bin_str.substr(i);
        result += "-";

        i = 0;
        for (i = 0; i < 32; i++)
        {
            if (day_bin_str[i] == '1')
                break;
        }
        result += day_bin_str.substr(i);


        return result;
    }
};
