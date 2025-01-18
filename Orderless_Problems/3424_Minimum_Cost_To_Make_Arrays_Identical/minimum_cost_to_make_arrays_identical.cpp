/*
    ==============
    === MEDIUM ===
    ==============

    ===========================================
    3424) Minimum Cost to Make Arrays Identical
    ===========================================

    ============
    Description:
    ============

    You are given two integer arrays arr and brr of length n, and an integer k.
    You can perform the following operations on arr any number of times:

        + Split arr into any number of contiguous subarrays and rearrange these
          subarrays in any order. This operation has a fixed cost of k.

        + Choose any element in arr and add or subtract a positive integer x to
          it. The cost of this operation is x.

    Return the minimum total cost to make arr equal to brr.

    A subarray is a contiguous non-empty sequence of elements within an array.

    =============================================================================
    FUNCTION: long long minCost(vector<int>& arr, vector<int>& brr, long long k);
    =============================================================================

    ==========================================================================
    ================================ EXAMPLES ================================
    ==========================================================================

    --- Example 1 ---
    Input: arr = [-7,9,5], brr = [7,-2,-5], k = 2
    Output: 13
    Explanation:
        Split arr into two contiguous subarrays: [-7] and [9, 5] and rearrange them as [9, 5, -7], with a cost of 2.
        Subtract 2 from element arr[0]. The array becomes [7, 5, -7]. The cost of this operation is 2.
        Subtract 7 from element arr[1]. The array becomes [7, -2, -7]. The cost of this operation is 7.
        Add 2 to element arr[2]. The array becomes [7, -2, -5]. The cost of this operation is 2.

    The total cost to make the arrays equal is 2 + 2 + 7 + 2 = 13.


    --- Example 2 ---
    Input: arr = [2,1], brr = [2,1], k = 0
    Output: 0
    Explanation:
    Since the arrays are already equal, no operations are needed, and the total cost is 0.


    *** Constraints ***
    1 <= arr.length == brr.length <= 10^5
    0 <= k <= 2 * 10^10
    -10^5 <= arr[i] <= 10^5
    -10^5 <= brr[i] <= 10^5

*/

#include <algorithm>
#include <vector>
using namespace std;


/*
    ------------
    --- IDEA ---
    ------------

    It's crucial to be very careful when reading. When they told us this:

        + Split arr into any number of contiguous subarrays and rearrange these
          subarrays in any order. This operation has a fixed cost of k.

    That literally means we are allowed to sort.
    How?

    Imagine that we didn't split it and we just rearranged it. That's a basic
    sort.

    However, now let's look how to minimize the result.
    Can we just be greedy?

    Yes!

    Literally smallest element from arr should be compared to the smallest
    element of brr and so on. Largest element from arr should be compared to
    the largest element of brr.

    That means we have to sort both arrays either increasingly or decreasingly.

    However, what if brr is ALREADY sorted in some way?
    What if brr is already sorted but in DECREASING order?

    In that case we don't want to spend time and sort both brr and arr to be
    increasing, instead it would be much better to just sort arr to follow the
    same apttern, that is to be DECREASING as well.

    However, if "brr" is NOT in DECREASING order, then we ought to sort both of
    them in INCREASING order.


    But there's a small caveat. It could be true that, because of cost 'k',
    it's better NOT to be greedy and to just find absolute differences of
    elements in both arrays as is, without rearranging anything.

    That way we don't get out "penalty" of 'k' and thus have a smaller result.

    Also if the order or "arr" ALREADY matches our given "brr" order, then
    we OUGHT NOT to rearrange and thus we can circumvent the penatly.

    But, if you consider it closer, that case is covered in this NON-GREEDY
    approach where we find the differences of elements as they come, without
    modifying.

*/

/* Time  Beats: 33.33% */
/* Space Beats: 33.33% */

/* Time  Complexity: O(n * logn) */
/* Space Complexity: O(n)        */
class Solution {
public:
    long long minCost(vector<int>& arr, vector<int>& brr, long long k)
    {
        const int N = arr.size();

        long long result = k; // For rearranging

        vector<int> copy_arr = arr;

        vector<int> incr_brr = brr;
        vector<int> decr_brr = brr;

        sort(incr_brr.begin(), incr_brr.end());
        sort(decr_brr.begin(), decr_brr.end(), greater<int>());

        bool flag_decr = false;
        if (decr_brr == brr)
        {
            flag_decr = true;
            sort(copy_arr.begin(), copy_arr.end(), greater<int>());
        }
        else
        {
            sort(copy_arr.begin(), copy_arr.end());
        }

        // if (arr == copy_arr)
            // result -= k; // We didn't need to sort

        for (int i = 0; i < N; i++)
        {
            result += abs(copy_arr[i] - (flag_decr ? decr_brr[i] : incr_brr[i]));
        }

        long long without_sorting = 0;
        for (int i = 0; i < N; i++)
        {
            without_sorting += abs(arr[i] - brr[i]);
        }

        return min(result, without_sorting);
    }
};
