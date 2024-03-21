#include <iostream>
#include <vector>
#include <algorithm>
#include <queue>
#include <unordered_set>

/*
    ==============
    === MEDIUM ===
    ==============

    ===========================
    46) Permutations
    ===========================

    ============
    Description:
    ============

    Given an array "nums" of distinct integers, return all the possible
    permutations.

    =====
    Node: You can return the answer in any order.
    =====

    ========================================================================
    FUNCTION: std::vector<std::vector<int>> permute(std::vector<int>& nums);
    ========================================================================

    ==========================================================================
    ================================ EXAMPLES ================================
    ==========================================================================

    --- Example 1 ---
    Input:  nums = [1, 2, 3]
    Output: [[1, 2, 3], [1, 3, 2], [2, 1, 3], [2, 3, 1], [3, 2, 1]]

    --- Example 2 ---
    Input:  nums = [0, 1]
    Output: [[0, 1], [1, 0]]

    --- Example 3 ---
    Input:  nums = [1]
    Ouput:  [[1]]

    *** Constraints ***
    1 <= nums.length <= 6
    -10 <= nums[i] <= 10
    All the integers of "nums" are unique

*/



/*
    ------------
    --- IDEA ---
    ------------

    A bit trickier Backtracking, but the main idea is to see the decision Tree.

                              [1, 2, 3]
                             /    |   \
                            /     |    \
                           /      |     \
                          /       |      \
                       1 /       2|       \ 3
                        /         |        \
                       /          |         \
                      /           |          \
                     /            |           \
 ------------>  [2, 3]         [1, 3]        [2, 3]
 |               /  \           /  \          /  \
 |            2 /    \ 3      1/    \ 3     2/    \ 3
 |             /      \       /      \      /      \
 |            [3]    [2]     [3]    [1]    [3]    [2]
 |             |      |       |      |      |      |
 |            3|      |2     3|      |1    3|      |2
 |             |      |       |      |      |      |
 |            [ ]    [ ]     [ ]    [ ]    [ ]    [ ]
 |
 |
 |
 |
 |  Each "edge" represents popping that element from the current array.
 |
 |  The only important thing here is this. Once we're here:
 |                                                      |
 |______________________________________________________|
 ^
 |
 |  We are going to pop 2 and go to the left. Then on the next level, pop the 3
 |  and then on the next "level" we will store the combination in order in
 |  which they were popped. But here is the important part, once we return
 |  from the next level, we don't push the old popped element at the
 |  front(where it was before popping), instead we're pushing it to the back.
 |
 |  So here:
 |______|
 ^
 |  Before the initial pop: [2, 3]
 |  Then we pop the 2:      [3]
 |  Then once the left tree ends, we have to push the 2 back and go to the
 |  right. But where do we push it? TO THE BACK.
 |
 |_ Now at this same level: after we get back from the left subtree, we'll have
    this: [3, 2] and then we'll pop from the front(3 in this case) and proceed
    to go to the right.

    That's the whole idea.

*/

/* Time  Beats: 53.48% */
/* Space Beats:  5.25% */

/* Time  Complexity: O(n * n!) */
/* Space Complexity: O(n!) */
class Solution_Backtracking_Queue {
public:
    std::vector<std::vector<int>> permute(std::vector<int>& nums)
    {
        std::vector<std::vector<int>> results;
        std::queue<int> queue;
        std::vector<int> curr;

        for (int& num : nums)
            queue.push(num);

        backtracking(queue, curr, results);

        return results;
    }

private:
    void backtracking(std::queue<int> queue, std::vector<int> curr, std::vector<std::vector<int>>& results)
    {
        if (queue.empty())
        {
            results.push_back(curr);
            return;
        }

        for (int i = 0; i < queue.size(); i++)
        {
            int num = queue.front();
            queue.pop();
            curr.push_back(num);

            backtracking(queue, curr, results);

            curr.pop_back();
            queue.push(num);
        }
    }
};





/*
    ------------
    --- IDEA ---
    ------------

    Very similar to the one above. However, this one doesn't use a queue,
    instead it always iterates from 0 to nums.size(), however it uses an
    unordered Set to determine if some number was already in use in our current
    combination.

    That's the whole difference.

    Conceptually it's a different way of thinking about Backtracking Solution,
    therefore I wanted to have both.

*/

/* Time  Beats: 51.61% */
/* Space Beats:  8.86% */

/* Time  Complexity: O(n * n!) */
/* Space Complexity: O(n!) */
class Solution_Backtracking_Basic {
public:
    std::vector<std::vector<int>> permute(std::vector<int>& nums)
    {
        std::vector<std::vector<int>> results;
        std::unordered_set<int> uset_curr_comb; // Unordered set of a curr comb

        backtracking(nums, {}, uset_curr_comb, results);

        return results;
    }

private:
    void backtracking(std::vector<int>& nums,
                      std::vector<int> curr_comb,
                      std::unordered_set<int>& uset_curr_comb,
                      std::vector<std::vector<int>>& results)
    {
        if (curr_comb.size() == nums.size())
        {
            results.push_back(curr_comb);
            return;
        }

        for (int i = 0; i < nums.size(); i++)
        {
            if (uset_curr_comb.count(nums[i])) // If it exists in the Set
                continue;

            curr_comb.push_back(nums[i]);
            uset_curr_comb.insert(nums[i]);

            backtracking(nums, curr_comb, uset_curr_comb, results);

            uset_curr_comb.erase(nums[i]);
            curr_comb.pop_back();
        }
    }
};




/*
    ------------
    --- IDEA ---
    ------------

    - First we sort our initial "nums" array since that won't
      change the runtime complexity and we need our array values in
      sorted order

    - We begin from permutation:
      A = {A[0] A[1] ... A[n - 1]}

    - Find the biggest index "left" (0 <= left < n - 1)
      such that A[left] < A[left + 1]

    - Find the biggest index "right" (left < right && right <= n - 1)
      such that A[left] < A[right]

    - Swap A[left] and A[right]

    - Reverse the order of elements
      A[left + 1] A[left + 2] ... A[n - 1]

    left  = ^
    right = #

    1 2 3 4 5 --> 1 2 3 5 | 4 --> 1 2 3 5 4
          ^ #

    1 2 3 5 4 --> 1 2 4 | 5 3 --> 1 2 4 3 5
        ^   #

    1 2 4 3 5 --> 1 2 4 5 | 3 --> 1 2 4 5 3
          ^ #

    1 2 4 5 3 --> 1 2 5 | 4 3 --> 1 2 5 3 4
        ^ #

    1 2 5 3 4 --> 1 2 5 4 | 3 --> 1 2 5 4 3
          ^ #

    1 2 5 4 3 --> 1 3 | 5 4 2 --> 1 3 2 4 5
      ^     #

    1 3 2 4 5 --> 1 3 2 5 | 4 --> 1 3 2 5 4
          ^ #
    ...

*/

/* Time  Beats: 100% */
/* Space Beats: 30.17% */

/* Time  Complexity: O(n!) */
/* Space Complexity: O(1) */
class Solution_Next_Permutation {
public:
    std::vector<std::vector<int>> permute(std::vector<int>& nums)
    {
        std::vector<std::vector<int>> results;

        /* Base case */
        if (nums.size() == 1)
        {
            results.push_back(nums);

            return results;
        }

        /* Sort */
        std::sort(nums.begin(), nums.end());

        /* Push the current permutation and permute nums again */
        do
        {
            std::vector<int> vec_tmp;
            for (int i = 0; i < nums.size(); i++)
                vec_tmp.push_back(nums[i]);

            results.push_back(vec_tmp);
        } while (next_permutation(nums));

        return results;
    }

private:
    int next_permutation(std::vector<int>& nums)
    {
        int n = nums.size();

        int first = 0;
        int last  = n - 1;

        int left  = last - 1;
        int right = last;

        // Find the largest "left" so that nums[left] < nums[left + 1]
        while (left > first)
        {
            if (nums[left] < nums[left + 1])
                break;

            left--;
        }

        /*
           If no nums[left] < nums[left + 1], "nums" is the last permutation
           in lexicographic order
         */
        if (nums[left] > nums[left + 1])
            return 0;

        // Find largest "right" so that nums[left] < nums[right]
        while (left < right)
        {
            if (nums[left] < nums[right])
                break;

            right--;
        }

        // Swap nums[right] and nums[left]
        int tmp     = nums[left];
        nums[left]  = nums[right];
        nums[right] = tmp;

        // Reverse the remaining nums[left + 1] ... nums[n - 1]
        first = left + 1;

        while (first < last)
        {
            tmp         = nums[first];
            nums[first] = nums[last];
            nums[last]  = tmp;

            first++;
            last--;
        }

        return 1;
    }
};


int
main()
{
    Solution_Backtracking_Queue sol_queue;
    Solution_Backtracking_Basic sol_basic;
    Solution_Next_Permutation   sol_next;

    /* Example 1 */
    std::vector<int> nums = {1, 2, 3};

    /* Example 2 */
    // std::vector<int> nums = {0, 1};

    /* Example 3 */
    // std::vector<int> nums = {1};

    /* Example 4 */
    // std::vector<int> nums = {0, 7, -2, -5};

    std::cout << "\n\t====================";
    std::cout << "\n\t=== PERMUTATIONS ===";
    std::cout << "\n\t====================\n";

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
    // std::vector<std::vector<int>> results = sol_queue.permute(nums);
    // std::vector<std::vector<int>> results = sol_basic.permute(nums);
    std::vector<std::vector<int>> results = sol_next.permute(nums);


    /* Write Output */
    first = true;
    std::cout << "\n\tResults: [";
    for (auto x: results)
    {
        if (!first)
            std::cout << ", ";

        bool first_first = true;
        std::cout << "[";
        for (const auto& xx : x)
        {
            if (!first_first)
                std::cout << ", ";

            std::cout << xx;
            first_first = false;
        }
        std::cout << "]";

        first = false;
    }
    std::cout << "]\n\n";

    return 0;
}
