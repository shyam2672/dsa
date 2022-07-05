#include <stdio.h>
#include <stdlib.h>

struct node{
    int key;
    struct node* prev;
    struct node* next;
};

struct hashtableitem{
    
    struct node* head;
    struct node* tail;
    
};
struct hashtableitem* arr;
struct hashtable{
    
    int size;
    int capacity;
};

struct hashtable* generatehashtable(int capacity){
     struct hashtable* temp=malloc(sizeof(struct hashtable));
     temp->size=0;
     temp->capacity=capacity;
     //printf("lsd");
     return temp;
}

int hashvalue(struct hashtable* table,int k){
    return k%table->capacity;
}
int search(struct node* chain,int key){
    int temp=0;
    while(chain!=NULL){
        if(chain->key==key)
        return temp;
        chain=chain->next;
        temp++;
    }
    return -1;
}
struct node* get_element(struct node* chain,int index){
    int p=0;
  
    if(index<0)
    return NULL;
    else
    {
        struct node* temp=chain;
        while(p!=index && temp!=NULL){
            temp=temp->next;
            p++;
        }
        return temp;
    }
}

void insert(struct hashtable** table,int key){
   
    int index=hashvalue(*table,key);
    printf("%d",index);
    struct node* chain=arr[index].head;
 printf("lsd");
    struct node* item=malloc(sizeof(struct node));
    item->key=key;
   printf("lsd");
    item->prev=NULL;
    item->next=NULL;
    if(chain==NULL){
        arr[index].head=item;
        arr[index].tail=item;
          (*table)->size++;
    }
    else
    {
        int find=search(chain,key);
        if(find==-1){
            item->prev=arr[index].tail;
            arr[index].tail->next=item;
            arr[index].tail=item;
            (*table)->size++;
        }
        else{
            printf("element is already present\n");
        }
    }
}

void delete(struct hashtable* table,int key){
    int index=hashvalue(table,key);
    struct node* chain=arr[index].head;
    int i=search(chain,key);
    if(i==-1){
        printf("element does not exist\n");
        return ;
    }
    else{
    struct node* temp=chain;
    if(temp->key==key){
        arr[index].head=temp->next;
        arr[index].head->prev=NULL;
        free(temp);
        table->size--;
        return;
    }
    else{
        while(temp->key!=key){
            temp=temp->next;
        }
        if(arr[index].tail==temp){
            temp->prev->next=NULL;
            arr[index].tail=temp->prev;
            free(temp);
            table->size--;
            return;
        }
        else{
            temp->prev->next=temp->next;
            temp->next->prev=temp->prev;
            free(temp);
            table->size--;
            return;
        }
    }
    }

}

void display(struct hashtable* table){
    for(int i=0;i<table->capacity;i++){
        struct node* temp=arr[i].head;
    if(temp==NULL)
    printf(" INDEX %d: NULL\n",i);
    else{
        printf(" INDEX %d: ",i);
        while(temp!=NULL){
            printf("%d ",temp->key);
            temp=temp->next;
        }
        printf("\n");
    }
    }
 }
int main(){
    int m;
    printf("enter hash table size m: \n");
    scanf("%d ",&m);

   struct hashtable* table=generatehashtable(m);
   insert(&table,10);
   display(table);
   /*int choice;
   while(1){
       printf("1. Insert\n2. Delete\n3. Search\n4.Display\n5. Quit\n");
       printf("enter your choice: ");
       scanf("%d",&choice);
       if(choice==1){
           printf("enter value to insert: ");
           int d;
           scanf("%d",&d);
           insert(table,d);
           printf("\n");
       }
       if(choice==2){
           printf("enter the element you want to delete: ");
           int d;
           scanf("%d",&d);
           delete(table,d);
           printf("\n");
       }
       if(choice==3){
           printf("enter the element to be searched: ");
           int d;
           scanf("%d",&d);
           int index=hashvalue(table,d);
           struct node* chain=arr[index].head;
           search(chain,d);
       }
       if(choice==4){
           display(table);
       }
       if(choice==5){
           return 0;
       }
   }
   */
}