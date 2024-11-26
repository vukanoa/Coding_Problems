#include <iostream>
#include <vector>

/*
    ============
    === EASY ===
    ============

    ===========================
    1089) Duplicate Zeroes
    ===========================

    ============
    Description:
    ============

    Given a fixed-length integer array arr, duplicate each occurrence of zero,
    shifting the remaining elements to the right.

    =====
    Note: that elements beyond the length of the original array are not
          written. Do the above modifications to the input array in place and
          do not return anything.
    =====

    ================================================
    FUNCTION: void duplicateZeros(vector<int>& arr);
    ================================================

    ==========================================================================
    ================================ EXAMPLES ================================
    ==========================================================================

    --- Example 1 ---
    Input: arr = [1,0,2,3,0,4,5,0]
    Output: [1,0,0,2,3,0,0,4]
    Explanation: After calling your function, the input array is modified to:
                 [1,0,0,2,3,0,0,4]


    --- Example 2 ---
    Input: arr = [1,2,3]
    Output: [1,2,3]
    Explanation: After calling your function, the input array is modified to:
                 [1,2,3]


    *** Constraints ***
    1 <= arr.length <= 10^4
    0 <= arr[i] <= 9

*/

using namespace std;



/*
    ------------
    --- IDEA ---
    ------------

    This is "tricky" to implement, but the idea is simple.

    Idea is the count all of the zeroes in the Input array "arr". Once we have
    that information, we can pretend as if the INput array "arr" is longer by
    that amount of zeroes.

    The number of zeroes we got tells us the effective shifts. If we were to
    go from the front, it would be drastically less efficient, since we would
    have to shift for every zero found. In the worst case, if there array "arr"
    is consisted of ALL 0s, then the Time Complexity would be O(n^2).

    To prevent that, we can go backwards and we can determine a total SHIFT by
    countring zeroes.(that's how many new elements we're going to "insert")

    However, this is not completely true, since some 0s can also be
    Out-of-Bounds after we're doing with replace-shifts, i.e. 0s can be in the
    Virtual portion of the array.

    Example:
        arr = [1, 0, 2 ,3 ,0 ,4 ,5 ,0]
               0  1  2  3  4  5  6  7

                                        Virtual portion of the array
                                          |
                                          v
                                       ~~~~~~~
        arr = [1, 0, 2 ,3 ,0 ,4 ,5 ,0]{_, _, _}
               0  1  2  3  4  5  6  7  8  9 10


        In the original Input, there are 3 zeroes, however the new-last-element
        will NOT be the element from idx:
            [n-1 - 3], (i.e. last_element_idx_from_original - 3),

        instead it will be:
            [n-1 - 2]

        Why?
        Because the duplicate of the last zero in this Example is going to be
        Out-of-Bounds immediately, it will NOT cause a shift of other elements.

        This is kind of difficult to wrap your head around, but bear with me.


    We don't won't to make this complicated and to do different things whether
    some zero is either cause a shift or not. That would be too complicated.

    Instead, we'll simply do this:

    Count all the zeroes in the Input. Use Two Pointers:
        1. put_at_idx
        2. take_from_idx

    "put_at_idx" will be the Index at which we're "replacing". This is very
    important to understand.

    This index will NOT be always be valid. At the beginning we're going to
    initialize it to point at the last positions of the Virtual array(the array
    that doesn't really exist. That index is out of bounds)

    However, as long as this index is >= n, i.e. Out-of-bounds for the Original
    array, we're ONLY going to be decrementing "put_at_idx" and "take_from_idx"


    "take_from_idx", on the other hand, will be initialized with the last index
    of the ORIGINAL array.

    The while-loop will be executing as long as "put_at_idx" is >= 0.

    We will be takin elements at index arr[take_from_idx] and we'll place it at
    arr[put_at_idx], but that is ONLY possible if "put_at_idx" is < n, i.e. it
    is NOT Out-of-Bounds.

    If it is INDEED Out-of-Bounds we'll only:
        1. decrement put_at_idx by one.
        
    If it is NOT    Out-of-Bounds we'll
        1. arr[put_at_idx] = arr[take_from_idx]
        2. decrement put_at_idx by one.


    However, there's a BIG caveat. If arr[take_from_idx] is 0, then we MUST
    duplicate it. That means we MUST place it at arr[put_at_idx](if it is NOT
    Out-of-Bounds) and then we must decrement put_at_idx by one and THEN we
    MUST place 0 at arr[put_at_idx] and decrement put_at_idx by one again.

    There is a lot going on, but it's not too bad. Once you look at the code,
    I'm sure you'll understand.

*/

/* Time  Beats: 100.00% */
/* Space Beats:  6.13% */

/* Time  Complexity: O(n) */
/* Space Complexity: O(1) */
class Solution {
public:
    void duplicateZeros(vector<int>& arr)
    {
        const int n = arr.size();

        // Step 1: Count zeros to determine the effective shifts
        int zero_counter = 0;
        for (int i = 0; i < n; ++i)
        {
            if (arr[i] == 0)
                zero_counter++;
        }

        if (zero_counter == 0)
            return; // No zeros to duplicate

        int put_at_idx    = n-1 + zero_counter; // Virtual  array position
        int take_from_idx = n-1;                // Original array position

        // Step 2: Traverse from the end of the Virtual array
        while (take_from_idx >= 0)
        {
            if (put_at_idx < n) // If we're replacing ORIGINAL array
                arr[put_at_idx] = arr[take_from_idx];

            // If the current value is zero, we need to duplicate it
            if (arr[take_from_idx] == 0)
            {
                put_at_idx--;

                // put_at_idx will ALWAYS be >= 0, we don't have to check it
                if (put_at_idx < n) // If we're replacing ORIGINAL array
                    arr[put_at_idx] = 0; // Duplicate the zero
            }

            put_at_idx--;
            take_from_idx--;
        }
    }
};
