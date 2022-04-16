#include <stdio.h>
#include <fcntl.h>

const unsigned int length = 16;

unsigned char readBuffer[16] = {0};
unsigned int readPosition = 0;
int sourceFile;

// Returns the next char from the file using the buffer (type int, so we can read the EOF value)
int buf_in() {
    unsigned int index = readPosition % length; // Buffer index ranging from 0-15
    if (index == 0) // We always read new data into the buffer at index 0
        read(sourceFile, readBuffer, length);
    if (readPosition == filelength(sourceFile)) // Return EOF (-1) if we reach the end
        return EOF;
    return readBuffer[index]; // Simply return the byte at the index
}

// Reads and prints up to "readLength" bytes a file, returns early if file is smaller
void readAndPrint(unsigned int readLength) {
    printf("Read:\n");
    for (int i = 0; i < readLength; i++) {
        readPosition = i;
        int byte = buf_in(); // Getting the byte value
        printf("%c", byte);
        if (byte == EOF) break; // Exit loop early if end is reached
    }
    printf("\n");
}

int main(int argc, char **argv) {
    if (argc == 2) {
        // Opening file in read only mode
        sourceFile = open(argv[1], O_RDONLY);
        readAndPrint(256000);
        close(sourceFile);
    }
    return 0;
}
