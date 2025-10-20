#include <stdio.h>
#include "camera.h"
#include "photo.h"
			
int print_ascii(const unsigned char photo[], int rows, int cols){			
	//printing original photo
	for (int i = 0;i<rows;i++){
		for (int j = 0;j<cols;j++){
			if (photo[j+(cols*i)] == '1'){
				printf("*");
			}else{
				printf(".");
			}
		}printf("\n");		
	}return 0;
}

int pack_bits(unsigned char packed[], const unsigned char photo[], int num_chars){
	//packing photo
	unsigned char byte = 0;
	for(int i = 0;i<num_chars;i++){
		byte = 0;
		for(int j = 0;j<8;j++){
			if (photo[i*8 + j] == '1'){
				 byte += (1<<(7-j));
			}	
		}packed[i] = byte; 
	
	}return 0;
}

int print_packed_bits(const unsigned char photo[], int rows, int cols){
	//printing packed photo
	int maskSize = rows*cols/8;	
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
		}
	}return maskSize; 
}
	
int rle_encode(unsigned char encoded_result[], const unsigned char packed[], int rows, int cols){ 
	unsigned char run = 0;
	int index = 2;
	encoded_result[0] = rows;
	encoded_result[1] = cols;
	unsigned char current = 0;
	int packedSize = (rows*cols)/8;

	for(int i = 0; i<packedSize;i++){
		unsigned char byte = packed[i];
		for(int j = 7; j>= 0;j--){
			unsigned char bit = (byte>>j)&1;
			if(bit == current){
				run++;
				if(run == 255){
					encoded_result[index++] = run;
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
	return index;
}

int print_rle(const unsigned char encoded[]){
	//printing packed photo
	int rows = encoded[0];
	int cols = encoded[1];
	int length = rows*cols/8;
	int count = 0;
	int bit = 0;
	int newLines = 0;

	for(int i = 2;i<length;i++){
		for(int j  = 0; j<encoded[i];j++){
			if(newLines == cols){
				printf("\n");
				newLines = 0;
			}
			if(bit=='0'){
				printf("#");
			}else{
				printf(" ");
			}newLines++;
		}if(bit=='1'){
			bit = '0';
		}else{
			bit = '1';
		}
	}printf("\n");
	return length;

}
/* Your code for the function implementations in photo.h should be place here.*/
