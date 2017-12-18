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

// void storeFiles(ofstream archive, string baseDir, bool recursive) {
//     DIR *dp;
//     struct dirent *dirp;

//     if ((dp = opendir(baseDir.c_str())) == nullptr) {
//         cout << "[ERROR: " << errno << "] Cannot open " << baseDir << endl;
//         return;
//     }
//     else {
//         struct stat fileInfo;
//         while ((dirp = readdir(dp)) != nullptr) {
//             if (dirp->d_name != string(".") && dirp->d_name != string("..") && dirp->d_name != string(".DS_Store")) {
//                 if (isDir(baseDir + dirp->d_name) && recursive) { // directory
//                     storeFiles(archive, baseDir + dirp->d_name + "/", true);
//                 }
//                 else { // file
//                     // get information of the input file
//                     stat((baseDir + dirp->d_name).c_str(), &fileInfo);

//                     // writing to the archive file
//                     archive.write((baseDir + dirp->d_name).c_str(), 126);
//                     archive.write(reinterpret_cast<const char *>(fileInfo.st_uid), sizeof(uid_t));
//                     archive.write(reinterpret_cast<const char *>(fileInfo.st_gid), sizeof(gid_t));
//                     archive.write(reinterpret_cast<const char *>(fileInfo.st_mode), sizeof(mode_t));
//                     archive.write(reinterpret_cast<const char *>(fileInfo.st_size), sizeof(off_t));

// //                    archive << baseDir << dirp->d_name; // write the name
// //                    archive << fileInfo.st_uid;         // write the user ID
// //                    archive << fileInfo.st_gid;         // write the group ID
// //                    archive << fileInfo.st_mode;        // write the mode
// //                    archive << fileInfo.st_size;        // write the size
//                 }
//             }
//         }
//         closedir(dp);
//     }
// }

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

    // cout << "Hello World!" << endl;

    if (argc != 4) {
        cerr << "[ERROR] Invalid arguments: please enter a command in this format:" <<
             "./adzip -flag <archive_file> <input_file>" << endl;
        exit(1);
    }

//    DIR *root;
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

//    if ((fd = open(archive_file, O_CREAT | O_RDWR, PERMS)) == -1) { // open the archive file
//        cerr << "Error: Cannot open archive file" << archive_file << endl;
//        exit(1);
//    }
//    else {
//        cout << "Success! Opened archive file: " << archive_file << endl;
//    }

    // Getting arguments from the command line
    if (strcmp(argv[1], "-c") == 0) { // store
        // store files/directories into archive file
//        storeFiles(archive, input_dir, true);
        DIR *dp;
        struct dirent *direntp;

        if ((dp = opendir(input_dir)) == nullptr) {
            cout << "[ERROR: " << errno << "] Cannot open " << input_dir << endl;
        }
        else {
            cout << "Opened " << input_dir << endl;

            while ((direntp = readdir(dp)) != nullptr) {
                if (direntp->d_name != string(".") && direntp->d_name != string("..") &&
                    direntp->d_name != string(".DS_Store")) {
                    char x[100];
                    strcpy(x, input_dir);
                    string base = x;
                    string name = direntp->d_name;
                    if (isDir(base + name)) { // directory
//                        storeFiles(archive, *input_dir + dirp->d_name + "/", true);
                    }
                    else { // file
                        // char x[100];
                        // strcpy(x, input_dir);
                        // string base = x;
                        // string name = direntp->d_name;
                        // cout << a + b << endl;
                        // get information of the input file
                        struct stat fileInfo;
                        stat((base + name).c_str(), &fileInfo);

                        // writing to the archive file
                        cout << base << name << endl;
                        cout << fileInfo.st_uid << endl;
                        cout << fileInfo.st_gid << endl;
                        cout << fileInfo.st_mode << endl;
                        cout << fileInfo.st_size << endl;

                        archive.write((base + name + "\0").c_str(), 126);
//                        archive.write(reinterpret_cast<const char *>(fileInfo.st_uid), sizeof(uid_t));
                        // archive.write(reinterpret_cast<const char *>(fileInfo.st_gid), sizeof(gid_t));
                        // archive.write(reinterpret_cast<const char *>(fileInfo.st_mode), sizeof(mode_t));
                        // archive.write(reinterpret_cast<const char *>(fileInfo.st_size), sizeof(off_t));

                        archive << base << name; // write the name
                        archive << fileInfo.st_uid;         // write the user ID
//                    archive << fileInfo.st_gid;         // write the group ID
//                    archive << fileInfo.st_mode;        // write the mode
//                    archive << fileInfo.st_size;        // write the size
                    }
                }
            }
            closedir(dp);
        }
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
