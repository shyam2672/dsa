// NAME: SHYAM PRAJAPATI
//ENTRY NUMBER: 2020CSB1110
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
//IMPLEMENTING QUEUE
struct queue
{
    int front, rear, size, capacity;
    int *array;
};
struct queue *createqueue(unsigned capacity)
{
    struct queue *temp = (struct queue *)malloc(sizeof(struct queue));
    temp->capacity = capacity;
    temp->front = temp->size = 0;
    temp->rear = capacity - 1;
    temp->array = (int *)malloc( temp->capacity * sizeof(int));
    return temp;
}
int isEmpty(struct queue *queue)
{
    return (queue->size == 0);
}
int isFull(struct queue *queue)
{
    return (queue->size == queue->capacity);
}
// Function to add an item to the QUEUE
void enqueue(struct queue *queue, int item)
{
    if (isFull(queue))
        return;
    queue->rear = (queue->rear + 1) % queue->capacity;
    queue->array[queue->rear] = item;
    queue->size = queue->size + 1;
}

// Function to remove an item from queue.
int dequeue(struct queue *queue)
{
    if (isEmpty(queue))
        return INT_MIN;
    int item = queue->array[queue->front];
    queue->front = (queue->front + 1) % queue->capacity;
    queue->size = queue->size - 1;
    return item;
}

// Function to get front of queue
int front(struct queue *queue)
{
    if (isEmpty(queue))
        return INT_MIN;
    return queue->array[queue->front];
}
// STRUCTURE OF EACH VERTEX OF THE GRAPH
struct node
{
    int data;
    struct node *next;
};
//LIST OF ADJACENT ELEMENTS OF EACH VERTEX
struct list
{
    struct node *head;
};
//ARRAY OF ADJACENT VERTEX LISTS
struct graph
{
    int v;
    struct list *arr;
};
//FUNCTION TO CREATE A NODE
struct node *createnode(int data)
{
    struct node *temp = malloc(sizeof(struct node));
    temp->data = data;
    temp->next = NULL;

    return temp;
}
// FUNCTION TO CREATE A GRAPH
struct graph *creategraph(int v)
{
    struct graph *gr = malloc(sizeof(struct graph));
    gr->v = v;
    gr->arr = (struct list *)malloc(v * sizeof(struct list));
    //CREATING AN EMPTY GRAPH
    for (int i = 0; i < v; i++)
    {
        gr->arr[i].head = NULL;
    }
    return gr;
}
//FUNCTION TO ADD AN EDGE IN DIRECTED GRAPH
void addedgedirected(struct graph *gr, int u, int v)
{
    struct node *temp;
    temp = createnode(v);

    temp->next = gr->arr[u].head;
    gr->arr[u].head = temp;
}
//FUNCTION TO ADD AN EDGE IN UNDIRECTED GRAPH
void addedgeundirected(struct graph *gr, int u, int v)
{
    struct node *temp;
    temp = createnode(v);
    temp->next = gr->arr[u].head;
    gr->arr[u].head = temp;

    temp = createnode(u);
    temp->next = gr->arr[v].head;
    gr->arr[v].head = temp;
}
//FUNCTION TO DISPLAY THE GRAPH
void display(struct graph *gr)
{
    for (int i = 0; i < gr->v; i++)
    {   
        struct node *temp = gr->arr[i].head;

        printf("vertex %d: ", i);
        while (temp != NULL)
        {
            printf("%d", temp->data);
            if (temp->next != NULL)
                printf("->");
            temp = temp->next;
        }
        printf("\n");
    }
}
//FUNCTION TO IMPLEMENT BFS
void BFS(struct graph *gr, int s)
{
    struct queue *q = createqueue(gr->v);//CREATING A QUEUE
    int V = gr->v;
    int colour[V];//ARRAY OF COLOURS.(-1 CORRESPONDS TO WHITE 0 CORRESPONDS TO GREY 1 CORRESPONDS TO BLACK) COLOUR ODF EVERY VERTEX IS STORED AT CORRESPONDING INDEX. FOR EG. COLOUR OF VERTEX 3 IS WHITE THEREFORE COLOUR[3]=-1
    int d[V];// ARRAY OF DISTANCE OF ALL VERTICES WITH RESPECT TO S
    int pre[V];//ARRAY OF PREDECESSORS OF ALL VERTICES
    //INITIALLISING ALL NODES WITH WHITE COLOUR DISTANCE INFINITY(-1 STANDS FOR INFINITY) AND PREDECESSOR INT_MIN(STANDS FOR NIL)
    for (int i = 0; i < V; i++)
    {
        colour[i] = -1;
        d[i] = -1;
        pre[i] = INT_MIN;
    }
    colour[s] = 0;
    d[s] = 0;
    enqueue(q, s);
    while (isEmpty(q) != 1)
    {
        int u = dequeue(q);
        printf(" distance of vertex %d from vertex %d is %d \n", u, s, d[u]);
        struct node *temp = gr->arr[u].head;

        while (temp != NULL)
        {

            if (colour[temp->data] == -1)//CHECK IF THE ADJACENT VERTEX IS UNACCESSED
            {
                colour[temp->data] = 0;//MARK ACCESSED VERTICES AS GREY
                d[temp->data] = d[u] + 1;//UPDATE THEIS DISTANCE
                pre[temp->data] = u;//STORE PREDECESSOR
                enqueue(q, temp->data);
            }
            temp = temp->next;
        }
        colour[u] = 1;
    }
    printf("\n");
}
int main()
{
    int v;
    printf("enter the number of vertices\n");
    scanf("%d", &v);

    struct graph *gr = creategraph(v);
    char c;

    printf("enter D for directed graph and U for undirected graph\n");
    scanf(" %c", &c);
    if (c == 'U')
    {
        printf("enter edges one by one, press any character except Q to enter and press Q to stop entering edges\n");
        char p;
        while (1)
        {
            scanf(" %c", &p);

            if (p == 'Q')
            {
                break;
            }
            int u, v;
            scanf(" %d %d", &u, &v);
            addedgeundirected(gr, u, v);
        }
        printf("your undirected graph is as follows\n");
        display(gr);
    }
    else if (c == 'D')
    {
        printf("enter edges one by one, press any character except Q to enter and press Q to stop entering edges\n");
        char p;
        while (1)
        {
            scanf(" %c", &p);

            if (p == 'Q')
            {
                break;
            }
            int u, v;

            scanf(" %d %d", &u, &v);

            addedgedirected(gr, u, v);
        }
        printf("your directed graph is as follows\n");
        display(gr);
    }

    printf("enter a vertex to run BFS with respect to\n");
    int s;
    scanf(" %d",&s);
    BFS(gr,s);
    return 0;
}