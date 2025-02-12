/*
    ==============
    === MEDIUM ===
    ==============

    ================================================
    2342) Max Sum of a Pair With Equal Sum of Digits
    ================================================

    ============
    Description:
    ============

    You are given a 0-indexed array nums consisting of positive integers. You
    can choose two indices i and j, such that i != j, and the sum of digits of
    the number nums[i] is equal to that of nums[j].

    Return the maximum value of nums[i] + nums[j] that you can obtain over all
    possible indices i and j that satisfy the conditions.

    ============================================
    FUNCTION: int maximumSum(vector<int>& nums);
    ============================================

    ==========================================================================
    ================================ EXAMPLES ================================
    ==========================================================================

    --- Example 1 ---
    Input: nums = [18,43,36,13,7]
    Output: 54
    Explanation: The pairs (i, j) that satisfy the conditions are:
    - (0, 2), both numbers have a sum of digits equal to 9, and their sum is 18 + 36 = 54.
    - (1, 4), both numbers have a sum of digits equal to 7, and their sum is 43 + 7 = 50.
    So the maximum sum that we can obtain is 54.

    --- Example 2 ---
    Input: nums = [10,12,19,14]
    Output: -1
    Explanation: There are no two numbers that satisfy the conditions, so we return -1.


    *** Constraints ***
    1 <= nums.length <= 10^5
    1 <= nums[i] <= 10^9

*/

#include <queue>
#include <unordered_map>
#include <vector>
using namespace std;

/*
    ------------
    --- IDEA ---
    ------------

    Edge case immediately--If there is only one element, that we certainly
    cannot return anything other than -1.

    Since multiple DIFFERENT elements in nums will have the same
    "sum of digits", we obviously need a HashMap.

    However, we cannot return "sum of digits" as a result, but actually have to
    take largest 2 elements from nums.

    Therefore, a Hashmap where key is "sum of digits" and value is occurrence
    is simply not enough.

    What about

             key                   value
        {"sum of digits",{occurrence, vector_elements_with_that_sum_of_digits}}

    That wouldn't work either because we'd have to iterate over the vector to
    two of the largest elements within that vector.

    If we have million elements where all of them have the sam "sum of digits",
    then we'd have to iterate through all N elements again.

    It would still be O(N), but it'd be a lot less efficient than it has to be.
    The Solutions is screaming at you at this point--Heap.

    Basic MaxHeap will do a job instead of a vector.


    This is how the Solution works:

        1. Create a HashMap of {"sum of digits", {occurrences, max_heap}}

        2. Iterate through every element in nums and calculate "sum of digits"

        3. Put that calculated "sum of digits" in our HashMap

        4. Once we're done with that, iterate through every entry in HashMap

        5. Only if there are more than two elements in Heap for some "key", we
            5.1. Take the max between "result" and top two elements in the Heap

        6. Return result

*/

/* Time  Beats: 42.73% */
/* Space Beats: 35.53% */

/* Time  Complexity: O(N * logN) */
/* Space Complexity: O(N)        */
class Solution {
public:
    int maximumSum(vector<int>& nums)
    {
        const int N = nums.size();
        int result = -1;

        if (N == 1)
            return -1;

        unordered_map<int, pair<int,priority_queue<int>>> counter;
        for (int i = 0; i < N; i++)
        {
            int sum = sum_digits(nums[i]);
            counter[sum].first++;
            counter[sum].second.push(nums[i]);
        }

        for (auto& entry : counter)
        {
            if (entry.second.first > 1)
            {
                int one = entry.second.second.top();
                entry.second.second.pop();

                int two = entry.second.second.top();
                // entry.second.second.pop();

                result = max(result, one + two);
            }
        }

        return result;
    }

private:
    int sum_digits(int num)
    {
        int result = 0;
        while (num)
        {
            result += num % 10;
            num /= 10;
        }

        return result;
    }
};




/*
    ------------
    --- IDEA ---
    ------------

    However, since we ALWAYS need only the top two elements for each
    "sum of digits", we don't really need to use a MaxHeap since that will drag
    us down in efficiency.

    We can just keep the track of the top two manually, for every
    "sum of digits".

    This way the total Time Complexity is reduce from O(N * logN) down to O(N).

*/

/* Time  Beats: 81.56% */
/* Space Beats: 75.41% */

/* Time  Complexity: O(N) */
/* Space Complexity: O(N) */
class Solution_Efficient {
public:
    int maximumSum(vector<int>& nums)
    {
        const int N = nums.size();
        int result = -1;

        if (N == 1)
            return -1;

        unordered_map<int, pair<int,pair<int,int>>> counter;
        for (int i = 0; i < N; i++)
        {
            int sum = sum_digits(nums[i]);
            counter[sum].first++;

            if (counter[sum].second.first < nums[i])
            {
                counter[sum].second.second = counter[sum].second.first;
                counter[sum].second.first  = nums[i];
            }
            else if (counter[sum].second.second < nums[i])
            {
                counter[sum].second.second = nums[i];
            }
        }

        for (auto& entry : counter)
        {
            int one = entry.second.second.first;
            int two = entry.second.second.second;
            if (one == 0 || two == 0)
                continue;

            result = max(result, one + two);
        }

        return result;
    }

private:
    int sum_digits(int num)
    {
        int result = 0;
        while (num)
        {
            result += num % 10;
            num /= 10;
        }

        return result;
    }
};
