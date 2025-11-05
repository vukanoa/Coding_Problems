/*
    ============
    === EASY ===
    ============

    ===============================
    2409) Count Days Spent Together
    ===============================

    ============
    Description:
    ============

    Alice and Bob are traveling to Rome for separate business meetings.

    You are given 4 strings arriveAlice, leaveAlice, arriveBob, and leaveBob.
    Alice will be in the city from the dates arriveAlice to leaveAlice
    (inclusive), while Bob will be in the city from the dates arriveBob to
    leaveBob (inclusive). Each will be a 5-character string in the format
    "MM-DD", corresponding to the month and day of the date.

    Return the total number of days that Alice and Bob are in Rome together.

    You can assume that all dates occur in the same calendar year, which is not
    a leap year. Note that the number of days per month can be represented as:
    [31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31].

    ==========================================================================================================
    FUNCTION: int countDaysTogether(string arriveAlice, string leaveAlice, string arriveBob, string leaveBob);
    ==========================================================================================================

    ==========================================================================
    ================================ EXAMPLES ================================
    ==========================================================================

    --- Example 1 ---
    Input: arriveAlice = "08-15", leaveAlice = "08-18", arriveBob = "08-16",
           leaveBob = "08-19"
    Output: 3
    Explanation: Alice will be in Rome from August 15 to August 18. Bob will be
                 in Rome from August 16 to August 19. They are both in Rome
                 together on August 16th, 17th, and 18th, so the answer is 3.

    --- Example 2 ---
    Input: arriveAlice = "10-01", leaveAlice = "10-31", arriveBob = "11-01",
           leaveBob = "12-31"
    Output: 0
    Explanation: There is no day when Alice and Bob are in Rome together, so we
                 return 0.


    *** Constraints ***
    All dates are provided in the format "MM-DD".
    Alice and Bob's arrival dates are earlier than or equal to their leaving
    dates.
    The given dates are valid dates of a non-leap year.

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
/* Space Beats:  28.17% */

/* Time  Complexity: O(N) */
/* Space Complexity: O(N) */
class Solution {
private:
    int month[13] = {0, 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};

public:
    int countDaysTogether(string arriveAlice, string leaveAlice, string arriveBob, string leaveBob)
    {
        int days_arrive_alice = convert_to_days(arriveAlice);
        int days_arrive_bob   = convert_to_days(arriveBob);
        int days_leave_alice  = convert_to_days(leaveAlice);
        int days_leave_bob    = convert_to_days(leaveBob);

        int arrive = max(days_arrive_alice, days_arrive_bob);
        int leave  = min(days_leave_alice,  days_leave_bob);

        if (arrive > leave)
            return 0;

        return leave - arrive + 1;
    }

private:
    int convert_to_days(string &s)
    {
        string str_month;
        string str_day;

        str_month += s[0];
        str_month += s[1];

        str_day += s[3];
        str_day += s[4];

        int count = 0;
        int int_month = stoi(str_month);
        int int_day   = stoi(str_day);

        for (int i = 0; i < int_month; i++)
            count += month[i];

        count = count + int_day;

        return count;
    }
};
