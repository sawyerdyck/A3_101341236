# Assignment 1, Bits and Bytes
02 This program has a 3 features. It first prints an ascii image from an array of '0's and '1's, then it back the bits from the original array into a compressed array that is 1/8th the size, then it uses a different compression technique; RLE to attempt to further compress the image past 1/8th. The images used have noticeably long runs of 0's and 1's which allows RLE to be very efficient and compress them smaller than the bit packing method. After each compression is complete, a custom print function prints the data in a proper manner.
03
04 ## Building and Running
05 1. Open a terminal and navigate to the folder containing the program's files,
06 2. Type the command `gcc -Wall main.c photo.c camera.o -o a3`,
07 3. The program should compile without any warning/error and an executable 'a3' should appear in the directory
08 4. From that directory, you can run `./a3` to execute the project.
09 5. If you want to test it, you can use either of the camera_test_packed() or camera_test_encode() functions!
10 6. after running the 'a3' executable three variants of each image should print out and there should be a line under the 3rd print showing the actual size of the data after each compression.
11
12 ## Credits
13 - Developed individually by Sawyer Dyck (101341236)
