
#include<stdio.h>
#define SIZE 10
#include<stdlib.h>

 struct stack
 {
     int data[SIZE];
     int top;
 };
 void push(struct stack *sptr,int element);
 int pop(struct stack *sptr);
 int peek(struct stack *sptr);
 void display(struct stack *sptr);
  void display2(struct stack *sptr);

 int main()
 {
     FILE *fp1;
     FILE *fp4;
     struct stack s;
     struct stack *sptr;
     int ch,element;
     sptr=&s;
     sptr->top=-1;
     int data[SIZE],i,f,l,n;
      printf("enter the size of the array\n");
      scanf("%d",&n);
    printf("enter the elements in the array\n");
    printf("enter the higher and lower limit\n");
    scanf("%d%d",&f,&l);

     while(1)
     {
         printf("stack member\n");
         printf("1.PUSH 2.DISPLAY 3.POP 4.display2\n");
         printf("enter the choice\n");
         scanf("%d",&ch);
         switch(ch)
         {
             case 1:
              fp1=fopen("pushed.txt","w");
         for(i=0;i<n;i++)
       {
          data[i]=rand()%(l+f-1);
          fprintf(fp1,"%d",element);
            push(sptr,data[i]);
         fprintf(fp1,"%d ",data[i]);
          printf("%d ",data[i]);
       }
             // printf("enter the elements to push\n");
              //scanf("%d",&element);
              fclose(fp1);
             break;
              case 2:display(sptr);
             break;
             case 3:fp4=fopen("popped.txt","w");
                 element=pop(sptr);
             if(element==-1)
             {
                 printf("stack overflowed\n");

             }
             else
             {
                 printf("popped element %d\n",element);
                 fprintf(fp4,"%d",element);
                 fclose(fp4);
             }
             break;
              case 4:display2(sptr);
             break;
             case 5:exit(0);
             break;
             default:printf("invalid choice\n");
             break;
        }
     }
     return 0;
 }
 void push(struct stack *sptr,int element)
{
     if(sptr->top==SIZE-1)
    {
       printf("stack overflowed\n");
    }
     else
    {
        sptr->top++;
        sptr->data[sptr->top]=element;
    }
}
void display(struct stack *sptr)
 {
     FILE *fp3;
     fp3=fopen("stack.txt","w");
     int i;
     if(sptr->top==-1)
     {
         printf("stack is empty\n");
     }
     else
     {
         for(i=sptr->top;i>=0;i--)
         {
             printf("%d\n",sptr->data[i]);
             fprintf(fp3,"%d",sptr->data[i]);
         }
         fclose(fp3);
     }
 }
 int pop(struct stack *sptr)
 {
     int element;
     if(sptr->top==-1)
     {
         return -1;
     }
     else
     {
         element=sptr->data[sptr->top];
         sptr->top--;
      }
      return element;
 }

  void display2(struct stack *sptr)
 {
     FILE *fp4;
     fp4=fopen("stack2.txt","w");
     int i;
     if(sptr->top==-1)
     {
         printf("stack is empty\n");
     }
     else
     {
         for(i=sptr->top;i>=0;i--)
         {
             printf("%d\n",sptr->data[i]);
             fprintf(fp4,"%d",sptr->data[i]);
         }
         fclose(fp4);
     }
 }
