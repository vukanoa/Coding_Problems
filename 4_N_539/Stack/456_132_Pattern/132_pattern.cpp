#include <iostream>
#include <vector>
#include <stack>

/*
    ==============
    === MEDIUM ===
    ==============

    ===========================
    456) 123 Pattern
    ===========================

    ============
    Description:
    ============

    Given an array of n integers nums, a 132 pattern is a subsequence of three
    integers nums[i], nums[j] and nums[k] such that i < j < k and nums[i] <
    nums[k] < nums[j].

    Return true if there is a 132 pattern in nums, otherwise, return false.

    =================================================
    FUNCTION: bool find132pattern(vector<int>& nums);
    =================================================

    ==========================================================================
    ================================ EXAMPLES ================================
    ==========================================================================

    --- Example 1 ---
    Input: nums = [1,2,3,4]
    Output: false
    Explanation: There is no 132 pattern in the sequence.

    --- Example 2 ---
    Input: nums = [3,1,4,2]
    Output: true
    Explanation: There is a 132 pattern in the sequence: [1, 4, 2].

    --- Example 3 ---
    Input: nums = [-1,3,2,0]
    Output: true
    Explanation: There are three 132 patterns in the sequence: [-1, 3, 2],
                 [-1, 3, 0] and [-1, 2, 0].


    *** Constraints ***
    n == nums.length
    1 <= n <= 2 * 10^5
    -10^9 <= nums[i] <= 10^9

*/

/*
    ------------
    --- IDEA ---
    ------------

    This one is a bit more difficult than it seems.


    First of all, DO NOT oversee what is being asked of you here.

            i   <    j    <   k

        nums[i] < nums[k] < nums[j]  // nums[j] is GREATEST!! Not nums[k]!!


    So, the element that has the "middle index" is the one that should be the
    GREATEST.

    Element that has that has the "lowest index" is the one that should be the
    LOWEST.

    Element that has the the "largest index" is the one that should be the
    between LOWEST and GREATEST(cannot be equal to either of those).


    ---------------------------------------------------------------------------

    If you have never heard of "Monotonic Stack", and to be precise
    "Monotonicly Decreasing Stack", then you have no chance solving this
    problem.

    If you have heard of it, it's still unintuitive to come up with this type
    of solution.


    Let's consider one example:

        nums  = [3, 1, 4, 2]

    Since we want it to be DECREASING:

                ------------------------
        stack = |
                ------------------------


        1. 
            nums = [3, 1, 4, 2]
                    i

                    ------------------------
            stack = | 3                        // Push
                    ------------------------

        2. 
            nums = [3, 1, 4, 2]
                       i

                    ------------------------
            stack = | 3 | 1                    // Push
                    ------------------------


        3. 
            nums = [3, 1, 4, 2]
                          i

                    ------------------------
            stack = | 3 | 1                     // Pop
                    ------------------------
                    ------------------------
            stack = | 1                         // Pop
                    ------------------------
                    ------------------------
            stack = | 4                         // Push
                    ------------------------

        4. 
            nums = [3, 1, 4, 2]
                             i

                    ------------------------
            stack = | 4 | 2                     // Push
                    ------------------------


    
    But, why do we use a "Monotonicly Decreasing Stack"?

    Since we need nums[j](element that has the "middle index" in our
    subsequence) to be the GREATEST and since we need nums[k](element that has
    the "largest index" in our subsequence) to be the SECOND largest, then
    having a "Monotonicly Decreasing Stack" ensures this proparty.

    If there are more than 2 elements on the stack, that means we have
    certainly have nums[j] and nums[k].

    But how are we going to know if we have found nums[i](element that has the
    "lowest index" and that is considered LOWEST value out of all three)?

    As you see above, in the 3rd step, we've popped both 1 and 3, because
    placing 4 on the stack would otherwise violate the "Monotonicly Decreasing
    Stack" property.

    At the end we do have 2 or more elements on the stack, meaning we have
    nums[j] and nums[k], however, we DO NOT have nums[i] anymore since we've
    popped it.


    So the absolute crux of this Solution is this:

        If we have nums[j] < nums[k] property fulfilled because we used:
        "Monotonicly Decreasing Stack", then the only thing we have to know
        additionally, to be able to solve this, is to know if there are
        elements LEFT of index j that is LOWER than nums[k].

        [Make sure you read the above paragraph carefully]

        #######################################################################
            Remember, we are looking for this:
                i   <    j    <   k

            nums[i] < nums[k] < nums[j]  // nums[j] is GREATEST!! Not nums[k]!!
        #######################################################################


        [?, ?, ...., nums[j], ?, .. ?, nums[k]]

        Our Stack looks like this:

            --------------------------------
            | nums[j] | nums[k]                 // nums[j] > nums[k]
            --------------------------------


        Before pushing nums[k] on the stack, our Stack looked like this:

            --------------------------------
            | nums[j]
            --------------------------------

        Since nums[j] is > nums[k] we have that part done. However, we would
        like to know if there is an element BEFORE index j, that is LOWER
        than nums[k].

        Nowhere on our Stack is that information. Even worse, we had that
        information, but we've popped it to obtain a Decreasing property of our
        Stack.

        So what should we do?
        This is the part that is unintuitive:

            We should keep a Stack of pairs! (Or 2 stacks of same size)

        [It's easier to draw two stacks, but consider them a single one with
         pairs as elements]

                    ----------------   
              nums  | nums[j]  |
                    -----------+----   
           min_left | nums[i]  |     // Min to the left, EXCLUDING current num
                    ----------------   


    Now let's do the same problem, using this Stack with "pairs" as elements:

*******************************************************************************
********************************** SIMULATION *********************************
*******************************************************************************

    

        Stack:
                    ------------------------
           curr_num |
                    ------------------------
           min_left |
                    ------------------------

                    // minimum value left of index i
                    curr_min = INT_MAX

-------------------------------------------------------------------------------

        1. 
            nums = [3, 1, 4, 2]
                    i

                Before pushing each element onto the Stack, we have to check:

                if (
                    !stack.empty()               &&
                    stack.top().first  > nums[i] &&
                    stack.top().second < nums[i]
                   )


                However, we can omit the 2nd condition:

                    stack.top().first  > nums[i]

                because if we haven't popped it yet, then we are sure it's
                greater than our nums[i]. That's the power and the very reason
                we are using "Monotonicly Decreasing Stack".

                Therefore, before pushing each element into a Stack, we have to
                check:

                if (
                    !stack.empty()               &&
                    stack.top().second < nums[i]
                   )

                This is NOT fullfilled, therefore we are going to Push:

                    ------------------------
           curr_num | 3                       // Push
                    ------------------------
           min_left | INT_MAX                 // Push
                    --^---------------------
                      |
                      ------- curr_min

                    // minimum value left of index i
                    curr_min = min(curr_min, nums[i])
                    curr_min = min( INT_MAX,   3    ) = 3     // NEW MIN

-------------------------------------------------------------------------------

        2. 
            nums = [3, 1, 4, 2]
                       i

                Before pushing each element onto the Stack, we have to check:

                if (
                    !stack.empty()               &&
                    stack.top().first  > nums[i] &&
                    stack.top().second < nums[i]
                   )


                However, we can omit the 2nd condition:

                    stack.top().first  > nums[i]

                because if we haven't popped it yet, then we are sure it's
                greater than our nums[i]. That's the power and the very reason
                we are using "Monotonicly Decreasing Stack".

                Therefore, before pushing each element into a Stack, we have to
                check:

                if (
                    !stack.empty()               &&
                    stack.top().second < nums[i]
                   )

                This is NOT fullfilled, therefore we are going to Push:

                    ------------------------
           curr_num |   3     | 1             // Push
                    ----------+-------------
           min_left | INT_MAX | 3             // Push
                    ------------^-----------
                                |
                                --- curr_min

                    // minimum value left of index i
                    curr_min = min(curr_min, nums[i])
                    curr_min = min(   3    ,   1    ) = 1     // NEW MIN

-------------------------------------------------------------------------------

        3. 
            nums = [3, 1, 4, 2]
                          i

                    ------------------------
           curr_num |   3     | 1             // Pop
                    ----------+-------------
           min_left | INT_MAX | 3             // Pop
                    ------------------------

                    ------------------------
           curr_num |   3                     // Pop
                    ------------------------
           min_left | INT_MAX                 // Pop
                    ------------------------

                    ------------------------
           curr_num |
                    ------------------------
           min_left |
                    ------------------------

                Before pushing each element onto the Stack, we have to check:

                if (
                    !stack.empty()               &&
                    stack.top().first  > nums[i] &&
                    stack.top().second < nums[i]
                   )


                However, we can omit the 2nd condition:

                    stack.top().first  > nums[i]

                because if we haven't popped it yet, then we are sure it's
                greater than our nums[i]. That's the power and the very reason
                we are using "Monotonicly Decreasing Stack".

                Therefore, before pushing each element into a Stack, we have to
                check:

                if (
                    !stack.empty()               &&
                    stack.top().second < nums[i]
                   )

                This is NOT fullfilled, therefore we are going to Push:

                    ------------------------
           curr_num | 4                       // Push
                    ------------------------
           min_left | 1                       // Push
                    --^---------------------
                      |
                      --- curr_min

-------------------------------------------------------------------------------

        4. 
            nums = [3, 1, 4, 2]
                             i

            Before pushing each element onto the Stack, we have to check:

            if (
                !stack.empty()               &&
                stack.top().first  > nums[i] &&
                stack.top().second < nums[i]
               )


            However, we can omit the 2nd condition:

                stack.top().first  > nums[i]

            because if we haven't popped it yet, then we are sure it's greater
            than our nums[i]. That's the power and the very reason we are using
            "Monotonicly Decreasing Stack".

            Therefore, before pushing each element into a Stack, we have to
            check:

            if (
                !stack.empty()               &&
                stack.top().second < nums[i]
               )

                    ------------------------
           curr_num | 4
                    ------------------------
           min_left | 1
                    ------------------------


            Since stack is NOT empty and stack.top().second < nums[i], that
            means we have "132" pattern and we immediately return true.

-------------------------------------------------------------------------------

    Good Example to try yourself:
        [5, 8, 1, 4, 5, 3, 7, 6, 3, 4, 9]

*/

/* Time  Beats: 11.09% */
/* Space Beats: 10.34% */

/* Time  Complexity: O(n) */
/* Space Complexity: O(n) */
class Solution {
public:
    bool find132pattern(std::vector<int>& nums)
    {
        std::stack<std::pair<int, int>> stack; // {num, min_to_the_left}
        int curr_min = nums[0];

        for (int i = 1; i < nums.size(); i++)
        {
            while (!stack.empty() && stack.top().first <= nums[i])
                stack.pop();

            if (!stack.empty() && stack.top().second < nums[i])
                return true;

            stack.push({nums[i], curr_min});
            curr_min = std::min(nums[i], curr_min);
        }

        return false;
    }
};




/*
    ------------
    --- IDEA ---
    ------------

    Virtually the same IDEA, though implemented in another way. We are going
    backwards therefore we don't have to have a pair inside our stack.

*/
/* Time  Beats: 11.73% */
/* Space Beats:  5.67% */

/* Time  Complexity: O(n) */
/* Space Complexity: O(n) */
class Solution_2 {
public:
    bool find132pattern(std::vector<int>& nums)
    {
        std::stack<int> stack;
        int third = INT_MIN;

        for (int i = nums.size()-1; i >= 0; i--)
        {
            if (nums[i] < third)
                return true;

            while (!stack.empty() && stack.top() < nums[i])
            {
                third = stack.top();
                stack.pop();
            }

            stack.push(nums[i]);
        }

        return false;
    }
};
