#ifndef FOR_H_INCLUDED
#define FOR_H_INCLUDED
#include "get_token.h"
#include "Globals.h"
#include "expressions.h"
#include "Vars&Arrays.h"

/*
for идентификатор := <выражение инициализации> to|downto <выражение конечное > do оператор

"идентификатором"  может быть только идентификатор простой переменной: только типа INTEGER
 Элемент массива в качестве счётчика цикла недопустим.
*/

/*
Выполнить оператор for.
На момент вызова текущей лексемой должна быть for.
После окончания - текущей лексемой будет последняя лексема оператора.
*/

bool ExecFor()
{
	get_token();
	//перешли к счётчику.
	if( token_type != VARIABLE )
	{
		serror("Expected counter.");
		return false;
	}
	//переменнная integer?
	//т.к. текущеая лексема это сугуб имя переменной, то нам вполне хватит везде просто token
	if ( GetTypeVar ( token ) != INTEGER )// проверка-целое ли число?
	{
		serror("Only INTEGER variable can be a counter in FOR");
		return false;
	}

	//int* counter =  getIntegerVariable(token);//счетчик может оказаться пустым
	int counter = (int)getValue(token);
	if ( counter == 0 )
	{
		serror("ERROR in for. Counter ptr is NULL");
		return false;
	}
	get_token();
	if( tok != ASSIGNMENT )//не указан знак присваивания
	{
		serror("Expected ASSIGNMENT ':='");
		return false;
	}
	bool ok;
	*counter = get_exp_as_integer( &ok );// что она делает?
	if(!ok) return false;

	get_token();
	if ( token_type!= TO && token_type != DOWNTO )//не нашли TO или DOWNTO
	{
		serror("Expected TO or DOWNTO");
		return false;
	}
	bool up = ( token_type == TO ) ? true : false;//up = true - счётчик увеличивается ( TO ), иначе уменьшается ( DOWNTO )

	int finish = get_exp_as_integer( &ok );//finish хранит конечное значение
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
	if ( token_type!= DO )//не нашли DO
	{
		serror("Expected DO");
		return false;
	}
	char* begin = prog;//сохраняем позицию. Отсюда начинается итерация цикла.
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
	//перешли к счётчику.
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
