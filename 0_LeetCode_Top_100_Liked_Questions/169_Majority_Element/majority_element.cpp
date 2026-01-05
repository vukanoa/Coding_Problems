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

#include <vector>
#include <unordered_map>
using namespace std;

/*
    ------------
    --- IDEA ---
    ------------

    The only reason this Solution is in this file is to be able to fully
    appreciate the optimal ones in comparison to this, naive, one.

*/

/* Time  Beats: 100.00% */
/* Space Beats:  62.21% */

/* Time  Complexity: O(N) */
/* Space Complexity: O(N) */
class Solution_Brute {
public:
    int majorityElement(vector<int>& nums)
    {
        const int N = nums.size();

        unordered_map<int, int> umap;

        int majority_element;
        int count = 0;
        for (int i = 0; i < N; i++)
        {
            umap[nums[i]]++; // If it does NOT yet exist, its frequency is 0

            if (umap[nums[i]] > count)
            {
                majority_element = nums[i];
                count            = umap[nums[i]];
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

    If an element "majority_element" occurs more than floor(n/2) times,
    then there are at least floor(n/2) elements of identical values with
    "num" at each bit. That is, we can reconstruct the exact value of "num" by
    combining the most frequent value (0 or 1) at each bit.

    Starting from the least significant bit, we create a bitmask to determine
    which value is the majority at this bit, 0 or 1, and put this value to the
    corresponding bit of the result variable "majority_element".


    Because all numbers are in the range [-10^9, 10^9], which can be
    represented in 32-bits, we only need to a "mask" for the first 32 bits.

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
    int majorityElement(vector<int>& nums)
    {
        const int N = nums.size();

        int majority_element = 0;
        for (int i = 0; i < 32; i++)
        {
            int bit = 1 << i;

            // Count how many numbers have this bit set in the entire "nums"
            int freq_of_curr_bit = 0;
            for (const int& num : nums)
            {
                if (num & bit)
                    freq_of_curr_bit++;
            }

            // If this bit is present in more than n / 2 elements
            // then it must be set in the majority element
            if (freq_of_curr_bit > N / 2)
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
/* Time  Complexity: O(N) */
/* Space Complexity: O(1) */
class Solution_Boyer_Moore_Majority_Voting_Algorithm {
public:
    int majorityElement(vector<int>& nums)
    {
        const int N = nums.size();

        int majority_element = nums[0];
        int count = 1;
        for (int i = 1; i < N; i++)
        {
            if (nums[i] == majority_element)
            {
                count++;
            }
            else
            {
                count--;

                if (count == 0)
                {
                    majority_element = nums[i];
                    count = 1;
                }
            }
        }

        return majority_element;
    }
};
