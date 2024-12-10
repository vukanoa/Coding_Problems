#include <iostream>
#include <vector>

/*
    ==============
    === MEDIUM ===
    ==============

    ====================================
    1027) Longest Arithmetic Subsequence
    ====================================

    ============
    Description:
    ============


    Given an array nums of integers, return the length of the longest arithmetic subsequence in nums.

    Note that:

        + A subsequence is an array that can be derived from another array by
          deleting some or no elements without changing the order of the
          remaining elements.

        + A sequence seq is arithmetic if seq[i + 1] - seq[i] are all the same
          value (for 0 <= i < seq.length - 1).

    =======================================================
    FUNCTION: int longestArithSeqLength(vector<int>& nums);
    =======================================================

    ==========================================================================
    ================================ EXAMPLES ================================
    ==========================================================================

    --- Example 1 ---
    Input: nums = [3,6,9,12]
    Output: 4
    Explanation:  The whole array is an arithmetic sequence with steps of
                  length = 3.

    --- Example 2 ---
    Input: nums = [9,4,7,2,10]
    Output: 3
    Explanation:  The longest arithmetic subsequence is [4,7,10].

    --- Example 3 ---
    Input: nums = [20,1,15,3,10,5,8]
    Output: 4
    Explanation:  The longest arithmetic subsequence is [20,15,10,5].


    *** Constraints ***
    2 <= nums.length <= 1000
    0 <= nums[i] <= 500

*/

using namespace std;

/*
    ------------
    --- IDEA ---
    ------------

    Let's try to write all of the possible differences between current element
    and every remaining element to its right.


                  0   1    2   3    4   5   6  // indices

        nums = [ 20,  1,  15,  3,  10,  5,  8]
                -19  14  -12  -7   -5   3   /
                 -5   2   -5   2   -2
                -17   9  -10   5
                -10   4   -7
                -15   7
                -12


    Now it is obvious that there is now way to do this in a more efficient way
    than O(N^2).

    Why?
    Because there is no "repeated work" here. We do indeed need to see all of
    these values. There's no way around it.

    So where are we supposed to use dp anyway then?

    Well it turns out this O(N^2) would be insufficient if we would to only
    pass roughly N times for every element in the array.

    For example, some element can have a difference of -5, and some other
    element can have difference of -5 as well. That doesn't mean the answer is
    3.

    (3 because if we find that the maximum length of arithmetic subsequence for
    any difference is only 2 elements, we'll see that by checking the current
    one, therefore we have to add one to it, therefore we say it's 2. If we
    find two elements with same difference, then we say there are 3 elements)

    Example:
        nums = [ 7,  5,  6,  3]
                -2   1   -3  /
                -1  -2
                -4

        Since both at 7 and at 5 are differences of -2, then that means there
        is a subsequence of length 3.
        Why?
        Well, 7 has a difference with 5 and 5 has a difference with 3, thus

            [7,5,3] is a subsequence. And we've found only "-2"s.


    However this would be misleading to leave like this.
    What if we, again, had two "-2"s, but the subsequence was NOT of size 3?
    How is tha even possible?

    Consider this example:
        nums = [ 7, 5, 11, 13]
                -2  6  -2   /
                 4  8
                 6

        Here we, again, have two differences of "-2". Does that mean the
        subsequence is of length 3? No!!

        Why not?

        Because 7 has a difference of "-2" with 5, but next difference of "-2"
        doesn't continue from 5, instead it happened from 11 to 13.

        If we were to say there is a length 3 subsequence with arithmetic diff
        of 3, what would that look like?

            [7, 5, 11, 13] ??

        This doesn't make any sense.
        The difference between 7 and 5 is -2, and the difference between 11 and
        13 is also -2, so why not?

        Because the difference between 5 and 11 is 6.
        We need to have such a subsequence where EVERY two adjacent elements's
        difference is the same.


    So in order to remedy this, we need to see if there is a difference of "X"
    kind of consecutively. (I don't mean literally consecutively, but
    subsequence consecutive)

    Let me explain:

    If we've found a difference of -2 between 7 and 5, then in order to
    continue this subsequence, we'd need to find a difference of -2 FROM 5.

    Then, if starting at 5, there is some element to the right that makes the
    difference of -2 as well, then we need to start at that element, and so on.


    Thus, we conclude, we'll need to have a 2D vector, aka matrix and use our
    Dynamic Programming approach to solve this.

    Let's use our first exampe from this Explanation:

                  0   1    2   3    4   5   6  // indices

        nums = [ 20,  1,  15,  3,  10,  5,  8]
                -19  14  -12  -7   -5   3   /
                 -5   2   -5   2   -2
                -17   9  -10   5
                -10   4   -7
                -15   7
                -12

        We'll have N amount of ROWS, but we'll have 2000 columns.
        Why 2000?

        Because it is said that nums[i] can be [0, 500].
        Thus:
            1) Minimum difference possible is -500 - 500 which is -1000
            2) Maximum difference possible is +500 + 500 which is +1000

        Total range of possible differences is: +1000 - (-1000) which is 2000.

        So for each element, i.e. for each row, we want to say how long is the
        subsequence for that difference so far.

        For example:
            for element 20,  15 - 20 = -5, thus difference of -5 for row 1(elem
            15) length of the longest "consecutive" subsequence is 2.

            Why 2?
            Because subsequence of [20, 15] is of length 2. The difference
            between every two adjacent elements in it is 2.

            So we would mark dp[row for elem 15][diff] = max(2, dp[row for elem 20][diff] + 1)

            Why dp[row for elem 20][diff] + 1??

            Because it's either only length of 2(minimal possible) or it's
            previous longest subsequence of that difference that ENDS at elem.
            20.

            Read that again. It is confusing at first, but you'll get it.

            If you still don't understand it, let's try with a continuation of
            this difference further down the vector "nums".


            Let's say we're trying every single element to the right of 15 to
            see the differences it makes.

            We'll ignore all the other differences except for:  10 - 15 = -5
                                                                 j    i

            Here, the difference is, again, -5. We are again going to do this:

                dp[row][diff] = max(2, dp[row for elem 15][diff] + 1)

            Why dp[row for elemt 15][diff]??

            Because we see that subsequence length with difference -5 that
            begins at current element 15, is of length 2.

            BUT, we have to ask - Is there any subsequence with difference -5
            so far that ENDS on curr element 15?

            There certainly is, remember what we've already found:

                [20, 15]

            At current element's row(elem 15) difference(column) of -5 is 2.
            Why 2?

            Because a subsequence with difference of -5 ENDS at element 15, at
            the current row 'i'.


            Therefore, now for element 10(row 'j') we are going to say it is:

                dp[row for elem 10][diff] = max(2, dp[row for elem 15][diff] + 1)


            Let me fill the table below. Try to read this explanation above and
            look at this table. It will click at some point. Don't get
            dicouraged.


            Remember that we have 2000 columns, where:

                column 0    represents number: -1000
                column 1    represents number: -999
                ...
                column 1999 represents number: +1000

            Thus, when calculating the difference we'll always do:

                nums[j] - nums[i] + 1000


        Let's rewrite our Example, for readability purposes:

                      0   1    2   3    4   5   6  // indices
            nums = [ 20,  1,  15,  3,  10,  5,  8]
                    -19  14  -12  -7   -5   3   /
                     -5   2   -5   2   -2
                    -17   9  -10   5
                    -10   4   -7
                    -15   7
                    -12
            Sorted:
                -19 -17 -15 -12 -12 -10 -10 -7 -7 -5 -5 -5 -2 2 2 3 4 5 7 9 14

            -19 +1000 = 9981
            -17 +1000 = 9983
            -15 +1000 = 9985
            -12 +1000 = 9988
            -12 +1000 = 9988
            -10 +1000 = 9990
            -10 +1000 = 9990
             -7 +1000 = 9993
             -7 +1000 = 9993
             -5 +1000 = 9995
             -5 +1000 = 9995
             -5 +1000 = 9995
             -2 +1000 = 9998
              2 +1000 = 1002
              2 +1000 = 1002
              3 +1000 = 1003
              4 +1000 = 1004
              5 +1000 = 1005
              7 +1000 = 1007
              9 +1000 = 1009
             14 +1000 = 1014

        Let's rewrite our Example, for readability purposes:

                      0   1    2   3    4   5   6  // indices
            nums = [ 20,  1,  15,  3,  10,  5,  8]
                    -19  14  -12  -7   -5   3   /
                     -5   2   -5   2   -2
                    -17   9  -10   5
                    -10   4   -7
                    -15   7
                    -12
            Sorted:
                -19 -17 -15 -12 -12 -10 -10 -7 -7 -5 -5 -5 -2 2 2 3 4 5 7 9 14


           -------- "row" can be either 'i' or 'j'. Current elem. is at 'i'.
           |                                        But elem. on the right side
           |                                        of 'i' is element at 'j'.
           |
           |
           |       diff
           |        -19              -17               -15             -12              -10                -7              -5               -2         2        3        4        5                7               9               14
           |       9981             9983             9985             9988             9990              9993            9995             9998      1002     1003     1004     1005             1007      ...   1009      ...    1014 
           v    +--------+  ...  +--------+  ...  +--------+  ...  +--------+  ...  +--------+  ...  +--------+  ...  +--------+  ...  +--------+--------+--------+--------+---------+       +--------+       +--------+       +--------+ 
          row 0 |        +       +        +       +        +       +        +       +        +       +        +       +        +       +        +        +        +        +         +  ...  +        +  ...  +        +  ...  +        + 
                +--------+  ...  +--------+  ...  +--------+  ...  +--------+  ...  +--------+  ...  +--------+  ...  +--------+  ...  +--------+--------+--------+--------+---------+       +--------+       +--------+       +--------+ 
              1 |   2    +       +        +       +        +       +        +       +        +       +        +       +        +       +        +        +        +        +         +  ...  +        +  ...  +        +  ...  +        + 
                +--------+  ...  +--------+  ...  +--------+  ...  +--------+  ...  +--------+  ...  +--------+  ...  +--------+  ...  +--------+--------+--------+--------+---------+       +--------+       +--------+       +--------+ 
              2 |        +       +        +       +        +       +        +       +        +       +        +       +   2    +       +        +        +        +        +         +  ...  +        +  ...  +        +  ...  +   2    + 
                +--------+  ...  +--------+  ...  +--------+  ...  +--------+  ...  +--------+  ...  +--------+  ...  +--------+  ...  +--------+--------+--------+--------+---------+       +--------+       +--------+       +--------+ 
              3 |        +       +   2    +       +        +       +    2   +       +        +       +        +       +        +       +        +    2   +        +        +         +  ...  +        +  ...  +        +  ...  +        + 
                +--------+  ...  +--------+  ...  +--------+  ...  +--------+  ...  +--------+  ...  +--------+  ...  +--------+  ...  +--------+--------+--------+--------+---------+       +--------+       +--------+       +--------+ 
              4 |        +       +        +       +        +       +        +       +   2    +       +   2    +       +   2    +       +        +        +        +        +         +  ...  +        +  ...  +   2    +  ...  +        + 
                +--------+  ...  +--------+  ...  +--------+  ...  +--------+  ...  +--------+  ...  +--------+  ...  +--------+  ...  +--------+--------+--------+--------+---------+       +--------+       +--------+       +--------+ 
              5 |        +       +        +       +   2    +       +    2   +       +   2    +       +        +       +   2    +       +        +    2   +        +        +         +  ...  +   2    +  ...  +        +  ...  +        + 
                +--------+  ...  +--------+  ...  +--------+  ...  +--------+  ...  +--------+  ...  +--------+  ...  +--------+  ...  +--------+--------+--------+--------+---------+       +--------+       +--------+       +--------+ 
              6 |        +       +        +       +        +       +    2   +       +        +       +   2    +       +        +       +    2   +        +        +        +    2    +  ...  +        +  ...  +        +  ...  +        + 
                +--------+  ...  +--------+  ...  +--------+  ...  +--------+  ...  +--------+  ...  +--------+  ...  +--------+  ...  +--------+--------+--------+--------+---------+       +--------+       +--------+       +--------+ 


    Slowly go through this table and I'm sure you'll understadn it if you've
    read the above explanation.

    (Maybe not the best example since tehre are subsequences of length 3 or
     more but it's not that big of a deal)

*/

/* Time  Beats: 72,93% */
/* Space Beats: 19.67% */

/* Time  Complexity: O(n^2) */
/* Space Complexity: O(M) */ // Where M == (max_elem(nums) + max_elem(nums)) - (min_elem(nums) - min_elem(nums))
class Solution {
public:
    int longestArithSeqLength(vector<int>& nums)
    {
        const int N = nums.size();
        int result = 2;

        vector<vector<int>> dp(N, vector<int>(2000, 0));
        for (int i = 0; i < N; i++)
        {
            for (int j = i+1; j < N; j++)
            {
                int diff = nums[j] - nums[i] + 1000; // +1000 for indexing

                dp[j][diff] = max(2, dp[i][diff] + 1);
                result = max(result, dp[j][diff]);
            }
        }

        return result;
    }
};
