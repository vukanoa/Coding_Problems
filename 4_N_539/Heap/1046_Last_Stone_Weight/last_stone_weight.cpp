#include <iostream>
#include <vector>
#include <queue>

/*
    ============
    === EASY ===
    ============

    ===========================
    1046) Last Stone Weight
    ===========================

    ============
    Description:
    ============

    You are given an array of integers stones where stones[i] is the weight of
    the ith stone.

    We are playing a game with the stones. On each turn, we choose the heaviest
    two stones and smash them together. Suppose the heaviest two stones have
    weights x and y with x <= y. The result of this smash is:

        If x == y, both stones are destroyed, and If x != y, the stone of
        weight x is destroyed, and the stone of weight y has new weight y - x.

    At the end of the game, there is at most one stone left.

    Return the weight of the last remaining stone. If there are no stones left,
    return 0.

    ===================================================
    FUNCTION: int lastStoneWeight(vector<int>& stones);
    ===================================================

    ==========================================================================
    ================================ EXAMPLES ================================
    ==========================================================================

    --- Example 1 ---
    Input: stones = [2,7,4,1,8,1]
    Output: 1
    Explanation:
    We combine 7 and 8 to get 1 so the array converts to [2,4,1,1,1] then,
    we combine 2 and 4 to get 2 so the array converts to [2,1,1,1] then,
    we combine 2 and 1 to get 1 so the array converts to [1,1,1] then,
    we combine 1 and 1 to get 0 so the array converts to [1] then that's the
    value of the last stone.


    --- Example 2 ---
    Input: stones = [1]
    Output: 1


    *** Constraints ***
    1 <= stones.length <= 30
    1 <= stones[i] <= 1000

*/

/*
    ------------
    --- IDEA ---
    ------------

    Basic use of "Priority Queue" aka Heap.

    It doesn't get any more textbook "Heap Problem" than this.

    They've asked us to sum two of the heaviest stones at any given moment. A
    naive, Brute Force, approach would be to find two heaviest stones for each
    new number of remaining stones by iterating through the stones and finding
    them "manually".

    Please note that each new number of remaining stones is going to be UNIQUE.
    Why?

    Because if, say, we begin with N elements. In each iteration we're going to
    remove heaviest two stones and then either:
        1. Don't push back either of those two, currently, heaviest stones
        2. Push back element y-x // 1st_Heaviest - 2nd_heaviest

    So, we begin with N elements, then remove 2. Now we have N-2.
    Then we have two options:
        1. Continue with N-2 elements                     // N-2 + 0
        2. Push back y-x, i.e. continue with N-1 element  // N-2 + 1

    Therefore, as you can see, each iteration is going be reducing the total
    amount of elements by either 1 or 2.

    You can already notice that to simply remove two heaviest stones from a
    standard "vector", it would require O(n) to find them and then it would
    require O(n) to remove them because you would have to be shifting the
    remaining elements afterwards.

    So even before we tried solving the second part of this problem(to push
    back y-x), we realize it's going to be inefficient.

    Is there an efficient way of removing and pushing elements back?

    The first thing that comes to mind would, maybe, be sorting the Input.
    However, you'll quickly realize that you are having the exact same problem.
    If you were to remove two heaviest stones, you can improve finding them
    from O(n) to O(logn), however when it comes down to removing, you see that
    after the removal you potentially must shift the remaining elements,
    therefore it is, again, O(n).


    So, what do we need? Let's ask ourselves.

    1. We need a way of finding "kth" largest element and "k - 1st" largest
       element efficiently and remove them.

    If we ask ourselves the same question, but in a bit of a different way,
    we'll quickly come up with a solution.

    1. We need a way of finding "kth" largest element efficiently.
    2. We need to remove that "kth" largest element efficiently.
    3. We need a way of finding "kth" largest element efficiently. // New 'kth'
    4. We need to remove that "kth" largest element efficiently.

    Once we find the first "kth" largest element and remove it, then if we,
    again, try to find the "kth" largest element, we'll find the "k - 1st"
    largest element in the entire initial array.

    So is there a data structure which helps us find the kth largest element?

    Or let me put it this way - Is there a data structure which helps us find
    the minimum value out of k elements efficiently?

    Yes, there is. It's a Heap.

    We'll make a heap out of our initial array, however we're going to be
    popping elements until we end up with a total of k largest elements.
    (Hint hint, it's going to be a Max Heap)

    Once we have k elements, then finding the minimum can be performed in O(1)
    and it can be removed in O(1) as well.

    Once we do that now the new minimum value is "k - 1st" element from the
    original elements of size k.

    We, then, remove that one as well and do what they are telling us to do in
    the Description of this problem:
        I.e. If x == y, we just continue, else we push y-x back to our heap.

    Repeat this until we either end up with a single element or with no
    elements at all.

    If at the end there are no elements in our heap, then we return 0.
    Otherwise, we return the value that's left.

*/

/* Time  Beats:  100% */
/* Space Beats: 20.53% */

/* Time  Complexity: O(n) */
/* Space Complexity: O(n) */
class Solution {
public:
    int lastStoneWeight(std::vector<int>& stones)
    {
        std::priority_queue<int> max_heap(stones.begin(), stones.end());

        while (max_heap.size() > 1)
        {
            int y = max_heap.top();
            max_heap.pop(); // O(logn)

            int x = max_heap.top();
            max_heap.pop(); // O(logn)

            if (x != y)
                max_heap.push(y - x);
        }

        return max_heap.empty() ? 0 : max_heap.top();
    }
};
