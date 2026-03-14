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

#include <vector>
#include <algorithm>
#include <queue>
#include <unordered_set>
using namespace std;

/*
    ------------
    --- IDEA ---
    ------------

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

/* Time  Complexity: O( N * N! ) */
/* Space Complexity: O(     N! )  */
class Solution_Queue {
public:
    vector<vector<int>> permute(vector<int>& nums)
    {
        vector<vector<int>> results;

        queue<int> queue;
        for (int& num : nums)
            queue.push(num);

        /* Backtracking */
        backtracking(queue, {}, results);

        return results;
    }

private:
    void backtracking(queue<int> queue, vector<int> curr_permutation, vector<vector<int>>& results)
    {
        if (queue.empty())
        {
            results.push_back(curr_permutation);
            return;
        }

        const int QUEUE_SIZE = queue.size();
        for (int i = 0; i < QUEUE_SIZE; i++)
        {
            int num = queue.front();
            queue.pop();

            curr_permutation.push_back(num);
            backtracking(queue, curr_permutation, results);
            curr_permutation.pop_back();

            queue.push(num);
        }
    }
};




/*
    ------------
    --- IDEA ---
    ------------

    Very similar to the one above(with the Queue).

    However, this one doesn't use a queue, instead it always iterates from 0 to
    N, however it uses an unordered Set to determine if some number was already
    in use in our current combination.

    That's the whole difference.

    Conceptually it's a different way of thinking about Backtracking Solution,
    therefore I wanted to have both.

*/

/* Time  Beats: 6.12% */
/* Space Beats: 5.05% */

/* Time  Complexity: O(N * N!) */
/* Space Complexity: O(N)      */
class Solution {
public:
    vector<vector<int>> permute(vector<int>& nums)
    {
        const int N = nums.size();
        vector<vector<int>> results;

        /* Backtracking */
        backtracking({}, {}, nums, results);

        return results;
    }

private:
    void backtracking(vector<int> curr_permutation, unordered_set<int> used, vector<int>& nums, vector<vector<int>>& results)
    {
        if (curr_permutation.size() == nums.size())
        {
            results.push_back(curr_permutation); // O(N)
            return;
        }

        const int N = nums.size();
        for (int i = 0; i < N; i++)
        {
            if (used.count(nums[i]))
                continue;

            used.insert(nums[i]);
            curr_permutation.push_back(nums[i]);

            backtracking(curr_permutation, used, nums, results);

            curr_permutation.pop_back();
            used.erase(nums[i]);
        }
    }
};




/*
    ------------
    --- IDEA ---
    ------------

    TODO

*/

/* Time  Beats: 27.59% */
/* Space Beats: 10.05% */

/* Time  Complexity: O(N * N!) */
/* Space Complexity: O(N * N!) */
class Solution_Bit_Manipulation {
public:
    vector<vector<int>> permute(vector<int>& nums)
    {
        vector<vector<int>> result;

        /* Backtracking */ 
        backtrack({}, 0, nums, result);

        return result;
    }

    void backtrack(vector<int> curr_permutation, int mask, vector<int>& nums, vector<vector<int>>& result)
    {
        if (curr_permutation.size() == nums.size())
        {
            result.push_back(curr_permutation);
            return;
        }

        for (int i = 0; i < nums.size(); i++)
        {
            if ((mask & (1 << i)) == 0)
            {
                curr_permutation.push_back(nums[i]);
                backtrack(curr_permutation, mask | (1 << i), nums, result);
                curr_permutation.pop_back();
            }
        }
    }
};




/*
    ------------
    --- IDEA ---
    ------------

    Read the code and you'll understand. This is the most clean Backtracking
    Solution you'll find for this problem. Very useful concept.

*/

/* Time  Beats: 100.00% */
/* Space Beats:  70.02% */

/* Time  Complexity: O(N * N!) */
/* Space Complexity: O(N)      */
class Solution_Clean_Backtracking {
public:
    vector<vector<int>> permute(vector<int>& nums)
    {
        vector<vector<int>> results;

        /* Backtracking */
        backtracking(0, nums, results);

        return results;
    }

private:
    void backtracking(int idx, vector<int>& nums, vector<vector<int>>& results)
    {
        const int N = nums.size();

        if (idx == N)
        {
            results.push_back(nums);
            return;
        }

        for (int i = idx; i < N; i++)
        {
            swap(nums[idx], nums[i]);
            backtracking(idx + 1, nums, results);
            swap(nums[idx], nums[i]);
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
    vector<vector<int>> permute(vector<int>& nums)
    {
        vector<vector<int>> results;

        /* Base case */
        if (nums.size() == 1)
        {
            results.push_back(nums);

            return results;
        }

        /* Sort */
        sort(nums.begin(), nums.end());

        /* Push the current permutation and permute nums again */
        do
        {
            vector<int> vec_tmp;
            for (int i = 0; i < nums.size(); i++)
                vec_tmp.push_back(nums[i]);

            results.push_back(vec_tmp);
        } while (next_permutation(nums));

        return results;
    }

private:
    int next_permutation(vector<int>& nums)
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
