#include <iostream>
#include <cstring>
#include <cassert>

using namespace std;

const int STRING_SIZE = 80;

//one node in the linked list looks like this
struct Node{
  char word [STRING_SIZE]; // a string
  Node *next; //pointer to next node
  Node *prev; //pointer to previous node
};

//Create a pointer to a new node
Node *create_new_node(const char *contents){
  Node *new_node = new (nothrow) Node;
  assert(new_node != NULL);
  strcpy(new_node ->word, contents); //initialise the node with tect contents
  new_node->next = NULL; //set the next node pointer to NULL
  new_node->prev = NULL;
  return new_node;
}

//set up an empty list
void initialise_list(Node *&front, Node *&rear){ //dereference the address of the node
  front=rear=NULL; 
}

void add_to_front(Node *&front, Node *&rear, const char *word){
  Node *item = create_new_node(word);

  //empty list case
  if(!front){
    front = rear = item;
    return;
  }

  //default case
  item->next = front;
  front->prev = item;
  front = item;
}

void add_to_rear(Node *&front, Node *&rear, const char *word){
  Node *item = create_new_node(word);

  //empty list case
  if(!front){
    front = rear = item;
  }

  //default case
  rear->next = item;
  item->prev = rear;
  rear=item;
}

void print_list(Node *front){
  for(Node *current = front;current;current=current->next){
    cout << "[" << current->word << "]" << endl;
  }
}

void delete_node(Node *&front, Node *&rear, const char *target){
  Node *p = front, *q = NULL;

  for (p=front; p && strcmp(p->word, target);p=p->next){
    q=p;
  }
  if(p == NULL){
    cout << "could not find the word " << target << " in the list" << endl;
    return;
  }
  Node *link = p->next;
  delete p;

  if (p==front){
    front = link;
    if(front == NULL){
      rear= NULL;
    }
    return;
  }
  q-> next = link;

  if(p == rear){
    rear = q;
  }
}

void add_sorted(Node *&front, Node *&rear, const char *new_word){
  Node *p = front, *q = NULL;

  for(p=front;p && (strcmp(p->word, new_word)<0);p=p->next){
    q=p;
  }

  if(q==NULL){
    add_to_front(front, rear, new_word);
    return;
  }

  if(p==NULL){
    add_to_rear(front, rear, new_word);
    return;
  }

  Node *new_node = create_new_node(new_word);

  new_node->next = p;
  new_node->prev = q;
  p->prev = new_node;
  q->next = new_node;
}

void delete_list(Node *&front, Node *&rear){
  while(front != NULL){
    Node *link = front->next;
    delete front;
    front=link;
  }
  rear=NULL;
}

int main(){
  Node *front, *rear;

  initialise_list(front, rear);

  add_to_front(front, rear, "sat");
  add_to_rear(front, rear, "cat");
  add_to_front(front, rear, "mat");
  add_to_rear(front, rear, "hat");

  print_list(front);
  cout << endl;

  delete_node(front, rear, "mat");

  print_list(front);
  cout << endl;

  delete_node(front, rear, "mat");

  print_list(front);
  cout << endl;

  delete_list(front, rear);

  add_sorted(front, rear, "sat");
  add_sorted(front, rear, "cat");
  add_sorted(front, rear, "hat");
  add_sorted(front, rear, "mat");
  add_sorted(front, rear, "bat");
  add_sorted(front, rear, "rat");

  print_list(front);
  cout << endl;

  delete_list(front,rear);

  return 0;
}
