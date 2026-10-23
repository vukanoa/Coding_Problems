/*
    ==============
    === MEDIUM ===
    ==============

    =============================================
    3776) Minimum Moves to Balance Circular Array
    =============================================

    ============
    Description:
    ============

    You are given a circular array balance of length n, where balance[i] is the
    net balance of person i.

    In one move, a person can transfer exactly 1 unit of balance to either
    their left or right neighbor.

    Return the minimum number of moves required so that every person has a
    non-negative balance. If it is impossible, return -1.

    =====
    Note: You are guaranteed that at most 1 index has a negative balance
          initially. 
    =====

    ===================================================
    FUNCTION: long long minMoves(vector<int>& balance);
    ===================================================

    ==========================================================================
    ================================ EXAMPLES ================================
    ==========================================================================

    --- Example 1 ---
    Input: balance = [5,1,-4]
    Output: 4
    Explanation:
    One optimal sequence of moves is:
        Move 1 unit from i = 1 to i = 2, resulting in balance = [5, 0, -3]
        Move 1 unit from i = 0 to i = 2, resulting in balance = [4, 0, -2]
        Move 1 unit from i = 0 to i = 2, resulting in balance = [3, 0, -1]
        Move 1 unit from i = 0 to i = 2, resulting in balance = [2, 0, 0]
    Thus, the minimum number of moves required is 4.


    --- Example 2 ---
    Input: balance = [1,2,-5,2]
    Output: 6
    Explanation:
    One optimal sequence of moves is:
        Move 1 unit from i = 1 to i = 2, resulting in balance = [1, 1, -4, 2]
        Move 1 unit from i = 1 to i = 2, resulting in balance = [1, 0, -3, 2]
        Move 1 unit from i = 3 to i = 2, resulting in balance = [1, 0, -2, 1]
        Move 1 unit from i = 3 to i = 2, resulting in balance = [1, 0, -1, 0]
        Move 1 unit from i = 0 to i = 1, resulting in balance = [0, 1, -1, 0]
        Move 1 unit from i = 1 to i = 2, resulting in balance = [0, 0, 0, 0]
    Thus, the minimum number of moves required is 6.


    --- Example 3 ---
    Input: balance = [-3,2]
    Output: -1
    Explanation:
    It is impossible to make all balances non-negative for balance = [-3, 2],
    so the answer is -1.




    *** Constraints ***
    1 <= n == balance.length <= 10^5
    -10^9 <= balance[i] <= 10^9
    There is at most one negative value in balance initially.

*/

#include <cmath>
#include <cstdlib>
#include <vector>
using namespace std;

/*
    ------------
    --- IDEA ---
    ------------

    TODO

*/

/* Time  Beats: 39.29% */
/* Space Beats: 20.83% */

/* Time  Complexity: O(N) */
/* Space Complexity: O(N) */
class Solution {
public:
    long long minMoves(vector<int>& balance)
    {
        const int N = balance.size();
        long long operations = 0LL;

        int       idx_one = -1;
        long long total   = 0LL;
        for (int i = 0; i < N; i++)
        {
            total += balance[i];

            if (balance[i] < 0)
                idx_one = i;
        }

        if (total < 0)
            return -1;

        if (idx_one == -1)
            return 0;

        int idx_two = idx_one + N;
        int required = -1LL * balance[idx_one];
        

        balance.insert(balance.end(), balance.begin(), balance.end());

        int L = (idx_one - 1 + N) % N;
        int R =  idx_one + 1;
        for (;;)
        {
            if (balance[L] >= 0)
            {
                int distance = min(abs(L - idx_one),
                                   abs(L - idx_two));
                
                int transferred = min(balance[L], required);

                operations += transferred * 1LL * distance;
                required   -= transferred;
    
                if (required == 0)
                    break;        
            }

            if (balance[R] >= 0)
            {
                int distance = min(abs(R - idx_one),
                                   abs(R - idx_two));

                int transferred = min(balance[R], required);
                
                operations += transferred * 1LL * distance;
                required   -= transferred;
    
                if (required == 0)
                   break;
            }

            L = (L - 1 + N) % N;
            R =  R + 1;
        }

        // To restore original "balance"
        while (balance.size() > N)
            balance.pop_back();

        return operations;
    }
};
