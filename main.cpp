#include <iostream>
#include <locale.h>
#include "get_token.h"
#include "Vars&Arrays.h"
#include "expressions.h"
#include <fstream>
#include "assignment.h"

using namespace std;

char* loadFile(int argc, char* argv[]);

int main(int argc, char* argv[])
{
    setlocale (LC_ALL,"RUS");
	prog = loadFile(argc, argv);
	int tokInt = 0;

	do {
		tokInt = get_token();
		switch(tok) {
			case ASSIGNMENT:
				testing = true;
				assignment();
				break;
			case FOR:
				//For function
				break;
			//И так далее..
		}
	} while(tokInt != ERROR && tokInt != FINISHED);





  //  printf("%s\n\nToken\t\tToken_type\tTok\n\n",prog);
  /*  while(1)
	{
	  int result = get_token();
	  ///еслkи ошибки или конец программы.
		if (result==9 || result==18)
		{
		  //int a;
		  break;

		}
		printf("%s \t\t%d - %s \t\t%d - %s", token, token_type,typeToName(token_type), tok,typeToName(tok) );
		getchar();
	}
/*	AddVar ("x",INTEGER,10,true);
	AddVar ("s",INTEGER,20.5,true);


   AddVar ("y",REAL,20.1,false);
	AddVar ("z",REAL,1.5,false);

/*
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
//getchar();*/
//bool ok, result;
//strcpy( prog, "2+2.98" );
//prog = "z*(2+3)";
//prog = "2 > 3";
//get_token ();
//get_exp_abstract
//result = get_exp_abstract( &Vars["z"]);
//result = get_logic_exp (&ok);
//////printf("ok = %d, result = %d\n", ok, result );
//	printf("prog -> %s\n", prog );
     //cout<<"var z="<<Vars["z"].value;

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
