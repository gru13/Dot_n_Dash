#include "./Inbulit_types.h"

// Stack implementations

// Function to initialize the stack
void StackInit(Stack *s) {
    s->capacity = INITIAL_CAPACITY;
    s->top = -1;
    s->items = (int *)malloc(s->capacity * sizeof(int));
    if (!s->items) {
        printf("Memory allocation failed\n");
        exit(EXIT_FAILURE);
    }
}

// Function to check if the stack is full
int StackisFull(Stack *s) {
    return s->top == s->capacity - 1;
}

// Function to check if the stack is empty
int StackisEmpty(Stack *s) {
    return s->top == -1;
}

// Function to StackResize the stack
void StackResize(Stack *s, int new_capacity) {
    s->capacity = new_capacity;
    s->items = (int *)realloc(s->items, s->capacity * sizeof(int));
    if (!s->items) {
        printf("Memory allocation failed\n");
        exit(EXIT_FAILURE);
    }
}

// Function to push an element onto the stack
void StackPush(Stack *s, int value) {
    if (StackisFull(s)) {
        StackResize(s, s->capacity + INCREMENT);
    }
    s->items[++(s->top)] = value;
}

// Function to pop an element from the stack
int StackPop(Stack *s) {
    if (StackisEmpty(s)) {
        printf("Stack Underflow\n");
        exit(EXIT_FAILURE);
    }
    int popped_value = s->items[(s->top)--];

    // If the current size drops below capacity minus 20, and capacity is above the initial, decrease capacity by 20
    if (s->capacity > INITIAL_CAPACITY && s->top < s->capacity - INCREMENT - 1) {
        StackResize(s, s->capacity - INCREMENT);

        // Ensure capacity doesn't drop below the initial capacity
        if (s->capacity < INITIAL_CAPACITY) {
            StackResize(s, INITIAL_CAPACITY);
        }
    }

    return popped_value;
}

// Function to StactPeek at the top element of the stack
int StactPeek(Stack *s) {
    if (StackisEmpty(s)) {
        printf("Stack is empty\n");
        exit(EXIT_FAILURE);
    }
    return s->items[s->top];
}

// Function to free the allocated memory
void Stackfree(Stack *s) {
    free(s->items);
    s->items = NULL;
}

// Function to print all the elements in the stack
void StackPrint(Stack *s) {
    if (StackisEmpty(s)) {
        printf("Stack is empty\n");
        return;
    }
    printf("Stack elements are:\n");
    for (int i = 0; i <= s->top; i++) {
        printf("%d ", s->items[i]);
    }
    printf("\n");
}


// Queue Implementation

// Function to initialize the queue
void QueueInit(Queue *q) {
    q->capacity = INITIAL_CAPACITY;
    q->front = 0;
    q->size = 0;
    q->rear = q->capacity - 1;
    q->items = (int *)malloc(q->capacity * sizeof(int));
    if (!q->items) {
        printf("Memory allocation failed\n");
        exit(EXIT_FAILURE);
    }
}

// Function to check if the queue is full
int QueueIsFull(Queue *q) {
    return q->size == q->capacity;
}

// Function to check if the queue is empty
int QueueIsEmpty(Queue *q) {
    return q->size == 0;
}

// Function to resize the queue
void QueueResize(Queue *q, int new_capacity) {
    int *new_items = (int *)malloc(new_capacity * sizeof(int));
    if (!new_items) {
        printf("Memory allocation failed\n");
        exit(EXIT_FAILURE);
    }

    // Copy elements to the new array
    for (int i = 0; i < q->size; i++) {
        new_items[i] = q->items[(q->front + i) % q->capacity];
    }

    free(q->items);
    q->items = new_items;
    q->capacity = new_capacity;
    q->front = 0;
    q->rear = q->size - 1;
}

// Function to enqueue an element to the queue
void QueueEnqueue(Queue *q, int value) {
    if (QueueIsFull(q)) {
        QueueResize(q, q->capacity + INCREMENT);
    }
    q->rear = (q->rear + 1) % q->capacity;
    q->items[q->rear] = value;
    q->size++;
}

// Function to dequeue an element from the queue
int QueueDequeue(Queue *q) {
    if (QueueIsEmpty(q)) {
        printf("Queue Underflow\n");
        exit(EXIT_FAILURE);
    }
    int dequeued_value = q->items[q->front];
    q->front = (q->front + 1) % q->capacity;
    q->size--;

    // If the current size drops below capacity minus 20, and capacity is above the initial, decrease capacity by 20
    if (q->capacity > INITIAL_CAPACITY && q->size < q->capacity - INCREMENT) {
        int new_capacity = q->capacity - INCREMENT;
        if (new_capacity < INITIAL_CAPACITY) {
            new_capacity = INITIAL_CAPACITY;
        }
        QueueResize(q, new_capacity);
    }

    return dequeued_value;
}

// Function to get the front element of the queue
int QueueFront(Queue *q) {
    if (QueueIsEmpty(q)) {
        printf("Queue is empty\n");
        exit(EXIT_FAILURE);
    }
    return q->items[q->front];
}

// Function to get the rear element of the queue
int QueueRear(Queue *q) {
    if (QueueIsEmpty(q)) {
        printf("Queue is empty\n");
        exit(EXIT_FAILURE);
    }
    return q->items[q->rear];
}

// Function to free the allocated memory
void QueueFree(Queue *q) {
    free(q->items);
    q->items = NULL;
}

// Function to print all the elements in the queue
void QueuePrint(Queue *q) {
    if (QueueIsEmpty(q)) {
        printf("Queue is empty\n");
        return;
    }
    printf("Queue elements are:\n");
    for (int i = 0; i < q->size; i++) {
        printf("%d ", q->items[(q->front + i) % q->capacity]);
    }
    printf("\n");
}
