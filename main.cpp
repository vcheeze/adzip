/**
 * Operating Systems Project 4
 * The functions isDir and listFiles come from SwedBo (https://bbs.archlinux.org/viewtopic.php?id=97216)
 */

#include <iostream>
#include <fcntl.h>
#include <dirent.h>
#include <sys/stat.h>
#include <fstream>

#define HDR_SIZE (126 + sizeof(uid_t) + sizeof(gid_t) + sizeof(mode_t) + sizeof(off_t))


using namespace std;


bool isDir(string dir) {
    struct stat fileInfo;
    stat(dir.c_str(), &fileInfo);
    // cout << fileInfo.st_uid << endl;
    // cout << fileInfo.st_gid << endl;
    // cout << fileInfo.st_mode << endl;
    // cout << fileInfo.st_size << endl;
    if (S_ISDIR(fileInfo.st_mode)) {
        return true;
    }
    else {
        return false;
    }
}

void storeFiles(fstream &archive, string baseDir, bool recursive) {
    DIR *dp;
    struct dirent *dirp;

    if ((dp = opendir(baseDir.c_str())) == nullptr) {
        cout << "[ERROR: " << errno << "] Cannot open " << baseDir << endl;
    }
    else {
        cout << "Opened " << baseDir << endl;

        while ((dirp = readdir(dp)) != nullptr) { // iterate through the directory
            if (dirp->d_name != string(".") && dirp->d_name != string("..") &&
                dirp->d_name != string(".DS_Store")) {
                // some char to string operations to make isDir and stat work
//            char x[100];
//            strcpy(x, baseDir);
                string base = baseDir;
                string name = dirp->d_name;

                if (isDir(base + name) && recursive) { // directory
                    // storeFiles(archive, baseDir + dirp->d_name + "/", true);
                }
                else { // file
                    // get information of the input file
                    struct stat fileInfo;
                    stat((base + name).c_str(), &fileInfo);
//                    base.pop_back(); // remove newline char

                    cout << "File name: " << base << name << endl;
                    cout << "User ID: " << fileInfo.st_uid << endl;
                    cout << "Group ID: " << fileInfo.st_gid << endl;
                    cout << "Mode: " << fileInfo.st_mode << endl;
                    cout << "Size: " << fileInfo.st_size << endl;

                    // write meta data to the archive file
                    archive.write((base + name + "\0").c_str(), 126); // write file name
                    archive << fileInfo.st_uid;                       // write the user ID
                    archive << fileInfo.st_gid;                       // write the group ID
                    archive << fileInfo.st_mode;                      // write the mode
                    archive << fileInfo.st_size;                      // write the size

                    // copy the file content
                    ifstream infile;
                    char c;

                    infile.open(base + name);
                    if (infile.is_open()) {
                        while (!infile.eof()) {
                            c = (char) infile.get();
                            archive.put(c);
                        }
                        infile.close();
                    }
                    else {
                        cerr << "[ERROR] Failed to open file: " << base << name << endl;
                    }
                }
            }
        }
        closedir(dp);
    }
}

void listFiles(string baseDir, bool recursive) {
    DIR *dp;
    struct dirent *dirp;

    if ((dp = opendir(baseDir.c_str())) == nullptr) {
        cout << "[ERROR: " << errno << "] Cannot open " << baseDir << endl;
        return;
    }
    else {
        while ((dirp = readdir(dp)) != nullptr) {
            if (dirp->d_name != string(".") && dirp->d_name != string("..") && dirp->d_name != string(".DS_Store")) {
                if (isDir(baseDir + dirp->d_name) && recursive) { // directory
                    cout << "[DIR]\t" << baseDir << dirp->d_name << "/" << endl;
                    listFiles(baseDir + dirp->d_name + "/", true);
                }
                else { // file
                    cout << "[FILE]\t" << baseDir << dirp->d_name << endl;
                }
            }
        }
        closedir(dp);
    }
}


int main(int argc, char *argv[]) {

    if (argc != 4) {
        cerr << "[ERROR] Invalid arguments: please enter a command in this format:" <<
             "./adzip -flag <archive_file> <input_file>" << endl;
        exit(1);
    }

    struct dirent *dirp;

    char *archive_file, *input_dir;
    fstream archive;

    archive_file = argv[2];
    input_dir = argv[3];

    archive.open(archive_file, fstream::in | fstream:: out | fstream::trunc);

    if (archive.is_open()) {
        cout << "Archive is opened" << endl;
    }
    else {
        cerr << "[ERROR] Archive failed to open" << endl;
    }

    // Getting arguments from the command line
    if (strcmp(argv[1], "-c") == 0) { // store
        // store files/directories into archive file
        storeFiles(archive, input_dir, true);
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

    archive.close(); // close the archive file


    return 0;
}
