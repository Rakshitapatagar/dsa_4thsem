#include<stdio.h>

void read(int a[100][100],int m,int n);
void print(int a[100][100],int m,int n);
void symmetric(int a[100][100],int m,int n);

int main()
{
    int m,n,a[100][100],b[100][100];
    printf("enter the number of rows and coloumn\n");
    scanf("%d %d",&m,&n);
    read(a,m,n);
    print(a,m,n);
    symmetric(a,m,n);


}

void read(int a[100][100],int m,int n)
{
    printf("matrix elements are ");
    for (int i=0;i<m;i++)
    {
        for(int j=0;j<n;j++)
        {
            scanf("%d",&a[i][j]);
        }
    }
}
void print(int a[100][100],int m,int n)
{
    for(int i=0;i<m;i++)
    {
        for(int j=0;j<n;j++)
        {
            printf("%d ",a[i][j]);
        }
        printf("\n");
    }
}
void symmetric(int a[100][100],int m,int n)
{
    int s=0;
    int b[100][100];
    for(int i=0;i<m;i++)
    {
        for(int j=0;j<n;j++)
        {
            b[i][j]=a[j][i];
        }
    }
    for(int i=0;i<m;i++)
    {
        for(int j=0;j<n;j++)
        {
            printf("%d ",b[i][j]);
        }
        printf("\n");
    }
    for(int i=0;i<m;i++)
    {
        for(int j=0;j<n;j++)
        {
           if(b[i][j]==a[i][j])
             s++;
        }
    }
            if(s==(m*n))
            {
                printf("symmetric");
            }
            else

                printf("not symmetric");

}


