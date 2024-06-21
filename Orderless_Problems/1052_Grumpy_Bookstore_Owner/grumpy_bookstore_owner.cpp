#include <iostream>
#include <vector>

/*
    ==============
    === MEDIUM ===
    ==============

    ============================
    1052) Grumpy Bookstore Owner
    ============================

    ============
    Description:
    ============

    There is a bookstore owner that has a store open for n minutes. Every
    minute, some number of customers enter the store. You are given an integer
    array customers of length n where customers[i] is the number of the
    customer that enters the store at the start of the ith minute and all those
    customers leave after the end of that minute.

    On some minutes, the bookstore owner is grumpy. You are given a binary
    array grumpy where grumpy[i] is 1 if the bookstore owner is grumpy during
    the ith minute, and is 0 otherwise.

    When the bookstore owner is grumpy, the customers of that minute are not
    satisfied, otherwise, they are satisfied.

    The bookstore owner knows a secret technique to keep themselves not grumpy
    for minutes consecutive minutes, but can only use it once.

    Return the maximum number of customers that can be satisfied throughout the
    day.

    =====================================================================================
    FUNCTION: int maxSatisfied(vector<int>& customers, vector<int>& grumpy, int minutes); 
    =====================================================================================

    ==========================================================================
    ================================ EXAMPLES ================================
    ==========================================================================

    --- Example 1 ---
    Input: customers = [1,0,1,2,1,1,7,5],
           grumpy    = [0,1,0,1,0,1,0,1],
           minutes   = 3

    Output: 16

    Explanation: The bookstore owner keeps themselves not grumpy for the last 3
    minutes.  The maximum number of customers that can be satisfied = 1 + 1 + 1
    + 1 + 7 + 5 = 16


    --- Example 2 ---
    Input: customers = [1], grumpy = [0], minutes = 1
    Output: 1



    *** Constraints ***
    n == customers.length == grumpy.length
    1 <= minutes <= n <= 2 * 10^4
    0 <= customers[i] <= 1000
    grumpy[i] is either 0 or 1.

*/

/*
    ------------
    --- IDEA ---
    ------------

    TODO

*/

/* Time  Beats: 55.38% */
/* Space Beats: 82.34% */

/* Time  Complexity: O(n) */
/* Space Complexity: O(1) */
class Solution {
public:
    int maxSatisfied(std::vector<int>& cust, std::vector<int>& grumpy, int minutes)
    {
        int result = 0;
        int curr = 0;

        for (int i = 0; i < cust.size(); i++)
        {
            if (grumpy[i] == 0)
                result += cust[i];
        }
        
        for (int i = 0; i < minutes; i++)
        {
            if (grumpy[i])
                curr += cust[i];
        }

        int addi = curr;
        for(int i = minutes; i < cust.size(); i++)
        {
            if(grumpy[i - minutes])
                curr -= cust[i - minutes];

            if(grumpy[i])
                curr += cust[i];

            addi = std::max(addi, curr);
        }

        return result + addi;
    }
};
