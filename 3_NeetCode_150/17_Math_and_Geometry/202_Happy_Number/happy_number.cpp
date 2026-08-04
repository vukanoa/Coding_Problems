/*
    ============
    === EASY ===
    ============

    ===========================
    202) Happy Number
    ===========================

    ============
    Description:
    ============

    Write an algorithm to determine if a number n is happy.

    A happy number is a number defined by the following process:

    - Starting with any positive integer, replace the number by the sum of the
      squares of its digits.

    - Repeat the process until the number equals 1 (where it will stay), or it
      loops endlessly in a cycle which does not include 1.

    - Those numbers for which this process ends in 1 are happy.

    Return true if n is a happy number, and false if not.

    ==============================
    FUNCTION: bool isHappy(int n);
    ==============================

    ==========================================================================
    ================================ EXAMPLES ================================
    ==========================================================================

    --- Example 1 ---
    Input: n = 19
    Output: true
    Explanation:
    1^2 + 9^2 = 82
    8^2 + 2^2 = 68
    6^2 + 8^2 = 100

    1^2 + 0^2 + 0^2 = 1


    --- Example 2 ---
    Input: n = 2
    Output: false


    *** Constraints ***
    1 <= n <= 2^31 - 1

*/

#include <unordered_set>
using namespace std;

/*
    ------------
    --- IDEA ---
    ------------

    Intuitive. Self-Explanatory.
    
*/

/* Time  Beats: 100.00% */
/* Space Beats:  52.78% */

/* Time  Complexity: O((logN)^2) */
/* Space Complexity: O(logN)     */
class Solution {
public:
    bool isHappy(int n)
    {
        unordered_set<int> uset;

        while (n != 1)
        {
            if (uset.find(n) != uset.end()) // Already used it
                return false;

            uset.insert(n);

            int num = n;
            n = 0;
            while (num > 0)
            {
                int digit = num % 10;

                n += digit * digit;
                num /= 10;
            }
        }

        return true;
    }
};




/*
    ------------
    --- IDEA ---
    ------------

    We can treat the digits as linked list nodes and perform a standard
    "Floyd's Algorithm" aka "Tortoise and Hare".

*/

/* Time Complexity:  O(log N) */
/* Space Complexity: O(1)     */
class Solution_Floyd__Tortoise_and_Hare {
public:
    bool isHappy(int n)
    {
        int slow = n;
        int fast = n;

        do
        {
            slow = find_next(slow);
            fast = find_next(find_next(fast));
        }
        while (slow != fast);

        return slow == 1;
    }

private:
    int find_next(int n)
    {
        int result = 0;

        while (n != 0)
        {
            int digit = n % 10;

            result += digit * digit;
            n /= 10;
        }

        return result;
    }
};




/*
    ------------
    --- IDEA ---
    ------------

    Brent's Cycle Detection.

*/

/* Time  Beats: 100.00% */
/* Space Beats:  68.46% */

/* Time  Complexity: O(log N) */
/* Space Complexity: O(1)     */
class Solution_Brents_Cycle_Detection {
public:
    bool isHappy(int n)
    {
        int slow = n;
        int fast = find_next(n);

        int power = 1;
        int steps_in_current_block = 1;

        while (slow != fast)
        {
            if (power == steps_in_current_block)
            {
                slow = fast;
                power *= 2;
                steps_in_current_block = 0;
            }

            steps_in_current_block++;
            fast = find_next(fast);
        }

        return fast == 1;
    }

private:
    int find_next(int n)
    {
        int output = 0;
        while (n != 0)
        {
            int digit = n % 10;

            output += digit * digit;
            n /= 10;
        }

        return output;
    }
};
