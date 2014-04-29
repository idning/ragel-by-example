#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <unistd.h>

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

void dump(uint8_t *buf, uint32_t len){
    
}

%%{
    machine redis; 

    action start_cmd{
        printf("%20s state: %2d ### at %.*s \n", "start_cmd", cs, (int)(p-buf), buf);
    }
    action end_cmd{
        printf("%20s state: %2d ### at %.*s \n", "end_cmd", cs, (int)(p-buf), buf);
    }


    action start_argc{
        last = p;
        printf("%20s state: %2d ### at %.*s \n", "start_argc", cs, (int)(p-buf), buf);
    }
    action end_argc{
        argc = atol(last);
        printf("%20s state: %2d ### at %.*s \n", "end_argc", cs, (int)(p-buf), buf);
        printf("argc: %d \n", argc);
    }

    action start_arglen{
        last = p;
        printf("%20s state: %2d ### at %.*s \n", "start_arglen", cs, (int)(p-buf), buf);
    }
    action end_arglen{
        arglen = atol(last);
        printf("%20s state: %2d ### at %.*s \n", "end_arglen", cs, (int)(p-buf), buf);
        printf("arglen: %d \n", arglen);
    }

    action start_arg{
        printf("%20s state: %2d ### at %.*s \n", "start_arg", cs, (int)(p-buf), buf);
    }
    action end_arg{
        printf("%20s state: %2d ### at %.*s \n", "end_arg", cs, (int)(p-buf), buf);
    }
    action all{
        printf("%20s state: %2d ### at %.*s \n", "-----all", cs, (int)(p-buf), buf);
    }

    #test how many args readed
    action test_argc{ argc-- > 0 }

    #test how many char readed in arg
    action test_arglen{ (printf("test_arglen %c %d  arglen>0:%d\n", *p, arglen, arglen>0) && (arglen-- > 0)) }

    crlf = "<>";
    argc = ("*" 
            digit+                          >start_argc %end_argc
            crlf);       

    arglen = ("$" 
            digit+                          >start_arglen %end_arglen
            crlf);    
    arg = (arglen 
            (any when test_arglen)+         >start_arg %end_arg
            crlf);
    main := ((any when test_arglen)+        >start_arg %end_arg $all 
            <:
            crlf );
}%%

%% write data;

Msg* msg_parse(uint8_t *buf, uint32_t len){
    int cs;             //used by ragel
    uint8_t *p, *pe, *eof;       //used by ragel
    

    uint8_t *last; //last pos
    uint32_t argc;
    uint32_t arglen = 7;

    p = buf;
    eof = pe = buf + len;

    %%{
        write init;   
        write exec;   
    }%%

}

int main(){
    /*uint8_t buf[] = "*3<>$3<>SET<>$5<>mykey<>$7<>myva<>e<>";*/
    uint8_t buf[] = "myva<>e<>";
    uint32_t buflen = strlen(buf);
    msg_parse(buf, buflen);
}

