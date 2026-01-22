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

#include <cstdlib>
#include <vector>
using namespace std;

/*
    ------------
    --- IDEA ---
    ------------

    Standard Sliding-Window technique.

*/

/* Time  Beats: 54.11% */
/* Space Beats: 91.44% */

/* Time  Complexity: O(N) */
/* Space Complexity: O(1) */ // "result" is not EXTRA Space
class Solution {
public:
    vector<int> findClosestElements(vector<int>& arr, int k, int x)
    {
        const int N = arr.size();

        int L = 0;
        int R = N-1;

        while ((R - L + 1) > k) // (R - L + 1) <==> current_window_length
        {
            if (abs(arr[L] - x) <= abs(arr[R] - x))
                R--;
            else
                L++;
        }

        return vector<int>(arr.begin() + L, arr.end() + R + 1);
    }
};




/*
    ------------
    --- IDEA ---
    ------------

   Note that, you SHOULD NOT compare the absolute value of:
       abs(x - A[mid]) and abs(A[mid + k] - x).

   It fails at cases like arr = [1, 1, 2, 2, 2, 2, 2, 3, 3], x = 3, k = 3
                                 0  1  2  3  4  5  6  7  8
                                 L                 R
                                 ^                 ^
                                 |                 |
               Initially:  0 -----                 ------- arr.size() - k


    It's difficult to come up with this Solution and it is difficult to explain
    it, but I'll try my best.

    The main idea of this problem is that we do NOT want to iterate through the
    entire array "arr" because that will make our Solution's Time Complexity
    O(n).

    O(n) isn't bad, but we can clearly do better since they made the word
    "sorted", in the description, bold. "Sorted" highly indicates that we're
    able to do a Binary Search or else it wouldn't be highlighted.

    It's easy to do this problem using a fixed Sliding Window, therefore they
    probably didn't highlight the word without a reason, hence Binary Search.


    Now that we have this idea in our mind(to use a Binary Search), ask
    yourself - What do we want to find with our binary search?

    The answer seems obvious, but that intuitive idea is WRONG. You probably
    this: We should find a value that is the closest to target x.

    Okay, let's assume that we've found one, what should we do next?
    Consider this example(it's always easier to follow with an example):

               0  1  2  3  4  5   6
        arr = [2, 3, 5, 8, 9, 11, 12], k = 3, x = 6
        res = [3, 5, 8]

    Let's say that we've found the element that is closest to our target x, in
    this case value 6.

    Our "mid" pointer would be at index 3.

               0  1  2  3  4  5   6
        arr = [2, 3, 5, 8, 9, 11, 12], k = 3, x = 6
                        M
                        L
                        R

    So, how can this help us? How can we utilize this?

    You'd now probably try to do what I've done in the above Solution, named:
        Solution_Binary_Search_+_Two_Pointers.

    However that Solution's Time Complexity is O(logN + k) which is indeed
    efficient, especially since k is at max arr.size(), which means that the
    worst possible scenario would be: O(logN + N) which is fine.

    However, we can do slightly better.
    We can have a O(log(N - K) + K) Time Complexity Solution.

    This way of thinking is not obvious but bear with me.

    In a nutshell, we want to consder some middle window of size k and we want
    to check which of the two is closer to target:
        1. Leftmost element within the curr_window of size k
            OR
        2. The first element to the right that falls outside of the curr_window

    Why would we consider that?

    Well, since with our Binary Search, we are not looking for our target value
    x, we just want to "arbitrarily" consider a window of size k and from that
    we want to move our window either left or right, depending on the elements
    in the current window.

    Let me draw it, it'll make much more sense:
    (Let's use a slightly different example)

               0  1  2  3  4  5   6   7   8
        arr = [2, 3, 3, 7, 9, 10, 15, 17, 18], k = 3, x = 16

    As I've said, we want to find a random point and try to consider a window
    of size k from that point onwards.
    Meaning, if we get that our "mid" pointer is at index 4, then beginning at
    index 4(including index 4) we want to consider next k-1 elements as part of
    our current window.

    We consider next k-1 and not k because we're including element at index 4.
    So we are considering this:

                            curr_window
                           ____________
                           |          |
               0  1  2  3  |4  5   6  | 7   8
        arr = [2, 3, 3, 7, |9, 10, 15,| 17, 18], k = 3, x = 16
                           |__________|

    You may ask:"But why, if we wanted a "random point", do we need a Binary
    Search here? Why can't we just, at random, pick an index and begin there?"

    Good question. The answer is that we'll use a Binary Search to "Slide" the
    window. You'll see in a bit.

    Let's get to our idea. Once we are consider some curr_window, we want to
    check, which of the two is CLOSER to our target x:

        1. Leftmost element within our curr_window
           (9 in this case)

            OR

        2. The first element to the right that falls outside of the curr_window
           (17 in this case)

    Whichever gets to be closer to our target x, we'll move in the opposite
    direction. If they are equidistant, then "pick" a smaller one, i.e. move
    the window towards the left. By "move window" I just mean to update either
    "left" or "right" pointer.

    (If our target was 13, then we'd have an equidistant case. In that case we
    would want to keep the 9, meaning we'd move our window to the left by
    updating "right" pointer value to "mid").

    However, there is a VERY important thing to consider. Since we want to use
    Binary Search to find some "starting point" for our window, what if, at
    some point, we end up having our "mid" pointer be last or second-to-last
    element from the right, while our k values is, for example, 4.

    If we begin considering elements from the last or second-to-last element
    and we consider next k-1 elements, we'd go OUT OF BOUNDS!

    That tells us that we should NOT permit that our "mid" pointer get past
    "arr.size() - k"th index.

               0  1  2  3  4  5  6  7
        arr = [x, x, x, x, x, x, x, x], k = 4
                           ^
                           |
                           |_____________
                                        |
    arr.size() - k ==> 8 - 4 ==> 4 ------

    That is the last VALID index at which we can place our "mid" pointer.
    Therefore, our "right" pointer should NOT intially be at "arr.size() - 1",
    but at "arr.size() - k".

    Let's now do one Simulation, and I'm sure you'll get it.


*******************************************************************************
********************************** SIMULATION *********************************
*******************************************************************************

                   0  1  2  3  4  5   6   7   8
            arr = [2, 3, 3, 7, 9, 10, 15, 17, 18], k = 3, x = 16
                   L                  R                   ^
                                                          |
                                                        target

-------------------------------------------------------------------------------

    1.

                        curr_window
                        ____________
                        |          |
               0  1  2  | 3  4  5  |  6    7   8
        arr = [2, 3, 3, | 7, 9, 10,| 15, 17, 18], k = 3, x = 16
               L        | M        |  R
                        | ^        |  ^
                        |_|________|  |
                          |           |_________
                          |_______________     |
                                         |     |
            Which one is closer to x=16: 7 or 15?

            It's 15, therefore we move "L"(left) pointer to be M(mid) + 1.

-------------------------------------------------------------------------------

    2.

                               curr_window
                              _______________
                              |             |
               0  1  2  3  4  | 5    6    7 | 8
        arr = [2, 3, 3, 7, 9, | 10,  15, 17,| 18], k = 3, x = 16
                           L  |  M   R      |  ^
                              |  ^          |  |
                              |__|__________|  |
                                 |             |
                                 |_________    |_
                                          |      |
            Which one is closer to x=16: 10 or  18?

            It's 18, therefore we move "L"(left) pointer to be M(mid) + 1.

-------------------------------------------------------------------------------

    3.


               0  1  2  3  4   5   6   7   8
        arr = [2, 3, 3, 7, 9, 10, 15, 17,  18], k = 3, x = 16
                                   R
                                   L

        Since now both L(left) and R(right) pointers point to the same index,
        we're done, i.e. we break the "while loop".

        (Notice how if we kept going "to the right", i.e. moving our L to M+1,
         the next curr_window of size k would be OUT OF BOUNDS! That's why we
         must stop)

-------------------------------------------------------------------------------

    At the end we're return this window:

                               curr_window
                              ______________
                              |            |
           0  1  2  3  4   5  |  6   7   8 |
    arr = [2, 3, 3, 7, 9, 10, | 15, 17,  18|]
                              |  R         |
                              |  L         |
                              |____________|


    Note this again:
    You SHOULD NOT compare the absolute value of:
        abs(x - A[mid]) and abs(A[mid + k] - x).

    It fails at cases like arr = [1, 1, 2, 2, 2, 2, 2, 3, 3], x = 3, k = 3
                                  0  1  2  3  4  5  6  7  8
                                  L                 R
                                  ^                 ^
                                  |                 |
                Initially:  0 -----                 ------- arr.size() - k

    Instead we should use:
            if (x - arr[mid] > arr[mid + k] - x)

    Try running on a few examples to get a feeling for how this works.
    On the other hand, as for "Why it works" or how to come up with it,
    I have no answer.

*/

/* Time  Beats: 98.93% */
/* Space Beats: 26.20% */

/* Time  Complexity: O(log(N - K) + K) */
/* Space Complexity: O(K) */
class Solution_Binary_Search {
public:
    vector<int> findClosestElements(vector<int>& arr, int k, int x)
    {
        const int N = arr.size();

        int low  = 0;
        int high = N - k;

        while (low < high)
        {
            int mid = low + (high - low) / 2;

            if (x - arr[mid] > arr[mid + k] - x)
                low = mid + 1;
            else
                high = mid;
        }

        return vector<int>(arr.begin() + low, arr.begin() + low + k);
    }
};
