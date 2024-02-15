#include <iostream>
#include <vector>
#include <unordered_map>

/*
    ============
    === EASY ===
    ============

    ===========================
    169) Majority Element
    ===========================

    ============
    Description:
    ============

    Given an array "nums" of size "n", return the majority element.

    The majority element is the element that appears more than [n / 2] times.
    You may assume that the majority element always exists in the array.

    =================================================
    FUNCTION: int majorityElement(vector<int>& nums);
    =================================================

    ==========================================================================
    ================================ EXAMPLES ================================
    ==========================================================================

    --- Example 1 ---
    Input:  nums = [3, 2, 3]
    Output: 3

    --- Example 2 ---
    Input:  nums = [2, 2, 1, 1, 1, 2, 2]
    Output: 2

    *** Constraints ***
    n == nums.length
    1 <= n <= 5 * 10^4
    -10^9 <= nums[i] <= 10^9

    Follow-up: Could you solve the problem in linear time and in O(1) space?

*/




/*
    ------------
    --- IDEA ---
    ------------

    Self-explanatory Brute Force Solution.

*/

/* Time  Beats: 44.58% */
/* Space Beats: 33.33% */

/* Time  Complexity: O(n) */
/* Space Complexity: O(n) */
class Solution_Brute {
public:
    int majorityElement(std::vector<int>& nums)
    {
        std::unordered_map<int, int> umap;
        int majority_element;
        int max_occurrence = 0;

        for (int i = 0; i < nums.size(); i++)
        {
            auto it = umap.find(nums[i]);

            if (it != umap.end())
                it->second++;
            else
                umap.insert({nums[i], 1});

            if (umap.at(nums[i]) > max_occurrence)
            {
                max_occurrence   = umap.at(nums[i]);
                majority_element = nums[i];
            }
        }

        return majority_element;
    }
};




/*
    ------------
    --- IDEA ---
    ------------

    Approach: Bit Manipulation

    Intuition

    If an element "majority_element" occurs more than std::floor(n/2) times,
    then there are at least std::floor(n/2) elements of identical values with
    "num" at each bit. That is, we can reconstruct the exact value of "num" by
    combining the most frequent value (0 or 1) at each bit.


    Algorithm

    Starting from the least significant bit, we enumerate each bit to determine
    which value is the majority at this bit, 0 or 1, and put this value to the
    corresponding bit of the result. Finally, we end up with the most least
    significant bit of all elements and return the result.


    Implementation

    Because all numbers are in the range [-10^9, 10^9], which can be
    represented in 32-bit, we only need to enumerate 32 bits.

*/

/* Time  Beats: 49.55% */
/* Space Beats: 76.13% */

/*
    Time  Complexity: O(n * logC) => O(n * 32) => O(n)
    C is the max absolute value in "nums", i.e., 10^5 in this problem.
    We enumerate all logC bits for each number in "nums".
*/
/* Space Complexity: O(1) */
class Solution_Bit_Manipulation {
public:
    int majorityElement(std::vector<int>& nums)
    {
        int n = nums.size();
        int majority_element = 0;

        for (int i = 0; i < 32; i++)
        {
            int bit = 1 << i;

            // Count how many numbers have this bit set
            int bit_count = 0;
            for (int num : nums)
            {
                if ((num & bit) != 0)
                    bit_count++;
            }

            // If this bit is present in more than n / 2 elements
            // then it must be set in the majority element
            if (bit_count > n / 2)
                majority_element |= bit;
        }

        return majority_element;
    }
};




/*
    ------------
    --- IDEA ---
    ------------

    ************************************
    *** Boyer-Moore Voting Algorithm ***
    ************************************

    Intuition
    If we had some way of counting instances of the majority element as +1 and
    instances of any other as -1, summing them would make it obvious that the
    majority element is indeed the majority lement.

    Algorithm
    Essentially, what Boyer-Moore does is look for a suffix "suf" of "nums"
    where suf[0] is the majority element in that suffix. To do this, we
    maintain a count, which is incremented whenever we see an instance of our
    current candidate for majority element and decremented whenever we see
    anything else. Whenever "count" equals 0, we effectively forget about
    everything in "nums" up to the current index and consider the current
    number as the candidate for majority element. It is not immediately
    obvious why we can get away with forgetting prefixes of "nums" - consider
    the following examples (pipes are inserted to separate runs of nonzero
    "count").

    Example 1:
    [7, 7, 5, 7, 5, 1 | 5, 7, | 5, 5, 7, 7 | 7, 7, 7, 7]

    Here, the 7 at index 0 is selected to be the first candidate for majority
    element. "count" will eventually reach 0 after index 5 is processed, so the
    5 at index 6 will be the next candidate.
    In this case, 7 is the true majority element, so by disregarding this
    prefix, we are ignoring an equal number of majority and minority
    elements - therefore, 7 will still be the majority element in the suffix
    formed by throwing away the first prefix.

    Example 2:
    [7, 7, 5, 7, 5, 1 | 5, 7 | 5, 5, 7, 7 | 5, 5, 5, 5]

    Now, the majority element is 5 (we changed the last run of the array from
    7s to 5s), but our first candidate is still 7. In this case, our candidate
    is not the true majority element, but we still cannot discard more majority
    elements than minority elements (this would imply that "count" could reach
    -1 before we reassign "candidate", which is obviously false).

    Therefore, given that it is impossible (in both cases) to discard more
    majority elements than minority elements, we are safe in discarding the
    prefix and attempting to recursively solve the majority element problem for
    the suffix. Eventually, a suffix will be found for which "count" does not
    hit 0, and the majority element of that suffix will necessarily be the same
    as the majority element of the overall array.

*/

/* Time  Beats: 99.84% */
/* Space Beats: 33.33% */ // I don't know how is this possible

/* Time  Beats: 71.72% */
/* Space Beats: 96.74% */

/* Time  Complexity: O(n) */
/* Space Complexity: O(1) */
class Solution_Boyer_Moore_Voting {
public:
    int majorityElement(std::vector<int>& nums)
    {
        int count = 0;
        int candidate = 0;

        for (int i = 0; i < nums.size(); i++)
        {
            if (count == 0)
                candidate = nums[i];

            count += (nums[i] == candidate) ? 1 : -1;
        }

        return candidate;
    }
};




/*
    ------------
    --- IDEA ---
    ------------

    ************************************
    *** Boyer-Moore Voting Algorithm ***
    ************************************

    It's the same algorithm as the above, just written in a more verbose way.
    I think it's much easier to read and graps from the code down below.

*/


/* Time  Beats: 93.70% */
/* Space Beats: 33.33% */ // I don't know how is this possible

/* Time  Complexity: O(n) */
/* Space Complexity: O(1) */
class Solution_Boyer_Moore_Voting_Verbose {
public:
    int majorityElement(std::vector<int>& nums)
    {
        int n = nums.size();

        int candidate = nums[0];
        int majority = 1;
        int minority = 0;

        // Starting from the 2nd element, i.e. Element at index 1
        for (const int& num : std::vector<int>(nums.begin() + 1, nums.end()))
        {
            if (majority == minority)
            {
                candidate = num;
                majority = 0;
                minority = 0;
            }

            if (num == candidate)
                majority++;
            else
                minority++;
        }

        return candidate;
    }
};




/*
    ------------
    --- IDEA ---
    ------------

    Third way of implementing the "Boyer Moore Voting" Algorithm.

*/

/* Time  Beats: 96.77% */
/* Space Beats: 45.21% */

/* Time  Complexity: O(n) */
/* Space Complexity: O(1) */
class Solution_Boyer_Moore_Voting_3 {
public:
    int majorityElement(std::vector<int>& nums)
    {
        int majority = nums[0];
        int count = 1;

        for (int i = 1; i < nums.size(); i++)
        {
            if (majority != nums[i])
                count--;
            else
                count++;

            if (count == 0)
            {
                majority = nums[i];
                count = 1;
            }
        }

        return majority;
    }
};


int
main()
{
    Solution_Brute                      sol_brute;
    Solution_Bit_Manipulation           sol_bit_manipulation;
    Solution_Boyer_Moore_Voting         sol_boyer_moore_voting;
    Solution_Boyer_Moore_Voting_Verbose sol_boyer_moore_voting_verbose;
    Solution_Boyer_Moore_Voting_3       sol_boyer_moore_voting_3;


    /* Example 1 */
    // std::vector<int> nums = {3, 2, 3};

    /* Example 2 */
    // std::vector<int> nums = {2, 2, 1, 1, 1, 2, 2};

    /* Example 3 */
    // std::vector<int> nums = {7, 7, 5, 7, 5, 1, 5, 7, 5, 5, 7, 7, 7, 7, 7, 7};

    /* Example 4 */
    // std::vector<int> nums = {7, 7, 5, 7, 5, 1, 5, 7, 5, 5, 7, 7, 5, 5, 5, 5};

    /* Example 5 */
    // std::vector<int> nums = {1, 2, 2, 3, 3, 1, 1};

    /* Example 6 */
    // std::vector<int> nums = {1, 2, 2, 3, 3, 3, 3};

    /* Example 7 */
    // std::vector<int> nums = {1, 1, 2, 1, 2, 3, 3, 4, 3, 3};

    /* Example 8 */
    std::vector<int> nums = {1, 1, 2, 1, 2, 3, 2, 4, 2, 3};



    std::cout << "\n\t========================";
    std::cout << "\n\t=== MAJORITY ELEMENT ===";
    std::cout << "\n\t========================\n";


    /* Write Input */
    bool first = true;
    std::cout << "\n\tArray: [";
    for (auto x: nums)
    {
        if (!first)
            std::cout << ", ";

        std::cout << x;
        first = false;
    }
    std::cout << "]\n";


    /* Solution */
    // int majority_element = sol_brute.majorityElement(nums);
    // int majority_element = sol_bit_manipulation.majorityElement(nums);
    // int majority_element = sol_boyer_moore_voting.majorityElement(nums);
    // int majority_element = sol_boyer_moore_voting_verbose.majorityElement(nums);
    int majority_element = sol_boyer_moore_voting_3.majorityElement(nums);


    /* Write Output */
    std::cout << "\n\tMajority Element: " << majority_element << "\n\n";


    return 0;
}
