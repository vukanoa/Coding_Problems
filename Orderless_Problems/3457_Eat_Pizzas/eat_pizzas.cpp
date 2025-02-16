/*
    ==============
    === MEDIUM ===
    ==============

    ===========================
    3457) Eat Pizzas!
    ===========================

    ============
    Description:
    ============

    You are given an integer array pizzas of size n, where pizzas[i] represents
    the weight of the ith pizza. Every day, you eat exactly 4 pizzas. Due to
    your incredible metabolism, when you eat pizzas of weights W, X, Y, and Z,
    where W <= X <= Y <= Z, you gain the weight of only 1 pizza!

        + On odd-numbered days (1-indexed), you gain a weight of Z.
        + On even-numbered days, you gain a weight of Y.

    Find the maximum total weight you can gain by eating all pizzas optimally.

    =====
    Note: It is guaranteed that n is a multiple of 4, and each pizza can be
          eaten only once.
    =====

    ===================================================
    FUNCTION: long long maxWeight(vector<int>& pizzas);
    ===================================================

    ==========================================================================
    ================================ EXAMPLES ================================
    ==========================================================================

    --- Example 1 ---
    Input: pizzas = [1,2,3,4,5,6,7,8]
    Output: 14
    Explanation:
        On day 1, you eat pizzas at indices [1, 2, 4, 7] = [2, 3, 5, 8]. You gain a weight of 8.
        On day 2, you eat pizzas at indices [0, 3, 5, 6] = [1, 4, 6, 7]. You gain a weight of 6.

    The total weight gained after eating all the pizzas is 8 + 6 = 14.


    --- Example 2 ---
    Input: pizzas = [2,1,1,1,1,1,1,1]
    Output: 3
    Explanation:
        On day 1, you eat pizzas at indices [4, 5, 6, 0] = [1, 1, 1, 2]. You gain a weight of 2.
        On day 2, you eat pizzas at indices [1, 2, 3, 7] = [1, 1, 1, 1]. You gain a weight of 1.

    The total weight gained after eating all the pizzas is 2 + 1 = 3.


    *** Constraints ***
    4 <= n == pizzas.length <= 2 * 10^5
    1 <= pizzas[i] <= 10^5
    n is a multiple of 4.

*/

#include <algorithm>
#include <vector>
using namespace std;


/*
    ------------
    --- IDEA ---
    ------------

    This one is pretty easy if you take enough time to think about it.

    Since the order of elements is important and our elements are "messy", it
    really does scream to us:"Sort it!".

    Let's take a few examples into consideration:
    (All sorted since we don't care about it anymore)

        1) pizzas = [1, 1, 2, 13, 15, 19, 110, 117]
                     0  1  2   3   4   5   6    7

        2) pizzas = [1, 1, 1, 1, 2, 2, 3, 3, 3, 4, 5, 5]
                     0  1  2  3  4  5  6  7  8  9 10 11

        3) pizzas = [4, 5, 6, 6, 7, 7, 7, 7, 11, 14, 15, 15]
                     0  1  2  3  4  5  6  7   8   9  10  11

        4) pizzas = [1, 2, 2, 2, 2, 3, 3, 3, 4, 4, 5, 5]
                     0  1  2  3  4  5  6  7  8  9 10 11

        5) pizzas = [1, 1, 2, 2, 2, 2, 2, 2, 2, 2, 3, 3, 4, 4, 4, 4, 4, 5, 5, 5]
                     0  1  2  3  4  5  6  7  8  9 10 11 12 13 14 15 16 17 18 19

    These are all the examples you'll need. They're excellent. You won't need
    any other example.

    Let's look at our first example:

        1) pizzas = [1, 1, 2, 13, 15, 19, 110, 117]
                     0  1  2   3   4   5   6    7

        First, understand this: At ODD days, we will ALWAYS take the maximum
        number and other 3 will be our smallest numbers.

        Why?

        Because, if we have sorted elements, then it's true for ANY 4 elements
        that: W <= X <= Y <= Z

        Therefore, for 'Z', which we'll add to our result, ALWAYS take the
        biggest one and for the remaining three, ALWAYS take the smallest ones.

        Why?

        Because we ONLY care about the largest one, because that's the only
        thing we'll add to our result, however we want to remove as many small
        ones as we can so that we indirectly maximize our "weight gain".


        So for Odd days, it's easy: ALWAYS take the biggest element and 3
        smallest ones.

        However, for Even days, it's a bit more tricky.
        Let's rewrite our example with marked elements that are taken:

                         taken at Odd days
                     ----------------------------
                     |  |  |                    |
                     |  |  |                    |
                     v  v  v                    v
                     O  O  O                    O    // 'O' for Odd
        1) pizzas = [1, 1, 2, 13, 15, 19, 110, 117]
                     0  1  2   3   4   5   6    7

        Now we're left with:

            pizzas = [13, 15, 19, 110]
                       0   1   2   3

        But we do NOT want to think about it this way. We don't want to keep
        removing pizzas we've eaten, we just want to move our 'L' and 'R'
        pointers.

        Therefore, we'll have something like this insead:

                         taken at Odd days
                     ----------------------------
                     |  |  |                    |
                     |  |  |                    |
                     v  v  v                    v
                     O  O  O                    O    // 'O' for Odd
        1) pizzas = [1, 1, 2, 13, 15, 19, 110, 117]
                     0  1  2   3   4   5   6    7
                               L           R
                               ^           ^
                               |           |
                               |           |
                              left       right


        Now, this is the important part.
        Since we've had a total of 8 elements, and since we're ALWAYS eating
        EXACTLY 4 pizzas, that means we were about to eat this in 2 days.

        Had there been 12 elements, we would be eating them in 3 days.
        Also, keep in mind that we're ALWAYS starting with "Odd" day since the
        count of days is 1-indexed, i.e. starts from 1.


        What I am about to say is the absolute CRUX of this Solution:
        If we are at the EVEN day and we know there aren't ANY DAYS LEFT after
        this EVEN day, then we simply take 'Y' in the remaining 4 elements and
        add it to the result.

        (It's not as if we have any choice for the last day that is EVEN, given
         the description of the problem)

        However, the tricky part is when we DO have more days after this
        current EVEN day.

    Let's see that case. We are going to consider two examples:

        2) pizzas = [1, 1, 1, 1, 2, 2, 3, 3, 3, 4, 5, 5]
                     0  1  2  3  4  5  6  7  8  9 10 11

        4) pizzas = [1, 2, 2, 2, 2, 3, 3, 3, 4, 4, 5, 5]
                     0  1  2  3  4  5  6  7  8  9 10 11


    First, let's consider Example 2)

        2) pizzas = [1, 1, 1, 1, 2, 2, 3, 3, 3, 4, 5, 5]
                     0  1  2  3  4  5  6  7  8  9 10 11

        Since we have a total of 12 pizzas, that means we'll have 3 days to eat
        them up.

        That also means we'll have 2 Odd days and 1 Even day.
        Since "Odd" days are always straightforward, let's consider what
        happens at this "Even" day. Let's see what is so special about it.

        First, let's get rid of the first "Odd" day.

                         taken at Odd days
                     ----------------------------------
                     |  |  |                          |
                     |  |  |                          |
                     v  v  v                          v
                     O  O  O                          O
        2) pizzas = [1, 1, 1, 1, 2, 2, 3, 3, 3, 4, 5, 5]
                     0  1  2  3  4  5  6  7  8  9 10 11
                              L                    R
                              ^                    ^
                              |                    |
                              |                    |
                             left                right



        We're left with remaining 8 elements, i.e.: R - L + 1 <==> 10 - 3 + 1


        In the previous example, since that "Even" day was the last total day,
        we've simply taken the remaining 4 elements and added Y's weight to
        our result.

        However, here this "Even" day is NOT the last one!

        We'll have more day or days after it.

        Let's see what are our options. For "Even" days it seems we always have
        only two options:

            a) Take smallest two and (2nd & 1st largest)
            b) Take smallest two and (3rd & 2nd largest)


        Let's look at our example:

        2) pizzas = [1, 1, 1, 1, 2, 2, 3, 3, 3, 4, 5, 5]
                     0  1  2  3  4  5  6  7  8  9 10 11
                              L                    R

            a) Take the smallest two and largest two. (Y is 2nd largest of remaining pizzas)

                                   1st largest  ---------
                                                        |
                                   2nd largest  ------  |
                                                     |  |
                                   3rd largest  ---  |  |
                                                  |  |  |
                                                  |  |  |
                                                  |  v  v
                                                  |
                                   W  X           |  Y  Z
                                   |  |           |  |  |
                                   |  |           |  |  |
                                   v  v           v  v  |
                                   E  E           E  E  v
                pizzas = [1, 1, 1, 1, 2, 2, 3, 3, 3, 4, 5, 5]
                          0  1  2  3  4  5  6  7  8  9 10 11
                                   L                    R
                                   ^                    ^
                                   |                    |
                                   |                    |
                                  left                right




            b) Take the smallest three and largest one. (Y is 3rd smallest of remaining pizzas)

                                   1st largest  ---------
                                                        |
                                   2nd largest  ------  |
                                                     |  |
                                   3rd largest  ---  |  |
                                                  |  |  |
                                                  |  |  |
                                                  v  v  |
                                                        |
                                   W  X           Y  Z  |
                                   |  |           |  |  |
                                   |  |           |  |  |
                                   v  v           v  v  |
                                   E  E           E  E  v     // 'E' for EVEN
                pizzas = [1, 1, 1, 1, 2, 2, 3, 3, 3, 4, 5, 5]
                          0  1  2  3  4  5  6  7  8  9 10 11
                                   L                    R
                                   ^                    ^
                                   |                    |
                                   |                    |
                                  left                right



        So let's compare them:

               Odd     Even    Odd
            a) Z=5  +  Y=4  +  Z=3  <==> 5 + 4 + 3 = 12

            b) Z=5  +  Y=3  +  Z=5  <==> 5 + 3 + 5 = 13


        Clearly b) is overall better because we'll gain more weight going down
        that path.

        However, that is not greedy. How can we know if we should take:
        a) or b)?


        The problem complicates even more if we have, say, 11 eating days.
        Which one should we take for Even days that are NOT the last day?


    It turns out that the result is actually greedy in a sense.
    Consider this example:

    5) pizzas = [1, 1, 2, 2, 2, 2, 2, 2, 2, 2, 3, 3, 4, 4, 4, 4, 4, 5, 5, 5]
                 0  1  2  3  4  5  6  7  8  9 10 11 12 13 14 15 16 17 18 19

    Let's say we're done with the first Odd day:

    5) pizzas = [1, 1, 2, 2, 2, 2, 2, 2, 2, 2, 3, 3, 4, 4, 4, 4, 4, 5, 5, 5]
                 0  1  2  3  4  5  6  7  8  9 10 11 12 13 14 15 16 17 18 19
                          L                                            R


    What should we do here? a) or b) 'strategy"?

    Actually NONE!
    How? Why?

    Because No matter what we pick, it'll be wrong!
    Why?

    Because we know that there a total of 20 elements, meaning there are a
    total of 5 days, which further means there will be 3 Odd and 2 Even day.

    If there are 3 Odd days and Odd days are straightforward, then why don't we
    try to maximize those first?

    We take largest 3 pizzas in the entire array as proclaim those 3 Z's.
    That way we've maximized our Odd gain.

    But what happens with our Even gain then?

    We simply start getting every 2nd Largest from that point.(We're taking
    every 2nd Largest because for Even days we're required to get Y's and not
    Z's)


    We don't have to worry about small elements, we only need to know how many
    total days we need and how many of those total days will be Odd.

    Then just go from the largest elements and add to our result variable.

    5) pizzas = [1, 1, 2, 2, 2, 2, 2, 2, 2, 2, 3, 3, 4, 4, 4, 4, 4, 5, 5, 5]
                 0  1  2  3  4  5  6  7  8  9 10 11 12 13 14 15 16 17 18 19


    Since we'll have 3 Odd days, let's maximize: 5 + 5 + 5

    Now we have 2 Even days left. Out of the remaining elements, take the 2nd
    largest each time:

                 O1 O1 O1 O2 O2 O2 O3 O3 O3             Y     Y     O3 O2 O1
    5) pizzas = [1, 1, 2, 2, 2, 2, 2, 2, 2, 2, 3, 3, 4, 4, 4, 4, 4, 5, 5, 5]
                 0  1  2  3  4  5  6  7  8  9 10 11 12 13 14 15 16 17 18 19


    At the end we'll have: 5 + 5 + 5 + 4 + 4 = 23

    Now read the code and I'm sure you'll understand it even better.

*/

/* Time  Beats: 66.67% */
/* Space Beats: 66.67% */

/* Time  Complexity: O(N * logN) */
/* Space Complexity: O(1)        */
class Solution {
public:
    long long maxWeight(vector<int>& pizzas)
    {
        const int N = pizzas.size();
        long long result = 0;

        sort(pizzas.begin(), pizzas.end());

        int L = 0;
        int R = N-1;

        int days = N / 4;

        int odd_days  = N / 4 / 2 + (days & 1);
        int even_days = N / 4 / 2;

        while (odd_days > 0)
        {
            result += pizzas[R];

            R--;
            odd_days--;
        }

        R--;
        while (even_days > 0)
        {
            result += pizzas[R];

            R -= 2;
            even_days--;
        }

        return result;
    }
};
