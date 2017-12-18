/**
 * Operating Systems Project 4
 */

#include <iostream>
#include <fcntl.h>
#include <dirent.h>

#define PERMS 0644


using namespace std;


int main(int argc, char *argv[]) {

    // cout << "Hello World!" << endl;

    if (argc != 4) {
        cerr << "Invalid arguments: please enter a command in this format:" << "./adzip -flag <archive_file> <input_file>" << endl;
        exit(1);
    }

    DIR *root;
    struct dirent *direntp;
    string archive_file;
    char *input_dir;

    // Getting arguments from the command line
    if (strcmp(argv[1], "-c") == 0) { // store
        // store files/directories into archive file
    }
    else if (strcmp(argv[1], "-a") == 0) { // append
        // append files/directories into archive file
    }
    else if (strcmp(argv[1], "-x") == 0) { // extract
        // extract all files from archive file
    }
    else if (strcmp(argv[1], "-m") == 0) { // print meta data
        // print out meta data for all files/directories inside archive file
    }
    else if (strcmp(argv[1], "-p") == 0) { // display hierarchy
        // display hierarchy of files/directories inside archive file
    }
    else { // no valid input provided
        // invalid input
    }

    archive_file = argv[2];
    input_dir = argv[3];

    if ((root = opendir(input_dir)) == nullptr) {
        cerr << "Error: Cannot open input directory" << input_dir << endl;
        exit(1);
    }
    else {
        cout << "Success! Opened input directory: " << input_dir << endl;
        while ((direntp = readdir(root)) != nullptr) {
            cout << direntp->d_name << endl;
        }
        closedir(root);
    }

    return 0;
}
