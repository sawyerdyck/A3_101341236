#include <stdio.h>
#include "camera.h"
#include "photo.h"

/*
Prints the ASCII image of a photo using '*' for '1' pixels and
'.' for '0' pixels.

in: photo; An array of chars ('1' or '0') representing the photo.
in: rows;  The number of rows in the photo.
in: cols;  The number of columns in the photo.

Return: 0 if the photo was printed successfully, or -2 if the input contained
        an invalid character.
*/


int print_ascii(const unsigned char photo[], int rows, int cols){			
	//printing original photo
	for (int i = 0;i<rows;i++){//iterate through rows and columsn
		for (int j = 0;j<cols;j++){
			unsigned char bit = photo[i*cols+j];//access current char 
			if (bit == '1'){
				printf("*");
			}else if (bit == '0'){
				printf(".");
			}else{
				return ERR_UNKNOWN_CHARACTER;
			}
		}printf("\n");		
	}printf("\n");return ERR_OK;
}

/*
Converts an ASCII photo into a packed bit
representation, where each byte represents 8 pixels.

out: packed; An array to store the packed bytes.
in:  photo;  The ASCII photo to convert.
in:  num_chars; The total number of chars in the photo.

Return: The number of packed bytes produced, or -1 if the input size is not
        a multiple of 8/-2 if contains invalid characters.
*/

int pack_bits(unsigned char packed[], const unsigned char photo[], int num_chars){
	if(num_chars%8 != 0){return ERR_INVALID_PHOTO_SIZE;}//check that size is a multiple of 8
	//packing photo
	unsigned char byte = 0;
	for(int i = 0;i<num_chars;i++){//iterate through each byte for expected packed size
		byte = 0;
		for(int j = 0;j<8;j++){
			unsigned char bit = photo[i*8+j];//access current bit
			if (bit == '1'){
				 byte += (1<<(7-j));//add bit to next position in current byte
			}else if(bit != '0'){
				return ERR_UNKNOWN_CHARACTER;
			}	
		}packed[i] = byte;// add each byte to packed array
	
	}return num_chars;
}

/*
Prints a packed photo to the console using '+' for 1-bits and '-' for 0-bits.
The bits are unpacked MSB-first from each byte and printed in order.

in: photo; An array of packed bytes representing the photo.
in: rows;  The number of rows in the photo.
in: cols;  The number of columns in the photo.

Return: The number of bytes that were printed.
*/

int print_packed_bits(const unsigned char photo[], int rows, int cols){
	//printing packed photo
	int maskSize = rows * cols;
	int toPrint = maskSize/8;	
	int newLine = 0;

	for(int i = 0;i<toPrint;i++){//iterate through each byte
		for(int y = 7; y>=0;y--){//iterate through each bit (largest to smallest)
			if(newLine == cols){//check for new line
				printf("\n");
				newLine = 0;
			}
			if(photo[i] & (1<<y)){//now that bits are stored im just using bool logic and getting next position in current byte
				printf("+");
			}else{
				printf("-");
			}newLine++;
			if (newLine >= toPrint){break;}
		}
	}printf("\n");return toPrint; 
}

/*
Encodes a packed photo using Run-Length Encoding. Alternates runs of
0s and 1s, storing up to 255 bits per run. The first two bytes of the
encoded result store the number of columns and rows.

out: encoded; An array that will store the RLE-encoded bytes.
in:  packed;  The packed photo to be encoded.
in:  rows;    The number of rows in the photo.
in:  cols;    The number of columns in the photo.

Return: The total number of bytes used in the result, or -1 if
        the photo dimensions exceed 255 × 255.
*/

int rle_encode(unsigned char encoded_result[], const unsigned char packed[], int rows, int cols){ 
	if(rows > 255 || cols > 255){return ERR_INVALID_PHOTO_SIZE;}//checking proper size
	
	unsigned char run = 0;//counter for run length
	int index = 2;//starting ind is 2 because first 2 spots are predetermined
	unsigned char current = 1;//assuming first bit is a 1
	
	int packedSize = (rows*cols)/8;

	encoded_result[0] = rows;//storing ros and cols in first 2 pos
	encoded_result[1] = cols;

	for(int i = 0; i<packedSize;i++){//iterate through each byte
		unsigned char byte = packed[i];
		for(int j = 7; j>= 0;j--){//iterate through each bit (;largest to smallest)
			unsigned char bit = (byte>>j)&1;
			if(bit == current){//when run continues
				run++;
				if(run == 255){//checking that run isnt exceeding 255
					encoded_result[index++] = run;
					encoded_result[index++] = 0;//add a 0 run to other bit to continue current run without going over 255
					run = 0;
				}
			}else{//when run ends
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
'#' for 1-runs and spaces for 0-runs. 

in: encoded; An array of RLE-encoded bytes.

Return: The total number of pixels printed.
*/

int print_rle(const unsigned char encoded[]){
	//printing packed photo
	int rows = encoded[0];//getting dimesions from array
	int cols = encoded[1];
	int length = rows*cols;

	int count = 0;//bits printed
	int run = 2;//current run being printed
	int newLines = 0;
	unsigned char bit = 1;//assuming first bit is 1
	
	while(count < length){
		for(int i = 0; i<encoded[run];i++){//iterate through individual run
			if(newLines == cols){
				printf("\n");
				newLines = 0;
			}
			if(bit == 1){
				printf("#");
			}else{
				printf(" ");
			}
			newLines++;
			count++;
		}
		bit = !bit; run++;//since were assuming rle starts with a run value for a 1 run, i just start with bit set to 1 and alternate after every run is printed
	}
	
	printf("\n");
	return count;


    return ERR_OK;
}
/* Your code for the function implementations in photo.h should be place here.*/
