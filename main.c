#include <stdio.h>
#include <string.h>
#include "commands.h"

int main (int argc, char* argv[]){
    if(argc < 2){
        fprintf(stderr, "Usage: mygit <command> [<args>]\n");
      }

    if(strcmp(argv[1], "init") == 0){
      return cmd_init();
      printf("Thanks for the initialization\n");
    } else {
      fprintf(stderr, " Unknown command : %s\n", argv[1]);
    }
  }
  
