#include <fcntl.h>

const unsigned int length = 16;

unsigned char writeBuffer[16] = {0};
unsigned int writePosition = 0;
int destFile;

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

void writeToFile(char *string, unsigned int writeLength) {
    for (int i = 0; i < writeLength; i++) {
        writePosition = i;
        buf_out(string[i]);
    }
    // Flushing the leftover data
    buf_flush();
}


int main(int argc, char **argv) {
    if (argc == 2) {
        destFile = open(argv[1], O_WRONLY);

        writeToFile("writing testings", 16);

        close(destFile);
    }
    return 0;
}
