/*
    ============
    === EASY ===
    ============

    ==========================================
    3318) Find X-Sum of All K-Long Subarrays I
    ==========================================

    ============
    Description:
    ============

    You are given an array nums of n integers and two integers k and x.

    The x-sum of an array is calculated by the following procedure:

    Count the occurrences of all elements in the array.
    Keep only the occurrences of the top x most frequent elements. If two
    elements have the same number of occurrences, the element with the bigger
    value is considered more frequent. Calculate the sum of the resulting array.

    Note that if an array has less than x distinct elements, its x-sum is the
    sum of the array.

    Return an integer array answer of length n - k + 1 where answer[i] is the
    x-sum of the subarray nums[i..i + k - 1].

    ================================================================
    FUNCTION: vector<int> findXSum(vector<int>& nums, int k, int x);
    ================================================================

    ==========================================================================
    ================================ EXAMPLES ================================
    ==========================================================================

    --- Example 1 ---
    Input: nums = [1,1,2,2,3,4,2,3], k = 6, x = 2
    Output: [6,10,12]
    Explanation:
    For subarray [1, 1, 2, 2, 3, 4],
    only elements 1 and 2 will be kept in the resulting array.
    Hence, answer[0] = 1 + 1 + 2 + 2.

    For subarray [1, 2, 2, 3, 4, 2],
    only elements 2 and 4 will be kept in the resulting array.
    Hence, answer[1] = 2 + 2 + 2 + 4. Note that 4 is kept in the array since it
    is bigger than 3 and 1 which occur the same number of times.

    For subarray [2, 2, 3, 4, 2, 3], only elements 2 and 3 are kept in the
    resulting array. Hence, answer[2] = 2 + 2 + 2 + 3 + 3.


    --- Example 2 ---
    Input: nums = [3,8,7,8,7,5], k = 2, x = 2
    Output: [11,15,15,15,12]
    Explanation:
    Since k == x, answer[i] is equal to the sum of the subarray nums[i..i + k - 1].


    *** Constraints ***
    1 <= n == nums.length <= 50
    1 <= nums[i] <= 50
    1 <= x <= k <= nums.length

*/

#include <algorithm>
#include <unordered_map>
#include <vector>
using namespace std;

/*
    ------------
    --- IDEA ---
    ------------

    This one is not as easy as one would expect for an EASY problem.

    It is not that difficult, but it composes of many parts.
    First of all, there will be exactly "N-k+1" windows.

    Each of those windows will differ from the other one by two elements.
    (leftmost element of the previous window will be excluded and a rightmost
    element of this current window will be included)

    Since that is the case, we do not have to count frequencies each time "from
    scratch". Insteac, we can simply use our previously calculated window,
    subtract the leftmost element because we're moving the window, and add a
    rightmost element from this new window.

    That way instead of having a Time Complexity, so far, of O((N-k+1) * k), we
    get to have only O(N-k+1).


    However, we're just about to realize that we actually MUST have a TC of:
    O((N-k+1) * k) because we need to create a vector "freq_elem" from our hash
    map, however, we're still improving our "wall clock time" and that is,
    essentially what matters the most.

    So, why do we need to create a vector freq_elem of our "map" if we already
    have our map?

    Because we need to take first 'x' ones, i.e. we need a MaxHeap. We cannot
    do that with "map", but we need the "map" nonetheless since we do NOT want
    to count the occurrences of the current windows each time, as we've
    discussed up above.

    But why are we creating a "vector" and not a "priority_queue"?
    Good question.

    In C++, working with MaxHeap, and Heaps in general, comes in two forms:
        1. Using "priority_queue", or
        2. Using "vector"

    If we use a vector, we can Heapify it in O(n) time.
    If we use a priority_queue, to Heapify it we can only push each element
    one-by-one, which takes O(n * logn) time.

    Therefore, if you can work with a vector, do that. Especially because our
    plan was never to pop each element from this MaxHeap, but only first x.

    Which means that if we use "vector" as a Heap, and we pop first x ones,
    that is FASTER than just creating "priority_queue", let alone pop x
    elements from "priority_queue".

    That's why we're using a "vector" as a MaxHeap.

    It's important to note that each time we are decrementing the frequency of
    the leftmost element we're about to shrink, it's very important to erase it
    if it's 0 after the decrementation.

    Also update "left" pointer by incrementing it by 1 afterwards.

    Also, since the last window will have "k + i" out of bounds, we need to
    prevent Out-Of-Bounds error by checking if it's withing the bounds of the
    array "nums".

*/

/* Time  Beats: 43.42% */
/* Space Beats: 81.28% */

/*
    N = size of "nums"
    k = size of the sliding window
    x = number of elements to sum
    M = number of distinct elements in the current window
*/
/* Time  Complexity: O((N - k + 1) * x * logM) */
/* Space Complexity: O(M)                      */
class Solution {
public:
    vector<int> findXSum(vector<int>& nums, int k, int x)
    {
        const int N = nums.size();
        vector<int> answer(N-k+1);
        int left  = 0;
        int right = k;

        unordered_map<int,int> umap;
        for (int i = 0; i < right; i++)
            umap[nums[i]]++;

        for (int i = 0; i < N-k+1; i++)
        {
            vector<pair<int,int>> freq_elem;
            for (const auto &[elem, freq] : umap)
                freq_elem.push_back( {freq, elem} );

            
            make_heap(freq_elem.begin(), freq_elem.end());

            for (int j = 0; j < x; j++)
            {
                if (freq_elem.empty())
                    break;

                std::pop_heap(freq_elem.begin(), freq_elem.end());  // Move max element to the end
                auto top = freq_elem.back();                        // Get the max element
                freq_elem.pop_back();                               // Actually remove the element

                answer[i] += top.first * top.second;
            }

            umap[nums[left]]--;
            if (umap[nums[left]] == 0)
                umap.erase(nums[left]);
            left++;
            
            if (k+i < N)
                umap[nums[k+i]]++;
        }

        return answer;
    }
};
