#include <iostream>

/*
    ==============
    === MEDIUM ===
    ==============

    ===================================================================
    1888) Minimum Number of Flips to Make The Binary String Alternating
    ===================================================================

    ============
    Description:
    ============

    You are given a binary string s. You are allowed to perform two types of
    operations on the string in any sequence:

        Type-1: Remove the character at the start of the string s and append it
        to the end of the string.

        Type-2: Pick any character in s and flip its
        value, i.e., if its value is '0' it becomes '1' and vice-versa.

    Return the minimum number of type-2 operations you need to perform such
    that s becomes alternating.

    The string is called alternating if no two adjacent characters are equal.

        For example, the strings "010" and "1010" are alternating, while the
        string "0100" is not.

    =================================
    FUNCTION: int minFlips(string s);
    =================================

    ==========================================================================
    ================================ EXAMPLES ================================
    ==========================================================================

    --- Example 1 ---
    Input: s = "111000"
    Output: 2
    Explanation: Use the first operation two times to make s = "100011".  Then,
                 use the second operation on the third and sixth elements to
                 make s = "101010".


    --- Example 2 ---
    Input: s = "010"
    Output: 0
    Explanation: The string is already alternating.


    --- Example 3 ---
    Input: s = "1110"
    Output: 1
    Explanation: Use the second operation on the second element to make s =
                 "1010".


    *** Constraints ***
    1 <= s.length <= 10^5
    s[i] is either '0' or '1'.

*/

/*
    ------------
    --- IDEA ---
    ------------

    This is a very clever approach.

    When you are solving these types of problems, always ask yourself:"What am
    I being asked to do here?". Even if it's blatantly obvious.

    Here we're being asked to turn some string s into a string of same length
    but with alternating characters.(Only allowed characters are '0' and '1').

    Let's consider Example 1:
        
        s = 1 1 1 0 0 0

    Ask yourself - "What am I being asked to do here? What is the goal I am
    trying to reach?"

    It's to transform this string s:
        
        s = 1 1 1 0 0 0

    into either of these two strings:
        
        s = 0 1 0 1 0 1
        s = 1 0 1 0 1 0


    What is it that we can notice here? Say it out loud even if it's blatantly
    obvious.

    1. We can notice that the desired length and our input string s are of the
       same length.

    2. We can notice that our Input string s can be transformed either in a
       string of the same length that starts with 0 and then alternates OR in a
       string of the same length that starts with 1 and then alternates.


    See how even if it's painfully obvious and kind of shameful to say out
    loud these kinds of things, this genuinely helps you understand the problem
    better and potentially hints you with a possible Solution.
    (It doesn't have to be an efficient but, but any solution is a great
     starting point if the alternative is to perpetually hear the echo "I don't
     know" in your head)

    We have two possible "tools" at our disposal. We can use type-1 and type-2
    operations.

    Type-1 operations doesn't increase the result, whereas type-2 does.

    So let's first consider doing only type-2(flipping bits) and then we'll see
    if and how type-1 can help us.

    Since now we know that from this:

           s = 1 1 1 0 0 0

    we want to get either of these:
        
        alt0 = 0 1 0 1 0 1
        alt1 = 1 0 1 0 1 0

    How can we do that?
    We'll, that is obvious as well, isn't it?

    Let's write result below the Input:

           s = 1 1 1 0 0 0 // Input
        alt0 = 0 1 0 1 0 1 // Potential result 1 (starts with 0)

           s = 1 1 1 0 0 0 // Input
        alt1 = 1 0 1 0 1 0 // Potential result 2 (starts with 1)

        OR 

    How many of these do we have to flip in either case?
    To determine that all we have to do is to XOR each corresponding bit and if
    it's 1(i.e. we had to flip the Input bit) then increment the difference,
    aka "result".

    If we want to get a result that starts with 0:

           s = 1 1 1 0 0 0 // Input
        alt0 = 0 1 0 1 0 1 // Potential result 2
               ^   ^ ^   ^
               |   | |   |
               |   | |   |
               -----------------
                               |
           Then we had to flip 4 bits.


    If we want to get a result that starts with 1:

           s = 1 1 1 0 0 0 // Input
        alt1 = 1 0 1 0 1 0 // Potential result 2 (starts with 1)
                 ^     ^  
                 |     |
                 |     |
                 ---------------
                               |
           Then we had to flip 2 bits.


    So which one should we do?
    The 2nd one, of course. The one where we only have to flip less bits, and
    in this situation, it's the 2nd option, the result that starts with 1.

    However, this is the result if we only use a type-2 operation. There are
    cases where doing only what we did above won't give us the most optimal
    Solution.

    Let's have an Example and prove that.
 
        s = 0 1 0 0 1 0 0 1 1 0 1 

    If we tried the same thing here, meaning to just use type-2 operation, we'd
    get this:

        If we want to get a result that starts with 0:

               s = 0 1 0 0 1 0 0 1 1 0 1 
            alt0 = 0 1 0 1 0 1 0 1 0 1 0 
                         ^ ^ ^     ^ ^ ^
                         | | |     | | |
                         | | |     | | |
                         ------------------
                                          |
           Then we had to flip a total of 6 bits.

        If we want to get a result that starts with 1:

               s = 0 1 0 0 1 0 0 1 1 0 1 
            alt0 = 1 0 1 0 1 0 1 0 1 0 1
                   ^ ^ ^       ^ ^ 
                   | | |       | |
                   | | |       | |
                   ------------------------
                                          |
           Then we had to flip a total of 5 bits.

    So, if we only performed type-2 operations, less flips are performed if we
    want to get a result that starts alternating with 1, therefore we'd get a
    result of 5, which is incorrect.

    The correct result is 2, but for that we'd have to use type-1 operations as
    well.

    For that to happen, we'd first have to use type-1 operation 3 times and
    only then would we perform the same thing as befor, i.e. use only type-2.

    (REMINDER: Type-2 operation means: "Remove the character at the start of
     the string s and append it to the end of the string")

    From our Input string:
        
        s = 0 1 0 0 1 0 0 1 1 0 1 

    we would perform type-1 three times and we'd get this:

        s = 0 1 0 0 1 1 0 1 0 1 0

    Then we'd proceed to do the same as before. We'd only perform type-2
    operations and we'd check which one has to be flipped less times.

    (I'm not going to repeat the whole process again, you get the idea)

    But from:

           s = 0 1 0 0 1 1 0 1 0 1 0
        alt0 = 0 1 0 1 0 1 0 1 0 1 0
                     ^ ^ 
                     | |
                     | |
                     -----------------------------
                                                 |
        The result would be that we flipped only 2 bits.


    The big questions still remains - How do we know how many times should we
    rotate(since type-1 is nothing more than a rotation of bits) before trying
    to use only type-2 and taking the lesser amount of flips?

    Well, the very moment you ask that question is the moment you got very
    close to the result.

    Let's first consider the Brute Force.

    When we use a type-2 operation only, we have to check the entire length of
    our input string twice. Once for the result starting with 0 and once for
    the result starting with 1.

    Since we have to check the entire length of our input string, meaning we
    have to iterate through the entire string, that'd take us O(n) time.

    We also have to do that twice, which means it would take us a total of:
    O(2 * n) time, which is just O(n).

    Okay, but what about type-1 now?

    Notice something very obvious, again. We can rotate the string(use type-1)
    at max of n times before we end up with the exact same string as the input.

    Example:
        s = 1100

    We can rotate it maximally 4 times, meaning there are 4 different rotations
    here. 5th rotation will mean we consider the same one as the one we started
    with.

        Example:
              s = 1 1 0 0

        Rotations:
            0th = 1 1 0 0        // First  unique
            1st = 1 0 0 1        // Second unique
            2nd = 0 0 1 1        // Third  unique
            3rd = 0 1 1 0        // Fourth unique
            4th = 1 1 0 0        // Fifth would be the same as the First one

    Okay, so we can see that there are a total of N **different** rotations.
    (including 0th rotation, i.e. the initial input).

    (N is the length of our input string s)

    If we try to perform a type-2 only operation on EVERY UNIQUE ROTATION, we'd
    get a O(n) * O(n) ==> O(n^2) Time Complexity Solution.

    However, let's consider two DIFFERENT rotations and see if there is any
    repeated work.

    Let's try with Example 1:

           s = 111000

           (Let's consider only alt0)


        ========= 0th Rotation ========= (Initial input) 
               
                      ___________
                     (           )
                     (           )
               s = 1 ( 1 1 0 0 0 )
            alt0 = 0 ( 1 0 1 0 1 )
                     (           )
                     (___________) <---------------------------------
                                                                    |
                                                       These are repeating
        ========= 1st Rotation  =========                           |
                     _____________                                  |
                     (           ) <---------------------------------
                     (           )  
                   --(-----------)--  
                   | (           ) |  
                   | (           ) v  
               s = 1 ( 1 1 0 0 0 ) 1  
            alt0 = 0 ( 1 0 1 0 1 ) 0   
                     (___________)
                        
        

        Difference in 0th Rotation was 4 and since we had to rotate only the
        first bit of s and appending to the end, that means we don't have to
        check the entire string again. We can only, conditionally, decrement
        the difference in the 1st rotation if the 0th rotation's leftmost bit
        was different than alt0's leftmost bit.

        And now since that bit is appended we only have to check that bit.
        It's VERY IMPORTANT to note that now, alt0, is actually going to be
        alt1 since if we extend alt0 we must keep it alternating, thus now it
        will become alt1.

            alt0          = 0 1 0 1 0 1 0 1 0
            alt0_extended = 0 1 0 1 0 1 0 1 0 1

        And since we always consider only N characters at the time, now our
        alt0_extended is going to consider only last N characters:

            alt0_extended = 0 1 0 1 0 1 0 1 0 1
                              ^ ^ ^ ^ ^ ^ ^ ^ ^
                              | | | | | | | | |
                              |_|_|_|_|_|_|_|_|
                                      |
                                    These
                        (See how now this alt0_extended starts with 1?)

        
        Since that is the case and since we have, as we've seen, a total of N
        rotations, we can extend our Input s by appending s to itself:

               s = 111000        // Normal   Length = N
               s = 111000111000  // Extended Length = 2 * N

        And we will also extend alternating strings:

            alt0 = 010101        // Normal   Length = N
            alt0 = 010101010101  // Extended Length = 2 * N

            alt1 = 101010        // Normal   Length = N
            alt1 = 101010101010  // Extended Length = 2 * N

        
        And now we will use a "Fixed Sliding Window technique".

               s = 111000111000
            alt0 = 010101010101
            alt1 = 101010101010


        First we'll consider these:

                    Window (Fixed)
                   ________
                   |      |
               s = |111000|111000
            alt0 = |010101|010101
            alt1 = |101010|101010
                   |______|



        And then we'll move our Fixed Window to the right and consider these:

                     Window (Fixed)
                    ________
                    |      |
               s = 1|110001|11000
            alt0 = 0|101010|10101
            alt1 = 1|010101|01010
                    |______|

        ...

        And so on.

        At the end we just return the minimum amount of flips we had to do in
        any window we considered. (Any window of length N).

        In each window we take minimum out of these three:
            1. Current global minimimum "result"
            2. Difference between current considered rotation in s and alt0
            3. Difference between current considered rotation in s and alt1

        At the end we just return result.

*/

/* Time  Beats: 58.72% */
/* Space Beats: 54.09% */

/* Time  Complexity: O(n) */
/* Space Complexity: O(1) */
class Solution {
public:
    int minFlips(string s)
    {
        int N = s.length();

        s = s + s;
        int two_N = s.length();

        std::string alt_0;
        std::string alt_1;

        alt_0.reserve(two_N);
        alt_1.reserve(two_N);

        for (int i = 0; i < two_N; i++)
        {
            alt_0 += i & 1 ? '1' : '0';
            alt_1 += i & 1 ? '0' : '1';
        }

        int result = INT_MAX;
        int diff_1 = 0;
        int diff_2 = 0;

        int left  = 0;
        int right = 0;
        while (right < two_N)
        {
            if (s[right] != alt_0[right])
                diff_1++;

            if (s[right] != alt_1[right])
                diff_2++;

            if ((right - left + 1) > N)
            {
                if (s[left] != alt_0[left])
                    diff_1--;

                if (s[left] != alt_1[left])
                    diff_2--;

                left++;
            }

            if ((right - left + 1) == N)
                result = std::min({result, diff_1, diff_2});

            right++;
        }

        return result;
    }
};
