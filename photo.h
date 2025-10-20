/*
    This file contains all of the forward declarations and definitions required by photos 
    that are NOT part of camera.o requirements, and should be included in each file that
    uses your photo functionality.
*/

#define ERR_OK 0
#define ERR_INVALID_PHOTO_SIZE -1
#define ERR_UNKNOWN_CHARACTER -2

int print_ascii(const unsigned char photo[], int rows, int cols);
int pack_bits(unsigned char packed[], const unsigned char photo[], int num_chars);
int print_packed_bits(const unsigned char photo[], int rows, int cols);
int rle_encode(unsigned char encoded_result[], const unsigned char packed[], int rows, int cols);
int print_rle(const unsigned char encoded[]);

			
// Only used for the sidequest. Uncomment if you are attempting the side quest.
// int print_sq_bits(const unsigned char photo[]);
