#include <iostream>

/*
    ==============
    === MEDIUM ===
    ==============

    ==================================
    949) Largest Time For Given Digits
    ==================================

    ============
    Description:
    ============

    Given an array arr of 4 digits, find the latest 24-hour time that can be
    made using each digit exactly once.

    24-hour times are formatted as "HH:MM", where HH is between 00 and 23, and
    MM is between 00 and 59. The earliest 24-hour time is 00:00, and the latest
    is 23:59.

    Return the latest 24-hour time in "HH:MM" format. If no valid time can be
    made, return an empty string.

    =========================================================
    FUNCTION: string largestTimeFromDigits(vector<int>& arr);
    =========================================================

    ==========================================================================
    ================================ EXAMPLES ================================
    ==========================================================================

    --- Example 1 ---
    Input: arr = [1,2,3,4]
    Output: "23:41"
    Explanation: The valid 24-hour times are "12:34", "12:43", "13:24",
    "13:42", "14:23", "14:32", "21:34", "21:43", "23:14", and "23:41". Of these
    times, "23:41" is the latest.

    --- Example 2 ---
    Input: arr = [5,5,5,5]
    Output: ""
    Explanation: There are no valid 24-hour times as "55:55" is not valid.

    *** Constraints ***
    arr.length == 4
    0 <= arr[i] <= 9

*/

/*
    ------------
    --- IDEA ---
    ------------

    TODO

*/

/* Time  Beats: 100% */
/* Space Beats: 77.16% */

/* Time  Complexity: O(1) */
/* Space Complexity: O(1) */
class Solution {
public:
    std::string largestTimeFromDigits(std::vector<int>& arr)
    {
        std::sort(arr.begin(), arr.end(), greater<int>());

        do{
            int hours   = arr[0] * 10 + arr[1];
            int minutes = arr[2] * 10 + arr[3];

            if(hours < 24 && minutes < 60)
            {
                string time = "";
                if(hours<10)
                    time += "0";

                time += std::to_string(hours);
                time += ":";

                if(minutes<10)
                    time += "0";

                time += to_string(minutes);
                return time;
            }

        } while( prev_permutation(arr.begin(), arr.end()) );

        return "";
    }
};
