#include <iostream>
#include <cstdlib>
#include <cstring>

using namespace std;

const int MAX_WORD_LENGTH = 80;

struct Node;
typedef Node *Node_ptr;

struct Node{
  char word[MAX_WORD_LENGTH];
  Node_ptr ptr_to_next_node;
};

void assign_list(Node_ptr &a_list);

void assign_new_node(Node_ptr &a_node);

void print_list(Node_ptr a_node);

void print_list_backwards(Node_ptr a_node);

void add_after(Node_ptr &list, char a_word[], char word_after[]);

void delete_node(Node_ptr &a_list, char a_word[]);

void list_selection_sort(Node_ptr &a_list);

void swap_words(char first[], char second[]);

bool compare_string(char str_1[], char str_2[]);

int main(){
  char a_word[MAX_WORD_LENGTH],new_word[MAX_WORD_LENGTH],del_word[MAX_WORD_LENGTH];
  Node_ptr my_list = NULL;

  assign_list(my_list);
  cout << "\n THE LIST IS NOW:\n";
  print_list(my_list);
  print_list_backwards(my_list);
  cout << "ADD A WORD:  " << endl;
  cin >> new_word;
  cout << "AFTER WORD: " << endl;
  cin >> a_word;

  add_after(my_list, a_word, new_word);

  print_list(my_list);

  cout << "DELETE WORD: " << endl;
  cin >> del_word;
  
  delete_node(my_list,del_word);

  print_list(my_list);

  list_selection_sort(my_list);

  print_list(my_list);
  
  return 0;
}

void assign_list(Node_ptr &a_list){
  Node_ptr current_node, last_node;
  assign_new_node(a_list);
  cout << "Enter first word (or '.' to end list):";
  cin >> a_list->word;
  if(!strcmp("a",a_list->word)){
    delete a_list;
    a_list = NULL;
  }
  current_node = a_list;

  while(current_node !=NULL){
    assign_new_node(last_node);
    cout << "Enter next word (or '.' to end list): ";
    cin >> last_node->word;
    if(!strcmp(".",last_node->word)){
      delete last_node;
      last_node = NULL;
    }
    current_node->ptr_to_next_node = last_node;
    current_node = last_node;
  }
}

void assign_new_node(Node_ptr &a_node){ // ampersand denotes you are passing in by reference (the actual pointer)
  a_node = new(nothrow) Node;
  if(a_node == NULL){
    cout << "sorry - no more memory\n";
    exit(1);
  }
}

void print_list(Node_ptr a_node){ //no ampersand means you are initialising a copy of the pointer
  if(!a_node){
    cout << endl;
    return;
  }
  cout << a_node->word << " ";
  print_list(a_node->ptr_to_next_node);
  /*while(a_node != NULL){
    cout << a_node->word << " ";
    a_node = a_node->ptr_to_next_node;
  }
  cout << endl;
  */
}

void print_list_backwards(Node_ptr a_node){ //no ampersand means you are initialising a copy of the pointer
  if(!a_node){
    return;
  }
  print_list_backwards(a_node->ptr_to_next_node);
  cout << a_node->word << " ";
  return;
  /*while(a_node != NULL){
    cout << a_node->word << " ";
    a_node = a_node->ptr_to_next_node;
  }
  cout << endl;
  */
}

void add_after(Node_ptr &a_list,char a_word[], char word_after[]){
  //empty list case
  if(!a_list){
    return;
  }
  Node_ptr p = a_list;
  while(p){
    if(!strcmp(a_word, p->word)){
      Node_ptr new_node;
      assign_new_node(new_node);
      strcpy(new_node->word,word_after);
      new_node->ptr_to_next_node = p->ptr_to_next_node;
      p->ptr_to_next_node = new_node;
      return;
    }
    p=p->ptr_to_next_node;
  }
  return;
}

void delete_node(Node_ptr &a_list, char a_word[]){
  Node_ptr p=a_list, q;
  while(p){ //check p
    if(!strcmp(a_word,p->word)){ //checl for similarity
      if(q){ //if q is not empty, make q (node before node to be deleted to point to the next node of the node to be deleted)
	q->ptr_to_next_node=p->ptr_to_next_node;
      }else{
	a_list=p->ptr_to_next_node;
      }
      delete p; //delete p
      p=NULL; // make p null
      return;
    }
    q=p; //if not the same, assign q to p;
    p=p->ptr_to_next_node; //point to next node
  }
  return;
}

void list_selection_sort(Node_ptr &a_list){
  Node_ptr p = a_list;

  while(p){
    Node_ptr q = p->ptr_to_next_node, smallest_ptr = p;
    while(q){
      if(compare_string(q->word, smallest_ptr->word)){
	smallest_ptr = q;
      }
      q=q->ptr_to_next_node;
    }
    if(smallest_ptr != p){
      swap_words(p->word,smallest_ptr->word);
    }
    p=p->ptr_to_next_node;
  }
}

void swap_words(char first[], char second[]){
  char temp [MAX_WORD_LENGTH];
  strcpy(temp,first);
  strcpy(first, second);
  strcpy(second,temp);
}

bool compare_string(char str_1[],char str_2[]){
  int count=0;
  while (str_1[count]!='\0'){
    if(str_1[count]<str_2[count]){
      return true;
    }else if(str_1[count]>str_2[count]){
      return false;
    }
    count++;
  }
  if (str_2[count]){
    return true;
  }else{
    return false;
  }
}
