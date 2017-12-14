/**
 * Operating Systems Project 4
 */

#include <iostream>


using namespace std;


int main(int argc, char *argv[]) {
  // Getting arguments from the command line
  for (int i = 1; i < argc; i += 2) {
      if (strcmp(argv[i], "-c") == 0) {        // file to be sorted
          // store files/directories into archive file
      } else if (strcmp(argv[i], "-a") == 0) { // number of lines in file to be sorted
          // append files/directories into archive file
      } else if (strcmp(argv[i], "-x") == 0) { // number of sorter nodes to be created
          // extract all files from archive file
      } else if (strcmp(argv[i], "-m") == 0) { // name of sort executable
          // print out meta data for all files/directories inside archive file
      } else if (strcmp(argv[i], "-p") == 0) { // attribute number
          // display hierarchy of files/directories inside archive file
      } else {                                // no valid input provided
          // invalid input
      }
  }

  return 0;
}
