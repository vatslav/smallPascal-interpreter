#ifndef EXPRESSIONS_H_INCLUDED
#define EXPRESSIONS_H_INCLUDED
////�������������� ���������.

/*

��������� = ���� [ + ��� ][- ����]
���� = ������ [ * ������ ][ / ������ ][ div ������ ][ mod ������ ]
������ = [+|-]��������
�������� = ����������|�����|(���������)

*/


bool level2(struct Var*), level3(struct Var*), level4(struct Var*);
bool level5(struct Var*), unary( char, struct Var* ), arith( char, struct Var*, struct Var*);
bool primitive( struct Var * );
//levelI: ��� ������ ������� �������� ������ ���� ������ ������� �������������� ����� ���������.
//��� �������� ���������� ������� �������� ����� ��������� ������� ����� �������������� ����� ���������

bool get_exp_abstract( Var* result);

/**@function get_exp_abstract
����������� �������� ���������.
@param result - ��������� �� ������������ ( ������ ) ��������� Var, � ������� � ����� ������� ���������.*/
bool get_exp_abstract( Var* result )
{

  //result->value = 0;
  get_token();//������ �����, ����� := ?

  if( !*token )
  {
    serror("�������� �������");
    return false;
  }
  bool resultExpes = level2( result );
  if(!resultExpes) return false;
  putback(); /* ���������� ��������� ��������� ������� ������� �� ������� ����� */ //�����?
  return true;
}

/**@function get_exp_as_integer
���������� ���������  � ������� ��� ��������� ���� integer */
int get_exp_as_integer( bool *ok )
{
	struct Var result;//������-�� ���� �������� ���������, �� �� ��� ��� ������� get_exp_abstract
	bool good = get_exp_abstract( &result );
	if(!good)
	{
		*ok = false;
		return 0;
	}

	*ok = true;

	if ( result.type == INTEGER )
		return (result.value);
	else if (result.type == REAL )
	{
		serror("Expected INTEGER result, got REAL");
		*ok = false;
		return 0;
	}
	else
	{
		serror("get_exp_as_integer::Expression result is neither INTEGER nor REAL");
		*ok = false;
		return 0;
	}

}



/**@function get_exp_as_real
���������� ���������  � ������� ��� ��������� ���� real */

float get_exp_as_real( bool *ok )
{
	struct Var result;//������-�� ���� �������� ���������, �� �� ��� ��� ������� get_exp_abstract
	bool good = get_exp_abstract( &result ); //
	if(!good)
	{
		*ok = false;
		return 0;
	}

	*ok = true;

	if ( result.type == INTEGER )
		return (float)(result.value);
	else if (result.type == REAL )
		return (float)(result.value);
	else
	{
		serror("get_exp_as_real::Expected INTEGER or REAL in struct Var");
		*ok = false;
		return 0;
	}
}


/**@function pass_exp_as_real
������� �������� ���������*/
void pass_exp_as_real( bool *ok )
{
	*ok = true;
	get_token();
	if ( strchr( ",.:;", token[0] ) ||
		token_type == OPERATOR || token_type == STRING || token_type == FINISHED ||
			token_type == ERROR || ( token_type == RESERVED && tok!=TRUE && tok != FALSE ) )
	{
		serror("Bad expression");
		*ok = false;
		return;
	}

	do
	{
		get_token();
	}
	while( !( strchr( ",.:;", token[0] ) ||
		token_type == OPERATOR || token_type == STRING || token_type == FINISHED ||
			token_type == ERROR || ( token_type == RESERVED && tok!=TRUE && tok != FALSE ) ) );
	putback();
}
void pass_exp_as_integer(bool*ok)
{
	pass_exp_as_real( ok );
}

void pass_logic_exp( bool*ok )
{
	pass_exp_as_real( ok );
}




/**@function level2
 �������� ��� ��������� ���� ������ */
bool level2( struct Var* result )
{
  register char op;
  struct Var hold;

  bool ok = level3( result );
  if(!ok) return false;

  while( ( op = *token) == '+' || op == '-' )
  {
    get_token();
    ok = level3( &hold );///�.�. ��� �� *, �� ����� �� &
	if(!ok) return false;

    //printf("result=%d, hold=%d\n", *(int*)(result->var), (hold.type) );
    //fflush(stdout);

    ok = arith( op, result, &hold );
   	if(!ok) return false;
  }

  return true;
}


/* ���������� ������������ ��� �������� ���� ��������. ��� �������������� ������� � ������� �� �������. */
bool level3( struct Var* result )
{
  register char op;
  struct Var hold;
  hold.value = 0;

  bool ok = level4( result );
  if( !ok ) return false;

  while( ( op = *token) == '*' || op == '/' || ( token_type == OPERATOR && (op == 'd' || op == 'm')) )//d, m - div, mod
  {
    get_token();
    ok = level4( &hold );
    if ( !ok ) return false;

    ok = arith( op, result, &hold );
    if( !ok ) return false;

  }

  return true;
}



/* ������� + ��� - */
bool level4( struct Var* result )
{
	register char op;

	op = 0;
	if ( ( token_type == OPERATOR ) && ( *token == '+' || *token == '-' ) )
	{
		op = *token;
		get_token();
	}
	bool ok = level5( result );
	if( !ok ) return false;

	if( op )
		ok = unary( op, result );
	if ( !ok ) return false;

	return true;
}

/* ��������� ��������� � ������� ������� ��� ��������� �����. */
bool level5( struct Var* result )
{
	bool ok;
	if( ( *token == '(' ) && ( token_type == DELIMITER ) )
	{
		get_token();
		ok = level2( result );
		if ( !ok ) return false;

		if ( *token != ')' )
		{
			serror("Expected ')'");
			return false;
		}
		get_token();
	}
	else
	{
		ok = primitive( result );
		if(!ok) return false;
	}

	return true;
}

/* ����������� �������� ���������� �� � ����� */
bool primitive( struct Var* result )
{
	//printf("primitive: token=%s; type=%d\n", token, token_type );//111111111
	switch( token_type )
	{
		case VARIABLE:
		//getNumberFromVariable �� ���������� variables �� ����� ���������� ����������
		//��������� Var, ���������� ��� � �������� ����������, ��� ������� �������������
		//��������� ���������� ������ � ���� ��� ������� ������� ( �������� �������, ������� ���� ), ���������� ��� ��������, �����
		//���������� ������ ��������� Var.
			result->value = getValue( token );
			//if ( result->type == 0 ) return false;//���� �� ������� �������� ��������.
			//����� ����� ��������, ��� ���������� � ����� ������ ����� ���������� ( ����� �������� �� get_token, �� ���
			//�������, ��� ��� Var ). ������ ������������ ����������� ��������� �������� - ������������ ����������
			//�������� ��� ������������ �������� �������� ��� ����������-�������.
			get_token();
			return true;
			break;
		case CONSTANT:
			result->value = getValue( token );
			//��� get_token �������, ��� ��� CONSTANT, ������ ����� ��������� ����� ����. � ��� ������, ��� ������ ����� �� �����.
			//��� �� ������ � �� ���������.
			//!!!���������� ��������� �� ���� ������� �� ������� � ���, ��� �������� � ���������� Vars.
			//!!!��������� var ��������� �� ������� ������, ��� ����� ����� �������� �� ���������� Vars.
			//������ ���? �� ������, ��� ���� �� result.var �������� �� ������� ������, ��� �������� ������ ��������
			//���������� ( � �� ����� �������� ), ������� arith ��� �������� �� ����������. � ����� ������ �������� �����
			//������...
			get_token();
			return true;
			break;
		case INTEGER:
			result -> type = INTEGER;
			result -> value = atof( token );

			get_token();

			return true;
			break;
		case REAL:
			result -> type = REAL;
			result -> value = atof( token );

			get_token();

			return true;
			break;
		default:
			serror( "Expected identifier or Var"  ) ;
			return false;
	}
}

////// ��������� ������� /////////
//���������� �������� ��� INTEGER
bool int_arith( char o, float* r, float* h )
{


	switch( o )
	{
		case '-':
			*r = *r - *h;
			break;
		case '+':
			*r = *r + *h;
			break;
		case '*':
			*r = *r * *h;
			break;
		//case '/': // ��� �������������� � ���������� ���������.
        default:
            serror("int_arith::unreachable section is reached");
            return false;
            break;
	}
	return true;
}

//���������� �������� ��� REAL
bool float_arith( char o, float* r, float* h )
{


	switch( o )
	{
		case '-':
			*r = *r - *h;
			break;
		case '+':
			*r = *r + *h;
			break;
		case '*':
			*r = *r * *h;
			break;
		case '/':
			if ( *h == 0 )
			{
				serror("Division by 0");
				return false;
			}
			*r = (*r)/(*h);
			break;
        default:
            serror("float_arith::reached unreachable code.");
            return false;
            break;
	}

	return true;
}

//���������� ���� INTEGER � ���� REAL



/* ���������� ����������������� ����������.
��������� ������������ � r */
bool arith( char op, struct Var* r, struct Var* h )
{

/*
	if ( r -> type != h-> type )//���� ����� ���������� �����.
	{
		struct Var* lowest;
		if( r->type == INTEGER ) lowest = r;
		else if ( h->type == INTEGER ) lowest = h;
		else
		{
			serror("arith::Expected struct variable with type = INTEGER or REAL" );
			return false;
		}

		lowest -> type = REAL;
		int d = (int)(lowest->value);
		//free( lowest->value );
		//lowest -> var = malloc( sizeof( float ) );
		(float)(lowest->value) = (float)d;

	}*/


	if ( r-> type == INTEGER )
	{
	    /*if ( op == '/' )
	    //��� ������� integer-�� � ������� �� ���������� ������������ ������� �����,
	    //� ���������� ������� � ���� ������ real.
	    {
	        r->type = REAL;
	        float result = ((r->value) / (h->value));
	        //free( r-> var );
	        //r->var = malloc ( sizeof( float ) );
	        //*((float*)(r->var)) = result;
	        return true;
	    }
	    else */
	    return int_arith( op, &(r->value), &(h->value) );
	}

	else if ( r -> type == REAL )
		return float_arith( op, &(r->value), &(h->value) );
	else
	{
		serror("arith::Expected struct variable with type = INTEGER or REAL (2)");
		return false;
	}


}

/* ��������� ����� */
bool unary( char o, struct Var* r )
{
	if ( o == '-' )
	{

			r->value = -(r->value);
//		else if ( r->type == REAL )
//			*(float*)(r->var) = -*(float*)(r->var);
//		else
//		{
//			serror("unary: Expected struct variable with type = INTEGER or REAL");
//			return false;
//		}
	}
	return true;
}








#endif // EXPRESSIONS_H_INCLUDED
