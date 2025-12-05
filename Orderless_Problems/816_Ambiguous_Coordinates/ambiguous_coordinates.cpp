/*
    ==============
    === MEDIUM ===
    ==============

    ===========================
    816) Ambiguous Coordinates
    ===========================

    ============
    Description:
    ============

    We had some 2-dimensional coordinates, like "(1, 3)" or "(2, 0.5)". Then,
    we removed all commas, decimal points, and spaces and ended up with the
    string s.

        For example, "(1, 3)" becomes s = "(13)" and "(2, 0.5)" becomes s =
        "(205)".

    Return a list of strings representing all possibilities for what our
    original coordinates could have been.

    Our original representation never had extraneous zeroes, so we never
    started with numbers like "00", "0.0", "0.00", "1.0", "001", "00.01", or
    any other number that can be represented with fewer digits. Also, a decimal
    point within a number never occurs without at least one digit occurring
    before it, so we never started with numbers like ".1".

    The final answer list can be returned in any order. All coordinates in the
    final answer have exactly one space between them (occurring after the
    comma.)

    ========================================================
    FUNCTION: vector<string> ambiguousCoordinates(string s);
    ========================================================

    ==========================================================================
    ================================ EXAMPLES ================================
    ==========================================================================

    --- Example 1 ---
    Input: s = "(123)"
    Output: ["(1, 2.3)","(1, 23)","(1.2, 3)","(12, 3)"]

    --- Example 2 ---
    Input: s = "(0123)"
    Output: ["(0, 1.23)","(0, 12.3)","(0, 123)","(0.1, 2.3)","(0.1, 23)","(0.12, 3)"]
    Explanation: 0.0, 00, 0001 or 00.01 are not allowed.

    --- Example 3 ---
    Input: s = "(00011)"
    Output: ["(0, 0.011)","(0.001, 1)"]


    *** Constraints ***
    4 <= s.length <= 12
    s[0] == '(' and s[s.length - 1] == ')'.
    The rest of s are digits.

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

/* Time  Beats: 82.73% */
/* Space Beats: 72.29% */

/* Time  Complexity: O(N^3) */
/* Space Complexity: O(N^2) */
class Solution {
public:
    vector<string> ambiguousCoordinates(string s)
    {
        const int N = s.size();
        vector<string> result;

        for (int i = 1; i < N - 2; i++)
        {
            vector<string> left_options  = generate_valid_numbers(s.substr(1, i));
            vector<string> right_options = generate_valid_numbers(s.substr(i + 1, N - 2 - i));

            for (const auto& a : left_options)
            {
                for (const auto& b : right_options)
                    result.push_back("(" + a + ", " + b + ")");
            }
        }

        return result;
    }

    vector<string> generate_valid_numbers(string s)
    {
        const int N = s.size();

        if (N == 0 || (N > 1 && s[0] == '0' && s[N - 1] == '0'))
            return {};

        if (N > 1 && s[0] == '0')
            return {"0." + s.substr(1)};

        if (N == 1 || s[N - 1] == '0')
            return {s};

        vector<string> result = {s};
        for (int i = 1; i < N; i++)
            result.push_back(s.substr(0, i) + '.' + s.substr(i));

        return result;
    }
};
