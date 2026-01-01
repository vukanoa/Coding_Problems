/*
    ============
    === EASY ===
    ============

    ===========================
    66) Plus One
    ===========================

    ============
    Description:
    ============

    You are given a **large integer** represented as an integer array "digits",
    where eeach digit[i] is the i-th digit of the integer.o

    You are given a large integer represented as an integer array digits, where
    each digits[i] is the ith digit of the integer. The digits are ordered from
    most significant to least significant in left-to-right order. The large
    integer does not contain any leading 0's.

    Increment the large integer by one and return the resulting array of
    digits.

    ===================================================
    FUNCTION: vector<int> plusOne(vector<int>& digits);
    ===================================================

    ==========================================================================
    ================================ EXAMPLES ================================
    ==========================================================================

    --- Example 1 ---
    Input: digits = [1,2,3]
    Output: [1,2,4]
    Explanation: The array represents the integer 123.
    Incrementing by one gives 123 + 1 = 124.
    Thus, the result should be [1,2,4].

    --- Example 2 ---
    Input: digits = [4,3,2,1]
    Output: [4,3,2,2]
    Explanation: The array represents the integer 4321.
    Incrementing by one gives 4321 + 1 = 4322.
    Thus, the result should be [4,3,2,2].


    --- Example 3 ---
    Input: digits = [9]
    Output: [1,0]
    Explanation: The array represents the integer 9.
    Incrementing by one gives 9 + 1 = 10.
    Thus, the result should be [1,0].


    *** Constraints ***
    1 <= digits.length <= 100
    0 <= digits[i] <= 9
    digits does not contain any leading 0's.


*/

#include <numeric>
#include <vector>
using namespace std;

/*
    ------------
    --- IDEA ---
    ------------

    The only "difficult" part in this problem is the figuring out WHEN do we
    actually need to add an additional digit in the front(most significant
    digit).

    That happens EXCLUSIVELY if ALL of the digits in "digits" are 9s.

    Think about it, if we have [1, 9, 9, 9], we'll end up with [2, 0, 0, 0]
    Or if we have [8, 9, 9], we 'll end up with [9, 0, 0].

    However, if we had: [9, 9, 9], then we'll have N+1 digits in result.
    We'd end up with:

        [1, 0, 0, 0]

    Therefore, an easy way to check for that is to simply calculate the total
    sum of digits in "digits".

    If it's eqaul to: 9 * size_of_digits, then that means "digits" is populated
    with all 9s.

    If that's the case, simply return a vector of size N+1, that has all 0s,
    except for the digit at, now, index 0 which should be equal to 1.

        digits = [9, 9, 9]
                  0  1  2

        result = [1, 0, 0, 0]
                  0  1  2  3

    Otherwise, simply assign result to be equal to "digits" and then iterate
    from the last digit(from the back) and as soon as you increment a non-9
    digit, break and return result.

*/

/* Time  Beats: 100.00% */
/* Space Beats: 50.17% */

/* Time  Complexity: O(N)                                       */
/* Space Complexity: O(N) total Space, but O(1) Auxiliary Space */
class Solution {
public:
    vector<int> plusOne(vector<int>& digits)
    {
        const int N = digits.size();

        int total_sum = accumulate(digits.begin(), digits.end(), 0); // O(N)

        // O(N) (entire block)
        if (9 * N == total_sum) // If it's all 9s
        {
            vector<int> result(N+1, 0); // O(N)
            result[0] = 1;

            return result;
        }

        // O(N) (entire block)
        vector<int> result = digits;
        for (int i = N-1; i >= 0; i--) // O(N)
        {
            if (result[i] < 9)
            {
                result[i]++;
                break;
            }

            result[i] = 0;
        }

        return result;
    }
};




/*
    ------------
    --- IDEA ---
    ------------

    Instead of checking if all elements are 9s, we try to be greedy.
    Keep incrementing and if we stumble upon a non-9 digit, then return
    immediately.

    If we do finish the loop, then that means we shall return a vector of size
    N+1 that has 0th element 1 and everything else 0.

    However, since we've already incremented all of the digits in "digits" to
    be, we only need to PREprend a 1.

    Unfortunately, we need to shift every element to the right, which takes
    O(N) time, however this way we do NOT use an additional vector "result".

    But one could argue that this extension is a new vector.

*/

/* Time  Complexity: O(2 * N) --> O(N) */
/* Space Complexity: O(1)              */
class Solution_In_Place_Almost {
public:
    vector<int> plusOne(vector<int>& digits)
    {
        const int N = digits.size();

        // O(N) (entire block)
        for (int i = N-1; i >= 0; i--) // O(N)
        {
            if (digits[i] < 9)
            {
                digits[i]++;
                return digits;
            }

            digits[i] = 0;
        }

        digits.insert(digits.begin(), 1); // O(N)

        return digits;
    }
};
