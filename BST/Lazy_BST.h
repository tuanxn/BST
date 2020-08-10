// Student ID: 20274909

#include <string>
#include <sstream>
#include <math.h>
#include <vector>
#include <iostream>
#include <iomanip>
#include <list>
#include <iterator>

using namespace std;

#ifndef Lazy_BST_h
#define Lazy_BST_h

// T must be comparable. That is, must support ordering via <
template <typename T>
class Lazy_BST {
protected:
   struct Node {
      T _data;
      Node* _left, * _right;
      bool _is_deleted;

      Node(const T& d) : _data(d), _left(nullptr), _right(nullptr), _is_deleted(false) {}
   };
   Node* _root;
   size_t _size, _real_size;

   // Private helpers
   bool _recursive_delete(Node*& p) {
      if (p == nullptr) {
         return false;
      }
      else {
         _recursive_delete(p->_left);
         _recursive_delete(p->_right);
         if (!p->_is_deleted)
            _real_size--;
         delete p;
         p = nullptr;
         _size--;
         return true;
      }
   }

   bool _insert(Node*& p, const T& elem) {
      if (p == nullptr) {
         p = new Node(elem);
         this->_size++;
         this->_real_size++;
         return true;
      }
      else if (p->_data == elem && !p->_is_deleted) {
         return false;
      }
      else if (p->_data == elem && p->_is_deleted) {
         p->_is_deleted = false;
         this->_size++;
         return true;
      }
      else {
         if (elem < p->_data) {
            return _insert(p->_left, elem);
         }
         else {
            return _insert(p->_right, elem);
         }
      }
   }

   bool _remove(Node*& p, const T& elem) {
      if (p == nullptr) {
         return false;
      }
      else if (p->_data == elem && p->_is_deleted) {
         return false;
      }
      else if (p->_data == elem && !p->_is_deleted) {
         p->_is_deleted = true;
         this->_size--;
         return true;
      }
      else {
         if (elem < p->_data) {
            return _remove(p->_left, elem);
         }
         else {
            return _remove(p->_right, elem);
         }
      }
   }

   bool _collect_garbage(Node*& p) {
      if (p == nullptr) {
         return false;
      }
      bool found;
      found = _collect_garbage(p->_left);
      if (found) {
         _collect_garbage(p->_right);
      }
      else {
         found = _collect_garbage(p->_right);
      }

      if (p->_is_deleted) {
         _really_remove(p, p->_data);
         return true;
      }

      return found;
   }

   const Node* _find_min(const Node* p) const {
      if (p == nullptr) {
         return nullptr;
      }
      else {
         const Node* left_child = _find_min(p->_left);
         if (left_child == nullptr) {
            if (p->_is_deleted) {
               const Node* right_child = _find_min(p->_right);
               if (right_child == nullptr) {
                  return nullptr;
               }
               else {
                  right_child;
               }
            }
            else {
               return p;
            }
         }
         else {
            return left_child;
         }


         //const Node* current = _find_min(p->_left);
         //if (current == nullptr) {
         //   return p;
         //}
         //else if (current->_is_deleted) {
         //   const Node* right = _find_min(current->_right);
         //   if (right == nullptr) {
         //      return p;
         //   }
         //   else if (right->_is_deleted) {
         //      return _find_min(right->_right);
         //   }
         //   else {
         //      return right;
         //   }
         //}
         //else {
         //   return current;
         //}
      }
   }

   const Node* _find_real_min(const Node* p) const {
      if (p == nullptr) {
         return nullptr;
      }
      else if (p->_left != nullptr) {
         return _find_real_min(p->_left);
      }
      else {
         return p;
      }
   }

   const Node* _find(const Node* p, const T& elem) const {
      if (p == nullptr) {
         return nullptr;
      }
      else if (p->_data == elem && p->_is_deleted) {
         return nullptr;
      }
      else if (elem < p->_data) {
         return _find(p->_left, elem);
      }
      else if (elem > p->_data) {
         return _find(p->_right, elem);
      }
      else {
         return p;
      }
   }

   bool _really_remove(Node*& p, const T& elem) {
      if (p == nullptr) {
         return false;
      }
      else if (p->_data == elem) {
         if (p->_left == nullptr && p->_right == nullptr) {
            if (!p->_is_deleted)
               _size--;
            _real_size--;
            delete p;
            p = nullptr;
         }
         else if (p->_left == nullptr) {
            if (!p->_is_deleted)
               _size--;
            _real_size--;
            Node* temp = p->_right;
            delete p;
            p = temp;
         }
         else if (p->_right == nullptr) {
            if (!p->_is_deleted)
               _size--;
            _real_size--;
            Node* temp = p->_left;
            delete p;
            p = temp;
         }
         else {
            //Node* replacement = _find_real_min(p->_right);
            T replacement = _find_real_min(p->_right)->_data;
            p->_data = replacement;
            //p->_is_deleted = replacement->_is_deleted;
            _really_remove(p->_right, replacement);
            p->_is_deleted = false;
         }
         return true;
      }
      else {
         if (elem < p->_data) {
            return _remove(p->_left, elem);
         }
         else {
            return _remove(p->_right, elem);
         }
      }
   }

   string _to_string(const Node* p) const {
      string output = "";
      if (p == nullptr) {
         return "";
      }
      else if (p->_left == nullptr && p->_right == nullptr) {
         return "";
      }
      else if (p->_left == nullptr) {
         std::stringstream parent;
         parent << p->_data;
         std::stringstream child;
         child << p->_right->_data;
         output += parent.str()
            + ((p->_is_deleted) ? "*" : "") + " : [null] " 
            + child.str() + ((p->_right->_is_deleted) ? "*" : "")
            + "\n";
      }
      else if (p->_right == nullptr) {
         std::stringstream parent;
         parent << p->_data;
         std::stringstream child;
         child << p->_left->_data;
         output += parent.str()
            + ((p->_is_deleted) ? "*" : "") + " : " 
            + child.str() + ((p->_left->_is_deleted) ? "*" : "")
            + " [null]\n";
      }
      else {
         std::stringstream parent;
         parent << p->_data;
         std::stringstream child_left;
         child_left << p->_left->_data;
         std::stringstream child_right;
         child_right << p->_right->_data;
         output += parent.str() + ((p->_is_deleted) ? "*" : "")
            + " : " + child_left.str() + ((p->_left->_is_deleted) ? "*" : "")
            + " " + child_right.str() + ((p->_right->_is_deleted) ? "*" : "") 
            + "\n";
      }
      output += _to_string(p->_left);
      output += _to_string(p->_right);
      return output;
   }

public:
   Lazy_BST() : _root(nullptr), _size(0), _real_size(0) {}
   ~Lazy_BST() { _recursive_delete(_root); }

   T get_min() { return _find_min(_root)->_data; }

   size_t get_size() const { return _size; }
   size_t get_real_size() const { return _real_size; }
   bool insert(const T& elem) { return _insert(_root, elem); }
   bool remove(const T& elem) { return _remove(_root, elem); }
   bool collect_garbage() { return _collect_garbage(_root); }
   bool contains(const T& elem) const { return _find(_root, elem) != nullptr; }
   const T& find(const T& elem) const { return _find(_root, elem)->_data; }
   string to_string() const {
      std::stringstream ss;
      ss << _root->_data;

      string output = "# Tree rooted at " + ss.str() + "\n";
      output += "# size = " + std::to_string(get_size()) + "\n";
      output += _to_string(_root);
      output += "# End of tree\n";
      return output;
   }
   bool clear() { return _root == nullptr; }

   class Not_found_exception : public exception {
   public:
      string what() { return "Element not found exception"; }
   };
   friend class Tests; // Don't remove this line
};

#endif