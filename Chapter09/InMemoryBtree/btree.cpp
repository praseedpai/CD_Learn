#include <iostream>
#include <iomanip>
#include <ctype.h>
#include <stdio.h>

using namespace std;
//----------------- Order of the B-Tree 
//----------------- Currently fixed at 5
//

#define M 5   

//----- Btree Node key type
typedef int dtype;

//----- B-Tree Library Operational Status 
enum status { InsertNotComplete, Success , DuplicateKey,Underflow, NotFound };

//------------ Declaration of the node

struct node {
     int n; // number of nodes stored in a page
     dtype k[M-1];  // number of the key per node
     node *p[M]; // Pointers to the Child nodes (n+1) in the use 
};

//------------ class Btree

class Btree {
  public:
    //------------- ctor
    Btree() : root(0) {}
    //--------------- Public insertion routine
    void Insert(dtype x );
    //------------- Public Routine to Dump a Btree
    void print( ) const { printf("Contents =>\n"); pr(root,0); };
    //---------------- Public Routine to Delete a Node
    void DelNode(dtype x );
    //------------ Show the Search Path of the B-Tree
    void ShowSearch( dtype x ) const;
     

  private:
    node *root; // pointer to the root node 
    //--------------- insertion routine
    status ins(node *r , dtype x , dtype& y, node *&u ); 
    //--------------- B-Tree Dump Routine
    void pr(const node *r , int nSpace ) const ;
    //----------Search a node wtihin the Btree
    int NodeSearch( dtype x, const dtype *a , int n ) const ;
    //---------- Detele Routine
    status del( node *r , dtype x ); // recursive routine


};

//---------------- Insert a Key into the B-Tree
void Btree::Insert(dtype x ) { 
       printf("insert => %d\n" , x );
       Node *pNew;
       dtype xNew;
       status code = ins(root, x , xNew,pNew );

       if ( code == DuplicateKey ) { printf("Duplicate Key Ignored ..\n"); return; }
        
       if ( code == InsertNotComplete ) {
              node *root0 = root;
              root = new node;
              root->n = 1; root->k[0] = xNew ; 
              root->p[0] = root; root->p[1] = pNew;
              return;
       }
}

//---------------- Public Routine to Delete a Node
void Btree::DelNode(dtype x ) {}
//------------ Show the Search Path of
void Btree::ShowSearch( dtype x ) const
{

}

//-------------------- Private Insertion routine
status Btree::ins(node *r , dtype x , dtype& y, node *&u ) {

          
          
          return InsertNotComplete;
}

//--------------- B-Tree Dump Routine
void Btree::pr(const node *r , int nSpace ) const 
{
             printf("Recursive dump of the Btree\n");
}
//----------Search a node wtihin the Btree
int Btree::NodeSearch( dtype x, const dtype *a , int n ) const 
{
        return -1;
}
//---------- Detele Routine
status Btree::del( node *r , dtype x ) // recursive routine
{

         return Underflow;

}

int main(int argc , char **argv )
{
    Btree t;

    printf("Btree Indexing System.....\n");

}