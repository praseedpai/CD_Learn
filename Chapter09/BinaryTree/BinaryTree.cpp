#include <iostream>
#include <bits/stdc++.h>
using namespace std;


//---- A Node Class
 
class Node {
   public:
    int key;
    Node* left;
    Node* right;

    // Val is the key or the value that
    // has to be added to the data part
    Node(int val)
    {
        key = val;
 
        // Left and right child for node
        // will be initialized to null
        left = NULL;
        right = NULL;
    }
    ~Node() { key = -1;} 
};



 

// A utility function to create a new BST node
Node * newNode(int item){
    Node *ret_value = new Node(item);
    if ( ret_value == 0 ) { return 0; }
    return ret_value;
}


//-------------- A Simple Binary Search Tree of Integer

class BinarySearchTree {
      Node *root;
   public:
      BinarySearchTree () { root = 0; }
      // A utility function to do
      // inorder traversal of BST
      void inorder(Node* root);
      Node* insert(Node* node, int key);
      Node* minValueNode(Node* node);
      Node* deleteNode(Node * root, int key);
};



void BinarySearchTree::inorder(Node* root){
        if (root != NULL) {
           inorder(root->left);
           cout << root->key << " ";
           inorder(root->right);
       }
}

// A method to insert a new node with given key in the BST 
//
//
Node* BinarySearchTree::insert(Node* node, int key)
{
    //If the tree is empty, return a new node 
    if (node == NULL) { return newNode(key); }
 
    //--- Otherwise, Descend down the tree
    if (key < node->key)
        node->left = insert(node->left, key);
    else
        node->right = insert(node->right, key);
 
    //----- return the (unchanged) node pointer 
    return node;
}
 
//Given a non-empty binary search tree, return the node
//with minimum key value found in that tree. Note that the
//entire tree does not need to be searched. 
Node* BinarySearchTree::minValueNode(Node* node)
{
    Node* current = node;
 
    //loop down to find the leftmost leaf 
    while (current && current->left != NULL)
        current = current->left;
 
    return current;
}
 
//Given a binary search tree and a key, this function
//deletes the key and returns the new root 
//
Node* BinarySearchTree::deleteNode(Node * root, int key)
{
    // base case
    if (root == NULL) { return root; }
 
    // If the key to be deleted is
    // smaller than the root's
    // key, then it lies in left subtree
    if (key < root->key)
        root->left = deleteNode(root->left, key);
 
    // If the key to be deleted is
    // greater than the root's
    // key, then it lies in right subtree
    else if (key > root->key)
        root->right = deleteNode(root->right, key);
 
    // if key is same as root's key, then This is the node
    // to be deleted
    else {
        // node has no child
        if (root->left==NULL and root->right==NULL)
            return NULL;
       
        // node with only one child or no child
        else if (root->left == NULL) {
            Node* temp = root->right;
            delete root;
            return temp;
        }
        else if (root->right == NULL) {
            Node* temp = root->left;
            delete root;
            return temp;
        }
 
        // node with two children: Get the inorder successor
        // (smallest in the right subtree)
        Node* temp = minValueNode(root->right);
 
        // Copy the inorder successor's content to this node
        root->key = temp->key;
 
        // Delete the inorder successor
        root->right = deleteNode(root->right, temp->key);
    }
    return root;
}
 
// Driver Code
int main()
{
    /* Let us create following BST
            50
        /     \
        30     70
        / \ / \
    20 40 60 80 */
    Node* root = NULL;
    BinarySearchTree t;
    root = t.insert(root, 50);
    root = t.insert(root, 30);
    root = t.insert(root, 20);
    root = t.insert(root, 40);
    root = t.insert(root, 70);
    root = t.insert(root, 60);
    root = t.insert(root, 80);
 
    cout << "Inorder traversal of the given tree \n";
    t.inorder(root);
 
    cout << "\nDelete 20\n";
    root = t.deleteNode(root, 20);
    cout << "Inorder traversal of the modified tree \n";
    t.inorder(root);
 
    cout << "\nDelete 30\n";
    root = t.deleteNode(root, 30);
    cout << "Inorder traversal of the modified tree \n";
    t.inorder(root);
 
    cout << "\nDelete 50\n";
    root = t.deleteNode(root, 50);
    cout << "Inorder traversal of the modified tree \n";
    t.inorder(root);
 
    return 0;
}
 
