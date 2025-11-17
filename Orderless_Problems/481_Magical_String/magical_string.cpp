/*
    ==============
    === MEDIUM ===
    ==============

    ===========================
    481) Magical String
    ===========================

    ============
    Description:
    ============

    A magical string s consists of only '1' and '2' and obeys the following
    rules:

        + The string s is magical because concatenating the number of
          contiguous occurrences of characters '1' and '2' generates the string
          s itself.

    The first few elements of s is s = "1221121221221121122……". If we group the
    consecutive 1's and 2's in s, it will be "1 22 11 2 1 22 1 22 11 2 11 22
    ......" and the occurrences of 1's or 2's in each group are "1 2 2 1 1 2 1
    2 2 1 2 2 ......". You can see that the occurrence sequence is s itself.

    Given an integer n, return the number of 1's in the first n number in the
    magical string s.

    ===================================
    FUNCTION: int magicalString(int n);
    ===================================

    ==========================================================================
    ================================ EXAMPLES ================================
    ==========================================================================

    --- Example 1 ---
    Input: n = 6
    Output: 3
    Explanation: The first 6 elements of magical string s is "122112" and it
                 contains three 1's, so return 3.

    --- Example 2 ---
    Input: n = 1
    Output: 1

    *** Constraints ***
    1 <= n <= 10^5

*/

#include <algorithm>
#include <string>
using namespace std;

/*
    ------------
    --- IDEA ---
    ------------

    The only important thing here is to RESERVE space for stirng s so that we
    do NOT perform any reallocations.

    (n + 1) is enough given the Description of the problem.

*/

/* Time  Beats: 59.12% */
/* Space Beats: 96.26% */

/* Time  Complexity: O(N) */
/* Space Complexity: O(N) */
class Solution {
public:
    int magicalString(int n)
    {
       if (n <= 3)
            return 1;

       string s = "122";
       s.reserve(n + 1);

       int i = 2;
       while (static_cast<int>(s.length()) < n)
       {
           if (s[i] == '1')
           {
               if (s.back() == '2')
                   s.push_back('1');
               else
                   s.push_back('2');
           }
           else
           {
               if (s.back() == '2')
                   s += "11";
               else
                   s += "22";
           }

           i++;
       }

       int ones = count(s.begin(), s.begin() + n, '1');

       return ones;
    }
};
