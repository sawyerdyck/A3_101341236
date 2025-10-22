#include <stdio.h>
#include "camera.h"
#include "photo.h"
int main(void) {

	unsigned char dest[MAX_PHOTO_SIZE];
        int rows, cols;
        int size = get_next_photo(dest, &rows, &cols);
        if(size%8 != 0){
                printf("packing error, invalid length");
        }else{
                while (size !=0){
                        unsigned char packed[PACKED_PHOTO_SIZE] = {0};
                        unsigned char rle[ENCODED_PHOTO_SIZE] = {0};
			
                        print_ascii(dest, rows, cols);

                        int packedSize = pack_bits(packed, dest, size/8);
                    	camera_test_packed(dest, packed, rows, cols);
			print_packed_bits(packed, rows, cols);
                        
			int rleSize = rle_encode(rle, packed, rows, cols);
                        camera_test_encoding(packed, rle, rows, cols);
			print_rle(rle);
                        
			printf("ASCII Used: %d | Packed Used: %d | Encoded Used: %d\n", size, packedSize, rleSize);
                        size = get_next_photo(dest, &rows, &cols);
                }
        }    
	return 0;
}

