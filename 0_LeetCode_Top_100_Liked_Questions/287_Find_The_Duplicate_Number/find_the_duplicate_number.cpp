/*
    ==============
    === MEDIUM ===
    ==============

    ==============================
    287) Find the Duplicate Number
    ==============================

    ============
    Description:
    ============

    Given an array of integers "nums" containing n + 1 integers where each
    integer is in the range [1, n] inclusive.

    There is only one repeated number in "nums", return this repeated number.

    // ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
        My Note(This isn't a part of LeetCode Description)

        (This means that one number can repeat multiple times, not that the
        repeating number can repeat once, i.e. repeating number has frequency
        of 2 while other have frequency of 1.

        This is possible: [2, 2, 2, 2, 2])
    // ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

    You must solve the problem WITHOUT modifying the array "nums" and uses
    only constant extra space.

    Follow up:
        - How can we prove that at least one duplicate number must exist in
          "nums"?

        - Can you solve the problem in linear runtime complexity?

    ===============================================
    FUNCTION: int findDuplicate(vector<int>& nums);
    ===============================================

    ==========================================================================
    ================================ EXAMPLES ================================
    ==========================================================================

    --- Example 1 ---
    Input:  nums = [1, 3, 4, 2, 2]
    Output: 2

    --- Example 2 ---
    Input:  nums = [3, 1, 3, 4, 2]
    Output: 3

    --- Example 3 ---
    Input:  nums = [2, 2, 2, 2, 2]
    Output: 2

    *** Constraints ***
    1 <= n <= 10^5
    nums.length == n + 1
    1 <= nums[i] <= n
    All the integers in "nums" appear only *once* except for *precisely one
    integer* which appears two or more times.

*/

#include <cstdlib>
#include <vector>
using namespace std;

/*
    ------------
    --- IDEA ---
    ------------

    Floyd's Tortoise and Hare (Cycle Detection)

    Intuition
    The idea is to reduce the problem to Problem: 142 Linked List Cycle II
    "Given a linked list, return the node where the cycle begins."

    First of all, where does the cycle come from? Let's use the function
    f(x) = nums[x] to construct the sequence:

        x, nums[x], nums[nums[x]], nums[nums[nums[x]]], ...

    Each new element in the sequence is an element in nums at the index of the
    previous element's value.

    The cycle appears because "nums" contains duplicates. The duplicate node
    is a cycle entrance

    Here is how it works:

    ----------   --------
    |        v   v       |
    |    0 1 2 3 4 5 6   |
    |    2 6 4 1 3 1 5   |
    |    |   |           |
    ------   -------------

    (etc. you get the point. Every VALUE is used as a POINTER. And instead
    of having addresses as pointers which you dereference, we use indices
    instead.

    And dereferencing is the same:

        nums[4] <==> *(nums + 4)


    Explanation:

    Remember that the length of array is n + 1, but every value in the array is
    going to be between [1, n].

    So there is n different values, but there is n + 1 positions.

    Example:

        nums = [1, 3, 4, 2, 2]              length = n + 1;
             i  0  1  2  3  4               nums[i] in [1, n]

    Here we have 5 elements and we know that the elements are going to be in
    range [1...4].

    So instead of thinking about elements as values, let's think of them as
    pointers.

    We know for sure that every single value in the array is going to be in the
    range [1...4], that means - If we considered every value as a pointer, each
    value is going to point at some position in this block of remaining 4
    elements.

        nums = [1, 3, 4, 2, 2]
                0  1  2  3  4

        Element 1 points to index 1, which is element of value 3.
        Element 3 points to index 3, which is element of value 2.
        Element 2 points to index 2, which is element of value 4.
        Element 4 points ot index 4, which is element of value 2.

    Linked List equivalent of this array:


        0 -> 3 -> 2 _
                 ^   \
                /     \
                \     /
                 \   /
                  \ v
                   4


                0  1  2  3  4
        nums = [1, 3, 4, 2, 2]
                   ~~~~^~~~~~
                       ^
                       |__________
                                 |
                                 |
                                 |
    It's not hard to see that this portion is going to form a cycle because no
    matter what value we look at it's going to point at some other value inside
    this range.

    There's never going to be an exit condition. None of these values are going
    to point outside of the range. So this portion is going to form a cycle
    linked list somewhere.


        nums = [1, 3, 4, 2, 2]
              ^
              |
              |______
                    |
    But what about this value? Is that value going to be a part of the cycle?

        nums = [1, 3, 4, 2, 2]
                   ~~~~^~~~~~
                       ^
                       |___
                          |
                          |
                          |
    Notice how none of these values are ever going to point at index 0,
    meaning - outside of the range. The range is ALWAYS [1 - n], i.e. [1 - 4]
    in this case.

    So none of the elements, values, is going to be zero, so non of them is
    going to point at index 0, therefore we can guarantee that element at
    index 0 is never going to be a part of the cycle.

    And you can notice that in the Linked List representation:
    This is not part of the cycle.
      |
      |
      |_
        |        ______________
        v        |            |
        0 -> 3 --|--> 2 _     |
                 |   ^   \    |
                 |  /     \   |
                 |  \     /   |
                 |   \   /    |
                 |    \ v     |
                 |     4      |
                 |____________|

                        ^
                        |
                        |
                        |
        Cycle ----------


    And that's going to be very important. Once we start traversing this linked
    list, we'll always start at node with value 0, because we know that is NOT
    a part of the cycle.

    In this example 2 is the Duplicate number. Element at index 3 and element
    at index 4 are both going to be pointing at index 2. So what does that tell
    us about our Linked List??

    That means at the node, that's labeled "2", multiple nodes are going to be
    pointing to node 2. Therefore, we know that that node is going to be the
    start of the cycle.

    We know for sure there is going to be a cycle and we know for sure that
    there is going to be a portion before the cycle.

    If we can somehow identify the beginning of the cycle in this Linked List,
    then we will know that beginning of the cycle is the return value that
    we're looking for.

    So, at this point it's all about applying Floyd's Algorithm to find the
    beginning of a cycle.

    So, once you've determined that it's a Linked List problem, then you just
    need to apply this Floyd's Algorithm.

    Note: Floyd's Algorithm is also not very intuitive. If you haven't seen
    this "trick", it's very unlikely that you will be able to solve it even if
    it's not that hard. It's just that it's not intuitive.

    Let's look at a slightly different example to illustrate Floyd's Algorithm:


        0 ---> 1 -------> 2
                ^        /
                 \      /
                  \    /
                   -3<-

    First I'm going to explain what the Floyd's Algorithm is and then I'm going
    to explain a bit of Intuition of why it actually works.

    ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
    ~~~~~ Floyd's Algorithm ~~~~~~
    ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

    I)

    So both "slow" and "fast" pointers are going to start at node with value 0.
    Both will be moved at the same time (per iteration).

    "slow" pointer is going to be shifted by one node each iteration, whereas
    "fast" pointer is going to be shifted by two nodes each iteration.

    Try it yourself and you'll see that they'll end up meeting at node with
    value 3.
    That node is represents the Intersection.


        0 ---> 1 -------> 2
                ^        /
                 \      /
                  \    /
                   -3<-
                    ^ (Intersection)
                   / \
                  /   \
                 /     \
          slow --       --- fast

    So that is the 1st phase of the algorithm.

    II)
        Then we take our "slow" pointer and put it right at the beginning(at
        node with value 0).

        slow ---
        _______|
        |
        |
        v
        0 ---> 1 -------> 2
                ^        /
                 \      /
                  \    /
                   -3<-
                    ^
                    |
                    |
        fast --------

        And now we're going to keep shifting both "slow" and "fast" pointers
        by ONE each iteration until they intersect again. The node at which
        they Intersect ***MUST*** be the beginning of the cycle!


         slow     fast
            \     /
             \   /
              \ /
               v (100 % Beginning of the Cycle!)
        0 ---> 1 -------> 2
                ^        /
                 \      /
                  \    /
                   -3<-

        It's not intuitive at all why this second Intersection absolute MUST be
        the beginning of a cycle, so let me explain:

        So this Algorithm relies on the fact that the first Intersection(node 3
        in this example) between two pointers, the distance between this first
        Intersection and the beginning of the cycle is THE SAME as the distance
        between the beginning of the Linked List and the beginning of the
        cycle.

        In this case distance is 1.
           1
        0 -|-> 1 -------> 2
           |    ^        /
           <=>---\1     /
                  \    /
                   -3<-

        That's why we can take "slow" pointer(which is at the beginning of
        Linked List) and "fast" pointer(which is at the first Intersection,
        node 3 in this case) and shift each by one each iteration until they
        meet. Since the distance from the beginning of the cycle is THE SAME
        from either point, that means they MUST meet at the beginning of the
        cycle.

        But WHY is the case that the distance between first Intersection point
        and beginning of the cycle is the same as the distance from the Start
        of the Linked List to the beginning of the cycle?

        Let's look at even bigger example:

        0 ---> 1 -------> 2 -----> 3
                ^                 /
                 \               /
                  \             /
                   -5 <---- 4 <-

        Let's say that 'p' is the number of previous nodes we have before the
        actual start of the cycle.

        And let's say arbitrarily that node "5" is the first Intersection point
        between the two pointers.

           p
        0 ---> 1 -------> 2 -----> 3
                ^                 /
                 \X              /
                  \             /
                   -5 <---- 4 <-
                    ^
            ________|
            |
            |
        arbitrarily picked first Intersection. (Let's label the distance from
        this node to the beginning of the node 'X'). Let's not label it 'p'
        since we have not sure that it's going to be the same.

        The remaining portion of the CYCLE is going to be: C - X
        C is the length of the cycle, 5 in this case.

        So the total Cycle is 5, i.e C, but the remaining portion of the Cycle
        is:
            C - X

        where X is the distance between first Intersection and the beginning of
        the Linked List.

        So we know that the "slow" pointer is going to start out at the
        beginning, it's going to traverse this 'p' portion and then it's going
        to traverse this C-X portion and it's going to land at first
        Intersection point(5 in this case).

        Now we know that "fast" pointer is going to do more than that. It's
        going to do this 'p' portion once, then it's going to do a COMPLETE
        loop(remember that the "fast" pointer is going to out loop "slow"
        pointer before they meet at first Intersection point) and it's going to
        overlap a "slow" pointer.

        So it's going to do at least one FULL loop and the it's going to be at
        the beginning of the cycle and then it's going to traverse "C-x"
        portion to get to the first Intersection point where will overlap with
        the "slow" pointer.

        We, currently, don't know where the Intersection point is going to be,
        it could be anywhere, so let's write that mathematical equation out:

        So we know that 2 times number of nodes the slow pointer moves is equal
        to the number of nodes the fast pointer moves:
            2 * slow = fast

        So how many nodes did we say that the "fast" pointer does? It's going
        to do:
            p + C + (C - X)

            'p' to get to the beginning of the cycle.
            'C' to do one COMPLETE loop.
            "C - X" until it catches up with "slow" pointer.

            Again let's write it down:
            2 * slow = fast
            2 * slow = p + C + (C - X)

               Or, more neatly written:

            2 * slow = p + 2C - X

            And what about the "slow" pointer? How many nodes did we say that
            the "slow" pointer does? It's going to do:
                p + (C - X)

            Let's get it back in the equation:
                2 * (p + (C - X)) = p + 2C - X

            Simplify the equation a bit:
                2p + 2C - 2X = p + 2C - X

            This is the part where we could start doing a bit of algebra:
            Cross "2C" from both sides. Cross one X on both sides. Cross one p
            from both sides of the equation.

            Once we do that, we end up with:
                p - X = 0

            Which is:
                p = X

        And we just proved that p MUST be equal to X. So once we get to the
        first Intersection point and return "slow" pointer to the beginning of
        the Linked List and start moving each of those pointer by one per
        Iteration, we're guaranteed that they'll meet at the beginning of the
        Cycle.

*/

/* Time  Beats: 82.73% */
/* Space Beats: 87.42% */

/* Time  Complexity: O(N) */
/* Space Complexity: O(1) */
class Solution {
public:
    int findDuplicate(vector<int>& nums)
    {
        int slow = nums[0];
        int fast = nums[0];

        // Find the "intersection" point of the two runners
        do
        {
            slow = nums[slow];
            fast = nums[nums[fast]];
        } while (slow != fast);

        // Find the "entrance" to the cycle.
        slow = nums[0];
        while (slow != fast)
        {
            slow = nums[slow];
            fast = nums[fast];
        }

        return fast;
    }
};




/*
    ------------
    --- IDEA ---
    ------------

    Every number from range [1..N-1] should appear EXACTLY once, however in
    our "nums", we know that one number appears TWICE.

    Therefore, we count for each BIT, how many times does it appear.

    If it appears more than the time it SHOULD appear in range [1..N] were
    there only non-duplicates, then we know this bit is CERTAINLY going to be
    included in the final result.

    We construct the final result by SETTING that bit.

*/

/* Time  Beats: 20.44% */
/* Space Beats: 89.51% */

/* Time  Complexity: O(32 * N) --> O(N) */
/* Space Complexity: O(1)               */
class Solution_Bit_Masking {
public:
    int findDuplicate(vector<int>& nums)
    {
        const int N = nums.size();
        int result = 0;

        // O(32 * N) (entire block)
        for (int bit_position = 0; bit_position < 32; bit_position++) // O(32)
        {
            int actual_count_at_bit_position = 0;
            int expected_count_at_bit_position = 0;

            int mask = 1 << bit_position;

            // Count how many numbers in the array have this bit set
            for (int number : nums) // O(N)
            {
                if (number & mask)
                    actual_count_at_bit_position++;
            }

            // Count how many numbers in range [1..N-1] should have this bit set
            for (int number = 1; number < N; number++) // O(N)
            {
                if (number & mask)
                    expected_count_at_bit_position++;
            }

            // If we found more numbers with this bit set than expected,
            // then that means duplicate number MUST have this bit set
            if (actual_count_at_bit_position > expected_count_at_bit_position)
                result |= mask;
        }

        return result;
    }
};




/*
    ------------
    --- IDEA ---
    ------------

    Since we're told that EVERY value in "nums" is going to be [1..N-1], then
    every value should have its own unique position in the vector.

    We can iterate through "nums" in order and each time we see a value, we
    MARK it by multiplying the value at nums[correct_position] with -1.

    However, if we stumble upon a value where the number correct_position is
    ALREADY NEGATIVE, that indicates some previous number of the SAME VALUE has
    already marked that position.

    Therefore, we know there is a DUPLICATE value to the current one and that
    is our answer.

*/

/* Time  Beats: 100.00% */
/* Space Beats:  68.83% */

/* Time  Complexity: O(N) */
/* Space Complexity: O(1) */
class Solution_Negative_Marking {
public:
    int findDuplicate(vector<int>& nums)
    {
        const int N = nums.size();

        for (int i = 0; i < N; i++)
        {
            int value            = abs(nums[i]);
            int correct_position = value - 1;

            // If "val" is ALREADY SEEN--that's the answer
            if (nums[correct_position] < 0)
                return value;

            nums[correct_position] *= -1; // Mark current value as SEEN so far
        }

        return -1; // Unreachable code
    }
};




/*
    ------------
    --- IDEA ---
    ------------

    The idea is very similar to the above one with "Negative Marking". However,
    this one, instead, swaps elements to its correct positions.

    As soon as some value is NOT where it should be, however in index "correct
    position"  there is ALREADY that value, that indicates this is a DUPLICATE.

    It is important to be aware of both techniques, as someone you can apply
    only one and not the other.

*/

/* Time  Beats: 67.66% */
/* Space Beats: 89.51% */

/* Time  Complexity: O(N) */
/* Space Complexity: O(1) */
class Solution_In_place_Swapping {
public:
    int findDuplicate(vector<int>& nums)
    {
        const int N = nums.size();
        
        // Place each number at its correct position
        for (int i = 0; i < N; i++)
        {
            // While the current number is NOT at its correct position
            while (nums[i] != (i+1))
            {
                int correct_position = nums[i] - 1;
                
                // If the correct position ALREADY has this number, we have
                // found the duplicate
                if (nums[correct_position] == nums[i])
                    return nums[i];
                    
                // Swap the current number to its correct position
                swap(nums[i], nums[correct_position]);
            }
        }

        return -1; // Unreachable code
    }
};
