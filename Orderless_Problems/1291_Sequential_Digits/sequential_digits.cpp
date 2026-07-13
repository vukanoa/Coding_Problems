/*
    ==============
    === MEDIUM ===
    ==============

    ===========================
    1291) Sequential Digits
    ===========================

    ============
    Description:
    ============

    An integer has sequential digits if and only if each digit in the number is
    one more than the previous digit.

    Return a sorted list of all the integers in the range [low, high] inclusive
    that have sequential digits.

    ==========================================================
    FUNCTION: vector<int> sequentialDigits(int low, int high);
    ==========================================================

    ==========================================================================
    ================================ EXAMPLES ================================
    ==========================================================================

    --- Example 1 ---
    Input: low = 100, high = 300
    Output: [123,234]

    --- Example 2 ---
    Input: low = 1000, high = 13000
    Output: [1234,2345,3456,4567,5678,6789,12345]


    *** Constraints ***
    10 <= low <= high <= 10^9

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


/* Time  Beats: 100.00% */
/* Space Beats:  76.91% */

/* Time  Complexity: O(1) */
/* Space Complexity: O(1) */
class Solution {
public:
    vector<int> sequentialDigits(int low, int high)
    {
        vector<int> result;
        const int min_DIGITS = to_string(low).size();
        const int MAX_DIGITS = to_string(high).size();

        string str_digits = "0123456789";
        const int DIGITS  = str_digits.size();


        // Start from 2 because low >= 10, which consist of 2 digits.
        for (int num_digits = min_DIGITS; num_digits <= MAX_DIGITS; num_digits++)
        {
            /*
                Last valid starting index for a sequence of length num_digits
                is (DIGITS - num_digits).
                
                start_idx <==> start_digit
                
                We CANNOT start a number with a '0' digit, that's why
                start_idx begins at 1.
            */
            for (int start_idx = 1; start_idx <= DIGITS - num_digits; start_idx++)
            {
                string sequential_digits = str_digits.substr(start_idx, num_digits);

                int number = stoi(sequential_digits);

                if (low <= number && number <= high)
                    result.push_back(number);
            }
        }

        return result;
    }
};
