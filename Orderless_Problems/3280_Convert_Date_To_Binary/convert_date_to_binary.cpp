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
#include <bitset>
#include <sstream>
using namespace std;

/*
    ------------
    --- IDEA ---
    ------------

    Just a standard string to int, and vice-versa, manipulation.
    And an integer to binary_string conversion.

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

        // Convert int to binary_string
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




/*
    ------------
    --- IDEA ---
    ------------

    Another way of implementing it. This one uses bitsets and a few other C++
    features such as s.find('1').

*/

/* Time  Beats: 100.00% */
/* Space Beats:  80.97% */

/* Time  Complexity: O(n) */
/* Space Complexity: O(n) */
class Solution_2 {
public:
    string convertDateToBinary(string date)
    {
        size_t first_dash = date.find('-');
        size_t second_dash = date.find('-', first_dash + 1);

        int year = stoi(date.substr(0, first_dash));
        int month = stoi(date.substr(first_dash + 1, second_dash - first_dash - 1));
        int day = stoi(date.substr(second_dash + 1));

        string result = get_binary_string(bitset<32>(year));
        result += "-" + get_binary_string(bitset<32>(month));
        result += "-" + get_binary_string(bitset<32>(day));

        return result;
    }

private:
    // Function to convert a bitset to a binary string and remove leading zeros
    string get_binary_string(const bitset<32>& bits)
    {
        string s = bits.to_string();
        size_t idx_of_most_significant_set_bit = s.find('1');

        // If no '1' is found, the value is 0, so return "0".
        if (idx_of_most_significant_set_bit == string::npos)
            return "0";

        // Otherwise, return the substring starting from the first '1'.
        return s.substr(idx_of_most_significant_set_bit);
    }
};




/*
    ------------
    --- IDEA ---
    ------------

    This is yet another Implementation. It uses stringstream and GCC's feature
    __builtin_clz function.

    Also integer to binary_string is implemented slightly different. It is very
    handy to be familiar with all these ways to of string manipulation. They
    are all very important.

*/

/* Time  Beats: 100.00% */
/* Space Beats:  85.11% */

/* Time  Complexity: O(n) */
/* Space Complexity: O(n) */
class Solution_3 {
public:
    string convertDateToBinary(string& date)
    {
        stringstream ss(date);

        int year;
        int month;
        int day;

        char dash_eater;
        ss >> year >> dash_eater >> month >> dash_eater >> day;

        return to_binary(year) + "-" + to_binary(month) + "-" + to_binary(day);
    }

private:
    string to_binary(int x)
    {
        int bit = 31 - __builtin_clz(x);

        string result = "1";

        for (int i = bit-1; i >= 0; i--)
            result += (x & (1 << i)) ? '1' : '0';

        return result;
    }
};
