#include <iostream>
#include <string>
#include <algorithm>

/*
    ==============
    === MEDIUM ===
    ==============

    ===========================
    670) Maximum Swap
    ===========================

    ============
    Description:
    ============

    You are given an integer num. You can swap two digits at most once to get
    the maximum valued number.

    Return the maximum valued number you can get.

    ===================================
    FUNCTION: int maximumSwap(int num);
    ===================================

    ==========================================================================
    ================================ EXAMPLES ================================
    ==========================================================================

    --- Example 1 ---
    Input: num = 2736
    Output: 7236
    Explanation: Swap the number 2 and the number 7.


    --- Example 2 ---
    Input: num = 9973
    Output: 9973
    Explanation: No swap.


    *** Constraints ***
    0 <= num <= 10^8

*/

/*
    ------------
    --- IDEA ---
    ------------

    TODO

*/

/* Time  Beats: 100.00% */
/* Space Beats:  38.03% */

/* Time  Complexity: O(n) */
/* Space Complexity: O(n) */
class Solution {
public:
    int maximumSwap(int num)
    {
        std::string str_num = std::to_string(num);
        std::vector<int> last_index(10, -1);  // {digit: last index}

        for (int i = 0; i < str_num.length(); i++)
            last_index[str_num[i] - '0'] = i;

        for (int i = 0; i < str_num.length(); i++)
        {
            for (int digit = 9; digit > str_num[i] - '0'; digit--)
            {
                if (last_index[digit] > i)
                {
                    std::swap(str_num[i], str_num[last_index[digit]]);
                    return std::stoi(str_num);
                }
            }
        }

        return num;
    }
};




/*
    ------------
    --- IDEA ---
    ------------

    Iterate backwards through the number's digits, marking a swap candidate
    when encountering a larger digit. Commit to the swap in subsequent
    iterations only if it results in an improvement

*/

/* Time  Beats: 100.00% */
/* Space Beats:  72.27% */

/* Time  Complexity: O(n) */
/* Space Complexity: O(n) */
class Solution_2 {
public:
    int maximumSwap(int num)
    {
        std::string str_num = std::to_string(num);
        const int n = str_num.length();

        int max_position = str_num.length() - 1;
        int best_src  = -1;
        int best_dest = -1;

        for (int i = n-1; i >= 0; i--)
        {
            if (str_num[i] > str_num[max_position])
                max_position = i;
            else if (str_num[i] < str_num[max_position])
            {
                best_src = max_position;
                best_dest = i;
            }
        }

        if (best_src != -1)
            std::swap(str_num[best_src], str_num[best_dest]);

        return std::stoi(str_num);
    }
};
