/*
    ==============
    === MEDIUM ===
    ==============

    =======================================
    3282) Reach End of Array With Max Score
    =======================================

    ============
    Description:
    ============

    You are given an integer array nums of length n.

    Your goal is to start at index 0 and reach index n - 1. You can only jump
    to indices greater than your current index.

    The score for a jump from index i to index j is calculated as
    (j - i) * nums[i].

    Return the maximum possible total score by the time you reach the last
    index.

    ========================================================
    FUNCTION: long long findMaximumScore(vector<int>& nums);
    ========================================================

    ==========================================================================
    ================================ EXAMPLES ================================
    ==========================================================================

    --- Example 1 ---
    Input: nums = [1,3,1,5]
    Output: 7
    Explanation: First, jump to index 1 and then jump to the last index.
                 The final score is 1 * 1 + 2 * 3 = 7.

    --- Example 2 ---
    Input: nums = [4,3,1,3,2]
    Output: 16
    Explanation: Jump directly to the last index. The final score is 4 * 4 = 16

    *** Constraints ***
    1 <= nums.length <= 10^5
    1 <= nums[i] <= 10^5

*/

#include <vector>
using namespace std;

/*
    ------------
    --- IDEA ---
    ------------

    This is NOT obvious at all. It's not intuitive. However, one way you can
    try to figure out problems like this is to try with a Brute-Force.

    When you try that you'll quickly realize that, given the Constraints for
    this problem, O(n^2) Solution is most certainly unacceptable. So there must
    be some more optimal one.

    Either O(n * logn) or O(n). (or some weird O(SQRT(n)), but that's unlikely)

    Let's consider O(n * logn) for now.
    To have a Solution that runs in O(n * logn) you either have to implement it
    using:

        1) Sort + some_logic
        2) Heap
        3) Binary Search

    Since we are NOT allowed to change the order of any element and since
    elements are NOT in sorted order to begin with, then none of the 3 above
    Solutions are allowed, therefore O(n * logn) is almost certainly not a
    possible runtime for this Problem.


    Now we know:

        1) Brute-Force O(n^2) is almost certainly impossible given the
           Constraints.

        2) Sorting, Heap and Binary Search CANNOT be used for this problem,
           therefore O(n * logn) is ALSO not a Solution.

    It's VERY unlikely that Solution is some kind of O(SQRT(n)) like in
    "Sieve of Eratosthenes", therefore the only plausible possibilty is that
    we can solve this in O(n), i.e. Linear Time Complexity.


    But how can that be? It seems impossible!

    Even though it seems impossible, keep in mind that Greedy types of problems
    are incredulous. Even when you see them, you don't believe that it'll work.

    It's NOT intuitive. It's not natural to think that way.

    But... That's, it seems, our only option, isn't it?
    What other option is still on the table?


    So let's try to think of some way to solve this by being Greedy.
    Let's consider Example 1:

        Input: nums = [1,3,1,5]
                       0 1 2 3
        Output: 7


    Since we MUST begin at index 0, we want to consider jumping to the FIRST
    LARGER element to the right of the current index(i.e. index 0).

    In this case, that's a score of 3.

    How much do we have to jump to get to number 3?

        (idx_of_3 - curr_idx) * nums[curr_idx]

        That's: (1 - 0) * 1  <==>  1


    Now, we're at curr_idx = 1;

    What is the FIRST LARGER element to the right of curr_idx(i.e. index 1)?
    It's element 5, out destination.

    So how many do we need to jump to that?

        It's: (idx_of_5 - curr_idx) * nums[curr_idx]

        That's: (3 - 1) * nums[1]   <==> (2) * 3  <==> 6


    Since we've arrived at our destination, i.e. index N-1, i.e. last element
    let's check our score:

        1 + 6 = 7

        Expected Output: 7


    It seems it worked!


    Let's try with the second Example as well:

        Input: nums = [4,3,1,3,2]
                       0 1 2 3 4
        Output: 16

    Since there are NO elements to the right of the element at index 0, then
    by our Greedy logic we're checking, the Final result should be:

        (last_idx - curr_idx) * nums[curr_idx]

        That's: (4 - 0) * 4  <==> 16

    It seems that it works!


    But how should we implement it?
    We'll since we're looking for the first larger element to the right and
    since, the jump is caculated like this:

        (j - i) * nums[i]

    Meaning, there are (j - i) steps we have to take.

    So, since we're looking for the first LARGER element than the current one,
    if we HAVEN'T found one, then use the current nums[i] as the largest
    step-score we can take.

    Potentially update the max_score_so_far and add its value for each step we
    take until we are finally at our destination.


    This helped me think about the Steps:

        [3, 1, 2, 1, 4, ...]
         0  1  2  3  4

    Since from our human-perspective, we know that Greedy approach should take
    us to take to index 4, since 4 is greater than 3, we know our jump would
    make a score of:

        (4 - 0) * nums[0]  <==> (4) * 3  <==> 12

    But that's kind of more difficult to implement that we need it to be. We
    can also think that, since the score is 12, because the DISTANCE is 4, then
    it's as if we did this:

        3 to jump from index 0 to index 1
        3 to jump from index 1 to index 2
        3 to jump from index 2 to index 3
        3 to jump from index 3 to index 4


        That's: 3 + 3 + 3 + 3, which is 12.


    We done THE EXACT same thing, but incrementally instead of doing some kind
    of additional search or something like that.

    Now we know we can just iterate through every element in "nums" and as long
    as we haven't found the larger element, i.e. larger score, use the current
    score as the biggest one-step forward, towards the last element.

    Now the implementation is trivial.

*/

/* Time  Beats: 36.60% */
/* Space Beats: 59.08% */

/* Time  Complexity: O(n) */
/* Space Complexity: O(1) */
class Solution {
public:
    long long findMaximumScore(vector<int>& nums)
    {
        long long result = 0;

        int max_score_so_far = 0;
        for (int num : nums)
        {
            result += max_score_so_far;
            max_score_so_far = max(max_score_so_far, num);
        }

        return result;
    }
};
