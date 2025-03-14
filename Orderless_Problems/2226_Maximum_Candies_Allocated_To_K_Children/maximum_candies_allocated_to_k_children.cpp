/*
    ==============
    === MEDIUM ===
    ==============

    =============================================
    2226) Maximum Candies Allocated to K Children
    =============================================

    ============
    Description:
    ============

    You are given a 0-indexed integer array candies. Each element in the array
    denotes a pile of candies of size candies[i]. You can divide each pile into
    any number of sub piles, but you cannot merge two piles together.

    You are also given an integer k. You should allocate piles of candies to k
    children such that each child gets the same number of candies. Each child
    can be allocated candies from only one pile of candies and some piles of
    candies may go unused.

    Return the maximum number of candies each child can get.

    ================================================================
    FUNCTION: int maximumCandies(vector<int>& candies, long long k);
    ================================================================

    ==========================================================================
    ================================ EXAMPLES ================================
    ==========================================================================

    --- Example 1 ---
    Input: candies = [5,8,6], k = 3
    Output: 5
    Explanation: We can divide candies[1] into 2 piles of size 5 and 3, and
                 candies[2] into 2 piles of size 5 and 1. We now have five
                 piles of candies of sizes 5, 5, 3, 5, and 1. We can allocate
                 the 3 piles of size 5 to 3 children. It can be proven that
                 each child cannot receive more than 5 candies.


    --- Example 2 ---
    Input: candies = [2,5], k = 11
    Output: 0
    Explanation: There are 11 children but only 7 candies in total, so it is
                 impossible to ensure each child receives at least one candy.
                 Thus, each child gets no candy and the answer is 0.


    *** Constraints ***
    1 <= candies.length <= 10^5
    1 <= candies[i] <= 10^7
    1 <= k <= 10^12

*/

#include <numeric>
#include <vector>
using namespace std;

/*
    ------------
    --- IDEA ---
    ------------

    This is a classic Binary Search problem. It may not be obvious to people
    who just started using Binary Search, but this is Binary Search by-the-book

    (It's almost equivalent problem to the famous "875. Koko Eating Bananas")

    The initial Binary Search people know of is when you have a sorted array
    through which you have to find some element using it.

    But that's way too trivial. No interviewer will ever ask such a question.
    Instead, Binary Search problems look exactly like this.

    You don't have a sorted vector, but you can perform it.
    How?

    Anytime you don't know what to do, ask yourself this question:

        "Is there a MINIMAL and MAXIMAL possible answer to this problem?"

    In other words, we're asked what is THE MAXIMUM number of candies we can
    allocate given that there are k children.

    If we sum all the candies and the total number of candies is LESS than k,
    then we are certain that we cannot allocate even 1 candies to all children.


        ******************
        *** Digression ***
        ******************

        Consider this example:

            Input: candies = [1,8,6], k = 7

        To allocate candies for k=7 children, we need AT LEAST 7 candies in
        total, right?

        However we don't really need to use every pile. Here we're able to
        obtain candies from only index 1 and index 2.


        Index 1 will gives us two candies for 4 children.
        Index 2 will gives us two candies for 3 children.

        Therefore we got 2 candies for all k=7 children even if we didn't use
        our index=1 pile of candies(1 in this case).


        But if we had this instead:

            Input: candies = [1,1,7,6], k = 7

        Here we WOULD NOT be able to allocate two candies for all k=2 children.
        How is that possible if--in total--we have same amount of candies?

        We can allocate one candy for each of k=7 children. If the total sum of
        candies is GREATER THAN OR EQUALS than k, then we can, at least,
        allocate 1 candy per child.

        However, in this example, even if we could, in theory allocate 2
        candies for each of k=7 children, we can't do that in practice because
        every child MUST get all of its X candies from a SINGLE pile.

        Let me say that again: 

            Every child MUST get all of its X candies from a SINGLE pile!

        In our example:

            Input: candies = [1,1,7,6], k = 7

        We have a total of 15 candies. In theory we could give 2 candies to
        each of our k=7 children.

        However, since we're NOT allowed to give any child candies from more
        than a SINGLE pile, we can't do that.

        Why?
        Let's see:

            pile 0: We can't allocate 2 candies for    any   children.
            pile 1: We can't allocate 2 candies for    any   children.
            pile 2: We CAN   allocate 2 candies for  7/2 = 3 children.
            pile 3: We CAN   allocate 2 candies for  7/2 = 3 children.

        Therefore, given our rule, we can allocate 2 candies for 6 children,
        but we needed to do that for k=7 children.

        Therefore, since we are NOT allowed to allocate candies to any child
        from more than a SINGLE pile, we can't "pile up" pile 0 and pile 1 to
        allocate 2 candies for the last child.


    Now let's ask our "magic" question:

        "Is there a MINIMAL and MAXIMAL possible answer to this problem?"

    Yes, there is!

    MINIMAL possible answer is to allocate 1 candy   for k children.
    MAXIMAL possible answer is to allocate X candies for k children.

        where 'X' can be any number from 1 up to sum of all candies.

    For example, if we had:

        Input: candies = [0, 0, 17, 0], k=1

    MINIMAL: 1
    MAXIMAL: 17

    Computer doesn't know immediately which one is it, but the answer lays
    between 1 and 17, that's for sure.

    Since we've established that there is a RANGE between which the answer is
    guaranteed--We now know Binary Search is technique to be used.


    Instead of:
        Trying to see if we can allocate 1  candy   for k children, then
        trying to see if we can allocate 2  candies for k children, then
        trying to see if we can allocate 3  candies for k children, ...

        trying to se eif we can allocate 17 candies for k children

    Which would take us O(M * N), where M is the sum of all candies, i.e. 17
    and N is the size of candies through which we have to iterate each time
    and see how many can we allocate FROM WITHIN EACH PILE SEPARATELY.

    Then, if there are >= than k allocated, we say that we can allocate that
    many candies, otherwise we can't and we stop immediately.


    But instead of doing it in this Brute-Force way, since we've established
    that there is a RANGE between which the answer is guaranteed, we can do
    Binary Search on this outer part to reduce Time Complexity.

    Therefore, now we'll try to allocate "mid" amount of candies, where "mid"
    is the calculation of "mid" in a Binary Search, i.e.:

        mid = L + (R - L) / 2;      // Be careful NOT to do this: (L + R) / 2

    Then we try to see if we can allocate "mid" amount of candies for k
    children by iterating thorugh all of our N candies and counting how many
    candies can we allocate WITHIN EACH PILE SEPARATELY.

    If we can allocate >= k candies, then:
        L = mid + 1
    else
        R = mi - 1

    This way, we've reduced our Time Complexity:

        from O(M * N) down to (logM * N)

*/

/* Time  Beats: 14.61% */
/* Space Beats: 73.33% */

/* Time  Complexity: O(N * logM) */
/* Space Complexity: O(1)        */
class Solution {
public:
    int maximumCandies(vector<int>& candies, long long k)
    {
        const int N = candies.size();
        unsigned long long result = 0;

        unsigned long long L = 1;
        unsigned long long R = accumulate(candies.begin(), candies.end(), 0ULL);

        if (R < k)
            return 0;
        else if (R == k)
            return 1;

        /* Binary Search */
        while (L <= R)
        {
            unsigned long long mid = L + (R - L) / 2; // To prevent Overflow, i.e. (L + R) / 2

            if (can_allocate_mid_for_k_children(candies, mid, k))
            {
                L = mid + 1;

                result = max(result, mid);
            }
            else
                R = mid - 1;
        }

        return result;
    }

private:
    bool can_allocate_mid_for_k_children(vector<int>& candies, unsigned long long& mid, long long k)
    {
        const int N = candies.size();

        unsigned long long can_allocate = 0;
        for (int i = 0; i < N; i++)
            can_allocate += static_cast<unsigned long long>(candies[i]) / mid;

        return can_allocate >= k;
    }
};
