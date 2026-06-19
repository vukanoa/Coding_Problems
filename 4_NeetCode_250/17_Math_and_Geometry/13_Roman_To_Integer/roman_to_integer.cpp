/*
    ============
    === EASY ===
    ============

    ===========================
    13) Roman to Integer
    ===========================

    ============
    Description:
    ============

    Roman numerals are represented by seven different symbols:
    I, V, X, L, C, D and M.

    Symbol    Value
    I         1
    V         5
    X         10
    L         50
    C         100
    D         500
    M         1000

    ===================================
    FUNCTION: int romanToInt(string s);
    ===================================

    For example, 2 is written as II in Roman numeral, just two ones added
    together. 12 is written as XII, which is simply X + II. The number 27 is
    written as XXVII, which is XX + V + II.

    Roman numerals are usually written largest to smallest from left to right.
    However, the numeral for four is not IIII. Instead, the number four is
    written as IV. Because the one is before the five we subtract it making
    four. The same principle applies to the number nine, which is written as
    IX. There are six instances where subtraction is used:
        1. 'I' can be placed before 'V' (5) and 'X'(10) to make 4 and 9.
        2. 'X' can be placed before 'L' (50) and 'C'(100) to make 40 and 90.
        3. 'C' can be placed before 'D' (500) and 'M'(1000) ot make 400 and 900.

    Given a roman numeral, convert it to an integer.

    ==========================================================================
    ================================ EXAMPLES ================================
    ==========================================================================

    --- Example 1 ---
    Input:  s = "III"
    Output: 3

    --- Example 2 ---
    Input:  s = "LVIII"
    Output 58

    --- Example 3 ---
    Input:  s = "MCMXCIV"
    Output: 1994

    *** Constraints ***
    1 <= s.length <= 15
    s contains only the characters ('I', 'V', 'X', 'L', 'C', 'D', 'M').
    It is guaranteed that s is a valid roman numeral in the range [1, 3999]

*/

#include <string>
#include <unordered_map>
using namespace std;



/*
    ------------
    --- IDEA ---
    ------------

    We have an unordered Hash Map [char, int] corresponding to Roman characters
    and its values.

    We iterate through a given Roman number from left to right.
    Consider Example:
        MCIV
        ^

    If we find that the current one is greater than its right Roman character
    then we just add its value to our variable "number" which we return as a
    final result.

    However, if the current one is less than its right Roman character(less in
    values) then we subtract current Roman character's value from our variable
    "number".

    Why?
    If we are at index 2(at character 'I' for the above example) then if its
    right Roman character is greater in value than the current one('I') then
    that means that this character represents "decreasing part" of the very
    next Roman character. Thus we subtract this one and add the next one.

*/

/* Time  Beats: 74.40% */
/* Space Beats: 32.17% */

/* Time  Complexity: O(N) */
/* Space Complexity: O(N) */
class Solution {
public:
    int romanToInt(string s)
    {
        const int N = s.size();
        int number = 0;

        unordered_map<char, int> value_of_roman = {
            { 'I', 1 },
            { 'V', 5 },
            { 'X', 10 },
            { 'L', 50 },
            { 'C', 100 },
            { 'D', 500 },
            { 'M', 1000 }
        };


        for (int i = 0; i < N; i++)
        {
            int curr_val = value_of_roman[s[i]];
            int next_val = (i+1 < N) ? value_of_roman[s[i+1]] : 0;

            if (curr_val < next_val)
                number -= curr_val;
            else
                number += curr_val;
        }

        return number;
    }
};




/*
    ------------
    --- IDEA ---
    ------------

    Here we literally cover each of the "edge cases" manually. This makes the
    Solution much much messier and less elegant, however we do NOT use any
    additional space.

    Though, you could argue that in the above Solution we haven't used any
    additional space either because the size of the HashMap is ALWAYS going to
    be 7, thus O(7) --> O(1).

*/

/* Time  Beats: 100.00% */
/* Space Beats:  94.12% */

/* Time  Complexity: O(N) */
/* Space Complexity: O(1) */
class Solution_Manual_Parsing {
public:
    int romanToInt(string s)
    {
        const int N = s.size();
        int result = 0;

        int i = 0;
        while (i < N)
        {
            switch (s[i])
            {
                case 'I':
                    if (i+1 == N || (s[i+1] != 'V' && s[i+1] != 'X'))
                    {
                        result += 1;
                        i++;
                    }
                    else if (s[i+1] == 'V')
                    {
                        result += 4;
                        i += 2;
                    }
                    else if (s[i+1] == 'X')
                    {
                        result += 9;
                        i += 2;
                    }
                    break;

                case 'V':
                    result += 5;
                    i++;
                    break;

                case 'X':
                    if (i+1 == N || (s[i+1] != 'L' && s[i+1] != 'C'))
                    {
                        result += 10;
                        i++;
                    }
                    else if (s[i+1] == 'L')
                    {
                        result += 40;
                        i += 2;
                    }
                    else if (s[i+1] == 'C')
                    {
                        result += 90;
                        i += 2;
                    }
                    break;

                case 'L':
                    result += 50;
                    i++;

                    break;

                case 'C':
                    if (i+1 == N || (s[i+1] != 'D' && s[i+1] != 'M'))
                    {
                        result += 100;
                        i++;
                    }
                    else if (s[i+1] == 'D')
                    {
                        result += 400;
                        i += 2;
                    }
                    else if (s[i+1] == 'M')
                    {
                        result += 900;
                        i += 2;
                    }

                    break;

                case 'D':
                    result += 500;
                    i++;
                    break;

                case 'M':
                    result += 1000;
                    i++;
                    break;
            }
        }

        return result;
    }
};
