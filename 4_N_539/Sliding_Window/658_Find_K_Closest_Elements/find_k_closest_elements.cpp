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

    It's a bit messy because of a lot of Edge-cases, but it essentially comes
    down to:

    Do a lower_bound Binary Search with target x and that element is certainly
    going to bein the result vector.

    Now we're trying to expand the window so that it cointains exactly k
    elements as needed.

    Current element, the one that is certainly going to be in the result, is at
    index "idx" which we've found with our "lower_bound" function.

    Now we say that both "left" and "right" point to "idx", but we are checking
    which of the two is smaller:
        1. abs(x - arr[left  - 1])
        2. abs(x - arr[right + 1])

    Let's look at an example, it'll be much easier:

               0  1  2  3  4  5  6  7  8  9
        arr = {0, 0, 1, 2, 3, 3, 4, 5, 7, 8}, k = 3, x = 5
                                    ^
                                    |
                                    |
    idx -----------------------------

    Now we'll set L(left) and R(right) pointers to point to idx as well.

               0  1  2  3  4  5  6  7  8  9
        arr = {0, 0, 1, 2, 3, 3, 4, 5, 7, 8}, k = 3, x = 5
                                    L
                                    R
                                    ^
                                    |
                                    |
    idx -----------------------------

    But now we're going to check if (L-1) or (R+1) is CLOSER to x(target).
    If we find out that they are equally far apart from the target, then we'll
    take the smaller value.

    In this example, which one is closer to target 5:
        1. 4 // difference is 1
        2. 7 // difference is 2

    So, 4 is closer and therefore we'll move our L(left) pointer to the left by
    one.

    Now we'll set L(left) and R(right) pointers to point to idx as well.
    Now we have this:

               0  1  2  3  4  5  6  7  8  9
        arr = {0, 0, 1, 2, 3, 3, 4, 5, 7, 8}, k = 3, x = 5
                                 L  R
                                    ^
                                    |
                                    |
    idx -----------------------------

    Let's do the same thing but for different values since our L(left) pointer
    is moved.

    Which one is closer to target 5:
        1. 3 // difference 2
        2. 7 // difference 2

    Since they are equally far apart from the target 5, we take the SMALLER
    values, which further means we are going to, again, decrement our L(left)
    pointer by one.

    Now we have this:

               0  1  2  3  4  5  6  7  8  9
        arr = {0, 0, 1, 2, 3, 3, 4, 5, 7, 8}, k = 3, x = 5
                              L     R
                                    ^
                                    |
                                    |
    idx -----------------------------

    Since now our window_len(which is: R - L + 1) is of size k, we stop.
    (However, in the code, it's much easier to just decrement k at every
     iteration)

    Now we just return std::vector<int>(arr.begin() + L, arr.begin() + L + k);


    As I've said, there are quite a few edge cases.

    First, if our "iter" gets to be arr.begin() that means "lower_bound"
    returned that element which further means, since the array is SORTED, that
    we just need to return first k elements as a result.

    Second, if our "iter" gets to be arr.end() that means "lower_bound" didn't
    find any element that is greater or equal than our target k and therefore
    we shall return last k elements of our array "arr".


    Third, if we have something like this:
        arr = [0, 0, 1, 2, 3, 3, 4, 7, 7, 8], k = 3, x = 5

    "lower_bound" will return value 7, at index 7, however we can see that the
    4 is closer to target 5, than the value 7, therefore we want to move one
    position to the left.

    That's why we do:
        iter--.

    However, it we directly write:
        iter--
    then, examples like these:
        arr = [1, 1, 1, 10, 10], k = 1, x = 9
               0  1  2  3   4
    won't work.

    "lower_bound" would return element at index 3, and we'd move it to index 2
    which would make this incorrect since 10 is closer to target 9, that 1 is.

    To overcome this issue we'll do this:

        if (std::abs(*(iter) - x) < std::abs(*(--iter) - x))
            iter++;                               ^
                                                  |
                                                  |___________________________
                                                                             |
    There's most certainly a better way to to write this, but since we are   |
    prefixely decrementing our iterator "iter" in the right-hand side of the |
    condition.                                                               |
                                                                             |
    Therefore if it happens that the current "iter" element is closer to the |
    target, we are going to INCREMENT it.                                    |
                                                                             |
    Why increment it, we that's the one we need?                             |
    Because we've DECREMENTED it prefixely in the condition.                 |
                     |                                                       |
                     |_______________________________________________________|

    It's a bit confusing, but it is what it is.


    You'll also notice that in the while loop we have these 2 if statements:
            if (left-1 < 0)
                right++;
            else if (right+1 == arr.size())
                left--;

    Why?

    That's because of the fact that we cannot expand our window out of bounds.
    If we hit the last element in the array with one side of our window, then
    we are only allowed to keep expanding in the other direction.

    And since our "while loop" will iterate until we have exactly k elements,
    we are sure that we won't be able to hit both ends before we get k
    elements.

*/

/* Time  Beats: 87.22% */
/* Space Beats: 28.22% */

/* Time  Complexity: O(logN + K) */
/* Space Complexity: O(1) */
class Solution_Binary_Search_+_Two_Pointers {
public:
    std::vector<int> findClosestElements(std::vector<int>& arr, int k, int x)
    {
        auto iter = std::lower_bound(arr.begin(), arr.end(), x);

        if (iter == arr.begin())
            return std::vector<int>(arr.begin(), arr.begin() + k);
        if (iter == arr.end())
            return std::vector<int>(arr.end() - k, arr.end());

        if (std::abs(*(iter) - x) < std::abs(*(--iter) - x))
            iter++;

        int idx = (iter - arr.begin());
        k--;

        int left  = idx;
        int right = idx;
        while (k-- > 0)
        {
            if (left-1 < 0)
                right++;
            else if (right+1 == arr.size())
                left--;
            else
            {
                if (std::abs(x - arr[left-1]) <= std::abs(x - arr[right+1]))
                    left--;
                else
                    right++;
            }
        }

        if (left >= 0)
            return std::vector<int>(arr.begin() + left, arr.begin() + right + 1);
        else
            return std::vector<int>(arr.begin() + right - k + 1, arr.begin() + right + 1);
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

/* Time  Complexity: O(log(N - K) + K) */
/* Space Complexity: O(K) */
class Solution_Binary_Search {
public:
    std::vector<int> findClosestElements(std::vector<int>& arr, int k, int x)
    {
        int left  = 0;
        int right = arr.size() - k;

        while (left < right)
        {
            // int mid = (left + right) / 2;
            int mid = left + (right - left) / 2;

            if (x - arr[mid] > arr[mid + k] - x)
                left = mid + 1;
            else
                right = mid;
        }

        return std::vector<int>(arr.begin() + left, arr.begin() + left + k);
    }
};
