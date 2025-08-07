/*
    ==============
    === MEDIUM ===
    ==============

    ===========================
    306) Additive Number
    ===========================

    ============
    Description:
    ============

    An additive number is a string whose digits can form an additive sequence.

    A valid additive sequence should contain at least three numbers. Except for
    the first two numbers, each subsequent number in the sequence must be the
    sum of the preceding two.

    Given a string containing only digits, return true if it is an additive
    number or false otherwise.

    =====
    Note: Numbers in the additive sequence cannot have leading zeros, so
          sequence 1, 2, 03 or 1, 02, 3 is invalid.
    =====

    ============================================
    FUNCTION: bool isAdditiveNumber(string num);
    ============================================

    ==========================================================================
    ================================ EXAMPLES ================================
    ==========================================================================

    --- Example 1 ---
    Input: "112358"
    Output: true
    Explanation:
    The digits can form an additive sequence: 1, 1, 2, 3, 5, 8.
    1 + 1 = 2, 1 + 2 = 3, 2 + 3 = 5, 3 + 5 = 8

    --- Example 2 ---
    Input: "199100199"
    Output: true
    Explanation:
    The additive sequence is: 1, 99, 100, 199.
    1 + 99 = 100, 99 + 100 = 199


    *** Constraints ***
    1 <= num.length <= 35
    num consists only of digits.

*/

#include <algorithm>
#include <string>
using namespace std;

/*
    ------------
    --- IDEA ---
    ------------

    TODO

*/

/* Time  Beats: 100.00% */
/* Space Beats:  56.94% */

/* Time  Complexity: O(N^3) */
/* Space Complexity: O(N)   */
class Solution {
public:
    bool isAdditiveNumber(string num)
    {
        const int N = num.size();

        for (int i = 1; i <= N/2; i++)
        {
            for (int j = 1; j <= (N-i)/2; j++)
            {
                if (check(num.substr(0,i), num.substr(i,j), num.substr(i+j)))
                    return true;
            }
        }

        return false;
    }

private:
    bool check(string num1, string num2, string num)
    {
        const int N = num.size();

        if (num1.size() > 1 && num1[0] == '0' || num2.size()>1 && num2[0] == '0')
            return false;

        string sum = add(num1, num2);

        if (num == sum)
            return true;

        if (N <= sum.size() || sum.compare(num.substr(0,sum.size())) != 0)
            return false;
        else
            return check(num2, sum, num.substr(sum.size()));
    }

    string add(string n, string m)
    {
        string result;

        int i = n.size()-1;
        int j = m.size()-1;

        int carry = 0;
        while (i >= 0 || j >= 0)
        {
            int sum = carry + (i >= 0 ? (n[i--] - '0') : 0) + (j >= 0?  (m[j--]-'0') : 0);
            result.push_back(sum%10+'0');
            carry = sum / 10;
        }

        if (carry)
            result.push_back(carry+'0');

        reverse(result.begin(), result.end());

        return result;
    }
};
