#include <fstream>
#include <iostream>
#include <string>
#include <regex>

#include <stdio.h>

using namespace std;


// textfile.cpp
//
// simple reading and writing for text files
//
// www.lighthouse3d.com
//
// You may use these functions freely.
// they are provided as is, and no warranties, either implicit,
// or explicit are given
//////////////////////////////////////////////////////////////////////

char *textFileRead(char *fn) {
    FILE *fp;
    char *content = NULL;
    
    int count=0;
    
    if (fn != NULL) {
        fp = fopen(fn,"rt");
        
        if (fp != NULL) {
            
            fseek(fp, 0, SEEK_END);
            count = ftell(fp);
            rewind(fp);
            
            if (count > 0) {
                content = (char *)malloc(sizeof(char) * (count+1));
                count = fread(content,sizeof(char),count,fp);
                content[count] = '\0';
            }
            fclose(fp);
        }
    }
    return content;
}




int main ()
{

    
    ifstream infile;

    infile.open("simple.pov", ifstream::in);

    

    string s ("this subject has a submarine as a subsequence");
    smatch m;
    regex e ("\\b(sub)([^ ]*)");   // matches words beginning by "sub"

    cout << "Target sequence: " << s << endl;
    cout << "Regular expression: /\\b(sub)([^ ]*)/" << endl;
    cout << "The following matches and submatches were found:" << endl;

    while (regex_search (s,m,e)) {
        for (auto x:m) cout << x << " ";
        cout << endl;
        s = m.suffix().str();
    }

    return 0;
}
