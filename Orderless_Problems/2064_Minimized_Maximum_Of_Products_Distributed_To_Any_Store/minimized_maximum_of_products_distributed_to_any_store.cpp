#include <iostream>
#include <vector>
#include <cmath>

/*
    ==============
    === MEDIUM ===
    ==============

    ============================================================
    2064) Minimized Maximum of Products Distributed to Any Store
    ============================================================

    ============
    Description:
    ============

    You are given an integer n indicating there are n specialty retail stores.
    There are m product types of varying amounts, which are given as a
    0-indexed integer array quantities, where quantities[i] represents the
    number of products of the ith product type.

    You need to distribute all products to the retail stores following these
rules:

        + A store can only be given at most one product type but can be given
          any amount of it.

        + After distribution, each store will have been given some number of
          products (possibly 0). Let x represent the maximum number of products
          given to any store. You want x to be as small as possible, i.e., you
          want to minimize the maximum number of products that are given to any
          store.

    Return the minimum possible x.

    ===============================================================
    FUNCTION: int minimizedMaximum(int n, vector<int>& quantities);
    ===============================================================

    ==========================================================================
    ================================ EXAMPLES ================================
    ==========================================================================

    --- Example 1 ---
    Input: n = 6, quantities = [11,6]
    Output: 3
    Explanation: One optimal way is:
    - The 11 products of type 0 are distributed to the first four stores in
      these amounts: 2, 3, 3, 3

    - The 6 products of type 1 are distributed to the other two stores in these
      amounts: 3, 3

    The maximum number of products given to any store is max(2, 3, 3, 3, 3, 3) = 3.


    --- Example 2 ---
    Input: n = 7, quantities = [15,10,10]
    Output: 5
    Explanation: One optimal way is:
    - The 15 products of type 0 are distributed to the first three stores in
      these amounts: 5, 5, 5

    - The 10 products of type 1 are distributed to the next two stores in these
      amounts: 5, 5

    - The 10 products of type 2 are distributed to the last two stores in these
      amounts: 5, 5

    The maximum number of products given to any store is max(5, 5, 5, 5, 5, 5, 5) = 5.


    --- Example 3 ---
    Input: n = 1, quantities = [100000]
    Output: 100000
    Explanation: The only optimal way is:
    - The 100000 products of type 0 are distributed to the only store.
    The maximum number of products given to any store is max(100000) = 100000.


    *** Constraints ***
    m == quantities.length
    1 <= m <= n <= 10^5
    1 <= quantities[i] <= 10^5

*/

/*
    ------------
    --- IDEA ---
    ------------

    This one is VERY similar to LeetCode: "875. Koko Eating Bananas"

    Let's think about the Brute-Force approach first and then the Optimization
    will be obvious.

    Consider Example 1:

        Input: n = 6, quantities = [11,6]

        _ _ _ _ _ _     [11, 6]


        We don't know what is the answer, but we know that the minimum quantity
        that can be maximum, in theory, is 1.

        On the other hand, we also know that the maximum quantity that can be
        maximum is 11 in this case.

        Why 11? Because that is the biggest quantity we're given for this
        Example.


        So the Brute-Force way would be to try having quantity of 1 to be
        the maximum quantity of all the stores.

        If "quantity of 1" is the biggest quantity in all the stores, we would
        be in this situation:

            1 1 1 1 1 1
            _ _ _ _ _ _     [11, 6]

        However, as we can see, we did NOT distribue each and every product,
        which is required. Therefore, we conclude "quantity of 1" CANNOT be
        the answer.

        Then, we try with "quantity of 2" as the maximum quantity in all of the
        stores:

            2 2 2 2 2 2
            _ _ _ _ _ _     [11, 6]

        Sum of all 2s is 12, which means we, once again, have NOT distribute
        each and every product.

        Let's move on to "quantity of 3" as the maximum quantity in all of the
        stores:

            2 3 3 3 3 3
            _ _ _ _ _ _     [11, 6]
            ^
            |
            ----- This 2 is NOT a mistake: 2 + 3 + 3 + 3 + 3 + 3 = 17, which
                  is the sum of all the products.

        Therefore, we conclude that we are able to distribute EACH and every
        product if the maximum quantity in any store is 3.


        But, do you see the unnecessary work here?
        Imagine if we a quantity of a single product to be 1000000 (1 million).

        We would, potentially go through thousands and thousands to tries to
        determine the result.

        This is where the Optimization comes in.


        We do NOT know what is the minimum quantity for which we can distribute
        all of the products and have that quantity as the maximum quantity,
        BUT(this is important), we know FOR A FACT that the quantity we're
        looking for is between:

                        1 and max_element of quantities.

        Therefore, instead of doing this work linearly, for each and every
        quantity, starting at 1, we can simply do a Binary Search and
        substantially improve the Time Complexity.

*/

/* Time  Beats: 30.71% */
/* Space Beats: 89.12% */

/* Time  Complexity: O(M * max_element(quantities)) */
/* Space Complexity: O(1)                           */
class Solution {
public:
    int minimizedMaximum(int n, vector<int>& quantities)
    {
        int result = 0;

        int left  = 1;
        int right = *max_element(quantities.begin(), quantities.end());

        while (left <= right)
        {
            int mid_curr_max_quantity = left + (right - left) / 2;

            if (can_distribute(n, quantities, mid_curr_max_quantity))
            {
                result = mid_curr_max_quantity; // Save result
                right = mid_curr_max_quantity - 1;
            }
            else
                left  = mid_curr_max_quantity + 1;
        }

        return result;
    }

private:
    bool can_distribute(int& n, vector<int>& quantities, int curr_max_quantity)
    {
        int stores = 0;

        for (const int& quantity : quantities)
            stores += std::ceil(1.0 * quantity / curr_max_quantity);

        return stores <= n;
    }
};
