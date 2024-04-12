#include <iostream>
#include <unordered_map>

/*
    ==============
    === MEDIUM ===
    ==============

    ===========================
    12) Integer to Roman
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

    For example, 2 is written as II in Roman numeral, just two one's added
    together. 12 is written as XII, which is simply X + II. The number 27
    is written as XXVII, which is XX + V + II.

    Roman numerals are usually written largest to smallest from left to right.
    However, the numeral for four is not IIII. Instead, the number four is
    written as IV. Because the one is before the five we subtract it making
    four. The same principle applies to the number nine, which is written as
    IX. There are six instances where subtraction is used:
        1. 'I' can be placed before V(5) and X(10) to make 4 and 9.
        2. 'X' can be placed before L(50) and C(100) to make 40 and 90.
        3. 'C' can be placed before D(500) and M(1000) to make 400 and 900.

    Given an integer, convert it to a roman numeral.

    ====================================
    FUNCTION: string intToRoman(int num)
    ====================================

    ==========================================================================
    ================================ EXAMPLES ================================
    ==========================================================================

    --- Example 1 ---
    Input:  num = 3
    Output: "III"

    --- Example 2 ---
    Input:  num = 58
    Output: "LVIII"

    --- Example 3 ---
    Input:  num = 1994
    Output: "MCMXCIV"

    *** Constraints ***
    1 <= num <= 3999
*/



/*
    ------------
    --- IDEA ---
    ------------

    This is the most intuitive, but, somehow, not as efficient in the LeetCode.

*/

/* Time  Beats: 5,10% */
/* Space Beats: 5.16% */

/*
    Time  Complexity: O(n)
    Since 3999 is max value possible, the number of digits is negligible. It
    could also be considered O(1)

*/
/* Space Complexity: O(1) */
class Solution_Intuitive {
public:
    string intToRoman(int num)
    {
        std::unordered_map<int, std::string> umap;
        umap.insert({1, "I"});
        umap.insert({2, "II"});
        umap.insert({3, "III"});
        umap.insert({4, "IV"});
        umap.insert({5, "V"});
        umap.insert({6, "VI"});
        umap.insert({7, "VII"});
        umap.insert({8, "VIII"});
        umap.insert({9, "IX"});

        umap.insert({10, "X"});
        umap.insert({20, "XX"});
        umap.insert({30, "XXX"});
        umap.insert({40, "XL"});
        umap.insert({50, "L"});
        umap.insert({60, "LX"});
        umap.insert({70, "LXX"});
        umap.insert({80, "LXXX"});
        umap.insert({90, "XC"});

        umap.insert({100, "C"});
        umap.insert({200, "CC"});
        umap.insert({300, "CCC"});
        umap.insert({400, "CD"});
        umap.insert({500, "D"});
        umap.insert({600, "DC"});
        umap.insert({700, "DCC"});
        umap.insert({800, "DCCC"});
        umap.insert({900, "CM"});

        umap.insert({1000, "M"});
        umap.insert({2000, "MM"});
        umap.insert({3000, "MMM"});

        std::string result = "";
        int mul = 1;
        while (num > 0)
        {
            int digit = num % 10;
            num /= 10;

            result = umap[digit * mul] + result;
            mul *= 10;
        }

        return result;
    }
};



/*
    ------------
    --- IDEA ---
    ------------

    We have 13 different values in "values" array.

    While number is greater than 0 we are trying to find the very first value
    from this array that is less then the current value of num(since we are
    subtracting the "covered" part in each iteration).

    For example 58.
    We stop when x = 6(x is starting from 12). Why?

    Because x = 6 is 50 which is the largest roman letter we have in our
    number.
    Then we subtract 58 from this largest roman letter, which is 50 in this
    case, and we get 8.

    Now we repeat the process until we have "covered" the whole number, meaning
    num == 0

*/



/* Time  Beats: 100 */
/* Space Beats: 99.73% */
/*
    Time  Complexity: O(n)
    Since 3999 is max value possible, the number of digits is negligible. It
    could also be considered O(1)

*/
/* Space Complexity: O(1) */
class Solution{
public:
    std::string intToRoman(int num)
    {
        int values[13] = {1, 4, 5, 9, 10, 40, 50, 90, 100, 400, 500, 900, 1000};
        std::string romans[13] = {"I", "IV", "V", "IX", "X", "XL", "L", "XC", "C", "CD", "D", "CM", "M"};

        int x = 13 - 1;
        std::string roman_num = "";

        while (num > 0)
        {
            while (num < values[x])
                x--;

            roman_num += romans[x];
            num -= values[x];
        }

        return roman_num;
    }
};


int
main()
{
    Solution_Intuitive sol_intuitive;
    Solution           sol;

    // int num = 1994;
    // int num = 8;
    // int num = 9;
    // int num = 37;
    // int num = 1998;
    int num = 2004;

    std::cout << "\n\t========================";
    std::cout << "\n\t=== INTEGER TO ROMAN ===";
    std::cout << "\n\t========================\n";

    /* Write Input */
    std::cout << "\n\tInteger: " << num << "\n";

    /* Solution */
    // std::string roman = sol.intToRoman(num);
    std::string roman = sol.intToRoman(num);

    /* Write Output */
    std::cout << "\n\tRoman: " << roman << "\n\n";

    return 0;
}
