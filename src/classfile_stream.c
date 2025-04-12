#include "classfile_stream.h"

void loader_read_bytes(Loader *loader, uint8_t *buf, size_t n) {
  if (loader->error != 0) return;

  size_t read = fread(buf, 1, n, loader->file);
  if (read != n) {
    loader->error = 1;
  }
}

uint8_t loader_u1(Loader *loader) {
  uint8_t buf[1];
  loader_read_bytes(loader, buf, 1);
  return buf[0];
}

uint16_t loader_u2(Loader *loader) {
  uint8_t buf[2];
  loader_read_bytes(loader, buf, 2);
  return (uint16_t)((buf[0] << 8) | buf[1]);
}

uint32_t loader_u4(Loader *loader) {
  uint8_t buf[4];
  loader_read_bytes(loader, buf, 4);
  return (uint32_t)(((uint32_t)buf[0] << 24) | ((uint32_t)buf[1] << 16) |
                    ((uint32_t)buf[2] << 8) | (uint32_t)buf[3]);
}

uint64_t loader_u8(Loader *loader) {
  uint8_t buf[8];
  loader_read_bytes(loader, buf, 8);
  return (uint64_t)((uint64_t)buf[0] << 56) | ((uint64_t)buf[1] << 48) |
         ((uint64_t)buf[2] << 40) | ((uint64_t)buf[3] << 32) |
         ((uint64_t)buf[4] << 24) | ((uint64_t)buf[5] << 16) |
         ((uint64_t)buf[6] << 8) | (uint64_t)buf[7];
}