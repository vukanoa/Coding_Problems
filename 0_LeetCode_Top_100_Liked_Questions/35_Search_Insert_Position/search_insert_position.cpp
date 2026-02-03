/*
    ============
    === EASY ===
    ============

    ===========================
    35) Search Insert Position
    ===========================

    ============
    Description:
    ============

    Given a sorted array of distinct integers and a target value, return the
    index if the target is found. If not, return the index where it would be if
    it were inserted in order.

    =====
    Node: You must write an algorithm with O(log n) runtime complexity.
    =====

    ==========================================================
    FUNCTION: int searchInsert(vector<int>& nums, int target);
    ==========================================================

    ==========================================================================
    ================================ EXAMPLES ================================
    ==========================================================================

    --- Example 1 ---
    Input:  nums = [1, 3, 5, 6], target = 5
    Output: 2

    --- Example 2 ---
    Input:  nums = [1, 3, 5, 6], target = 2
    Output: 1

    --- Example 3 ---
    Input: nums = [1, 3, 5, 6], target = 7
    Output: 4

    *** Constraints ***
    1 <= nums.length <= 10^4
    -10^4 <= nums[i] <= 10^4
    nums contains distinct values sorted in ascending order.
    -10^4 <= target <= 10^4

*/

#include <vector>
#include <algorithm>
using namespace std;

/*
    ------------
    --- IDEA ---
    ------------

    This problem is the exact functionality of std::lower_bound function.

    However, let's examine all the possible cases and "prove" it.

    First, let's refresh our memory with what does std::lower_bound returns.
    It returns:

        "Find the LOWEST VALUE that the target is less than or equal to."
         (If there are repeating elements, return the smallest index)


        std::vector<int> nums = {1, 2, 4, 5, 5, 5, 5, 6, 6};
                                 0  1  2  3  4  5  6  7  8


        target(value)           *iter(value)
           |                     |
           |         ____________|
           |_____    |
                |    |                 iter (not dereferenced)
                |    |          ________|
                |    |          |
                v    v          v
                0 <= 1 at index 0
                1 <= 1 at index 0
                2 <= 2 at index 1
                3 <= 4 at index 2
                4 <= 4 at index 2
                5 <= 5 at index 3
                6 <= 6 at index 7
                7 <= not found    // Iter will be pointing to nums.end()




    1.
        **************************************************
        ***** Target that DOES INDEED exists in nums *****
        **************************************************

                            (8) is NOT nums.end()!!!
                             |
              nums.begin()   |       nums.end()
                    |        |     _____|
                    |        |___  |
                    |           |  |
                    v           v  v
            nums = [1, 3, 5, 6, 8]        , target = 5
                    0  1  2  3  4  5
                          ^        ^
                          |        |
                          |        ----- Out of Bounds
                iter ------


            In this case, index 2 is exactly what we need to return. However
            "iter" is NOT an index, therefore we have to calculate index like
            this:

                iter - nums.begin()

            since "iter" is an iterator.





    2.
        **********************************************
        ***** Target that DOESN'T exists in nums *****
        **********************************************
        (but lowest value greater than target is in the middle of nums)
                                                 ~~~~~~~~~~~~~~~~~~~~~

                            (8) is NOT nums.end()!!!
                             |
              nums.begin()   |       nums.end()
                    |        |     _____|
                    |        |___  |
                    |           |  |
                    v           v  v
            nums = [1, 3, 5, 6, 8]        , target = 2
                    0  1  2  3  4  5
                       ^           ^
                       |           |
                       |           ----- Out of Bounds
                iter ---


            In this case, again, index 2 is exactly what we need to return and
            "iter" points to element at index 2.

            Think about it - If we wanted to insert target=2, at which index
            would we do it?
            Exactly at index 2.

            again, since "iter" is not an index, we must calculate index like
            this:

                iter - nums.begin()

            since "iter" is an iterator.



    3.
        **********************************************
        ***** Target that DOESN'T exists in nums *****
        **********************************************
        (but lowest value greater than target is nums.begin()
                                                 ~~~~~~~~~~~~

                            (8) is NOT nums.end()!!!
                             |
              nums.begin()   |       nums.end()
                    |        |     _____|
                    |        |___  |
                    |           |  |
                    v           v  v
            nums = [1, 3, 5, 6, 8]        , target = 0
                    0  1  2  3  4  5
                    ^              ^
                    |              |
                    |              ----- Out of Bounds
                  iter

            In this case, again, element at which "iter" points to is exactly
            at index we need to return. In this case it's index 0.

            If we wanted to insert target=0, at which index would we do it?
            Exactly at index 0.

            again, since "iter" is not an index, we must calculate index like
            this:

                iter - nums.begin()

            since "iter" is an iterator.



    4.
        **********************************************
        ***** Target that DOESN'T exists in nums *****
        **********************************************
        (but lowest value greater than target DOESN'T exist in nums)
                                              ~~~~~~~~~~~~~~~~~~~~~

                            (8) is NOT nums.end()!!!
                             |
              nums.begin()   |       nums.end()
                    |        |     _____|
                    |        |___  |
                    |           |  |
                    v           v  v
            nums = [1, 3, 5, 6, 8]        , target = 9
                    0  1  2  3  4  5
                    ^              ^
                    |              |
                    |              ----- Out of Bounds
                  iter

            In this case, since there is target=9 in nums and since there is no
            any element greater than target=9, "iter" will point to nums.end()
            which is an element to the right of the last element, i.e. at index
            nums.size().

            However, again, since we want to see where would we insert 9,
            "iter" poitns to "element" at which's index we would want to insert
            our target=9, which is index "nums.size()"(This is out of bounds
            for now, however, once we insert it, i.e. push_back, it won't be
            anymore)

            again, since "iter" is not an index, we must calculate index like
            this:

                iter - nums.begin()

            since "iter" is an iterator and since it is nums.end(), the result
            will be:

                nums.end() - nums.begin() ==> Index: nums.size()


                                (8) is NOT nums.end()!!!
                                 |
                  nums.begin()   |       nums.end()
                        |        |     _____|
                        |        |___  |
                        |           |  |
                        v           v  v
                nums = [1, 3, 5, 6, 8]        , target = 9
                        0  1  2  3  4  5



    We realize that std::lower_bound returns the desired "element" each time,
    therefore we just want to return:

        iter - nums.begin();

    That's it.

*/

/* Time  Beats: 100.00% */
/* Space Beats:  11.67% */

/* Time  Complexity: O(logN) */
/* Space Complexity: O(1)    */
class Solution_Lower_Bound {
public:
    int searchInsert(vector<int>& nums, int target)
    {
        auto iter = lower_bound(nums.begin(), nums.end(), target);

        return iter - nums.begin(); // <==> distance(nums.begin(), iter)
    }
};




/*
    ------------
    --- IDEA ---
    ------------

    Equvalent to the above Solution, just uses my own implementation of it.

*/

/* Time  Beats: 100.00% */
/* Space Beats:  76.30% */

/* Time  Complexity: O(logN) */
/* Space Complexity: O(1)    */
class Solution_My_Lower_Bound {
public:
    int searchInsert(vector<int>& nums, int target)
    {
        const int N = nums.size();

        /* Lower Bound */
        int low  = 0;
        int high = N; // Becuase 'N' is a VALID result as well

        while (low < high)
        {
            int mid = low + (high - low) / 2;

            if (target > nums[mid])
                low  = mid + 1;
            else
                high = mid;
        }

        return low; // Or "high" it does NOT matter
    }
};
