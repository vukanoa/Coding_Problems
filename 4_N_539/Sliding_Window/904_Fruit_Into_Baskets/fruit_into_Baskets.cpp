#include <iostream>
#include <vector>
#include <unordered_map>

/*
    ==============
    === MEDIUM ===
    ==============

    ===========================
    904) Fruit Into Baskets
    ===========================

    ============
    Description:
    ============

    You are visiting a farm that has a single row of fruit trees arranged from
    left to right. The trees are represented by an integer array fruits where
    fruits[i] is the type of fruit the ith tree produces.

    You want to collect as much fruit as possible. However, the owner has some
    strict rules that you must follow:

        - You only have two baskets, and each basket can only hold a single
          type of fruit. There is no limit on the amount of fruit each basket
          can hold.

        - Starting from any tree of your choice, you must pick exactly one
          fruit from every tree (including the start tree) while moving to the
          right. The picked fruits must fit in one of your baskets.

        - Once you reach a tree with fruit that cannot fit in your baskets, you
          must stop.

    Given the integer array fruits, return the maximum number of fruits you can
    pick.

    ==============================================
    FUNCTION: int totalFruit(vector<int>& fruits);
    ==============================================

    ==========================================================================
    ================================ EXAMPLES ================================
    ==========================================================================

    --- Example 1 ---
    Input: fruits = [1,2,1]
    Output: 3
    Explanation: We can pick from all 3 trees.


    --- Example 2 ---
    Input: fruits = [0,1,2,2]
    Output: 3
    Explanation: We can pick from trees [1,2,2].
    If we had started at the first tree, we would only pick from trees [0,1].


    --- Example 3 ---
    Input: fruits = [1,2,3,2,2]
    Output: 4
    Explanation: We can pick from trees [2,3,2,2].
    If we had started at the first tree, we would only pick from trees [1,2].


    *** Constraints ***
    1 <= fruits.length <= 10^5
    0 <= fruits[i] < fruits.length

*/

/*
    ------------
    --- IDEA ---
    ------------

    This entire Description can be summed-up into this:
    "What is the maximum contigous subarray with at most 2 distinct numbers?"

    Now, it's much easier.
    This is a textbook Sliding Window problem.

    We're going to convert a, Brute Force, O(n^2) Solution to a, Sliding
    Window, O(n) Solution.

    We'll have a HashMap (key=fruit_type, value=num_of_fruits_in_basket)

         Hash Map
    |  Key  :  Value |
    +----------------+
    |      ...       |
    +----------------+
    |      ...       |
    +----------------+

    We're going to be moving our "right" pointer and each time we're at some
    tree, we're going to increment the "num_of_fruits_in_basket" for that type.

    In C++, HashMaps work in a way that if you increment some yet unexistant
    entry, the entry will be created as soon as you change the value for that
    particular "key".

    At the very beginning, we have an empty HashMap:

             Hash Map
        |  Key  :  Value |
        +----------------+
        |       /        |
        +----------------+

    However, if we do this:

        hash_map[3]++;

    Now, entry {3, 1} will be created. // Default value for each key is 0.

    If we do anything with some entry in our HashMap, it will immediately
    become "visible", or property of the Hash Map.

    For example, again, if we have an empty Hash Map:

             Hash Map
        |  Key  :  Value |
        +----------------+
        |       /        |
        +----------------+

    And we write this line:
        if (hash_map[5] == <w/e>)  // <w/e> stands for "whatever".
            ...


    At that very point, if hash_map[5] DIDN'T exist in the HashMap yet, now it
    will. We'll have something like this now:

             Hash Map
        |  Key  :  Value  |
        +-----------------+
        |   5   :  <w/e>  |
        +-----------------+

    If you wish to circumvent this behavior, you could write the same if
    statement like this:
        if (hash_map.at(5) == <w/e>)  // <w/e> stands for "whatever".
            ...

    This accesses the value, however if it does NOT exist, it won't create a
    NEW pair, but it will, instead, give the 'std::out_of_range' error!

    So, be careful and use accordingly.

    Let's get back to our Solution.

    Since, by incrementing, we can "add" a new entry if it didn't already
    exist, we can use that to our advantage.

    At each iteration(at each position of "right" pointer), the very first
    thing we'll always do is this:

            hash_map[fruits[right]]++;

    If that type of fruit is already present in this "window", then we'll just
    increment it.

    However, and this is the crux of this Solution, if this type of fruit
    DOESN'T exist, then by incrementing it's value, we'll create a new entry
    in our Hash Map.

    It's important to refresh our memory with what are we being asked here:
    "What is the maximum contiguous subarray with at most 2 distinct numbers?"

    Since now, by making a new entry in our HashMap, we may have 3 entries, we
    must remove one. Which one should it be?

    Since we're doing a Sliding Window technique, it's obvious. But, how should
    one now to use this technique in the first place?

    The very first thing that should ring your bells is the word "CONTIGUOUS".

    Since we are asked to find the longest CONTIGUOUS subarray that has at max
    2 different numbers in it, we can consider this example:

    fruits [1, 1, 2, 1, 3]
            0  1  2  3  4
            L
            R

    We begin at index 0. At this point, our "window" is of size 1:
        window_len = R - L + 1 ===> 0 - 0 + 1 ===> 1

    Then we move our "R" pointer to the right by one.

    fruits [1, 1, 2, 1, 3]
            0  1  2  3  4
            L  R

    Here, we still have at max 2 different numbers in our window. Also, our
    window is of size 2 now:
        window_len = R - L + 1 = 1 - 0 + 1 = 2

    We're told that:"Starting from any tree of your choice, ..."

    So we began considering the longest contiguous window from index 0, but
    since now we're sure that if we start at index 0, we'll ALWAYS include a
    tree at index 1(because they are of same type), do we actually need to
    check what will happen if we begin at index 1?

    No, because starting at index 1 will ALWAYS give us a shorter contiguous
    subarray than if we are starting at index 0, because they are of the same
    type and tree at index 1 is implicitly included when starting at index 0.

    Therefore, we won't be having a O(n^2) Solution, but O(n) since we can
    notice that:
        1. They are asking us to find CONTIGUOUS subarrays
        2. Starting at index 1(in this example) will NEVER result in longer
           CONTINUOUS subarray than when starting at index 0.

    Therefore, we can use a Sliding Window technique.

    So, anytime we increment a value, we can check if that resulted in having
    more than 2 entries(more than 2 different numbers) in our Hash Map(in our
    current window).

    If it did, then keep shrinking the left boundary. Every time we "shrink" a
    left boundary we must decrement number of fruits, for that type of fruit,
    by one in our HashMap.

    At some point, by shrinking our left boundary, and therefore decrementing
    the number of fruits for that type, we'll have a value of 0 for a certain
    type.

    Once that happens, evict that entry from the HashMap and we'll, again, have
    a valid situation - Only 2 different numbers(type of fruits) are present
    in our current window.

    Now that our window is valid again, check if this window length is the
    longest so far.

    We'll do that with:

        result = std::max(result, R - L + 1); // window_len = R - L + 1


    At the end we'll just return the "result" variable.


*******************************************************************************
********************************** SIMULATION *********************************
*******************************************************************************

                        Input: fruits = [1,2,3,2,2]

                                 Hash Map
                            |  Key  :  Value |
                            +----------------+
                            |       /        |
                            +----------------+


===============================================================================

    1. R = 0

        fruits = [1, 2, 3, 2, 2]             Hash Map
                  0  1  2  3  4         |  Key  :  Value |
                  L                     +----------------+
                  R                     |   1   :   1    | // New entry
                                        +----------------+


===============================================================================

    2.  R = 1

        fruits = [1, 2, 3, 2, 2]             Hash Map
                  0  1  2  3  4         |  Key  :  Value |
                  L  R                  +----------------+
                                        |   1   :   1    |
                                        +----------------+
                                        |   2   :   1    | // New entry
                                        +----------------+

         result = max(result, R - L + 1) ==> max(0, 2) ==> 2 // New Max

===============================================================================

    3.  R = 2

        -------------------------------------------------------------------

        a)
            fruits = [1, 2, 3, 2, 2]             Hash Map
                      0  1  2  3  4         |  Key  :  Value |
                      L     R               +----------------+
                                            |   1   :   1    |
                                            +----------------+
                                            |   2   :   1    |
                                            +----------------+
                                            |   3   :   1    | // New entry
                                            +----------------+

            Since there are more than two entries in the HashMap, we must
            decrement fruits[L]-- and move L by one to the right: L++;

            Now we have this: (situation in b) )

        -------------------------------------------------------------------

        b)

            fruits = [1, 2, 3, 2, 2]             Hash Map
                      0  1  2  3  4         |  Key  :  Value |
                         L  R               +----------------+
                                            |   2   :   1    |
                                            +----------------+
                                            |   3   :   1    |
                                            +----------------+

            Now the window, again, contains less than or equal to two
            distinct numbers.

         result = max(result, R - L + 1) ==> max(2, 2) ==> 2

===============================================================================

    4.  R = 3

        fruits = [1, 2, 3, 2, 2]             Hash Map
                  0  1  2  3  4         |  Key  :  Value |
                     L     R            +----------------+
                                        |   2   :   2    | // Updated value
                                        +----------------+
                                        |   3   :   1    |
                                        +----------------+

            Now the window, again, contains less than or equal to two
            distinct numbers.

         result = max(result, R - L + 1) ==> max(2, 3) ==> 3 // New Max

===============================================================================

    5.  R = 4

        fruits = [1, 2, 3, 2, 2]             Hash Map
                  0  1  2  3  4         |  Key  :  Value |
                     L        R         +----------------+
                                        |   2   :   3    | // Updated value
                                        +----------------+
                                        |   3   :   1    |
                                        +----------------+

            The window, still, contains
            less than or equal to 2 distinct numbers.

         result = max(result, R - L + 1) ==> max(3, 4) ==> 4 // New Max

===============================================================================

    R is out of bounds, i.e. the "for loop" ended, return "result" variable.

*/

/* Time  Beats: 58.40% */
/* Space Beats: 73.02% */

/* Time  Complexity: O(n) */
/* Space Complexity: O(n) */
class Solution {
public:
    int totalFruit(vector<int>& fruits)
    {
        int result = INT_MIN;
        std::unordered_map<int, int> umap;

        int left  = 0;
        int right = 0;

        while (right < fruits.size())
        {
            umap[fruits[right]]++;

            while (umap.size() > 2)
            {
                umap[fruits[left]]--;

                if (umap[fruits[left]] == 0)
                    umap.erase(fruits[left]);

                left++;
            }

            result = std::max(result, right - left + 1);

            right++;
        }

        return result;
    }
};




/*
    ------------
    --- IDEA ---
    ------------

    Essentially the same Solution as the one above, but written in a much worse
    way.

    I wanted to keep both, so that you can compare and see how to optimize in
    general. This Solution is, maybe, a bit more intuitive, but much harder to
    read and, therefore, grasp.

*/

/* Time  Beats: 96.89% */
/* Space Beats: 88.69% */

/* Time  Complexity: O(n) */
/* Space Complexity: O(1) */
class Solution_Messy {
public:
    int totalFruit(vector<int>& fruits)
    {
        int type_1 = -1;
        int type_2 = -1;

        int basket_1 = 0;
        int basket_2 = 0;

        int left  = 0;
        int right = 0;

        int max = 0;

        while (right < fruits.size())
        {
            while (!match_one_basket(type_1, type_2, fruits[right]))
            {
                if (type_1 == -1)
                {
                    type_1 = fruits[right];
                    continue;
                }
                else if (type_2 == -1)
                {
                    type_2 = fruits[right];
                    continue;
                }

                if (fruits[left] == type_1)
                {
                    basket_1--;

                    if (basket_1 == 0)
                        type_1 = fruits[right];
                }
                else if (fruits[left] == type_2)
                {
                    basket_2--;

                    if (basket_2 == 0)
                        type_2 = fruits[right];
                }

                left++;
            }

            if (fruits[right] == type_1)
                basket_1++;
            else
                basket_2++;

            max = std::max(max, right - left + 1);

            right++;
        }

        return max;
    }

private:
    bool match_one_basket(int& type_1, int& type_2, int current_type)
    {
        return type_1 == current_type || type_2 == current_type;
    }
};
