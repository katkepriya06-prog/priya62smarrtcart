#include <iostream.h>
#include <conio.h>
#include <string.h>

#define MAX 10

// Structure for product list
struct Product {
    int id;
    char name[30];
    int price;
};

// Node for cart (Linked List)
struct Node {
    int id;
    char name[30];
    int price;
    Node *next;
};

// Stack for removed items
struct StackNode {
    int id;
    char name[30];
    int price;
    StackNode *next;
};

// Queue for orders
struct QueueNode {
    int id;
    char name[30];
    int price;
    QueueNode *next;
};

Product products[MAX] = {
    {1, "Rice", 60},
    {2, "Milk", 40},
    {3, "Bread", 30},
    {4, "Biscuits", 20},
    {5, "Juice", 50}
};

int productCount = 5;

Node *cart = NULL;
StackNode *top = NULL;
QueueNode *front = NULL;
QueueNode *rear = NULL;

// function to show items
void displayProducts() {
    cout << "\n----- PRODUCT LIST -----\n";
    for(int i = 0; i < productCount; i++) {
        cout << "ID: " << products[i].id << "  Name: " << products[i].name << "  Price: Rs." << products[i].price << "\n";
    }
}

// add to cart
void addToCart() {
    int id;
    int flag = 0;
    Node *newNode, *temp;

    cout << "\nEnter Product ID: ";
    cin >> id;

    for(int i = 0; i < productCount; i++) {
        if(products[i].id == id) {
            flag = 1;
            newNode = new Node;
            newNode->id = products[i].id;
            strcpy(newNode->name, products[i].name);
            newNode->price = products[i].price;
            newNode->next = NULL;

            if(cart == NULL) {
                cart = newNode;
            } else {
                temp = cart;
                while(temp->next != NULL) {
                    temp = temp->next;
                }
                temp->next = newNode;
            }
            cout << "\nProduct added to cart successfully!";
            break;
        }
    }

    if(flag == 0) {
        cout << "\nProduct not found!";
    }
}

// show cart contents
void displayCart() {
    Node *temp;
    cout << "\n----- MY CART -----\n";
    
    if(cart == NULL) {
        cout << "Cart is empty!";
        return;
    }

    temp = cart;
    while(temp != NULL) {
        cout << "ID: " << temp->id << "  " << temp->name << "  Rs." << temp->price << "\n";
        temp = temp->next;
    }
}

// remove item from cart and push to stack
void removeFromCart() {
    int id;
    Node *temp = cart;
    Node *prev = NULL;
    StackNode *s;

    cout << "\nEnter Product ID to remove: ";
    cin >> id;

    while(temp != NULL) {
        if(temp->id == id) {
            // push to stack
            s = new StackNode;
            s->id = temp->id;
            strcpy(s->name, temp->name);
            s->price = temp->price;
            s->next = top;
            top = s;

            // delete node
            if(prev == NULL) {
                cart = temp->next;
            } else {
                prev->next = temp->next;
            }
            delete temp;

            cout << "\nProduct removed from cart & added to Stack!";
            return;
        }
        prev = temp;
        temp = temp->next;
    }

    cout << "\nProduct not found in cart!";
}

// display stack items
void displayStack() {
    StackNode *temp = top;
    cout << "\n----- RECENTLY REMOVED -----\n";

    if(top == NULL) {
        cout << "No removed products.";
        return;
    }

    while(temp != NULL) {
        cout << temp->name << " - Rs." << temp->price << "\n";
        temp = temp->next;
    }
}

// place order (queue enqueue)
void placeOrder() {
    if(cart == NULL) {
        cout << "\nCart is empty! Cannot place order.";
        return;
    }

    Node *temp = cart;
    while(temp != NULL) {
        QueueNode *newNode = new QueueNode;
        newNode->id = temp->id;
        strcpy(newNode->name, temp->name);
        newNode->price = temp->price;
        newNode->next = NULL;

        if(rear == NULL) {
            front = rear = newNode;
        } else {
            rear->next = newNode;
            rear = newNode;
        }
        temp = temp->next;
    }
    cout << "\nOrder placed & added to Queue!";
}

// process order (queue dequeue)
void processOrder() {
    if(front == NULL) {
        cout << "\nNo orders in queue!";
        return;
    }

    QueueNode *temp = front;
    cout << "\nProcessing Order: " << temp->name << " - Rs." << temp->price;
    
    front = front->next;
    if(front == NULL) {
        rear = NULL;
    }
    delete temp;
}

// display queue
void displayQueue() {
    QueueNode *temp = front;
    cout << "\n----- ORDER QUEUE -----\n";

    if(front == NULL) {
        cout << "Queue is empty!";
        return;
    }

    while(temp != NULL) {
        cout << temp->name << " - Rs." << temp->price << "\n";
        temp = temp->next;
    }
}

// main menu
void main() {
    int choice;
    clrscr();

    do {
        cout << "\n\n========================";
        cout << "\n       SMARTCART";
        cout << "\n========================";
        cout << "\n1. Display Products";
        cout << "\n2. Add Product to Cart";
        cout << "\n3. Display Cart";
        cout << "\n4. Remove Product";
        cout << "\n5. Recently Removed";
        cout << "\n6. Place Order";
        cout << "\n7. Process Order";
        cout << "\n8. Display Order Queue";
        cout << "\n9. Exit";
        
        cout << "\n\nEnter your choice: ";
        cin >> choice;

        switch(choice) {
            case 1: displayProducts(); break;
            case 2: addToCart(); break;
            case 3: displayCart(); break;
            case 4: removeFromCart(); break;
            case 5: displayStack(); break;
            case 6: placeOrder(); break;
            case 7: processOrder(); break;
            case 8: displayQueue(); break;
            case 9: cout << "\nExiting... Thank you!"; break;
            default: cout << "\nInvalid choice! Try again.";
        }
    } while(choice != 9);

    getch();
}