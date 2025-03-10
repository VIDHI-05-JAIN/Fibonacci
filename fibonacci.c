#include <stdio.h>
#include <stdlib.h>

typedef struct Node {
    char data;
    struct Node* next;
} Node;

Node* createNode(char data) {
    Node* newNode = (Node*)malloc(sizeof(Node));
    newNode->data = data;
    newNode->next = NULL;
    return newNode;
}

Node* generateFibonacciLinkedList(int n) {
    int a = 1, b = 1, c = 0;
    for (int i = 2; i < n; i++) {
        c = a + b;
        a = b;
        b = c;
    }
    int lastFibonacci = (n <= 2) ? 1 : c;

    Node* head = NULL;
    Node* tail = NULL;
    for (int i = 0; i < lastFibonacci; i++) {
        char data = 'A' + (i % 26);
        Node* newNode = createNode(data);
        if (head == NULL) {
            head = newNode;
            tail = newNode;
        } else {
            tail->next = newNode;
            tail = newNode;
        }
    }
    return head;
}

int* generateFibonacciSequence(int n, int* size) {
    int* fib = (int*)malloc(n * sizeof(int));
    fib[0] = 1;
    if (n > 1) fib[1] = 1;
    for (int i = 2; i < n; i++) {
        fib[i] = fib[i - 1] + fib[i - 2];
    }
    *size = n;
    return fib;
}

Node* deleteFibonacciNodes(Node* head, int n) {
    int size;
    int* fib = generateFibonacciSequence(n, &size);
    Node* current = head;
    Node* prev = NULL;
    Node* temp = NULL;
    int count = 1;
    int fibIndex = 0;
    int deleted[100] = {0};

    while (fibIndex < size) {
        if(fib[fibIndex] > 100) break;
        if (fib[fibIndex] == count && deleted[fib[fibIndex]] == 0) {
            deleted[fib[fibIndex]] =1;
            if (prev == NULL) {
                temp = current;
                current = current->next;
                head = current;
                free(temp);
            } else {
                temp = current;
                current = current->next;
                prev->next = current;
                free(temp);
            }
            fibIndex++;
        } else {
            prev = current;
            if(current !=NULL)
            current = current->next;
            count++;
        }
        if(current == NULL)break;
    }

    free(fib);
    return head;
}

void printRemainingNodes(Node* head) {
    Node* current = head;
    while (current != NULL) {
        printf("%c", current->data);
        if (current->next != NULL) {
            printf("->");
        }
        current = current->next;
    }
    printf("\n");
}

int main() {
    int n;
    printf("Enter the number of Fibonacci elements to generate: ");
    scanf("%d", &n);

    Node* head = generateFibonacciLinkedList(n);
    head = deleteFibonacciNodes(head, n);
    printRemainingNodes(head);

    return 0;
}