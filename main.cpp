#include <iostream>
#include <sstream>

using std::cout;
using std::endl;
using std::ostringstream;

void compress(char* string){
    // Get length of original string.
    int length = 0;
    char* start = string;
    while(*start != '\0'){
        length++;
        start++;
    }
    
    char* newString = new char[length];
    int newLength = 0;
    for(int i = 0; i < length; i++){
        // Character to check repeats.
        char current = *(string + i);
        
        // Find number of occurences.
        int occurences = 1;
        char* repeatFinder = (string + i + 1);
        while(*repeatFinder == current){
            occurences++;
            repeatFinder++;
        }
        
        // Move ahead if there were extra occurences.
        i += occurences - 1;
        
        // Return if compressed string longer than original string.
        int lengthExtension = 2;
        int divided = occurences;
        while((divided / 10) > 0){
            lengthExtension++;
            divided /= 10;
        }
        if(newLength + lengthExtension >= length)
            return;
        
        // Add to new string.
        newString[newLength] = current;
        ostringstream converter;
        converter << occurences;
        memcpy(newString + newLength + 1, converter.str().c_str(), (occurences % 10));
        
        newLength += lengthExtension;
    }
    
    // Reset old string
    for(int i = 0; i < length; i++){
        string[i] = '\0';
    }
    memcpy(string, newString, newLength);
    delete newString;
}

int main(int argc, char* argv[]){
    char testString [18] = {0};
    memcpy(testString, "aaabbbcgoodjooooo", 17);
    compress(testString);
    cout << testString << endl;
}