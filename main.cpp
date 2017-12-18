/**
 * Operating Systems Project 4
 * The functions isDir and listFiles come from SwedBo (https://bbs.archlinux.org/viewtopic.php?id=97216)
 */

#include <iostream>
#include <fcntl.h>
#include <dirent.h>
#include <sys/stat.h>

#define PERMS 0644


using namespace std;


bool isDir(string dir) {
    struct stat fileInfo;
    stat(dir.c_str(), &fileInfo);
    if (S_ISDIR(fileInfo.st_mode)) {
        return true;
    }
    else {
        return false;
    }
}

void listFiles(string baseDir, bool recursive) {
    DIR *dp;
    struct dirent *dirp;

    if ((dp = opendir(baseDir.c_str())) == nullptr) {
        cout << "[ERROR: " << errno << "] Couldn't open " << baseDir << endl;
        return;
    }
    else {
        while ((dirp = readdir(dp)) != nullptr) {
            if (dirp->d_name != string(".") && dirp->d_name != string("..") && dirp->d_name != string(".DS_Store")) {
                if (isDir(baseDir + dirp->d_name) && recursive) {
                    cout << "[DIR]\t" << baseDir << dirp->d_name << "/" << endl;
                    listFiles(baseDir + dirp->d_name + "/", true);
                } else {
                    cout << "[FILE]\t" << baseDir << dirp->d_name << endl;
                }
            }
        }
        closedir(dp);
    }
}

int main(int argc, char *argv[]) {

    // cout << "Hello World!" << endl;

    if (argc != 4) {
        cerr << "[ERROR] Invalid arguments: please enter a command in this format:" <<
             "./adzip -flag <archive_file> <input_file>" << endl;
        exit(1);
    }

//    DIR *root;
    struct dirent *dirp;

    char *archive_file, *input_dir;
    int fd;

    archive_file = argv[2];
    input_dir = argv[3];

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
        listFiles(input_dir, true);
    }
    else { // no valid input provided
        cerr << "[ERROR] Incorrect flag: please use -c, -a, -x, -m, or -p." << endl;
        exit(1);
    }

    if ((fd = open(archive_file, O_CREAT | O_RDWR, PERMS)) == -1) {
        cerr << "Error: Cannot open archive file" << archive_file << endl;
        exit(1);
    }
    else {
        cout << "Success! Opened archive file: " << archive_file << endl;
    }

    return 0;
}
