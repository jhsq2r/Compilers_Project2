#include<stdlib.h>
#include<unistd.h>
#include<stdio.h>
#include<string.h>
#include"parser.h"

struct Token* vars(struct Token* list);
struct Token* varsExtended(struct Token* list);
struct Token* block(struct Token* list);
struct Token* stats(struct Token* list);
struct Token* mStat(struct Token* list);
struct Token* stat(struct Token* list);
struct Token* program(struct Token* list);
struct Token* programExtended(struct Token* list);
struct Token* pickbody(struct Token* list);
struct Token* ro(struct Token* list);
struct Token* roExtended(struct Token* list);
struct Token* expr(struct Token* list);
struct Token* n(struct Token* list);
struct Token* nExtended(struct Token* list);
struct Token* a(struct Token* list);
struct Token* m(struct Token* list);
struct Token* r(struct Token* list);






void parser(struct Token* list){
        //printf("In parser Function...\n");
        list = program(list);
        if(strcmp(list->idTk,"EOF_TK") == 0){
                printf("Success!!!\n");
        }else{
                printf("Error in parser function\n");
        }
        return;
}

struct Token* program(struct Token* list){
        //printf("In program Function...Token: %s\n", list->tokenInstance);
        list = vars(list);
        if(strcmp(list->idTk,"KW_TK") == 0 && strcmp(list->tokenInstance,"tape") == 0){
                list = programExtended(list->next);
                return list;
        }else{
                //error expected tape
                printf("Error: Expected 'tape' got %s\n", list->tokenInstance);


        }
}

struct Token* vars(struct Token* list){
        //printf("In vars Function...Token: %s\n", list->tokenInstance);
        if(strcmp(list->idTk,"KW_TK") == 0 && strcmp(list->tokenInstance,"create") == 0){
                list = list->next;
                if(strcmp(list->idTk,"IDENT_TK") == 0){
                        list = varsExtended(list->next);
                }
        }else{
                return list;
        }
        return list;
}

struct Token* varsExtended(struct Token* list){
        //printf("In varsExtended Function...Token: %s\n", list->tokenInstance);
        if(strcmp(list->idTk,"OP_TK") == 0 && strcmp(list->tokenInstance,";") == 0){
                return list->next;
        }else if(strcmp(list->idTk,"OP_TK") == 0 && strcmp(list->tokenInstance,":=") == 0){
                list = list->next;
                if(strcmp(list->idTk,"INT_TK") == 0){
                        list = list->next;
                        if(strcmp(list->idTk,"OP_TK") == 0 && strcmp(list->tokenInstance,";") == 0){
                                list = vars(list->next);
                                return list;
                        }else{
                                //error expected ;
                                printf("Error: Expected ';' got %s\n", list->tokenInstance);


                        }
                }else{
                        //error expected INT
                        printf("Error: Expected 'INT' got %s\n", list->tokenInstance);

                }
        }else{
                //error expected ; or := INT ;
                printf("Error: Expected ';' or ':= INT' got %s\n", list->tokenInstance);


        }
}

struct Token* programExtended(struct Token* list){
        //printf("In programExtended Function...Token: %s\n", list->tokenInstance);
        if(strcmp(list->idTk,"KW_TK") == 0 && strcmp(list->tokenInstance,"func") == 0){
                list = list->next;
                if(strcmp(list->idTk,"IDENT_TK") == 0){
                        list = block(list->next);
                        list = block(list);
                        return list;
                }else{
                        //error expected IDENT_TK
                        printf("Error: Expected 'IDENT_TK' got %s\n", list->tokenInstance);


                }
        }else{
                list = block(list);
                return list;
        }
}

struct Token* block(struct Token* list){
        //printf("In block Function...Token: %s\n", list->tokenInstance);
        if(strcmp(list->idTk,"OP_TK") == 0 && strcmp(list->tokenInstance,"{") == 0){
                list = list->next;
                list = vars(list);
                list = stats(list);
                if(strcmp(list->idTk,"OP_TK") == 0 && strcmp(list->tokenInstance,"}") == 0){
                        list = list->next;
                        return list;
                }else{
                        //errpr expected }
                        printf("Error: Expected '}' got %s\n", list->tokenInstance);


                }
        }else{
                //error expected {
                printf("Error: Expected '{' got %s\n", list->tokenInstance);


        }
}

struct Token* stats(struct Token* list){
        //printf("In stats Function...Token: %s\n", list->tokenInstance);
        list = stat(list);
        list = mStat(list);
        return list;
}

struct Token* mStat(struct Token* list){
        //printf("In mStat Function...Token: %s\n", list->tokenInstance);
        if(strcmp(list->idTk,"OP_TK") == 0 && strcmp(list->tokenInstance, "}") == 0){
                return list;
        }else{
                list = stat(list);
                list = mStat(list);
                return list;
        }
}

struct Token* stat(struct Token* list){
        //printf("In stat Function...Token: %s\n", list->tokenInstance);
        if(strcmp(list->idTk,"KW_TK") == 0 && strcmp(list->tokenInstance,"label") == 0){
                list = list->next;
                if(strcmp(list->idTk,"IDENT_TK") == 0){
                        list = list->next;
                        if(strcmp(list->idTk,"OP_TK") == 0 && strcmp(list->tokenInstance,";") == 0){
                                list = list->next;
                                return list;
                        }else{
                                //error expected ;
                                printf("Error: Expected ';' got %s\n", list->tokenInstance);

                        }
                }else{
                        //error expected IDENT_TK
                        printf("Error: Expected 'IDENT_TK' got %s\n", list->tokenInstance);

                }
        }else if(strcmp(list->idTk,"KW_TK") == 0 && strcmp(list->tokenInstance,"cin") == 0){
                list = list->next;
                if(strcmp(list->idTk,"IDENT_TK") == 0){
                        list = list->next;
                        if(strcmp(list->idTk,"OP_TK") == 0 && strcmp(list->tokenInstance,";") == 0){
                                list = list->next;
                                return list;
                        }else{
                                //error expected ;
                                printf("Error: Expected ';' got %s\n", list->tokenInstance);

                        }
                }else{
                        //error expected IDENT_TK
                        printf("Error: Expected 'IDENT_TK' got %s\n", list->tokenInstance);

                }
        }else if(strcmp(list->idTk,"KW_TK") == 0 && strcmp(list->tokenInstance,"cout") == 0){
                list = list->next;
                list = expr(list);
                if(strcmp(list->idTk,"OP_TK") == 0 && strcmp(list->tokenInstance,";") == 0){
                        list = list->next;
                        return list;
                }else{
                        //error expected ;
                        printf("Error: Expected ';' got %s\n", list->tokenInstance);

                }
        }else if(strcmp(list->idTk,"KW_TK") == 0 && strcmp(list->tokenInstance,"if") == 0){
                list = list->next;
                if(strcmp(list->idTk,"OP_TK") == 0 && strcmp(list->tokenInstance,"[") == 0){
                        list = list->next;
                        list = expr(list);
                        list = ro(list);
                        list = expr(list);
                        if(strcmp(list->idTk,"OP_TK") == 0 && strcmp(list->tokenInstance,"]") == 0){
                                list = list->next;
                                if(strcmp(list->idTk,"KW_TK") == 0 && strcmp(list->tokenInstance,"then") == 0){
                                        list = list->next;
                                        list = stat(list);
                                        if(strcmp(list->idTk,"OP_TK") == 0 && strcmp(list->tokenInstance,";") == 0){
                                                list = list->next;
                                                return list;
                                        }else{
                                                //error expected ;
                                                printf("Error: Expected ';' got %s\n", list->tokenInstance);

                                        }
                                }else{
                                        //error expected then
                                        printf("Error: Expected 'then' got %s\n", list->tokenInstance);

                                }
                        }else{
                                //error expected ]
                                printf("Error: Expected ']' got %s\n", list->tokenInstance);

                        }
                }else{
                        //error expected [
                        printf("Error: Expected '[' got %s\n", list->tokenInstance);

                }
        }else if(strcmp(list->idTk,"KW_TK") == 0 && strcmp(list->tokenInstance,"pick") == 0){
                list = list->next;
                list = expr(list);
                list = pickbody(list);
                if(strcmp(list->idTk,"OP_TK") == 0 && strcmp(list->tokenInstance,";") == 0){
                        list = list->next;
                        return list;
                }else{
                        //error expected ;
                        printf("Error: Expected ';' got %s\n", list->tokenInstance);

                }
        }else if(strcmp(list->idTk,"KW_TK") == 0 && strcmp(list->tokenInstance,"while") == 0){
                list = list->next;
                if(strcmp(list->idTk,"OP_TK") == 0 && strcmp(list->tokenInstance,"[") == 0){
                        list = list->next;
                        list = expr(list);
                        list = ro(list);
                        list = expr(list);
                        if(strcmp(list->idTk,"OP_TK") == 0 && strcmp(list->tokenInstance,"]") == 0){
                                list = list->next;
                                list = stat(list);
                                if(strcmp(list->idTk,"OP_TK") == 0 && strcmp(list->tokenInstance,";") == 0){
                                        list = list->next;
                                        return list;
                                }else{
                                        //error expected ;
                                        printf("Error: Expected ';' got %s\n", list->tokenInstance);

                                }
                        }else{
                                //error expected ]
                                printf("Error: Expected ']' got %s\n", list->tokenInstance);

                        }
                }else{
                        //error expected [
                        printf("Error: Expected '[' got %s\n", list->tokenInstance);
                }
        }else if(strcmp(list->idTk,"KW_TK") == 0 && strcmp(list->tokenInstance,"repeat") == 0){
                list = list->next;
                list = stat(list);
                if(strcmp(list->idTk,"KW_TK") == 0 && strcmp(list->tokenInstance,"until") == 0){
                        list = list->next;
                        if(strcmp(list->idTk,"OP_TK") == 0 && strcmp(list->tokenInstance,"[") == 0){
                                list = list->next;
                                list = expr(list);
                                list = ro(list);
                                list = expr(list);
                                if(strcmp(list->idTk,"OP_TK") == 0 && strcmp(list->tokenInstance,"]") == 0){
                                        list = list->next;
                                        if(strcmp(list->idTk,"OP_TK") == 0 && strcmp(list->tokenInstance,";") == 0){
                                                list = list->next;
                                                return list;
                                        }else{
                                                //error expected ;
                                                printf("Error: Expected ';' got %s\n", list->tokenInstance);

                                        }
                                }else{
                                        //error expected ]
                                        printf("Error: Expected ']' got %s\n", list->tokenInstance);

                                }
                        }else{
                                //error expected ]
                                printf("Error: Expected '[' got %s\n", list->tokenInstance);

                        }
                }else{
                        //error expected until
                        printf("Error: Expected 'until' got %s\n", list->tokenInstance);

                }
        }else if(strcmp(list->idTk,"KW_TK") == 0 && strcmp(list->tokenInstance,"set") == 0){
                list = list->next;
                if(strcmp(list->idTk,"IDENT_TK") == 0){
                        list = list->next;
                        if(strcmp(list->idTk,"OP_TK") == 0 && strcmp(list->tokenInstance,"=") == 0){
                                list = list->next;
                                list = expr(list);
                                if(strcmp(list->idTk,"OP_TK") == 0 && strcmp(list->tokenInstance,";") == 0){
                                        list = list->next;
                                        return list;
                                }else{
                                        //error expected ;
                                        printf("Error: Expected ';' got %s\n", list->tokenInstance);

                                }
                        }else{
                                //error expected =
                                printf("Error: Expected '=' got %s\n", list->tokenInstance);

                        }
                }else{
                        //error expected IDENT_TK
                        printf("Error: Expected 'IDENT_TK' got %s\n", list->tokenInstance);

                }
        }else if(strcmp(list->idTk,"IDENT_TK") == 0){
                list = list->next;
                if(strcmp(list->idTk,"OP_TK") == 0 && strcmp(list->tokenInstance,"=") == 0){
                        list = list->next;
                        list = expr(list);
                        if(strcmp(list->idTk,"OP_TK") == 0 && strcmp(list->tokenInstance,";") == 0){
                                list = list->next;
                                return list;
                        }else{
                                //error expected ;
                                printf("Error: Expected ';' got %s\n", list->tokenInstance);

                        }
                }else{
                        //error expected =
                        printf("Error: Expected '=' got %s\n", list->tokenInstance);

                }
        }else if(strcmp(list->idTk,"KW_TK") == 0 && strcmp(list->tokenInstance,"jump") == 0){
                list = list->next;
                if(strcmp(list->idTk,"IDENT_TK") == 0){
                        list = list->next;
                        if(strcmp(list->idTk,"OP_TK") == 0 && strcmp(list->tokenInstance,";") == 0){
                                list = list->next;
                                return list;
                        }else{
                                //error expected ;
                                printf("Error: Expected ';' got %s\n", list->tokenInstance);

                        }
                }else{
                        //error expected IDENT_TK
                        printf("Error: Expected 'IDENT_TK' got %s\n", list->tokenInstance);

                }
        }else if(strcmp(list->idTk,"OP_TK") == 0 && strcmp(list->tokenInstance,"{") == 0){
                list = block(list);
                return list;
        }else{
                //error in stat
                printf("Error: (Stat)Expected something but got %s\n", list->tokenInstance);

        }


}

struct Token* pickbody(struct Token* list){
        list = stat(list);
        if(strcmp(list->idTk,"OP_TK") == 0 && strcmp(list->tokenInstance,":") == 0){
                list = list->next;
                list = stat(list);
                return list;
        }else{
                //error expected :
                printf("Error: Expected ':' got %s\n", list->tokenInstance);

        }
}

struct Token* ro(struct Token* list){
        if(strcmp(list->idTk,"OP_TK") == 0 && strcmp(list->tokenInstance,"<") == 0){
                list = list->next;
                return list;
        }else if(strcmp(list->idTk,"OP_TK") == 0 && strcmp(list->tokenInstance,">") == 0){
                list = list->next;
                return list;
        }else if(strcmp(list->idTk,"OP_TK") == 0 && strcmp(list->tokenInstance,".") == 0){
                list = list->next;
                if(strcmp(list->idTk,"OP_TK") == 0 && strcmp(list->tokenInstance,".") == 0){
                        list = list->next;
                        if(strcmp(list->idTk,"OP_TK") == 0 && strcmp(list->tokenInstance,".") == 0){
                                list = list->next;
                                return list;
                        }else{
                                //error expected .
                                printf("Error: Expected '.' got %s\n", list->tokenInstance);

                        }
                }else{
                        //error expected .
                        printf("Error: Expected '.' got %s\n", list->tokenInstance);

                }
        }else if(strcmp(list->idTk,"OP_TK") == 0 && strcmp(list->tokenInstance,"=") == 0){
                list = list->next;
                list = roExtended(list);
                return list;
        }else{
                //error in ro
                printf("Error: (ro)Expected operator but got %s\n", list->tokenInstance);

        }
}

struct Token* roExtended(struct Token* list){
        if(strcmp(list->idTk,"OP_TK") == 0 && strcmp(list->tokenInstance,"=") == 0){
                list = list->next;
                return list;
        }else if(strcmp(list->idTk,"OP_TK") == 0 && strcmp(list->tokenInstance,"!") == 0){
                list = list->next;
                if(strcmp(list->idTk,"OP_TK") == 0 && strcmp(list->tokenInstance,"=") == 0){
                        list = list->next;
                        return list;
                }else{
                        //error expected =
                        printf("Error: Expected '=' got %s\n", list->tokenInstance);

                }
        }else{
                //error expected = or !=
                printf("Error: Expected '=' or '!=' got %s\n", list->tokenInstance);

        }
}

struct Token* expr(struct Token* list){
        list = n(list);
        if(strcmp(list->idTk,"OP_TK") == 0 && strcmp(list->tokenInstance,"-") == 0){
                list = list->next;
                list = expr(list);
                return list;
        }else{
                return list;
        }

}

struct Token* n(struct Token* list){
        list = a(list);
        list = nExtended(list);
        return list;
}

struct Token* nExtended(struct Token* list){
        if(strcmp(list->idTk,"OP_TK") == 0 && strcmp(list->tokenInstance,"/") == 0){
                list = list->next;
                list = a(list);
                list = nExtended(list);
                return list;
        }else if(strcmp(list->idTk,"OP_TK") == 0 && strcmp(list->tokenInstance,"+") == 0){
                list = list->next;
                list = a(list);
                list = nExtended(list);
                return list;
        }else{
                return list;
        }
}

struct Token* a(struct Token* list){
        list = m(list);
        if(strcmp(list->idTk,"OP_TK") == 0 && strcmp(list->tokenInstance,"*") == 0){
                list = list->next;
                list = a(list);
                return list;
        }else{
                return list;
        }
}

struct Token* m(struct Token* list){
        if(strcmp(list->idTk,"OP_TK") == 0 && strcmp(list->tokenInstance,"^") == 0){
                list = list->next;
                list = m(list);
                return list;
        }else{
                list = r(list);
                return list;
        }
}

struct Token* r(struct Token* list){
        if(strcmp(list->idTk,"OP_TK") == 0 && strcmp(list->tokenInstance,"(") == 0){
                list = list->next;
                list = expr(list);
                if(strcmp(list->idTk,"OP_TK") == 0 && strcmp(list->tokenInstance,")") == 0){
                        list = list->next;
                        return list;
                }else{
                        //error expected )
                        printf("Error: Expected ')' got %s\n", list->tokenInstance);

                }
        }else if(strcmp(list->idTk,"IDENT_TK") == 0){
                list = list->next;
                return list;
        }else if(strcmp(list->idTk,"INT_TK") == 0){
                list = list->next;
                return list;
        }else{
                //error in r
                printf("Error: Expected 'IDENTIFIER', 'INTEGER', or '(' got %s\n", list->tokenInstance);

        }
}
