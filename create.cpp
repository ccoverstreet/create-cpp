/*
  USAGE:
    ./create filename [date]
*/

#include <cstdio>
#include <cwchar>
#include <cstdlib>
#include <cstring>
#include <ctime>

using namespace std;

bool hasFileType(char* fileName) {
  char* type = strstr(fileName, ".cpp");
  if(!type) {
    return 0;
  }
  if(strlen(type) > 4) {
    return 0;
  }
  return 1;
}

int main(int argc, char** argv) {
  if(argc < 2) {
    printf("Usage: %s filename [date]\n", argv[0]);
    exit(0);
  }

  // Create new file
  char fileName[255];
  strcpy(fileName, argv[1]);

  // Add file type if needed
  if(!hasFileType(fileName)) {
    strcat(fileName, ".cpp");
  }

  // Err if filename too long
  if(strlen(fileName) > 32) {
    printf("Filename too long. Max 32 characters.");
  }

  // Create the file
  FILE* fout;
  fout = fopen(fileName, "w");

  // Setup
  wchar_t border[] = {L'═', L'╔', L'╗', L'╝', L'╚', L'─', L'╟', L'╢'};

  // Calc the width
  char width = 4 + strlen("Author: Kuba Zeligowski");
  width = (width > (strlen(fileName) + 6)) ? width : (strlen(fileName) + 6);
  char spacing;
  wchar_t space[width - 3];

  // Author line
  wchar_t authorLine[width + 5];
  spacing = width - 4 - strlen("Author:Kuba Zeligowski");

  wmemset(space, 0, width - 3);
  wmemset(space, L' ', spacing);
  wcscpy(authorLine, L"Author:");
  wcscat(authorLine, space);
  wcscat(authorLine, L"Kuba Zeligowski");

  wprintf(L"|%ls|\n", authorLine);

  // Date line
  wchar_t dateLine[width + 3];
  wchar_t date[strlen("mmm dd, YYYY") + 1];
  spacing = width - 3 - strlen("Date:mmm dd, YYYY") - 1;
  time_t timer;

  
  wmemset(space, 0, width - 3);
  wmemset(space, L' ', spacing);
  wmemset(dateLine, 0, width + 3);
  time(&timer);
  wcsftime(date, strlen("mmm dd, YYYY") + 1, L"%b %d, %Y", localtime(&timer));
  wprintf(L"%ls\n", date);

  wcscpy(dateLine, L"Date:");
  wcscat(dateLine, space);
  wcscat(dateLine, date);

  wprintf(L"%ls\n", dateLine);

  fwprintf(fout, L"|%ls|\n|%ls|\n", authorLine, dateLine);

  return 0;
}








