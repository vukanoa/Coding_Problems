/*
    ==============
    === MEDIUM ===
    ==============

    ========================================
    2513) Minimize the Maximum of Two Arrays
    ========================================

    ============
    Description:
    ============

    We have two arrays arr1 and arr2 which are initially empty. You need to add
    positive integers to them such that they satisfy all the following
    conditions:

        + arr1 contains uniqueCnt1 distinct positive integers, each of which is
          not divisible by divisor1.

        + arr2 contains uniqueCnt2 distinct positive integers, each of which is
          not divisible by divisor2.

        + No integer is present in both arr1 and arr2.

    Given divisor1, divisor2, uniqueCnt1, and uniqueCnt2, return the minimum
    possible maximum integer that can be present in either array.

    ======================================================================================
    FUNCTION: int minimizeSet(int divisor1, int divisor2, int uniqueCnt1, int uniqueCnt2);
    ======================================================================================

    ==========================================================================
    ================================ EXAMPLES ================================
    ==========================================================================

    --- Example 1 ---
    Input: divisor1 = 2, divisor2 = 7, uniqueCnt1 = 1, uniqueCnt2 = 3
    Output: 4
    Explanation: 
    We can distribute the first 4 natural numbers into arr1 and arr2.
    arr1 = [1] and arr2 = [2,3,4].
    We can see that both arrays satisfy all the conditions.
    Since the maximum value is 4, we return it.

    --- Example 2 ---
    Input: divisor1 = 3, divisor2 = 5, uniqueCnt1 = 2, uniqueCnt2 = 1
    Output: 3
    Explanation: 
    Here arr1 = [1,2], and arr2 = [3] satisfy all conditions.
    Since the maximum value is 3, we return it.

    --- Example 3 ---
    Input: divisor1 = 2, divisor2 = 4, uniqueCnt1 = 8, uniqueCnt2 = 2
    Output: 15
    Explanation: 
    Here, the final possible arrays can be arr1 = [1,3,5,7,9,11,13,15], and
    arr2 = [2,6]. It can be shown that it is not possible to obtain a lower
    maximum satisfying all conditions. 


    *** Constraints ***
    2 <= divisor1, divisor2 <= 10^5
    1 <= uniqueCnt1, uniqueCnt2 < 10^9
    2 <= uniqueCnt1 + uniqueCnt2 <= 10^9

*/

#include <climits>
using namespace std;

/*
    ------------
    --- IDEA ---
    ------------

    TODO

*/

/* Time  Beats: 100.00% */
/* Space Beats:  44.49% */

/* Time  Complexity: O(log(N)) */
/* Space Complexity: O(1)      */
class Solution {
private:
    int gcd(int a, int b)
    {
        if ( ! b) 
            return a;

        return gcd(b, a % b);
    }

    int lcm(long long a, long long b)
    {
        long long tmp = (a / gcd(a, b)) * b;
        return tmp > INT_MAX ? INT_MAX : tmp;
    }

public:
    int minimizeSet(int divisor1, int divisor2, int uniqueCnt1, int uniqueCnt2)
    {
        int left = 1;
        int right = INT_MAX;

        int LCM = lcm(divisor1, divisor2);

        while (left <= right)
        {
            int mid = left + (right - left) / 2;

            int count1 = mid / divisor1;
            int count2 = mid / divisor2;

            if (uniqueCnt1 <= mid - count1 &&
                uniqueCnt2 <= mid - count2 &&
                uniqueCnt1 + uniqueCnt2 <= mid - (mid / LCM))
            {
                right = mid - 1;
            }
            else
            {
                left = mid + 1;
            }
        }

        return left;
    }
};
