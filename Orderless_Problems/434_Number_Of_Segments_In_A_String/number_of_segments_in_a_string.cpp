/*
    ============
    === EASY ===
    ============

    ===================================
    434) Number Of Segments In a String
    ===================================

    ============
    Description:
    ============

    Given a string s, return the number of segments in the string.

    A segment is defined to be a contiguous sequence of non-space characters.

    ======================================
    FUNCTION: int countSegments(string s);
    ======================================

    ==========================================================================
    ================================ EXAMPLES ================================
    ==========================================================================

    --- Example 1 ---
    Input: s = "Hello, my name is John"
    Output: 5
    Explanation: The five segments are ["Hello,", "my", "name", "is", "John"]

    --- Example 2 ---
    Input: s = "Hello"
    Output: 1

    *** Constraints ***
    0 <= s.length <= 300
    s consists of lowercase and uppercase English letters, digits, or one of
    the following characters "!@#$%^&*()_+-=',.:".
    The only space character in s is ' '.

*/

#include <string>
using namespace std;

/*
    ------------
    --- IDEA ---
    ------------

    Start i from 0 and iterate until you either hit a ' ' character or unil you
    hit the end of a stirng.

    Either way, if you've iterated at least once through non-space character,
    then boolean variable named "segment" is set to true.

    If segment is true, then incnrement "result" by one.

    Either way, after that, iterate through the string unless you hit either
    a non-space character or end of the string. (So now it's in reverse than
    in the previos "while loop").

    Once the 'i' variable gets to be out of bounds for string s, we stop and
    return "result".

*/

/* Time  Beats: 100.00% */
/* Space Beats:  94.10% */

/* Time  Complexity: O(n) */
/* Space Complexity: O(1) */
class Solution {
public:
    int countSegments(string s)
    {
        const int N = s.length();
        int result = 0;

        int i = 0;
        while (i < N)
        {
            bool segment = false;

            while (i < N && s[i] != ' ')
            {
                i++;
                segment = true;
            }

            if (segment)
                result++;

            while (i < N && s[i] == ' ')
                i++;
        }

        return result;
    }
};




/*
    ------------
    --- IDEA ---
    ------------

    This one also solves it in-place, but it's MUCH more elegant.
    It's beneficial to see both solution and realize why and how
    to obtain the more elegant one.

*/
/* Time  Beats: 100.00% */
/* Space Beats:  81.12% */

/* Time  Complexity: O(n) */
/* Space Complexity: O(1) */
class Solution {
public:
    int countSegments(string s)
    {
        const int N = s.length();
        int segment_count = 0;

        for (int i = 0; i < N; i++)
        {
            if ((i == 0 || s[i - 1] == ' ') && s[i] != ' ')
                segment_count++;
        }

        return segment_count;
    }
};
