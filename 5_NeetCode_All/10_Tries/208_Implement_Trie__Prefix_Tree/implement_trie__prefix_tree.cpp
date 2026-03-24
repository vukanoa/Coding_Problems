/*
    ==============
    === MEDIUM ===
    ==============

    ==================================
    208) Implement Trie (Prefix Tree);
    ==================================

    ============
    Description:
    ============

    A trie (pronounced as "try") or prefix tree is a tree data structure used
    to efficiently store and retrieve keys in a dataset of strings. There are
    various applications od this data structure, such as autocomplete and
    spellchecker.

    Implements the Trie class:
        - "Trie()" Initializes the trie object.

        - "void insert(String word)" Inserts the string "word" into the trie.

        - "boolean search(String word)" Returns true if the string "word" is in
          the trie (i. e., was inserted before), and false otherwise.

        - "boolean startsWith(String prefix)" Returns true if there is a
          previously inserted string "word" that has the prefix "prefix", and
          false otherwise.

    ===============================
    CLASS:
    class Trie{
        Trie()
        {

        }

        void insert(std::string word)
        {

        }

        bool search(std::string word)
        {

        }

        bool startsWith(std::string prefix)
        {

        }
    };
    ===============================

    ==========================================================================
    ================================ EXAMPLES ================================
    ==========================================================================

    --- Example 1 ---
    Input:
    ["Trie", "insert", "search", "search", "startsWith", "insert", "search"]
    [[], ["apple"], ["apple"], ["app"], ["app"], ["app"], ["app"]]
    Output: [null, null, true, false, true, null, true]

    Explanation
    Trie *trie = new Trie();
    trie.insert("apple");
    trie.search("apple");    // return true
    trie.search("app");      // return false
    trie.startsWith("app");  // return true
    trie.insert("app");
    trie.search("app");      // return true

    *** Constraints ***
    1 <= word.length, prefix.length <= 200
    word and prefix consist only of lowercase English letters
    At most 3 * 10^4 in total will be made to insert, search, and startsWith.

*/

#include <string>
using namespace std;

/*
    ------------
    --- IDEA ---
    ------------

    Applications

    Trie (pronounced as "try") or prefix tree is a tree data structure, which
    is used for retrieval of a key in a dataset of strings.

    Some applications are:
        1. Autocomplete
        2. Spell Checker
        3. IP routing (Longest prefix matching)
        4. T9 predictive text
        5. Solving word games

    There are several other data structures, like balanced trees and hash
    tables, which give us the possibility to search for a word in a dataset of
    strings

    So, why---then---do we need trie?

    Although hash table has O(1) time complexity for looking for a key, however
    it is not efficient in the following operations:

        1. Finding all keys with a common prefix.
        2. Enumerating a dataset of strings in lexicographical order.

    Another reason why Trie outperforms hash table, is that as has table
    INCREASES in size, there are lots of HASH COLLISIONS and the search time
    complexity could deteriorate to O(N), where N is the number of keys
    inserted.

    Trie could use less space compared to Hash Table when storing many keys
    with the same prefix.

    In this case using trie has only O(M) time complexity, where "M" is the key
    length. Searching for a key in a balanced tree costs O(M * logM) time
    complexity.


    Trie node structure:
    Trie is a rooted tree. Its nodes have the following fields:

        + Maximum of "R" links to its children(26 in this specific problem),
          where each link corresponds to one of "R" character values from
          dataset alphabet.

        + Boolean field which specifies whether the node corresponds to the end
          of the key, or is just a key prefix.

    Let's say we've inserted a word "leet".

    Root:
    --------------------------------------------------------------
    |   is_end: false                                            |  node
    |   a b c d e f g h i j k l m n o p q r s t u v w x y z      |
    |_________________________#__________________________________|
                              |
                              |
                        ______|
                        |
                        | link
                        |
                        v
    --------------------------------------------------------------
    |   is_end: false                                            |  node
    |   a b c d e f g h i j k l m n o p q r s t u v w x y z      |
    |___________#________________________________________________|
                |
                |________
                        |
                        |
                        |
                        v
    -------------------------------------------------------------
    |   is_end: false                                           |  node
    |   a b c d e f g h i j k l m n o p q r s t u v w x y z     |
    |___________#_______________________________________________|
                |
                |________
                        |
                        |
                        v
     ------------------------------------------------------------
     |  is_end: false                                           |  node
     |  a b c d e f g h i j k l m n o p q r s t u v w x y z     |
     |________________________________________#_________________|
                                              |
                                              |
                        ______________________|
                        |
                        |
                        v
    |------------------------------------------------------------
    |   is_end: true                                            |  node
    |   a b c d e f g h i j k l m n o p q r s t u v w x y z     |
    |___________________________________________________________|




    Two of the most common operations in a trie are insertion of a key and
    search for a key.

    #################
    ### Insertion ###
    #################

    We insert a key by searching into the trie. We start from the root and
    search a link, which corresponds to the first key character. There are two
    cases:
        - A links exists. Then we move down the tree following the link to the
          next child level. The algorithm continues with searching for the next
          key character.

        - A link does not eist. Then we create a new node and link it with the
          parent's link matching the curent character. We repeat this step
          until we encounter the last character of the key, then we mark the
          current node as an end node(i.e. is_end = true) and the algorithm
          finishes.

    Inserting "le" into the Trie:

                            root
                             1
                              \'l'
                               2
                                \'e'
                                 3 (end of key "le")


    Inserting "leet" into the Trie:

                            root
                             1
                              \'l'
                               2
                                \'e'
                                 3 (end of key "le")
                                  \'e'
                                   4
                                    \'t'
                                     5 (end of key "leet")



    Inserting "code" into the Trie:

                            root
                              1
                          'c'/ \'l'
                            6   2
                        'o'/     \'e'
                          7       3 (end of key "le")
                      'd'/         \'e'
                        8           4
                    'e'/             \'t'
                      9 (end "code")  5 (end "leet")


    Inserting "co" into the Trie:

                            root
                              1
                          'c'/ \'l'
                            6   2
                        'o'/     \'e'
     (JUST MARK IS_END)   7       3 (end of key "le")
                      'd'/         \'e'
                        8           4
                    'e'/             \'t'
                      9 (end "code")  5 (end "leet")


    This was built from dataset {"le", "leet", "code"}




    ##############
    ### Search ###
    ##############

        Traverse the above Trie and if at ANY point you CANNOT "jump" to the
        next node, then immediately return false.

        Otherwise, if you've successfully found the entire word inserted in
        the Trie, you MUST(this is VERY important) check if that node has the
        is_end=true set.

        It can happen, as in the above example that we're searching for "cod".

                                root
                                  1
                              'c'/ \'l'
                                6   2
                            'o'/     \'e'
         (end of key "co")    7       3 (end of key "le")
                          'd'/         \'e'
                            8           4
                        'e'/             \'t'
                          9 (end "code")  5 (end "leet")

        Here we DO find "cod", however that node does NOT have is_end=true,
        therefore we'd return FALSE!




    ###########################
    ### Search for a prefix ###
    ###########################

        Here we would indeed find "cod" and we do NOT care whether or not its
        is_end=true because we're just checking the existence of a PREFIX!



    Practice Problems:

        Here are some additional problems to practice the Trie data structure.

    1. Add and Search Word - Data structure design
    2. Word Search II

*/

/* Time  Beats: 73.09% */
/* Space Beats: 54.88% */

/* Time  Complexity: O(N) */
/* Space Complexity: O(T) */ // 'T' <==> total number of created "TrieNode"s
class Trie {
private:
    struct TrieNode {
        TrieNode* letter[26] = {nullptr};
        bool is_end;

        TrieNode()
            : is_end(false)
        {}
    };

    TrieNode* root;

public:
    Trie()
        : root(nullptr)
    {}
    
    void insert(string word)
    {
        if ( ! root)
            root = new TrieNode();

        if (search(word)) // If it already exists, do nothing
            return;

        TrieNode* node = root;
        for (const char& chr : word)
        {
            if ( ! node->letter[chr - 'a'])
                node->letter[chr - 'a'] = new TrieNode();

            node = node->letter[chr - 'a'];
        }

        node->is_end = true;
    }
    
    bool search(string word)
    {
        if ( ! root)
            return false;

        TrieNode* node = root;
        for (const char& chr : word)
        {
            if ( ! node->letter[chr - 'a'])
                return false;

            node = node->letter[chr - 'a'];
        }

        return node->is_end;
    }
    
    bool startsWith(string prefix)
    {
        if ( ! root)
            return false;

        TrieNode* node = root;
        for (const char& chr : prefix)
        {
            if ( ! node->letter[chr - 'a'])
                return false;

            node = node->letter[chr - 'a'];
        }

        return true;
    }
};

/**
 * Your Trie object will be instantiated and called as such:
 * Trie* obj = new Trie();
 * obj->insert(word);
 * bool param_2 = obj->search(word);
 * bool param_3 = obj->startsWith(prefix);
 */
