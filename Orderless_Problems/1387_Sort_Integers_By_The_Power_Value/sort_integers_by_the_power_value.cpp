/*
    ==============
    === MEDIUM ===
    ==============

    ======================================
    1387) Sort Integers by The Power Value
    ======================================

    ============
    Description:
    ============

    The power of an integer x is defined as the number of steps needed to
    transform x into 1 using the following steps:

        if x is even then x = x / 2

        if x is odd then x = 3 * x + 1

    For example, the power of x = 3 is 7 because 3 needs 7 steps to become 1
    (3 --> 10 --> 5 --> 16 --> 8 --> 4 --> 2 --> 1).

    Given three integers lo, hi and k. The task is to sort all integers in the
    interval [lo, hi] by the power value in ascending order, if two or more
    integers have the same power value sort them by ascending order.

    Return the kth integer in the range [lo, hi] sorted by the power value.

    Notice that for any integer x (lo <= x <= hi) it is guaranteed that x will
    transform into 1 using these steps and that the power of x is will fit in a
    32-bit signed integer.

    ============================================
    FUNCTION: int getKth(int lo, int hi, int k);
    ============================================

    ==========================================================================
    ================================ EXAMPLES ================================
    ==========================================================================

    --- Example 1 ---
    Input: lo = 12, hi = 15, k = 2
    Output: 13
    Explanation: The power of 12 is 9 (12 --> 6 --> 3 --> 10 --> 5 --> 16 --> 8 --> 4 --> 2 --> 1)
    The power of 13 is 9
    The power of 14 is 17
    The power of 15 is 17
    The interval sorted by the power value [12,13,14,15]. For k = 2 answer is the second element which is 13.
    Notice that 12 and 13 have the same power value and we sorted them in ascending order. Same for 14 and 15.

    --- Example 2 ---
    Input: lo = 7, hi = 11, k = 4
    Output: 7
    Explanation: The power array corresponding to the interval [7, 8, 9, 10, 11] is [16, 3, 19, 6, 14].
    The interval sorted by power is [8, 10, 11, 7, 9].
    The fourth number in the sorted array is 7.


    *** Constraints ***
    1 <= lo <= hi <= 1000
    1 <= k <= hi - lo + 1

*/

#include <cstring>
#include <queue>
#include <utility>
#include <vector>
using namespace std;

/*
    ------------
    --- IDEA ---
    ------------

    TODO

    int max_reached = 0;
    for (int num = 1; num <= 1000; num++)
    {
        long long x = num;
        while (x != 1)
        {
            max_reached = max(max_reached, (int)x);

            if (x % 2 == 0)
                x /= 2;
            else
                x = 3 * x + 1;
        }
    }
    cout << "Max value ever reached: " << max_reached << endl;


    Time Complexity (TC): O((hi - lo + 1) * log k + T)
    Space Complexity (SC): O(T + k),
    where T is the number of unique values computed in solve(x) and memoized.

    Minimum size of memo: 1000 × 8 = 8000 is safe.
    Reason: The worst-case integer in [1, 1000] reaches at most ~8000 during
            the 3x+1 steps. So memo should at least handle numbers up to ~8000.

*/

/*
    Time  Complexity: O((hi - lo + 1) * logk + T)

    where T is the number of unique values computed in solve(x) and memoized.
*/
/*
    Space Complexity: O(T + k)
*/
class Solution {
private:
    int memo[10000000];
public:
    int getKth(int lo, int hi, int k)
    {
        priority_queue<pair<int,int>, vector<pair<int,int>>> max_heap;

        /* Memset */
        memset(memo, -1, sizeof(memo));

        for (int num = lo; num <= hi; num++)
        {
            int steps = solve(num);

            if (max_heap.size() == k)
            {
                if ((max_heap.top().first < steps) || (max_heap.top().first <= steps && max_heap.top().second < num))
                    continue;

                max_heap.pop();
            }

            max_heap.push( {steps, num} );
        }

        return max_heap.top().second;
    }

private:
    int solve(int num)
    {
        if (num == 1)
            return 0;

        if (memo[num] != -1)
            return memo[num];

        int steps = 0;
        if (num & 1)
        {
            steps = 1 + solve(num * 3 + 1);
            return memo[num] = steps;
        }

        steps = 1 + solve(num / 2);
        return memo[num] = steps;
    }
};
