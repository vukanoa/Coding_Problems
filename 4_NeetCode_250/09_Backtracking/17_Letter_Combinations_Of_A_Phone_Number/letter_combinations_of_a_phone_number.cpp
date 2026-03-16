/*
    ==============
    === MEDIUM ===
    ==============

    =========================================
    17) Letter Combinations of a Phone Number
    =========================================

    ============
    Description:
    ============

    Given a string containing digits from 2-9 inclusive, return all possible
    letter combinations that the number could represent. Return the answer
    in any order.

    =====
    Node: Number 1 does not map to any letters.
    =====

    ===========================================================
    FUNCTION: vector<string> letterCombinations(string digits);
    ===========================================================

    ==========================================================================
    ================================ EXAMPLES ================================
    ==========================================================================

    --- Example 1 ---
    Input:  digits = "23"
    Output: ["ad", "ae", "af", "bd", "be", "bf", "cd", "ce", "cf"]

    --- Example 2 ---
    Input:  digits = ""
    Output: []

    --- Example 3 ---
    Input:  digits = "2"
    Output: ["a", "b", "c"]

    *** Constraints ***
    0 <= digits.length <= 4
    digits[i] is a digit in the range ['2', '9'].

*/

#include <string>
#include <vector>
using namespace std;

/*
    ------------
    --- IDEA ---
    ------------

    Self-explanatory. Basic Backtracking.

*/

/* Time  Beats: 100.00% */
/* Space Beats:  98.97% */

/* Time  Complexity: O(N * 4^N) */
/* Space Complexity: O(N)       */
class Solution {
public:
    vector<string> letterCombinations(string digits)
    {
        const int N = digits.size();
        vector<string> result;

        const string buttons[10] = {"", "", "abc", "def", "ghi", "jkl", "mno", "pqrs", "tuv", "wxyz"};

        string combination;
        backtracking(0, combination, digits, buttons, result);

        return result;
    }

private:
    void backtracking(int digit_idx, string& combination, string& digits, const string buttons[10], vector<string>& result)
    {
        if (combination.size() == digits.size())
        {
            result.push_back(combination);
            return;
        }

        int curr_digit = digits[digit_idx] - '0';

        for (const char& letter : buttons[curr_digit])
        {
            combination += letter;
            backtracking(digit_idx + 1, combination, digits, buttons, result);
            combination.pop_back();
        }
    }
};




/*
    ------------
    --- IDEA ---
    ------------

    TODO

*/

/* Time  Beats: 15.49% */
/* Space Beats: 58.60% */

/* Time  Complexity: O(N * 4^N) */
/* Space Complexity: O(N)       */
class Solution_Iterative {
public:
    vector<string> letterCombinations(string digits)
    {
        if (digits.empty())
            return {};

        vector<string> result = {""}; // We'll overwrite this, but it must be set like this initially

        const string buttons[10] = {"", "", "abc", "def", "ghi", "jkl", "mno", "qprs", "tuv", "wxyz"};

        for (const char& digit_chr : digits)
        {
            vector<string> combinations;
            for (const string& curr_incomplete_combination : result)
            {
                for (const char& letter : buttons[digit_chr - '0'])
                    combinations.push_back(curr_incomplete_combination + letter);
            }

            result = combinations;
        }

        return result;
    }
};
