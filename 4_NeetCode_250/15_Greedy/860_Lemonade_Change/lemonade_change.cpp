/*
    ============
    === EASY ===
    ============

    ===========================
    860) Lemonade Change
    ===========================

    ============
    Description:
    ============

    At a lemonade stand, each lemonade costs $5. Customers are standing in a
    queue to buy from you and order one at a time (in the order specified by
    bills). Each customer will only buy one lemonade and pay with either a $5,
    $10, or $20 bill. You must provide the correct change to each customer so
    that the net transaction is that the customer pays $5.

    Note that you do not have any change in hand at first.

    Given an integer array bills where bills[i] is the bill the ith customer
    pays, return true if you can provide every customer with the correct
    change, or false otherwise.

    ==================================================
    FUNCTION: bool lemonadeChange(vector<int>& bills);
    ==================================================

    ==========================================================================
    ================================ EXAMPLES ================================
    ==========================================================================

    --- Example 1 ---
    Input: bills = [5,5,5,10,20]
    Output: true
    Explanation:
    From the first 3 customers, we collect three $5 bills in order.
    From the fourth customer, we collect a $10 bill and give back a $5.
    From the fifth customer, we give a $10 bill and a $5 bill.
    Since all customers got correct change, we output true.

    --- Example 2 ---
    Input: bills = [5,5,10,10,20]
    Output: false
    Explanation:
    From the first two customers in order, we collect two $5 bills.
    For the next two customers in order, we collect a $10 bill and give back a
    $5 bill.  For the last customer, we can not give the change of $15 back
    because we only have two $10 bills.  Since not every customer received the
    correct change, the answer is false.


    *** Constraints ***
    1 <= bills.length <= 10^5
    bills[i] is either 5, 10, or 20.

*/

#include <vector>
using namespace std;

/*
    ------------
    --- IDEA ---
    ------------

    No need for an explanation. I don't think there is a person on this planet
    who can't solve this problem if he knows about the most basic programming
    things.

*/

/* Time  Beats: 100.00% */
/* Space Beats:  43.55% */

/* Time  Complexity: O(N) */
/* Space Complexity: O(1) */
class Solution {
public:
    bool lemonadeChange(vector<int>& bills)
    {
        const int N = bills.size();

        int fives = 0;
        int tens  = 0;

        for (const int& dollar_bill : bills)
        {
            switch (dollar_bill)
            {
                case 5:
                    fives++;
                    break;

                case 10:
                    if (fives == 0) // Unable to give him the change
                        return false;

                    tens++;
                    fives--;

                    break;

                case 20:
                    if (tens >= 1 && fives >= 1)
                    {
                        --tens;  // 10
                        --fives; // 5
                    }
                    else if (fives >= 3)
                    {
                        --fives; // 5
                        --fives; // 5
                        --fives; // 5
                    }
                    else
                    {
                        return false;
                    }

                    break;
            }
        }

        return true;
    }
};
