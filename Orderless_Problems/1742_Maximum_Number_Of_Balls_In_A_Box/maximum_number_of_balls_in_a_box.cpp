/*
    ============
    === EASY ===
    ============

    ======================================
    1742) Maximum Number of Balls in a Box
    ======================================

    ============
    Description:
    ============

    You are working in a ball factory where you have n balls numbered from
    lowLimit up to highLimit inclusive (i.e., n == highLimit - lowLimit + 1),
    and an infinite number of boxes numbered from 1 to infinity.

    Your job at this factory is to put each ball in the box with a number equal
    to the sum of digits of the ball's number. For example, the ball number 321
    will be put in the box number 3 + 2 + 1 = 6 and the ball number 10 will be
    put in the box number 1 + 0 = 1.

    Given two integers lowLimit and highLimit, return the number of balls in
    the box with the most balls.

    ======================================================
    FUNCTION: int countBalls(int lowLimit, int highLimit);
    ======================================================

    ==========================================================================
    ================================ EXAMPLES ================================
    ==========================================================================

    --- Example 1 ---
    Input: lowLimit = 1, highLimit = 10
    Output: 2
    Explanation:
    Box Number:  1 2 3 4 5 6 7 8 9 10 11 ...
    Ball Count:  2 1 1 1 1 1 1 1 1 0  0  ...
    Box 1 has the most number of balls with 2 balls.

    --- Example 2 ---
    Input: lowLimit = 5, highLimit = 15
    Output: 2
    Explanation:
    Box Number:  1 2 3 4 5 6 7 8 9 10 11 ...
    Ball Count:  1 1 1 1 2 2 1 1 1 0  0  ...
    Boxes 5 and 6 have the most number of balls with 2 balls in each.

    --- Example 3 ---
    Input: lowLimit = 19, highLimit = 28
    Output: 2
    Explanation:
    Box Number:  1 2 3 4 5 6 7 8 9 10 11 12 ...
    Ball Count:  0 1 1 1 1 1 1 1 1 2  0  0  ...
    Box 10 has the most number of balls with 2 balls.


    *** Constraints ***
    1 <= lowLimit <= highLimit <= 10^5

*/

#include <algorithm>
#include <unordered_map>
using namespace std;


/*
    ------------
    --- IDEA ---
    ------------

    Self-explanatory. Basic use of HashMap.

*/

/* Time  Beats: 42.17% */
/* Space Beats: 11.57% */

/* Time  Complexity: O(highLimit - lowLimit + 1) */
/* Space Complexity: O(highLimit - lowLimit + 1) */
class Solution {
public:
    int countBalls(int lowLimit, int highLimit)
    {
        int result = 0;
        unordered_map<int,int> freq;

        for (int i = lowLimit; i <= highLimit; i++)
            result = max(result, ++freq[calculate_sum(i)]);

        return result;
    }

private:
    int calculate_sum(int number)
    {
        int sum = 0;
        while (number > 0)
        {
            sum += number % 10;
            number /= 10;
        }

        return sum;
    }
};




/*
    ------------
    --- IDEA ---
    ------------

    Since Constraints are:

        1 <= lowLimit <= highLimit <= 10^5

    In other words, the biggest number possible is: 100'000, it's easy to
    figure out that, therefore, the biggest sum of digits can be obtained from
    number:
    
        99'999 ---> 45

    Therefore, we do NOT need a HashMap, we can use a basic array and allocate
    it on the Stack, which is an order of magnitude faster, on the micro level.

*/

/* Time  Beats: 73.25% */
/* Space Beats: 78.07% */

/* Time  Complexity: O(N)           */ // N <==> highLimit - lowLimit + 1
/* Space Complexity: O(46) --> O(1) */
class Solution_Better_Implementation {
public:
    int countBalls(int lowLimit, int highLimit)
    {
        int result = 0;
        int freq[46] = {0};

        // O(N * 6) (entire block)
        for (int i = lowLimit; i <= highLimit; i++) // O(N)
        {
            int number = i;
            int sum = 0;

            // O(6) (entire block)
            while (number > 0)
            {
                sum += number % 10;
                number /= 10;
            }

            result = max(result, ++freq[sum]);
        }

        return result;
    }
};
