#include <iostream>
#include <vector>

/*
    ==============
    === MEDIUM ===
    ==============

    ===========================
    735) Asteroid Collision
    ===========================

    ============
    Description:
    ============

    We are given an array asteroids of integers representing asteroids in a
    row.

    For each asteroid, the absolute value represents its size, and the sign
    represents its direction (positive meaning right, negative meaning left).
    Each asteroid moves at the same speed.

    Find out the state of the asteroids after all collisions. If two asteroids
    meet, the smaller one will explode. If both are the same size, both will
    explode. Two asteroids moving in the same direction will never meet.

    ================================================================
    FUNCTION: vector<int> asteroidCollision(vector<int>& asteroids);
    ================================================================

    ==========================================================================
    ================================ EXAMPLES ================================
    ==========================================================================

    --- Example 1 ---
    Input: asteroids = [5,10,-5]
    Output: [5,10]
    Explanation: The 10 and -5 collide resulting in 10. The 5 and 10 never
                 collide.


    --- Example 2 ---
    Input: asteroids = [8,-8]
    Output: []
    Explanation: The 8 and -8 collide exploding each other.


    --- Example 3 ---
    Input: asteroids = [10,2,-5]
    Output: [10]
    Explanation: The 2 and -5 collide resulting in -5. The 10 and -5 collide
                 resulting in 10.


    *** Constraints ***
    2 <= asteroids.length <= 10^4
    -1000 <= asteroids[i] <= 1000
    asteroids[i] != 0

*/

/*
    ------------
    --- IDEA ---
    ------------

    Right out off the bat, let me show you a few more examples. Examples that
    they gave us are insufficient.

    Input: asteroids = [-1, -3, 5]
    Output: [-1, -3, 5]

    This one, above, is important because it shows you that, since all the
    asteroids are **on the same row and moving at the same speed**, asteroids
    that are all the way to the left are **NEVER** going to collide with any
    asteroid that is moving towards the right.

    That is an important thing to note.

    One could think that the Output of the previous example should be:
    Output: [5]

    But that is INCORRECT!


    The best advice I could give to you is to draw them in one row:

        <--       <--       -->
         -1        -3        5


    Reading them from left-to-right, which of them will collide?
    That's right - None!


    Let's draw one of their given Examples:

    Input: asteroids = [10,2,-5]
    Output: [10]

        -->       -->       <--
         10        2        -5


    Again - Which of them will collide? Now it's:  2 and -5

    -5 will "win" and then we'll be in this situation:

        -->       <--
         10       -5

    We'll have a collision once again, however now, "-5" is going to "lose".
    Therefore, we'll end up only with:

        -->
         10

    I.e. Output: [10]


    One more thing is important to emphasize:

        asteroids[i] != 0

    Asteroids CANNOT be of value 0. We'll take advantage of that.


    Now with all this out of the way, there is only ONE case in which we are
    going to have a collision and that is:

        If  stack is NOT empty
                &&
            asteroid on top of the stack is POSITIVE
                &&
            asteroids[i] is NEGATIVE

    That is THE ONLY CASE IN WHICH WE ARE GOING TO HAVE A COLLISION.

    Think about it.

    1)
        If the stack is empty, it's impossible to have a collison.

    2)
        If the asteroid on top of the stack is NEGATIVE, then it doesn't matter
        if asteroids[i] is positive or negative, there won't be a collison
        either way.

                stack: [-3, -7, -2, -5]

                asteroids[i] = 6
                    or
                asteroids[i] = -6

            As you can see, there won't be any collision, independent of the
            sign of asteroids[i].


    3) If the asteroids[i] (the one we're trying to process) is POSITIVE.

                stack: [1, 2, 3]    // All moving to the right
                    or
                stack: [-1, -2, -3] // All moving to the left
                    or
                stack: [-1, -2, 3]  // Mixed
                    or
                stack: [-1,  2, 3]  // Mixed

            If asteroids[i] > 0, then no matter which state the "stack" is in,
            we'll NEVER have a collision.



    Therefore, in order to have collision, NONE of these 3 must be true.

    So, the collision happens once the stack is NOT empty and once on the top
    of the stack is a POSITIVE asteroid and the asteroids[i] is NEGATIVE.

        stack[.., .., .., .., POSITIVE]

        asteroids[i] is NEGATIVE


    Now we have 3 possible scenarios:

        1) top: 1  && asteroids[i]: -2    // top < abs(asteroids[i])

        2) top: 5  && asteroids[i]: -2    // top > abs(asteroids[i])

        3) top: -2 && asteroids[i]: -2    // top == abs(asteroids[i])


    In order to simplify these cases, we can add "top" and "asteroids[i]" and
    then branch if accordingly.

        diff top + asteroids[i]

        1) diff = 1 + (-2) = -1    // diff < 0

        2) diff = 5 + (-2) = 3     // diff > 0

        2) diff = 2 + (-2) = 0     // diff == 0


    If it's:

        1)
            Pop from the stack and try to use the same asteroids[i] if the
            previous two conditions are met.
            (i.e. stack NOT empty && stack.back())

            We know that the 3rd condition is always met since we wouldn't be
            in this "while loop" in the first place.

            If the stack gets to be empty and are asteroids[i] is NEGATIVE,
            then and only then are we allowed to push a NEGATIVE asteroids[i]
            to the stack.


        2)
            Then we don't have to do anything. We just have to start processing
            the next asteroid, meaning i++ and then check the next asteroid.


        3)
            Pop from the stack and start processing next asteroid. Meaning i++
            and then check the next asteroid.


    You would quickly realize that is somewhat difficult to implement these
    cases one-by-one, therefore we can use one property that I've noted at the
    beginning:

        asteroids[i] != 0        // Asteroids CANNOT be negative


    After reading these three scenarios, you'll realize that only in the first
    one, i.e. diff < 0, are we permitted to push asteroids[i] to the stack.

    Therefore, if we go to any other case, meaning 2) or 3), then we will mark
    asteroids[i] to be EQUAL to 0.

    (Remember how asteroids != 0?)

    We'll use that marking system to check, AFTER THE WHILE LOOP ENDS, if we
    are allowed to push current asteroids[i] to the stack.


        if (asteroids[i] != 0)
            stack.push_back(asteroids[i]);

    After we're done processing every single asteroid in the row, then we
    simply return "stack".

    (Note that we're using a "vector" instead of a "stack, since we can easily
     use it as a stack and, this is the main reason, we're asked to return a
     vector at the end. Therefore, we'll only use a std::vector as a stack and
     we'll return it as a result at the end)

*/

/* Time  Beats: 99.04% */
/* Space Beats: 62.60% */

/* Time  Complexity: O(n) */
/* Space Complexity: O(1) */ // We don't count return vector as additional
class Solution {
public:
    std::vector<int> asteroidCollision(std::vector<int>& asteroids)
    {
        std::vector<int> stack;

        for (int i = 0; i < asteroids.size(); i++)
        {
            while (!stack.empty() && stack.back() > 0 && asteroids[i] < 0)
            {
                int diff = stack.back() + asteroids[i];

                if (diff < 0)
                    stack.pop_back();
                else if (diff > 0)
                    asteroids[i] = 0;
                else
                {
                    asteroids[i] = 0;
                    stack.pop_back();
                }
            }

            if (asteroids[i] != 0)
                stack.push_back(asteroids[i]);
        }

        return stack;
    }
};
