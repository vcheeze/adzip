/**
 * Operating Systems Project 4
 */

#include <iostream>


using namespace std;


int main(int argc, char *argv[]) {

    // Getting arguments from the command line
    for (int i = 1; i < argc; i++) {
        if (strcmp(argv[i], "-c") == 0) { // store
            // store files/directories into archive file
        }
        else if (strcmp(argv[i], "-a") == 0) { // append
            // append files/directories into archive file
        }
        else if (strcmp(argv[i], "-x") == 0) { // extract
            // extract all files from archive file
        }
        else if (strcmp(argv[i], "-m") == 0) { // print meta data
            // print out meta data for all files/directories inside archive file
        }
        else if (strcmp(argv[i], "-p") == 0) { // display hierarchy
            // display hierarchy of files/directories inside archive file
        }
        else { // no valid input provided
            // invalid input
        }
    }

    

    return 0;
}
