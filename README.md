# Flatting the Logical Hierarchy of a File System
Project 4 of Operating Systems class in New York University Abu Dhabi, taught by professor Alex Delis.

## Description
This project aims to create a C++ program that flattens the logical hierarchy(-ies) of a file system,then stores the hierarchy(-ies) in a single file with the postfix **.ad**.

## How to run
Enter `make` in the command line in order to compile the files. The program is invoked with the following syntax: `adtar(name of program) {-c|-a|-x|-m|-p} <archive-file> <file/directory list>`.

The parameters are described here:
* `-c`: store in the archive file the files/directories provided by the files/directories list. If other additional files/directories exist in <file/directory list>, then all this content is recursively stored in the \<archive-file>.
* `-a`: append filesystem entities indicated in the file <file/directory list> in the archive file <archive-file> that already exists. If additional files/directories exist in <file/directory list>, they are recursively appended along with their content in the designated <archive-file>.