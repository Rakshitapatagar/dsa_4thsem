#include<stdio.h>

#include<stdlib.h>

int main()

{

    FILE *fp1,*fp2;

    int k=0,l=0,i=0,m,q;

    char str[10][1000],temp[1000],key1[1000],key2[1000];

    fp1=fopen("input.txt.txt","r");

    fp2=fopen("output.txt","w");

    printf("key1 to search\n");

    scanf("%s",&key1);

    printf("key2 to insrt\n");

    scanf("%s",&key2);

    if(fp1==NULL)

    {

        printf("File does not exist.\n");

        exit(0);
    }

    //fputs("The lines containing the pattern 'ould' are\n",fp2);

    while(!feof(fp1))

    {

       fgets(str[i],1000,fp1);

       //fgets(key1[i],1000,fp1);

       //fgets(key2[i],1000,fp1);

       q=0;

       while(str[i][q]!='\0')

       {

           if(str[i][q]==key1[i]&&str[i][q+1]==key1[i+1]&&str[i][q+2]==key1[i+2])

           {

             // puts(str[i]);

             str[i][q]=key2[i];

             str[i][q+1]=key2[i+1];

             str[i][q+2]=key2[i+2];

            // str[i][q+3]=key2[i+3];

            //fputs(str[i],fp2);

              l++;

           }

            q++;

       }

       fputs(str[i],fp2);

    }

/*if(l==0)

    {

        printf("ZERO.There are no lines with 'key1' pattern\n");

        fputs("ZERO.There are no lines with '' pattern\n",fp2);

    }*/

    fclose(fp1);

    fclose(fp2);

    return 0;
}
