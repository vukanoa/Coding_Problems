#include <iostream>
#include <random>
#include <unordered_map>

/*
    ==============
    === MEDIUM ===
    ==============

    ==================================
    380) Insert Delete GetRandom O(1);
    ==================================

    ============
    Description:
    ============

    Implement the RandomizedSet class:

        - RandomizedSet() Initializes the RandomizedSet object.

        - bool insert(int val) Inserts an item val into the set if not present.
          Returns true if the item was not present, false otherwise.

        - bool remove(int val) Removes an item val from the set if present.
          Returns true if the item was present, false otherwise.

        - int getRandom() Returns a random element from the current set of
          elements (it's guaranteed that at least one element exists when this
          method is called). Each element must have the same probability of
          being returned.

    You must implement the functions of the class such that each function works
    in average O(1) time complexity.

    ===============================
    FUNCTION:
    ===============================

    ==========================================================================
    ================================ EXAMPLES ================================
    ==========================================================================

    --- Example 1 ---
    Input
    ["RandomizedSet", "insert", "remove", "insert", "getRandom", "remove",
     "insert", "getRandom"]

    [[], [1], [2], [2], [], [1], [2], []]
    Output
    [null, true, false, true, 2, true, false, 2]

    Explanation
    RandomizedSet randomizedSet = new RandomizedSet();
    randomizedSet.insert(1);   // Inserts 1 to the set. Returns true as 1 was
                                  inserted successfully.

    randomizedSet.remove(2);   // Returns false as 2 does not exist in the set.

    randomizedSet.insert(2);   // Inserts 2 to the set, returns true. Set now
                                  contains [1,2].

    randomizedSet.getRandom(); // getRandom() should return either 1 or 2
                                  randomly.

    randomizedSet.remove(1);   // Removes 1 from the set, returns true. Set now
                                  contains [2].

    randomizedSet.insert(2);   // 2 was already in the set, so return false.

    randomizedSet.getRandom(); // Since 2 is the only number in the set,
                                  getRandom() will always return 2.


    *** Constraints ***
    -2^31 <= val <= 2^31 - 1
    At most 2 * 105 calls will be made to insert, remove, and getRandom.
    There will be at least one element in the data structure when getRandom is
    called.

*/

int main()
{
    std::random_device dev;
    std::mt19937 rng(dev());
    // distribution in range [1, 6]
    std::uniform_int_distribution<std::mt19937::result_type> dist6(1,6);

    std::cout << dist6(rng) << std::endl;
}

/*
    ------------
    --- IDEA ---
    ------------

    I'm going to take you through the thought process of solving this problem.
    It's a bit tricky, but once you understand it, it becomes intuitive.

    So, this problem is pretty easy if we consider only the first two methods:
        1. bool insert(int val);
        2. bool remove(int val);

    in isolation.

    Inserting a value and Removing a value on Constant time, i.e. O(1) is
    pretty easy once you have a data structure "Hash Set".
    A "Hash Set" will actually be even more helpful because we'll also be able
    to know in O(1) time if a value already exists or if it doesn't exist.

    So rather than using a List and searching in O(n), we can do that using a
    "Hash Set" pretty easily in O(1) time.

    So a simple answer for these two methods is literally to just use a
    "Hash Set".

    But the problem comes when we get to the third function: int getRandom()

    Getting a random value isn't very easy, especially with the exact same
    probability. Even perfect functions can't do it perfectly. But that's
    exactly what we're going to do. We're going to use a bulit-in function to
    do that.

    The easy way to get a random value is, suppose you have an array of 3
    elements, to generate a random value based on the indices, which in this
    case are: 0, 1 and 2.

            [1, 2, 3]
             0  1  2

    If we had an array of elements, then we would've generated a random number
    within the range of indices and then we would index the number and get it.

    But we can't do that with a "Hash Set". "Hash Sets" are unordered.
    We could technically convert a "Hash Set" into an array, but that would
    take O(n) time to accomplish.

    So we can't just maintain a Hash Set. We also have to maintain an array at
    the same time.
    Everytime we add a value to a Hash Set, we also add a value to our array.

    With this additional array, we will be able to get a random value in O(1).

    But now the problem is a little bit subtle. Let's look at an example:
        Before:
            Hash Set: {} // This has no order
               Array: []

        1. Insert 1
            Inside the "insert" function we check if "1" already exists in a
            Hash Set(we do that in O(1) time). It's not in our Hash Set, so we
            add 1, but we also add it to the **end** of our array(currently
            empty) and we return true(meaning that it is inserted).

            Hash Set: {1      } // This has no order
               Array: [1]

        2. Insert 2
            Inside the "insert" function we check if "2" already exists in a
            Hash Set. It's not in our Hash Set, so we add 2, but we also add it
            to the **end** of our array and we return true.

            Hash Set: {1, 2   } // This has no order
               Array: [1, 2]

        3. Insert 1 (again)
            Inside the "insert" function we check if "1" already exists in a
            Hash Set. It does - return false.

        4. Get a Random value
            Since we have an array, we just do:
                return vec[rand() % vec.size()];

        5. Remove 2
            Inside "remove" function check if it does exist in our Hash Set. It
            does, so we pop it from our HashSet and we pop 2 from the **end of
            the array**.

            And if we wanted to get another random value, the same line would
            work indeed:
                return vec[rand() % vec.size()];

            That was easy because in that case, we removed we removed a value
            from the end of our array. But what if we were actually removing
            a value from the middle of our array.

            So let's assume that our Hash Set and our array looked like this:
                Hash Set: {1, 2, 3 } // This has no order
                   Array: [1, 2, 3]

            And imagine that we waned to remove a "2".
            From the Hash Set, removing a "2" in O(1) is easy, however how
            would we remove the "2" from the array in O(1) as well?

            Usually, how do you remove an element from an array?
            You index it and then shift all of the elements that come after it.
            But if we do that then it's a O(n) Time Complexity, which is not
            allowed.

            So, how do we do it?

            The first thing is that if we were removing "2" from the array, we
            don't even know what index "2" is at. We would have to search for
            it, which is forbidden because that is O(n).

            We know for sure that it exists, because of our Hash Set, but we
            don't know where it is.

            So instead of using a Hash Set, we're going to use a Hash Map.
            We are going to be mapping each element that we inserted to the
            index that it was inserted at.

            The "key"   is going to be an element we inserted.
            The "value" is going to be the index of that element in the array.

            In this example, we'd have something like this:

                            Hash Map

                        |  Key  :  Value |
                        +----------------|
                        |   1   :    0   |
                        +----------------|
                        |   2   :    1   |
                        +----------------|
                        |   3   :    2   |
                        +----------------|

                              Array
                            [1, 2, 3]
                             0  1  2


            So that's one part of the "remove" function.
            Now if we wanted to remove "2", we know exactly where it's at.

            Can we just erase that value? Can we just set it to 0 or something?
            No!

            If we would to set it to 0, -1 or some other default value, then
            we would have something like this:

                              Array
                            [1, 0, 3]
                             0  1  2

            Now imagine that someone called GetRandom(). What if the random
            value was index 1?
            It would give a non-existant value, which isn't correct.


            Okay, so that doesn't work. But how about replacing that removed
            value with it's left or right neighbor?
            Well in that case, we'd have something like this;

                              Array
                            [1, 1, 3]
                             0  1  2

            Now imagine that someone called GetRandom() again.
            It is noted that:
                "Each element must have the same probability of being returned"

            In this case, "1" would have a greater probability of getting
            picked than 3 and that is not correct.

            So what should we do?
            Remember that we could remove a value from the end of the array in
            O(1) time.

            ##################################################################
            #################### THIS IS THE TRICK ###########################
            ##################################################################
            So a clever way of handling this is:
            Take the last value and copy it in the index that we are removing
            from and then pop the last element of the array.

            That's done in O(1).

            So to remove a "2" from this:

                            Hash Map
                        |  Key  :  Value |
                        +----------------|
                        |   1   :    0   |
                        +----------------|
                        |   2   :    1   |
                        +----------------|
                        |   3   :    2   |
                        +----------------|

                              Array
                            [1, 2, 3]
                             0  1  2

            Take the last value, which is "3" in our case, copy it in the index
            at which "2" resides in the array(take that information from the
            Hash Map) and then pop back the last element of the array and erase
            it from the Hash Map.
            Also, DON'T FORGET to update the "Value" of last element("3" in our
            case) in the Hash Map. "3" used to be at index 2, now it's at index
            1.

                            Hash Map
                        |  Key  :  Value |
                        +----------------|
                        |   1   :    0   |
                        +----------------|
                        |   3   :    1   | // Updated value to 1
                        +----------------|

                              Array
                              [1, 3]
                               0  1

    Using all these tricks we're able to implement this in O(1) time.




    If you write getRandom() function like this:
        std::random_device dev;
        std::mt19937 rng(dev());

        // Distribution in range [0, vec.size() - 1]
        std::uniform_int_distribution<std::mt19937::result_type> gen(0, vec.size() - 1);

        return vec[gen(rng)];

    It is noticeably slower than simply writing:
        return vec[rand() % vec.size()];

*/

// With "mt19937" random number generator
/* Time  Beats:  5.20% */
/* Space Beats: 33.72% */

// Using simple modulo arithmetic
/* Time  Beats: 97.85% */
/* Space Beats: 46.54% */

/* Time  Complexity: O(1) */
/* Space Complexity: O(n) */
class RandomizedSet {
public:
    RandomizedSet()
    {

    }

    bool insert(int val)
    {
        if (umap.count(val))
            return false;

        umap.insert({val, vec.size()});
        vec.push_back(val);

        return true;
    }

    bool remove(int val)
    {
        if (umap.count(val) == 0)
            return false;

        int idx = umap[val];
        int last_element = vec.back();

        vec[idx] = last_element;
        umap[last_element] = idx;

        vec.pop_back();
        umap.erase(val);

        return true;
    }

    int getRandom()
    {
        int random_index = std::rand() % vec.size();
        return vec[random_index];
    }

private:
    std::unordered_map<int, int> umap;
    std::vector<int> vec;
};

/**
 * Your RandomizedSet object will be instantiated and called as such:
 * RandomizedSet* obj = new RandomizedSet();
 * bool param_1 = obj->insert(val);
 * bool param_2 = obj->remove(val);
 * int param_3 = obj->getRandom();
 */
