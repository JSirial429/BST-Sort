/*
 *Author: Jorge Sirias
 *COP 4338 
 *Professor Caryl Rahn
 *Purpose: To parse strings from either stdin or input file and then place them in a binary search tree 
 *
 *I affirm that I worte this program myself with no help from other people or sources from the internet
 *
 */

#include<stdlib.h>
#include<stdio.h>
#include<string.h>
#include<stdbool.h>
 
//Struct definiton for a node in a BST data structure
typedef struct Node
{

  int count;
  char* cString;
  struct Node* lNode; //Left Node
  struct Node* rNode; //Right Node

}Node;

//CreateNode functions creates a new node that is placed in a binary search tree
struct Node* createNode(char* aString)
{

  struct Node* newNode = (struct Node*)malloc(sizeof(struct Node)); //Allocate memory for new node
  
  newNode -> count = 0;
  newNode -> cString = aString;
  newNode -> lNode   = NULL;
  newNode -> rNode   = NULL;
  
  printf("newNode->cString: %s\n", newNode->cString);  //DELETE

  return newNode;

}

//Recursion function to find a spot in the BST for the node
struct Node* addNode(Node* rootNode, char* aString, int cFlag)
{

  //Node* currPtr = aNode; //ptr variable that points to the location of the current node
  //Node* prevPtr = NULL;  //Ptr varibale that holds location of the previous node
  int toRight = 0, toLeft = 0; //Holds the value of strCmpCase value. Determines whether node should go on the left or right  
  int strCmp; //Holds value returned by strCmpCase function  

  printf("Inside the addNode function\n"); //DELETE!!i
  printf("rootNode ptr = %p\n", rootNode);  //DELETE!
  //printf("cFlag = %d\n", cFlag);  //DELETE!!
  if(rootNode == NULL) //Base Case 
  {
    printf("rootNode == NULL. Creating new node.\n");  //DELETE!
    rootNode = createNode(aString);

  }
  else if(cFlag == 1)
  {
    
    Node* currPtr = rootNode; //ptr variable that points to the location of the current node
    Node* prevPtr = NULL;  //Ptr varibale that holds location of the previous node
    int strCmp = 0;
    printf("cFlag = 1 therefore conditional is activated\n");
    while(currPtr != NULL)
    {  
       printf("cFlag = 1 therefore conditional is activated\n");
       prevPtr = currPtr;
       if( (strCmp = strCmpCase(aString, prevPtr->cString)) == 1)//Returns 1 if aString is less than current node->data           
       {
         printf("aString: %s  currPtr->cString: %s\n", aString, prevPtr->cString); //DELETE !!
         printf("strCmpCase returned 1\n");  //DELETE!!
         //printf("Calling recusrsive function!\n");  //DELETE!!
         currPtr = currPtr->lNode;
         toLeft = 1;
       }
       else if( strCmp = (strCmpCase(aString, prevPtr->cString)) == -1)//returns -1 id aString is larger than current node->Data
       {
         printf("aString: %s  currPtr->cString: %s\n", aString, prevPtr->cString); //DELETE !!
         printf("strCmpCase returned -1\n");  //DELETE!!
         //printf("Calling recusrsive function!\n");  //DELETE!!
         currPtr = currPtr->rNode;
         toRight = 1;
       }     

    }

    if(toLeft == 1)
    {
      printf("I am in toLeft conditional\n");
      prevPtr->lNode = createNode(aString);
    }
    else
    {
      printf("I am in toLeft conditional\n"); 
      prevPtr->rNode = createNode(aString);
    }
  
  }
  printf("Exiting addNode function\n");  //DELETE!!
  return rootNode;
}

//Function that prints the BST in inorder traversal
void printInorder(struct Node* aNode)
{
  printf("Inside the printInorder traversal!\n");
  if(aNode != NULL) //Base Case
  {
    printInorder(aNode->lNode);
    printf("%s\n", aNode->cString);
    printInorder(aNode->rNode);
  }

}

//Function that compares two strings
int strCmpCase(char* alphaString,char* betaString)
{

  int AString, BString; //Variables that hold string length
  int count;
  int i = 0;

  char a, b; //Holds current char at index i of an array of char that makes up a string
 
  printf("strCmpCase: alphaString:%s betaString:%s\n", alphaString, betaString); //DELETE
 
  AString = strlen(alphaString);
  BString = strlen(betaString);
  printf("AString strlen: %d\n", AString);  //DELETE!
  printf("BString strlen: %d\n", BString);  //DELETE!

  if(AString <= BString)
  {
    count = AString;
    printf("Count: %d\n", count);  //DELETE!
  } 
  else if (BString < AString)
  {
    count = BString;
    printf("Count: %d\n", count); //DELETE!
  }

  AString = 0, BString = 0;

  while(i < count)
  {
  
    a = alphaString[i];
    b = betaString[i];

    if( a < b  )
    { 
      printf("%c/%d < %c/%d\n", a,(int)a,b,(int)b); //DELETE!
      AString++;
    }  
    else if( b < a  )
    {
      printf("%c/%d < %c/%d\n", b,(int)b,a,(int)a); //DELETE!
      BString++;
    }
    else
    {

      AString++;
      BString++;
    
    }
  
    i++;
   
  }
  
  if((AString < BString) || (AString == BString))
  {
    printf("AString/%d < BString/%d: Return 1\n", AString, BString); //DELETE!  
    return 1;
  } 
  else
  {
    printf("BString/%d < AString/%d: Return -1 \n", BString, AString); //DELETE!
    return -1;
  }

}

int main(int argc,char** argv)
{

  extern char* optarg; //Hold value after colon when processing flags via getopt
  extern int   optind; //Index of first element after processing options via getopt and on command line

  int oFlag = 0, cFlag = 0; //Variables that marks whether flags have been enabled via getopt

  int c; //Holds return value of calling getopt function

  char str[1024];//Stores string from user standard input or file
  char* outFileName;

  FILE* outFile = NULL;
  FILE* inFile = NULL;

  //bool firstNode = 1;

  struct Node* bstNode = NULL;

  while( (c = getopt(argc, argv, "co:")) != -1 )
  {

    switch(c)
    {

      case 'c':
        cFlag = 1;
        break;

      case 'o':
        oFlag = 1;
        outFileName = optarg;
        break;     

    }

  } 
 
  //No input file is present, standard input will be used for BST
  if(argv[optind] == NULL)
  {
    /////////////////////Experimental//////////////////
    //if(bstNode == NULL)
    //{
        
    //}
    //////////////////////Experimental/////////////////
    printf("I am inside the argv[optind] == NULL conditional in main\n");  //DELETE! 
    while(*(fgets(str, 1024, stdin)) != '\n' )
    {
      printf("Please type a string into the program:\n");
      //printf("Inside the while loop in the main function\n");  //DELETE!
      printf("bstNode* = %p\n", bstNode);  //DELETE!!
      printf("str:%s\n", str);  //DELETE!!
      bstNode = addNode(bstNode, str, cFlag);
      printf("bstNode->cString: %s", bstNode->cString);
    }
    printf("\n\nAbout to call printInorder function\n");     
    printInorder(bstNode);
  }
  printf("App has ran successfully.\n");  //DELETE!

  return 0;

}
