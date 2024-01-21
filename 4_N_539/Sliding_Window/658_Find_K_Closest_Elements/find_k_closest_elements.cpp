#include <iostream>
#include <vector>
#include <deque>

/*
    ==============
    === MEDIUM ===
    ==============

    ============================
    658) Find K Closest Elements
    ============================

    ============
    Description:
    ============

    Given a sorted integer array arr, two integers k and x, return the k
    closest integers to x in the array. The result should also be sorted in
    ascending order.

    An integer a is closer to x than an integer b if:
        |a - x| < |b - x|, or
        |a - x| == |b - x| and a < b


    ==========================================================================
    FUNCTION: vector<int> findClosestElements(vector<int>& arr, int k, int x);
    ==========================================================================

    ==========================================================================
    ================================ EXAMPLES ================================
    ==========================================================================

    --- Example 1 ---
    Input: arr = [1,2,3,4,5], k = 4, x = 3
    Output: [1,2,3,4]

    --- Example 2 ---
    Input: arr = [1,2,3,4,5], k = 4, x = -1
    Output: [1,2,3,4]


    *** Constraints ***
    1 <= k <= arr.length
    1 <= arr.length <= 10^4
    arr is sorted in ascending order.
    -10^4 <= arr[i], x <= 10^4

*/

/*
    ------------
    --- IDEA ---
    ------------

    It may not seem as a Sliding Window Solution, however this is another way
    of implementing a Sliding Window technique.

    We could've also implemented in a slightly different way(that Solution will
    be 2nd from the top in this file).

    What we are doing here is: We are filling our deque with exactly k+1(not k)
    elements.

    Once there are k+1 elements, that means we've exceeded the desired 'k'
    length of elements, therefore we must pop one.

    Since elements are sorted and we've put them in our deque in ascending
    order, we can just check which one is closer to our target 'x':
        1. Leftmost  in our deque(front in our Deque)
        2. Rightmost in our deque(back  in our deque)

    The one that is **further** away in terms of value(not in terms of index)
    is the one we're going to pop.

    For example:

        arr = [1, 2, 3, 4, 5, 6, 7, 8], k = 3, x = 5

    Our deque, after we "fill it" with first k+1 elements, look like this:

        deque = [1, 2, 3, 4]

    Since 'k' is equal to 3, we must evict one of the elements from this deque.
    Which one should it be?

    Well, target 'x' is equal to 5, therefore, since elements in our deque are
    sorted in ascending order, we should evict either:
        1. leftmost (smallest in our deque)
        2. rightmost(greatest in our deque)

    Difference between our "leftmost" value, in current state of deque, and
    target 'x' is:

        abs(1 - 5) = abs(-4) = 4

    whereas the difference between our "rightmost" value in current state of
    deque, and target 'x' is:

        abs(4 - 5) = abs(-1) = 1

    Since our rightmost element 4(at index 3) is **CLOSER** to our target 'x',
    we should evict the other one, ake the "leftmost" element in our deque.

        deque = [1, 2, 3, 4] // Before
        deque =    [2, 3, 4] // After

    We'll continue doing this until we process all the elements in the array.

    Once we exit the "for loop", we'll just put elements from our deque to
    "results" since we must return a vector and not a deque.

*/

/* Time  Beats: 95.34% */
/* Space Beats: 17.73% */

/* Time  Complexity: O(n) */
/* Space Complexity: O(k) */
class Solution_Sliding_Window {
public:
    std::vector<int> findClosestElements(std::vector<int>& arr, int k, int x)
    {
        std::deque<int> deque;
        for (int i = 0; i < arr.size(); i++)
        {
            deque.push_back(arr[i]);

            if (i - k >= 0) // If there are k+1 elements in our "deque"
            {
                /* Pop either leftmost or rightmost element */

                if (std::abs(deque.front() - x) <= std::abs(deque.back() - x))
                    deque.pop_back();
                else
                    deque.pop_front();
            }
        }

        std::vector<int> results(deque.begin(), deque.end());

        return results;
    }
};




/*
    ------------
    --- IDEA ---
    ------------

    The exact same Solution as above, but implemented differently.
    This one is, at least for me, easier to read, so maybe other people find it
    helpful as well.

*/

/* Time  Beats: 95.34% */
/* Space Beats: 17.73% */

/* Time  Complexity: O(n) */
/* Space Complexity: O(k) */
class Solution_Sliding_Window_Slightly_Different_Implementation {
public:
    std::vector<int> findClosestElements(std::vector<int>& arr, int k, int x)
    {
        std::deque<int> deque;
        for (int i = 0; i < k; i++) // Push first 'k' elements
            deque.push_back(arr[i]);

        for (int i = k; i < arr.size(); i++) // Starting at index 'k', i.e. k+1st element
        {
            deque.push_back(arr[i]); // Now this is always going to exceed k

            // Pop either leftmost or rightmost element

            if (std::abs(deque.front() - x) <= std::abs(deque.back() - x))
                deque.pop_back();
            else
                deque.pop_front();
        }

        std::vector<int> results(deque.begin(), deque.end());

        return results;
    }
};


/*
    ------------
    --- IDEA ---
    ------------

   Note that, you SHOULD NOT compare the absolute value of:
       abs(x - A[mid]) and abs(A[mid + k] - x).

   It fails at cases like arr = [1,1,2,2,2,2,2,3,3], x = 3, k = 3

*/

/* Time  Beats: 98.93% */
/* Space Beats: 26.20% */

/* Time  Complexity: O(log(N - K)) */
/* Space Complexity: O(K) */
class Solution_Binary_Search {
public:
    std::vector<int> findClosestElements(std::vector<int>& arr, int k, int x)
    {
        int left  = 0;
        int right = arr.size() - k;

        while (left < right)
        {
            int mid = (left + right) / 2;

            if (x - arr[mid] > arr[mid + k] - x)
                left = mid + 1;
            else
                right = mid;
        }

        return std::vector<int>(arr.begin() + left, arr.begin() + left + k);
    }
};
