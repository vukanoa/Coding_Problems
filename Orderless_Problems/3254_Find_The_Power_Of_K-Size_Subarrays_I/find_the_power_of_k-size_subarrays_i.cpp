#include <iostream>
#include <vector>

/*
    ==============
    === MEDIUM ===
    ==============

    ==========================================
    3254) Find the Power of K-Size Subarrays I
    ==========================================

    ============
    Description:
    ============

    You are given an array of integers nums of length n and a positive integer
    k.

    The power of an array is defined as:

        Its maximum element if all of its elements are consecutive and sorted
        in ascending order.

        -1 otherwise.

    You need to find the power of all subarrays of nums of size k.

    Return an integer array results of size n - k + 1, where results[i] is the
    power of nums[i..(i + k - 1)].

    =============================================================
    FUNCTION: vector<int> resultsArray(vector<int>& nums, int k);
    =============================================================

    ==========================================================================
    ================================ EXAMPLES ================================
    ==========================================================================

    --- Example 1 ---
    Input: nums = [1,2,3,4,3,2,5], k = 3
    Output: [3,4,-1,-1,-1]
    Explanation:
    There are 5 subarrays of nums of size 3:
        [1, 2, 3] with the maximum element 3.
        [2, 3, 4] with the maximum element 4.
        [3, 4, 3] whose elements are not consecutive.
        [4, 3, 2] whose elements are not sorted.
        [3, 2, 5] whose elements are not consecutive.


    --- Example 2 ---
    Input: nums = [2,2,2,2,2], k = 4
    Output: [-1,-1]


    --- Example 3 ---
    Input: nums = [3,2,3,2,3,2], k = 2
    Output: [-1,3,-1,3,-1]


    *** Constraints ***
    1 <= n == nums.length <= 500
    1 <= nums[i] <= 10^5
    1 <= k <= n

*/

/*
    ------------
    --- IDEA ---
    ------------

    This one was pretty easy.

    Note that the elements have to be sorted in CONSECUTIVE ascending order.

        Good: [3, 4, 5, 6, 7]
        Bad:  [3, 6, 7, 9, 10]

    Let's consider a Brute-Force approach first:

        nums = [2, 7, 1, 4, 5, 6, 7, 8, 9, 10, 11, 4, 7, 2, 17, 18, 19, 20, 21]
        k = 5

    (I've devised a longer example so that the optimization is more obvious)

    Since k=5, we have to make sure that all the elements:
        
        from left=0 to right=k-1, inclusively, are sorted in CONSECUTIVE
        ascending order.
    
    Brute-Forcing is would look like this:

               start
                |
                v
                #
        nums = [6, 7, 8,19, 5, 6, 7, 8, 9, 10, 11, 4, 7, 2, 17, 18, 19, 20, 21]
                0  1  2  3  4  5  6  7  8   9  10 11 12 13  14  15  16  17  18
                i


        nums = [6, 7, 8, 9, 5, 6, 7, 8, 9, 10, 11, 4, 7, 2, 17, 18, 19, 20, 21]
                0  1  2  3  4  5  6  7  8   9  10 11 12 13  14  15  16  17  18
                   i

        nums = [6, 7, 8, 9, 5, 6, 7, 8, 9, 10, 11, 4, 7, 2, 17, 18, 19, 20, 21]
                0  1  2  3  4  5  6  7  8   9  10 11 12 13  14  15  16  17  18
                      i

        nums = [6, 7, 8, 9, 5, 6, 7, 8, 9, 10, 11, 4, 7, 2, 17, 18, 19, 20, 21]
                0  1  2  3  4  5  6  7  8   9  10 11 12 13  14  15  16  17  18
                         i

        nums = [6, 7, 8, 9, 5, 6, 7, 8, 9, 10, 11, 4, 7, 2, 17, 18, 19, 20, 21]
                0  1  2  3  4  5  6  7  8   9  10 11 12 13  14  15  16  17  18
                            i

    Only at the very end of the first subarray of length k would we find out
    that the subarray is NOT sorted in CONSECUTIVE ascending order.

    Okay, then let's try the next Subarray:

                  start
                   |
                   v
                   #
        nums = [6, 7, 8,19, 5, 6, 7, 8, 9, 10, 11, 4, 7, 2, 17, 18, 19, 20, 21]
                0  1  2  3  4  5  6  7  8   9  10 11 12 13  14  15  16  17  18
                   i

        nums = [6, 7, 8, 9, 5, 6, 7, 8, 9, 10, 11, 4, 7, 2, 17, 18, 19, 20, 21]
                0  1  2  3  4  5  6  7  8   9  10 11 12 13  14  15  16  17  18
                      i

        nums = [6, 7, 8, 9, 5, 6, 7, 8, 9, 10, 11, 4, 7, 2, 17, 18, 19, 20, 21]
                0  1  2  3  4  5  6  7  8   9  10 11 12 13  14  15  16  17  18
                         i

        nums = [6, 7, 8, 9, 5, 6, 7, 8, 9, 10, 11, 4, 7, 2, 17, 18, 19, 20, 21]
                0  1  2  3  4  5  6  7  8   9  10 11 12 13  14  15  16  17  18
                            i
                (At this point, i=4) we would find out that this is NOT sorted

        
        nums = [6, 7, 8, 9, 5, 6, 7, 8, 9, 10, 11, 4, 7, 2, 17, 18, 19, 20, 21]
                0  1  2  3  4  5  6  7  8   9  10 11 12 13  14  15  16  17  18
                               i

    Do you see the repeated work?

    When we were checking if the first subarray is sorted, we realized that it
    is not because element at i=4 is NOT CONSECUTIVE to the previous element at
    i=3.

    Thus, why would we, again, iterate through most of the next subarray only
    to find what we already know? We know that it is NOT sorted.

    If the previous subarray was NOT sorted, then certainly the next won't be
    either, for every k > 1, because there is an overlap between the subarrays.


    We're going to solve this by using a "Sliding Window" technique, or the
    "Two Pointers", you could call it "Two Pointers" as well.

    We're going to have "left" and "right" pointers, but we will need another
    pointer to take care of the "sortedness" in cases k > 2.

    Another helper pointer will be called "mid" and it's going to take care of
    the "sortedness" of the current subarray.

    What is "sortedness" in this context?

    As we've seen there is a LOT of repeated work if we iterate through every
    subarray from the beginning to the end. Thus what we could do is start with
    "mid" pointer at k-1 index and then go backwards as long as the elements
    are in CONSEUCTIVE order.

    We stop once either:
        1) We hit index with our "mid" pointer, or
        2) We find out that the element to the left of "mid" pointer is NOT
           in consecutive order.

    What "mid" pointer will represent is the index from which the remaining
    part of the CURRENT subarray(i.e. until "right" pointer, inclusively) is
    sorted in CONSECUTIVE ascending order.

    That way, we won't need to iterate through every subarray from its
    beginning, instead we'll always know in O(1) if the new subarray is sorted
    in CONSECUTIVE ascending order or NOT.

    For a subarray to be ENTIRELY sorted in CONSECUTIVE ascending order, we
    need "left" and "mid" pointer to be pointing at the SAME ELEMENT.

    Remember, "left" represents the first element in the CURRENT subarray.
    While,"mid" represents the starting element from which the CURRENT subarray
    is sorted until the end of the array(i.e. until the "right pointer
    inclusively)

    ONLY when left == mid, we know that the CURRENT subarray is indeed sorted
    in CONSECUTIVE ascending order.


    Everytime we slide the current window(i.e. "left" and "right" pointers) to
    the right by 1 element, what should we do with "mid" pointers?

    How should it be taken care of?

    Luckily, there are only 2(maybe 3 ways) in which we'll take care of "mid"
    before we try the next subarray.

        1) Once we updated the "right" pointer, we can immediately ask if the
           previous element(to the left of "right" pointer) is exactly smaller
           by 1 than the current element. (that's what it means to be
           consecutive)

                     right(AFTER we've moved it to the right by 1 element)
                       |
                       v
                ... 5, 6, ... // Good, it is INDEED consecutive
                ... 5, 9, ... // Bad,  it is NOT    consecutive
                ... 5, 2, ... // Bad,  it is NOT    consecutive

            In this case, we can say that: mid = right
            Why?

            Because ANY subarray that is NOT starting at current "right" index,
            is IMPOSSIBLE to be in CONSECUTIVE ascending order. The first
            subarray that can be, potentially, sorted in CONSECUTIVE ascending
            order is the one that STARTS at current "right" index.

            If this seems confusing, look at the below example:

                nums = [6, 7, 8, 9, 5, 6, 7, 8, 9, 10, 11, 4, 7, 2]
                        0  1  2  3  4  5  6  7  8   9  10 11 12 13
                        L           R

            We know that the element BEFORE nums[4]=5 is nums[4]=9 which is NOT
            in CONSECUTIVE ascending order, therefore we are CERTAIN that ANY
            subarray that has elements nums[3]=9 and nums[4]=5 is IMPOSSIBLE to
            be sorted in CONSECUTIVE ascending order.

            Let's consider all subarrays that contains nums[3]=9 and nums[4]=5:
                
                1)          |             |
                    nums = [|6, 7, 8, 9, 5| 6, 7, 8, 9, 10, 11, 4, 7, 2]
                            |0  1  2  3  4| 5  6  7  8   9  10 11 12 13
                            |             |
                
                2)             |             |
                    nums = [ 6,|7, 8, 9, 5  6| 7, 8, 9, 10, 11, 4, 7, 2]
                             0 |1  2  3  4  5| 6  7  8   9  10 11 12 13
                               |             |
                
                3)                |             |
                    nums = [ 6, 7,|8, 9, 5  6, 7| 8, 9, 10, 11, 4, 7, 2]
                             0  1 |2  3  4  5  6| 7  8   9  10 11 12 13
                                  |             |
                
                4)                   |              |
                    nums = [ 6, 7, 8,|9, 5  6, 7, 8,|9, 10, 11, 4, 7, 2]
                             0  1  2 |3  4  5  6  7 |8   9  10 11 12 13
                                     |              |

            All four of these subarrays contains both nums[3]=9 and nums[4]=5,
            thus we KNOW that it is IMPOSSIBLE for these subarrays to be sorted
            in CONSECUTIVE ascending order.

            That is why we are moving "mid" pointer to "right" index. It's
            IMPORTANT that we're doing this when "right" is at the element that
            is NOT contuinuing the sequence.

            In the first subarray that was nums[4]=5.

            We know that in the current subarray(the first subarray) all the
            elements from "mid" until the end of the subarray are sorted in
            CONSECUTIVE ascending order. In thi case, unfortunately, there is
            only a single element.

            Each time we MOVE "right" pointer to the one, we check if the
            previous elements+1 is equal to the current element. If it is NOT,
            then and only then do we move "mid" to point at "right" index
            because of the reasons explained up above.


        2) We move "left" and "right" pointer by 1 element to the right each
           time, but in this case "mid" pointer STAYS where it is OR it moves
           to point at index "left"(after its shift).

           Consider this example:

               nums = [1, 2, 3, 4, 3, 2, 5],   k = 3
                       0  1  2  3  4  5  6
                       L     R
                       M

            In the first subarray we've realized that it is sorted indeed in
            CONSECUTIVE ascending order and thus "mid" pointer(designated as M)
            points to the same index as "left" pointer(designated as L).

            Now we shift "left" and "right" pointers to the right by 1 element:

               nums = [1, 2, 3, 4, 3, 2, 5],   k = 3
                       0  1  2  3  4  5  6
                       M  L     R
                
            But if we don't do anything, then our "mid" pointer is deprecated.
            Then we would need to, again, iterate over new subarray, which
            we've concluded was inefficient.

            In this case we update "mid" pointer to point where now "left"
            points, AFTER the slide.


            However, let's consider a case where we DON'T touch "mid" pointer
            after we move "left" and "right" pointer by 1 element to the right.


                k = 6(Six)
                nums = [2, 3, 1, 7, 8, 9, 10, 7, 8, 9, 10, 11, 4, 7, 2]
                        0  1  2  3  4  5   6  7  8   9  10 11 12 13
                        L        M     R

            In this first subarray, we've realized that from index
            M=3(inclusively), until the end of the subarray, all the elements
            are sorted in CONSECUTIVE ascending order.

            Since the current subarray is NOT sorted in CONSECUTIVE ascending
            order, we shift our "left" and "right" pointer by 1 element to the
            right.


                k = 6(Six)
                nums = [2, 3, 1, 7, 8, 9, 10, 7, 8, 9, 10, 11, 4, 7, 2]
                        0  1  2  3  4  5   6  7  8   9  10 11 12 13
                           L     M         R

            But what should we do with "mid" pointer now?
            Well, let's see if the new "right" is the continuation of the
            previous sequence.

                10 does INDEED come after 9, therefore it's all good.

            In this case we DO NOT touch "mid" pointer.

            Remember what our "mid" pointer represents:
                What "mid" pointer will represent is the index from which the
                remaining part of the CURRENT subarray(i.e. until "right"
                pointer, inclusively) is sorted in CONSECUTIVE ascending order.

            Since we've extended the CONSEUTIVE sequence, we should NOT touch
            our "mid" pointer since it still DOES INDEED point to a first
            element from which the CONSEUTIVE sequence begins.


            Since in this 2) case of "what we are doing with 'mid' pointer" we
            have kind of 2 subcases, we can take care of that like this:

                mid = max(left, mid);

            Whatever is more to the right, let "mid" be that. Do this AFTER you
            shift "left" and "right" pointers.

*/

/* Time  Beats: 100.00% */
/* Space Beats:  91.28% */

/* Time  Complexity: O(n) */
/* Space Complexity: O(1) */
class Solution {
public:
    vector<int> resultsArray(vector<int>& nums, int k)
    {
        const int n = nums.size();

        int left  = 0;
        int mid   = k-1;
        int right = k-1;

        while (mid > 0)
        {
            if ((nums[mid-1] + 1) != nums[mid])
                break;

            mid--;
        }

        vector<int> result(n-k+1, -1);
        while (right < n)
        {
            if (left == mid)
                result[left] = nums[right];

            left++;
            right++;

            if (right == n)
                break;

            if ((nums[right-1] + 1) != nums[right])
                mid = right;
            else
                mid = max(left, mid); // The one that is further to the right
        }

        return result;
    }
};
