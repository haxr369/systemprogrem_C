// crt_fread_s.c
// Command line: cl /EHsc /nologo /W4 crt_fread_s.c
//
// This program opens a file that's named FREAD.OUT and
// writes characters to the file. It then tries to open
// FREAD.OUT and read in characters by using fread_s. If the attempt succeeds,
// the program displays the number of actual items read.

#include <stdio.h>    // C standard library ex)stdio. stdlib ..... 마이크로소프트에서는  C Run Time libaray CRT라고 됨.

#define BUFFERSIZE 30
#define DATASIZE 25
#define ELEMENTCOUNT 2
#define ELEMENTSIZE (DATASIZE/ELEMENTCOUNT)
#define FILENAME "FREAD.OUT"

int main(void)
{
    FILE* stream;               // #1 파일 포인터를 정의
    char list[30];
    int  i, numread, numwritten;

    for (i = 0; i < DATASIZE; i++)
        list[i] = (char)('z' - i);
    list[DATASIZE] = '\0'; // terminal null so we can print it

    // Open file in text mode:
    if (fopen_s(&stream, FILENAME, "w+t") == 0)   // #2 파일 포인터로 파일을 open
    {
        // Write DATASIZE characters to stream
        printf("Contents of buffer before write/read:\n\t%s\n\n", list);
        numwritten = fwrite(list, sizeof(char), DATASIZE, stream); //#3파일에 글을 작성 읽고 쓰기할 때 파일 포인터를 입력!
        printf("Wrote %d items\n\n", numwritten);
        fclose(stream); //#4 파일을 작성하고 닫기
    }
    else {
        printf("Problem opening the file\n");
        return -1;
    }

    if (fopen_s(&stream, FILENAME, "r+t") == 0) {
        // Attempt to read in characters in 2 blocks of 11
        //버퍼사이즈는 list의 사이즈, 
        //stream의 
        numread = fread_s(list, BUFFERSIZE, ELEMENTSIZE, ELEMENTCOUNT, stream); //#5파일을 읽음
        printf("Number of %d-byte elements read = %d\n\n", ELEMENTSIZE, numread);
        printf("Contents of buffer after write/read:\n\t%s\n", list);
        fclose(stream);                                             //#6파일을 닫음
    }
    else {
        printf("File could not be opened\n");
        return -1;
    }
}