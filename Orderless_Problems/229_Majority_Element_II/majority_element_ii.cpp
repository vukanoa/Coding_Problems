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




/*
    ------------
    --- IDEA ---
    ------------

    We are required to return the number that has appeared more than ⌊n/3⌋
    times in our array.

    Seems Interesting.

    We know that we need something here, count the number of occurencies and
    store them somewhere and then return the required elements.

    It's a job for HASHMAPS !
    Our hero today is the HashMap since, we can store the number of occurencies
    for each unique element and then return the elements that have appeared
    more than ⌊n/3⌋ times.

    It is an easy solution. Can we do better?
    Actually, We can.
    There is an interesting observation we want to look at.

    Example 1:
    Input:  nums = [1, 2, 2, 4, 4, 4]
    Output: [4]

    Example 2:
    Input:  nums = [1, 2, 2, 2, 4, 4, 4]
    Output: [2, 4]

    Example 3:
    Input:  nums = [1, 1, 2, 2, 2, 4, 4, 4]
    Output: [2, 4]

    Example 4:
    Input:  nums = [1, 1, 1, 2, 2, 2, 4, 4, 4]
    Output: []


    I think we have something here.

    Since we are required to return elements that appeared more than ⌊n/3⌋
    times then we have atmost two elements that we can return.

    But how two elements?

    Since we want to return elements that appeared more than ⌊n/3⌋ times then
    atleast it must have appeared ⌊n/3⌋ + 1 times. ⌊n/3⌋ + 1 is greater than
    the third of the array so

        `⌊n/3⌋ + 1` * 3 > array size

    So, it is impossible to return more than two elements.

    How can we utilize a great observation like this?

    Instead of storing the occurencies of all elements, We can only track the
    two highest elements that have appeared in our array and return them!

    And there is algorithm for that. It is called Boyer-Moore Majority Voting
    Algorithm.


    This algorithm can be used to return the highest K elements that appeared
    in the array more than array_size/(K+1) times. In our case, K = 2.
        + The major Intuition behind this algorithm is that maintaining voting
          variable for the candidates:

            + Increase the variable if you faced the candidate in your
              iteration.
            + Decrease the variable if you faced another element.
            + If the variable reaches 0, look for another promising candidate.

    Why this work?

    Assume we are searching for the element that appeared more than:
        array_size / 2 times,
    then we are sure that the voting variable can has value:
        array_size / 2 + 1
    and if we decreased it for all other elements in the array it will also
    stay positive enough to tell us the desired candidate.

    This is small image illustrating the algorithm for K=1 and the major
    element is the red square.


    ^
    |
    |
    |
    |
    |                               #
    |                         #   #
    |   .   .           #   #   #
    | .   .   .   *   #   #
    |           .   *
    |____________________________________.
      . . . . . . * * # # # # # # # #


    Legend:
        . - Blue
        * - Yellow
        # - Red



    1. Create variables to track counts and candidates for potential majority
       elements.

    2. First Pass - Find Potential Majority Elements:
        + Iterate through the input array and identify potential majority
          element candidates.

        + Update the candidates based on specific conditions.
        + Maintain counts for each candidate.

    3. Second Pass - Count Occurrences:
       Iterate through the input array again to count the occurrences of the
       potential majority elements.

    4. Compare the counts with a threshold to determine the majority elements.

    5. Return Majority Elements.

*/

/* Time  Beats: 98.47% */
/* Space Beats: 91.83% */

/* Time  Complexity: O(n) */
/* Space Complexity: O(1) */
class Solution_Boyer_Moore_Majority_Voting {
public:
    std::vector<int> majorityElement(std::vector<int>& nums)
    {
        // Counters for the potential majority elements
        int count1 = 0;
        int count2 = 0;

        // Potential majority element candidates
        int candidate1 = 0;
        int candidate2 = 0;

        // First pass to find potential majority elements.
        for (int i = 0; i < nums.size(); i++)
        {
            if (count1 == 0 && nums[i] != candidate2)
            {
                count1 = 1;
                candidate1 = nums[i];
            }
            else if (count2 == 0 && nums[i] != candidate1)
            {
                count2 = 1;
                candidate2 = nums[i];
            }
            else if (candidate1 == nums[i])
            {
                count1++;
            }
            else if (candidate2 == nums[i])
            {
                count2++;
            }
            else
            {
                count1--;
                count2--;
            }
        }

        std::vector<int> result;
        int threshold = nums.size() / 3; // Threshold for majority element

        // Second pass to count occurrences of the potential majority elements.
        count1 = 0;
        count2 = 0;

        for (int i = 0; i < nums.size(); i++)
        {
            if (candidate1 == nums[i])
                count1++;
            else if (candidate2 == nums[i])
                count2++;
        }

        // Check if the counts of potential majority elements are greater than
        // n/3 and add them to the result.
        if (count1 > threshold)
            result.push_back(candidate1);

        if (count2 > threshold)
            result.push_back(candidate2);

        return result;
    }
};
