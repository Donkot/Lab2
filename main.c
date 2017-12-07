#include <stdio.h>
#include <stdlib.h>
char buffer[256];
FILE *file = NULL;
int get_code(char * word);
struct Cell{
    unsigned char data;
    struct Cell* right;
    struct Cell* left;
};
struct Cell * cell;
void process_command(int code);
int process_line();
int main(int argc, char *argv[])
{
    cell = (struct Cell*)malloc(sizeof(struct Cell));
    cell -> left = NULL;
    cell -> right = NULL;
    cell -> data = 0;
    if (argc !=  2)
        printf("No correct filename was entered");
    else file = fopen(argv[1], "r");
    if(file)
        {
            while(!feof(file)){
                process_command(process_line());
            }
    }
    else
        printf("\n Error with opening file");
    fclose(file);
    return 0;
}
int process_line(){
    int index = 0;
    if(!feof(file)){
        fgets(buffer, sizeof(buffer), file);
        while((buffer[index] == '\t') || (buffer[index] == ' '))
                    index++;
        return get_code(buffer + index);
    }
    return 0;
}
int get_code(char * word){
    if((word[0] == 'm') && (word[3] == 'l'))/*movl*/
        return 1;
    if((word[0] == 'm') && (word[3] == 'r'))/*movr*/
        return 2;
    if (word[0] == 'i')/*inc*/
        return 3;
    if (word[0] == 'd')/*dec*/
        return 4;
    if((word[0] == 'p') && (word[5] == 'c'))/*printc*/
        return 7;
    if(word[0] == 'p')/*print*/
        return 5;
    if(word[0] == 'g')/*get*/
        return 6;
    if(word[0] == 'b')/*begin*/
        return 8;
    if(word[0] == 'e')/*end.*/
        return 9;
    return 0;
}
void process_command(int code){
    switch(code){
    case 1:/*movl*/
        if(cell -> left != NULL)
            cell = cell -> left;
        else{
            struct Cell* temp = cell;
            cell -> left = (struct Cell*)malloc(sizeof(struct Cell));
            cell = cell -> left;
            cell -> data = 0;
            cell -> right = temp;
            cell -> left = NULL;
        }
        break;
    case 2:/*movr*/
        if(cell -> right != NULL)
            cell = cell -> right;
        else{
            struct Cell* temp = cell;
            cell -> right = (struct Cell*)malloc(sizeof(struct Cell));
            cell = cell -> right;
            cell -> left = temp;
            cell -> data = 0;
            cell -> right = NULL;
        }
        break;
    case 3:/*inc*/
        if (cell -> data == 255){
            cell -> data = 0;
            printf("cell data is too large\n");
        }else
            cell -> data++;
        break;
    case 4:/*dec*/
        if(cell -> data != 0)
            cell -> data --;
        break;
    case 5:/*print*/
        printf("%d\n", cell -> data);
        break;
    case 6:/*get*/
        {
            printf("Please enter a number (0..255): ");
            unsigned int temp;
            scanf("%u", &temp);
            cell -> data = temp;
            printf("\n");
        }
        break;
    case 7:/*printc*/
        printf("%c\n", (cell -> data));
        break;
    case 8:/*begin*/
        {
            int i = 0;
            char s[256];
            s[0] = process_line();
            while((s[i] != 9) && (!feof(file))){
                process_command(s[i]);
                i++;
                s[i] = process_line();
            }
            int max = i;/
            while(cell -> data){
                for(i = 0; i < max; i++){
                    process_command(s[i]);
                }
            }
        }
        break;
    }
}
