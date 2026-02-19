#include <stdio.h>
#include <string.h>
#include "commands.h"

// This is the entry point, git to start needs
// to be initialized, here is where that is checked and 
// there are some test commands to check the functions are
// working properly. 
// The main thing to focus on is the init, if the user provides 
// the init as the argument then that means, we are initializing the git
// and we call the init function that is written in the commands.c file
// which is being called using the commands.h
int main (int argc, char* argv[]){

  // basic check if the arguments is provided. if none is provided
  // remind the usr that comand is needed
    if(argc < 2){
        fprintf(stderr, "Usage: mygit <command> [<args>]\n");
      }

  // comparing the command that is being provided and
  // based on that we would call the respective functionality
    if(strcmp(argv[1], "init") == 0){
      return cmd_init();
      printf("Thanks for the initialization\n");
    } else if(strcmp(argv[1], "hashObject") == 0){
      return cmdHashObject(argv[2]);
    } else {
      fprintf(stderr, " Unknown command : %s\n", argv[1]);
    }
  }
  
