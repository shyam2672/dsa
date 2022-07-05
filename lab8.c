#include<stdio.h>
#include<stdlib.h>
struct node{
    int data;
    struct node* next;
};

struct list{
    struct node* head;
};

struct graph{
    int v;
    struct list* arr;
};

struct node* createnode(int data){
    struct node* temp=malloc(sizeof(struct node));
    temp->data=data;
    temp->next=NULL;
    return temp;
}

struct graph* creategraph(int v){
    struct graph* gr=malloc(sizeof(struct graph));
    gr->v=v;
    gr->arr=(struct list*)malloc(v*sizeof(struct list));
    for(int i=0;i<v;i++){
        gr->arr[i].head=NULL;
    }
    return gr;
}

void addedgedirected(struct graph* gr,int u,int v){
    struct node* temp;
    temp=createnode(v);

    
    temp->next=gr->arr[u].head;
    gr->arr[u].head=temp;

}
void addedgeundirected(struct graph* gr,int u,int v){
    struct node* temp;
    temp=createnode(v);
    temp->next=gr->arr[u].head;
    gr->arr[u].head=temp;
    
    temp=createnode(u);
    temp->next=gr->arr[v].head;
    gr->arr[v].head=temp;
}
void display(struct graph* gr){
    for(int i=0;i<gr->v;i++){
        struct node* temp=gr->arr[i].head;
        struct node* p=gr->arr[i].head;
        printf("vertex %d: ",i);
        while(temp!=NULL){
         printf("%d",temp->data);
         if(temp->next!=NULL)
         printf("->");
         temp=temp->next;
        }
        
         printf("\n");
        
    }
}
int main(){
    int v;
    printf("enter the number of vertices\n");
    scanf("%d",&v);
   
    struct graph* gr=creategraph(v);
    char c;
     
    
    printf("enter D for directed graph and U for undirected graph\n");
    scanf(" %c",&c);
    if(c=='U'){
        printf("enter edges one by one, press E to enter and Q to stop entering edges\n");
         char p;
        while(1)
       {
        scanf(" %c",&p);
        
        if(p=='Q'){break;}
        int u,v;
        
        scanf(" %d %d",&u,&v);
      
        addedgeundirected(gr,u,v);
       
       }
       printf("your undirected graph is as follows\n");
       display(gr);
       return 0;
    }
    else if(c=='D'){
         printf("enter edges one by one, press E to enter and Q to stop entering edges\n");
         char p;
        while(1)
       {
        scanf(" %c",&p);
        
        if(p=='Q'){break;}
        int u,v;
        
        scanf(" %d %d",&u,&v);
      
        addedgedirected(gr,u,v);
       
       }
       printf("your directed graph is as follows\n");
       display(gr);
       return 0;
    }
   
}