#include<stdio.h>
#include<string.h>
#include<stdlib.h>

int check(char *a);
char * next_string(char *str,int *start);


void export(char *filename, int sheet[][10]){
    FILE *f = fopen(filename,"w+");
    for(int i = 0; i < 10; i++)
    {
        for(int j = 0; j < 10; j++){
            fprintf(f,"%d", sheet[i][j]);
            if(j!=9)
            fprintf(f,", ");
        }
        fprintf(f,"\n");
    }
    fclose(f);
    printf("Exported Succesfully\n");
}

int get(char *s, int sheet[][10]){
    int col = s[0] - 65;
    int row = s[1] - '0';
    return sheet[row][col];
}

void set(char *s,int val,int sheet[][10]){

    int col = s[0] - 65;
    int row = s[1] - '0';
    sheet[row][col] = val;
    printf("Value Set");
}


void print(int sheet[][10]){
    int i,j;
    printf("Excel Sheet: \n");
    printf("   ");
    for(i = 0; i<10;i++)
    printf("%c  ", i + 'A');
    printf("\n");
    for(i = 0; i < 10; i++){
        printf("%d   ", i);
        for(j = 0; j < 10; j++)
        {
            printf("%d ",sheet[i][j]);
            if(j!=9)
            printf(",");
        }
        printf("\n");
    }
}

void import(char *filename,int sheet[][10]){
    int i = 0, j = 0;
    FILE *f = fopen(filename,"r");
    for(i =0;i<10;i++)
    for(j =0;j<10;j++)
    fscanf(f,"%d,",&sheet[i][j]);
    fclose(f);
}

int main(){
    char input[100];
    int a[10][10] = {0}, v;
   
    char *given, *token, *temp;
    printf("\n\n\n--------------------Excel version 1.0----------------------------\n\n\n");
    while (1)
    {
        fflush(stdin);
        printf(">> ");
        scanf("%[^\n]s", input);
        int i = 0;
        int cmd_type = check(next_string(input,&i));

        switch (cmd_type)
        {
        case 1:
            printf("%d ", get(next_string(input,&i),a));
            break;
        case 2:
        temp =  next_string(input,&i);
        v = atoi(next_string(input,&i));
        set(temp,v,a);break;
        case 3: print(a);break;
        case 4: import(next_string(input,&i),a);break;
        case 5: export(next_string(input,&i),a);break;
        case 0: exit(0);
        default: printf("Invalid Command or Syntax");
            break;
        }
        printf("\n");
    }
    return 0;
}

char * next_string(char *str,int *start){
    
    char *string = (char *)malloc(sizeof(char)*100);
    int i = 0;
    int j = *start;
    
    while((str[j] != '\0') && (str[j] != ' '))
    {
        string[i] = str[j];
        j++;
        i++;
    }
    string[i] = '\0';
    *start = j+1;
    
    return string;
}

int check(char *a){
    if(strcmpi(a,"get")==0)
    return 1;
    if(strcmpi(a,"set")==0)
    return 2;
    if(strcmpi(a,"print")==0)
    return 3;
    if(strcmpi(a,"import")==0)
    return 4;
    if(strcmpi(a,"export")==0)
    return 5;
    if(strcmpi(a,"exit")==0)
    return 0;
    return -1;
}