#include <iostream>

/*
    ==============
    === MEDIUM ===
    ==============

    ===========================
    846) Hand Of Straights
    ===========================

    ============
    Description:
    ============

    Alice has some number of cards and she wants to rearrange the cards into
    groups so that each group is of size groupSize, and consists of groupSize
    consecutive cards.

    Given an integer array hand where hand[i] is the value written on the ith
    card and an integer groupSize, return true if she can rearrange the cards,
    or false otherwise.

    =================================================================
    FUNCTION: bool isNStraightHand(vector<int>& hand, int groupSize);
    =================================================================

    ==========================================================================
    ================================ EXAMPLES ================================
    ==========================================================================

    --- Example 1 ---
    Input: hand = [1,2,3,6,2,3,4,7,8], groupSize = 3
    Output: true
    Explanation: Alice's hand can be rearranged as [1,2,3],[2,3,4],[6,7,8]


    --- Example 2 ---
    Input: hand = [1,2,3,4,5], groupSize = 4
    Output: false
    Explanation: Alice's hand can not be rearranged into groups of 4.


    *** Constraints ***
    1 <= hand.length <= 104
    0 <= hand[i] <= 109
    1 <= groupSize <= hand.length

*/


/*
    ------------
    --- IDEA ---
    ------------

    It's pretty intuitive. Once you go through the code, I'm sure you'll get
    the idea.

    However, it's important to note that this can be done using only vector
    "nums", but instead of sorting it and the pushing it into the deque, we
    could've sort it but in in reverse and then just do the same thing, but
    from the back of the vector "nums".

    I think this is easier to graps and on LeetCode it Beats most of the
    Solutions anyway, so why bother complicating it.

    Consider Example 1:
        hand = [1,2,3,6,2,3,4,7,8]
        groupSize = 3

        Output: true


    Immediately we have to check if groupSize is equal to 1. If that is the
    case than we are certainly sure we can group groupSize piles of groupSize
    consecutive elements since any number by itself will be a pile we don't
    even have to check if the consetutiveness is infringed within the pile.

    In that case we return true.

    However, in order to be possible to have groupSize piles, we must have
    hand.size() be divisible by groupSize.
    If that happens not to be the case, we imemdiately return false.

    First, sort it:
        hand  = [1, 2, 2, 3, 3, 4, 6, 7, 8]

    Push it in a Deque
        deque = [1, 2, 2, 3, 3, 5, 6, 7, 8]

    "prev" is used so that once we are iterating through the hand to complete
    the current pile, we have to check if the lowest remaining value is
    consecutive to the pile we have at the moment.

    We have to make a pile of 3 and if current pile is [1, 2], that means that
    "prev" is equal to 2 which will helps to see if there is a consecutive
    value in the deque.

    Since deque is sorted, deque.front() gives us the lowest remaining value
    which we can use to check if that is the element we need or if we can
    immediately return false since we cannot find the consecutive card for the
    current pile.

    That's why we use variable "prev".

    We are trying to do this until our deque becomes empty, i.e until we've
    succeded to use all of the elements, meaning we were able to assemble all
    of the piles in a correct way.

    At the beginning of the "construction" of the current pile, we immediately
    assign "prev" to deque.front() and pop that element from the deque.

    Also we have a variable "curr_pile" which indicates how many cards we have
    at the moment in our pile. Since we need to "construct" the group/pile of
    groupSize cards, we are going to be doing this inner part until curr_pile
    becomes equal to groupSize. (or until we empty the deque which would
    indicate that we weren't able to assemble current pile, which further
    indicates that we should return false)

    Once we're in the process of making the current pile we have to check if
    the current lowest amount in the deque is equal to the "prev". Why?
    Because if it is, we have to skip it, but we don't have to return false
    since that number can be used for a next pile.

    Since we have to skip it, we need to somehow save that number. We push it
    onto the stack, pop from the deque and continue.

    If, on the other hand, prev + 1 < deque.front() that means we cannot find
    a consecutive element in this current pile, then immediatel return false.

    If none of the above two if's are true that means we've successfully found
    the consecutive element needed for this pile, therefore we increment
    "curr_pile", change "prev" to that newly "added"(we're not adding) element
    and pop that element from the front of the deque.

    We repeat this until we complete entire pile.

    Once we're out of the inner while loop, that means one of the two things:
    Either:
        1) We were unable to assemble entire pile
          or
        2) We were able to assemble entire pile

    If 1) is the case, we return false.

    If 2) is the case, now we have to return all the elements we've skipped
    during this "search". (Remember that we've pushed it onto the stack?).

    Now pop from the stack and push into deque.front() until the stack becomes
    empty.

    We repeat all of this until:
    Either:
        1) Deque becomes empty
          or
        2) We've returned false at some point

    If 1) is the case, that means we successfully assembled all groupSize piles
    into groupSize consecutive elements and therefore we return true.

*/

/* Time  Beats: 99.19% */
/* Space Beats: 97.50% */

/* Time  Complexity: O(n * logn) */
/* Space Complexity: O(n) */
class Solution {
public:
    bool isNStraightHand(std::vector<int>& hand, int groupSize)
    {
        if (groupSize == 1)
            return true;
        else if (hand.size() % groupSize != 0)
            return false;

        std::deque<int> deque;
        std::stack<int> stack;

        // O(n * logn)
        std::sort(hand.begin(), hand.end());

        // O(n)
        for (int& card : hand)
            deque.push_back(card);

        int prev;
        while (!deque.empty())
        {
            prev = deque.front();
            deque.pop_front();

            int curr_pile = 1;

            while (!deque.empty() && curr_pile < groupSize)
            {
                if (prev == deque.front())
                {
                    stack.push(deque.front());
                    deque.pop_front();
                    continue;
                }
                else if (prev + 1 < deque.front()) // Not Consecutive within group
                    return false;

                curr_pile++;
                prev = deque.front();
                deque.pop_front();
            }

            if (curr_pile < groupSize)
                return false;

            while (!stack.empty())
            {
                deque.push_front(stack.top());
                stack.pop();
            }
        }

        return true;
    }
};
