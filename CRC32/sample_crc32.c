#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>

//#define LOGD(...)
#define LOGD(...) printf(__VA_ARGS__)

unsigned int crc_table[256];
unsigned int crc_table_extension[256];

void make_crc_table(void) {
    for (unsigned long int i = 0; i < 256; i++) {
        unsigned long int c = i;
        for (int j = 0; j < 8; j++) {
            c = (c & 1) ? (0xEDB88320 ^ (c >> 1)) : (c >> 1);
        }
        crc_table[i] = c;
    }
}

unsigned long int crc32(unsigned char *buf, size_t len) {
    unsigned long int c = 0xFFFFFFFF;
    for (size_t i = 0; i < len; i++) {
        c = crc_table[(c ^ buf[i]) & 0xFF] ^ (c >> 8);
    }
    return c ^ 0xFFFFFFFF;
}

void make_crc_table_extension(void){
    for(unsigned long int i=0; i<256; i++){
        unsigned long int c = i << 24;
        for( int j=0; j<8; j++){
            c = ( c << 1) ^ ( ( c & 0x80000000) ? 0x04C11DB7 : 0);
        }
        crc_table_extension[i] = c;
    }
}

unsigned long int crc32_extension(unsigned char *buf, int len){
    unsigned long int c = 0xffffffff;
    for (int i = 0; i < len; i++)    {
        c = (c << 8) ^ crc_table_extension[((c >> 24) ^ buf[i]) & 0xff];
    }
    return c;
}



static unsigned long int update_crc(unsigned long int crc, unsigned char *buf, int len)
{
	unsigned long int c = crc;
	unsigned char b;
	int n,i;

	for (n=0; n<len; n++)
	{
		b = buf[n];
		for (i=0; i<8; i++)
		{
			if (((c & 0x80000000L)?-1:0) ^ ((b & 0x80)?-1:0))
				c = (c << 1) ^ 0x04c11db7;
			else
				c = c << 1;
				b = b << 1;
		}
	}
	return c;
}

int main(int argc, char *argv[])
{
	unsigned char temp[] = {0,1,2,3,4,5,6,7,8,9};

	printf("Start crc32 \n");
	make_crc_table();
	make_crc_table_extension();
	printf("[1] crc32 = %x \n",crc32(temp, sizeof(temp)));
	printf("[2] crc32 = %x \n",update_crc(0xffffffffL, temp, sizeof(temp)));	
	printf("[3] crc32 = %x \n",crc32_extension(temp, sizeof(temp)));
	return 0;
}




