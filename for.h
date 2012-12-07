#ifndef FOR_H_INCLUDED
#define FOR_H_INCLUDED
#include "get_token.h"
#include "Globals.h"
#include "expressions.h"
#include "Vars&Arrays.h"

/*
for identifikator := <vyrazhenie inicializacii> to|downto <vyrazhenie konechnoe > do operator

"identifikatorom"  mozhet byt' tol'ko identifikator prostoj peremennoj: tol'ko tipa INTEGER
 Jelement massiva v kachestve schjotchika cikla nedopustim.
*/

/*
Vypolnit' operator for.
Na moment vyzova tekuwej leksemoj dolzhna byt' for.
Posle okonchanija - tekuwej leksemoj budet poslednjaja leksema operatora.
*/

bool ExecFor()
{
	get_token();
	//pereshli k schjotchiku.
	if( token_type != VARIABLE )
	{
		serror("Expected counter.");
		return false;
	}
	//peremennnaja integer?
	//t.k. tekuweaja leksema jeto sugub imja peremennoj, to nam vpolne hvatit vezde prosto token
	if ( GetTypeVar ( token ) != INTEGER )// proverka-celoe li chislo?
	{
		serror("Only INTEGER variable can be a counter in FOR");
		return false;
	}

	//int* counter =  getIntegerVariable(token);//schetchik mozhet okazat'sja pustym
	int counter = (int)getValue(token);
	if ( counter == 0 )
	{
		serror("ERROR in for. Counter ptr is NULL");
		return false;
	}
	get_token();
	if( tok != ASSIGNMENT )//ne ukazan znak prisvaivanija
	{
		serror("Expected ASSIGNMENT ':='");
		return false;
	}
	bool ok;
	*counter = get_exp_as_integer( &ok );// chto ona delaet?
	if(!ok) return false;

	get_token();
	if ( token_type!= TO && token_type != DOWNTO )//ne nashli TO ili DOWNTO
	{
		serror("Expected TO or DOWNTO");
		return false;
	}
	bool up = ( token_type == TO ) ? true : false;//up = true - schjotchik uvelichivaetsja ( TO ), inache umen'shaetsja ( DOWNTO )

	int finish = get_exp_as_integer( &ok );//finish hranit konechnoe znachenie
	if(!ok) return false;

	if ( up )
	{
		if ( finish < *counter )
		{
			serror("finish value of counter is less, then start for TO-for");
			return false;
		};
	}
	else
	{
		if ( finish > *counter )
		{
			serror("finish value of counter is more, then start for DOWNTO-for");
			return false;
		};
	}

	get_token();
	if ( token_type!= DO )//ne nashli DO
	{
		serror("Expected DO");
		return false;
	}
	char* begin = prog;//sohranjaem poziciju. Otsjuda nachinaetsja iteracija cikla.
	while ( 1 )
	{
		if ( !ExecOperator() ) return false;
		*counter = ( up )? *counter+1 : *counter - 1;

		if ( up && *counter > finish ) return true;
		else if ( !up && *counter < finish ) return true;
		else prog = begin;
	}

	serror("ExecFor::Unreachable code is reached");
	return false;
}


bool PassFor()
{
	get_token();
	//pereshli k schjotchiku.
	if( token_type != VARIABLE )
	{
		serror("Expected counter.");
		return false;
	}

	get_token();
	if( token_type != ASSIGNMENT )
	{
		serror("Expected ASSIGNMENT ':='");
		return false;
	}
	bool ok;
	pass_exp_as_integer( &ok );
	if(!ok) return false;

	get_token();
	if ( token_type!= TO && token_type!= DOWNTO )
	{
		serror("Expected TO or DOWNTO");
		return false;
	}

	pass_exp_as_integer( &ok );
	if(!ok) return false;


	get_token();
	if ( token_type != DO )
	{
		serror("Expected DO");
		return false;
	}
	if(!PassOperator() ) return false;

	return true;
}
#endif // FOR_H_INCLUDED
