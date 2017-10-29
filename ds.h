/**
  Convention (for now):
  The abstract data type refers to nodes as integers.
  But the internal data structure has actual node class, and we have a hash map from int to node.
**/
#include <unordered_map>

/**
  Pointer machine abstract class.
  Basically just specifies that we have a node class.
**/
class PM {
    public:
        virtual class Node;
        // returns node corresponding to x
        Node * get_node(int x) { return node_map[x]; }
    protected:
        std::unordered_map<int, Node*> node_map;
};

class DSU : public PM {
    public:
        void add(int x);
        void merge(Node * x, Node * y);
        void merge(int x, int y);
        Node * find(Node * x);
        Node * find(int x);
        bool conn(Node * x, Node * y);
        bool conn(int x, int y);
};

class Splay : public PM {
    public:
        void splay(Node * x);
        void splay(int x);
        void insert(Node * x);
        void insert(int x);
        bool remove(Node * x);
        bool remove(int x);
        Node * find(int x);
};

class ETT : public PM {
    public:
        void add(int x);
        void link(Node * x, Node * y);
        void link(int x, int y);
        bool cut(Node * x, Node * y);
        bool cut(int x, int y);
        bool conn(Node * x, Node * y);
        bool conn(int x, int y);
};

class LCT : public PM {};
class FDC : public PM {};
