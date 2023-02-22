#pragma once
#ifndef FUNCIONES_H
#define FUNCIONES_H
#include<cstdint>
struct EjecutableWindows{
 uint8_t id[2];
 uint8_t x[58];
 uint32_t offset;
}__attribute__((packed));

struct EjecutableLinux{
 uint8_t id[4];
 uint8_t type;
}__attribute__((packed));

struct GIF{
  uint8_t id[4];
  char m[2];
  uint16_t width;
  uint16_t height;

}__attribute__((packed));

struct PNG{
  uint8_t id[8];
  char y[8];
  uint8_t width[4];
  uint8_t height[4];

}__attribute__((packed));
struct BMP{
uint8_t id[2];
uint32_t size;
uint16_t res1;
uint16_t res2;
uint32_t offset;
//Header info
uint32_t sizeheader;
int32_t width;
int32_t height;
uint16_t colorplane;
uint16_t bpp;
uint32_t compression;
uint32_t imageSize;
uint32_t hResolution;
uint32_t vResolution;
uint32_t numberColors;
uint32_t importntColors;

}__attribute__((packed));
struct JPG{
    unsigned char id[10];

}__attribute__((packed));

struct TIFF{
    uint8_t id[4];

}__attribute__((packed));

struct SVG{
  uint8_t id[5];

}__attribute__((packed));

struct ZIP{
  uint8_t id[4];

}__attribute__((packed));
struct RAR{
  char id[7];

}__attribute__((packed));
struct GZIP{
  uint8_t id[3];
 

}__attribute__((packed));
struct BZIP{
  char id[3];

}__attribute__((packed));
struct XZ{
  uint8_t id[6];
 

}__attribute__((packed));
class Funciones{
public:
 Funciones(){}
 int VerificacionDeArchivo(char*);
 uint32_t toLittleEndian(uint8_t ,uint8_t ,uint8_t,uint8_t );
};
#endif