#include "Bitmap.h"

int main() {
    Bitmap bmp;
    bmp.set(10);
    bmp.print(11);
    printf("\n%s\n", bmp.bits2string(11));
    return 0;
}