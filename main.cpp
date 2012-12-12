#include <iostream>
#include <locale.h>
#include "get_token.h"
#include "Vars&Arrays.h"
#include "expressions.h"

using namespace std;

int main()
{
    setlocale (LC_ALL,"RUS");
    //asdasd
   /* prog = "Program Test\n"
    "c:=3 "
    "const a=5+2+g, b=3;\n"
    "var\n"
    "i,j:integer;\n"
    "y:array [1..a,1..b] of integer;\n"
    "Begin\n"
    "    write (a);\n"
    "    read (k);\n"
    "{ Комментарий     \n"
    "    Продолжение  }\n"
    "    if a>=b then i:=a+1 else j:=b+1\n"
    "    for i:=1 to a do i:=i*j;\n"
    "    while (i>0) i:= i - 2\n"
    "End.";
    //" (1243+236)bsg+43.36";
    printf("%s\n\nToken\t\tToken_type\tTok\n\n",prog);
    while(1)
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
	}*/
	AddVar ("x",INTEGER,10,true);
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
bool ok, result;
//strcpy( prog, "2+2.98" );
//prog = "z*(2+3)";
prog = "2 > 3";
//get_token ();
//get_exp_abstract
//result = get_exp_abstract( &Vars["z"]);
result = get_logic_exp (&ok);
printf("ok = %d, result = %d\n", ok, result );
	printf("prog -> %s\n", prog );
     //cout<<"var z="<<Vars["z"].value;

    return 0;
}
