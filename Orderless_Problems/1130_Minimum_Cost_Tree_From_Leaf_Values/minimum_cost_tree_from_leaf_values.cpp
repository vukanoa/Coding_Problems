/*
    ==============
    === MEDIUM ===
    ==============

    ========================================
    1130) Minimum Cost Tree From Leaf Values
    ========================================

    ============
    Description:
    ============

    Given an array arr of positive integers, consider all binary trees such
    that:

        + Each node has either 0 or 2 children;

        + The values of arr correspond to the values of each leaf in an
          in-order traversal of the tree.

        + The value of each non-leaf node is equal to the product of the
          largest leaf value in its left and right subtree, respectively.

    Among all possible binary trees considered, return the smallest possible
    sum of the values of each non-leaf node. It is guaranteed this sum fits
    into a 32-bit integer.

    A node is a leaf if and only if it has zero children.

    ==================================================
    FUNCTION: int mctFromLeafValues(vector<int>& arr);
    ==================================================

    ==========================================================================
    ================================ EXAMPLES ================================
    ==========================================================================

    --- Example 1 ---
    Input: arr = [6,2,4]
    Output: 32
    Explanation: There are two possible trees shown.
    The first has a non-leaf node sum 36, and the second has non-leaf node sum
    32.

    --- Example 2 ---
    Input: arr = [4,11]
    Output: 44


    *** Constraints ***
    2 <= arr.length <= 40
    1 <= arr[i] <= 15
    It is guaranteed that the answer fits into a 32-bit signed integer (i.e.,
    it is less than 231).

*/

#include <stack>
#include <vector>
using namespace std;

/*
    ------------
    --- IDEA ---
    ------------

    TODO

*/

/* Time  Beats: 100.00% */
/* Space Beats:  98.73% */

/* Time  Complexity: O(N) */
/* Space Complexity: O(N) */
class Solution {
    int mctFromLeafValues(vector<int>& arr)
    {
        const int N = arr.size();

        if (N < 2)
            return 0;
        
        int result = 0;
        stack<int> mono_decr_stack;
        for (const int& num : arr)
        {
            while ( ! mono_decr_stack.empty() && mono_decr_stack.top() <= num)
            {
                int mid = mono_decr_stack.top();
                mono_decr_stack.pop();

                if (mono_decr_stack.empty())
                    result += mid * num;
                else
                    result += mid * min(mono_decr_stack.top(), num);
            }

            mono_decr_stack.push(num);
        }
        
        while (mono_decr_stack.size() > 1)
        {
            int top = mono_decr_stack.top();
            mono_decr_stack.pop();

            result += top * mono_decr_stack.top();
        }
        
        return result;
    }
};
