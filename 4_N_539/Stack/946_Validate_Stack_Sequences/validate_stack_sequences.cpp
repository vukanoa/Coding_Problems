#include <iostream>
#include <stack>

/*
    ==============
    === MEDIUM ===
    ==============

    =============================
    946) Validate Stack Sequences
    =============================

    ============
    Description:
    ============

    Given two integer arrays pushed and popped each with distinct values,
    return true if this could have been the result of a sequence of push and
    pop operations on an initially empty stack, or false otherwise.

    ================================================================================
    FUNCTION: bool validateStackSequences(vector<int>& pushed, vector<int>& popped);
    ================================================================================

    ==========================================================================
    ================================ EXAMPLES ================================
    ==========================================================================

    --- Example 1 ---
    Input: pushed = [1,2,3,4,5], popped = [4,5,3,2,1]
    Output: true
    Explanation: We might do the following sequence:
    push(1), push(2), push(3), push(4),
    pop() -> 4,
    push(5),
    pop() -> 5, pop() -> 3, pop() -> 2, pop() -> 1


    --- Example 2 ---
    Input: pushed = [1,2,3,4,5], popped = [4,3,5,1,2]
    Output: false
    Explanation: 1 cannot be popped before 2.



    *** Constraints ***
    1 <= pushed.length <= 1000
    0 <= pushed[i] <= 1000
    All the elements of pushed are unique.
    popped.length == pushed.length
    popped is a permutation of pushed.

*/


/* Time  Beats: 87.89% */
/* Space Beats: 65.15% */

/* Time  Complexity: O(n) */
/* Space Complexity: O(n) */
class Solution_1 {
public:
    bool validateStackSequences(vector<int>& pushed, vector<int>& popped)
    {
        int n = pushed.size(); // Or popped.size(), it's the same.
        std::stack<int> stack;

        int i = 0;
        int j = 0;

        while (i < n)
        {
            if (stack.empty())
                stack.push(pushed[i++]);

            if (stack.top() != popped[j])
            {
                while (i < n && popped[j] != stack.top())
                    stack.push(pushed[i++]);

                if (stack.top() != popped[j])
                    return false;
            }

            stack.pop();
            j++;
        }

        while (j < n)
        {
            if (stack.empty() || stack.top() != popped[j])
                return false;

            stack.pop();
            j++;
        }

        return stack.empty();
    }
};




/* Time  Beats: 87.89% */
/* Space Beats: 38.93% */

/* Time  Complexity: O(n) */
/* Space Complexity: O(n) */
class Solution_2 {
public:
    bool validateStackSequences(std::vector<int>& pushed, std::vector<int>& popped)
    {
        std::stack<int> stack;
        int j = 0;

        for(int x : pushed)
        {
            stack.push(x);

            while(!stack.empty() && stack.top() == popped[j])
            {
                stack.pop();
                j++;
            }
        }

        return stack.empty();
    }
};




/* Time  Beats: 94.85% */
/* Space Beats: 65.15% */

/* Time  Complexity: O(n) */
/* Space Complexity: O(1) */ // Constant Space
class Solution_Constant_Space {
public:
    bool validateStackSequences(std::vector<int>& pushed, std::vector<int>& popped)
    {
        int i = 0;
        int j = 0;

        for (auto x : pushed)
        {
            pushed[i++] = x;

            while (i > 0 and pushed[i-1] == popped[j])
            {
                --i;
                ++j;
            }
        }

        return i == 0;
    }
};
