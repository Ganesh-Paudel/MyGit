#include "commands.h"
#include <stdio.h>
#include <stdlib.h>
#include <openssl/sha.h>
#include <sys/stat.h>
#include <errno.h>
#include <string.h>
#include <zlib.h>
#include "objectStore.h"
#include "util.h"


// The init command
// If the user passed the init command,
// We have couple things we need to do 
// The main thing is creating the .git directory, 
// Then once it is created, we create some sub directories which
// is used during the tracking, 
// objects, refs, refs/objects and head
// if all of that is fulfilled then, we have sucessfully created a 
// repo in the given folder 
int cmd_init(){

  // Make the main .git directory
    
//  if (mkdir(".myGit", 0755) == -1 && errno != EEXIST){
//   perror("Failed to create .git\n");
//    return 1;
//  }
  if (ensureDirExists(".myGit/objects") != 0 || 
      ensureDirExists(".myGit/refs/heads") != 0) {
      die("Failed to initialize repository structure");
  }

  FILE *headFile = fopen(".myGit/HEAD", "w");
  if (headFile == NULL) {
      die("Failed to create .myGit/HEAD: %s", strerror(errno));
  }

  fprintf(headFile, "ref: refs/heads/master\n");
  fclose(headFile);

  printf("Initialized empty Git repository in .myGit/\n");
  return 0;
}
