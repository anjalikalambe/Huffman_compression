#include <string.h>
#include <stdio.h>
#include <stdlib.h>

#define TABLE "huffman_table_<FILE>"

/*tree node*/
struct node
{
    char letter;
    int frequency;
    struct node *left;
    struct node *right;
    int visited;
    char* codes[10];
};
typedef struct node node_t;

struct huffman_row
{
  char letter;
  char code[10];
};

typedef struct huffman_row huffman_row_t;

int get_unique_chars(char chars[], int length); /*gets number of unique characters in array of characters.*/
node_t *make_leaf_nodes(char char_array[], int length); /*for each unique element creates leaf node, assigns frequency and stores in array*/
void sort_nodes_ascending(node_t *nodes, int length); /*gets array and arranges it in ascending order*/
node_t *make_tree(node_t *nodes, int length); /*removes 2 nodes from the front of the array and creates internal node, which is then added to queue after traversing.*/
void post_order_traversal(node_t* node);
/*void create_huffman_table(node_t* tree, char char_arr[], int length);
void save_huffman_code(node_t* node);*/

int main(void)
{
    printf("Hi, this is assignment 3 Huffman Coding! \n");

    char chars[] = {'a', 'c', 'c', 'a', 'x', 'f', 'j', 'a', 'e', 'e', 'm'};
    int length = (int)sizeof(chars);
    int unique_chars = get_unique_chars(chars, length);
    printf("unique characters: %d\n", unique_chars);

    node_t *nodes_array = make_leaf_nodes(chars, length);
    int i;
    for (i = 0; i < unique_chars; i++)
    {
        printf("position in array:  %d, ", i);
        printf("letter in array node:  %c, ", nodes_array[i].letter);
        printf("frequency in array node %d\n", nodes_array[i].frequency);
    }

    sort_nodes_ascending(nodes_array, unique_chars);
    printf("\n");

    node_t *tree = make_tree(nodes_array, unique_chars);
    post_order_traversal(tree);
    /*create_huffman_table(tree, chars, length);*/

    return 0;
}

/*gets number of unique characters in array of characters.*/
int get_unique_chars(char chars[], int length)
{
    int unique_chars = 0;
    int i;
    for (i = 0; i < length; i++)
    {
        char character = chars[i];
        int duplicates = 0; /*false - no duplicates*/
        int k;
        for (k = 0; k < i; k++)
        {
            if (character == chars[k])
            {
                duplicates = 1; /*true - duplicate exists*/
            }
        }

        if (duplicates == 0)
        {
            unique_chars++;
        }
    }
    return unique_chars;
}

/*for each unique element create a leaf node, assign frequency and store in an ascending order*/
node_t *make_leaf_nodes(char chars[], int length)
{
    node_t nodes_array[1000];
    node_t *array_ptr = nodes_array;
    int unique_chars = 0;

    int i;
    for (i = 0; i < length; i++)
    {
        node_t newNode;
        char character = chars[i];
        int frequency = 1;

        int duplicates = 0; /*false - no duplicates*/
        int k;
        for (k = 0; k < i; k++)
        {
            if (character == chars[k])
            {
                duplicates = 1; /*true - duplicate exists*/
            }
        }

        if (duplicates == 0)
        {
            int j;
            for (j = i + 1; j < length; j++)
            {
                if (character == chars[j])
                {
                    frequency++;
                }
            }

            newNode.letter = character;
            newNode.frequency = frequency;
            newNode.right = NULL;
            newNode.left = NULL;
            newNode.visited = 0;
            nodes_array[unique_chars] = newNode;
            unique_chars++;
        }
    }
    return array_ptr;
}


void sort_nodes_ascending(node_t* nodes, int length)
{
  printf("%d\n", length);
  int i;
  for (i = 0; i < length; i++)
  {
    int j;
    for (j = i + 1; j < length; j++)
    {
      if ((nodes[j].frequency) < nodes[i].frequency)
      {
        node_t temp = nodes[i];
        nodes[i] = nodes[j];
        nodes[j] = temp;
      }
    }
  }
    printf("After sorting\n");
    int k;
    for (k = 0; k < length; k++){
      printf("new array position: %d ",k );
      printf("letter: %c ",nodes[k].letter);
      printf("frequency of node: %d ", nodes[k].frequency);
      printf("address of node: %p\n", &nodes[k]);
    }
    printf("\n");
}


node_t* make_tree(node_t* nodes, int length){
  printf("%d\n", length);

  node_t nodes_array[1000];/*need to make dynamic becuase c cant allocate memory at runtime*/
  node_t* tree = nodes_array;

    sort_nodes_ascending(nodes, length);
    printf("%d\n", nodes[0].frequency);

    while (length != 1)
    {
        int freq1 = nodes[0].frequency;
        int freq2 = nodes[1].frequency;

        int position = 0;
        node_t internal_node;
        internal_node.left = &nodes[0];
        internal_node.right = &nodes[1];
        internal_node.frequency = freq1 + freq2;
        internal_node.letter = 'z';
        printf("address stored at internal nodes left: %p\n", internal_node.left);
        printf("address stored at internal nodes right: %p\n", internal_node.right);
        printf("frequency of internal node: %d\n", internal_node.frequency);


        tree[position] = internal_node;
        position++;
        int i;
        for (i = position; i < length - 1; i++)
        {
            tree[i] = nodes[i + 1];
        }
        length--;
        printf("Before sorting\n");
        int j;
        for (j = 0; j < length; j++)
        {
            printf("new array position: %d ", j);
            printf("letter: %c ", tree[j].letter);
            printf("frequency of node: %d\n", tree[j].frequency);
        }
        sort_nodes_ascending(tree, length);
        nodes = tree;
  }
  return tree;
}

void post_order_traversal(node_t* node){
    if (node == NULL) 
        return; 
    post_order_traversal(node->left); 
  
    post_order_traversal(node->right); 
  
    printf("%d \n", node->frequency);
}


// void create_huffman_table(node_t* tree, char char_arr[], int length){
//     /*have a method which can return an array which only contains unique characters*/


//     char characters[50];
//     int position=0;

//     int i;
//     for (i = 0; i < length; i++)
//     {
//         char unique_char;
//         char character = char_arr[i];
//         int frequency = 1;

//         int duplicates = 0; /*false - no duplicates*/
//         int k;
//         for (k = 0; k < i; k++)
//         {
//             if (character == char_arr[k])
//             {
//                 duplicates = 1; /*true - duplicate exists*/
//             }
//         }

//         if (duplicates == 0)
//         {
//             characters[position] = character;
//             position++;
//         }
//     }

//     printf("\n");
//     for (i = 0; i < position; i++)
//     {
//         printf("position in array:  %d, ", i);
//         printf("letter in array node:  %c \n", characters[i]);
//     }
//     /*ABOVE CODE SHOULD HAVE ITS OWN METHOD!!!*/

//     node_t *node = tree;
//     node_t *root = tree;

//     node_t stack[100];
//     int currentPos = 0;
//     int headPos = 0;

//     while(currentPos!=length){
//         printf("hi\n");
//         if(node->visited==0 && node->left!=NULL && node->right!=NULL){
//             stack[headPos] = *node; /*imitate stack push*/
//             headPos++;
//             node = node->left;
//         }else if(node->visited==0 && node->left==NULL && node->right==NULL){
//             printf("%c",node->letter);
//             headPos--;
//             node = &stack[headPos];
//             node->visited = node->visited+1; /*mark as 1 child visited*/
//         } else if(node->visited==1){
//             /* node->visited = 2; mark as 2 children visited*/
//             node = node->right;
//         }

//     }

// }
