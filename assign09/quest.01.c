#include <stdio.h>
#include <stdlib.h>

struct node {
    int data;
    struct node*parent;
    struct node*next;
};

struct pool {
    int key;
    struct node*value;
    struct pool*left;
    struct pool*right;
};
struct pool *head=NULL;

struct pool*createpool(int key,struct node*value){
    struct pool*tmp=(struct pool*)malloc(sizeof(struct pool));
    tmp->key=key;
    tmp->value=value;
    tmp->left=NULL;
    tmp->right=NULL;
    return tmp;
}

void insert(int key, struct node*value){ // O(logn)
    if(head==NULL){
        head=createpool(key,value);
    }
    else {
        struct pool*child=head,*parent=NULL;
        for(;child!=NULL;)
        {
            parent=child;
            if(key <=child->key)
                child=child->left;
            else if(key > child->key)
                child=child->right;
        }
        if(key<=parent->key)
            parent->left=createpool(key,value);
        else if(key > parent->key)
            parent->right=createpool(key,value);
    }
}

struct node*get(int data){ //O(logn)
    struct pool*child=head;
    for(;child!=NULL;){
        if(data == child->key)
            return child->value;
        if(data < child->key)
            child=child->left;
        else if(data > child->key)
            child=child->right;
    }
    return NULL;
}

struct node*createnode(int data){
    struct node*tmp=(struct node*)malloc(sizeof(struct node));
    tmp->data=data;
    tmp->next=NULL;
    tmp->parent=NULL;
    return tmp;
}

void makeset(int data){
    struct node*tmp=createnode(data);
    tmp->parent=tmp;
    insert(data,tmp);
}

struct node*findset(struct node*item){
    return item->parent;
}
void unionset(int data1,int data2){
    struct node*n1=get(data1);
    struct node*n2=get(data2);
    struct node*p1=findset(n1);
    struct node*p2=findset(n2);
    if(p1->data==p2->data)
        return;
    struct node*tmp=p1;
    for(;tmp->next!=NULL;tmp=tmp->next);
    tmp->next=p2;
    tmp=p2;
    for(;tmp!=NULL;tmp=tmp->next){
        tmp->parent=p1;
    }
}

void printset(int data){
    struct node*parent=findset(get(data));
    printf("{ ");
    for(;parent!=NULL;parent=parent->next){
        printf("%d ",parent->data);
    }
    printf("}");
    printf("\n");
}

int main(){
    int n,data,k1,k2;
    scanf("%d",&n);
    while(n--){
        scanf("%d",&data);
        makeset(data);
    }
    scanf("%d%d",&k1,&k2);
    printset(k1);
    printset(k2);
    unionset(k1,k2);
    printset(k1);
    printset(k2);
    printf("\n");
}
