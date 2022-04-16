#include <stdio.h>
#include <fcntl.h>
#include <time.h>

const unsigned int length = 64;

unsigned char readBuffer[64] = {0};
unsigned int readPosition = 0;
int sourceFile;

unsigned char writeBuffer[64] = {0};
unsigned int writePosition = 0;
int destFile;

// Returns the next char from the file using the buffer (type int, so we can read the EOF value)
int buf_in() {
    unsigned int index = readPosition % length; // Buffer index ranging from 0-15
    if (index == 0) // We always read new data into the buffer at index 0
        read(sourceFile, readBuffer, length);
    if (readPosition == filelength(sourceFile)) // Return EOF (-1) if we reach the end
        return EOF;
    return readBuffer[index]; // Simply return the byte at the index
}

void buf_flush() {
    unsigned int count = writePosition % length; // The length of the buffer we want to flush
    if (count == 0) // If 0, we want to flush the whole buffer
        count = length;
    else // Else we want to flush count + 1 bytes
        count++;
    // Writing "count" length of data to the file from the buffer
    write(destFile, writeBuffer, count);
}

void buf_out(unsigned char byte) {
    unsigned int index = writePosition % length;
    // If the index is 0, the buffer has been fully written
    // to as long as write position is not 0, so we flush it
    if (index == 0 && writePosition != 0)
        buf_flush();
    // Writing the byte to the buffer
    writeBuffer[index] = byte;
}

// Reads and writes up to "copyLength" bytes of a file, returns early if file is smaller
void copy(unsigned int copyLength) {
    for (int i = 0; i < copyLength; i++) {
        readPosition = i;
        int byte = buf_in(); // Getting the byte value
        if (byte == EOF) break; // Exit loop early if end is reached
        writePosition = readPosition; // Updating the write position
        buf_out(byte); // Writing the byte to the buffer
    }
    buf_flush();
}


int main(int argc, char **argv) {
    if (argc == 3) {
        // Opening file in read only mode
        sourceFile = open(argv[1], O_RDONLY);
        // Opening file in write only mode
        destFile = open(argv[2], O_WRONLY);

        clock_t t = clock(); // Start

        copy(256000);

        long fLength = filelength(sourceFile);
        float et = (float) clock() - (float) t; // Delta
        float difference = ((et) / (float) CLOCKS_PER_SEC) * 1000; // Delta time in milliseconds
        printf("Execution time: %f, average byte time: %f, file length: %ld\n",
               difference, difference / (float) fLength, fLength);

        close(destFile);
        close(sourceFile);
    }
    return 0;
}
