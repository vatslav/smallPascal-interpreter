#ifndef ASSINGNMENT_H_INCLUDED
#define ASSINGNMENT_H_INCLUDED

//Присваивание
	void assignment() {
		if (testing) cout<<"\nAssignment function\n";
prog--;
prog--;
prog--;
prog--;
get_token();

char* tmpName = new char[80];
strcpy(tmpName, token);

//TODO: Поддержка длинных названий переменных
if(Vars.count(tmpName) == 0) AddVar(tmpName,INTEGER,0,true);

prog++;
prog++;
//get_token();
bool result = get_exp_abstract (&Vars[tmpName]);

if (testing) cout<< "Value of " << tmpName << " == " << getValue(tmpName);
//if (testing) printf("\nResult of assignment = %d\n", result );
//if (testing) printf("\n%s \t\t%d - %s \t\t%d - %s", token, token_type,typeToName(token_type), tok, typeToName(tok));
if (testing) getchar();

	}

#endif ASSINGNMENT_H_INCLUDED
