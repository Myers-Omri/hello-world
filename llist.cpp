#include<stdio.h>
#include<stdlib.h>

struct node_t  {
	int data;
	struct node_t* next;
	struct node_t* prev;
};

typedef node_t Node;
Node* head; 

//Creates a new Node and returns pointer to it. 
Node* GetNewNode(int x) {
	Node* newNode
		= (Node*)malloc(sizeof(Node));
	newNode->data = x;
	newNode->prev = NULL;
	newNode->next = NULL;
	return newNode;
}

//Inserts a Node at head of doubly linked list
void InsertAtHead(int x) {
	Node* newNode = GetNewNode(x);
	if (head == NULL) {
		head = newNode;
		return;
	}
	head->prev = newNode;
	newNode->next = head;
	head = newNode;
}

//Inserts a Node at tail of Doubly linked list
void InsertAtTail(int x) {
	Node* temp = head;
	Node* newNode = GetNewNode(x);
	if (head == NULL) {
		head = newNode;
		return;
	}
	while (temp->next != NULL) temp = temp->next; // Go To last Node
	temp->next = newNode;
	newNode->prev = temp;
}

//Prints all the elements in linked list in forward traversal order
void Print() {
	Node* temp = head;
	printf("Forward: ");
	while (temp != NULL) {
		printf("%d ", temp->data);
		temp = temp->next;
	}
	printf("\n");
}

//Prints all elements in linked list in reverse traversal order. 
void ReversePrint() {
	Node* temp = head;
	if (temp == NULL) return; // empty list, exit
	// Going to last Node
	while (temp->next != NULL) {
		temp = temp->next;
	}
	// Traversing backward using prev pointer
	printf("Reverse: ");
	while (temp != NULL) {
		printf("%d ", temp->data);
		temp = temp->prev;
	}
	printf("\n");
}

int main(void) {

	/*Driver code to test the implementation*/
	head = NULL; // empty list. set head as NULL. 

	// Calling an Insert and printing list both in forward as well as reverse direction. 
	InsertAtTail(2); Print(); ReversePrint();
	InsertAtTail(4); Print(); ReversePrint();
	InsertAtHead(6); Print(); ReversePrint();
	InsertAtTail(8); Print(); ReversePrint();

	system("pause");
	return 0;

}