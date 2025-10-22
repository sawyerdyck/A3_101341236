#include <stdio.h>
#include "camera.h"
#include "photo.h"

/*
Prints the ASCII representation of a photo using '#' for '1' pixels and
a space for '0' pixels.

in: photo; An array of ASCII characters ('1' or '0') representing the photo pixels.
in: rows;  The number of rows in the photo.
in: cols;  The number of columns in the photo.

Return: 0 if the photo was printed successfully, or -1 if the input contained
        an invalid character (anything other than '0' or '1').
*/


int print_ascii(const unsigned char photo[], int rows, int cols){			
	//printing original photo
	for (int i = 0;i<rows;i++){
		for (int j = 0;j<cols;j++){
			unsigned char bit = photo[i*cols+j];
			if (bit == '1'){
				printf("*");
			}else if (bit == '0'){
				printf(".");
			}else{
				return -1;
			}
		}printf("\n");		
	}printf("\n");return 0;
}

/*
Converts an ASCII photo ('1' and '0' characters) into a packed binary
representation, where each byte represents 8 pixels (MSB-first).

out: packed; An array to store the resulting packed bytes.
in:  photo;  The ASCII photo to convert ('1' and '0' characters).
in:  num_chars; The total number of characters (pixels) in the photo.

Return: The number of packed bytes produced, or -1 if the input size is not
        a multiple of 8 or contains invalid characters.
*/

int pack_bits(unsigned char packed[], const unsigned char photo[], int num_chars){
	if(num_chars%8 != 0){return -1;}
	//packing photo
	unsigned char byte = 0;
	for(int i = 0;i<num_chars;i++){
		byte = 0;
		for(int j = 0;j<8;j++){
			unsigned char bit = photo[i*8+j];
			if (bit == '1'){
				 byte += (1<<(7-j));
			}else if(bit != '0'){
				return -1;
			}	
		}packed[i] = byte; 
	
	}return num_chars;
}

/*
Prints a packed photo to the console using '#' for 1-bits and spaces for 0-bits.
The bits are unpacked MSB-first from each byte and printed in image order.

in: photo; An array of packed bytes representing the photo.
in: rows;  The number of rows in the photo.
in: cols;  The number of columns in the photo.

Return: The number of bytes that were processed and printed.
*/

int print_packed_bits(const unsigned char photo[], int rows, int cols){
	//printing packed photo
	int toPrint = rows * cols;
	int maskSize = toPrint/8;	
	int newLine = 0;
	for(int i = 0;i<maskSize;i++){
		for(int y = 7; y>=0;y--){
			if(newLine == cols){
				printf("\n");
				newLine = 0;
			}
			if(photo[i] & (1<<y)){
				printf("+");
			}else{
				printf("-");
			}newLine++;
			if (newLine >= toPrint){break;}
		}
	}printf("\n");return maskSize; 
}

/*
Encodes a packed photo using Run-Length Encoding (RLE). Alternates runs of
0s and 1s, storing counts up to 255 per run. The first two bytes of the
encoded result store the number of columns and rows respectively.

out: encoded; An array that will store the resulting RLE-encoded bytes.
in:  packed;  The packed photo data to be encoded.
in:  rows;    The number of rows in the photo.
in:  cols;    The number of columns in the photo.

Return: The total number of bytes used in the encoded result, or -1 if
        the photo dimensions exceed 255 × 255.
*/

int rle_encode(unsigned char encoded_result[], const unsigned char packed[], int rows, int cols){ 
	if(rows > 255 || cols > 255){return -1;}
	
	unsigned char run = 0;
	int index = 2;
	unsigned char current = 1;
	
	int packedSize = (rows*cols)/8;

	encoded_result[0] = rows;
	encoded_result[1] = cols;

	for(int i = 0; i<packedSize;i++){
		unsigned char byte = packed[i];
		for(int j = 7; j>= 0;j--){
			unsigned char bit = (byte>>j)&1;
			if(bit == current){
				run++;
				if(run == 255){
					encoded_result[index++] = run;
					encoded_result[index++] = 0;
					run = 0;
				}
			}else{
				encoded_result[index++] = run;
				current = bit;
				run = 1;
			}
		}
	}
	encoded_result[index++] = run;
	
	printf("\n");
	return index;
}

/*
Prints a Run-Length Encoded (RLE) photo to the console as ASCII art, using
'#' for 1-runs and spaces for 0-runs. The first two bytes of the input
represent the number of columns and rows in the photo.

in: encoded; An array of RLE-encoded bytes (produced by rle_encode()).

Return: The total number of pixels printed (rows × cols).
*/

int print_rle(const unsigned char encoded[]){
	//printing packed photo
	int rows = encoded[0];
	int cols = encoded[1];
	int length = rows*cols;
	int count = 0;
	int run = 2;
	int newLines = 0;
	unsigned char bit = 0;
	
	while(count < length){
		for(int i = 0; i<encoded[run];i++){
			if(newLines == cols){
				printf("\n");
				newLines = 0;
			}
			if(bit == 0){
				printf("#");
			}else{
				printf(" ");
			}
			newLines++;
			count++;
		}
		bit = !bit; run++;
	}
	
	printf("\n");
	return count;


    return 0;
}
/* Your code for the function implementations in photo.h should be place here.*/
