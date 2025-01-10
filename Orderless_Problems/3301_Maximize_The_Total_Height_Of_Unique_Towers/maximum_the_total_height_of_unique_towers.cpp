/*
    ==============
    === MEDIUM ===
    ==============

    ===============================================
    3301) Maximum the Total Height of Unique Towers
    ===============================================

    ============
    Description:
    ============

    You are given an array maximumHeight, where maximumHeight[i] denotes the
    maximum height the ith tower can be assigned.

    Your task is to assign a height to each tower so that:

        + The height of the ith tower is a positive integer and does not exceed
          maximumHeight[i].

        + No two towers have the same height.

    Return the maximum possible total sum of the tower heights. If it's not
    possible to assign heights, return -1.

    ================================================================
    FUNCTION: long long maximumTotalSum(vector<int>& maximumHeight);
    ================================================================

    ==========================================================================
    ================================ EXAMPLES ================================
    ==========================================================================

    --- Example 1 ---
    Input: maximumHeight = [2,3,4,3]
    Output: 10
    Explanation: We can assign heights in the following way: [1, 2, 4, 3].

    --- Example 2 ---
    Input: maximumHeight = [15,10]
    Output: 25
    Explanation: We can assign heights in the following way: [15, 10].

    --- Example 3 ---
    Input: maximumHeight = [2,2,1]
    Output: -1
    Explanation: It's impossible to assign positive heights to each index so
                 that no two towers have the same height.


    *** Constraints ***
    1 <= maximumHeight.length <= 10^5
    1 <= maximumHeight[i] <= 10^9

*/

#include <algorithm>
#include <vector>
using namespace std;

/*
    ------------
    --- IDEA ---
    ------------

    The very first thing you should notice is this:

        if the maximum height is LESS tha the total amount of elements in
        "maximumHeight", then it is IMPOSSIBLE to achieve what we are being
        aked and thus, we shall return -1 as a result.


    Also, we can notice that we do not care about the order of elements. We
    only care about maximizing the sum.

    That means we're allowed to sort the Input.

    So, can we just be greedy?
    Yes! We can!

    But there's a caveat.
    Let's consider this example:

        maximumHeight = [10, 15, 3, 2, 3, 2]
                          0   1  2  3  4  5

            *** SORT in decreasing order ***

        maximumHeight = [15, 10, 3, 3, 2, 2]
                          0   1  2  3  4  5
                          i

    Since 15 is the maximum height among all of the heights, we check:

        if (15 < 6) // Where '6' is N, i.e. the number of elements

    It is not, therefore, we add "15" to our sum(i.e. "result").
    Now, 15 is not able to be added to "result" anymore since we've just used
    it. We decrement 15 by 1 and now it's 14.

    We'll call this veriable "currently_max_assignable_height".
    It begins at the maximum height among all of the maximumHeight heights.

    Each time we use certain height, we must decrement by one, since this one
    is used.

    However if "currently_max_assignable_height" is 14, but our, now,
    largest element is 10, then because of the description of the problem we
    are NOT allowed to assign 14 to our now largest unprocessed element 10.

    Therefore, we must take the minimum of these two:

        min(currently_max_assignable_height, maximumHeight[i])

    However,

    Now, our 'i' pointer is shifted: [15, 10, 3, 3, 2, 2]
                                       0   1  2  3  4  5
                                           i

    Our "currently_max_assignable_height" is 14, however, our
    maximumHeight[i] is 10.

    Therefore, we aren't allowed to assign 14 since height 10 is the upper
    bound, thus, each time we are taking the minimum out of these two:

        min(currently_max_assignable_height, maximumHeight[i])


    However, do you remember the thing we've noticed at the beginning?
    Let me repeat that:

        if the maximum height is LESS tha the total amount of elements in
        "maximumHeight", then it is IMPOSSIBLE to achieve what we are being
        aked and thus, we shall return -1 as a result.

    Once you notice that, and once you read carefully the Description, you'll
    realize that we have to do this check for each element.

    But how can we know how many elements are left at our current 'i'?

    Simply: N - i

    Since we've sorted it:

        [15, 10, 3, 3, 2, 2]
         0   1   2  3  4  5

    Our Prefix would look like this:

        [6,  5   4  3  2  1]
         0   1   2  3  4  5

    If at ANY point our "currently_max_assignable_height" is LESS than (N-i)
    that means we're done. It's impossible to aschieve what we're being asked.

    IMPORTANT: we checking this AFTER we've taken the minimum out of these:

        min(currently_max_assignable_height, maximumHeight[i])

    In this example, we'd return -1 once 'i' is at index 2.
    Why?

    Because 'i' is pointing at element 3, which means that our
    "currently_max_assignable_height" can be of maximum 3, but there is a
    problem because there are 4 remaining elements.

    If we begin assigning from 3, then we won't be able to assign the last one.

    remaining 4 slots: [x, x, x, x]

    first one MUST begin by 3, and all the rest must be LESS than 3.

        3emaining 4 slots: [x, x, x, x]
        remaining 3 slots: [3, x, x, x]
        remaining 2 slots: [3, 2, x, x]
        remaining 1 slot : [3, 2, 1, x]
                                     ^
                         ____________|
                         |
                         |
    And what do we put here then?

    Nothing, we can't do it, therefore we are returning -1.

    That's why we must do this check-up at EACH element, i.e. at each position
    of our 'i' pointer.

*/

/* Time  Beats: 93.32% */
/* Space Beats: 54.43% */

/* Time  Complexity: O(N * logN) */
/* Space Complexity: O(N)        */
class Solution {
public:
    long long maximumTotalSum(vector<int>& maximumHeight)
    {
        const int N = maximumHeight.size();
        long long result = 0;

        int currently_max_assignable_height = *max_element(maximumHeight.begin(), maximumHeight.end());

        if (currently_max_assignable_height < N)
            return -1;

        sort(maximumHeight.begin(), maximumHeight.end(), greater<int>());

        for (int i = 0; i < maximumHeight.size(); i++)
        {
            result += min(maximumHeight[i], currently_max_assignable_height);

            currently_max_assignable_height = min(currently_max_assignable_height, maximumHeight[i]);

            if (currently_max_assignable_height <  (N - i))
                return -1;

            currently_max_assignable_height--;
        }

        return result;
    }
};
