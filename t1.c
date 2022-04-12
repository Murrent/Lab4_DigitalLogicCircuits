#include <stdio.h>

void buf_in(unsigned char* buffer) {
    const unsigned int size = 16;
    for (int i = 0; i < size; i++) {
        printf("%d ", buffer[i]);

    }
}

int main() {
    unsigned char buffer[16] = {0};
    buf_in(buffer);
    return 0;
}
