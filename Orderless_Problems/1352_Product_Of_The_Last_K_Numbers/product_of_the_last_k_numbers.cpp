/*
    ==============
    === MEDIUM ===
    ==============

    ===================================
    1352) Product of the Last K Numbers
    ===================================

    ============
    Description:
    ============

    Design an algorithm that accepts a stream of integers and retrieves the
    product of the last k integers of the stream.

    Implement the ProductOfNumbers class:

        + ProductOfNumbers() Initializes the object with an empty stream.

        + void add(int num) Appends the integer num to the stream.

        + int getProduct(int k) Returns the product of the last k numbers in
          the current list. You can assume that always the current list has at
          least k numbers.

    The test cases are generated so that, at any time, the product of any
    contiguous sequence of numbers will fit into a single 32-bit integer
    without overflowing.


    ---------------
    -- Follow Up --
    ---------------

    Can you implement both GetProduct and Add to work in O(1) time complexity
    instead of O(k) time complexity?


    ===============================
    CLASS:
    class ProductOfNumbers {
    public:
        ProductOfNumbers()
        {

        }

        void add(int num)
        {

        }

        int getProduct(int k)
        {

        }
    };
    ===============================

    ==========================================================================
    ================================ EXAMPLES ================================
    ==========================================================================

    --- Example 1 ---
    Input
    ["ProductOfNumbers","add","add","add","add","add","getProduct","getProduct","getProduct","add","getProduct"]
    [[],[3],[0],[2],[5],[4],[2],[3],[4],[8],[2]]

    Output
    [null,null,null,null,null,null,20,40,0,null,32]

    Explanation
    ProductOfNumbers productOfNumbers = new ProductOfNumbers();
    productOfNumbers.add(3);        // [3]
    productOfNumbers.add(0);        // [3,0]
    productOfNumbers.add(2);        // [3,0,2]
    productOfNumbers.add(5);        // [3,0,2,5]
    productOfNumbers.add(4);        // [3,0,2,5,4]
    productOfNumbers.getProduct(2); // return 20. The product of the last 2
   numbers is 5 * 4 = 20 productOfNumbers.getProduct(3); // return 40. The
   product of the last 3 numbers is 2 * 5 * 4 = 40
    productOfNumbers.getProduct(4); // return 0. The product of the last 4
   numbers is 0 * 2 * 5 * 4 = 0 productOfNumbers.add(8);        // [3,0,2,5,4,8]
    productOfNumbers.getProduct(2); // return 32. The product of the last 2
   numbers is 4 * 8 = 32



    *** Constraints ***
    0 <= num <= 100
    1 <= k <= 4 * 10^4
    At most 4 * 104 calls will be made to add and getProduct.
    The product of the stream at any point in time will fit in a 32-bit integer.

*/

#include <vector>
using namespace std;

/*
    ------------
    --- IDEA ---
    ------------

    Brute-Force.

*/

/* Time  Beats: 17.02% */
/* Space Beats: 56.86% */
class ProductOfNumbers {
public:
    ProductOfNumbers()
    {

    }

    // O(1)
    void add(int num)
    {
        vec.push_back(num);
    }

    // O(k)
    int getProduct(int k)
    {
        int product = 1;

        for (int i = vec.size()-1; i >= vec.size()-k && i >= 0; i--)
            product *= vec[i];

        return product;
    }

private:
    vector<int> vec;
};




/*
    ------------
    --- IDEA ---
    ------------

    The only tricky part here is how we handle number 0. In this case we're
    resetting our prefix_product, however that leaves us with a potential
    problem which appears once k is GREATER than the number of last non-zero
    elements.

    For example:

        4, 8, 9, 2, 0, 4, 2, 3
                             ^
                             |
                       first from the back

        k = 5 or k = 6


    We're told one important thing for the getProduct function:

        "You can assume that always the current list has at least k numbers."

    However, since we're RESETTING our "size" variable, that will NOT be the
    case anymore. Therefore, we have to be careful with it.

    We're going to handle it by always checking if there are less last non-zero
    elements than k and if that's true, we just return 0.

    If this confuses you, look at the example:

    For example:

        4, 8, 9, 2, 0, 4, 2, 3
                             ^
                             |
                       first from the back


        For k = 4 ork = 5 or k = 6, our result SHOULD be 0.

        For k = 6: 9 * 2 * 0 * 4 * 2 * 3 = 0
        For k = 5:     2 * 0 * 4 * 2 * 3 = 0
        For k = 4:         0 * 4 * 2 * 3 = 0

        However, for k = 3 or k = 2 or k = 1, we should return: 24, 6, 3
        respectively.

        For k = 3: 4 * 2 * 3 = 24
        For k = 2:     2 * 3 =  6
        For k = 1:         3 =  3

    If k is NOT greater than our size of last non-zero elements, then simply
    return:

        return prefix_product[size] / prefix_product[size - k];

*/

/* Time  Beats: 38.79% */
/* Space Beats: 93.67% */
class ProductOfNumbers_Follow_Up {
public:
    ProductOfNumbers_Follow_Up ()
    {
        prefix_product.push_back(1);
        size = 0;
    }

    // O(1)
    void add(int num)
    {
        if (num == 0)
        {
            prefix_product = {1};
            size = 0;
        }
        else
        {
            prefix_product.push_back(prefix_product[size] * num);
            size++;
        }
    }

    // O(1)
    int getProduct(int k)
    {
        // This never happens according to Constraints, but we reset "size"
        if (k > size)
            return 0;

        return prefix_product[size] / prefix_product[size - k];
    }

private:
    vector<int> prefix_product;
    int size = 0;
};
