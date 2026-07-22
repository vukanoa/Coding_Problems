/*
    ==============
    === MEDIUM ===
    ==============

    ====================================
    1344) Angle Between Hands of a Clock
    ====================================

    ============
    Description:
    ============

    Given two numbers, hour and minutes, return the smaller angle (in degrees)
    formed between the hour and the minute hand.

    Answers within 10-5 of the actual value will be accepted as correct.

    ===================================================
    FUNCTION: double angleClock(int hour, int minutes);
    ===================================================

    ==========================================================================
    ================================ EXAMPLES ================================
    ==========================================================================

    --- Example 1 ---
    Input: hour = 12, minutes = 30
    Output: 165

    --- Example 2 ---
    Input: hour = 3, minutes = 30
    Output: 75

    --- Example 3 ---
    Input: hour = 3, minutes = 15
    Output: 7.5


    *** Constraints ***
    1 <= hour <= 12
    0 <= minutes <= 59

*/

#include <algorithm>
#include <cfloat>
using namespace std;

/*
    ------------
    --- IDEA ---
    ------------

    TODO

*/

/* Time  Beats: 100.00% */
/* Space Beats:  74.16% */

/* Time  Complexity: O(1) */
/* Space Complexity: O(1) */
class Solution {
public:
    double angleClock(int hour, int minutes)
    {
        hour = hour == 12 ? 0 : hour;

        double degrees_minute = 360.0 / (60.0 / minutes); 
        double degrees_hour   = 30.0 * hour + (30.0 / (60.0 / minutes));

        double one   = (degrees_minute - degrees_hour);
        double two   = (degrees_hour   - degrees_minute); 
        double three = 360 - one;
        double four  = 360 - two;

        return min( {one   < 0 ? DBL_MAX : one,
                     two   < 0 ? DBL_MAX : two,
                     three < 0 ? DBL_MAX : three,
                     four  < 0 ? DBL_MAX : four} );
    }
};
