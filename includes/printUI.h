// * function for printing text on CLI
/* template






*/
// header files and namespace
#include <iostream>
#include <string>
#include <cmath>
using namespace std;


// prototype functions
void printBorder(int n);
int checkDecimals(double spacing, int decimals);
double calculateSpace(double lineSpace, double len);


// global variables
string bankNm[2] = {"FBC", "Filipinas Banking Corporation"};


// main
void printUI(string text) {
  // get user name
  string nm;
  cout << "Name: ";
  getline(cin, nm); // get input with spaces

  // ! TO REVISE ONCE MAIN HAS MORE PROGRESS
  // initialize line text and place into an array
  string l3 = "Author: " + nm;
  string l4 = "Due Date: Thursday, Jan. 24";
  string lines[4] = {bankNm[0], bankNm[1], l3, l4};

  // get the character lenght of each line
  double len[4] = {bankNm[0].length(), bankNm[1].length(), l3.length(), l4.length()};

  // determine the line with the most characters
  int index = 0;
  for (int i = 0; i < 4; i++) {
    if (len[i] > len[index]) {
      index = i;
    }
  }

  /*
  calculate:
    (1) maximum characters per line
    (2) requied space for each line
    (3) total lines to be printed
  */
  double lineSpace = len[index] + 7.00; // add a few blank spaces (7.00) to the longest line
  double spacing = calculateSpace(lineSpace, double(len[0]));
  int totalLines = sizeof(lines)/sizeof(lines[0]); 

  // print upper border 
  printBorder(lineSpace);

  // print texts and border
  for (int i = 0, j = 0, k = 0; i < spacing; i++) {
    /*
    indexes:
      i -> printing "—" and " "
      j -> printing line text
      k -> determining end of spacing (before and after line text)
    */

    // check if calculated space has decimals
    int decimals = checkDecimals(spacing, 0);

    // end loop if it has printed all lines
    if (j == totalLines) {
      break;
    }

    /*
    printing:
      print * at the start of the line space, then
      print spaces
    */
    if (i == 0) {
      cout << "—";
    } else {
      cout << " ";
    }

    /*
    if spacing has decimals:
    (1) print an extra space before the line text
    (2) round down spacing to nearest integer
    (3) set spacing is now a whole number
    */
    if (decimals == 1) {
      decimals = 0;
      cout << " ";
      spacing = int(spacing);
    }

    /*
    if line text been printed and spaces after the text has been printed"
      (1) print "—" to complete border
      (2) reset i (i = -1 since i will iterate once after this), and k
      (3) increment j (go to next line text)
      (4) calculate required spacing for new line text
    */
    if (k == 1 && i == spacing-1) {
      cout << "—" << endl << endl;
      i = -1, k = 0, j++;
      spacing = calculateSpace(lineSpace, len[j]);

      // add border after 2nd line
      if (j == 2) {
        printBorder(lineSpace);
      }
    }

    /*
    if i has printed all spaces:
      (1) print line text
      (2) redo spaces (i = 0)
      (3) tell program line text has been printed (k = 1)
    */
    if (i == spacing-1) {
      cout << lines[j];
      i = 0, k = 1;
    }
  }

  // print bottom border
  printBorder(lineSpace);
} 


// print the border with "—" up to the lenght of the longest line
void printBorder(int n) {
  for (int i = 0; i < n; i++) {
    cout << "—";
  } cout << endl << endl;
}


// determine if the calculated spacing for each line has decimals
int checkDecimals(double spacing, int decimals) {
  if (ceil(spacing) != floor(spacing)) {
      decimals = 1; // line has decimals
  } return decimals;
}


// calculate the characters spaces each line must have with reference to the longest line
double calculateSpace(double lineSpace, double len) {
  return (lineSpace - len)/2;
}