#include <stdio.h>
#include "camera.h"
#include "photo.h"
			
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
