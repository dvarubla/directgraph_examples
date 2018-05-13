#include <directgraph.h>
#include <stdio.h>

#pragma pack (1)
struct head {
    short bftype;
    long  bfsize;
    short rez1, rez2;
    long  bfoffbits;
    long  bisize;
    long  biwidth;
    long  biheight;
    short biplanes;
    short bibitcount;
    long  bicompression;
    long  bisizeimage;
    long  bix;
    long  biy;
    long  biclrused;
    long  biclrimp;
} head_file;
#pragma pack ()

int Offset(int width)
{
    width *= 3;
    int offset = 0;
    while (width % 4 != 0) {
        width++;
        offset++;
    }
    return offset;
}

void mainx()
{
    resize(800, 600);
    FILE *f;
    f = fopen("_carib_TC.bmp", "rb");
    fread(&head_file, sizeof(head_file), 1, f);
    int width = head_file.biwidth;
    int height = head_file.biheight;
    byte c[3];
    int offset = Offset(width);
    for (int i = height - 1; i >= 0; i--) {
        for (int j = 0; j < width; j++) {
            fread(c, 3, 1, f);
            putpixel(j, i, RGB(c[2], c[1], c[0]));
        }
        fseek(f, offset, SEEK_CUR);
    }
    fclose(f);
}
