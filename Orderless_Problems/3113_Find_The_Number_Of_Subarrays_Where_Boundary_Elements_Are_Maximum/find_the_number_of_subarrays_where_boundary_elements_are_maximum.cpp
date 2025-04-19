/*
    ============
    === HARD ===
    ============

    ======================================================================
    3113) Find the Number of Subarrays Where Boundary Elements Are Maximum
    ======================================================================

    ============
    Description:
    ============

    You are given an array of positive integers nums.

    Return the number of subarrays of nums, where the first and the last
    elements of the subarray are equal to the largest element in the subarray.

    =========================================================
    FUNCTION: long long numberOfSubarrays(vector<int>& nums);
    =========================================================

    ==========================================================================
    ================================ EXAMPLES ================================
    ==========================================================================

    --- Example 1 ---
    Input: nums = [1,4,3,3,2]
    Output: 6
    Explanation:
    There are 6 subarrays which have the first and the last elements equal to
    the largest element of the subarray:
        subarray [1,4,3,3,2], with its largest element 1. The first element is 1 and the last element is also 1.
        subarray [1,4,3,3,2], with its largest element 4. The first element is 4 and the last element is also 4.
        subarray [1,4,3,3,2], with its largest element 3. The first element is 3 and the last element is also 3.
        subarray [1,4,3,3,2], with its largest element 3. The first element is 3 and the last element is also 3.
        subarray [1,4,3,3,2], with its largest element 2. The first element is 2 and the last element is also 2.
        subarray [1,4,3,3,2], with its largest element 3. The first element is 3 and the last element is also 3.
    Hence, we return 6.


    --- Example 2 ---
    Input: nums = [3,3,3]
    Output: 6
    Explanation:
    There are 6 subarrays which have the first and the last elements equal to
    the largest element of the subarray:
        subarray [3,3,3], with its largest element 3. The first element is 3 and the last element is also 3.
        subarray [3,3,3], with its largest element 3. The first element is 3 and the last element is also 3.
        subarray [3,3,3], with its largest element 3. The first element is 3 and the last element is also 3.
        subarray [3,3,3], with its largest element 3. The first element is 3 and the last element is also 3.
        subarray [3,3,3], with its largest element 3. The first element is 3 and the last element is also 3.
        subarray [3,3,3], with its largest element 3. The first element is 3 and the last element is also 3.
    Hence, we return 6.


    --- Example 3 ---
    Input: nums = [1]
    Output: 1
    Explanation:
    There is a single subarray of nums which is [1], with its largest element 1.
    The first element is 1 and the last element is also 1.
    Hence, we return 1.


    *** Constraints ***
    1 <= nums.length <= 10^5
    1 <= nums[i] <= 10^9

*/

#include <stack>
#include <vector>
using namespace std;

/*
    ------------
    --- IDEA ---
    ------------

    Once you lay this example in front of yourself, it should be clear what the
    right approach is:

        nums = [4, 3, 2, 1, 1, 2, 3, 4]

    TODO

*/

/* Time  Beats: 71.51% */
/* Space Beats: 76.54% */

/* Time  Complexity: O(N) */
/* Space Complexity: O(N) */
class Solution {
public:
    long long numberOfSubarrays(vector<int>& nums)
    {
        const int N = nums.size();
        unsigned long long result = N;

        stack<pair<unsigned long long, long long>> stack;

        stack.push( {nums[0], 1} );

        for (int i = 1; i < N; i++)
        {
            if ( ! stack.empty())
            {
                while ( ! stack.empty() && stack.top().first < nums[i])
                    stack.pop();

                if ( ! stack.empty() && stack.top().first == nums[i])
                {
                    result += stack.top().second;
                    stack.top().second++;
                }
                else
                    stack.push( {nums[i], 1} );
            }
            else
                stack.push( {nums[i], 1} );
        }

        return result;
    }
};
