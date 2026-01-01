#include <iostream>
#include <vector>
#include <algorithm>

/*
    ==============
    === MEDIUM ===
    ==============

    ===========================
    881) Boats To Save People
    ===========================

    ============
    Description:
    ============

    You are given an array people where people[i] is the weight of the ith
    person, and an infinite number of boats where each boat can carry a maximum
    weight of limit. Each boat carries at most two people at the same time,
    provided the sum of the weight of those people is at most limit.

    Return the minimum number of boats to carry every given person.

    =============================================================
    FUNCTION: int numRescueBoats(vector<int>& people, int limit);
    =============================================================

    ==========================================================================
    ================================ EXAMPLES ================================
    ==========================================================================

    --- Example 1 ---
    Input: people = [1,2], limit = 3
    Output: 1
    Explanation: 1 boat (1, 2)


    --- Example 2 ---
    Input: people = [3,2,2,1], limit = 3
    Output: 3
    Explanation: 3 boats (1, 2), (2) and (3)


    --- Example 3 ---
    Input: people = [3,5,3,4], limit = 5
    Output: 4
    Explanation: 4 boats (3), (3), (4), (5)


    *** Constraints ***
    1 <= people.length <= 5 * 10^4
    1 <= people[i] <= limit <= 3 * 10^4

*/

/*
    ------------
    --- IDEA ---
    ------------

    This implementation is easier to read, however it uses the same code as
    in the other solution, Solution_2.

    Since we are told that:
        1 <= people[i] <= limit <= 3 * 10^4

    We know that at worst we needs people.size() boats. Therefore, a Binary
    Search comes to mind immediately, but upon further thinking it's easy to
    realize that it is unnecessary.

    If we sort the Input array:

        nums = [3, 3, 1, 2, 2], limit = 3 // Original

        nums = [1, 2, 2, 3, 3], limit = 3 // Sorted

    We'll realize that, since we have another limitation other than the "limit"
    size, which is that at most there can be 2 people in any boat, if we want
    to smuggle another human alongside the one with the greatest weight, the
    best chance of not exceeding the limit is to take the lightest person with
    him.

    Therefore, each time check if the heaviest person and the lightest person
    can be shipped together. If they can, cool, increment "left" and decrement
    "right" and ship them in one boat.

    Otheriwse, ship the heaviest and decrement only "right" pointer, while the
    "left" pointer remains untouched.

*/

/* Time  Beats: 98.14% */
/* Space Beats: 12.31% */

/* Time  Complexity: O(n * logn) */
/* Space Complexity: O(1)        */ // Depending on the sort
class Solution_1 {
public:
    int numRescueBoats(std::vector<int>& people, int limit)
    {
        std::sort(people.begin(), people.end());

        int left  = 0;
        int right = people.size() - 1;

        int boats = 0;
        while (left <= right)
        {
            if (people[left] + people[right] > limit)
                right--;
            else
            {
                left++;
                right--;
            }

            boats++;
        }

        return boats;
    }
};




/*
    ------------
    --- IDEA ---
    ------------

    This one is implemented without using the same code twice, though it is
    more difficult to read.

*/

/* Time  Beats: 95.17% */
/* Space Beats: 15.56% */

/* Time  Complexity: O(n * logn) */
/* Space Complexity: O(1)        */ // Depending on the sort
class Solution_2 {
public:
    int numRescueBoats(std::vector<int>& people, int limit)
    {
        std::sort(people.begin(), people.end());

        int left  = 0;
        int right = people.size() - 1;

        int boats = 0;

        while (left <= right)
        {
            if (people[left] + people[right] <= limit)
                left++;

            right--;
            boats++;
        }

        return boats;
    }
};
