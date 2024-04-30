#include <iostream>
#include <vector>
#include <unordered_map>

/*
    ==============
    === MEDIUM ===
    ==============

    ===========================
    229) Majority Element II
    ===========================

    ============
    Description:
    ============

    Given an integer array of size n, find all elements that appear more than
    ⌊n/3 ⌋ times


    Follow up: Could you solve the problem in linear time and in O(1) space?

    =========================================================
    FUNCTION: vector<int> majorityElement(vector<int>& nums);
    =========================================================

    ==========================================================================
    ================================ EXAMPLES ================================
    ==========================================================================

    --- Example 1 ---
    Input: nums = [3,2,3]
    Output: [3]

    --- Example 2 ---
    Input: nums = [1]
    Output: [1]

    --- Example 3 ---
    Input: nums = [1,2]
    Output: [1,2]


    *** Constraints ***
    1 <= nums.length <= 5 * 10^4
    -10^9 <= nums[i] <= 10^9

*/

/*
    ------------
    --- IDEA ---
    ------------

    1. Create an HashMap to store the count of each element.

    2. Iterate through the input array and increment the count for each element
       in the HashMap.

    3. Create a vector to store the result and Calculate the threshold count
       (1/3 of the array size).

    4. Iterate through the HashMap and for each element:
        + Check if the element count is greater than the threshold.
        + If yes, add the element to the result vector.

    5. Return the vector containing the identified majority elements.

*/

/*
    ------------
    --- IDEA ---
    ------------

    Self-Explanatory.

*/

/* Time  Beats: 85.90% */
/* Space Beats: 25.66% */

/* Time  Complexity: O(n) */
/* Space Complexity: O(n) */
class Solution {
public:
    std::vector<int> majorityElement(std::vector<int>& nums)
    {
        // Create a frequency map to store the count of each element
        std::unordered_map<int, int> element_count_map;

        // Iterate through the input array to count element occurrences
        for(int i = 0; i < nums.size(); i++)
            element_count_map[nums[i]]++;

        std::vector<int> majority_elements;
        int threshold = nums.size() / 3;

        // Iterate through the frequency map to identify majority elements
        for (auto elementCountPair : element_count_map)
        {
            int element = elementCountPair.first;
            int count   = elementCountPair.second;

            // Check if the element count is greater than the threshold
            if (count > threshold)
                majority_elements.push_back(element);
        }

        return majority_elements;
    }
};
