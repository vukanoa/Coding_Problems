/*
    ==============
    === MEDIUM ===
    ==============

    ==================================
    138) Copy List with Random Pointer
    ==================================

    ============
    Description:
    ============

    A linked list of length 'n' is given such that each node contains an
    additional random pointer, which could point to any node in the list, or
    "null".

    Construct a deep copy of the list. The deep copy should consist of exactly
    'n' brand new nodes, where each new node has its value set to the value of
    its corresponding original node. Both the "next" and "random" pointer of
    the new nodes should point to new nodes in the copied list such that the
    pointers in the original list and copied list represent the same list
    state.

    NONE OF THE POINTERS IN THE NEW LIST SHOULD POINT TO NODES IN THE ORIGINAL
    LIST.

    For example, if there are two nodes 'X' and 'Y' in the original list, where
        X.random --> Y
    then for the corresponding two nodes 'x' and 'y' in the copied list
        x.random --> y

    (Notice that the other one is lowercase)

    Return the head of the copied linked list.

    The linked list is represented in the input/output as a list of 'n' nodes.
    Each node is represented as a pair of [val, random_index] where:
        1. "val" an integer representing Node.val
        2. "random_index": the index of the node (range from 0 to n-1) that
           the "random" pointer points to, or "null" if it does not point to
           any node.

    Your code will ONLY be given the "head" of the original list.

    ===========================================
    FUNCTION: Node* copyRandomList(Node* head);
    ===========================================

    ==========================================================================
    ================================ EXAMPLES ================================
    ==========================================================================

    --- Example 1 ---
    Input:  head = [[7, null], [13, 0], [11, 4], [10, 2], [1, 0]]
    Output: [[7, null], [13, 0], [11, 4], [10, 2], [1, 0]]

    --- Example 2 ---
    Input:  head = [[1, 1], [2, 1]]
    Output: [[1, 1], [2, 1]]

    --- Example 3 ---
    Input:  head = [[3, null], [3, 0], [3, null]]
    Output: [[3, null], [3, 0], [3, null]]

    *** Constraints ***
    0 <= n <= 1000
    -10^4 <= Node.val <= 10^4
    Node.random is null or is pointing to some node in the linked list

*/

#include <unordered_map>
using namespace std;

class Node {
public:
    int val;
    Node* next;
    Node* random;

    Node(int _val)
    {
        val = _val;
        next = nullptr;
        random = nullptr;
    }
};

/*
    ------------
    --- IDEA ---
    ------------

    Make a:
        Hashmap<Node*, Node*>

    where the original node will be mapped "1 to 1" to a copied node.

    Thus, we won't have issues if we have, say, nodes with same values or
    something like that.

    Example:
    head = [[7, null], [13, 0], [11, 4], [10, 2], [1, 0]]

    The below display of Hashmap nodes in Keys and Values is in the form:
        [value, random, next]

    Note: "random" and "next" nodes won't be represented with their respective
    values, but rather with an index of the list. Thus, for example:
        Index 0: Node(7, null, 1)
        Index 3: Node(10)

    This is done in two passes:
        1. Make a copy node out of the original node and insert in Hashmap,
           alongside its original:

           (Originals)       (Copies)
               Key        |    Value
            [7,  null, 1]    [7,  null, null]
            [13,  0,   2]    [13, null, null]
            [11,  4,   3]    [11, null, null]
            [10,  2,   4]    [10, null, null]
            [1,   0,   5]    [1,  null, null]


        2. Go through the original linked list and for each's corresponding
           copy node set copy's "next" and "random" pointers to copied
           correspondings of the "next" and "random" nodes of the original
           linked list(from our Hash Map).

           (Originals)       (Copies)
               Key        |    Value
            [7,  null, 1]   [7,  null, 1]
            [13,  0,   2]   [13,  0,   2]
            [11,  4,   3]   [11,  4,   3]
            [10,  2,   4]   [10,  2,   4]
            [1,   0,   5]   [1,   0,   5]

    Return the corresponding copy of the Original List's head, from our
    Hashmap.
*/

/* Time  Beats: 91.88% */
/* Space Beats: 69.95% */

/* Time  Complexity: O(N) */
/* Space Complexity: O(N) */
class Solution_Two_Passes {
public:
    Node* copyRandomList(Node* head)
    {
        if (head == nullptr)
            return nullptr;

        unordered_map<Node*, Node*> orig_to_copy;
        orig_to_copy.insert( {nullptr, nullptr} );

        Node* orig = head;

        while (orig)
        {
            Node* copy = new Node(orig->val);
            orig_to_copy.insert( {orig, copy} );

            // Move forward
            orig = orig->next;
        }

        orig = head;
        while (orig)
        {
            Node* copy = orig_to_copy[orig];

            copy->next   = orig_to_copy[orig->next];
            copy->random = orig_to_copy[orig->random];

            // Move forward
            orig = orig->next;
        }

        return orig_to_copy[head];
    }
};




/*
    ------------
    --- IDEA ---
    ------------

    This one has the same IDEA as above, however this is done in ONE-Pass as
    opposed to Two-Passes.

    It's a bit difficult to read, but go slowly, take your time and I'm sure
    you'll understand it.

    It's not that bad.

*/

/* Time  Beats: 100.00% */
/* Space Beats:  69.65% */

/* Time  Complexity: O(N) */ // One-Pass
/* Space Complexity: O(N) */
class Solution_One_Pass {
public:
    Node* copyRandomList(Node* head)
    {
        if (head == nullptr)
            return nullptr;

        unordered_map<Node*, Node*> orig_to_copy;
        orig_to_copy.insert( {nullptr, nullptr} );

        Node* orig = head;

        while (orig)
        {
            // Fill "val"
            if (orig_to_copy.find(orig) == orig_to_copy.end())
            {
                Node* empty_node = new Node(0);
                orig_to_copy.insert( {orig, empty_node} );
            }
            orig_to_copy[orig]->val = orig->val;

            // Fill "next" pointer
            if (orig_to_copy.find(orig->next) == orig_to_copy.end())
            {
                Node* empty_node = new Node(0);
                orig_to_copy.insert( {orig->next, empty_node} );
            }
            orig_to_copy[orig]->next = orig_to_copy[orig->next];

            // Fill "random" pointer
            if (orig_to_copy.find(orig->random) == orig_to_copy.end())
            {
                Node* empty_node = new Node(0);
                orig_to_copy.insert( {orig->random, empty_node} );
            }
            orig_to_copy[orig]->random = orig_to_copy[orig->random];

            // Move forward
            orig = orig->next;
        }

        return orig_to_copy[head];
    }
};




/*
    ------------
    --- IDEA ---
    ------------

    Example:

        // Original Linked-List 
        2 --> 7 --> 8 --> 3 --> 5


    Instead of using a Hash Map, we can create a new, copy, linked list and 
    interleave it with the original list.

        2 --> 2 --> 7 --> 7 --> 8 --> 8 --> 3  --> 3 --> 5 --> 5
              C           C           C            C           C
              ^           ^           ^            ^           ^
              |           |           |            |           |
              |___________|___________|____________|___________|
                                      |
                                    Copy nodes
              
    Then we link "random" pointers of this copy Linked-List by doing:

        copy         = orig->next;
        copy->random = orig->random->next;


    Then we link "next" pointers of this copy Linked-List, which makes both the
    original and copy Linked-List as they ought to be. The original list is
    restored, whereas the copy list is as its required of us.

        copy       = orig->next;
        orig->next = copy->next;

        if (copy->next)
            copy->next = copy->next->next;

*/

/* Time  Beats: 92.74% */
/* Space Beats: 95.80% */

/* Time  Complexity: O(N) */
/* Space Complexity: O(1) */ // New Linked-List is not considered "Extra" space
class Solution_Space_Optimized {
public:
    Node* copyRandomList(Node* head)
    {
        if (head == nullptr)
            return nullptr;

        Node* orig = head;
        while (orig)
        {
            // Create copy node
            Node* copy = new Node(orig->val);

            // Insert copy node into the original list
            copy->next = orig->next;
            orig->next = copy;

            // Move forward
            orig = copy->next;
        }

        Node* new_head = head->next;

        orig = head;
        while (orig)
        {
            // Link "random" pointers of copy nodes
            if (orig->random)
                orig->next->random = orig->random->next;

            // Move forward
            orig = orig->next->next;
        }

        orig = head;
        while (orig)
        {
            // Get the copy node
            Node* copy = orig->next;

            // Restore original list by re-linking "next" pointers of orig node
            orig->next = copy->next;

            // Link "next" pointers of copy nodes
            if (copy->next)
                copy->next = copy->next->next;

            // Move forward
            orig = orig->next;
        }

        return new_head;
    }
};




/*
    ------------
    --- IDEA ---
    ------------

    Similar idea to the above "Space Optimized I", however instead of
    interleaving copy-nodes with the original list, we can do something
    similar, but better.

    We use original nodes' "random" pointers to point at new copy nodes and
    copy nodes point to original "random" nodes.

    Then we can simply link "random" pointers of copy-nodes.

    Once we've done that, we restore the original Linked-List and we link
    "next" pointers of copy nodes.

*/

/* Time  Beats: 91.90% */
/* Space Beats: 69.71% */

/* Time  Complexity: O(N) */
/* Space Complexity: O(1) */ // New Linked-List is not considered "Extra" space
class Solution_Space_Optimized_II {
public:
    Node* copyRandomList(Node* head)
    {
        if ( ! head)
            return nullptr;

        Node* orig = head;
        while (orig)
        {
            Node* copy = new Node(orig->val);

            copy->next = orig->random; // Make copy point to orig's random node
            orig->random = copy;       // Make orig->random be copy

            // Move forward
            orig = orig->next;
        }

        Node* new_head = head->random;

        orig = head;
        while (orig)
        {
            Node* copy = orig->random;

            // Link "random" pointer of copy-nodes
            copy->random = (copy->next) ? copy->next->random : nullptr;

            // Move forward
            orig = orig->next;
        }

        orig = head;
        while (orig)
        {
            Node* copy = orig->random;

            // Restore orig Linked_list & Link "next" pointers of copy nodes
            orig->random = copy->next;
            copy->next = (orig->next) ? orig->next->random : nullptr;

            // Move forward
            orig = orig->next;
        }

        return new_head;
    }
};




/* This doesn't pass LeetCode tests since it modifies the original list */
/* However, it's a genius idea in my opinion */

/*
    ------------
    --- IDEA ---
    ------------

    ********************
    *** Solution_DNA ***
    ********************

    Why am I calling it "DNA"? It is reminiscent of DNA replication. At least
    it reminds me of it.

    How does this work?

    Again, we have 2 passes:
        1. First we have to remember the Original List's next since we're
           going to modify it.

           Now make a copy of the current Original List's node and set
           Original List's next pointer to point to this, just created, copy.

           We're going to link copy nodes within the first pass with a use
           of "prev" pointer which, at the beginning, points to "nullptr"
           and it always gets set to newly created copy.
           After the first iteration "prev" isn't a "nullptr", thus it's "next"
           pointer gets set to the current copy.
           That way we link the whole copied list.

           So, we have started the loop with this(Example):
           (right arrows represent "next" pointer, while the ones that go
           up and down, in this drawing, represent "random" pointers)

    Original List: (Before the while loop)

      head -----
               |
  --------------
  |
  |
  |
  |   ----------------------------
  |   |                          |
  |   v                          |
  |   ---------------------------|--------
  |   |             -------      |       |
  |   |             v     |      |       v
  |-> 7 ==> 13 ==> 11 ==> 10 ==> 1 ==> nullptr
      ^      |      |            ^
      |      |      |            |
      -------       --------------


  Original List: (Before the while loop)

        head -----
                 |
        ----------
        |
        v
     -->7     -->13     -->11     -->10     -->1               (Original List)
     |  |     |   |     |   |     |   |     |  |
     |  v     |   v     |   v     |   v     |  v
     ---7 ==> ---13 ==> ---11 ==> ---10 ==> ---1 ==> nullptr    (Copied List)

// From up   (Original List) downards is the "next" pointer of Original List
// From down (Copied   List) upwards is the "random" pointer of the Copied List


        2. Iterate through this Copied List and make:
           curr_copy->random (instead of now pointing at its Original
           List's corresponding node), make it now point to:

           curr_copy->random->random->next;

           Let's unpack this:
           curr_copy->random points to its Original List corresponding
           node:
               meaning Copied Node(7)'s random is pointing to Original
               Node(7)

          Now let's see the next pointer:
          curr_copy->random->random
          ~~~~~~~~~~~~~~~~~
                ^
                |
                |
   Original List's corresponding node of the Copied Node


          Now when we are on that node(Original List's corresponding
          node), now take ITS random pointer.
          Its random pointer points to the random node in the Original
          List.

          So can we use this?
          Well, remember that we have modified Original List's "next"
          pointers?
          They are pointing to its Copied corresponding nodes.

          Thus:
          curr_copy->random->random->next

          will give us the appropriate Random Node but from out Copied
          List.

          We do that for every curr_copy in the list and we're done.

          Now just return the:
              head->next

          Since head is pointing to the head of the Original List, and we have
          left Original List modified in terms of its "next" pointers, that
          means that head->next is pointing to the head of our copied list
          which we're asked to return.

*/

/*    Time  Complexity: O(n) */
/*
    Space Complexity: O(1)
    Technically it's still O(n) since we need the space for new 'n' nodes.
    However, we don't need to use anything other than that, so it could, maybe,
    be considered O(1) since I'm not using anything additional that I
    absolutely must.

    Also there is a downside to this solution:
        It leaves the Original List Modified.
*/
class Solution_DNA {
public:
    Node* copyRandomList(Node* head)
    {
        Node* curr_orig = head;
        Node* next_orig = nullptr;
        Node* prev_copy = nullptr;

        while (curr_orig)
        {
            next_orig = curr_orig->next;

            Node* curr_copy = new Node(curr_orig->val);
            curr_orig->next = curr_copy;

            // Update Copy's next
            if (prev_copy != nullptr)
                prev_copy->next = curr_copy;

            // Update Copy's random
            curr_copy->random = curr_orig;

            prev_copy = curr_copy;
            curr_orig = next_orig;
        }

        // Since we have just adjusted it to point like this
        Node* curr_copy = head->next;

        // Assign Copied Nodes to "random" pointers.
        while (curr_copy)
        {
            if (curr_copy->random->random != nullptr)
                curr_copy->random = curr_copy->random->random->next;
            else
                curr_copy->random = nullptr;

            // Move forward
            curr_copy = curr_copy->next;
        }

        return head->next;
    }
};
