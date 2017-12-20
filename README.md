# Flatting the Logical Hierarchy of a File System
Project 4 of Operating Systems class in New York University Abu Dhabi, taught by professor Alex Delis.

## Description
This project aims to create a C++ program that flattens the logical hierarchy(-ies) of a file system,then stores the hierarchy(-ies) in a single file with the postfix **.ad**.

## How to run
Enter `make` in the command line in order to compile the files. The program is invoked with the following syntax: `adtar(name of program) {-c|-a|-x|-m|-p} <archive-file> <file/directory list>`.

NOTE: the <file/directory list> has to contain a trailing slash to indicate that it is a directory.

The flags are described here:
* `-c`: store in the archive file the files/directories provided by the files/directories list. If other additional files/directories exist in <file/directory list>, then all this content is recursively stored in the \<archive-file>.
* `-a`: append filesystem entities indicated in the file <file/directory list> in the archive file \<archive-file> that already exists. If additional files/directories exist in <file/directory list>, they are recursively appended along with their content in the designated \<archive-file>.
* `-x`: extract all files and directories that have been archived in file \<archive-file>.
* `-m`: print out the meta data (owner, group, rights) for all files/directories that have been archived in \<archive-file>.
* `-p`: display the hierarchy(-ies) of the files and directories stored in the \<archive-file>. Do this in a way that can be readily understood by the user.

## Implementation
Our **.ad** file is designed like this: we pair each file's meta data and file data together. Using the folder <file/directory list> provided as an argument when the program is invoked as the root folder, we recursively go through each file and nested directory, and write each file's meta data and file data in pairs to the **.ad** file.

This means that each of the meta data - essentially the header - section will have to contain the offset to the next header block for the next file. This can actually be easily done, since we can access the size of the file data using the `stat` system call. This will be the offset to the next header block. One thing to note is that since we are writing everything one after another, we have to have fixed sizes for each field in the header block. The **file name** is always set to 126 characters long, the **uid** and **gid** 4 characters, the **mode** 6 characters, and the **size** 10 characters.
