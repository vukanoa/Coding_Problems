#include <iostream>
#include <vector>
#include <algorithm>

/*
    ==============
    === MEDIUM ===
    ==============

    ============================================
    2300) Successful Pairs of Spells and Potions
    ============================================

    ============
    Description:
    ============

    You are given two positive integer arrays spells and potions, of length n
    and m respectively, where spells[i] represents the strength of the ith
    spell and potions[j] represents the strength of the jth potion.

    You are also given an integer success. A spell and potion pair is
    considered successful if the product of their strengths is at least
    success.

    Return an integer array pairs of length n where pairs[i] is the number of
    potions that will form a successful pair with the ith spell.

    ===================================================================================================
    FUNCTION: vector<int> successfulPairs(vector<int>& spells, vector<int>& points, long long success);
    ===================================================================================================

    ==========================================================================
    ================================ EXAMPLES ================================
    ==========================================================================

    --- Example 1 ---
    Input: spells = [5,1,3], potions = [1,2,3,4,5], success = 7
    Output: [4,0,3]
    Explanation:
    - 0th spell: 5 * [1,2,3,4,5] = [5,10,15,20,25]. 4 pairs are successful.
    - 1st spell: 1 * [1,2,3,4,5] = [1,2,3,4,5]. 0 pairs are successful.
    - 2nd spell: 3 * [1,2,3,4,5] = [3,6,9,12,15]. 3 pairs are successful.
    Thus, [4,0,3] is returned.


    --- Example 2 ---
    Input: spells = [3,1,2], potions = [8,5,8], success = 16
    Output: [2,0,2]
    Explanation:
    - 0th spell: 3 * [8,5,8] = [24,15,24]. 2 pairs are successful.
    - 1st spell: 1 * [8,5,8] = [8,5,8]. 0 pairs are successful.
    - 2nd spell: 2 * [8,5,8] = [16,10,16]. 2 pairs are successful.
    Thus, [2,0,2] is returned.



    *** Constraints ***
    n == spells.length
    m == potions.length
    1 <= n, m <= 10^5
    1 <= spells[i], potions[i] <= 10^5
    1 <= success <= 10^10

*/

/*
    ------------
    --- IDEA ---
    ------------

    First thing to notice in this problem is that pairs[i] represents how many
    potions combined with spells[i] are success.

    They tell us that up-front, but it's important.
    Why is it so important?

    It's important because that implicitly means we are NOT allowed to reorder,
    or sort, "spells".

    However, when you understand what are they asking us to do you'll realize
    they don't care in which order and which potions exactly are success with
    certain spells, they ONLY care about HOW MUCH potions are success with
    certain spells.

    Therefore, we can conclude that the order of potions is NOT imporant, which
    further means we are allowed to reorder/rearrange potions, i.e. we can
    sort them if we think that is going to help us.

    Let's see if that is going to be of any help to us.

    Consider this example:

        spells = [7,1,3], potions = [8,5,3,2,5], success = 20
                  0 1 2

        Output = [4,0,1]
                  0 1 2

    What would be the Brute force way to do this?
    For every spell in "spells", iterate through all the "potions" and check if
    the current spell multiplies by current potions is greater than or equal to
    "success".

    Iterating through all of the "spells" would take O(N), however iterating
    through all the "potions" would take O(M), therefore total Time Complexity
    would be:
        O(N * M)

    Since both N and M are within the same range:
        1 <= n, m <= 10^5

    We can consider this Time Complexity quadratic, which is inefficient.

    So, is there anything we could do to reduce this Time Complexity?
    Let's check if we can reduce O(N) part to O(logN) or even O(1).

    We can quickly realize that we cannot since we must, at least once, check
    the current spell. Also, to build our "pairs"(result) vector, it takes us
    at least O(N), therefore reducing the O(N) part is out of the question.

    Now let's see if we can reduce O(M) to O(logM) or even to O(1).
    Let's consider the same example as above:

        spells = [7,1,3], potions = [8,5,3,2,5], success = 20
                  0 1 2

        Output = [4,0,1]
                  0 1 2

    Is there a way to check how many potions multiplied by the current spell
    would give us success without checking each and every potion?

    What if we sort potions? (Remember that we can reorder of potions?)

        spells = [7,1,3], potions = [2,3,5,5,8], success = 20
                  0 1 2

    Let's ask the same question - Can we check how many potions multiplied by
    the current spell would give us success without checking each and every
    potion?

    Yes, we can.
    How?

    Let's say we pick a value in the middle(index 2, element 5 in this case).
    Is 7 * 5 >= success(20)?

    Yes!
    Then that means that all the elements from the current one(Inclusive) until
    the end of the array would give success as well.

    We know that since we've sorted the elements and if:
        current_element * current_potion

    gives success, then it is guarantted that:
        current_element * value_greater_than_current_potion

    will also be >= success.


    This screams "Binary Search".
    From now on, it is a basic Binary Search that is implemented for "potions".

*/

/* Time  Beats: 86.64% */
/* Space Beats: 17.37% */

/* Time  Complexity: O(N * logM + M * logM) */
/* Space Complexity: O(max(N, M)) */
class Solution {
public:
    std::vector<int> successfulPairs(std::vector<int>& spells,
                                     std::vector<int>& potions,
                                     long long success)
    {
        int N = spells.size();
        int M = potions.size();
        std::vector<int> pairs(N);

        // O(M * logM)
        std::sort(potions.begin(), potions.end());

        // O(N * logM)
        for (int i = 0; i < N; i++)
        {
            int max_potions = 0;

            int left  = 0;
            int right = M-1;

            while (left <= right)
            {
                int mid = left + (right - left) / 2;

                if ((long long)spells[i] * (long long)potions[mid] >= success)
                {
                    max_potions = std::max(max_potions, M - mid);
                    right = mid - 1;
                }
                else
                    left  = mid + 1;
            }

            pairs[i] = max_potions;
        }

        return pairs;
    }
};




/*
    ------------
    --- IDEA ---
    ------------

    This is a more clean way of implementing the same IDEA.

*/

/* Time  Beats: 94.59% */
/* Space Beats: 12.42% */

/* Time  Complexity: O(N * logM + M * logM) */
/* Space Complexity: O(max(N, M)) */
class Solution_2 {
public:
    std::vector<int> successfulPairs(std::vector<int>& spells,
                                     std::vector<int>& potions,
                                     long long success)
    {
        const int N = spells.size();
        const int M = potions.size();
        std::vector<int> pairs;

        // O(M * logM)
        std::sort(potions.begin(), potions.end());

        // O(N * logM)
        for (int& spell : spells)
        {
            int left  = 0;
            int right = M - 1;

            while (left <= right)
            {
                int mid = left + (right - left) / 2;

                if ((long long)spell * (long long)potions[mid] >= success)
                    right = mid - 1;
                else
                    left  = mid + 1;
            }

            pairs.push_back(M - left);
        }

        return pairs;
    }
};
