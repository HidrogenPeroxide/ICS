#include <stdio.h>
typedef unsigned char *byte_pointer;
void show_bytes(byte_pointer start, size_t len)
{
    for (int i = 0; i < len; i++)
    {
        printf("%.2x\t", start[i]);
    }
    printf("\n");
}
void show_int(int x)
{
    show_bytes((byte_pointer)&x, sizeof(int));
}
void show_double(double x) {
    show_bytes((byte_pointer)&x, sizeof(double));
}
void show_float(float x) {
    show_bytes((byte_pointer)&x, sizeof(float));
}

int main(void)
{
    int x = 0x12345678;
    //show_int(x);
    //show_double(x);
    //show_float(x);
}