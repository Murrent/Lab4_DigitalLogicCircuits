#include <stdio.h>
#include <fcntl.h>

const unsigned int length = 16;
unsigned char readBuffer[16] = {0};
unsigned int readPosition = 0;
int sourceFile;

unsigned char writeBuffer[16] = {0};
unsigned int writePosition = 0;
int destFile;

unsigned int buf_in() {
    unsigned int index = readPosition % length;
    if (index == 0)
        read(sourceFile, readBuffer, length);
    if (readPosition == filelength(sourceFile))
        return EOF;
    return readBuffer[index];
}

void readAndPrint(unsigned int readLength) {
    printf("Read:\n");
    for (int i = 0; i < readLength; i++) {
        readPosition = i;
        unsigned int byte = buf_in();
        printf("%c", byte);
        if (byte == EOF) break;
    }
    printf("\n");
}

void buf_flush() {
    unsigned int count = writePosition % length;
    if (count == 0)
        count = length;
    else
        count++;
    write(destFile, writeBuffer, count);
}

void buf_out(unsigned char byte) {
    unsigned int index = writePosition % length;
    if (index == 0 && writePosition != 0)
        buf_flush();
    writeBuffer[index] = byte;
}

void copy(unsigned int readLength) {
    printf("Read:\n");
    for (int i = 0; i < readLength; i++) {
        readPosition = i;
        unsigned int byte = buf_in();
        if (byte == EOF) break;
        writePosition = readPosition;
        buf_out(byte);
    }
    buf_flush();
    printf("\n");
}



int main(int argc, char **argv) {
    if (argc == 3) {
        sourceFile = open(argv[1], O_RDONLY);
        destFile = open(argv[2], O_WRONLY);
        copy(256);

        close(destFile);
        close(sourceFile);
    }
    return 0;
}
