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

        You only have two baskets, and each basket can only hold a single type
        of fruit. There is no limit on the amount of fruit each basket can
        hold.  Starting from any tree of your choice, you must pick exactly one
        fruit from every tree (including the start tree) while moving to the
        right. The picked fruits must fit in one of your baskets.  Once you
        reach a tree with fruit that cannot fit in your baskets, you must stop.

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

    TODO

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
