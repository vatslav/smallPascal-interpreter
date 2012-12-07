#ifndef EXPRESSIONS_H_INCLUDED
#define EXPRESSIONS_H_INCLUDED
////Arifmeticheskie vyrazhenija.

/*

Vyrazhenie = Term [ + Ter ][- Term]
Term = Faktor [ * Faktor ][ / Faktor ][ div Faktor ][ mod Faktor ]
Faktor = [+|-]Znachenie
Znachenie = Peremennaja|Chislo|(Vyrazhenie)

*/


bool level2(struct Var*), level3(struct Var*), level4(struct Var*);
bool level5(struct Var*), unary( char, struct Var* ), arith( char, struct Var*, struct Var*);
bool primitive( struct Var * );
//levelI: Pri vyzove tekuwej leksemoj dolzhna byt' pervaja leksema obrabatyvaemoj chasti vyrazhenija.
//Pri uspeshnom zavershenii tekuwej leksemoj budet sledujuwaja leksema posle obrabatyvaemoj chasti vyrazhenija

bool get_exp_abstract( );

/**@function get_exp_abstract
raschityvaet znachenie vyrazhenija.
@param result - ukazatel' na suwestvujuwuju ( pustuju ) strukturu Var, v kotoruju i budet zapisan rezul'tat.*/
bool get_exp_abstract( Var* result )
{

  result->value = 0;
  get_token();//pervyj vyzov, posle := ?

  if( !*token )
  {
    serror("Nevernaja leksema");
    return false;
  }
  bool resultExpes = level2( result );
  if(!resultExpes) return false;
  putback(); /* Vozvrawaet poslednjuju schitannuju leksemu obratno vo vhodnoj potok */ //zachem?
  return true;
}

/**@function get_exp_as_integer
obrabotchik vyrazhenij  v kotoryh oba uchatnika tipa integer */
int get_exp_as_integer( bool *ok )
{
	struct Var result;//voobwe-to nado obnulit' ukazatel', no za nas jeto sdelaet get_exp_abstract
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
obrabotchik vyrazhenij  v kotoryh oba uchatnika tipa real */

float get_exp_as_real( bool *ok )
{
	struct Var result;//voobwe-to nado obnulit' ukazatel', no za nas jeto sdelaet get_exp_abstract
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
Funkcii propuska vyrazhenija*/
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
 Slozhenie ili vychitanie dvuh termov */
bool level2( struct Var* result )
{
  register char op;
  struct Var hold;

  bool ok = level3( result );
  if(!ok) return false;

  while( ( op = *token) == '+' || op == '-' )
  {
    get_token();
    ok = level3( &hold );///t.k. tut ne *, to nuzhen li &
	if(!ok) return false;

    //printf("result=%d, hold=%d\n", *(int*)(result->var), (hold.type) );
    //fflush(stdout);

    ok = arith( op, result, &hold );
   	if(!ok) return false;
  }

  return true;
}


/* Vychislenie proizvedenija ili chastnogo dvuh faktorov. Ewjo celochislennogo delenija i ostatka ot delenija. */
bool level3( struct Var result )
{
  register char op;
  struct variable hold;hold.var = 0;

  bool ok = level4( result );
  if( !ok ) return false;

  while( ( op = *token) == '*' || op == '/' || ( token_type == OPERATION && (op == 'd' || op == 'm')) )//d, m - div, mod
  {
    get_token();
    ok = level4( &hold );
    if ( !ok ) return false;

    ok = arith( op, result, &hold );
    if( !ok ) return false;

  }

  return true;
}



/* Unarnyj + ili - */
bool level4( struct Vars result )
{
	register char op;

	op = 0;
	if ( ( token_type == OPERATION ) && ( *token == '+' || *token == '-' ) )
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

/* Obrabotku vyrazhenija v kruglyh skobkah ili poluchenie chisla. */
bool level5( struct Vars result )
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

/* Opredelenie znachenija peremennoj po ejo imeni */
bool primitive( struct Vars result )
{
	//printf("primitive: token=%s; type=%d\n", token, token_type );//111111111
	switch( token_type )
	{
		case VARIABLE:
		//getNumberFromVariable iz podsistemy variables po imeni peremennoj vozvrawaet
		//strukturu Var, soderzhawuju tip i znachenie peremennoj, dlja massivo avtomaticheski
		//schityvaet kvadratnye skobki i esli jeto jelement massiva ( indeksov stol'ko, skol'ko nado ), vozvrawaet ego opisanie, inache
		//vozvrawaet pustuju strukturu Var.
			*result = getNumberFromVar( token );
			if ( result->type == 0 ) return false;//esli ne udalos' poluchit' znachenie.
			//Zdes' vazhno ponimat', chto PEREMENNAJa s takim imenem tochno suwestvuet ( inache rugalas' by get_token, no ona
			//skazala, chto jeto Var ). Posemu edinstvennaja vozmozhnost' neshtatnoj situacii - nepravil'noe kolichestvo
			//indeksov ili nekorrketnye znachenija indeksov dlja peremennoj-massiva.
			get_token();
			return true;
			break;
		case CONSTANT:
			*result = getNumberFromConstant( token );
			//Raz get_token skazala, chto jeto CONSTANT, znachit takaja konstanta tochno est'. A jeto znachit, chto oshibki tochno ne budet.
			//Vot my nichego i ne proverjaem.
			//!!!Poluchennaja struktura ni koim obrazom ne svjazana s toj, chto hranitsja v podsisteme Vars.
			//!!!Ukazatel' var ukazyvaet na oblast' pamjati, gde lezhit KOPIJa znachenija iz podsistemy Vars.
			//Pochemu tak? Da potomu, chto esli by result.var ukazyval na oblast' pamjati, gde hranitsja imenno znachenie
			//peremennoj ( a ne kopija znachenija ), funkcija arith jeto znachenie by perepisala. I takuju oshibku otlovit' ochen'
			//trudno...
			get_token();
			return true;
			break;
		case INT_NUMBER:
			result -> type = INTEGER;
			int* d = (int*)malloc( sizeof( int ) );
			*d = atoi( token );
			result -> var = d;

			get_token();

			return true;
			break;
		case REAL_NUMBER:
			result -> type = REAL;
			float* dd = (float*)malloc( sizeof( float ) );
			*dd = atof( token );
			result -> var = dd;

			get_token();

			return true;
			break;
		case FUNCTION:
			{
				//printf("primitive::FUNCTION\n");
				//fflush(stdout);
				bool ok = ExecBuiltInMath( result );

				if(!ok) return false;
				else return true;
			}
			break;
		default:
			serror( "Expected identifier or Var"  ) ;
			return false;
	}
}

////// sluzhebnye funkcii /////////
//vypolnenie operacij dlja INTEGER
bool int_arith( char o, int* r, int* h )
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
		//case '/': // jeto obrabatyvaetsja v vyzyvajuwej procedure.
		case 'd':

			if ( *h == 0 )
			{
				serror("Division by 0");
				return false;
			}
			*r = (*r)/(*h);
			break;
		case 'm':

			*r = (*r) % (*h);
			break;
        default:
            serror("int_arith::unreachable section is reached");
            return false;
            break;
	}
	return true;
}

//vypolnenie operacij dlja REAL
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
		case 'm':
			serror("Expected integer Vars for 'mod'");
			return false;
			break;
		case 'd':
      serror("Expected intger Vars for 'div'");
      return false;
      break;
        default:
            serror("float_arith::reached unreachable code.");
            return false;
            break;
	}

	return true;
}

//privedenie tipa INTEGER k tipu REAL



/* Vypolnenie specificirovannoj arifmetiki.
Rezul'tat zapisyvaetsja v r */
bool arith( char op, struct Var* r, struct Var* h )
{


	if ( r -> type != h-> type )//esli nuzhno privedenie tipov.
	{
		struct variable* lowest;
		if( r->type == INTEGER ) lowest = r;
		else if ( h->type == INTEGER ) lowest = h;
		else
		{
			serror("arith::Expected struct variable with type = INTEGER or REAL" );
			return false;
		}

		lowest -> type = REAL;
		int d = *(int*)(lowest->var);
		free( lowest->var );
		lowest -> var = malloc( sizeof( float ) );
		*(float*)(lowest->var) = (float)d;

	}


	if ( r-> type == INTEGER )
	{
	    if ( op == '/' )
	    //Pri delenii integer-ov v Paskale ne proishodit otbrasyvanija drobnoj chasti,
	    //a prosihodit perehod k tipu dannyh real.
	    {
	        r->type = REAL;
	        float result = ((float)(*(int*)(r->var))) / ( * (int*)(h->var));
	        free( r-> var );
	        r->var = malloc ( sizeof( float ) );
	        *((float*)(r->var)) = result;
	        return true;
	    }
	    else return int_arith( op, (int*)(r->var), (int*)(h->var) );
	}

	else if ( r -> type == REAL )
		return float_arith( op, (float*)(r->var), (float*)(h->var) );
	else
	{
		serror("arith::Expected struct variable with type = INTEGER or REAL (2)");
		return false;
	}


}

/* Izmenenie znaka */
bool unary( char o, struct variable* r )
{
	if ( o == '-' )
	{
		if ( r-> type  == INTEGER )
			*(int*)(r->var) = -*(int*)(r->var);
		else if ( r->type == REAL )
			*(float*)(r->var) = -*(float*)(r->var);
		else
		{
			serror("unary: Expected struct variable with type = INTEGER or REAL");
			return false;
		}
	}
	return true;
}








#endif // EXPRESSIONS_H_INCLUDED
