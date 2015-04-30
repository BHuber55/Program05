#if !defined (NULL)
#define NULL 0
#endif

#if !defined (AVLTREE_H)
#define AVLTREE_H

#include "Drawable.h"
#include "AVLTreeIterator.h"
#include "Line.h"

#include "Text.h"
using CSC2110::String;

#include <iostream>
using namespace std;

template < class T >
class AVLTree : public Drawable
{
   
   private:
      AVLTreeNode<T>* root;

      bool avlFlag;
      int sze;

	  //stuff for new constructor
	  bool min_max;
	  bool allow_duplicates;
	  bool duplicates_on_left

      int (*compare_items) (T* item_1, T* item_2);
      int (*compare_keys) (String* key, T* item);

      void setRootNode(AVLTreeNode<T>* tNode);
      AVLTreeNode<T>* getRootNode();
      int getHeight(AVLTreeNode<T>* tNode);
      int isBalanced(AVLTreeNode<T>* tNode);

      void destroyItem(AVLTreeNode<T>* tNode);
      void destroy();

      AVLTreeNode<T>* insertItem(AVLTreeNode<T>* tNode, T* item);
      AVLTreeNode<T>* removeItem(AVLTreeNode<T>* tNode, String* searchKey);
      AVLTreeNode<T>* removeNode(AVLTreeNode<T>* tNode);

      AVLTreeNode<T>* removeLeftMost(AVLTreeNode<T>* tNode);		//<<<<=======	new stuff.
      T* findLeftMost(AVLTreeNode<T>* tNode);						//<<<<=======
	  AVLTreeNode<T>* removeRightMost(AVLTreeNode<T>* tNode);		//<<<<=======
	  T* findRightMost(AVLTreeNode<T>* tNode);						//<<<<=======


      AVLTreeNode<T>* rotateLeft(AVLTreeNode<T>* tNode);
      AVLTreeNode<T>* rotateRight(AVLTreeNode<T>* tNode);
      AVLTreeNode<T>* DLR(AVLTreeNode<T>* tNode);
      AVLTreeNode<T>* DRL(AVLTreeNode<T>* tNode);

      AVLTreeNode<T>* avlFixAddLeft(AVLTreeNode<T>* tNode);
      AVLTreeNode<T>* avlFixAddRight(AVLTreeNode<T>* tNode);
      AVLTreeNode<T>* avlFixRemoveLeft(AVLTreeNode<T>* tNode);
      AVLTreeNode<T>* avlFixRemoveRight(AVLTreeNode<T>* tNode);
      AVLTreeNode<T>* DLR(AVLTreeNode<T>* tNode, AVLTreeNode<T>* left);  //changes balance factors, calls the other DLR to do two rotations
      AVLTreeNode<T>* DRL(AVLTreeNode<T>* tNode, AVLTreeNode<T>* right);  //changes balance factors, calls the other DRL to do two rotations

      virtual void drawRec(AVLTreeNode<T>* tNode, Cairo::RefPtr<Cairo::Context> cr, Line* line, int x_parent, int x_curr, int y_curr);

   public:
	  //OG constructor
      AVLTree(int (*comp_items) (T* item_1, T* item_2), int (*comp_keys) (String* key, T* item));
      ~AVLTree();

	  //new constructor
	  AVLTree(bool min_max, bool allow_duplicates, bool duplicates_on_left, int(*comp_items) (T* item_1, T* item_2), int(*comp_keys) (String* key, T* item));

      int size();
      void insert(T* item);
      void remove(String* sk);
      T* retrieve(String* sk);

	  //The function we were suppose to add. suppose to remove the smalleset or largest itme in the tree
	  //based on user passed from constructor
	  T* remove();

      bool isEmpty();
      void makeEmpty();
      T* getRootItem();
      AVLTreeIterator<T>* iterator();

      int getHeight();
      bool isBalanced();

      void draw(Cairo::RefPtr<Cairo::Context> cr, int width, int height);
      void mouseClicked(int x, int y);

};

template < class T >
AVLTree<T>::AVLTree(int (*comp_items) (T* item_1, T* item_2), int (*comp_keys) (String* key, T* item))
{
   root = NULL;
   sze = 0;
   compare_items = comp_items;
   compare_keys = comp_keys;
}

template < class T >
AVLTree<T>::~AVLTree()
{
   destroy();
}

/* NOTES!!!

	If min = go right, allow duplicates on right = true, on left = false
	if max = go left, 

	probz gonna need a leftmost rightmost function.
			maybe have these? ^^^^
			findleftmost
			removeleftmost
		probably dont have findrightmost or removerightmost. gotta write those //copy paste & change left to right
	ALWAYS CHECK FOR ROTATIONS AND WHAT NOT.

	remove:
		if min go left, then check for right children, check for balances and the usual.


	insert:
		duplicates and what not.
					
*/



//NEW STUFF!!!!!!!!!
//other constructor
template < class T > 
AVLTree<T>::AVLTree(bool min_max, bool allow_duplicates, bool duplicates_on_left, int(*comp_items) (T* item_1, T* item_2), int(*comp_keys) (String* key, T* item))
{
	root = NULL;
	sze = 0;
	compare_items = comp_items;
	compare_keys = comp_keys;

	min_or_max = min_max;
	allow_duplicates = allow_duplicates;
	dupplicates_on_left = duplicates_on_left;
}

template < class T >
T* AVLTree<T>::remove()
{
	T* item;

	if (min_or_max)
	{
		item = findLeftMost(root);
		root = removeLeftMost(root);

	}
	else
	{
		item = findRightMost(root);
		root = removeRightMost(root);
	}
	sze--;

	return item;
}

template < class T >
T* AVLTree<T>::findRightMost(AVLTreeNode<T>* tNode)
{
	while (tNode->getRight() != NULL)
	{
		tNode = tNode->getRight();
	}
	
	return tNode->getItem();
}

template < class T >
AVLTreeNode<T>* AVLTree<T>::removeRightMost(AVLTreeNode<T>* tNode)
{
	AVLTreeNode<T>* subtree;

	if (tNode->getRight() == NULL)
	{
		avlFlag = true;
		subtree = tNode->getLeft();
		delete tNode;
		return subtree;
	}
	else
	{
		subtree = removeRightMost(tNode->getRight());
		tNode->setRight(subtree);
		if (avlFlag)
		{
			tNode = avlFixRemoveRight(tNode);  //came from right
		}
		return tNode;
	}
}



//OLD STUFFF!!!!!!!!!!!!

template < class T >
void AVLTree<T>::destroy()
{
   destroyItem(root);
}

template < class T >
void AVLTree<T>::destroyItem(AVLTreeNode<T>* tNode)
{
   if (tNode != NULL)
   {
      destroyItem(tNode->getLeft());
      destroyItem(tNode->getRight());
      delete tNode;
   }
}

template < class T >
bool AVLTree<T>::isEmpty()
{
   return (sze == 0);
}

template < class T >
int AVLTree<T>::size()
{
   return sze;
}

template < class T >
void AVLTree<T>::makeEmpty()
{
   destroy();
   root == NULL;
   sze = 0;
}

template < class T >
AVLTreeNode<T>* AVLTree<T>::getRootNode()
{
   return root;
}

template < class T >
void AVLTree<T>::setRootNode(AVLTreeNode<T>* tNode)
{  
   root = tNode;
}

template < class T >
T* AVLTree<T>::getRootItem()
{
   T* root_item = root->getItem();
   return root_item;
}

template < class T >
AVLTreeIterator<T>* AVLTree<T>::iterator()
{
   return new AVLTreeIterator<T>(root);
}

template < class T >
T* AVLTree<T>::retrieve(String* sk)
{
   AVLTreeNode<T>* tNode = getRootNode();

   while (tNode != NULL)
   {
      T* node_item = tNode->getItem();
      int comp = (*compare_keys) (sk, node_item);
      if (comp == 0)
      {
         return node_item;
      }
      else if (comp < 0)
      {
         tNode = tNode->getLeft();
      }
      else
      {
         tNode = tNode->getRight();
      }
   }

   return NULL; //item is not in the tree
} 

template < class T >
void AVLTree<T>::insert(T* item)
{
   root = insertItem(root, item);
   avlFlag = false;
} 

template < class T >
AVLTreeNode<T>* AVLTree<T>::insertItem(AVLTreeNode<T>* tNode, T* item) 
{
	if (tNode == NULL) 
	{
		tNode = new AVLTreeNode<T>(item);
		tNode->setBalanceFactor(BALANCED);	
		avlFlag = true; //need to check
		sze++;
		return tNode;
	} 

	AVLTreeNode<T>* subtree;
	AVLTreeNode<T>* left = tNode->getLeft();
	AVLTreeNode<T>* right = tNode->getRight();
	T* node_item = tNode->getItem();
	int comp = (*compare_items) (item, node_item);

	if (comp == 0)
	{
		if (allow_duplicates)
		{
			if (duplicates_on_left)
			{
				subtree = insertItem(left, item);
				tNode->setLeft(subtree);

				if (avlFlag)  //still need to check
				{
					tNode = avlFixAddLeft(tNode);  //came from the left
				}
			}
			else
			{
				subtree = insertItem(right, item);
				tNode->setRight(subtree);

				if (avlFlag)
				{
					tNode = avlFixAddRight(tNode);  //came from the right
				}
			}
		}
		else
		{
			//no duplicate search keys allowed, so do nothing
			return tNode;
		}
   }
   else if (comp < 0) 
   {
      subtree = insertItem(tNode->getLeft(), item);
      tNode->setLeft(subtree);

      //check balance factor and rotate if necessary
      if (avlFlag)  //still need to check
      {
         tNode = avlFixAddLeft(tNode);  //came from the left
      }
   }
   else 
   { 
      subtree = insertItem(tNode->getRight(), item);
      tNode->setRight(subtree);

      //check balance factor and rotate if necessary
      if (avlFlag)
      {
         tNode = avlFixAddRight(tNode);  //came from the right
      }
   } 
   return tNode;
} 

template < class T >
void AVLTree<T>::remove(String* sk)
{
   root = removeItem(root, sk);
   avlFlag = false;
}

template < class T >
AVLTreeNode<T>* AVLTree<T>::removeItem(AVLTreeNode<T>* tNode, String* sk) 
{
   AVLTreeNode<T>* subtree;
   if (tNode == NULL) 
   {
      return tNode;  //item not present, take no action
   }

   T* node_item = tNode->getItem();
   int comp = (*compare_keys) (sk, node_item);

   if (comp == 0) 
   {
      //item is in the root of some subtree
      //found something to remove so set avlFlag to true
      avlFlag = true;
      tNode = removeNode(tNode);  // delete the item
      sze--;
   }
   else if (comp < 0) 
   {
      subtree = removeItem(tNode->getLeft(), sk);
      tNode->setLeft(subtree);
      if (avlFlag)
      {
         tNode = avlFixRemoveLeft(tNode);  //came from left
      }
   }
   else 
   { 
      subtree = removeItem(tNode->getRight(), sk);
      tNode->setRight(subtree);
      if (avlFlag)
      {
         tNode = avlFixRemoveRight(tNode);  //came from right
      }
   }  

   return tNode;
} 

template < class T >
AVLTreeNode<T>* AVLTree<T>::removeNode(AVLTreeNode<T>* tNode) 
{
   T* replacement_item;

   // test for a leaf --  this test is taken care of by the next two
   if ((tNode->getLeft() == NULL) && (tNode->getRight() == NULL)) 
   {
      delete tNode;
      return NULL;
   }  

   // test for no left child
   else if (tNode->getLeft() == NULL) 
   {
      AVLTreeNode<T>* temp = tNode->getRight();
      delete tNode;
      return temp;
   } 

   // test for no right child
   else if (tNode->getRight() == NULL) 
   {
      AVLTreeNode<T>* temp = tNode->getLeft();
      delete tNode;
      return temp;
   }  

   // there are two children:
   // retrieve and delete the inorder successor
   else 
   {
      replacement_item = findLeftMost(tNode->getRight());
      tNode->setItem(replacement_item);
      tNode->setRight(removeLeftMost(tNode->getRight()));
      if (avlFlag)
      {
         tNode = avlFixRemoveRight(tNode);  //came from right
      }
      return tNode;
   }  
}

template < class T >
T* AVLTree<T>::findLeftMost(AVLTreeNode<T>* tNode)
{
   while (tNode->getLeft() != NULL)
   {
      tNode = tNode->getLeft();
   }
   return tNode->getItem();
}

template < class T >
AVLTreeNode<T>* AVLTree<T>::removeLeftMost(AVLTreeNode<T>* tNode) 
{
   AVLTreeNode<T>* subtree;

   if (tNode->getLeft() == NULL) 
   {
      avlFlag = true;
      subtree = tNode->getRight();
      delete tNode;
      return subtree;
   }
   else 
   {
      subtree = removeLeftMost(tNode->getLeft());
      tNode->setLeft(subtree);
      if (avlFlag)
      {
         tNode = avlFixRemoveLeft(tNode);  //came from left
      }
      return tNode;
   }  
}

template < class T >
bool AVLTree<T>::isBalanced()
{
    int bal = isBalanced(getRootNode());
    if (bal == -1)
    {
       return false;
    }
    return true;
}

template < class T >
int AVLTree<T>::isBalanced(AVLTreeNode<T>* tNode)
{
   if (tNode == NULL)
   {
       return 0;
   }

   int balance = -1;
   AVLTreeNode<T>* left = tNode->getLeft();
   AVLTreeNode<T>* right = tNode->getRight();

   int left_height = isBalanced(left);
   int right_height = isBalanced(right);

   if (left_height != -1  &&  right_height != -1)
   {
       int bal = left_height - right_height;
       if (bal < 0) bal = bal * -1;
       if (bal <= 1)
       {
           if (left_height >= right_height)
           {
               balance = left_height + 1;
           }
           else
           {
               balance = right_height + 1;
           }
       }
   }
   return balance;
}

template < class T >
int AVLTree<T>::getHeight()
{
   int height = getHeight(root);
   return height;
}

template < class T >
int AVLTree<T>::getHeight(AVLTreeNode<T>* tNode)
{
   int height;
   int right_height;

   if (tNode == NULL)
   {
       return 0;
   }
   else
   {
       height = getHeight(tNode->getLeft());
       right_height = getHeight(tNode->getRight());

       if (right_height > height)
       {
           height = right_height;
       }

       return height + 1;
   }
}

template < class T >
AVLTreeNode<T>* AVLTree<T>::rotateLeft(AVLTreeNode<T>* tNode)
{
   AVLTreeNode<T>* right = tNode->getRight();
   AVLTreeNode<T>* rightleft = right->getLeft();

   tNode->setRight(rightleft);
   right->setLeft(tNode);

   return right;
}

template < class T >
AVLTreeNode<T>* AVLTree<T>::rotateRight(AVLTreeNode<T>* tNode)
{
   AVLTreeNode<T>* left = tNode->getLeft();
   AVLTreeNode<T>* leftright = left->getRight();

   tNode->setLeft(leftright);
   left->setRight(tNode);

   return left;
}

template < class T >
AVLTreeNode<T>* AVLTree<T>::DLR(AVLTreeNode<T>* tNode)
{
   AVLTreeNode<T>* left = tNode->getLeft();
   AVLTreeNode<T>* temp = rotateLeft(left);
   tNode->setLeft(temp);
   temp = rotateRight(tNode);
   return temp;
}

template < class T >
AVLTreeNode<T>* AVLTree<T>::DRL(AVLTreeNode<T>* tNode)
{
   AVLTreeNode<T>* right = tNode->getRight();
   AVLTreeNode<T>* temp = rotateRight(right);
   tNode->setRight(temp);
   temp = rotateLeft(tNode);
   return temp;
}

template < class T >
AVLTreeNode<T>* AVLTree<T>::DLR(AVLTreeNode<T>* tNode, AVLTreeNode<T>* left)
{
   AVLTreeNode<T>* leftRight = left->getRight();
   AVL LRBF = leftRight->getBalanceFactor();
   leftRight->setBalanceFactor(BALANCED);

   if (LRBF == RIGHT_HEAVY)
   {
      left->setBalanceFactor(LEFT_HEAVY);
   }
   else if (LRBF == LEFT_HEAVY)
   {
      tNode->setBalanceFactor(RIGHT_HEAVY);    
   }

   tNode = DLR(tNode);
   //cout << "DLR" << endl;
   return tNode;
}

template < class T >
AVLTreeNode<T>* AVLTree<T>::DRL(AVLTreeNode<T>* tNode, AVLTreeNode<T>* right)
{
   AVLTreeNode<T>* rightLeft = right->getLeft();
   AVL RLBF = rightLeft->getBalanceFactor();
   rightLeft->setBalanceFactor(BALANCED);

   if (RLBF == RIGHT_HEAVY)
   {
      tNode->setBalanceFactor(LEFT_HEAVY);
   }
   else if (RLBF == LEFT_HEAVY)
   {
      right->setBalanceFactor(RIGHT_HEAVY);
   }

   tNode = DRL(tNode);
   //cout << "DRL" << endl;
   return tNode;
}

template < class T >
AVLTreeNode<T>* AVLTree<T>::avlFixAddLeft(AVLTreeNode<T>* tNode)
{
   tNode->insertLeft();
   AVL factor = tNode->getBalanceFactor();

   if (factor == BALANCED)
   {
      avlFlag = false; //no more to do this time around
   }
   else if (factor == LEFT_UNBALANCED)
   {
      AVLTreeNode<T>* left = tNode->getLeft();
      AVL LBF = left->getBalanceFactor();

      tNode->setBalanceFactor(BALANCED);
      left->setBalanceFactor(BALANCED);

      //DLR
      if (LBF == RIGHT_HEAVY)
      {
         tNode = DLR(tNode, left);
      }
      //SR
      else 
      {
         tNode = rotateRight(tNode);
         //cout << "SR" << endl;
      }

      avlFlag = false; //basically, stop checking (return the replacement node for this position)
   }
  
   return tNode;
}

template < class T >
AVLTreeNode<T>* AVLTree<T>::avlFixAddRight(AVLTreeNode<T>* tNode)
{
   tNode->insertRight();
   AVL factor = tNode->getBalanceFactor();

   if (factor == BALANCED)
   {
      avlFlag = false; //no more to do this time around
   }
   else if (factor == RIGHT_UNBALANCED)
   {
      AVLTreeNode<T>* right = tNode->getRight();
      AVL RBF = right->getBalanceFactor();

      tNode->setBalanceFactor(BALANCED);
      right->setBalanceFactor(BALANCED);

      //DRL
      if (RBF == LEFT_HEAVY)
      {
         tNode = DRL(tNode, right);
      }

      //SL
      else 
      {
         tNode = rotateLeft(tNode);
         //cout << "SL" << endl;
      }

      avlFlag = false; //basically, stop checking (return the replacement node for this position)
   }

   return tNode;
}

template < class T >
AVLTreeNode<T>* AVLTree<T>::avlFixRemoveLeft(AVLTreeNode<T>* tNode)
{
   tNode->removeLeft();
   AVL factor = tNode->getBalanceFactor();

   if (factor == RIGHT_HEAVY)  //was BALANCED, so completely done for this delete
   {
      avlFlag = false;
   }
   else if (factor == RIGHT_UNBALANCED)
   {
      AVLTreeNode<T>* right = tNode->getRight();
      AVL RBF = right->getBalanceFactor();

      tNode->setBalanceFactor(BALANCED);
      right->setBalanceFactor(BALANCED);

      if (RBF == BALANCED)  //can't happen for insert, only delete
      {
         tNode->setBalanceFactor(RIGHT_HEAVY);
         right->setBalanceFactor(LEFT_HEAVY);
         tNode = rotateLeft(tNode);
         avlFlag = false;  //STOP
         //cout << "SL0" << endl;
      }
      else if (RBF == RIGHT_HEAVY)
      {
         tNode = rotateLeft(tNode);
         //cout << "SL" << endl;
         //KEEP GOING
      }
      else
      {
         tNode = DRL(tNode, right);
      }
   }

   return tNode;
}

template < class T >
AVLTreeNode<T>* AVLTree<T>::avlFixRemoveRight(AVLTreeNode<T>* tNode)
{
   tNode->removeRight();
   AVL factor = tNode->getBalanceFactor();

   if (factor == LEFT_HEAVY)  //was BALANCED, so completely done for this delete
   {
      avlFlag = false;
   }
   else if (factor == LEFT_UNBALANCED)
   {
      AVLTreeNode<T>* left = tNode->getLeft();
      AVL LBF = left->getBalanceFactor();

      tNode->setBalanceFactor(BALANCED);
      left->setBalanceFactor(BALANCED);

      if (LBF == BALANCED)  //can't happen for insert, only delete
      {
         tNode->setBalanceFactor(LEFT_HEAVY);
         left->setBalanceFactor(RIGHT_HEAVY);
         tNode = rotateRight(tNode);
         avlFlag = false;  //STOP
         //cout << "SR0" << endl;
      }
      else if (LBF == LEFT_HEAVY)
      {
         tNode = rotateRight(tNode);
         //cout << "SR" << endl;
         //KEEP GOING
      }
      else 
      {
         tNode = DLR(tNode, left);
      }
   }

   return tNode;
}

//the below methods have been completed for you

template < class T >
void AVLTree<T>::draw(Cairo::RefPtr<Cairo::Context> cr, int width, int height)
{
   Line line(new Color(0, 0, 0), 5.0);
   drawRec(getRootNode(), cr, &line, width, width/2, 20);
}

template < class T >
void AVLTree<T>::drawRec(AVLTreeNode<T>* tNode, Cairo::RefPtr<Cairo::Context> cr, Line* line, int x_parent, int x_curr, int y_curr)
{

   //traversal to draw the entire binary tree
   if (tNode != NULL)
   {
      //computing the location of the current node's two children
      //the distance between a node's two children is the same as the horizontal distance between
      //the current node and the current node's parent
      //need to do this first as the drawing is from the bottom to the top
      int separation = abs(x_curr - x_parent);

      //need to make sure that the children are symmetrically placed with respect to the parent
      int x_left = x_curr - separation/2;  //the location of the left child
      int x_right = x_left + separation;   //the location of the right child

      //compute the vertical location of the current node's parent
      //and the current node's two children
      int y_parent = y_curr - 50;
      int y_children = y_curr + 50;

      //draw the line connecting the current node to its parent
      if (tNode != root)
      {
         line->draw(cr, x_curr, y_curr, x_parent, y_parent);
      }

      //draw the children
      drawRec(tNode->getLeft(), cr, line, x_curr, x_left, y_children);
      drawRec(tNode->getRight(), cr, line, x_curr, x_right, y_children);

      //draw tNode
      tNode->draw(cr, x_curr, y_curr);
   }
}

template < class T >
void AVLTree<T>::mouseClicked(int x, int y) {}

#endif
