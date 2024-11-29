#include <iostream>
#include <vector>

/*
    ==============
    === MEDIUM ===
    ==============

    =================================
    238) Product of Array Except Self
    =================================

    ============
    Description:
    ============

    Given an integer array "nums", return an array "answer" such that answer[i]
    is equal to the product of all the elements of "nums" except nums[i].

    The product of any prefix or suffix of "nums" is guaranteed to fit in a
    32-bit integer.

    You must write an algorithm that runs in O(n) time and without using the
    division operation.

    Follow up: Can you solve the problem in O(1) extra space complexity?
    (The output array does NOT count as extra space for space complexity
    analysis)

    ===========================================================
    FUNCTION: vector<int> productExceptSelf(vector<int>& nums);
    ===========================================================

    ==========================================================================
    ================================ EXAMPLES ================================
    ==========================================================================

    --- Example 1 ---
    Input:  nums = [1, 2, 3, 4]
    Output: [24, 12, 8, 6]

    --- Example 2 ---
    Input:  nums = [-1, 1, 0, -3, 3]
    Output: [0, 0, 9, 0, 0]

    *** Constraints ***
    2 <= nums.length <= 10^5
    -30 <= nums[i] <= 30
    The product of any prefix or suffix of "nums" is guaranteed to fit in a
    32-bit integer.

*/


/*
    ------------
    --- IDEA ---
    ------------

    Finding Prefix Product and Suffix Product

    Similar to finding Prefix Sum Array, here we would intend to find the
    Prefix Product Array and Suffix Product Array for our original array, i.e.
        prefix[i] = prefix[i - 1] * nums[i - 1]
    (yes, we multiply with nums[i - 1] and not with nums[i] on purpose) and
    similarly:
        suffix[i] = suffix[i + 1] * nums[i + 1]

    Now, at any index 'i' our final results "results[i]" would be given by:
        results[i] = prefix[i] * suffix[i]

    Why? Because "prefix[i] * suffix[i]" contains product of every element
    before 'i' and every element after 'i' but not the element at index 'i'
    (and that is the reason why we excluded a[i] in our prefix and suffix
    product).

*/

/* Time  Beats: 54.36% */
/* Space Beats: 20.88% */

/* Time  Complexity: O(n) */
/* Space Complexity: O(n) */
class Solution{
public:
    std::vector<int> productExceptSelf(std::vector<int>& nums)
    {
        int n = nums.size();
        std::vector<int> prefix(n, 1);
        std::vector<int> suffix(n, 1);

        for (int i = 1; i < n; i++)
            prefix[i] = prefix[i - 1] * nums[i - 1];

        for (int i = n - 2; i >= 0; i--)
            suffix[i] = suffix[i + 1] * nums[i + 1];

        std::vector<int> results(n, 1);
        for (int i = 0; i < n; i++)
            results[i] = prefix[i] * suffix[i];

        return results;
    }
};




/*
    ------------
    --- IDEA ---
    ------------

    Follow-Up:
    Directly store the product of prefix and suffix into the final "results"
    array(vector).

    The logic is, we don't actually need separate arrays to store prefix
    product and suffix products, we can store directly into our final "results"
    array(vector).

    Now the Time Complexity reduces from O(n) to O(1)


    Let's look at an example:
    [2, 3, 4, 5]

    Regarding the third number '4' the product of array except '4' is 2 * 3 * 5
    which consists of two parts:
        Prefix:  2 * 3
        Suffix: 5

    The product is left * right. We can get lefts and rights:
        Numbers:        2     3     4     5
        Prefixes:       1     2    2*3  2*3*4
        Suffixes:    3*4*5   4*5    5     1

    We can calculate prefixes and suffixes in 2 loops.

    We store prefixes in "answer".
    If we were to allocate a new array for suffixes the Space complexity would
    be O(n).

    To make it O(1), we just need to store it in a variable which is "suffix"
    and multiply with the "results" array.


    The *Suffix* part could be written like this as well:
    (It's maaybe easier to read, I dont know)

    // Suffix
    int suffix = 1;
    for (int i = n - 2; i >= 0; i--)
    {
        results[i] *= nums[i + 1] * suffix;
        suffix     *= nums[i + 1];
    }

*/

/* Time  Beats: 92.10% */
/* Space Beats: 85.19% */

/* Time  Complexity: O(n) */
/* Space Complexity: O(1) */
class Solution_Follow_Up{
public:
    std::vector<int> productExceptSelf(std::vector<int>& nums)
    {
        int n = nums.size();
        std::vector<int> results(n, 1);

        /* Prefix */
        for (int i = 1; i < n; i++)
            results[i] = results[i - 1] * nums[i - 1];

        /* Suffix */
        int suffix = 1;
        for (int i = n - 1; i >= 0; i--)
        {
            results[i] *= suffix;
            suffix    *= nums[i];
        }

        return results;
    }
};


int
main()
{
    Solution sol;
    Solution_Follow_Up sol_followup;

    /* Example 1 */
    std::vector<int> nums {1, 2, 3, 4};

    /* Example 2 */
    // std::vector<int> nums {-1, 1, 0, -3, 3};

    /* Example 3 */
    // std::vector<int> nums {5, 4, -1, 2, 3};

    std::cout << "\n\t====================================";
    std::cout << "\n\t=== PRODUCT OF ARRAY EXCEPT SELF ===";
    std::cout << "\n\t====================================\n";


    /* Write Input */
    bool first = true;
    std::cout << "\n\tnums: [";
    for (auto x: nums)
    {
        if (!first)
            std::cout << ", ";

        std::cout << x;
        first = false;
    }
    std::cout << "]\n";


    /* Solution */
    // std::vector<int> results = sol.productExceptSelf(nums);
    std::vector<int> results = sol_followup.productExceptSelf(nums);

    /* Write Output */

    first = true;
    std::cout << "\n\tresults: [";
    for (auto x: results)
    {
        if (!first)
            std::cout << ", ";

        std::cout << x;
        first = false;
    }
    std::cout << "]\n\n";



    return 0;
}
