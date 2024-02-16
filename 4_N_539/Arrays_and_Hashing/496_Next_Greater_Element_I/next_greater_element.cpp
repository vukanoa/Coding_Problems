#include <iostream>
#include <vector>
#include <unordered_map>
#include <stack>

/*
    ============
    === EASY ===
    ============

    ===========================
    496) Next Greater Element I
    ===========================

    ============
    Description:
    ============

    The next greater element of some element x in an array is the first greater
    element that is to the right of x in the same array.

    You are given two distinct 0-indexed integer arrays nums1 and nums2, where
    nums1 is a subset of nums2.

    For each 0 <= i < nums1.length, find the index j such that nums1[i] ==
    nums2[j] and determine the next greater element of nums2[j] in nums2. If
    there is no next greater element, then the answer for this query is -1.

    Return an array ans of length nums1.length such that ans[i] is the next
    greater element as described above.

    =================================================================================
    FUNCTION: vector<int> nextGreaterElement(vector<int>& nums1, vector<int>& nums2);
    =================================================================================

    ==========================================================================
    ================================ EXAMPLES ================================
    ==========================================================================

    --- Example 1 ---
    Input: nums1 = [4,1,2], nums2 = [1,3,4,2]
    Output: [-1,3,-1]
    Explanation: The next greater element for each value of nums1 is as follows:
    - 4 is underlined in nums2 = [1,3,4,2]. There is no next greater element,
      so the answer is -1.
    - 1 is underlined in nums2 = [1,3,4,2]. The next greater element is 3.
    - 2 is underlined in nums2 = [1,3,4,2]. There is no next greater element,
      so the answer is -1.


    --- Example 2 ---
    Input: nums1 = [2,4], nums2 = [1,2,3,4]
    Output: [3,-1]
    Explanation: The next greater element for each value of nums1 is as
    follows:
    - 2 is underlined in nums2 = [1,2,3,4]. The next greater element is 3.
    - 4 is underlined in nums2 = [1,2,3,4]. There is no next greater element,
      so the answer is -1.



    *** Constraints ***
    1 <= nums1.length <= nums2.length <= 1000
    0 <= nums1[i], nums2[i] <= 10^4
    All integers in nums1 and nums2 are unique.
    All the integers of nums1 also appear in nums2.

*/

/*
    ------------
    --- IDEA ---
    ------------

    TODO

    Both Solutions are essentially the same, thought this first one is more
    verbose, hence the name.

    It doesn't "skip" the steps, therefore it's a bit easier to read for
    people who are seeing this for the first time.

*/

/* Time  Beats: 89.77% */
/* Space Beats:  7.60% */

/* Time  Complexity: O(M + N) */
/* Space Complexity: O(N) */
class Solution_1 {
public:
    std::vector<int> nextGreaterElement(std::vector<int>& nums1, std::vector<int>& nums2)
    {
        int m = nums1.size();
        int n = nums2.size();

        std::stack<int> stack; // Monotonicly Decreasing Stack

        std::unordered_map<int, int> umap; // Element from nums2 to its index
        std::vector<int> next_greater(n, -1);

        for (int j = n-1; j >=0; j--)
        {
            umap.insert({nums2[j], j}); // Every element is distinct

            while (!stack.empty() && nums2[j] > stack.top())
                stack.pop();

            if (!stack.empty())
                next_greater[j] = stack.top();

            stack.push(nums2[j]);
        }

        std::vector<int> result(m, -1);

        for (int i = 0; i < m; i++)
            result[i] = next_greater[umap[nums1[i]]];

        return result;
    }
};




/*
    ------------
    --- IDEA ---
    ------------

    Same as above, written in a bit different way.

*/

/* Time  Beats:   100% */
/* Space Beats: 58.84% */

/* Time  Complexity: O(M + N) */
/* Space Complexity: O(N) */
class Solution_2 {
public:
    std::vector<int> nextGreaterElement(std::vector<int>& nums1, std::vector<int>& nums2)
    {
        if (nums1.empty() || nums2.empty())
            return {};

        int M = nums1.size();
        int N = nums2.size();

        std::vector<int> monotonic_stack;
        std::unordered_map<int, int> umap;

        for (int i = N - 1; i >= 0; i--)
        {
            while (!monotonic_stack.empty() && monotonic_stack.back() < nums2[i])
                monotonic_stack.pop_back();

            if (monotonic_stack.empty())
                umap.insert({nums2[i], -1});
            else
                umap.insert({nums2[i], monotonic_stack.back()});

            monotonic_stack.push_back(nums2[i]);
        }

        std::vector<int> results(M, -1);
        for (int i = 0; i < M; i++)
            results[i] = umap.at(nums1[i]);

        return results;
    }
};
