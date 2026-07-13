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




/*
    ------------
    --- IDEA ---
    ------------

    Since the Constraints are:

        10 <= low <= high <= 10^9

    We can know for a FACT that there are exactly 46 sequential numbers.

    How do we know that?

    We perform s simple BFS on the number of digits.
    When you look at the picture, it'll become painfully obvious:

    1            2            3            4            5            6            7            8            9  <---- 1 digit sequantial numbers
    12           23           34           45           56           67           78           89              <---- 2 digit sequantial numbers
    123          234          345          456          567          678          789                          <---- 3 digit sequantial numbers
    1234         2345         3456         4567         5678         6789                                      <---- 4 digit sequantial numbers
    12345        23456        34567        45678        56789                                                  <---- 5 digit sequantial numbers
    123456       234567       345678       456789                                                              <---- 6 digit sequantial numbers
    1234567      2345678      3456789                                                                          <---- 7 digit sequantial numbers
    12345678     23456789                                                                                      <---- 8 digit sequantial numbers
    123456789                                                                                                  <---- 9 digit sequantial number  (the ONLY one)


    We begin by exactly 9 of the "9 digit" numbers and the we simply add 1 to
    the last digit of each of those numbers--except the one that ends in digit
    9--and we form a new numbers with ONE digit MORE than the previous "level".

    That's why this can be thought of as a BFS.

*/

/* Time  Beats: 100.00% */
/* Space Beats:  97.69% */

/* Time  Complexity: O(1) */
/* Space Complexity: O(1) */
class Solution_BFS {
private:
    int sequential_numbers[45];
    int sequential_number_count = 0;

public:
    void generate_ALL_sequential_numbers()
    {
        sequential_number_count = 0;

        for (int digit = 1; digit <= 9; digit++)
            sequential_numbers[sequential_number_count++] = digit;

        for (int idx = 0; idx < sequential_number_count; idx++)
        {
            int last_digit = sequential_numbers[idx] % 10;

            if (last_digit < 9)
            {
                sequential_numbers[sequential_number_count] = sequential_numbers[idx] * 10 + (last_digit + 1);

                // Increment
                sequential_number_count++;
            }
        }
    }

    vector<int> sequentialDigits(int low, int high)
    {
        generate_ALL_sequential_numbers();

        vector<int> result;
        for (const auto& sequential_number : sequential_numbers)
        {
            if (low <= sequential_number && sequential_number <= high)
                result.push_back(sequential_number);
        }

        return result;
    }
};
