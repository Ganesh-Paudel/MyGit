#include "commands.h"
#include <stdio.h>
#include <stdlib.h>
#include <openssl/sha.h>
#include <sys/stat.h>
#include <errno.h>
#include <string.h>
#include <zlib.h>


void hashToHex(unsigned char* hash, char* out){
  for(int i = 0; i < 20; i++){
    sprintf(out + (i*2), "%02x", hash[i]);
  }
  out[40] = '\0';
}

int compressObject(const char* path, unsigned char* data, int len){

  z_stream strm;
  strm.zalloc = Z_NULL;
  strm.zfree = Z_NULL;
  strm.opaque = Z_NULL;

  if (deflateInit(&strm, Z_BEST_COMPRESSION) != Z_OK) return 1;

  int out_max = deflateBound(&strm, len);
  unsigned char *out = malloc(out_max);

  strm.next_in = data;
  strm.avail_in = len;
  strm.next_out = out;
  strm.avail_out = out_max;

  // 3. Compress
  deflate(&strm, Z_FINISH);
  int compressed_size = out_max - strm.avail_out;

  // 4. Write compressed data to disk
  FILE *f = fopen(path, "wb");
  if (f) {
      fwrite(out, 1, compressed_size, f);
      fclose(f);
  }

  // Clean up
  deflateEnd(&strm);
  free(out);
  return 0;
}

// Git tracks the file based on the content and not name,
// if two files have same content they have ame track since 
// the hash is generated based on content,
// Here, we create that hash
int cmdHashObject(const char* fileName){

  // Reading the input file 

  FILE *f = fopen(fileName, "rb");
  if(!f){
    perror("fopen");
    return 1;
  }

  fseek(f, 0, SEEK_END);
  long fsize = ftell(f);
  fseek(f, 0, SEEK_SET);


  char *content = malloc(fsize);
  fread(content , 1, fsize, f);
  fclose(f);


  char header[64];
  int headerLen = sprintf(header, "blob %ld", fsize) + 1; // +1 for the '\0'

  // 3. Combine header and content for hashing
  int totalLen = headerLen + fsize;
  unsigned char *storeBuf = malloc(totalLen);
  memcpy(storeBuf, header, headerLen);
  memcpy(storeBuf + headerLen, content, fsize);

  // 4. Calculate SHA-1
  unsigned char hash[SHA_DIGEST_LENGTH];
  SHA1(storeBuf, totalLen, hash);

  char hexHash[41];
  hashToHex(hash, hexHash);
  printf("Hash: %s\n", hexHash);

  // 5. Store the object (The Fan-out)
  char dirPath[32];
  sprintf(dirPath, ".myGit/objects/%.2s", hexHash);
  mkdir(dirPath, 0755); // Create the 2-char prefix directory

  char objPath[128];
  sprintf(objPath, "%s/%s", dirPath, hexHash + 2);

  if(compressObject(objPath, storeBuf, totalLen) != 0){
    fprintf(stderr, "Failed to compress and save object\n");
    return 1;
  }

  free(content);
  free(storeBuf);
  return 0;
}

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
    
  if (mkdir(".myGit", 0755) == -1 && errno != EEXIST){
    perror("Failed to create .git\n");
    return 1;
  }

  // Creating the sub directories once the .git is created, 
  //
  const char* dirs[] = {".myGit/objects", ".myGit/refs", ".myGit/refs/heads"};

  for(int i = 0; i < 3; i++){
    if(mkdir(dirs[i], 0755) == -1 && errno != EEXIST){
      perror("Failed to create subdirectory");
    }
  }
  
  FILE *headFile = fopen("./.myGit/HEAD", "w");
  if(headFile == NULL){
    perror("Failed to create .git/HEAD\n");
    return 1;
  }

  fprintf(headFile, "ref: refs/heads/master\n");
  fclose(headFile);

  printf("Initialized empty git repository in .git/\n");
  return 0;
}
