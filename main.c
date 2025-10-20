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
            		unsigned char packed[MAX_PHOTO_SIZE / 8];
			unsigned char rle[MAX_PHOTO_SIZE];

			print_ascii(dest, rows, cols);
			int packedSize = pack_bits(packed, dest, size);
			print_packed_bits(packed, rows, cols);
			int rleSize = rle_encode(rle, packed, rows, cols);
			print_rle(rle);

			printf("%d %d %d\n", size, packedSize, rleSize);
			size = get_next_photo(dest, &rows, &cols);
		}
	}


    return 0;
}
