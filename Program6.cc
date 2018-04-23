/*
 * Andrew Hosang
 * ajh150830@utdallas.edu
 * CS 3377.501
 * Program 6
 */

#include <iostream>
#include <sstream>
#include <fstream>
#include <iomanip>
#include <stdint.h>
#include <string>
#include "cdk.h"


#define MATRIX_WIDTH 3
#define MATRIX_HEIGHT 5
#define BOX_WIDTH 30
#define MATRIX_NAME_STRING "Test Matrix"

using namespace std;

const int maxRecordStringLength = 25;

class BinaryFileHeader
{
public:
  uint32_t magicNumber; /* Should be 0xFEEDFACE */
  uint32_t versionNumber;
  uint64_t numRecords;
};

class BinaryFileRecord
{
public:
  uint8_t strLength;
  char stringBuffer[maxRecordStringLength];
};

int main()
{

  WINDOW	*window;
  CDKSCREEN	*cdkscreen;
  CDKMATRIX     *myMatrix;           // CDK Screen Matrix

  // Remember that matrix starts out at 1,1.
  // Since arrays start out at 0, the first entries
  // below ("R0", and "C0") are just placeholders
  // 
  // Finally... make sure your arrays have enough entries given the
  // values you choose to set for MATRIX_WIDTH and MATRIX_HEIGHT
  // above.

  const char 		*rowTitles[] = {"R0", "R1", "R2", "R3", "R4", "R5"};
  const char 		*columnTitles[] = {"C0", "C1", "C2", "C3", "C4", "C5"};
  int		boxWidths[] = {BOX_WIDTH, BOX_WIDTH, BOX_WIDTH, BOX_WIDTH, BOX_WIDTH, BOX_WIDTH};
  int		boxTypes[] = {vMIXED, vMIXED, vMIXED, vMIXED,  vMIXED,  vMIXED};

  /*
   * Initialize the Cdk screen.
   *
   * Make sure the putty terminal is large enough
   */
  window = initscr();
  cdkscreen = initCDKScreen(window);

  /* Start CDK Colors */
  initCDKColor();

  /*
   * Create the matrix.  Need to manually cast (const char**) to (char **)
  */
  myMatrix = newCDKMatrix(cdkscreen, CENTER, CENTER, MATRIX_HEIGHT, MATRIX_WIDTH, MATRIX_HEIGHT, MATRIX_WIDTH,
			  MATRIX_NAME_STRING, (char **) rowTitles, (char **) columnTitles, boxWidths,
				     boxTypes, 1, 1, ' ', ROW, true, true, false);

  if (myMatrix ==NULL)
    {
      printf("Error creating Matrix\n");
      _exit(1);
    }

  /* Display the Matrix */
  drawCDKMatrix(myMatrix, true);
  
  BinaryFileHeader *myHeader = new BinaryFileHeader();
  //  BinaryFileRecord *myRecord = new BinaryFileRecord();

  ifstream binInfile ("cs3377.bin", ios::in | ios::binary);

  binInfile.read((char *) myHeader, sizeof(BinaryFileHeader));

  stringstream stream;
  stream << "0x" << hex << (int)myHeader->magicNumber;

  string magic = "Magic: " + stream.str();

  setCDKMatrixCell(myMatrix, 1, 1, magic.c_str());

  /*
   * Dipslay a message
   */
  //  setCDKMatrixCell(myMatrix, 1, 1, "Hello World");
  drawCDKMatrix(myMatrix, true);    /* required  */

  /* So we can see results, pause until a key is pressed. */
  unsigned char x;
  cin >> x;

  // Cleanup screen
  endCDK();


  /*
  cout << myHeader->magicNumber << endl;
  cout << myHeader->versionNumber << endl;
  cout << myHeader->numRecords << endl;
  cout << endl;

  for(int x=0;x<(int)myHeader->numRecords;x++)
    {
      binInfile.read((char *) myRecord, sizeof(BinaryFileRecord));  
      cout << "Strlen: " << (int)myRecord->strLength << endl;
      cout << myRecord->stringBuffer << endl;
      cout << endl;
    }
  */

  binInfile.close();

}
