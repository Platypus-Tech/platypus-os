#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct initrd_header {
  uint8_t magic;
  char name[64];
  uint32_t offset;
  uint32_t length;
};

int main(int argc, char *argv[]) {

  int nheaders = (argc - 1) / 2;
  struct initrd_header headers[64];

  printf("Size of Header: %ld\n", sizeof(struct initrd_header));

  unsigned int off = sizeof(struct initrd_header) * 64 + sizeof(int);

  for (int i = 0; i < nheaders; i++) {
    printf("Writing file %s->%s at 0x%x\n", argv[i * 2 + 1], argv[i * 2 + 2],
           off);
    strcpy(headers[i].name, argv[i * 2 + 2]);
    headers[i].offset = off;
    FILE *stream = fopen(argv[i * 2 + 1], "r");

    if (stream == 0) {
      printf("Error: %s : file not found\n", argv[i * 2 + 1]);
      return 1;
    }

    fseek(stream, 0, SEEK_END);
    headers[i].length = ftell(stream);
    off += headers[i].length;
    fclose(stream);
    headers[i].magic = 0xBF;
  }

  FILE *wstream = fopen("./initrd.img", "w");
  unsigned char *data = (unsigned char *)malloc(off);
  fwrite(&nheaders, sizeof(int), 1, wstream);
  fwrite(headers, sizeof(struct initrd_header), 64, wstream);

  for (int i = 0; i < nheaders; i++) {
    FILE *stream = fopen(argv[i * 2 + 1], "r");
    unsigned char *buf = (unsigned char *)malloc(headers[i].length);
    fread(buf, 1, headers[i].length, stream);
    fwrite(buf, 1, headers[i].length, wstream);
    fclose(stream);
    free(buf);
  }

  fclose(wstream);
  free(data);

  return 0;
}
