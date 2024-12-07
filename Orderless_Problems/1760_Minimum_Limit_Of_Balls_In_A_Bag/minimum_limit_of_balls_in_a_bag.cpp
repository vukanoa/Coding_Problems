#include <iostream>
#include <vector>

/*
    ==============
    === MEDIUM ===
    ==============

    =====================================
    1760) Minimum Limit of Balls in a Bag
    =====================================

    ============
    Description:
    ============

    You are given an integer array nums where the ith bag contains nums[i]
    balls. You are also given an integer maxOperations.

    You can perform the following operation at most maxOperations times:

        Take any bag of balls and divide it into two new bags with a positive
        number of balls.

            For example, a bag of 5 balls can become two new bags of 1 and 4
            balls, or two new bags of 2 and 3 balls.

    Your penalty is the maximum number of balls in a bag. You want to minimize
    your penalty after the operations.

    Return the minimum possible penalty after performing the operations.

    ================================================================
    FUNCTION: int minimumSize(vector<int>& nums, int maxOperations);
    ================================================================

    ==========================================================================
    ================================ EXAMPLES ================================
    ==========================================================================

    --- Example 1 ---
    Input: nums = [9], maxOperations = 2
    Output: 3
    Explanation:
    - Divide the bag with 9 balls into two bags of sizes 6 and 3. [9] -> [6,3].
    - Divide the bag with 6 balls into two bags of sizes 3 and 3. [6,3] -> [3,3,3].
    The bag with the most number of balls has 3 balls, so your penalty is 3 and
    you should return 3.

    --- Example 2 ---
    Input: nums = [2,4,8,2], maxOperations = 4
    Output: 2
    Explanation:
    - Divide the bag with 8 balls into two bags of sizes 4 and 4. [2,4,8,2] -> [2,4,4,4,2].
    - Divide the bag with 4 balls into two bags of sizes 2 and 2. [2,4,4,4,2] -> [2,2,2,4,4,2].
    - Divide the bag with 4 balls into two bags of sizes 2 and 2. [2,2,2,4,4,2] -> [2,2,2,2,2,4,2].
    - Divide the bag with 4 balls into two bags of sizes 2 and 2. [2,2,2,2,2,4,2] -> [2,2,2,2,2,2,2,2].
    The bag with the most number of balls has 2 balls, so your penalty is 2, and you should return 2.


    *** Constraints ***
    1 <= nums.length <= 10^5
    1 <= maxOperations, nums[i] <= 10^9

*/

using namespace std;

/*
    ------------
    --- IDEA ---
    ------------

    The problem is that Neet didn't go through the 2nd Example that has more
    than one Bag at the beginning and it confused most of us.

    Let me explain my understanding using a few examples.

    First, even when considering a "Brute Force", you MUST understand what is
    this range that Neet shows.

    It is NOT a range for ONLY splitting current number(9 in his case).

    Instead, it is the maximum possible and the lowest possible MAX value AFTER
    the split. (This is confusing, keep reading it gets a lot more clear)

    Let me say that in another way:

    Example:
        nums = [7, 5, 9]

    Current max_value is 9.

    a)
        If we performed NO operations, what would be our penalty?
        It would be 9.


    b)
        However, if we had INFINITE amount of operations, we would be able to
        split each and every bag in "nums" so that every single bag contains
        only 1 ball.

        {7} -> {1}, {1}, {1}, {1}, {1}, {1}, {1}
        {5} -> {1}, {1}, {1}, {1}, {1}
        {9} -> {1}, {1}, {1}, {1}, {1}, {1}, {1}, {1}, {1}


    So, now we know that the MINIMAL possible result(i.e. penalty) is 1.
    But to achieve that, for our example: nums=[7,5,9], we'd need:
        
        7 splits + 5 splits + 9 splits == 21 splits

    We would need maxOperations to be 21 or higher.


    On the other hand if we had maxOperations == 0, then our MINIMAL possible
    result(i.e. penalty) would be 9, since that is the largest element in
    "nums" without any splitting whatsoever.


        Now we know WHY the range is: [1 ... 9]

    Let's continue:
    Now, if we did it in a Brute-Force way, what would that even mean?

    // This is VERY important!
    WHAT is each element in this range [1 .. 9] representing EXACTLY?


    Let's say we pick number 6 from this range. WHAT is 6 representing?
    WHAT are we trying to do with it?

    We are trying to see if we can SPLIT all the elements in "nums" in such a
    way as to have 6 as the maximum value, BUT we MUST do it in maxOperations
    or LESS.

    6 represents the maximal value AFTER optimal splitting maxOperations times.

    Let me say that again, this is the absolute CRUX of the problem!

    If we've picked 6, we want to go through each element in "nums" and ask:

        How many operations is needed to split this ONE bag into TWO OR MORE
        bags that have have 6 as the biggest amount of balls in those newly
        created TWO OR MORE bags?

        nums = [7, 5, 9]
            
            {7} --> {3}, {4}   // We needed only ONE operation to achieve that
            {5} --> {5}        // This bag is ALREADY less than or equals to 6

            {9} --> {3}, {6}   // We needed only ONE operation to achieve that
                or
                --> {4}, {5}


            So now we sum amount of operations for each original bag in "nums"
            needed to create TWO OR MORE bags, per ORIGINAL bag, that do NOT
            have more than 6 balls per bag.

                1 split for 7
                0 split for 5
                1 split for 9

                1 + 0 + 1 = 2

            Thus, we conclude:

                nums=[7, 5, 9] can INDEED be transformed to nums={3,4, 5, 3,6}
                                                         or nums=[3,4, 5, 4,5]
                
                As you can see, AFTER the transformation 6 is the max_value.
                We can achieve it in maxOperations = 2 or more

    Since we've seen that we CAN INDEED get bags of 6 or less balls per bag
    using maxOperations = 2, now we can try the same thing but with 5.

    But instead of LINEARLY trying: 9, then 8, then 7, etc.

    We can perform a Binary Search. If we CAN INDEED split it as to have "mid"
    amount of balls or less per bag in maxOperations, then we consider that a
    potential result and we shrink the range and try again in hopes of finding
    a lower "mid" value that can be max_value after the split maxOperation
    times or less.

    If not, we shrink the range but to the right and try again.
    
    Here is the "Simulation" of a Binary Search on this same example and
    another explanation of those same concepts in case someone still doesn't
    understand them.



    Can we split all the bags in "nums" in maxOperations or LESS so that "mid"
    value is the maximum number of balls in any single bag?

    Example:
        nums = [7, 5, 9],  MaxOperations = 2

        // We want to make "nums" have "mid" value as its maximum
        mid = 5;

        How many operations do we need?

        9:
            How many operations we need in order to split a bag of 9 balls in
            such way as to have only bags with 5 balls as the biggest amount
            per bag?

            The answer is 1.
            Why?

            Because we can split a bag of 9 balls into two bags:
                {9} --> {4}, {5}

            As you can see, AFTER the split, maximum number of balls in one bag
            is 5(i.e. our "mid" value) or less.


        7: 
            How many operations we need in order to split a bag of 7 balls in
            such way as to have only bags with 5 balls as the biggest amount
            per bag?

            The answer is also 1.
            Why?

            Because we can split a bag of 9 balls to two bags:
                {7} --> {3}, {4}

            AFTER the split, maximum number of balls in one bag is 4.


        5: 
            How many operations we need in order to split 5 balls in such way
            as to have 5 balls as the biggest amount?

            The answer is 0.
            Why?

            Because we already have a bag of 5 balls, we don't need to split it
            further.

        

        Now we sum the total amount of operations needed to split nums=[7,5,9]
        in such a way as to make mid=5 the largest value:

            1 + 1 + 0 = 2

            2 <= maxOperations

        Therefore, we conclude that this array "nums" CAN be split in such a
        way as to have value 5 as its maximum value AFTER we split bags in
        optimal way maxOperations times.

        Thus, we can try with 4 now. But instead of going down linearly(or up)
        we can optimize this part using Binary Search.

        If our range was from 1 .. 9, and we've seen that we CAN split "nums"
        in such a way as to make 5 the biggest value, using maxOperations,
        therefore we can try (1 + (5-1)/2) = 3

        If we were to continue, we'd see that it is IMPOSSIBLE to split "nums"
        in such a way as to have 3 as the largest value in maxOperations.

        Thus, we move "left" to mid+1. ("mid" was 3, therefore left becomes 4)

        Then, we try: (4 + (5-4)/2) = 4


        And we would see that it is possible INDEED to split "nums" in such a
        way as to make 4 the largest value in maxOperations or less.

*/

/* Time  Beats: 54.67% */
/* Space Beats: 28.46% */

/* Time  Complexity: O(N * logM) */
/* Space Complexity: O(N)        */
class Solution {
public:
    int minimumSize(vector<int>& nums, int maxOperations)
    {
        ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0); // Accelerates
        
        int left  = 1;
        int right = *max_element(nums.begin(), nums.end());

        int result = right;

        while (left < right)
        {
            int mid = left + (right - left) / 2;

            if (can_divide(nums, mid, maxOperations))
            {
                right = mid;
                result = right;
            }
            else
            {
                left = mid + 1;
            }
        }

        return result;
    }

private:
    bool can_divide(vector<int>& nums, int max_balls, int& maxOperations)
    {
        int operations = 0;
        for (int i = 0; i < nums.size(); i++)
        {
            // operations += ceil(static_cast<double>(nums[i]) / max_balls) - 1;
            operations += ceil(1.0*nums[i] / max_balls) - 1;

            if (operations > maxOperations)
                return false;
        }

        return true;
    }
};
