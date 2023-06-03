 #include<stdio.h>
#include<stdlib.h>

struct node
{
    int num;
    struct node *link;
};
typedef struct node *NODE;

NODE create_node()
{
    NODE newnode;
    newnode=(NODE)malloc(sizeof(struct node));
    if(newnode==NULL)
    {
        printf("Node not created\n");
        exit(0);
    }
    printf("Enter the number\n");
    scanf("%d",&newnode->num);
    newnode->link=NULL;
    return newnode;
}

NODE insert_end(NODE head)
{
    NODE newnode,cur;
    newnode=create_node();
    if(head==NULL)
        head=newnode;
    else
    {
        cur=head;
        while(cur->link!=NULL)
            cur=cur->link;
        cur->link=newnode;
    }
    return head;
}

NODE insert_front(NODE head)
{
   NODE cur,newnode;
   newnode=create_node();
   if(head==NULL)
        head=newnode;
   else
   {
       cur=head;
       newnode->link=cur;
       head=newnode;
   }
   return head;
}

NODE delete_front(NODE head)
{
    NODE cur;
    if(head==NULL)
        printf("List is empty\n");
    else if(head->link==NULL)
    {
        free(head);
        head=NULL;
    }
    else
    {
        cur=head;
        printf("Deleted %d\n",cur->num);
        head=cur->link;
        free(cur);
    }
    return head;
}

NODE delete_end(NODE head)
{
    NODE cur,prev;
    if(head==NULL)
        printf("List is empty\n");
    else if(head->link==NULL)
    {
        free(head);
        head=NULL;
    }
    else
    {
        prev=NULL;
        cur=head;
        while(cur->link!=NULL)
        {
            prev=cur;
            cur=cur->link;
        }
        printf("Deleted %d\n",cur->num);
        prev->link=NULL;
        free(cur);
    }
    return head;
}

int count_nodes(NODE head)
{
    NODE cur;
    int c=0;
    cur=head;
    while(cur!=NULL)
    {
        c++;
        cur=cur->link;
    }
    return c;
}

NODE insert_position(NODE head)
{
    int c,pos,i;
    NODE cur,prev,newnode;
    c=count_nodes(head);+
    printf("Enter the position you want to insert a number\n");
    scanf("%d",&pos);
    if(head==NULL)
    {
        newnode=create_node();
        head=newnode;
    }
    else if(pos==1&&head==NULL)
        head=insert_front(head);
    else if(pos==1)
        head=insert_front(head);
    else if(pos>1&&pos<=c)
    {
        newnode=create_node();
        prev=NULL;
        cur=head;
        for(i=0;i<pos-1;i++)
        {
            prev=cur;
            cur=cur->link;
        }
        prev->link=newnode;
        newnode->link=cur;
    }
    else if(pos>c)
        head=insert_end(head);
    else
        printf("Invalid position\n");
    return head;
}

NODE delete_position(NODE head)
{
    NODE cur,prev;
    int c,pos,i;
    c=count_nodes(head);
    printf("Enter the position you want to delete\n");
    scanf("%d",&pos);
    if(head==NULL)
        printf("List is empty\n");
    else if(pos==1&&head->link==NULL)
        head=delete_front(head);
    else if(pos==1)
        head=delete_front(head);
    else if(pos>1&&pos<c)
    {
        prev=NULL;
        cur=head;
        for(i=0;i<pos-1;i++)
        {
            prev=cur;
            cur=cur->link;
        }
        printf("Deleted %d\n",cur->num);
        prev->link=cur->link;
        free(cur);
    }
    else if(pos==c)
        head=delete_end(head);
    else
        printf("Invalid position\n");
    return head;
}

void display_list(NODE head)
{
    NODE cur;
    printf("The singly linked list is\n");
    cur=head;
    if(head==NULL)
        printf("List is empty\n");
    while(cur!=NULL)
    {
        printf("%d ",cur->num);
        cur=cur->link;
    }
}

int main()
{
    NODE head;
    head=NULL;
    int ch;
    while(1)
    {
        printf("1.Insert front 2.Insert end 3.Delete front 4.Delete end 5.Insert specific position 6.Delete specific position ");
        printf("7.Display list 8.Exit\n");
        printf("Enter your choice\n");
        scanf("%d",&ch);
        switch(ch)
        {
            case 1:head=insert_front(head);
                   break;
            case 2:head=insert_end(head);
                   break;
            case 3:head=delete_front(head);
                   break;
            case 4:head=delete_end(head);
                   break;
            case 5:head=insert_position(head);
                   break;
            case 6:head=delete_position(head);
                   break;
            case 7:display_list(head);
                   printf("\n");
                   break;
            case 8:exit(0);
                   break;
            default:printf("Invalid Input\n");
                    break;
        }
    }
    return 0;
}
