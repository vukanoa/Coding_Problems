#include <iostream>
#include <vector>
#include <numeric> // for "accumulate"

/*
    ============
    === EASY ===
    ============

    ======================================
    2558) Take Gifts From the Richest Pile
    ======================================

    ============
    Description:
    ============

    You are given an integer array gifts denoting the number of gifts in
    various piles. Every second, you do the following:

        + Choose the pile with the maximum number of gifts.

        + If there is more than one pile with the maximum number of gifts,
          choose any.

        + Leave behind the floor of the square root of the number of gifts in
          the pile. Take the rest of the gifts.

    Return the number of gifts remaining after k seconds.

    =========================================================
    FUNCTION: long long pickGifts(vector<int>& gifts, int k);
    =========================================================

    ==========================================================================
    ================================ EXAMPLES ================================
    ==========================================================================

    --- Example 1 ---
    Input: gifts = [25,64,9,4,100], k = 4
    Output: 29
    Explanation:
    The gifts are taken in the following way:
    - In the first second, the last pile is chosen and 10 gifts are left behind.
    - Then the second pile is chosen and 8 gifts are left behind.
    - After that the first pile is chosen and 5 gifts are left behind.
    - Finally, the last pile is chosen again and 3 gifts are left behind.
    The final remaining gifts are [5,8,9,4,3], so the total number of gifts
    remaining is 29.

    --- Example 2 ---
    Input: gifts = [1,1,1,1], k = 4
    Output: 4
    Explanation:
    In this case, regardless which pile you choose, you have to leave behind 1
    gift in each pile. That is, you can't take any pile with you.
    So, the total gifts remaining are 4.


    *** Constraints ***
    1 <= gifts.length <= 10^3
    1 <= gifts[i] <= 10^9
    1 <= k <= 10^3

*/

using namespace std;

/*
    ------------
    --- IDEA ---
    ------------

    The most fundamental Heap problem. If you couldn't do it by yourself, learn
    about Heaps and learn about the syntax and how-to-use Heaps in your
    language.

    In C++, there are 2 ways:
        1) Priority Queue
        2) Using original vector as a Heap

    Priority Queue is a more robuts implementation, however it uses extra space
    since we have to copy entire Input vector in it and then work with that
    priority_queue(by default it's "max Heap")

    On the other hand, using original vector as a heap is more efficient in
    terms of space, but it's less robuts. If you need to do some advanced
    things, I suggest using more space and going with the Priority Queue
    implementation.

*/

/* Time  Beats: 100.00% */
/* Space Beats:  95.91% */

/* Time  Complexity: O(k * logn) */
/* Space Complexity: O(1)        */
class Solution {
public:
    long long pickGifts(vector<int>& gifts, int k)
    {
        make_heap(gifts.begin(), gifts.end()); // O(n)

        while (k-- > 0)
        {
            pop_heap(gifts.begin(), gifts.end()); // O(logn)
            int pile = gifts.back();
            gifts.pop_back();

            pile = floor(sqrt(pile));

            gifts.push_back(pile);
            push_heap(gifts.begin(), gifts.end()); // O(logn)
        }

        /* If you don't want to use "accumulate" function */

        // long long result = 0;
        // for (int i = 0; i < gifts.size(); i++)
        //     result += static_cast<long long>(gifts[i]);

        long long result = std::accumulate(gifts.begin(), gifts.end(), 0LL, [](long long sum, int gift) {
            return sum + static_cast<long long>(gift);
        });

        return result;
    }
};
