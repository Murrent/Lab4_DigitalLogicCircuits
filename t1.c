#include <stdio.h>
#include <fcntl.h>

const unsigned int length = 16;
unsigned char buffer[16] = {0};
unsigned int position = 0;

const char *source = "test.txt";
int sourceFile;
const char *dest = "destination.txt";
int destFile;

unsigned int buf_in() {
    unsigned int index = position % length;
    if (index == 0)
        read(sourceFile, buffer, length);
    if (position == filelength(sourceFile))
        return EOF;
    return buffer[index];
}

void readAndPrint(unsigned int readLength) {
    printf("Read:\n");
    for (int i = 0; i < readLength; i++) {
        position = i;
        unsigned int byte = buf_in();
        printf("%c", byte);
        if (byte == EOF) break;
    }
    printf("\n");
}

void buf_flush() {
    unsigned int count = position % length;
    if (count == 0)
        count = length;
    printf("Writing %s %d %d \n", buffer, position, count);
    write(destFile, buffer, count);
}

void buf_out(unsigned char byte) {
    unsigned int index = position % length;
    printf("buf_out %d\n", index);
    if (index == 0 && position != 0)
        buf_flush();
    buffer[index] = byte;
}

void copy(unsigned int readLength) {
    printf("Read:\n");
    for (int i = 0; i < readLength; i++) {
        position = i;
        unsigned int byte = buf_in();
        printf("bytes %s\n", buffer);
        if (byte == EOF) break;
        buf_out(byte);
    }
    buf_flush();
    printf("\n");
}

int main() {
    sourceFile = open(source, O_RDONLY);
    destFile = open(dest, O_WRONLY);
    copy(100);

    close(destFile);
    close(sourceFile);
    return 0;
}
