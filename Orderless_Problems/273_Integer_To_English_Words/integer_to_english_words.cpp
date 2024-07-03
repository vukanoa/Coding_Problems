#include <iostream>

/*
    ============
    === HARD ===
    ============

    =============================
    273) Integer To English Words
    =============================

    ============
    Description:
    ============

    Convert a non-negative integer num to its English words representation.

    ========================================
    FUNCTION: string numberToWords(int num);
    ========================================

    ==========================================================================
    ================================ EXAMPLES ================================
    ==========================================================================

    --- Example 1 ---
    Input: num = 123
    Output: "One Hundred Twenty Three"

    --- Example 2 ---
    Input: num = 12345
    Output: "Twelve Thousand Three Hundred Forty Five"

    --- Example 3 ---
    Input: num = 1234567
    Output: "One Million Two Hundred Thirty Four Thousand Five Hundred Sixty
            Seven"


    *** Constraints ***
    0 <= num <= 2^31 - 1


*/

/*
    ------------
    --- IDEA ---
    ------------

    Intuitive, self-explanatory.

*/

/* Time  Beats: 64.99% */
/* Space Beats: 74.49% */

/* Time  Complexity: O(n) */
/* Space Complexity: O(n) */
class Solution {
public:
    // Globally declare arrays
    std::string ones[20] = {"", " One", " Two", " Three", " Four", " Five", " Six", " Seven", " Eight", " Nine", " Ten", " Eleven", " Twelve", " Thirteen", " Fourteen", " Fifteen", " Sixteen", " Seventeen", " Eighteen", " Nineteen"};
    std::string tens[10] = {"", " Ten", " Twenty", " Thirty", " Forty", " Fifty", " Sixty", " Seventy", " Eighty", " Ninety"};
    std::string thousands[4] = {"", " Thousand", " Million", " Billion"};

    std::string numberToWords(int num)
    {
        // edge case
        if (num == 0) 
            return "Zero";
        return helper(num).substr(1);
    }

private:
    // Helper function
    std::string helper(int n)
    {
        if (n < 20) 
            return ones[n];
        if (n < 100) 
            return tens[n / 10] + helper(n % 10);
        if (n < 1000) 
            return helper(n / 100) + " Hundred" + helper(n % 100);
        for (int i = 3; i >= 0; i--) {
            if (n >= pow(1000, i)) {
                return helper(n / pow(1000, i)) + thousands[i] + helper(n % (int)pow(1000, i));
            }
        }

        return "";
    }
};
