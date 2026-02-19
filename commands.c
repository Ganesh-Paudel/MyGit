#include "commands.h"
#include <stdio.h>
#include <stdlib.h>
#include <openssl/sha.h>
#include <sys/stat.h>
#include <errno.h>
#include <string.h>

void hashToHex(unsigned char* hash, char* out){
  for(int i = 0; i < 20; i++){
    sprintf(out + (i*2), "%02x", hash[i]);
  }
  out[40] = '\0';
}

int cmdHashObject(const char* fileName){

}

int cmd_init(){

  // Make the main .git directory
    
  if (mkdir(".git", 0755) == -1 && errno != EEXIST){
    perror("Failed to create .git\n");
    return 1;
  }

  // Creating the sub directories once the .git is created, 
  
  FILE *headFile = fopen("./.git/HEAD", "w");
  if(headFile == NULL){
    perror("Failed to create .git/HEAD\n");
    return 1;
  }

  fprintf(headFile, "ref: refs/heads/master\n");
  fclose(headFile);

  printf("Initialized empty git repository in .git/\n");
  return 0;
}
