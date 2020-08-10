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

#ifndef BST_h
#define BST_h

// T must be comparable. That is, must support ordering via <
template <typename T>
class BST {
private:
   struct Node {
      T _data;
      Node* _left, * _right;
      Node(const T& d, Node* l = nullptr, Node* r = nullptr) : _data(d), _left(l), _right(r) {}
   };
   Node* _root;
   size_t _size;

   // Helpers
   static Node* _deep_copy(const Node* p) {
      if (p == nullptr) {
         return nullptr;
      }else {
         Node* temp = new Node(p->_data);
         temp->_left = _deep_copy(p->_left);
         temp->_right = _deep_copy(p->_right);
         return temp;
      }
   }

   bool _insert(Node*& p, const T& elem) {
      if (p == nullptr) {
         p = new Node(elem);
         this->_size++;
         return true;
      }
      else if (p->_data == elem) {
         return false;
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
      else if (p->_data == elem) {
         if (p->_left == nullptr && p->_right == nullptr) {
            delete p;
            p = nullptr;
            _size--;
         }
         else if (p->_left == nullptr) {
            Node* temp = p->_right;
            delete p;
            p = temp;
            _size--;
         }
         else if (p->_right == nullptr) {
            Node* temp = p->_left;
            delete p;
            p = temp;
            _size--;
         }
         else {
            T replacement = _find_min(p->_right)->_data;
            p->_data = replacement;
            _remove(p->_right, replacement);
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

   bool _recursive_delete(Node*& p) {
      if (p == nullptr) {
         return false;
      }
      else {
         _recursive_delete(p->_left);
         _recursive_delete(p->_right);
         delete p;
         p = nullptr;
         _size--;
         return true;
      }
   }
   
   const Node* _find_min(Node* p) const {
      if (p == nullptr) {
         return nullptr;
      }
      else if (p->_left != nullptr) {
         return _find_min(p->_left);
      }
      else {
         return p;
      }
   }

   Node* _find(Node* p, const T& elem) const {
      if (p == nullptr) {
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
         output += parent.str() + " : [null] " + child.str() + "\n";
      }
      else if (p->_right == nullptr) {
         std::stringstream parent;
         parent << p->_data;
         std::stringstream child;
         child << p->_left->_data;
         output += parent.str() + " : " + child.str() + " [null]\n";
      }
      else {
         std::stringstream parent;
         parent << p->_data;
         std::stringstream child_left;
         child_left << p->_left->_data;
         std::stringstream child_right;
         child_right << p->_right->_data;
         output += parent.str() + " : " + child_left.str() + " " + child_right.str() + "\n";
      }
      output += _to_string(p->_left);
      output += _to_string(p->_right);
      return output;
   }

public:

   BST() : _root(nullptr), _size(0) {}
   virtual ~BST() { _recursive_delete(_root); }

   //void set_root(Node* p) {
   //   _root = p;
   //}

   //Node* copy() {
   //   return _deep_copy(_root);
   //}

   virtual size_t get_size() const { return _size; }

   virtual bool insert(const T& elem) { return _insert(_root, elem); }
   virtual bool remove(const T& elem) { return _remove(_root, elem); }
   virtual bool clear() { return _root == nullptr; }

   virtual bool contains(const T& elem) const { return _find(_root, elem) != nullptr; }
   virtual T& find(const T& elem) const { 
      Node* found = _find(_root, elem);
      if (found == nullptr)
         throw Not_found_exception();
      return found->_data;
   }
   virtual string to_string() const {
      std::stringstream ss;
      ss << _root->_data;

      string output = "# Tree rooted at " + ss.str() +"\n";
      output += "# size = " + std::to_string(get_size()) + "\n";
      output += _to_string(_root);
      output += "# End of tree\n";
      return output;
   }

   class Not_found_exception : public exception {
   public:
      string to_string() { return "Not found exception"; }
   };

   friend class Tests; // Don't remove
};

#endif
