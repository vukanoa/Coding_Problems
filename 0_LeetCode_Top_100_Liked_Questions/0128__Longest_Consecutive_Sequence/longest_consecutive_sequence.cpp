#include <iostream>
#include <vector>
#include <unordered_set>

/*
    ==============
    === MEDIUM === (Previously was under HARD)
    ==============

    =================================
    128) Longest Consecutive Sequence
    =================================

    ============
    Description:
    ============

    Given an unsorted array of integers "nums", return the length of the
    longest consecutive elements sequence.

    =====
    Node: You must write an algorithm that runs in O(n) time.
    =====

    =========================================================
    FUNCTION: int longestConsecutive(std::vector<int>& nums);
    =========================================================

    ==========================================================================
    ================================ EXAMPLES ================================
    ==========================================================================

    --- Example 1 ---
    Input:  nums = [100, 4, 200, 1, 3, 2]
    Output: 4

    --- Example 2 ---
    Input:  nums = [0, 3, 7, 2, 5, 8, 4, 6, 0, 1]
    Output: 9

    *** Constraints ***
    0 <= nums.length <= 10^5
    -10^9 <= nums[i] <= 10^9

*/


/*
    ------------
    --- IDEA ---
    ------------

    Let's start with a brute force solution:

    class Solution{
    private:
        // O(n)
        bool number_exists(std::vector<int>& nums, int num)
        {
            for (int i = 0; i < nums.size(); i++)
            {
                if (nums[i] == num)
                    return true;
            }

            return false;
        }

    public:
        int longestConsecutive(std::vector<int>& nums)
        {
            int max = 0;

            // O(n)
            for (int i = 0; i < nums.size(); i++)
            {
                int current_num = nums[i];
                int current_sequence_length = 1;

                // O(n) * (number_exists -> O(n)) => O(n^2)
                while (number_exists(nums, current_num + 1))
                {
                    current_num++;
                    current_sequence_length++;
                }

                max = std::max(max, current_sequence_length);
            }

            return max;
        }
    };


    We can immediately see that if we use a Set instead of iterating through
    the entire array each time in function "number_exists" we can reduce the
    time complexity from O(n^3) to O(n^2).

    Here is a O(n^2) Solution:
    // O(n^2)

    class Solution{
    public:
        int longestConsecutive(std::vector<int>& nums)
        {
            std::unordered_set<int> uset;

            for (int num: nums)
                uset.insert(num);

            int max = 0;

            // O(n)
            for (int i = 0; i < nums.size(); i++)
            {
                int current_num = nums[i];
                int current_sequence_length = 1;

                // O(n)
                // uset.find -> O(1)
                while (uset.find(current_num + 1) != uset.end())
                {
                    current_num++;
                    current_sequence_length++;
                }

                max = std::max(max, current_sequence_length);
            }

            return max;
        }
    };

    Let's consider the first Example:
    Input:  nums = [100, 4, 200, 1, 3, 2]

    We can immediately see that we don't have to start "counting" the length
    of the longest sequence if we are at elements: 4, 3 or 2 since they do not
    represent the start of the longest sequence.

    Thus, we can see that we only have to "track" the longest sequence if the
    element indeed represents the start of a sequence.

    So how can we know if an element is a starting element if, in this example,
    we see '1' AFTER we see 4, and we have to do it in O(n)?

    The answer is - Starting element is the smallest in the sequence.
    Starting element minus 1 does NOT exist in the array, or rather, in Set.

    When we get to element '4' we can try to find a '3' if it does exist then
    that indicates that '4' is NOT a starting element, thus we can just move
    forward.

    99  does NOT    exist so 100 is INDEED a starting element
    3   does INDEED exist so 4   is NOT    a starting element
    199 does NOT    exist so 200 is INDEED a starting element
    0   does NOT    exist so 1   is INDEED a starting element
    2   does INDEED exist so 3   is NOT    a starting element
    1   does INDEED exist so 2   is NOT    a starting element

    We only loop the while loop for starting elements, which in this example,
    are:
        100, 200 and 1.

    Thus we keep Time Complexity to O(n).


    1 2 3 4       100     200

    You can clearly observe that to know that a single element is a starting
    one, it must NOT have a left neighbor.

      1 doesn't have left neighbor, i.e. 0
    100 doesn't have left neighbor i.e. 99
    200 doesn't have left neighbor i.e. 199

    So each element will be processed twice. Once when creating a set at the
    beginning. And once when iterating through sequence from each starting
    element, thus this makes it O(n).

*/

/* Time  Beats: 32.64% */
/* Space Beats: 57.57% */

/* Time  Complexity: O(n) */
/* Space Complexity: O(n) */
class Solution_Linear_1 {
public:
    int longestConsecutive(std::vector<int>& nums)
    {
        int longest = 0;
        std::unordered_set<int> uset(nums.begin(), nums.end());

        // O(n)
        for (int i = 0; i < nums.size(); i++)
        {
            // If it DOESN'T exist --> It' a start of sequence
            if (uset.count(nums[i] - 1) == 0)
            {
                int length = 1;
                int number = nums[i];

                while (uset.count(++number))
                    length++;

                longest = std::max(longest, length);
            }
        }

        return longest;
    }
};




/*
    ------------
    --- IDEA ---
    ------------

    Same idea, but written in another way, it's maybe easier to grasp.

    Note that nowadays all these Solutoins aren't beating more than 5% for some
    reason. They used to beat more than 30%.

    I do not know any better and/or more efficient idea to solve this problem.

    (Update: it turns out that on LeetCode, it's faster to just sort "nums"
     and then just compare with the previous. This makes no sense, but it is
     how it is)

*/

/* Time  Beats: 5.00% */
/* Space Beats: 12.77% */

/* Time  Complexity: O(n) */
/* Space Complexity: O(n) */
class Solution_Linear_2 {
public:
    int longestConsecutive(std::vector<int>& nums)
    {
        std::unordered_set<int> uset(nums.begin(), nums.end());
        int longest = 0;

        for (int i = 0; i < nums.size(); i++)
        {
            if (uset.count(nums[i] - 1) == 0)
            {
                int count = 1;
                while (uset.count(nums[i] + count)) // This part is different
                    count++;

                longest = std::max(longest, count);
            }
        }

        return longest;
    }
};




/*
    ------------
    --- idea ---
    ------------

    just sort it and compare with the previous while iterating through the
    sorted array "nums".

*/

/* Time  Beats: 82.17% */
/* Space Beats: 75.53% */

/* Time  Complexity: O(n * logn) */ // This is faster than O(n) somehow
/* Space Complexity: O(n)        */
class Solution_Sort_1 {
public:
    int longestConsecutive(vector<int>& nums)
    {
        int n = nums.size();

        std::sort(nums.begin(), nums.end());
        std::unique(nums.begin(), nums.end());

        int c = 1;
        int longest = 1;
        for(int i = 0; i < n - 1; i++)
        {
            if(nums[i] - nums[i+1] == -1)
                c++;
            else
            {
                longest = std::max(longest, c);
                c = 1;
            }
        }

        longest = std::max(longest, c);

        if(n > 0)
            return m;

        return 0;
    }
};




/*
    ------------
    --- idea ---
    ------------

    just sort it and compare with the previous while iterating through the
    sorted array "nums".

*/

/* Time  Beats: 99.27% */
/* Space Beats: 73.03% */

/* Time  Complexity: O(n * logn) */ // This is faster than O(n) somehow
/* Space Complexity: O(n)        */
class Solution_Sort_2 {
public:
    int longestConsecutive(vector<int>& nums)
    {
        ios::sync_with_stdio(0);
        cin.tie(0);

        int len = 0;
        int n = nums.size();

        if(n==0 || n==1)
            return n;

        std::vector<int> res(n,1);
        std::sort(nums.begin(),nums.end());


        for(int i = 1; i < n; i++)
        {
            if (nums[i - 1] == nums[i] - 1)
                res[i] = res[i - 1] + 1;
            else if (nums[i] - nums[i - 1] == 0)
                res[i] = res[i - 1];
        }

        return *max_element(res.begin(),res.end());
    }
};



int
main()
{
    Solution_Linear_1   sol_linear_1;
    Solution_Linear_2   sol_linear_2;
    Solution_Sort_1     sol_sort_1;
    Solution_Sort_2     sol_sort_2;

    /* Example 1 */
    std::vector<int> nums = {100, 4, 200, 1, 3, 2};

    /* Example 2 */
    // std::vector<int> nums = {0, 3, 7, 2, 5, 8, 4, 6, 0, 1};

    /* Example 3 */
    // std::vector<int> nums = {8, 304, 7, 3, 4, 305, 303, 6, 308, 307, 306};

    /* Example 4 */
    // std::vector<int> nums = {};

    /* Example 5 */
    // std::vector<int> nums = {3};

    std::cout << "\n\t====================================";
    std::cout << "\n\t=== LONGEST CONSECUTIVE SEQUENCE ===";
    std::cout << "\n\t====================================\n";


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
    // int max = sol_linear_1.longestConsecutive(nums);
    // int max = sol_linear_2.longestConsecutive(nums);
    // int max = sol_sort_1.longestConsecutive(nums);
    int max = sol_sort_2.longestConsecutive(nums);


    /* Write Output */
    std::cout << "\n\tLongest Consecutive Sequence: " << max << "\n\n";


    return 0;
}
