#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <unistd.h>

typedef char *sds;

struct sdshdr {
    int len;
    int free;
    char buf[];
};

sds sdsnewlen(const void *init, size_t initlen) {
    struct sdshdr *sh;

    sh = malloc(sizeof(struct sdshdr)+initlen+1);
    if (sh == NULL) return NULL;
    sh->len = initlen;
    sh->free = 0;
    if (initlen && init)
        memcpy(sh->buf, init, initlen);
    sh->buf[initlen] = '\0';
    return (char*)sh->buf;
}


typedef struct Msg{
    int argc; // if argc < 0, means this msg is not used
    char ** argv;
}Msg;

Msg* msg_new(int argc){
    Msg * msg;
    msg = malloc(sizeof(Msg));
    msg->argc = argc;
    msg->argv = malloc(sizeof(char*) * msg->argc);
    return msg;
}

%%{
    machine redis; 

    action start_cmd{
    }
    action end_cmd{
    }

    action start_argc{
        last = p;
    }
    action end_argc{
        argc = atol(last);
        msg = msg_new(argc);
    }

    action start_arglen{
        last = p;
    }
    action end_arglen{
        arglen = atol(last);
        msg->argv[c_arg] = sdsnewlen(NULL, arglen);
    }

    action start_arg{
        last = p;
    }
    action end_arg{
        memcpy(msg->argv[c_arg], last, p-last);
        len = p-last;
        msg->argv[c_arg][len] = '\0';

        c_arg ++;
    }

    #test how many args readed
    action test_argc{ c_arg < argc}

    #test how many char readed in arg
    action test_arglen{arglen-- > 0}

    crlf = "<>";
    argc = ("*" 
            digit+                          >start_argc %end_argc
            crlf);       

    arglen = ("$" 
            digit+                          >start_arglen %end_arglen
            crlf);    
    arg = (arglen 
            (any when test_arglen)+         >start_arg %end_arg
             <:
            crlf);
    main := (argc 
            (arg when test_argc)+
            )                               >start_cmd %end_cmd;

}%%

%% write data;

Msg* msg_parse(uint8_t *buf, uint32_t buflen){
    int cs;             //used by ragel
    uint8_t *p, *pe, *eof;       //used by ragel

    Msg * msg = NULL; 
    uint8_t *last; //last pos
    uint32_t argc;
    uint32_t arglen;
    uint32_t len, c_arg=0;

    p = buf;
    eof = pe = buf + buflen;

    %%{
        write init;   
        write exec;   
    }%%
    return msg;
}

int main(){
    uint8_t buf[] = "*3<>$3<>SET<>$5<>mykey<>$7<>myva<>e<>$5<>mykey<>";
    uint32_t buflen = strlen(buf);
    int i;
    Msg * msg = msg_parse(buf, buflen);
    
    if(msg == NULL){
        printf("error on parse msg");
    }
    printf("msg->argc: %d\n", msg->argc);
    for(i=0; i<msg->argc; i++){
        printf("%s\n", msg->argv[i]);
    }
}

