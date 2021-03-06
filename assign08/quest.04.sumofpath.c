#include <stdio.h>
#include <stdlib.h>

struct node {
    int data;
    struct node*left;
    struct node*right;
};

struct node*createnode(int data){
    struct node*tmp=(struct node*)malloc(sizeof(struct node));
    tmp->data=data;
    tmp->left=NULL;
    tmp->right=NULL;
    return tmp;
}

void insert(struct node**root,int data){
    struct node*new_node=createnode(data);
    if(*root==NULL)
        *root=new_node;
    else
    {
        struct node*parent=NULL,*child=*root;
        for(;child!=NULL;){
            parent=child;
            if(data <= child->data)
                child=child->left;
            else child=child->right;
        }
        if(data <= parent->data)
            parent->left=new_node;
        else
            parent->right=new_node;
    }
}

void inorder_traversal(struct node*root){
    if(root){
        inorder_traversal(root->left);
        printf("%d ",root->data);
        inorder_traversal(root->right);
    }
}

struct stack {
    struct node *list;
    struct stack *next;
};

struct stack*create(struct node*root){
    struct stack*tmp=(struct stack*)malloc(sizeof(struct stack));
    tmp->list=root;
    tmp->next=NULL;
    return tmp;
}
void push(struct stack**top,struct node*root){
    struct stack*tmp=create(root);
    if(*top==NULL){
        *top=tmp;
    }
    else {
        tmp->next=*top;
        (*top)=tmp;
    }
}
struct node* pop(struct stack**top){
    if(*top==NULL)
        return NULL;
    else
    {
        struct stack*tmp=*top;
        struct node*bst_node=(*top)->list;
        (*top)=(*top)->next;
        free(tmp);
        return bst_node;
    }
}

int print(struct stack*s){
    if(s){
        return print(s->next)+s->list->data;
    }
    return 0;
}
void post_order(struct node*root,struct stack**s){
    if(root){
        push(s,root);
        post_order(root->left,s);
        post_order(root->right,s);
        if(root->left==root->right){
            printf("%d\n",print(*s));
        }
        pop(s);
    }
}

int main(){
    struct node*root=NULL;
    struct stack*s=NULL;
    int n,data;
    scanf("%d",&n);
    while(n--) {scanf("%d",&data); insert(&root,data);}
    post_order(root,&s);
    return 0;
}
