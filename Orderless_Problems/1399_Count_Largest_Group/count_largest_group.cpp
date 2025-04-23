/*
    ============
    === EASY ===
    ============

    ===========================
    1399) Count Largest Group
    ===========================

    ============
    Description:
    ============

    You are given an integer n.

    Each number from 1 to n is grouped according to the sum of its digits.

    Return the number of groups that have the largest size.

    =======================================
    FUNCTION: int countLargestGroup(int n);
    =======================================

    ==========================================================================
    ================================ EXAMPLES ================================
    ==========================================================================

    --- Example 1 ---
    Input: n = 13
    Output: 4
    Explanation: There are 9 groups in total, they are grouped according sum of
    its digits of numbers from 1 to 13:
    [1,10], [2,11], [3,12], [4,13], [5], [6], [7], [8], [9].
    There are 4 groups with largest size.

    --- Example 2 ---
    Input: n = 2
    Output: 2
    Explanation: There are 2 groups [1], [2] of size 1.


    *** Constraints ***
    1 <= n <= 10^4

*/

#include <unordered_map>
using namespace std;

/*
    ------------
    --- IDEA ---
    ------------

    Self-Explanatory.

*/

/* Time  Beats: 51.86% */
/* Space Beats: 17.46% */

/*
    Time  Complexity: O(N * d) ---> O(N * log10(N))

    where 'D' is the number of digits in n(i.e. 'D' is log10(n)).
*/
/*
    Space Complexity: O(k)

    where k is the number of possible digit sums -> at most O(81) --> O(1)
*/
class Solution {
public:
    int countLargestGroup(int n)
    {
        unordered_map<int, int> umap;

        int biggest_group = 0;
        for (int i = 1; i <= n; i++)
        {
            int number = i;

            int sum = 0;
            while (number != 0)
            {
                sum += number % 10;
                number /= 10;
            }

            umap[sum]++;

            biggest_group = max(biggest_group, umap[sum]);
        }

        int result = 0;
        for (const auto& entry : umap)
        {
            if (entry.second == biggest_group)
                result++;
        }

        return result;
    }
};
