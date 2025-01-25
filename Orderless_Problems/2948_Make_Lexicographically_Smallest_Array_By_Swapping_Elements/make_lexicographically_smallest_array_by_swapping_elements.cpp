/*
    ==============
    === MEDIUM ===
    ==============

    ================================================================
    2948) Make Lexicographically Smallest Array by Swapping Elements
    ================================================================

    ============
    Description:
    ============

    You are given a 0-indexed array of positive integers nums and a positive
    integer limit.

    In one operation, you can choose any two indices i and j and swap nums[i]
    and nums[j] if |nums[i] - nums[j]| <= limit.

    Return the lexicographically smallest array that can be obtained by
    performing the operation any number of times.

    An array a is lexicographically smaller than an array b if in the first
    position where a and b differ, array a has an element that is less than the
    corresponding element in b. For example, the array [2,10,3] is
    lexicographically smaller than the array [10,2,3] because they differ at
    index 0 and 2 < 10.

    ===================================================================================
    FUNCTION: vector<int> lexicographicallySmallestArray(vector<int>& nums, int limit);
    ===================================================================================

    ==========================================================================
    ================================ EXAMPLES ================================
    ==========================================================================

    --- Example 1 ---
    Input: nums = [1,5,3,9,8], limit = 2
    Output: [1,3,5,8,9]
    Explanation: Apply the operation 2 times:
    - Swap nums[1] with nums[2]. The array becomes [1,3,5,9,8]
    - Swap nums[3] with nums[4]. The array becomes [1,3,5,8,9]
    We cannot obtain a lexicographically smaller array by applying any more operations.
    Note that it may be possible to get the same result by doing different operations.

    --- Example 2 ---
    Input: nums = [1,7,6,18,2,1], limit = 3
    Output: [1,6,7,18,1,2]
    Explanation: Apply the operation 3 times:
    - Swap nums[1] with nums[2]. The array becomes [1,6,7,18,2,1]
    - Swap nums[0] with nums[4]. The array becomes [2,6,7,18,1,1]
    - Swap nums[0] with nums[5]. The array becomes [1,6,7,18,1,2]
    We cannot obtain a lexicographically smaller array by applying any more operations.

    --- Example 3 ---
    Input: nums = [1,7,28,19,10], limit = 3
    Output: [1,7,28,19,10]
    Explanation: [1,7,28,19,10] is the lexicographically smallest array we can obtain because we cannot apply the operation on any two indices.


    *** Constraints ***
    1 <= nums.length <= 10^5
    1 <= nums[i] <= 10^9
    1 <= limit <= 10^9

*/

#include <algorithm>
#include <deque>
#include <unordered_map>
#include <vector>
using namespace std;

/*
    ------------
    --- IDEA ---
    ------------

    This one is fairly difficult to come up with, so don't feel bad if you
    didn't manage to solve it.

    This is one of those Problems where you MUST invent greater examples in
    order to see the pattern and, eventually, get the idea.

    The very first example is a great one, but we'll do more than that.

    Example 1:
         Input: nums = [1,5,3,9,8], limit = 2
        Output: [1,3,5,8,9]


        [1, 5, 3, 9, 8]

    Since: 1, 5 and 3 have a maximum difference between consecutive elements
           less than or equal to "limit", that means we can basically rearrange
           them in any order we want.

    Look at this:

        1, 3, 5  // Aready sorted
        1, 5, 3  --> 1, 3, 5
        3, 1, 5  --> 1, 3, 5
        3, 5, 1  --> 1, 5, 3 --> 1, 3, 5
        5, 1, 3  --> 3, 1, 5 --> 1, 3, 5
        5, 3, 1  --> 3, 5, 1 --> 1, 5, 3 --> 1, 3, 5

    All of these can become "1, 3, 5"

    That means if the MAXIMUM DIFFERENCE between any two CONSECUTIVE elements
    is <= limit, then we can rearrange that SUBSEQUENCE any way we want.



    An even more obvious example is:

        [3, 2, 1],  limit = 1

    Since the MAXIMUM difference of CONSECUTIVE elements(that means if you had
    a sorted array and check the "gaps" between any two CONSECUTIVE elements)
    is <= limit.

        [3, 2, 1]  --> [1, 2, 3]
                          1  1
                          ^  ^
                          |  |
                          ------- "gaps"


    However, what if we had this:

        [5, 3, 2, 1]

    We can still "sort" [3,2,1] subarray/subsequence, but we CANNOT move 5.
    Why?

    Because 5 doesn't have ANY element to swap the position with. Closest one
    is 3, however abs(5 - 3) is 2, which is GREATER than limit, therefore we
    are NOT allowed to move the 5.

    Thus:
        [5, 3, 2, 1]   -- becomes --> [5, 1, 2, 3]


    But, what if we had this:

        [6, 5, 3, 2, 1]

    Now we CAN move our 5 since we can swap it with 6. But those two(5 and 6)
    cannot be swapped with other elements.

    So... It's like they are diferent GROUPS.


    Take a loot at this:
        [3, 6, 1, 5, 2]

    The groups that ought to be formed are {1,2,3} and {5,6}.
    But how are we going to create them?

    Or, look at the very first example:
        [1, 5, 3, 9, 8]

    Going from left-to-right, how can we know that 1 and 5 are going to end up
    in the SAME group?

    What if the 3 was at the end, like this:
        [1, 5, 8, 9, 3]

    The absolute difference between 1 and 5 is 4 which is GREATER than limit.
    So how in the world can we conclude that 1 and 5 will be in the same group?

    This is the ultimate question.
    This is the absolute crux of this solution which makes it difficult to come
    up with.

    The intuition and what should be done isn't super difficult, but this part
    is very tricky.

    Solution:
        1. We should copy "nums" to our helper vector "copied_nums"
        2. We should sort "copied_nums"
        3. We should create a vector of deques.


    First, we need to copy "nums" since, usually, it's not a good idea to
    modify the Input unless it's a copy itself. However in this problem, it is
    passed as a reference, therefore if we make any modification it may not get
    accepted.

    That's why it's always a safe but to assume we are NOT allow to modify it.

    But, why do we need to sort this "copied_nums"?

    Remember our ultimate question?
    "
        [1, 5, 8, 9, 3]

        The absolute difference between 1 and 5 is 4 which is GREATER than
        limit.

        So how in the world can we conclude that 1 and 5 will be in the same
        group?
    "

    If we've sorted this array:

        [1, 3, 5, 8, 9]

    Isn't it now EASY to know which groups are going to be formed?

    We push 1 to "group 0"
    We push 3 to "group 0" as well because abs(1 - 3) <= limit
    We push 5 to "group 0" as well because abs(3 - 5) <= limit. (That's how)

    We push 8 to "group 1" because abs(5 - 8) >  limit, and 5 is from "group 0"
    We push 9 to "group 1" because abs(8 - 9) <= limit


    But, now there's another problem. How can we know where to put these
    numbers?

    In the above example "1, 5, 3" subsequence is spaced out. Elemet 3 is at
    the very end and there are a bunch of elements that are NOT members of
    "group 0".


    To overcome that challenge, we need to have a HashMap where the key is
    going to be:
        nums[i]

    and the value is going to be the INDEX OF THE GROUP it belongs to.

        nums[i] : groupIDX

    That's why we'll call it umap_num_groupIDX.


    But why in the world do we need to have a vector of DEQUES?

    Since we are going to be iterating through NON-sorted nums at the end and
    since we wish to put current element in its correct place given its group,
    we need to have a DEQUE.

    Consider this:

        vector<deque<int>> groups = {{1,2,3}, {5,6}}
                                        0       1

        umap_num_to_groupIDX:

                 Hash Map
            |  Key  :  Value |  (I wanted to emphasize this is UNORDERED map)
            +----------------+
            |   1   :    0   |
            +----------------+
            |   6   :    1   |
            +----------------+
            |   5   :    1   |
            +----------------+
            |   3   :    0   |
            +----------------+
            |   2   :    0   |
            +----------------+



        nums = [3, 6, 1, 5, 2]
                0  1  2  3  4


    We are going to build our "result" vector iterateively, by going from i=0
    up until i=N.

        i=0:
            nums[i] = 3
            Where should we put 3?

            We DO NOT CARE about that for now! We only care about the IDX of
            the current group.

            We need to put at this place the SMALLEST element that the group,
            which 3 is a member of, has.

            That's number 1.
            That's why we needed this HashMap.

            result = {}
            {}.push_back(1)

            And now we POP 1 from the DEQUE of the "group 0" which 3 is a part
            of.

        i=1:
            nums[i] = 6

            6 is a part of "group 1".
            Smallest unassigned element from that group is 5.

            result = {3}
            {3}.push_back(5)

            We POP 5 from the DEQUE of the "group 1" which 6 is a part of.

        ...


    You get the idea.
    Go through the code once and you'll understand it now.

*/

/* Time  Beats: 12.84% */
/* Space Beats:  5.40% */

/* Time  Complexity: O(n * logn) */
/* Space Complexity: O(n)        */
class Solution {
public:
    vector<int> lexicographicallySmallestArray(vector<int>& nums, int limit)
    {
        const int N = nums.size();
        vector<int> result;

        vector<int> copied_nums = nums;
        sort(copied_nums.begin(), copied_nums.end());

        vector<deque<int>> groups;
        unordered_map<int,int> umap_num_to_groupIDX;

        for (const int& num : copied_nums)
        {
            if (groups.empty() || abs(groups.back().back() - num) > limit)
                groups.push_back( {} );

            groups.back().push_back(num);
            umap_num_to_groupIDX.insert( {num, groups.size() - 1} );
        }

        for (int i = 0; i < N; i++)
        {
            result.push_back(groups[umap_num_to_groupIDX[nums[i]]].front());
            groups[umap_num_to_groupIDX[nums[i]]].pop_front();
        }

        return result;
    }
};
