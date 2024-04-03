#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include "scanner.h"


//Author: Jarod Stagner
//Date: 03/12/2024

void help(){
        printf("Incorrect Usage\nHere are the valid ways to run this program:\n./Project1 [filename]\n");
        printf("./Project1\n./Project1 < [filename]\nDoing the second option will let the user enter in code until they enter the EOF command CTRL+D\n");
        printf("The program will then tokenize the code in the file and output it to the screen\n");
}

int main(int argc, char** argv) {

        FILE *file;
        char buffer[100];

        if(argc > 2){//if invalid

                help();
                return EXIT_FAILURE;

        }else if(argc == 2){//if file input

                file = fopen(argv[1],"r");

        }else{//if stdin

                file = fopen("tempfile.txt", "w+");

                while (fgets(buffer, sizeof(buffer),stdin) != NULL){
                        fputs(buffer, file);
                }

                fseek(file, 0, SEEK_SET);

        }

        if(file == NULL){
                printf("Problem with given file... exiting\n");
                return EXIT_FAILURE;
        }
        fseek(file, 0, SEEK_END);
        if(ftell(file) == 0){
                fclose(file);
                printf("Given file is empty... exiting\n");
                return EXIT_FAILURE;
        }else{
                fseek(file, 0, SEEK_SET);
        }

        FILE *filterfile;
        filterfile = fopen("filteredFile.txt", "w+");
        filter(file,filterfile);
        fseek(filterfile, 0, SEEK_SET);

        struct Token* tokenList = scanner(filterfile);
        displayTokenList(tokenList);

        parser(tokenList);

        while(tokenList != NULL){
                struct Token* temp = tokenList;
                tokenList = tokenList->next;
                free(temp);
        }

        fclose(file);
        fclose(filterfile);

        return;
}
