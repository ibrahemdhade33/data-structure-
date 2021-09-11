#include <stdio.h>
#include <malloc.h>
#include <aclapi.h>
#define maxchar 100
//define a struct with next and pre
//the pre is for printing
struct node{
    char comand[maxchar];
   struct node *next;
   struct node *pre;
}node;
//define all nodes we need
struct node *top=NULL;
struct node *tail=NULL;
struct node *top1=NULL;


int len=0,len1=0;
//is empty function
int isempty(int  flag){
    if(flag==0)
    return len==0;
    else
        return len1==0;
}
//push function with flags
//flag 1 push for the redo stack and flag 0 push for undo stack
void push(char element[],int flag){
    struct node *newnode;
    if(flag==0) {
        newnode = (struct node *) malloc(sizeof(struct node));
        strcpy(newnode->comand, element);
        if (isempty(0)) {

            newnode->next = NULL;
            newnode->pre = NULL;
            top = tail = newnode;
            len++;

        } else {
            newnode->next = top;
            top->pre = newnode;
            newnode->pre = NULL;

            top = newnode;
            len++;
        }
    }
    else {
        newnode = (struct node *) malloc(sizeof(struct node));
        strcpy(newnode->comand, element);
        if (isempty(1)) {
            newnode->next = NULL;
            newnode->pre = NULL;
            top1  = newnode;
            len1++;
        } else {
            newnode->next = top1;
            top1 = newnode;
            len1++;
        }
    }
}
//function pop with flag0 for undo and with flag 1 for redo
void pop(int flag){
    if (flag==0){
        push(top->comand,1);
        struct node *temp=top;
        top=top->next;
        if(top!=NULL)
        top->pre=NULL;
        else
            tail=NULL;
        free(temp);
len--;
    }
    else {
        push(top1->comand,0);
        struct node *temp=top1;
        top1=top1->next;
        if(top1!=NULL)
        top1->pre=NULL;
        free(temp);
        len1--;
    }
}
//print the stack as we enter using tail
void print(){
    struct node *temp=tail;
    while (temp!=NULL){
        printf("%s\n",temp->comand);
temp=temp->pre;
    }
}
//main function and menu
int main() {
int todo;
struct node *temp;
    char comand[maxchar]="";
FILE *out= fopen("output.txt","a+");
    printf("welcome to our program, please chose from the menu  : \n"
           "1- enter a new command : \n"
           "2- undo : \n"
           "3- redo : \n"
           "4- print the commands : \n"
           "5- save the commands to file : \n"
           "6- exit from the program : \n");
    scanf("%d",&todo);
    while (todo >=1){
        switch (todo) {
            case 1:
                gets(comand);
                scanf("%s",comand);
                push(comand,0);
                print();

                break;
            case 2:
                if(top==NULL)
                    printf("there is no string to remove\n");
                else{
                pop(0);
                print();
                }
                break;
            case 3:
                if(top1==NULL)
                     printf("there is no string to redo it\n");
                else {
                pop(1);
                print();
                }
                break;
            case 4:
                print();
                break;
            case 5:
                temp =tail;
                fprintf(out,"your data is : \n ");
                while(temp!=NULL){
                    fprintf(out,"%s\n",temp->comand);
                    temp=temp->pre;
                }
                fclose(out);
                break;
            case 6:
                exit(1);
            default:
                printf("out of range please chose from the menu again \n");
                break;
        }
        printf("welcome to our program, please chose from the menu  : \n"
               "1- enter a new command : \n"
               "2- undo : \n"
               "3- redo : \n"
               "4- print the commands : \n"
               "5- save the commands to file : \n"
               "6- exit from the program : \n");
        scanf("%d",&todo);
    }
    printf("Hello, World!\n");
    return 0;
}
