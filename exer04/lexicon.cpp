#include <iostream>
#include <string>
using namespace std;

class lexicon {
    public:
      
      lexicon() : root(nullptr), the_size(0) {}
      ~lexicon() { purge(root); }

      void insert(const string &s) {
          if(root == nullptr) {
              root = new node(s, nullptr, nullptr, nullptr);
              ++the_size;
          }
          else if(insert(root,s)) 
            ++the_size;
      }

      int lookup(const string &s) const {
          if(root == nullptr) return 0;
          else return search(root, s) ;
      }

      int depth(const string &s) const {
          int x = 1;
          if(root == nullptr) return 0;
          else return search_depth(root, s, x);
      }
      void replace(const string &s1, const string &s2) {
          if(lookup(s1) == 0) return;
          int k = lookup(s1);
          if(lookup(s2) == 0) {
              pop(s1);
              insert(s2);
              search_node(root,s2)->counter = k;
          }
          else {
              pop(s1);
              search_node(root,s2)->counter += k;
          }
      }

      friend ostream & operator << (ostream &out, const lexicon &l) {
          l.print(l.root);
          return out;
      }

      private:

       struct node {
           string data;
           int counter;
           node *left, *right, *parent;
           node(const string &s, node *l, node *r, node *p) : data(s), left(l), right(r), parent(p), counter(1) {}
           };

        node *root;
        int the_size;

        static void purge(node *t) {
            if(t != nullptr) {
                purge(t->left);
                purge(t->right);
                delete t;
            }
        }
        static bool(insert(node *t, const string &s)) {
            if(s < t->data) {
                if(t->left == nullptr) {
                    t->left = new node(s, nullptr, nullptr, t);
                    return true;
                }
                else return(insert(t->left,s));
            }
            else if(s > t->data) {
                if(t->right == nullptr) {
                    t->right = new node(s, nullptr, nullptr, t);
                    return true;
                }
                else return insert(t->right,s);
            }
            else {
              ++t->counter;
              return false;
            }
        }
        static int search(node *t, const string &s) {
            if(t == nullptr) return 0;
            else if(t->data == s) return t-> counter;
            else if(s < t->data) return search(t->left, s);
            else if(s > t->data) return search(t-> right, s);
            return 0;
        }   

        static int search_depth( node *t, const string &s, int &x) {
            if(t == nullptr) return 0;
            else if(t->data == s) return x;
            else if(s < t->data ) { x++; return search_depth(t->left , s, x); }
            else if(s > t->data) { x++; return search_depth(t->right, s, x); }
            return 0;
        }

        static node * search_node(node *t, const string &s) {
            if(t == nullptr || t->data == s) return t;
            else if(s < t->data) { return search_node(t->left, s);}
            else if(s > t->data) { return search_node(t->right, s); }
            return nullptr;
        }
        static node * down_right(node *t) {
            node *q = t;
            while(q->right != nullptr) q=q->right;
            return q;
        }
        static void print(node *t) {
            if(t!=nullptr) {
                print(t->left);
                cout << t->data;
                cout << " " << t->counter << endl;
                print(t->right);
            }
        }
        static bool is_left_child(node *t) {
            return t->parent->left == t;
        }
        static bool is_right_child(node *t) {
            return t->parent->right == t;
        }
        void pop(const string &s1) {
            if(search_node(root,s1)->left == nullptr && search_node(root,s1)->right == nullptr) {  // 0 children
                node *q = search_node(root,s1);
                if(q == root) { root = nullptr; delete q; return; }
                if(is_left_child(q)) { q->parent->left = nullptr; delete q; return; }
                if(is_right_child(q)) { q->parent->right = nullptr; delete q; return;}
            }
            else if(search_node(root,s1)->left != nullptr && search_node(root,s1)->right == nullptr) { //1 child
                node *q = search_node(root,s1);
                if(q == root) { 
                    root = q->left;
                    q->left->parent = nullptr;
                    delete q;
                    return;
                }
                if(is_left_child(q)) {
                    q->parent->left = q->left;
                    q->left->parent = q->parent;
                    delete q;
                    return;
                }
                if(is_right_child(q)) {
                    q->parent->right = q->left;
                    q->left->parent = q->parent;
                    delete q;
                    return;
                }
            }
            else if(search_node(root,s1)->left == nullptr && search_node(root,s1)->right != nullptr) { //1 child
                node *q = search_node(root,s1);
                if(q == root) {
                    root = q->right;
                    q->right->parent = nullptr;
                    delete q;
                    return;
                }
                if(is_left_child(q)) {
                    q->parent->left = q->right;
                    q->right->parent = q->parent;
                    delete q;
                    return;
                }
                if(is_right_child(q)) {
                    q->parent->right = q->right;
                    q->right->parent = q->parent;
                    delete q;
                    return;
                }
            }
            else { // 2 children
                node *q = search_node(root,s1);
                node *p = down_right(q->left);
                q->data = p->data;
                q->counter = p->counter;
                if(q->left == p) {
                    q->left = p->left;
                    if(p->left!=nullptr) 
                      p->left->parent = q;
                    delete p;
                }
                else {
                    p->parent->right = p->left;
                    if(p->left!=nullptr)
                      p->left->parent = p->parent;
                    delete p;
                }
            }
        }
};