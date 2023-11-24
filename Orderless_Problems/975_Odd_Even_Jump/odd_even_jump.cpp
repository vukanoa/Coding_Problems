#include <iostream>
#include <vector>
#include <map>

/*
    ============
    === HARD ===
    ============

    ===========================
    975) Odd Even Jump
    ===========================

    @@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
    @@@@@@@@@@@@@@@@@@@@@@@@@@  DISCLAIMER  @@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
    @@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@

            THIS DESCRIPTION IS VERY VERY VERY VERY DECEPTIVE.
            IT IS UNBELIEVABLY POORLY WRITTEN.

            DOWN BELOW, THERE ARE LISTED REASONS WHY IT IS
            DECEPTIVE AND THERE ARE ADDITIONAL NOTES TO THE
            DESCRIPTION OF THIS PROBLEM THAT MITIGATES THIS
            DECEPTION.

    @@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
    @@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
    @@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@


    ============
    Description:
    ============

    You are given an integer array arr. From some starting index, you can make
    a series of jumps. The (1st, 3rd, 5th, ...) jumps in the series are called
    odd-numbered jumps, and the (2nd, 4th, 6th, ...) jumps in the series are
    called even-numbered jumps. Note that the jumps are numbered, not the
    indices.

    You may jump forward from index i to index j (with i < j) in the following
    way:

        During odd-numbered jumps (i.e., jumps 1, 3, 5, ...), you jump to the
        index j such that arr[i] <= arr[j] and arr[j] is the smallest possible
        value. If there are multiple such indices j, you can only jump to the
        smallest such index j.

        During even-numbered jumps (i.e., jumps 2, 4, 6, ...), you jump to the
        index j such that arr[i] >= arr[j] and arr[j] is the largest possible
        value. If there are multiple such indices j, you can only jump to the
        smallest such index j.

        It may be the case that for some index i, there are no legal jumps.

    A starting index is good if, starting from that index, you can reach the
    end of the array (index arr.length - 1) by jumping some number of times
    (possibly 0 or more than once).

    Return the number of good starting indices.

    ===========================================
    FUNCTION: int OddEvenJumps(vector<int>& A);
    ===========================================

    ==========================================================================
    ================================ EXAMPLES ================================
    ==========================================================================

    --- Example 1 ---
    Input: arr = [10,13,12,14,15]
    Output: 2

    Explanation:

    From starting index i = 0, we can make our 1st jump to i = 2 (since arr[2]
    is the smallest among arr[1], arr[2], arr[3], arr[4] that is greater or
    equal to arr[0]), then we cannot jump any more.

    From starting index i = 1 and i = 2, we can make our 1st jump to i = 3,
    then we cannot jump any more.

    From starting index i = 3, we can make our 1st jump to i = 4, so we have
    reached the end.

    From starting index i = 4, we have reached the end already.

    In total, there are 2 different starting indices i = 3 and i = 4, where we
    can reach the end with some number of
    jumps.






    --- Example 2 ---
    Input: arr = [2,3,1,1,4]
    Output: 3

    Explanation:

    From starting index i = 0, we make jumps to i = 1, i = 2, i = 3:

    During our 1st jump (odd-numbered), we first jump to i = 1 because arr[1]
    is the smallest value in [arr[1], arr[2], arr[3], arr[4]] that is greater
    than or equal to arr[0].

    During our 2nd jump (even-numbered), we jump from i = 1 to i = 2 because
    arr[2] is the largest value in [arr[2], arr[3], arr[4]] that is less than
    or equal to arr[1]. arr[3] is also the largest value, but 2 is a smaller
    index, so we can only jump to i = 2 and not i = 3.

    During our 3rd jump (odd-numbered), we jump from i = 2 to i = 3 because
    arr[3] is the smallest value in [arr[3], arr[4]] that is greater than or
    equal to arr[2].

    We can't jump from i = 3 to i = 4, so the starting index i = 0 is not good.

    In a similar manner, we can deduce that:
    From starting index i = 1, we jump to i = 4, so we reach the end.
    From starting index i = 2, we jump to i = 3, and then we can't jump anymore.
    From starting index i = 3, we jump to i = 4, so we reach the end.
    From starting index i = 4, we are already at the end.

    In total, there are 3 different starting indices i = 1, i = 3, and i = 4,
    where we can reach the end with some number of jumps.







    --- Example 3 ---
    Input: arr = [5,1,3,4,2]
    Output: 3
    Explanation: We can reach the end from starting indices 1, 2, and 4.





    *** Constraints ***
    1 <= arr.length <= 2 * 10^4
    0 <= arr[i] < 10^5

*/

/*

    @@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
    @@@@@@@@@@@@@@@@@@@@@@   ADDITIONAL NOTES   @@@@@@@@@@@@@@@@@@@@@@
    @@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@

    The Description of this problem is **VERY** problematic.

    1. It DOESN'T say that we MUST alternate between odd and even jumps, yet
       that is expected.

    2. It doesn't say that we MUST start with an odd jump, yet that is also
       expected.

    3. Description is deceptive. It is said that "odd-numbered-jumps" are (1,
       3, 5, ...) where those are the values of jumps, not the indices.
       However that doesn't seem to be true or to matter at all.

    In the very first Example given: arr = [10, 13, 12, 14, 15], once we start
    at index 0 and try to do an odd-numbered-jumping, we need to find the
    smallest value to the right that is GREATER than OR EQUALS to 10. In this
    case that is value 12.

    And we're somehow ALLOWED to jump to 12(index 2) from 10(index 0) as it
    is said in the "Explanation" part below the Example, even though we're
    previously told explicitly that "odd-numbered jumps" are (1, 3, 5, ...) and
    that is even emphasized by saying that those are values of the jumps and
    not indices.

    That seems quite deceptive since we're previously told that "odd-numbered
    jumps" are (1, 3, 5).

    One would think that once you perform an "odd jump",  you can, hint hint,
    jump forward by either of these steps: (1, 3, 5, ...) as long as current
    index + <odd steps>  is less than arr.size();

    I've spent much more time trying to figure out the Description than doing
    the problem even though this was a Hard problem. I think that tells you
    enough how poorly worded this Description is.

    @@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
    @@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
    @@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@

*/


/*
    ------------
    --- IDEA ---
    ------------

    Both Solutions down below are THE SAME, however this one uses shorter
    variable names and is, thus, easier to read once you know what is
    happening.

    However, if you're seeing the Solution for this problem for the very first
    time, I highly suggest to look the Solution_Verbose, since names are picked
    to explain the entire Solution by itself.

    However, the names are quite long, therefore, in a way, it's more difficult
    to read, hence I wrote both Solutions.



    Since we can only go to the right, from each point, we can start from the
    back and use precomputed information.

    Precomputed information that we'll use here is whether, starting at certain
    index, we can reach the end if we begin to jump:
        1. With Odd  jumps
        2. With Even jumps
    to not.

    Again, I want to emphasize what we need to alternate between jumps and we
    MUST begin with an Odd jump.

    We start from the second element from the back since we're certainly sure
    that once we start with the last element, we can reach the last element.

    Since at each index we start, we have to find:
        1. Smallest height that is Greater than or Equals to the height we're currently on
        2. Biggest  height that is Lower   than or Equals to the height we're currently on

    If you've ever used:
        1. std::lower_bound, and
        2. std::upper_bound

    You'd know that above requirements align perfectly with the description
    of these functions, respectively.

    However, we have a problem. Our array is NOT sorted and we CAN'T sort it
    since that would potentially mess the indices and we're explicitly told
    that when we jump, either odd or even it doesn't matter, we MUST just only
    from index i to index j, where (i < j).

    If we sort the array, we may infringe on that constraint.

    So, what should we do?

    Remember that we're starting from the back?
    Since we're going from the back, at each point we're currently processing,
    we know from the description that we're only able to jump to the right,
    however since we're going backwards that means that all the element forward
    are precomputed, which further means that we're allowed to sorted THEM
    because we cannot mess anything since they're already used(computed).

    However we're not going to sort the entire "right portion" each time we
    finish processing current point and move further back. That would take us
    O(n * logn) time, which is too much since we'd be doing that n times which
    would make Time Complexity of the entire Solution O(n^2 * logn). That would
    defeat the while point of binary search optimization using:
        1. std::lower_bound, and
        2. std::upper_bound

    Instead we're going to use a data structure that will help us insert the
    current point(after we're done with it) in the already sorted "right
    portion" in O(log n).

    Which, since we're going to to that after we're done processing each point,
    will make Time Complexity for the entire Solution: O(n * logn), which is
    quite an optimization from the Brute Force which is O(n^2).

    The data structure that will provide us with O(logn) Time insertions in the
    already sorted array is a Red-Black Tree.

    Thankfully, we won't be implementing it since it already exists in STL
    under the name - std::map.

    Yes, std::map is a Red-Black tree "under the hood".

    Also, it's important that we don't just insert tha heights in std::map, but
    a pair of {height, index}, since we're going to use the index to determine
    if we've reached the last position/index.

    So, to summarize:
    The last element is always able to reach itself, thus we're inserting it in
    the std::map immediately.

    We start processing each element going backwards, starting at the second
    element from the back.

    While we're processing current height, i.e. we're checking if we can reach
    the last position/index from this index starting with ODD Jumping(this is
    important not to forget) and we have to alternate between Odd and Even
    Jumps.

    Since we have precomputed elements, the only thing we have to do at each
    point is:
        1. Find the lowest element to the right that is greater than or equal
           to current height.

        2. If we've found it(meaning there is such an element to the right),
           then check if from that element we can reach the end BUT STARTING
           WITH AN EVEN JUMP(Since we've just performed an Odd Jump).
           Store that boolean value in:
            odd__starting_reach_end = <true or false>;

        3. Now precompute if you can reach the last position/index STARTING
           WITH EVEN JUMP(even though we cannot actually start with it) so that
           we can save this result and use it for later element that stumble on
           this height with their Odd Jumping.

        4. We will do that by finding the greatest element to the right that is
           lower than or equal to the current height.

        5. If we've found it(meaning there is such an element to the right),
           then check if that element can reach the end BUT STARTING WITH AN
           ODD JUMP(since we've just performed an Even Jump).
           Store that boolean value in:
            even_starting_reach_end = <true or false>;

        6. Check if we're able to reach the end from this current index
           starting with an ODD Jump. If we can, then:
            result++;

    At the end just return variable result.

*/

/* Time  Beats: 91.50% */
/* Space Beats: 56.19% */

/* Time  Complexity: O(n * logn) */
/* Space Complexity: O(n) */
class Solution_Short {
public:
    int oddEvenJumps(vector<int>& A)
    {
        int n  = A.size();

        // For the last index we're already at the end
        int result = 1;

        std::vector<int> higher(n);
        std::vector<int> lower(n);

        higher[n - 1] = 1;
        lower[n - 1]  = 1;

        std::map<int, int> map;
        map[A[n - 1]] = n - 1;

        for (int i = n-2; i >= 0; --i)
        {
            auto hi = map.lower_bound(A[i]); // Nearest Greater Or Equals
            auto lo = map.upper_bound(A[i]); // First   Greater

            if (hi != map.end())
                higher[i] = lower[hi->second];

            if (lo != map.begin())
                lower[i] = higher[(--lo)->second];

            if (higher[i])
                result++;

            map[A[i]] = i;
        }

        return result;
    }
};




/*
    ------------
    --- IDEA ---
    ------------

    Idea is absolutely equivalent to the one above, it just uses different
    variable names to make it easy to follow.

*/

/* Time  Beats: 86.51% */
/* Space Beats: 85.95% */

/* Time  Complexity: O(n * logn) */
/* Space Complexity: O(n) */
class Solution_Verbose {
public:
    int oddEvenJumps(vector<int>& A)
    {
        int n  = A.size();

        // For the last index we're already at the end
        int result = 1;

        std::vector<bool> odd__starting_reach_end(n);
        std::vector<bool> even_starting_reach_end(n);
        odd__starting_reach_end[n - 1] = true;
        even_starting_reach_end[n - 1] = true;

        // {Key=height : Value=index}
        std::map<int, int> map;
        map[A[n - 1]] = n - 1;

        for (int i = n-2; i >= 0; --i)
        {
            auto nearest_greater_or_equal = map.lower_bound(A[i]);
            auto first_greater            = map.upper_bound(A[i]);

            // ->second represents the index, since in our Map Key=height and Value=index

            if (nearest_greater_or_equal != map.end())
                odd__starting_reach_end[i]  = even_starting_reach_end[nearest_greater_or_equal->second];

            if (first_greater != map.begin())
                even_starting_reach_end[i] = odd__starting_reach_end[(--first_greater)->second];

            if (odd__starting_reach_end[i])
                result++;

            map[A[i]] = i;
        }

        return result;
    }
};
