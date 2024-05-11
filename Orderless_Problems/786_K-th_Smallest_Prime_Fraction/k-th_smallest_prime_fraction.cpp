#include <iostream>
#include <vector>
#include <queue>

/*
    ==============
    === MEDIUM ===
    ==============

    =================================
    786) K-th Smallest Prime Fraction
    =================================

    ============
    Description:
    ============

    You are given a sorted integer array arr containing 1 and prime numbers,
    where all the integers of arr are unique. You are also given an integer k.

    For every i and j where 0 <= i < j < arr.length, we consider the fraction
    arr[i] / arr[j].

    Return the kth smallest fraction considered. Return your answer as an array
    of integers of size 2, where answer[0] == arr[i] and answer[1] == arr[j].

    ---------------
    -- Follow Up --
    ---------------

    Can you solve the problem with better than O(n2) complexity?


    ========================================================================
    FUNCTION: vector<int> kthSmallestPrimeFraction(vector<int>& arr, int k);
    ========================================================================

    ==========================================================================
    ================================ EXAMPLES ================================
    ==========================================================================

    --- Example 1 ---
    Input: arr = [1,2,3,5], k = 3
    Output: [2,5]
    Explanation: The fractions to be considered in sorted order are:
    1/5, 1/3, 2/5, 1/2, 3/5, and 2/3.
    The third fraction is 2/5.

    --- Example 2 ---
    Input: arr = [1,7], k = 1
    Output: [1,7]


    *** Constraints ***
    2 <= arr.length <= 1000
    1 <= arr[i] <= 3 * 10^4
    arr[0] == 1
    arr[i] is a prime number for i > 0.
    All the numbers of arr are unique and sorted in strictly increasing order.
    1 <= k <= arr.length * (arr.length - 1) / 2

*/

/*
    ------------
    --- IDEA ---
    ------------

    This is a Brute Force Solution. It works, but it VERY inefficient. I wanted
    to include this one in the current file as well so that we can see the
    gradation of improvement.

*/

/* Time  Beats: 6.78% */
/* Space Beats: 5.22% */

/* Time  Complexity: O(n^2 * logk) */
/* Space Complexity: O(n^2) */
class Solution_Inefficient {
public:
    std::vector<int> kthSmallestPrimeFraction(std::vector<int>& arr, int k)
    {
        const int N = arr.size();

        std::priority_queue<std::pair<double, std::vector<int>>,
                            std::vector<std::pair<double, std::vector<int>>>,
                            std::greater<std::pair<double, std::vector<int>>>> min_heap;


        for (int i = 0; i < N-1; i++)
        {
            for (int j = i+1; j < N; j++)
                min_heap.push( {1.0 * arr[i] / arr[j], {arr[i], arr[j]} } );
        }

        std::vector<int> result;
        for (int i = 0; i < k; i++)
        {
            result = min_heap.top().second;
            min_heap.pop();
        }

        return result;
    }
};




/*
    ------------
    --- IDEA ---
    ------------

    Similar idea as above, but Time Complexity is reduced to O(n^2), however
    this is still considered a Brute Force Solution.

*/

/* Time  Beats: 10.26% */
/* Space Beats:  6.77% */

/* Time  Complexity: O(n^2) */
/* Space Complexity: O(k) */
class Solution_Better_But_Still_Inefficient {
public:
    std::vector<int> kthSmallestPrimeFraction(std::vector<int>& arr, int k)
    {
        const int N = arr.size();
        std::priority_queue<std::pair<double, std::vector<int>>> max_heap;

        for (int i = 0; i < N-1; i++)
        {
            for (int j = i+1; j < N; j++)
            {
                max_heap.push( {1.0 * arr[i] / arr[j], {arr[i], arr[j]} } );

                if(max_heap.size() > k)
                    max_heap.pop();
            }
        }

        std::vector<int> result = max_heap.top().second;
        return result;
    }
};




/*
    ------------
    --- IDEA ---
    ------------

    Let's consider the first Example:

        arr = [1,2,3,5], k = 3

    And let's calculate all of the fractions in this vector "arr".

        1/2 = 0.5
        1/3 = 0.333
        1/5 = 0.2
        2/3 = 0.667
        2/5 = 0.4
        3/5 = 0.6

    Now let's sort them in Descending order:

        1) 2/3 = 0.667
        2) 3/5 = 0.6
        3) 1/2 = 0.5
        4) 2/5 = 0.4
        5) 1/3 = 0.333
        6) 1/5 = 0.2


    Also, one important thing that is obvious is:

            same_number / 3   >   same_number / 5

    because 3 < 5. I.e. every subsequent number that is greater than 5 will
    give lesser and lesser result if dividing the "same_number"(assuming, of 
    course, that "same_number" is LESS than the denominator)

    That is an obvious but very important observation.


    The idea I'm about to explain is NOT intuitive at all. However to determine
    if there is a Binary Search Solution for some problem, then you have to ask
    yourself two questions:
        1. Is the array sorted?
        2. Is there ANY range within which the result is guaranteed to be in?

    If the answer is:"Yes!", then you probably can and should use a Binary
    Search approach, however it may not be easy to find "the range" and to
    figure out "the trick" as you're about to see here.


    Okay, let's try to reason our way out.

    To calculate each and every fraction, Time Complexity is O(n^2), so that is
    out of the question, we can't do that.

    So, since we want only FIRST k fractions, we don't really have to calculate
    every single one to determine that.

    How can we know which ones are first or last k if we don't calculate them?
    Great question!

    This is why we made an obvious, but important, observation at the beginning
    of this IDEA. Let's repeat it:

            some_number / 3   >   some_number / 5

        because 3 < 5. I.e. every subsequent number that is greater than 5 will
        give lesser and lesser result if dividing the "same_number".(assuming,
        of course, that "same_number" is LESS than the denominator)
.

    That means that if we have:

        arr = [1,2,3,4,5,6,7,8], k=12

    Since we know that calculation of EVERY fraction in this vector "arr" is
    going to be between (0, 1), exclusively(since every element is UNIQUE and
    since the nominator is ALWAYS going to be smaller than the denominator).

    That means we get to pick any number between 0 and 1 and use it as our
    "pivot". Similar to how "pivot" is used in Quick-sort or, even better, in
    Quick-Select algorithm.

    We pick a "pivot" in some way and then we want to have all of the values
    that are less than the "pivot" to be on one side and all of the elements
    that are greater than the pivot to be on the other side of the "pivot".

    This is the crux of the algorithm, so bear with me.

    In both Quick-Sort and, thus, Quick-Select algorithm, we have to iterate
    over EVERY element in order to "separate them" to correct size. However if
    we proceed to do the same in this problem, we'll again end up with a Time
    Complexity of O(n^2) which isn' any improvement at all, therefore that's
    out of the question.

    So how are we going to separate all of the fractions to "correct side" if
    we AREN'T allowed to even calculate all of them?

    It seems absurd, right?

    However, again, let's recall our obvious but important observation from the
    beginning:

            some_number / 3   >   some_number / 5

        because 3 < 5. I.e. every subsequent number that is greater than 5 will
        give lesser and lesser result if dividing the "same_number".(assuming,
        of course, that "same_number" is LESS than the denominator)


    How is this going to help us?

    Since the nominator is ALWAYS smaller than the denominator, and since all
    the numbers are SORTED, once we determine that some fraction result is
    SMALLER than our "pivot", then WE CAN STOP! (this is why we DON'T have to
    calculate every single fraction but can still separate them on the "corret
    side")

    Let's consider this example:

        arr = [1,2,3,4,5,6,7,8], k=12

    We will have fractions that start with each element as a nominator, except
    for the last element(8 in this case):

        1/2, 1/3, 1/4, 1/5, 1/6, 1/7, 1/8 // Nominator 1
             2/3, 2/4, 2/5, 2/6, 2/7, 2/8 // Nominator 2
                  3/4, 3/5, 3/6, 3/7, 3/8 // Nominator 3
                       4/5, 4/6, 4/7, 4/8 // Nominator 4
                            5/6, 5/7, 5/8 // Nominator 5
                                 6/7, 6/8 // Nominator 6
                                      7/8 // Nominator 7


    Also, remember how we said(but it's obvious) that since every nominator is
    LESS THAN the denominator for EVERY fraction we are allowed to have

    (Remember that we're told:
        "For every i and j where 0 <= i < j < arr.length, we consider the
         fraction arr[i] / arr[j]."

     And also remember that the vector "arr" is sorted.
    )

    Therefore a fraction 5/3 or 6/2 or something like that ISN'T allowed and
    that's not "one of the fractions in our array".

    Only fractions that have a nominator LESS THAN denominator are considered
    fractions for this problem.


    Now let's introduce our "pivot". Since we've said that all of the fractions
    are going to be in the range (0, 1) exclusively, we are going to be doing
    a Binary Search on that range. But, don't worry about it at this very
    moment.

    Let's just say that our pivot is 0.5 okay?

    Now, given that these are all of our fractions:

        1/2, 1/3, 1/4, 1/5, 1/6, 1/7, 1/8 // Nominator 1
             2/3, 2/4, 2/5, 2/6, 2/7, 2/8 // Nominator 2
                  3/4, 3/5, 3/6, 3/7, 3/8 // Nominator 3
                       4/5, 4/6, 4/7, 4/8 // Nominator 4
                            5/6, 5/7, 5/8 // Nominator 5
                                 6/7, 6/8 // Nominator 6
                                      7/8 // Nominator 7

    How are we going to put them in "lower" or "higher" bracket if we aren't
    calculating all of them?

    The main reason is that we don't really need all of the values, we only
    need to calculate how many of them are there and how many are less than the
    pivot. That's why we don't need to calculate all of them. We know that some
    fractions are certainly smaller than some other ones we've calculated.

    As we've shallowly said above - We can stop calculating fractions for that
    NOMINATOR once we find out that some fraction is LESS THAN the "pivot".

    Let's say that in a more concise way and show it.


    First, let's consider only those fractions that have a nominator 1:

        1/2, 1/3, 1/4, 1/5, 1/6, 1/7, 1/8 // Nominator 1

    Since our pivot is 0.5, we are going to iterate through the fractions
    one-by-one until we find a fraction that is LESS THAN than our "pivot".

    1/2 = 0.5   // Not    LESS THAN pivot=0.5
    1/3 = 0.333 // Indeed LESS THAN pivot=0.5, therefore - WE STOP

    Since we stopped for this nominator(1 in this case), we know that all of
    the fractions, including 1/3, are LESS THAN the "pivot" of 0.5

    But how can we know how many are there if we don't calculate all of them?

    WE DON'T NEED THAT INFORMATION!
    Why?

    What is our goal? Our goal is to find the "K-th smallest". To find that
    we need to have K smallest fractions and then take the GREATEST one out of
    all of those K smallest.

    Read that again.

    Let's say we have 7 numbers:
        numbers = [5, 8, 9, 3, 2, 4, 7]

    And let's say k = 3. What are the smallest k(3) numbers?
    The smallest K(3) numbers are: 3, 2, 4

    Out of that K(3) numbers, which one is the GREATEST?
    The GREATEST is number 4.

    Since number 4 is the GREATEST among K(3) smallest elements, then we are
    sure that number 4 is EXACTLY the K-th SMALLEST element!


    Let's collect a few of the points together.
    Once we are calculating the fractions for the nominator 1, we are going to
    STOP once we stumble upon the FIRST fraction that is LESS THAN the "pivot".

    Then we could collect all of these "stumbling" fractions in one array(for
    every nominator), but we don't need to. We only care about the absolutely
    GREATEST among ALL of the fractions that are LESS THAN the "pivot".

    pivot = 0.5

        1/2, 1/3, 1/4, 1/5, 1/6, 1/7, 1/8 // Nominator 1
              ^
              |
              ----- 0.333

             2/3, 2/4, 2/5, 2/6, 2/7, 2/8 // Nominator 2
                        ^
                        |
                        ----- 0.4

                  3/4, 3/5, 3/6, 3/7, 3/8 // Nominator 3
                                  ^
                                  |
                                  ---- 0.429

                  All of the below are GREATER THAN OR EQUAL TO 0.5:
                       4/5, 4/6, 4/7, 4/8 // Nominator 4
                            5/6, 5/7, 5/8 // Nominator 5
                                 6/7, 6/8 // Nominator 6
                                      7/8 // Nominator 7


        So fractions that are all LESS THAN the pivot 0.5:
             1/3, 1/4, 1/5, 1/6, 1/7, 1/8 // Nominator 1
                       2/5, 2/6, 2/7, 2/8 // Nominator 2
                                 3/7, 3/8 // Nominator 3


        However, fractions:
            1/3 is the biggest fraction for Nominator 1
            2/5 is the biggest fraction for Nominator 2
            3/7 is the biggest fraction for Nominator 3

        Out of all these 3 fractions, which one is the greatest?

            1/3 = 0.333
            2/5 = 0.4
            3/7 = 0.429 // This one is the greatest


        Therefore, out of all these fractions that are LESS THAN the "pivot":

             1/3, 1/4, 1/5, 1/6, 1/7, 1/8 // Nominator 1
                       2/5, 2/6, 2/7, 2/8 // Nominator 2
                                 3/7, 3/8 // Nominator 3

        The greatest one is a fraction 3/7.
        That means that 3/7 is the ExACTLY the K-th Smallest element!
        Which is what we are looking for.


        ------------------------------------------
        --- THE ABSOLUTE CRUX OF THIS SOLUTION ---
        ------------------------------------------

        Once we finish "separating", or rather counting how many fractions are
        GREATER THAN OR EQUAL TO "pivot" and thus how many are LESS THAN the
        "pivot", only then can we ask if there are exactly K fractions that are
        LESS THAN the "pivot".

        If that is the case indeed, ONLY THEN are we allowed to take the
        greatest among all of those K smallest fractions.

        If that is NOT the case, then we have to RESIZE our range and THIS IS
        where the Binary Search FINALLY comes in!

        In we didn't manage to get exactly K fractions that are LESS THAN the
        "pivot", then we cannot get the "K-th smallest" right?

        Therefore we have to shrink the range either to the left or to the
        right based on how many fractions are LESS THAN the current "pivot".

        We do that by:

            if (total > k)
                right = mid;
            else
                left = mid;

        Variable "total" represents the number of fractions that are LESS THAN
        the current "pivot".


        And then we repeat this whole process until we find exactly K fractions
        that are LESS THAN the current "pivot".

        Once we found that, we return the greatest fraction among all of the
        K smallest ones, and that one GREATEST is stored in "max_fraction":

            if (total == k)
                return {arr[numerator_idx], arr[denominator_idx]};


        If you didn't quite "catch it" or didn't understand it completely, I
        suggest you reading this again in about 2 or three days. Come back and
        I promise you'll be much more likely to understand every little trick
        in this problem.

        Keep in mind that this is NOT an easy one to come up with, so don't
        feel bad if you didn't managed to come up with this one on the first
        try.

        This one requires experience.

*/

/* Time  Beats: 96.91% */
/* Space Beats: 92.65% */

/* Time  Complexity: O(n * logn) */
/* Space Complexity: O(1) */
class Solution {
public:
    std::vector<int> kthSmallestPrimeFraction(std::vector<int>& arr, int k)
    {
        const int N = arr.size();
        std::vector<int> result;

        double left  = 0;
        double right = 1;
        double mid;

        while (left <= right)
        {
            mid = left + (right - left) / 2;

            int j = 1; // Current denominator index

            int total = 0;
            double max_fraction = 0;

            int numerator_idx   = 0;
            int denominator_idx = 0;

            for (int i = 0; i < N; i++)
            {
                while (j < N && 1.0*arr[i] / arr[j] >= mid)
                    j++;

                total += N - j;

                if (j < N && max_fraction < 1.0*arr[i] / arr[j])
                {
                    max_fraction = 1.0*arr[i] / arr[j];

                    numerator_idx   = i;
                    denominator_idx = j;
                }
            }

            if (total == k)
            {
                result = {arr[numerator_idx], arr[denominator_idx]};
                break;
            }

            if (total > k)
                right = mid;
            else
                left = mid;
        }

        return result;
    }
};
