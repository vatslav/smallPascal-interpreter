#include <iostream>
#include <locale.h>
#include <fstream>

#include "get_token.h"
#include "Vars&Arrays.h"
//#include "expressions.h"

using namespace std;

char* loadFile(int argc, char* argv[]);

int main(int argc, char* argv[]) {
	prog = loadFile(argc, argv);

	//setlocale (LC_ALL,"RUS");

    printf("%s\n\nToken\t\tToken_type\tTok\n\n", prog);

    while(1)
    {
      int result = get_token();
      ///eslki oshibki ili konec programmy.
        if (result==9 || result==18) break;
        printf("%s \t\t%d - %s \t\t%d - %s", token, token_type,typeToName(token_type), tok,typeToName(tok) );
        getchar();
    }

    AddVar ("_s",INTEGER,0,true);
    AddVar ("s",INTEGER,5,true);


   AddVar ("se3",REAL,112.75,false);
    AddVar ("awf3",REAL,0.53,false);


    prog = "array [_s..s,0..10] of integer";
    AddArray ("a");

    try{
      // pres((int)getValue("a",2,2),"getValue");
    }
    catch (const char * exc)
    {
        cout<<exc;
    }

    catch(...)
    {
        cout<<"all cath"<<endl;
    }
    printArrays();
//fuction ();
//    getchar();
//getchar();
    return 0;
}

char* loadFile(int argc, char* argv[]) {
	//Delaem zagruzku programmi cherez argumenti, ili po umolchanijy input.txt v korne
	char inputFilePath[100];
	if (argc > 1) {
		strcpy(inputFilePath, argv[1]);
	} else {
		//strcpy(inputFilePath, argv[0]);
		strcat(inputFilePath, "input.txt");
	} //TODO: rabota s argumentami

	ifstream iStream(inputFilePath);
	string str;
	string programText = "";
	while(getline(iStream, str)) {
		programText += str + "\n";
	}
	//const char* progText = programText.c_str();
	//
	char* progText = new char[programText.size() + 1];
	copy(programText.begin(), programText.end(), progText);
	progText[programText.size()] = '\0'; // don't forget the terminating 0
	return progText;
}
