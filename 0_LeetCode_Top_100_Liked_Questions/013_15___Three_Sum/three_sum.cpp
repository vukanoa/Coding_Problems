#include <iostream>
#include <vector>
#include <algorithm>

/*
    ==============
    === MEDIUM ===
    ==============

    ===========================
    15) 3Sum
    ===========================

    ============
    Description:
    ============

    Given an integer array nums, return all the triplets:
    [nums[i], nums[j], nums[k]] such that i != j, i != k, and j != k, and
    num[i] + nums[j] + nums[k] == 0.

    =====
    Node: Notice that the solution set must not contain duplicate triplets.
    =====

    ==========================================================
    FUNCTION: vector<vector<int>> threeSum(vector<int>& nums);
    ==========================================================

    ==========================================================================
    ================================ EXAMPLES ================================
    ==========================================================================

    --- Example 1 ---
    Input:  nums = [-1, 0, 1, 2, -1, -4]
    Output: [[-1, -1, 2], [-1, 0, 1]]
    Explanation:
    nums[0] + nums[1] + nums[2] = (-1) + 0 +   1  = 0
    nums[0] + nums[2] + nums[4] =   0  + 1 + (-1) = 0
    nums[i] + nums[3] + nums[4] = (-1) + 2 + (-1) = 0

    The distinct triples are [-1, 0, 1] and [-1, -1, 2].
    Notice that the order of the output and the order of the triplets
    does not matter.

    --- Example 2 ---
    Input:  nums = [0, 1, 1]
    Output: []
    Explanation: The only possible triplet does not sum up to 0.

    --- Example 3 ---
    Input: nums = [0, 0, 0]
    Output [[0, 0, 0]]
    Explanation: The only possible triplet sums up to 0

    *** Constraints ***
    3 <= nums.length <= 3000
    -10^5 <= nums[i] <= 10^5
*/



/*
    ------------
    --- IDEA ---
    ------------

    Two Sum II should be done prior to this Problem. After it, the solution
    is straightforward.

    Note: "Two Sum II" is NOT the same as "Two sum".

    Make sure you do:
        Two Sum II

    First we should sort the vector "nums". Why? So that we don't have
    duplicate triplets.

    Consider this example:
        -3 3 4 -3 1 2

    First Triplet: -3, 1, 2
    That's when the first element starts with -3 at position 0.

    But a bit later, our first element is again going to start at value -3, but
    this time at position 3 and since the other two elements that sum up to 0
    are AFTER either of our two -3's, then that means we will have a duplicate
    triplet which is something we are warned about. It's something that we must
    avoid.

    So how do we fulfill this requirement?
    We sort the array and in each outer loop we only ask if 'i' is greater than
    0 and if 'i' is equal to 'i - 1'.

    We ask if 'i' is greater than 0 because if we weren't then for 0th element
    we would've asked if 0th element is equal to an element before the array
    which is some random value(out of bounds). So to avoid this we check
    if 'i' is greater than 0.

    And we ask if nums[i] == nums[i - 1] because only the very first element
    in a "chain of duplicates" in our, now sorted, array should be considered.

    So the previous example:
        -3 3 4 -3 1 2
    Now becomes
        -3 -3 1 2 3 4

    Thus the 2nd -3 won't even be considered. We are just going to skip it.

    And now this problem is divided to two:
        1. This outer for loop
        2. Two Sum II

    Two Sum II is solved using Two Pointer Technique. In the above (sorted)
    example we pick -3 for our first value, and we put two pointers to the end
    of the array and to the first non-duplicate element to the right.

    Now sum all three elements and see if it is greater than 0, lower than 0 or
    equal to 0.

    If it is greater than 0, then decrement the "right" pointer by one.
    If it is lower than 0, then increment the "left" pointer by one.
    If it is equal to 0, put all three elements in vector and push that vector
    to vector of vectors "triplets"(which we are returning).

*/


/* ========= */
/* === N === */
/* ========= */

/* Time  Beats: 78.48% */
/* Space Beats: 54.64% */
/* Time  Complexity: O(n^2) */
/* Space Complexity: O(1) or O(n), depends on the sort. Heapsort uses O(1) */
class Solution{
public:
    std::vector<std::vector<int>> threeSum(std::vector<int>& nums)
    {
        int n = nums.size();
        std::vector<std::vector<int>> triplets;

        // O(n * logn)
        std::sort(nums.begin(), nums.end());

        // O(n^2)
        for (int i = 0; i < n - 2; i++)
        {
            if (i > 0 && nums[i] == nums[i - 1])
                continue;

            // Two Sum II
            int left  = i + 1;
            int right = n - 1;
            while (left < right)
            {
                int sum = nums[i] + nums[left] + nums[right];

                if (sum > 0)
                    right--;
                else if (sum < 0)
                    left++;
                else
                {
                    std::vector<int> vec = {nums[i], nums[left], nums[right]};
                    triplets.push_back(vec);

                    left++;
                    while (nums[left] == nums[left - 1] && left < right)
                        left++;
                }
            }
        }

        return triplets;
    }

};


int
main()
{
    Solution sol;

    /* Example 1 */
    // std::vector<int> nums = {-1, 0, 1, 2, -1, -4};

    /* Example 2 */
    // std::vector<int> nums = {0, 1, 1};

    /* Example 3 */
    // std::vector<int> nums = {0, 0, 0};

    /* Example 4 */
    // std::vector<int> nums = {};

    /* Example 5 */
    std::vector<int> nums = {5, 2, 1, 0, -7, -3, 7, 8};

    std::cout << "\n\t=================";
    std::cout << "\n\t=== THREE SUM ===";
    std::cout << "\n\t=================\n";


    /* Write Input */
    bool first = true;
    std::cout << "\n\t=== Array ===\n\t[";
    for (auto x: nums)
    {
        if (!first)
            std::cout << ", ";

        std::cout << x;
        first = false;
    }
    std::cout << "]\n\n";

    /* Solution */
    std::vector<std::vector<int>> triplets = sol.threeSum(nums);

    /* Write Output */
    std::cout << "\n\t=== Triplets ===";
    if (triplets.empty())
        std::cout << "\n\t[]\n";

    int cnt = 1;
    for(auto triplet : triplets)
    {
        std::cout << "\n\t" << cnt++ << ") ";

        for (auto x : triplet)
            std::cout << x << " ";
        std::cout << "\n";
    }
    std::cout << "\n";

    return 0;
}
