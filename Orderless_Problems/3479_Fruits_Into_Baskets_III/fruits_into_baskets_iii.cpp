/*
    ==============
    === MEDIUM ===
    ==============

    =============================
    3479) Fruits Into Baskets III
    =============================

    ============
    Description:
    ============

    You are given two arrays of integers, fruits and baskets, each of length n,
    where fruits[i] represents the quantity of the ith type of fruit, and
    baskets[j] represents the capacity of the jth basket.

    From left to right, place the fruits according to these rules:

        + Each fruit type must be placed in the leftmost available basket with
          a capacity greater than or equal to the quantity of that fruit type.

        + Each basket can hold only one type of fruit.

        + If a fruit type cannot be placed in any basket, it remains unplaced.

    Return the number of fruit types that remain unplaced after all possible
    allocations are made.

    =============================================================================
    FUNCTION: int numOfUnplacedFruits(vector<int>& fruits, vector<int>& baskets);
    =============================================================================

    ==========================================================================
    ================================ EXAMPLES ================================
    ==========================================================================

    --- Example 1 ---
    Input: fruits = [4,2,5], baskets = [3,5,4]
    Output: 1
    Explanation:
        fruits[0] = 4 is placed in baskets[1] = 5.
        fruits[1] = 2 is placed in baskets[0] = 3.
        fruits[2] = 5 cannot be placed in baskets[2] = 4.

    Since one fruit type remains unplaced, we return 1.


    --- Example 2 ---
    Input: fruits = [3,6,1], baskets = [6,4,7]
    Output: 0
    Explanation:
        fruits[0] = 3 is placed in baskets[0] = 6.
        fruits[1] = 6 cannot be placed in baskets[1] = 4
        (insufficient capacity) but can be placed in the next available basket,
        baskets[2] = 7.
        fruits[2] = 1 is placed in baskets[1] = 4.

    Since all fruits are successfully placed, we return 0.


    *** Constraints ***
    n == fruits.length == baskets.length
    1 <= n <= 10^5
    1 <= fruits[i], baskets[i] <= 10^9

*/

#include <cmath>
#include <vector>
using namespace std;


/*
    ------------
    --- IDEA ---
    ------------

    TODO

*/

/* Time  Beats: 30.64% */
/* Space Beats: 98.89% */

/* Time  Complexity: O(N * sqrt(N)) */
/* Space Complexity: O(sqrt(N))     */
class Solution {
public:
    int numOfUnplacedFruits(vector<int>& fruits, vector<int>& baskets)
    {
        const int N = baskets.size();
        const int SQRT_OF_N = sqrt(N);

        int total_sections = (N + SQRT_OF_N - 1) / SQRT_OF_N;
        int unplaced = 0;

        vector<int> section_max_capacity(total_sections);

        for (int i = 0; i < N; i++)
        {
            section_max_capacity[i / SQRT_OF_N] = max(section_max_capacity[i / SQRT_OF_N], baskets[i]);
        }

        for (const int& fruit : fruits)
        {
            int is_unplaced  = 1;
            int curr_section = 0;

            while (curr_section < total_sections)
            {
                if (section_max_capacity[curr_section] < fruit)
                {
                    curr_section++;
                    continue;
                }

                bool is_chosen_basket = false;
                section_max_capacity[curr_section] = 0;

                for (int i = 0; i < SQRT_OF_N; i++)
                {
                    int basket_position = curr_section * SQRT_OF_N + i;

                    if (basket_position < N && baskets[basket_position] >= fruit && !is_chosen_basket)
                    {
                        baskets[basket_position] = 0;
                        is_chosen_basket = true;
                    }

                    if (basket_position < N)
                    {
                        section_max_capacity[curr_section] = max(section_max_capacity[curr_section], baskets[basket_position]);
                    }
                }

                is_unplaced = 0;
                break;
            }

            unplaced += is_unplaced;
        }

        return unplaced;
    }
};
