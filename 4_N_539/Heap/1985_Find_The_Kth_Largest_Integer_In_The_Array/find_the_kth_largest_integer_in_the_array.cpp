#include <iostream>
#include <vector>
#include <queue>

/*
    ==============
    === MEDIUM ===
    ==============

    ===============================================
    1985) Find the Kth Largest Integer in the Array
    ===============================================

    ============
    Description:
    ============

    You are given an array of strings nums and an integer k. Each string in
    nums represents an integer without leading zeros.

    Return the string that represents the kth largest integer in nums.

    Note: Duplicate numbers should be counted distinctly. For example, if nums
    is ["1","2","2"], "2" is the first largest integer, "2" is the
    second-largest integer, and "1" is the third-largest integer.

    ===============================================================
    FUNCTION: string kthLargestNumber(vector<string>& nums, int k);
    ===============================================================

    ==========================================================================
    ================================ EXAMPLES ================================
    ==========================================================================

    --- Example 1 ---
    Input: nums = ["3","6","7","10"], k = 4
    Output: "3"
    Explanation:
    The numbers in nums sorted in non-decreasing order are ["3","6","7","10"].
    The 4th largest integer in nums is "3".


    --- Example 2 ---
    Input: nums = ["2","21","12","1"], k = 3
    Output: "2"
    Explanation:
    The numbers in nums sorted in non-decreasing order are ["1","2","12","21"].
    The 3rd largest integer in nums is "2".


    --- Example 3 ---
    Input: nums = ["0","0"], k = 2
    Output: "0"
    Explanation:
    The numbers in nums sorted in non-decreasing order are ["0","0"].
    The 2nd largest integer in nums is "0".


    *** Constraints ***
    1 <= k <= nums.length <= 10^4
    1 <= nums[i].length <= 100
    nums[i] consists of only digits.
    nums[i] will not have any leading zeros.

*/

/*
    ------------
    --- IDEA ---
    ------------

    This one DOESN'T work. I just wanted to show that this approach won't
    work even if it comes to mind immediately, because of the given
    constraints:
       1 <= nums[i].length <= 100

    This means that we can have an integer up to 100 digits, which is,
    obviously larger than even the ULLONG_MAX which is consisted of 20 digits
    only.

    Therefore, we had to devise another way to keep this "sorted" on the heap.

*/
class NOT_Solution {
public:
    string kthLargestNumber(vector<string>& nums, int k)
    {
        std::priority_queue<unsigned long long, std::vector<unsigned long long>> max_heap;

        for (int i = 0; i < nums.size(); i++)
            max_heap.push((unsigned long long) std::stoull(nums[i]) );

        unsigned long long result;
        while (k--)
        {
            result = max_heap.top();
            max_heap.pop();
        }

        return std::to_string(result);
    }
};




/*
    ------------
    --- IDEA ---
    ------------

    The "int" in pair<int, string> is for length of string.

    Elements will be stored in lexicographical order when length of elements
    will be same else elements will be stored on the basis of length of string.

*/

/* Time  Beats: 77.07% */
/* Space Beats: 39.30% */

/* Time  Complexity: O(n * log n) */
/* Space Complexity: O(n) */
class Solution {
public:
    std::string kthLargestNumber(std::vector<std::string>& nums, int k)
    {
        std::priority_queue<pair<int, std::string>,
                            std::vector<std::pair<int, std::string>>,
                            std::greater<std::pair<int, std::string>>> min_heap;

        for(int i = 0; i < nums.size(); i++)
        {
            min_heap.push( {nums[i].size(), nums[i]} );

            if (min_heap.size() > k)
                min_heap.pop();
        }

        return min_heap.top().second;
    }
};
