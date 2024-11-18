#include <iostream>
#include <vector>
#include <algorithm>

/*
    ============
    === EASY ===
    ============

    ===========================
    1652) Defuse the Bomb
    ===========================

    ============
    Description:
    ============

    You have a bomb to defuse, and your time is running out! Your informer will
    provide you with a circular array code of length of n and a key k.

    To decrypt the code, you must replace every number. All the numbers are
    replaced simultaneously.

        + If k > 0, replace the ith number with the sum of the next k numbers.

        + If k < 0, replace the ith number with the sum of the previous k
          numbers.

        + If k == 0, replace the ith number with 0.

    As code is circular, the next element of code[n-1] is code[0], and the
    previous element of code[0] is code[n-1].

    Given the circular array code and an integer key k, return the decrypted
    code to defuse the bomb!

    ========================================================
    FUNCTION: vector<int> decrypt(vector<int>& code, int k);
    ========================================================

    ==========================================================================
    ================================ EXAMPLES ================================
    ==========================================================================

    --- Example 1 ---
    Input: code = [5,7,1,4], k = 3
    Output: [12,10,16,13]
    Explanation: Each number is replaced by the sum of the next 3 numbers. The
                 decrypted code is [7+1+4, 1+4+5, 4+5+7, 5+7+1]. Notice that
                 the numbers wrap around.


    --- Example 2 ---
    Input: code = [1,2,3,4], k = 0
    Output: [0,0,0,0]
    Explanation: When k is zero, the numbers are replaced by 0.


    --- Example 3 ---
    Input: code = [2,4,9,3], k = -2
    Output: [12,5,6,13]
    Explanation: The decrypted code is [3+9, 2+3, 4+2, 9+4]. Notice that the
                 numbers wrap around again. If k is negative, the sum is of the
                 previous numbers.


    *** Constraints ***
    n == code.length
    1 <= n <= 100
    1 <= code[i] <= 100
    -(n - 1) <= k <= n - 1

*/

/*
    ------------
    --- IDEA ---
    ------------

    If k == 0, we need to return a vector of the same length as "code", but
    with all 0s as values.

    We can treat that as a Base-case. If it is true that k is 0, then:
        return vector<int>(code.size(), 0);

    Now we have two more options:
        1. k is POSITIVE
        2. k is NEGATIVE

    It would be painful to write code for each separately and branch based on
    the value of k.

    Instead what we can do is check if the k is NEGATIVE and if it is, then
    REVERSE he INPUT vector "code" and change k to be positive number.

    Then do the entire problem as if K is POSITIVE and as if we are looking for
    "next k elements" and not "previous k elements" sum and at the very end
    simply reverse the "result" vector again.

    It is fairly simple to come up with the "Sliding Window" approach as it is
    the most natural approach in this case.

    The only thing you have to take care of is the "out of bounds" for both
    "left" and "right" pointers. If at any point any of them becomes "n", since
    we're ALWAYS moving them to the right, then simply make them point to 0.

    We have done that 3 times in the code, instead of 2 as it intuitively seems
    to be the case.

    Read the code and I'm sure you'll understand it.

*/

/* Time  Beats: 100.00% */
/* Space Beats:  17.93% */

/* Time  Complexity: O(n) */
/* Space Complexity: O(1) */ // We don't count "result" vector as Additional
class Solution {
public:
    vector<int> decrypt(vector<int>& code, int k)
    {
        if (k == 0)
            return vector<int>(code.size(), 0);

        const int n = code.size();

        bool negative = false;
        if (k < 0)
        {
            negative = true;
            k *= -1;
            reverse(code.begin(), code.end());
        }

        int left  = 1;
        int right = 1;

        int sum = 0;
        while (right - left < k)
        {
            sum += code[right];
            right++;
        }

        if (right == n)
            right = 0;

        vector<int> result(n, 0);
        for (int x = 0; x < n; x++)
        {
            result[x] = sum;

            sum -= code[left];
            left++;

            if (left == n)
                left = 0;

            sum += code[right];
            right++;

            if (right == n)
                right = 0;
        }

        if (negative)
            reverse(result.begin(), result.end());

        return result;
    }
};
