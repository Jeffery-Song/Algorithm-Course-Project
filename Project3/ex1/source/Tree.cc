#include <iostream>
#include <string>
#include <fstream>
#include <chrono>
#define black_s(s) "\033[40;1m" + s + "\033[0m"
#define red_s(s) "\033[41;1m" + s + "\033[0m"
#define print_black(s) system(("echo \"\033[40;1m" + s + "\"\033[0m").c_str())
#define print_red(s) system(("echo \"\033[41;1m" + s + "\"\033[0m").c_str())

enum Color {black = 0, red};
template <typename V>
class RBTree {
private:

  struct Node {
    Node *parent, *left, *right;
    V key;
    unsigned int size;
    Color color;
    Node() {}
    inline Node* Parent() {return parent;}
    inline Node* Left() {return left;}
    inline Node* Right() {return right;}
    inline Node* GrandParent() {
      return parent->parent;
    }
  } *NIL, *root;
  //Node *NIL, *root;
public:
  RBTree() {
    NIL = new Node;
    NIL->parent = NIL->left = NIL->right = NIL;
    NIL->color = black;
    NIL->size = 0;
    root = NIL;
  }
  ~RBTree() {
    Delete_RBTree(root);
    delete NIL;
  }
private:
  void Delete_RBTree(Node *p) {
    if (p == NIL) return;
    Delete_RBTree(p->left);
    Delete_RBTree(p->right);
    delete p;
  }
  inline Node* GrandParent(Node* p) {return p->parent->parent;}
  Node* Uncle(Node* p) {
    //if (GrandParent(p) == NIL) return NIL;
    if (p->parent == GrandParent(p)->left) return GrandParent(p)->right;
    return GrandParent(p)->left;
  }
  Node* Brother(Node* p) {
    //if (p->parent == NIL) return NIL;
    if (p == p->parent->left) return p->parent->right;
    return p->parent->left;
  }
  void Left_Rotate(Node* p) {
    p->right->size = p->size;
    p->size -= p->right->right->size + 1;
    if (p == root) {
      root = p->right;
    } else if (p->parent->left == p) {
      p->parent->left = p->right;
    } else {
      p->parent->right = p->right;
    }
    p->right->parent = p->parent;
    p->parent = p->right;
    p->right = p->right->left;
    p->right->parent = p;
    p->parent->left = p;
  }
  void Right_Rotate(Node* p) {
    p->left->size = p->size;
    p->size -= p->left->left->size + 1;
    if (p == root) {
      root = p->left;
    } else if (p->parent->left == p) {
      p->parent->left = p->left;
    } else {
      p->parent->right = p->left;
    }
    p->left->parent = p->parent;
    p->parent = p->left;
    p->left = p->left->right;
    p->left->parent = p;
    p->parent->right = p;
  }
  void insert_fix(Node* z) {
    while (z->parent->color == red) {
      Node* y = Uncle(z);
      // case 1
      if (y->color == red) {
        z->parent->color = black;
        y->color = black;
        z->parent->parent->color = red;
        z = z->parent->parent;
        continue;
      }
      // case 4
      if (z == z->parent->right && z->parent == GrandParent(z)->left) {
        Left_Rotate(z->parent);
        z = z->left;
      } else if (z == z->parent->left && z->parent == GrandParent(z)->right) {
        Right_Rotate(z->parent);
        z = z->right;
      }
      // case 5
      z->parent->color = black;
      GrandParent(z)->color = red;
      if (z == z->parent->left) {
        Right_Rotate(GrandParent(z));
      } else {
        Left_Rotate(GrandParent(z));
      }
      break;
    }
    root->color = black;
  }
  void print(Node* p, int depth) {
    if (p == NIL) return;
    print(p->right, depth + 1);
    std::string s;
    for (int i = 0; i < depth; i++) {
      s += "\t";
    }
    if (p->color == black) {
      system(("echo \"" + s + std::to_string(p->size) + "," + black_s(std::to_string(p->key)) + "\"").c_str());
    } else {
      system(("echo \"" + s + std::to_string(p->size) + "," + red_s(std::to_string(p->key)) + "\"").c_str());
    }
    print(p->left, depth + 1);
  }
  void preorder(Node* p, std::fstream &f) {
    if (p == NIL) return;
    f << p->key << ", ";
    preorder(p->left, f);
    preorder(p->right, f);
  }
  void inorder(Node* p, std::fstream &f) {
    if (p == NIL) return;
    inorder(p->left, f);
    f << p->key << ", ";
    inorder(p->right, f);
  }
  void postorder(Node* p, std::fstream &f) {
    if (p == NIL) return;
    postorder(p->left, f);
    postorder(p->right, f);
    f << p->key << ", ";
  }
  void transplant(Node* u, Node* v) {
    if (u == root) {
      root = v;
    } else if (u == u->parent->left) {
      u->parent->left = v;
    } else {
      u->parent->right = v;
    }
    v->parent = u->parent;
  }
  void delete_fix_up(Node* x) {
    while (x != root && x->color != black) {
      if (x == x->parent->left) {
        Node* w = x->parent->right;
        if (w->color == red) {
          w->color = black;
          x->parent->color = red;
          Left_Rotate(x->parent);
          w = x->parent->right;
        }
        if (w->left->color == black && w->right->color == black) {
          w->color = red;
          x = x->parent;
        } else {
          if (w->right->color == black) {
            w->left->color == black;
            w->color = red;
            Right_Rotate(w);
            w = x->parent->right;
          }
          w->color = x->parent->color;
          x->parent->color = black;
          w->right->color = black;
          Left_Rotate(x->parent);
          x = root;
        }
      } else {
        Node* w = x->parent->left;
        if (w->color == red) {
          w->color = black;
          x->parent->color = red;
          Right_Rotate(x->parent);
          w = x->parent->left;
        }
        if (w->right->color == black && w->left->color == black) {
          w->color = red;
          x = x->parent;
        } else {
          if (w->left->color == black) {
            w->right->color == black;
            w->color = red;
            Left_Rotate(w);
            w = x->parent->left;
          }
          w->color = x->parent->color;
          x->parent->color = black;
          w->left->color = black;
          Right_Rotate(x->parent);
          x = root;
        }
      }
    }
    x->color = black;
  }
  Node* locate_key(Node* p, const V &key) {
    if (p == NIL) return p;
    if (key == p->key) {
      return p;
    }
    if (key < p->key) {
      return locate_key(p->left, key);
    }
    return locate_key(p->right, key);
  }
  Node* locate_order(Node* p, int i) {
    if (p->left->size == i - 1) {
      return p;
    }
    if (p->left->size > i - 1) {
      return locate_order(p->left, i);
    }
    return locate_order(p->right, i - p->left->size - 1);
  }
  V find_order(Node* p, int i) {
    if (p->left->size == i - 1) {
      return p->key;
    }
    if (p->left->size > i - 1) {
      return find_order(p->left, i);
    }
    return find_order(p->right, i - p->left->size - 1);
  }
public:
  void insert(const V &key) {
    Node* p = new Node;
    p->key = key;
    Node **x, *q;
    q = NIL;
    x = &root;
    while (*x != NIL) {
      q = *x;
      (*x)->size++;
      if ((*x)->key > key) {
        x = &((*x)->left);
      } else {
        x = &((*x)->right);
      }
    }
    *x = p;
    p->parent = q;
    p->left = NIL;
    p->right = NIL;
    p->color = red;
    p->size = 1;
    insert_fix(p);
  }
  void print() {
    print(root, 0);
    system("echo");
  }
  void preorder() {
    std::fstream f;
    f.open("../output/size" + std::to_string(number) + "/preorder.txt", std::ios_base::out);
    preorder(root, f);
    f.close();
  }
  void inorder() {
    std::fstream f;
    f.open("../output/size" + std::to_string(number) + "/inorder.txt", std::ios_base::out);
    inorder(root, f);
    f.close();
  }
  void postorder() {
    std::fstream f;
    f.open("../output/size" + std::to_string(number) + "/postorder.txt", std::ios_base::out);
    postorder(root, f);
    f.close();
  }
  void delete_node(Node* z) {
    if (z == NIL) return;

    Node* y = z;
    Node* x = root;
    while (x != z) {
      x->size--;
      if (x->key < z->key) {
        x = x->right;
      } else {
        x = x->left;
      }
    }
    Color y_orig_color = y->color;
    if (z->left == NIL) {
      x = z->right;
      transplant(z, x);
    } else if (z->right == NIL) {
      x = z->left;
      transplant(z, x);
    } else {
      y = z->right;
      while (y->left != NIL) {y->size--; y = y->left;}
      y_orig_color = y->color;
      x = y->right;
      if (y->parent != z) {
        transplant(y, y->right);
        y->right = z->right;
        y->right->parent = y;
      }
      transplant(z, y);
      y->left = z->left;
      y->left->parent = y;
      y->color = z->color;
      y->size = z->size - 1;
    }
    if (y_orig_color == black) {
      delete_fix_up(x);
    }
  }
  Node* locate_key(const V &key) {
    return locate_key(root, key);
  }
  Node* locate_order(int i) {
    if (i > root->size) return NIL;
    return locate_order(root, i);
  }
  V find_order(int i) {
    if (i > root->size) {
      std::cerr << "size over match\n";
      return 0;
    }
    return find_order(root, i);
  }
};
int main() {
  RBTree<int> T;
  int key;
  std::fstream f, time, delete_data;
  f.open("../input/input.txt", std::ios_base::in);
  time.open("../output/size" + std::to_string(number) +"/time1.txt", std::ios_base::out);
  delete_data.open("../output/size" + std::to_string(number) + "/delete_data.txt", std::ios_base::out);
  std::chrono::system_clock::time_point start = std::chrono::system_clock::now();
  std::chrono::system_clock::time_point s1 = start;
  for (int i = 0; i < number; i++) {
    f >> key;
    T.insert(key);
    if (i % 10 == 9) {
      auto s2 = std::chrono::system_clock::now();
      auto d = std::chrono::duration_cast<std::chrono::nanoseconds>(s2 - s1);
      time << i + 1 << ": " << double(d.count()) * std::chrono::nanoseconds::period::num << std::endl;
      s1 = s2;
    }
  }
  std::chrono::system_clock::time_point end = std::chrono::system_clock::now();
  auto duration = std::chrono::duration_cast<std::chrono::nanoseconds>(end - start);
  time << "total: " << double(duration.count()) * std::chrono::nanoseconds::period::num;
  T.print();
  T.inorder();
  T.preorder();
  T.postorder();
  start = std::chrono::system_clock::now();
  delete_data << "Tree[number / 3] = Tree[" << number << " / 3] = Tree[" << number / 3 << "] = " << T.find_order(number / 3) << std::endl;
  T.delete_node(T.locate_order(number / 3));
  //T.print();
  delete_data << "Tree[number / 4] = Tree[" << number - 1 << " / 4] = Tree[" << (number - 1) / 4 << "] = " << T.find_order((number - 1) / 4) << std::endl;
  T.delete_node(T.locate_order((number - 1) / 4));
  end = std::chrono::system_clock::now();
  duration = std::chrono::duration_cast<std::chrono::nanoseconds>(end - start);
  time.close();
  time.open("../output/size" + std::to_string(number) + "/time2.txt", std::ios_base::out);
  time << "delete time: " << double(duration.count()) * std::chrono::nanoseconds::period::num;
  T.print();
  f.close();
  time.close();
  return 0;
}