#include <stdio.h>
#include "camera.h"
#include "photo.h"

int main(void) {
    // Create your arrays here. Remember to use correct sizes as defined in camera.h
    // And to handle error states in here, as main() handles the control flow.
    // Main shouldn't have any functions other than the main() function and any test / helper functions only needed inside main.
	
	
	unsigned char dest[MAX_PHOTO_SIZE];
	int rows, cols;
	int size = get_next_photo(dest, &rows, &cols);
	if(size%8 != 0){
		printf("packing error, invalid length");
	}else{		
		while (size !=0){
			int packedSize = size/8;
			unsigned char packed[packedSize];

			//printing original photo	
			for (int i = 0;i<rows;i++){
				for (int j = 0;j<cols;j++){
					if (dest[j+(cols*i)]== 49){
						printf("*");
					}else{
						printf(".");
					}
				}printf("\n");
		
			}
			//packing photo
			for(int i = 0;i<packedSize;i++){
				unsigned char byte = 0;
				for(int j = 0;j<8;j++){
					unsigned char entry = dest[i*8 + j];
					if (entry == '1'){
						 byte += (1<<(7-j));
					}	
				}packed[i] = byte; 
			}
			//printing packed photo
			int newLine = 0;	
			for(int x = 0;x<packedSize;x++){
				for(int y = 7;y>=0;y--){
					if(newLine == cols){
						printf("\n");
						newLine = 0;
					}
					if(packed[x] & (1<<y)){
						printf("+");
					}else{
						printf("-");
					}
					newLine++;	

				}
				
			}printf("\n");
			//rlencoding the photo
			unsigned char run = 1;
			unsigned char rle[MAX_PHOTO_SIZE+1];
			int index = 1;
			unsigned char current = dest[0];
			rle[0] = current;
			for(int i = 1;i<size;i++){
				if (dest[i] == current){
					run++;
					if(run == 255){
						rle[index++] = run;
						run = 0;
					}
				}else{
					rle[index++] = run;
					current = dest[i];
					run = 1;
				}
			}
			rle[index++] = run;
			//printing packed photo
			int newLines = 0;
			int bit = rle[0];	
			for(int x = 1;x<index;x++){
				for (int y = 0; y < rle[x];y++){
					if(newLines == cols){
						printf("\n");
						newLines = 0;
					}
					if(bit == '1'){
						printf("#");
					}else{
						printf(" ");
					}
					newLines++;
				}if(bit == '1'){
					bit = '0';
				}else{
					bit = '1';
				}
			}			
			printf("\n");	


			printf("\n");
			printf("%d %ld %d\n", size, sizeof(packed), index);
			
			size = get_next_photo(dest, &rows, &cols);
	
		}
	}

    return 0;
}
