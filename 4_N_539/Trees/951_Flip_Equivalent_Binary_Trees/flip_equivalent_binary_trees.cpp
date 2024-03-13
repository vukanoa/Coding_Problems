#include <iostream>

/*
    ==============
    === MEDIUM ===
    ==============

    =================================
    951) Flip Equivalent Binary Trees
    =================================

    ============
    Description:
    ============

    For a binary tree T, we can define a flip operation as follows: choose any
    node, and swap the left and right child subtrees.

    A binary tree X is flip equivalent to a binary tree Y if and only if we can
    make X equal to Y after some number of flip operations.

    Given the roots of two binary trees root1 and root2, return true if the two
    trees are flip equivalent or false otherwise.

    ===========================================================
    FUNCTION: bool flipEquiv(TreeNode* root1, TreeNode* root2);
    ===========================================================

    ==========================================================================
    ================================ EXAMPLES ================================
    ==========================================================================

    --- Example 1 ---
        ___________1___________          ___________1___________
        _____2___________3_____          _____3___________2_____
        __4_____5_____6________          ________6_____4_____5__
        ______7___8____________          __________________8___7

    Input: root1 = [1,2,3,4,5,6,null,null,null,7,8],
           root2 = [1,3,2,null,6,4,5,null,null,null,null,8,7]
    Output: true
    Explanation: We flipped at nodes with values 1, 3, and 5.


    --- Example 2 ---
    Input: root1 = [], root2 = []
    Output: true


    --- Example 3 ---
    Input: root1 = [], root2 = [1]
    Output: false


    *** Constraints ***
    The number of nodes in each tree is in the range [0, 100].
    Each tree will have unique node values in the range [0, 99].

*/

/*
    ------------
    --- IDEA ---
    ------------


    *****************
    *** Intuition ***
    *****************

    The very first thing that is **necessary** for you to "notice" is the exact
    words used in the Description.

    Let me point out what I mean:

    "A binary tree X is flip equivalent to a binary tree Y if and only if we
    can make X equal to Y after some number of flip operations."

    Do you see it? If not, let me help with a capitalization.

    "A binary tree X is flip equivalent to a binary tree Y if and only if we
    CAN make X equal to Y AFTER SOME NUMBER OF FLIP OPERATIONS."

    What I am trying to get at is the following - They are asking us if root1
    and root2 are flip-equivalent, which means that either:
    1. Subtree/s of root1 and root2 are already the same OR
    2. Subtree/s of root1 and root2 CAN BE MADE the same after SOME FLIPS

    In other words - We do NOT necessarily have to flip one subtree and then
    compare it to the subtree of another tree, instead we only have to perform
    that action if the compared two subtrees(of two different trees) are NOT
    the same.

    Let's look at Example 1:

                 root1                            root2
                   |                                |
                   v                                v
        ___________1___________          ___________1___________
        _____2___________3_____          _____3___________2_____
        __4_____5_____6________          ________6_____4_____5__
        ______7___8____________          __________________8___7

    root1's RIGHT subtree and root2's LEFT subtree are flipEquivalent. Why?
    Because they are mirrored, which means that if you perform flips at every
    sublevel, they will be equivalent.

    It's important to emphasize that they are NOT asking us if the root1 is the
    mirror tree of root2.

    However, on the other hand, when we check root1's LEFT subtree and root2's
    RIGHT subtree we can see that those two subtrees are already EQUIVALENT. No
    flips should be made, they are already the same.

    This is what they meant when they said:

    "A binary tree X is flip equivalent to a binary tree Y if and only if we
    CAN make X equal to Y AFTER SOME NUMBER OF FLIP OPERATIONS."

    We CAN make SOME NUMBER OF FLIPS OPERATIONS, but we absolutely DO NOT have
    to do that.

    They are only asking us:"If root1's LEFT subtree is NOT equivalent already
    with neither root2's LEFt or root2's RIGHT subtree, can you MAKE root2's
    LEFT or root2's RIGHT subtree be equivalent to root1's LEFT subtree by
    performing SOME NUMBER OF FLIPS?

    Once you understand what I wrote right up above, all you have to do now is
    to put the code where your mouth is.


    ********************************
    *** Explanation for the Code ***
    ********************************

    It's obvious that this will be solved by using recursion.

    Since we, at each call, have only one variable per tree(i.e. root1 & root2)
    the first thing we must always check is if both root1 & root 2 are NOT
    nullptr.

    If BOTH are nullptr, we return true, since empty trees are indeed both
    equivalent and flip-equivalent(even if this doesn't make sense to say for
    two empty trees, but it's still true nonetheless).

    If one is a nullptr and the other one is not, we return false since no
    amount of flips could be done to make those two trees equivalent since they
    differ at the fundamental level - Root level.

        Not necessary, but it's a nice implementation "trick" to know:

        We do NOT have to write it like this:

            // WORSE
            if (!root1 && !root2)
                return true;
            else if (!root1)
                return false;
            else if (!root2)
                return false;

        We can write it like this:

            // BETTER
            if (!root1 && !root2)
                return true;
            else if (!root1 || !root2)
                return false;

        If the first if statement is FALSE, then that means that either:
            1. Neither root1 nor root2 are nullptr, OR
            2. Either root1 or root2 is a nullptr

        Since we already assessed that it's NOT true that BOTH root1 and root2
        are nullptr, we only care to check if Either root1 or root2 is nullptr.

        If either root1 or root2 is nullptr, we return false since these two
        trees differ at the fundamental level and no amount of flips can make
        them equivalent.

    If neither root1 nor root2 is nullptr, then we need to check if their "val"
    differ. If they do, we return false immediately since, again, no amount of
    flips can be done to make those two trees flip-equivalent since they, also,
    differ at the fundamental, root, level.

    Now, look at the Example 1 again:

                 root1                            root2
                   |                                |
                   v                                v
        ___________1___________          ___________1___________
        _____2___________3_____          _____3___________2_____
        __4_____5_____6________          ________6_____4_____5__
        ______7___8____________          __________________8___7


    Repeat what we already noticed:

        Two subtrees(since at this point we only care about subtrees
        equivalency because we already assessed that the roots themselves are
        equivalent) are flip-equivalent if either:

        1. Two subtrees are already equivalent, OR
        2. Two subtrees CAN be made equivalent by performing SOME number of
           flips. ("some" number of flips can be NONE, but in that case it
           would mean option 1. "selected, i.e. true)

    As a product of the observed situation, we see that we have to check if:
        1. root1's LEFT subtree is already equivalent to root2's LEFT or RIGHT
           subtree.

           OR

        2. root1's LEFT subtree CAN BE MADE equivalent to root2's LEFT or RIGHT
           subtree by performing SOME NUMBER OF FLIPS OPERATIONS.(Notice that,
           here, "SOME" cannot be 0, since if it were 0, that would mean we
           already "selected" the 1. options, i.e. the 1. option would be true)

    Therefore, first we have to check the root1's LEFT subtree, however if we
    find out that root1's LEFT subtree is not equivalent to neither root2's
    LEFT or root2's RIGHT subtree and that we cannot even make at least one of
    them(root2's LEFT or root2's RIGHT) equivalent to root1's LEFt, then we do
    not have to do the same check-up for root1's RIGHT subtree since we already
    know that the trees themselves are not possible to be equivalent by
    performing any number of flips.

    Therefore, we should immediately stop by returning false and not waste any
    time.

    If, on the other hand, root1's LEFT subtree is or can be made to be
    equivalent to root2's LEFT or root2's RIGHT, then we can proceed to do the
    other check-up.

    Other check-up is if root1's RIGHT subtree is equivalent or can be made
    equivalent to root2's LEFT or RIGHT subtree by performing any number of
    flips.

    If it's impossible, again, return false.

    However if we haven't return false up to this point, then that means we
    haven't fell into any "pitfall" of "false" and we can return true.

*/

/* Time  Beats: 100.00% */
/* Space Beats: 95.76%  */

/* Time  Complexity: O(n) */
/* Space Complexity: O(n) */
class Solution {
public:
    bool flipEquiv(TreeNode* root1, TreeNode* root2)
    {
        if (!root1 && !root2)
            return true;
        else if (!root1 || !root2)
            return false;
        else if (root1->val != root2->val)
            return false;

        bool left_left  = flipEquiv(root1->left, root2->left);
        bool left_right = flipEquiv(root1->left, root2->right);

        if (!left_left && !left_right)
            return false;

        bool right_left  = flipEquiv(root1->right, root2->left);
        bool right_right = flipEquiv(root1->right, root2->right);

        if (!right_left && !right_right)
            return false;

        return true;
    }
};




/*
    ------------
    --- IDEA ---
    ------------

    Another way of implementing, however this one has a different concept.

    Here, we are specifically asking if at any point two trees are the same or
    if they are flippable.

    In the above Solution it's not as excplicit, so choose to your liking.

*/

/* Time  Beats: 100.00% */
/* Space Beats:  65.59% */

/* Time  Complexity: O(n) */
/* Space Complexity: O(n) */
class Solution {
public:
    bool flipEquiv(TreeNode* root1, TreeNode* root2)
    {
        if (!root1 && !root2) return true;
        if (!root1 || !root2) return false;

        if (root1->val != root2->val)
            return false;

        bool same_tree = flipEquiv(root1->left, root2->left) && flipEquiv(root1->right, root2->right);
        if (same_tree)
            return true;

        bool flippable = flipEquiv(root1->left, root2->right) && flipEquiv(root1->right, root2->left);
        if (flippable)
            return true;

        return false;
    }
};
