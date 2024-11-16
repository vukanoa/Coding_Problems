#include <iostream>
#include <vector>
#include <algorithm>
#include <limits>

/*
    ==============
    === MEDIUM ===
    ==============

    ==========================================================
    1574) Shortest Subarray to be Removed to Make Array Sorted
    ==========================================================

    ============
    Description:
    ============

    Given an integer array arr, remove a subarray (can be empty) from arr such
    that the remaining elements in arr are non-decreasing.

    Return the length of the shortest subarray to remove.

    A subarray is a contiguous subsequence of the array.

    =============================================================
    FUNCTION: int findLengthOfShortestSubarray(vector<int>& arr);
    =============================================================

    ==========================================================================
    ================================ EXAMPLES ================================
    ==========================================================================

    --- Example 1 ---
    Input: arr = [1,2,3,10,4,2,3,5]
    Output: 3
    Explanation: The shortest subarray we can remove is [10,4,2] of length 3.
                 The remaining elements after that will be [1,2,3,3,5] which
                 are sorted. Another correct solution is to remove the subarray
                 [3,10,4].


    --- Example 2 ---
    Input: arr = [5,4,3,2,1]
    Output: 4
    Explanation: Since the array is strictly decreasing, we can only keep a
                 single element. Therefore we need to remove a subarray of
                 length 4, either [5,4,3,2] or [4,3,2,1].


    --- Example 3 ---
    Input: arr = [1,2,3]
    Output: 0
    Explanation: The array is already non-decreasing. We do not need to remove
                 any elements.


    *** Constraints ***
    1 <= arr.length <= 10^5
    0 <= arr[i] <= 10^9

*/

/*
    ------------
    --- IDEA ---
    ------------

    TODO
    (This one requires a lengthy explanation)

    First thing you should know is that in every array, of length n, there are
    exatly n^2 subarrays.

    Second, it's important to emphasize that they are asking us to remove a
    SINGLE subarray. Meaning, if there is some sorted array we could obtain
    by removing two or more subarrays, we do NOT care about those.

    We only care about the MINIMUM LENGTH of a SINGLE SUBARRAY we can remove
    after which the remaining elements are in non-decreasing order.

    *******************************
    *** Note for non-decreasing ***
    *******************************
        Non-decreasing means there can be equal elements.

        Strictly increasing:  2, 3, 4, 5, 7, 9
        Non-decreasing:       2, 3, 3, 3, 7, 9

    
    Once we understand previous two things, it should be obvious that there are
    only three ways in which we can remove a single subarray:
        1) Prefix
        2) Suffix
        3) Middle

    
    1) Prefix
           Example: arr = [7, 8  2, 2, 1, 2, 3, 4, 5, 6]
                           ^^^^^^^^^^
           
           If we remove this prefix(these 4 elements: [7, 8, 2, 2]) we are
           left with the longest array that is still sorted.



    2) Suffix
           Example: arr = [1, 2, 3, 4, 5, 6, 2, 1, 0, 2]
                                             ^^^^^^^^^^^

           If we remove this suffix(these 4 elements: [2, 1, 0, 2]) we are
           left with the longest array that is still sorted.



    3) Middle
          Example: arr = [1, 2, 3, 4, 10, 12, 11, 6, 7, 8]
                                      ^^^^^^^^^^

           If we remove this middle subarray(these 3 elements: [10, 12, 11]) we
           are left with the longest array that is still sorted.


    
    There are 2 Base-cases that can be checked at the beginning:
        1) Strictly decreasing array
        2) Non-decreasing array


    1)
        If the array is sorted in a strictly decreasing order, then we can
        immediately know what is the answer, the answer is ALWAYS: n-1.

        Consider Example 2:
            arr = [5, 4, 3, 2, 1]

        We can be either left with [5] or with [1]. There is no other possible
        solution. However, in both cases the answer is the same ==> We must
        remove exactly n-1 elements.


    2)
        On the other hand, if the whole array is sorted in a non-decreasing
        order, then the answer is ALWAYS 0.

        Why?

        Let's look at the Example 3:
            arr = [1,2,3]

        What is the length of the subarray that we have to REMOVE in order to
        make our array sorted in non-decreasing order?

        The answer is: 0, the array is ALREADY in a non-decreasing order.



    After we're done with these Base-cases, we can finally move to the main
    part of this Solution.


    This one is kind of tricky to come up with, but it's not too bad.
    Let's refresh our memory - There are ONLY THREE WAYS in which we can remove
    a single subarray:
        1) Prefix
        2) Suffix
        3) Middle

    1) 
        To determine the length of the prefix subarray that we have to remove
        to obtain a sorted array, all we have to do is iterate from the back
        and find the first element that is strictly GREATER than the one next
        to it(to the right of it).

        Once we find that we know that from the index to the right of the
        current element, until the end of the array, all elements ARE SORTED.

        Let's look at the Example 1:

            arr = [1, 2, 3, 10, 4, 2, 3, 5]
                   0  1  2   3  4  5  6  7
                                   i

        We know that from index i=5 (inclusive) until the end of the array -
        ALL elements are sorted in a non-decreasing order.

        We'll call this 'i' index "sorted_from_idx".

        Now, check if this is the smallest LENGTH of the SUBARRAY we can remove
        by taking the minimum out of the current value of "result" and this
        index:

            // i.e. we removed elements from [0 to sorted_from_idx-1]
            result = min(result, sorted_from_idx);

        Alternatively, we could write this in a verbose way:
            result = min(result, sorted_from_idx-1 - 0 + 1);



    2)
        Conversely, we can do a similar thing for getting rid of the suffix.

        To determine the length of the suffix subarray that we have to remove
        to obtain a sorted array, all we have to do is iterate from the front
        and find the first element that is strictly SMALLER than the previous
        one(one that is to the left of it).

        Once we find that, we know that UP TO that index(NOT INCLUSIVELY!!!) -
        ALL elements are sorted in non-decreasing order.


        Let's, again, look at the Example 1:

            arr = [1, 2, 3, 10, 4, 2, 3, 5]
                   0  1  2   3  4  5  6  7
                                i

        We know that from index i=4 (NOT inclusive) until the end of the array
        - ALL elements are sorted in a non-decreasing order.

        We'll call this 'i' index "sorted_up_to_idx".

        Now, check if this is the smallest LENGTH of the SUBARRAY we can remove
        by taking the minimum out of the current value of "result" and the
        length of the subarray from the end until the index we've just found:

            result = min(result, n - sorted_up_to_idx);

        Alternatively, we could write this in a verbose way:
            result = min(result, n-1 - sorted_up_to_idx + 1);



    And finally let's look at the CRUX of this Solution - Remove the MIDDLE
    subarray to obtain a sorted array in non-decreasing order.

    3)
        For the third time, let's look at the Example 1:
        
            arr = [1, 2, 3, 10, 4, 2, 3, 5]
                   0  1  2   3  4  5  6  7

        It's VERY important to use the information we've gathered so far. We
        know that from index "sorted_from_idx"=5(inclusively) ALL the elements
        until the end of the array ARE SORTED!

        We can use that to our advantage.

        This is the idea:

        We can iterate through array "arr", from the beginning, and as long as
        elements are SORTED FROM THE BEGINNING, we can try to find it's OTHER
        part from the subarray at the end that we are SURE is SORTED as well.

            arr = [1, 2, 3, 10, 4, 2, 3, 5]
                   0  1  2   3  4  5  6  7
                   x               i

        We are currently at element arr[x]=1.
        We know that from index i=5(inclusively) all the elemensts ARE SORTED
        until the end of the array.

        Therefore, since we are looking for a MIDDLE SUBARRAY TO REMOVE(!!) we
        can try to link the sorted part at the beginning with the sorted part
        at the end of the array.

        However, maybe the element at index i=5 is LESS THAN the current
        element arr[x]=1, which means we are NOT able to link with i=5 as the
        beginning of the other part and, thus, we have to linearly scan through
        this sorted part at the end of the array.

        But that would be a O(n^2) Solution, which is a Brute-Force since we've
        concluded, at the very beginning, that the number of subarrays in ANY
        array of length n is n^2.

        But have we heard ourselves? Let's read, or say, that again:
            "... thus, we have to linearly SCAN THROUGH THIS SORTED PART at the
            end of the array."

        What is the optimization we can use to SCAN THROUGH THE SORTED array?
        Of course, it's: Binary Search!


        Let's summarize this part:

            We iterate, FROM THE BEGINNING, of the array and AS LONG AS THE
            ELEMENTS ARE IN NON-DECREASING ORDER, we are trying to find the
            other part, from the back of the array, that is also sorted, to
            link with and thus, implicitly REMOVE the MIDDLE SUBARRAY.

            Since the part on the back of the array is ALSO sorted and since we
            know the index from which that subarray starts(inclusively), we
            can perform a Binary Search on that part.

            Each time we find the leftmost element that is EQUAL TO OR GREATER
            THAN arr[x] in the sorted subarray from the back, we calculate:

                result = min(result, idx - (i+1));

            Once we find the first element, from the beginning, that is a
            "dip", meaning it's NOT EQUAL TO OR GREATER THAN the previous
            element, we stop. We break out of the for-loop and return the
            result.

*/

/* Time  Beats: 100.00% */
/* Space Beats:  66.98% */

/* Time  Complexity: O(n * logn) */
/* Space Complexity: O(1)        */
class Solution {
public:
    int findLengthOfShortestSubarray(vector<int>& arr)
    {
        const int n = arr.size();

        if (strictly_decreasing(arr)) // O(n)
            return n-1;
        else if (non_decreasing(arr)) // O(n)
            return 0;

        int result = 0;

        // O(n)
        /* From which Idx from the back, is the rest of the array sorted? */
        int sorted_from_idx = n; // Out of bounds currently
        for (int i = n-2; i >= 0; i--)
        {
            if (arr[i] > arr[i+1])
            {
                sorted_from_idx = i+1;

                // Or result = sorted_from_idx-1 - 0 + 1
                result = sorted_from_idx; // i.e. we removed elements from [0 to sorted_from_idx-1]
                break;
            }
        }

        // O(n)
        /* Up to which idx is the array in non-decreasing order? */
        int sorted_to_idx = -1; // Out of bounds currently
        for (int i = 1; i < n; i++)
        {
            if (arr[i-1] > arr[i])
            {
                sorted_to_idx = i;
                break;
            }
        }

        // O(n * logn)
        for (int i = 0; i < n; i++)
        {
            if (i > 0 && arr[i-1] > arr[i])
                break;

            if (arr[i] <= arr[sorted_from_idx])
                result = min(result, sorted_from_idx - (i+1));
            else
            {
                // Searching for the leftmost value that is EQUALS TO OR GREATER THAN the target=arr[i]
                auto it = std::lower_bound(arr.begin() + sorted_from_idx, arr.end(), arr[i]); // O(log n)
                if (it == arr.end())
                {
                    result = min(result, n - (i+1));
                    continue;
                }

                int idx = it - arr.begin();

                result = min(result, idx - (i+1));
            }
        }

        result = min(result, n - sorted_to_idx);

        return result;
    }

private:
    // ***************************
    // *** STRICTLY DECREASING ***
    // ***************************
    bool strictly_decreasing(vector<int>& arr)
    {
        for (int i = 1; i < arr.size(); i++)
        {
            if (arr[i-1] <= arr[i])
                return false;
        }

        return true;
    }


    // **********************
    // *** NON-DECREASING ***
    // **********************
    bool non_decreasing(vector<int>& arr)
    {
        for (int i = 1; i < arr.size(); i++)
        {
            if (arr[i-1] > arr[i])
                return false;
        }

        return true;
    }
};




/*
    ------------
    --- IDEA ---
    ------------

    TODO
    Slight, but VERY important, optimization on the above Solution.

    The only part that differs is how we handle the 3) case, i.e. Middle
    subarray removal.

    Instead of doing a Brute-Force O(n^2) by doing the following:

        Start from the beginning and as long as the elements are sorted from
        the beginning, scan through the sorted part from the back linearly.

        I.e. for every element that doesn't infringe on sortedness from the
        beginning, do a linear scan through sorted subarray from the back.

        That would be O(n^2)

    But, then we've optimized the linear scan through the sorted subarray by
    using Binary Search.

        This would be O(n * logn)

    Now, we can optimized that part even move. Instead of scanning through that
    part, we can have TwoPointers approach and do it entirely in O(n).

    Let's look at slightly modified Example 1:

        arr = [1, 3, 4, 10, 4, 2, 3, 5]
               0  1  2   3  4  5  6  7
               x               i
            
    arr[x=0] = 1 is sorted(because it's the very first element)
    Now we check: if arr[x]=1 is EQUALS TO OR SMALLER THAN arr[i]=2.

            if (arr[x] <= arr[i])

    If it is TRUE, then that means we can know the length of the
    subarray we're about to remove in O(1).

    How?

    The left sorted part is of length x+1. Since x=0, the sorted part
    is of length 0+1=1.

    However, since we know the BEGINNING of the sorted subarray on the
    "other side", and we've seen that the tail of the LEFT subarray is
    smaller than the HEAD(i.e. first element) of the RIGHT subarray,
    then the total length is:

        left_part_length + right_part_length   =  
            0 + 1        +    N - i            =  
              1          +    8 - 5            =  
              1          +      3              = 4

    However, that's not what we are looking for. We are looking for an
    opposite thing: The length of the subarray we will REMOVE, not the
    length of the remaining elements.

    Therefore, to do that, take the minimum of either:
        1) result
        2) sorted_from_idx - x+1

        // i <==> x in the line below
        result = min(result, sorted_from_idx - (i+1));

    
    Now we move to the next element by incrementing 'x'.

        arr = [1, 3, 4, 10, 4, 2, 3, 5]
               0  1  2   3  4  5  6  7
                  x            i

    Here, again, we check:

        if (arr[x] <= arr[i])

    But here, that's NOT the case. What do we do now?
    We simply move 'i' pointer to the right until it becomes EQUAL TO OR
    GREATER THAN arr[x](or it goes Out-of-Bounds).

    This is the absolute kernel of this Solution.

    Let's say it did go out of bounds, let's say we had something like this:

        arr = [1, 7, 8, 10, 4, 2, 3, 5]
               0  1  2   3  4  5  6  7
                  x            i

        In this case, we would move 'i' pointer to Out-Of-Bounds because we
        wouldn't be able to find an element that is EQUAL TO OR GREATER THAN
        arr[x].

        In that case, we can stop and we can be certain we've found the result.

        Result is either going to come from 1) Prefix or 2) Suffix or it will
        come from this new Suffix that was supposed to be Middle.

        We DO NOT have to continue since if the next element, to the right of
        current x, is in SORTED order, then we won't be able to find EQUAL TO
        OR GREATER THAN for that element either, thus we can stop.

    This way, we've removed Binary Search and now total Time Complexity is O(n)


*/

/* Time  Beats: 100.00% */
/* Space Beats:  25.81% */

/* Time  Complexity: O(n) */
/* Space Complexity: O(1) */
class Solution_Optimized {
class Solution {
public:
    int findLengthOfShortestSubarray(vector<int>& arr)
    {
        const int n = arr.size();

        if (strictly_decreasing(arr)) // O(n)
            return n-1;
        else if (non_decreasing(arr)) // O(n)
            return 0;

        int result = INT_MAX;

        // O(n)
        /* From which Idx from the back, is the rest of the array sorted? */
        int sorted_from_idx = n; // Out of bounds currently
        for (int i = n-2; i >= 0; i--)
        {
            if (arr[i] > arr[i+1])
            {
                sorted_from_idx = i+1;
                break;
            }
        }
        result = min(result, sorted_from_idx); // i.e. we removed elements from [0 to sorted_from_idx-1]
        cout << "\n\t\t\t---Result: " << result;

        // O(n)
        /* Up to which idx is the array in non-decreasing order? */
        int sorted_up_to_idx = -1; // Out of bounds currently
        for (int i = 1; i < n; i++)
        {
            if (arr[i-1] > arr[i])
            {
                sorted_up_to_idx = i;
                break;
            }
        }
        result = min(result, n - sorted_up_to_idx);

        // O(n)
        for (int x = 0; x < n; x++)
        {
            if (x > 0 && arr[x-1] > arr[x])
                break;

            while (sorted_from_idx < n && arr[x] > arr[sorted_from_idx])
                sorted_from_idx++;

            if (sorted_from_idx == n)
                break;

            result = min(result, sorted_from_idx - (x+1));
        }

        return result;
    }

private:
    // ***************************
    // *** STRICTLY DECREASING ***
    // ***************************
    bool strictly_decreasing(vector<int>& arr)
    {
        for (int i = 1; i < arr.size(); i++)
        {
            if (arr[i-1] <= arr[i])
                return false;
        }

        return true;
    }


    // **********************
    // *** NON-DECREASING ***
    // **********************
    bool non_decreasing(vector<int>& arr)
    {
        for (int i = 1; i < arr.size(); i++)
        {
            if (arr[i-1] > arr[i])
                return false;
        }

        return true;
    }
};
