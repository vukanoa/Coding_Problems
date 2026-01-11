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

#include <vector>
#include <unordered_map>
using namespace std;

/*
    ------------
    --- IDEA ---
    ------------

    Self-Explanatory.

*/

/* Time  Beats: 85.90% */
/* Space Beats: 25.66% */

/* Time  Complexity: O(N) */
/* Space Complexity: O(N) */
class Solution {
public:
    vector<int> majorityElement(vector<int>& nums)
    {
        const int N = nums.size();
        vector<int> result;

        unordered_map<int, int> freq;
        for (int i = 0; i < N; i++)
            freq[nums[i]]++;

        int threshold = N / 3;

        for (const auto& entry : freq)
        {
            const int& element = entry.first;
            const int& count   = entry.second;

            if (count > threshold)
                result.push_back(element);
        }

        return result;
    }
};




/*
    ------------
    --- IDEA ---
    ------------

    The very first thing one should note here is that there are AT MOST 2
    elements that have frequency STRICTLY GREATER than N/3.

    If you're not convinced of it, try to think of an example that has more
    than 2 elements. You will not be able to.

    #############
    ### Proof ###
    #############
    Suppose there are N elements:

        [a,  b,  c,  d,  e,  f,  g,  h,  i,  j,  k,  l,  m]
         0   1   2   3   4   5   6   7   8   9  10  11  12

    In this case, there are N=13 elements.
    Threshold_freq is N/3, which is: floor(13 / 3) <==> 4

    Therefore, we need elements that have threshold_freq STRICTLY GREATER than
    4, which is 5.

        threshold_freq = 5

        [X,  X,  X,  X,  X,  Y,  Y,  Y,  Y,  Y,  k,  l,  m]
         0   1   2   3   4   5   6   7   8   9  10  11  12
         ^^^^^^^^^^^^^^^^^   ^^^^^^^^^^^^^^^^^
                X                   Y

    Since for N=13, the threshold_freq == 5, the question is:

        Can you have:
            (3 * threshold_freq <==> 3 * 5 <==> 15 elements)
        in an array of N=13 elements?

    No, that's impossible. Therefore, we have proven that at most 2 elements
    with "threshold_freq" frequency(i.e. N/3) will be able to exist in any
    array.


    ######################
    ### Implementation ###
    ######################
    The algorithm we're going to use to solve this problem is called:

        "Boyer-Moore Majority_Voting Algorithm",

    but that's not the "hard" part here.

    The most difficult part here is--How to implement "Most Two Frequent
    Elements" using O(1) Space.

    There are two different ways to do that:
    
        1. Using a HashMap that once it gets to 3 elements, it decrements the
           count of all 3 and then pops the ones that have count of 0.

           or

        2. Using two(actually four) variables


    Below are both implementations.

*/

/* Time  Beats: 29.78% */
/* Space Beats: 42.00% */

/* Time  Complexity: O(N) */
/* Space Complexity: O(1) */ // Because there will always be at most 3 elements
class Solution_Boyer_Moore_Majority_Voting_Algorithm__1 {
public:
    vector<int> majorityElement(vector<int>& nums)
    {
        const int N = nums.size();
        const int threshold_freq = N / 3;
        vector<int> result;

        /* Two Most Frequent Elements using HashMap */
        unordered_map<int, int> umap_freq;
        for (int i = 0; i < N; i++)
        {
            umap_freq[nums[i]]++;

            if (umap_freq.size() == 3)
            {
                for (auto iter = umap_freq.begin(); iter != umap_freq.end();)
                {
                    iter->second--; // Freq

                    if (iter->second == 0)
                        iter = umap_freq.erase(iter); // Returns next iterator
                    else
                        iter++;
                }
            }
        }

        // Reset frequencies of at most two most frequent elements
        for (auto& [num, freq] : umap_freq)
            freq = 0;

        for (int i = 0; i < N; i++)
        {
            if (umap_freq.find(nums[i]) != umap_freq.end())
                umap_freq[nums[i]]++;
        }

        for (auto& [num, freq] : umap_freq)
        {
            if (freq > threshold_freq)
                result.push_back(num);
        }

        return result;
    }
};




/* Time  Beats: 100.00% */
/* Space Beats:  44.72% */

/* Time  Complexity: O(N) */
/* Space Complexity: O(1) */
class Solution_Boyer_Moore_Majority_Voting_Algorithm__2 {
public:
    vector<int> majorityElement(vector<int>& nums)
    {
        const int N = nums.size();
        const int threshold_freq = N / 3;
        vector<int> result;

        /* Two Most Frequent Elements */
        int majority_1 = -1;
        int majority_2 = -1;
        int freq_1 = 0;
        int freq_2 = 0;

        for (int i = 0; i < N; i++)
        {
            if (nums[i] == majority_1)
            {
                freq_1++;
            }
            else if (nums[i] == majority_2)
            {
                freq_2++;
            }
            else if (freq_1 == 0)
            {
                freq_1 = 1;
                majority_1 = nums[i];
            }
            else if (freq_2 == 0)
            {
                freq_2 = 1;
                majority_2 = nums[i];
            }
            else
            {
                freq_1--;
                freq_2--;
            }
        }

        freq_1 = 0;
        freq_2 = 0;
        for (int i = 0; i < N; i++)
        {
            if      (nums[i] == majority_1) freq_1++;
            else if (nums[i] == majority_2) freq_2++;
        }

        if (freq_1 > threshold_freq) result.push_back(majority_1);
        if (freq_2 > threshold_freq) result.push_back(majority_2);

        return result;
    }
};
