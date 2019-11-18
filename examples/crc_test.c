#include <stdint.h>
#include <string.h>
#include <limits.h>
#include <stdlib.h>
#include <stdio.h>
#include <stddef.h>
#include "crc32.h"
#include "crc16_xmodem.h"

int main(int argc, char* argv[])
{
    const char *data = "123456789";
	size_t length = strlen(data);
    uint32_t result = crc32((const uint8_t*)data, length);
	printf("CRC32 for %s is %x\n", data, result);
	result = crc16_xmodem((const uint8_t*)data, length);
	printf("CRC16-XMODEM for %s is %x\n", data, result);
	if (argc > 1)
	{
	    FILE* fp = fopen(argv[1], "rb");
	    if (fp == NULL)
	    {
	        fprintf(stderr, "Could not open %s", argv[1]);
	        exit(1);
	    }
	    fseek(fp, 0L, SEEK_END);
	    size_t file_size = ftell(fp);
	    rewind(fp);
	    uint8_t *data = (uint8_t *)malloc(file_size);
		if (data)
		{
			size_t nread = fread(data, 1, file_size, fp);
			result = crc32(data, nread);
			printf("CRC32 of file %s is %08x\n", argv[1], result);
		}
		else
		{
			fprintf(stderr, "Failed to allocate memory buffer of %zu for file %s\n",
				file_size, argv[1]);
		}
	}
}
