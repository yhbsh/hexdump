#include <stdio.h>
#include <stdlib.h>

#define MAX_BUF_SIZE 1024 * 500 // 500 kb

size_t read_file(void *buf, const char *file_path) {
  FILE *file = fopen(file_path, "rb");

  fseek(file, 0, SEEK_END);
  size_t file_size = ftell(file);
  fseek(file, 0, SEEK_SET);

  if (file_size >= MAX_BUF_SIZE) {
    fprintf(stderr, "[ERROR]: file is too large\n");
    exit(1);
  }

  fread(buf, 1, file_size, file);

  fclose(file);

  return file_size;
}

void hexdump(void *buf, size_t size) {
  char *data = buf;
  for (size_t i = 0; i < size - 1; i += 2) {
    if (i % 16 == 0) {
      if (i > 0) printf("\n");
      printf("%07zx ", i);
    }

    printf("%02x%02x ", data[i + 1], data[i]);
  }
  printf("\n");
}

int main(int argc, char **argv) {
  if (argc != 2) {
    fprintf(stderr, "[Usage]: ./main [input]\n");
    return 1;
  }

  char buf[MAX_BUF_SIZE] = {0};

  size_t file_size = read_file(buf, argv[1]);

  hexdump(buf, file_size);


  return 0;
}
