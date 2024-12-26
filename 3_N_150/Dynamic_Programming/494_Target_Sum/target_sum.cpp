/*
    ==============
    === MEDIUM ===
    ==============

    ===========================
    494) Target Sum
    ===========================

    ============
    Description:
    ============

    You are given an integer array nums and an integer target.

    You want to build an expression out of nums by adding one of the symbols
    '+' and '-' before each integer in nums and then concatenate all the
    integers.

        For example, if nums = [2, 1], you can add a '+' before 2 and a '-'
        before 1 and concatenate them to build the expression "+2-1".

    Return the number of different expressions that you can build, which
    evaluates to target.

    ===============================================================
    FUNCTION: int findTargetSumWays(vector<int>& nums, int target);
    ===============================================================

    ==========================================================================
    ================================ EXAMPLES ================================
    ==========================================================================

    --- Example 1 ---
    Input: nums = [1,1,1,1,1], target = 3
    Output: 5
    Explanation: There are 5 ways to assign symbols to make the sum of nums be
                 target 3.

    -1 + 1 + 1 + 1 + 1 = 3
    +1 - 1 + 1 + 1 + 1 = 3
    +1 + 1 - 1 + 1 + 1 = 3
    +1 + 1 + 1 - 1 + 1 = 3
    +1 + 1 + 1 + 1 - 1 = 3



    --- Example 2 ---
    Input: nums = [1], target = 1
    Output: 1



    *** Constraints ***
    1 <= nums.length <= 20
    0 <= nums[i] <= 1000
    0 <= sum(nums[i]) <= 1000
    -1000 <= target <= 1000

*/

#include <cstddef>
#include <functional>
#include <utility>
using namespace std;

/*
    ------------
    --- IDEA ---
    ------------

    WARNING: This will not be a tabulated, perfectly optimized DP solution.
    You can find those yourself.

    This explanation will walk you through the THINKING process behind Dynamic
    Programming so that you can solve these questions on your own.

        Category Most dynamic programming questions can be boiled down to a few
        categories. It's important to recognize the category because it allows
        us to FRAME a new question into something we already know. Frame means
        use the framework, not copy an approach from another problem into the
        current problem. You must understand that every DP problem is
        different.

        Question: Identify this problem as one of the categories below before
        continuing.
            1. 0/1 Knapsack
            2. Unbounded Knapsack
            3. Shortest Path (eg: Unique Paths I/II)
            4. Fibonacci Sequence (eg: House Robber, Jump Game)
            5. Longest Common Substring/Subsequeunce

        Answer: 0/1 Knapsack

        Why 0/1 Knapsack? Our 'Capacity' is the target we want to reach 'S'.
        Our 'Items' are the numbers in the input subset and the 'Weights' of
        the items are the values of the numbers itself. This question follows
        0/1 and not unbounded knapsack because we can use each number ONCE.

        What is the variation? The twist on this problem from standard knapsack
        is that we must add ALL items in the subset to our knapsack. We can
        reframe the question into adding the positive or negative value of the
        current number to our knapsack in order to reach the target capacity
        'S'.

        States What variables we need to keep track of in order to reach our
        optimal result? This Quora post explains state beautifully, so please
        refer to this link if you are confused:
        www.quora.com/What-does-a-state-represent-in-terms-of-Dynamic-Programming

        Question: Determine State variables.  Hint: As a general rule, Knapsack
        problems will require 2 states at minimum.

        Answer: Index and Current Sum Why Index? Index represents the index of
        the input subset we are considering. This tells us what values we have
        considered, what values we haven't considered, and what value we are
        currently considering. As a general rule, index is a required state in
        nearly all dynamic programming problems, except for shortest paths
        which is row and column instead of a single index but we'll get into
        that in a seperate post.

        Why Current Sum? The question asks us if we can sum every item (either
        the positive or negative value of that item) in the subset to reach the
        target value. Current Sum gives us the sum of all the values we have
        processed so far. Our answer revolves around Current Sum being equal to
        Target.

        Decisions Dynamic Programming is all about making the optimal decision.
        In order to make the optimal decision, we will have to try all
        decisions first. The MIT lecture on DP (highly recommended) refers to
        this as the guessing step. My brain works better calling this a
        decision instead of a guess. Decisions will have to bring us closer to
        the base case and lead us towards the question we want to answer. Base
        case is covered in Step 4 but really work in tandem with the decision
        step.

        Question: What decisions do we have to make at each recursive call?
        Hint: As a general rule, Knapsack problems will require 2 decisions.

        Answer: This problem requires we take ALL items in our input subset, so
        at every step we will be adding an item to our knapsack. Remember, we
        stated in Step 2 that "The question asks us if we can sum every item
        (either the positive or negative value of that item) in the subset to
        reach the target value." The decision is: Should we add the current
        numbers positive value Should we add the current numbers negative value

        As a note, knapsack problems usually don't require us to take all
        items, thus a usual knapsack decision is to take the item or leave the
        item.

        Base Case Base cases need to relate directly to the conditions required
        by the answer we are seeking. This is why it is important for our
        decisions to work towards our base cases, as it means our decisions are
        working towards our answer.

        Let's revisit the conditions for our answers.  We use all numbers in
        our input subset.  The sum of all numbers is equal to our target 'S'.

        Question: Identify the base cases.  Hint: There are 2 base cases.

        Answer: We need 2 base cases. One for when the current state is valid
        and one for when the current state is invalid.  Valid: Index is out of
        bounds AND current sum is equal to target 'S' Invalid: Index is out of
        bounds

        Why Index is out of bounds? A condition for our answer is that we use
        EVERY item in our input subset. When the index is out of bounds, we
        know we have considered every item in our input subset.

        Why current sum is equal to target? A condition for our answer is that
        the sum of using either the positive or negative values of items in our
        input subet equal to the target sum 'S'.

        If we have considered all the items in our input subset and our current
        sum is equal to our target, we have successfully met both conditions
        required by our answer.

        On the other hand, if we have considered all the items in our input
        subset and our current sum is NOT equal to our target, we have only met
        condition required by our answer. No bueno.

        Code it If you've thought through all the steps and understand the
        problem, it's trivial to code the actual solution.

        *** Pseudo code/Python  ***
         def findTargetSumWays(self, nums, S):
            index = len(nums) - 1
            curr_sum = 0

            return self.dp(nums, S, index, curr_sum)


         def dp(self, nums, target, index, curr_sum):
            # Base Cases
             if index < 0 and curr_sum == target: return 1 if index < 0: return
                 0

            # Decisions
             positive = self.dp(nums, target, index-1, curr_sum + nums[index])
             negative = self.dp(nums, target, index-1, curr_sum + -nums[index])

             return positive + negative


        Optimize Once we introduce memoization, we will only solve each
        subproblem ONCE. We can remove recursion altogether and avoid the
        overhead and potential of a stack overflow by introducing tabulation.
        It's important to note that the top down recursive and bottom up
        tabulation methods perform the EXACT same amount of work. The only
        different is memory. If they peform the exact same amount of work, the
        conversion just requires us to specify the order in which problems
        should be solved. This post is really long now so I won't cover these
        steps here, possibly in a future post.

        Memoization Solution for Reference

        class Solution:
            def findTargetSumWays(self, nums, S):
                index = len(nums) - 1
                curr_sum = 0
                self.memo = {}

                return self.dp(nums, S, index, curr_sum)


            def dp(self, nums, target, index, curr_sum):
                if (index, curr_sum) in self.memo:
                    return self.memo[(index, curr_sum)]

                if index < 0 and curr_sum == target:
                    return 1 if index < 0 else return 0

                positive = self.dp(nums, target, index-1, curr_sum + nums[index])
                negative = self.dp(nums, target, index-1, curr_sum - nums[index])

                self.memo[(index, curr_sum)] = positive + negative return
                self.memo[(index, curr_sum)]


    Let's draw a whole decision tree for the Example 1:
    nums = [1, 1, 1, 1, 1], target = 3


                                                                                                 0
                                                                                               /   \
                                                                                              /     \
                                                                                             /       \
                                                                                            /         \
                                                                                         + /           \ -
                                                                                          /             \
                                                                                         /               \
                                                                                        /                 \
                                                                                       /                   \
                                                                                     1                      -1
                                                                                   /  \                    /  \
                                                                                  /    \ 3               2/    \ 3
                                                                                 /      \                /      \
                                                                                /       ...            ...      ...
                                                                             + /
                                                                              /
                                                                             /
                                                                            /
                                                                           2
                                                                          /  \
                                                                         /    \
                                                                        /      \
                                                                       /        \
                                                                      /          \
                                                                     /            \
                                                                    /              \
                                                                   /                \
                                                                  /                  \
                                                                 /                    \
                                                             +  /                      \  -
                                                               /                        \
                                                              /                          \
                                                             /                            \
                                                            /                              \
                                                           /                                \
                                                          /                                  \
                                                         /                                    \
                                                        /                                      \
                                                       /                                        \
                                                      /                                          \
                                                     /                                            \
                                                    /                                              \
                                                   3                                                1
                                                  / \                Repeated work                 / \
                                                 /   \                   |    |                   /   \
                                                /     \                  |    |                  /     \
                                               /       \                 |    |                 /       \
                                              /         \                |    |                /         \
                                           + /           \ -             |    |             + /           \ -
                                            /             \              |    |              /             \
                                           /               \             |    |             /               \
                                          /                 \            |    |            /                 \
                                         /                   \           |    |           /                   \
                                        /                     \          |    |          /                     \
                                       4                       2    <-----    ----->    2                       0
                                      / \                     / \                      / \                     / \
                                     /   \                   /   \                    /   \                   /   \
                                  + /     \ -             + /     \ -              + /     \ -             + /     \ -
                                   /       \               /       \                /       \               /       \
                                  5         3             3         1              3         1             1        -1
                                  |         |             |         |              |         |             |         |
                                  No       Yes           Yes        No            Yes        No            No        No





                Here is a whole Decision tree:

                                                   0
                           1                                              -1
               2                       0                       0                      -2
         3           1           1          -1           1          -1          -1          -3
      4     2     2     0     2     0     0     -2    2     0     0    -2     0    -2     -2   -4
    5   3 3   1 3   1 1  -1 3   1 1  -1 1  -1 -1 -3 3   1 1  -1 1  -1 -1 -3 1  -1 -1 -3 -1 -3 -3 -5



    You can see that there are a lot of repeated work here, therefore we can
    use Dynamic Programming to optimze that.

*/

/*
    Time  Complexity: O(n * total)

    Where 'total' is the total number of values we can pass in "bactrack"
    function.

    Or rather, the sum of the entire array.

*/
/* Space Complexity: O(n) */
class Solution {
private:
    struct PairHash {
        std::size_t operator () (const std::pair<int, int>& p) const
        {
            auto h1 = std::hash<int>()(p.first);
            auto h2 = std::hash<int>()(p.second);

            return h2 ^ (h1 << 1);
        }
    };

public:
    int findTargetSumWays(std::vector<int>& nums, int target)
    {
        std::unordered_map<std::pair<int, int>, int, PairHash> dp;
        std::function<int(int, int)> backtrack;

        backtrack = [&](int i, int total) -> int
        {
            if (i == nums.size())
                return total == target ? 1 : 0;

            if (dp.count({i, total}))
                return dp[{i, total}];

            dp[{i, total}] = backtrack(i+1, total + nums[i]) +
                             backtrack(i+1, total - nums[i]);

            return dp[{i, total}];

        };

        return backtrack(0, 0);
    }
};
