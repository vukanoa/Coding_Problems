#include <iostream>
#include <vector>
#include <algorithm>

/*
    ==============
    === MEDIUM ===
    ==============

    ===========================
    18) 4Sum
    ===========================

    ============
    Description:
    ============

    Given an array nums of n integers, return an array of all the unique
    quadruplets [nums[a], nums[b], nums[c], nums[d]] such that:
        0 <= a, b, c, d < n
        a, b, c, and d are distinct
        nums[a] + nums[b] + nums[c] + nums[d] == target

    =====
    Node: You may return the answer in any order.
    =====

    =====================================================================
    FUNCTION: vector<vector<int>> fourSum(vector<int>& nums, int target);
    =====================================================================

    ==========================================================================
    ================================ EXAMPLES ================================
    ==========================================================================

    --- Example 1 ---
    Input:  nums = [1, 0, -1, 0, -2, 2], target = 0
    Output: [[-2, -1, 1, 2], [-2, 0, 0, 2], [-1, 0, 0, 1]]

    --- Example 2 ---
    Input:  nums = [2, 2, 2, 2, 2], target = 8
    Output: [[2, 2, 2, 2]]

    *** Constraints ***
    1 <= nums.length <= 200
    -10^9 <= nums[i] <= 10^9
    -10^9 <= target  <= 10^9

*/


/*
    ------------
    --- IDEA ---
    ------------

    This problem is a follow-up of 3Sum, so take a look at that problem first
    if you haven't already.

    4Sum and 3Sum are very similar; the difference is that we are looking for
    unique quadruplets instead of triplets.

    As you see, 3Sum just wraps Two Sum(Two Sum II actually) in an outer loop.
    As it iterates through each value 'v', it finds all pairs whose sum is
    equal to "(target - v)" using one of these approaches:

        1. "Two Sum" uses a hash set to check for a matching value.
        2. "Two Sum II" uses the two pointers technique in a sorted array.

    Following a similar logic, we can implement 4Sum by wrapping 3 Sum in
    another loop.
    But wait - there is a catch. If an interviewer asks you to solve 4Sum, they
    can follow-up with 5Sum, 6Sum, and so on. What they are really expecting at
    this point is a kSum solution. Therefore, we will focus on a generalized
    implementation here.

    Approach 1: Two Pointers Technique

    The two pointers technique requires the array to be sorted, so we do that
    first. Also, it's easier to deal with duplicates if the array is sorted:
    Repeated values are next to each other and easy to skip.

    For 3Sum, we enumerate each value in a single loop, and use the two
    pointers technique for the rest of the array. For kSum, we will have k - 2
    nested loops to enumerate all combinations of k - 2 values.

    right -----------------------------------
                                            |
    left  -----------------                 |
                          |                 |
                          |                 |
                          v     Two Sum     v
                          ________^___________
    1    2    ...    5    10    15    20    25
    k   k-1          ___________ _____________
                                v
                               3Sum

    We can implement k - 2 loops using a recursion. We will pass the starting
    point and 'k' as the parameters. When k == 2, we will call twoSum,
    terminating the recursion.

    1. For the main function:
        - Sort the input array "nums"
        - Calls kSum with start = 0, k = 4, and "target", and return the result

    2. For kSum function:
        - At the start of the kSum function, we will check three conditions:
            a) Have we run out of numbers to choose from?
            b) Is the smallest number remaining greater than target / k?
                If so, then any 'k' numbers we choose will be too large.
            c) Is the largest number remaining smaller than target / k?
                If so, then any k numbers we choose will be too small.
                If any of these conditions is true, there is no need to
                continue as no combination of the remaining elements can sum to
                "target.

        - If 'k' equals 2, call twoSum and return the result.

        - Iterate 'i' through the array from "start" :
            - If the current value is the same as the one before, skip it.
                (That's why we've sorted at the beginning)
            - Recursively call kSum with:
                start  = i + 1
                k      = k - 1
                target = target - nums[i]
            - For each returned "subset" of values:
                - Include the current value nums[i] into "subset".
                - Add "subset" to the result "vec_results". Once we have a 4
                    element "subset".

            - Return the result "vec_results";

    3. For twoSum function:
        - Set the low pointer "left" to "start", and "right" pointer to the
          last index.

        - While "left" pointer is smaller than "right":
            - If the sum of nums[left] and nums[right] is less than "target",
              increment "left".
                - Also increment "left" if the value is the same as left - 1
            - If the sum is greater than "target", decrement "right"
                - Also decrement "right" if the value is the same as right + 1
            - Otherwise, we found a pair:
                - Add it to the result "vec_results"
                - Decrement "right" and increment "left".

        - Return the result "vec_results"


~~~~~~~~~~~~~~~~~~~
~~~ static_cast ~~~
~~~~~~~~~~~~~~~~~~~

Consider this example:
    #include <iostream>

    int main()
    {
        const int MAX_INT = 2147483647;
        long long largeNum = MAX_INT * MAX_INT;
        std::cout << "largeNum = " << largeNum << std::endl;

        return 0;
    }

    This program attempts to compute the square of the maximum value of an
    'int' datatype. However, because the result of the multiplication is
    greater than the maximum value of a 'long long' data type, the result of
    the program is undefined. On my system, the output of this program is:

        largeNum = -9223372036854775808

    Which is not the correct result.




    If we instead use a 'static_cast' to convert 'MAX_INT' to 'long long'
    before performing the multiplication, as in the following code:

    #include <iostream>

    int main()
    {
        const int MAX_INT = 2147483647;
        long long largeNum = static_cast<long long>(MAX_INT) * static_cast<long long>(MAX_INT);
        std::cout << "largeNum = " largeNum << std::endl;

        return 0;
    }

    The program correctly computes the square of the maximum value of an 'int'
    data type:

        largeNum = 4611686014132420609

    So, while a 'static_cast' may not always be necessary, it can be useful in
    cases where the result of an operation might exceed the maximum value of
    the data type being used.

*/



/* Time  Beats: 99.50% */
/* Space Beats: 42.89% */
/*
    Time  Complexity:
    O(n^(k - 1)), or O(n^3) for 4Sum.
    We have k - 2 loops, and two_sum is O(n)
*/
/*
    Space Complexity:
    O(n). We need O(k) space for the recursion.
    k can be the same as n in the worst case for the generalized algorithm.
*/
class Solution{
public:
    std::vector<std::vector<int>>
    fourSum(std::vector<int>& nums, int target)
    {
        sort(nums.begin(), nums.end());
        return k_sum(nums, target, 0, 4);
    }

    std::vector<std::vector<int>>
    k_sum(std::vector<int>& nums, long long target, int start, int k)
    {
        std::vector<std::vector<int>> vec_results;

        if (start == nums.size())
            return vec_results;

        /*
            There are k remaining values to add to the sum.
            The average of these values is at least "target / k"
        */
        long long average_value = target / k;

        if (nums[start] > average_value || average_value > nums.back())
            return vec_results;

        if (k == 2)
            return two_sum(nums, target, start);

        for (int i = start; i < nums.size(); i++)
        {
            if (i == start || nums[i - 1] != nums[i])
            {
                for (std::vector<int>& subset : k_sum(nums, static_cast<long long>(target) - nums[i], i + 1, k - 1))
                {
                    /*
                        {{...}, {...}, {nums[i]}};
                    */
                    vec_results.push_back({nums[i]});

                    /*
                        We get the last vector of these vector of vectors and
                        then we specify arguments:
                        (
                         At which position of the last vector should we start inserting,
                         first position of the vector we want to insert,
                         last  position of the vector we want to insert
                        )
                    */
                    vec_results.back().insert(vec_results.back().end(), subset.begin(), subset.end());
                }
            }
        }

        return vec_results;
    }

    std::vector<std::vector<int>> two_sum(std::vector<int>& nums, long long target, int start)
    {
        std::vector<std::vector<int>> vec_results;
        int left = start;
        int right  = nums.size() - 1;

        while (left < right)
        {
            int sum = nums[left] + nums[right];

            if (sum < target || (left > start && nums[left] == nums[left - 1]))
                left++;
            else if (sum > target || (right < nums.size() - 1 && nums[right] == nums[right + 1]))
                right--;
            else
                vec_results.push_back({nums[left++], nums[right--]});
        }

        return vec_results;
    }
};




/*
    ------------
    --- IDEA ---
    ------------

    TODO

*/

/* Time  Beats: 51.84% */
/* Space Beats: 97.04% */

/* Time  Complexity: O(n^3) */
/* Space Complexity: O(n)   */
class Solution_Concise{
public:
    std::vector<std::vector<int>> fourSum(std::vector<int>& nums, int target)
    {
        std::sort(nums.begin(), nums.end());

        std::vector<std::vector<int>> result;
        int n = nums.size();

        for (int i = 0; i < n; i++)
        {
            if (i > 0 && nums[i] == nums[i - 1])
                continue;

            for (int j = i+1; j < n; j++)
            {
                if (j > (i+1) && nums[j] == nums[j-1])
                    continue;

                int left  = j+1;
                int right = n-1;

                while (left < right)
                {
                    long sum = (long)nums[i] + (long)nums[j] + (long)nums[left] + (long)nums[right];

                    if (sum == target)
                    {
                        result.push_back(std::vector<int>{nums[i], nums[j], nums[left], nums[right]});
                        left++;

                        while (left < right && nums[left] == nums[left-1])
                            left++;
                    }
                    else if (sum > target)
                        right--;
                    else
                        left++;
                }
            }
        }

        return result;
    }
};




int
main()
{
    Solution         sol;
    Solution_Concise sol_con;

    /* Example 1 */
    std::vector<int> nums = {1, 0, -1, 0, -2, 2};
    int target = 0;

    /* Example 2 */
    // std::vector<int> nums = {2, 2, 2, 2, 2};
    // int target = 8;

    std::cout << "\n\t================";
    std::cout << "\n\t=== FOUR SUM ===";
    std::cout << "\n\t================\n";


    /* Write Input */
    std::cout << "\n\tOriginal Vector: ";
    for (const auto& x : nums)
        std::cout << x << " ";
    std::cout << "\n\tTarget: " << target << "\n";


    /* Solution */
    // std::vector<std::vector<int>> vec_results = sol.fourSum(nums, target);
    std::vector<std::vector<int>> vec_results = sol_con.fourSum(nums, target);


    /* Write Output */
    std::cout << "\n\tResults:";
    std::vector<std::vector<int>> ::iterator it;
    it = vec_results.begin();
    for (it; it != vec_results.end(); it++)
    {
        std::cout << "\n\t" << it - vec_results.begin() + 1 << ") ";
        for(std::vector<int>::iterator it2 = it->begin(); it2 != it->end(); ++it2)
            std::cout << *it2 << " ";
    }
    std::cout << "\n\n";

    return 0;
}
