#include <iostream>

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

/* Time  Beats: 54.69% */
/* Space Beats: 32.05% */

/* Time  Complexity: O(n) */
/* Space Complexity: O(1) */ // At worst 2 elements in a Hash Map
class Solution {
public:
    int totalFruit(vector<int>& fruits)
    {
        if (fruits.size() == 1)
            return 1;

        std::unordered_map<int, int> umap;

        if (fruits[0] == fruits[1])
            umap.insert({fruits[0], 2});
        else
        {
            umap.insert({fruits[0], 1});
            umap.insert({fruits[1], 1});
        }

        int left  = 0;
        int right = 2;
        int total = right - left;
        while (right < fruits.size())
        {
            if (umap.count(fruits[right]))
                umap[fruits[right]]++;
            else
            {
                while (umap.size() == 2)
                {
                    umap[fruits[left]]--;

                    if (umap[fruits[left]] == 0)
                        umap.erase(fruits[left]);

                    left++;
                }

                umap.insert({fruits[right], 1});
            }

            total = std::max(total, right - left + 1);
            right++;
        }

        return total;
    }
};
