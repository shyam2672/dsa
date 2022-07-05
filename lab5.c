//NAME: SHYAM PRAJAPATI
//ENTRY NUMBER: 2020CSB1110
//LAB ASSIGNMENT 5


#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
// A Btree node
struct btnode
{
    int *keys;             // an array of keys
    int t;                 // minimum degree
    struct btnode **child; // an array of pointers to child of the node
    int n;                 // number of keys in the node at present
    bool leaf;             //true when the node is leaf else false.
};
//FUNCTION TO INORDER TRAVERSE ALL NODES OF THE TREE/SUBTREE ROOTED WITH THE GIVEN NODE 
void inordertraverse(struct btnode* root){
    //There are n keys and n+1 children, traverse through n keys and first n children
   int i=0;
   for(i=0;i < root->n;i++){
       // If this NODE is not leaf, then before printing keys[i], traverse the subtree rooted with child Child[i].
       if(root->leaf==false)
       inordertraverse(root->child[i]);
       printf(" %d",root->keys[i]);
   }
   //subtree rooted with last child
   if(root->leaf==false)
   inordertraverse(root->child[i]);
}
//function to generate a btree node
struct btnode *generatenode(int t1, bool leaf1)
{
    struct btnode *btreenode = malloc(sizeof(struct btnode));
    //copying given minimum and leaf property to generated node
    btreenode->t = t1;
    btreenode->leaf = leaf1;
    //allocating memory for child and keys array
    btreenode->keys = malloc((2 * btreenode->t - 1) * sizeof(int));
    btreenode->child = malloc((2 * btreenode->t) * sizeof(struct btnode *));
    //initialising total number of keys present to 0
    btreenode->n = 0;
    return btreenode;
}
//function to split a child  y of given node into two and moving middle element of y to the node
struct btnode *splitchild(struct btnode *root, int i, struct btnode *y)
{   //z is the node which is going to store last t-1 elements of y
    struct btnode *z = generatenode(y->t, y->leaf);
    //initialising total elements in z to t-1
    z->n = y->t - 1;
    //copying last t-1 elements of y to z
    for (int j = 0; j < y->t - 1; j++)
        z->keys[j] = y->keys[j + y->t];
        //copying last t children of y to z 
    if (y->leaf == false)
    {
        for (int j = 0; j < y->t; j++)
            z->child[j] = y->child[j + y->t];
    }
   
   //creating space for z child in the root 
     for (int j = root->n; j >= i+1; j--)
        root->child[j+1] = root->child[j];
        //linking z to root
        root->child[i+1]=z;
        //moving elements of root so that middle element of y can be stored at appropriate position
        for (int j = root->n-1; j >= i; j--)
        root->keys[j+1] = root->keys[j];
        //moving middle element of y to root
        root->keys[i]=y->keys[y->t-1];
        //increasing total number of element by 1
        root->n=root->n+1;
        //decreasing number of keys to t-1 for node y
        y->n=y->t-1;
        return root;

 
}
// A utility function to insert a new key in this node(root). The assumption is, the node must be non-full when this
// function is called
void insertnonfull(struct btnode **root, int k)
{ struct btnode* temp=*root;
// Initialize index as index of rightmost element in the node 
    int i = temp->n - 1;
    //if the node is leaf
    if (temp->leaf == true)
    {   //finds the location of new key and moves all greater keys 1 place ahead
        while (i >= 0 && temp->keys[i] > k)
        {
            temp->keys[i + 1] = temp->keys[i];
            i--;
        }
        //  // Insert the new key at found location
        temp->keys[i + 1] = k;
        //increase count of total elements by 1
        temp->n = temp->n + 1;
        
    }
    
    // If this node is not leaf
    else
    {// Find the child which is going to have the new key
        while (i >= 0 && temp->keys[i] > k)
            i--;
            //  if the found child is full
        if (temp->child[i + 1]->n == 2 * temp->t - 1)
        {   //if full then spit it
            temp = splitchild(temp, i + 1, temp->child[i + 1]);
            // After split, the middle key of child[i] goes up and child[i] is splitted into two.  See which of the two
            // is going to have the new key
            if (temp->child[i + 1]->keys[i + 1] < k)
                i++;
        }
        //calling recursively
         insertnonfull(&temp->child[i + 1], k);
        
    }
}
//the main function to insert a new key in btree
struct btnode *insert(struct btnode *root, int k, int t)
{
    struct btnode *temp = root;
    //if root is NULL
    if (temp == NULL)
    {
        temp = generatenode(t, true);
        temp->keys[0] = k;
        temp->n = 1;
        root=temp;
        return root;
    }
    
    else
    {//if root is full grow tree upwards
        if (temp->n == 2 * t - 1)
        {   //allocating memory for new root
            struct btnode *s = generatenode(t, false);
            s->child[0] = temp;//make old root as child of new root
            s = splitchild(s, 0, temp);//split old root and move its middle key to new root
            int i = 0;//new root has two child now find which child will have key
            if (s->keys[0] < k)
                i++;
             insertnonfull(&s->child[i], k);
             //change root
            root = s;
            return root;
        }
        else//if root is not full
         insertnonfull(&temp, k);
        return root;
    }
}
//function to search a element  in btree
void search(struct btnode* root,int k){
    int i=0;//find first key greater than k in the root
    while(i<root->n && k>root->keys[i])
    i++;
    //if k is present in root return
    if(root->keys[i]==k){
    printf("element is present\n");
    return;
    }

//if root is leaf an dkey is absent return 
    if(root->leaf==true)
    {
        printf("element not present\n");
        return ;
    }
    // search key in appropriate child
    search(root->child[i],k);
}
//function to find minimum element in a btree
void findmin(struct btnode* root){
    //if root is leaf then first key is the minimum
    if(root->leaf==true)
    {
        printf("%d",root->keys[0]);
        return;
    }
    //recursively calling the function for left most child
    findmin(root->child[0]);
}
int main()
{
    int t;
    char s;
    printf("enter the minimum degree\n");
   
    scanf("%d", &t);
     printf("enter either A or B\n");
     scanf(" %c",&s);
     struct btnode *root=NULL;
if(s=='A'){
      for (int i = 100; i > 0; i--)
          {
              root = insert(root, i, t);
          }
          printf("inorder traversal is: ");
          inordertraverse(root);
          printf("\n");
          printf("enter an element to search \n");
          int element;
          scanf(" %d",&element);
          search(root,element);
}
else if(s=='B'){
    while(1){
    printf("options: I for insertion, S for search, M for finding minimum, T for traversing the B-tree, E for exit: ");
    char f;
    scanf(" %c",&f);
    if(f=='I'){
        printf("enter the number of elements you want to insert");
        int num;
        scanf(" %d",&num);
        printf("enter %d elemts to insert\n",num);
        for(int i=0;i<num;i++){
            int e;
            scanf(" %d",&e);
            root=insert(root,e,t);
        }
    }
        if(f=='T'){
            printf("inorder traversal is: ");
            inordertraverse(root);
            printf("\n");
        }
        if(f=='S'){
            printf("enter element to search\n");
            int el;
            scanf(" %d",&el);
            search(root,el);
        }
          if(f=='M'){
          findmin(root);
          printf("\n");
      }
        if(f=='E'){
            return 0;
        }
    
    }
    }

return 0;
}
