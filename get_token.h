#ifndef GET_TOKEN_H_INCLUDED
#define GET_TOKEN_H_INCLUDED

#include "Globals.h"
#include <stdio.h>

/* Chtenie leksemy. */
char get_token()
{
  register char *temp;
  token_type = 0; tok = 0;
  temp = token;

  while(iswhite(*prog)) ++prog; /* Propusk probelov */

  if (*prog == '{') /* KOMMENTARII */
  { // U kommentariev net vnutrennego predstavlenija i tipa. Oni prosto propuskajutsja
    int cnt = 1;
    while (cnt != 0)
    {
      prog++;
      if (*prog == '{')
         cnt++;
      else if (*prog == '}')
         cnt--;
      else if (*prog == '\0')
      {
          printf("Error: Otsutstvuet parnyj simvol k '{'");
          break;
      }
    }
    if ( *prog ) prog++;
  while(iswhite(*prog)) ++prog; /* Propusk probelov */
  }

  if(*prog == '\0') /* KONEC FAJLA */
  {
    *token=0;
    tok = 0;
    return (token_type=FINISHED); //
  }

  if (strchr(".,:;()[]", *prog)) /* RAZDELITEL'' */
  {
    bool assign = false; //Priznak prisvaivanija
    *temp = *prog;

    if (*temp == ':')  //Esli natknulis' na ":",
       assign = true;  //  vozmozhno jeto prisvaivanie

    prog++; // Perehod na sledujuwuju poziciju
    temp++;

    if (*prog == '=' and assign == true)  //Esli vstretili "=" posle ":",
    {                                    //  znachit jeto tochno prisvaivanie
        *temp = *prog;
        prog++;
        temp++;
        *temp = 0;
        tok = ASSIGNMENT;  //Vnutrennee predstavlenie prisvaivanija.
        return ( token_type = OPERATOR ); // Tip "OPERATOR"
    }

    *temp = 0;
    return (token_type = DELIMITER);  // Tip "RAZDELITEL''"
  }

  if (strchr("+-*/=<>", *prog)) /* OPERATOR */
  {
    bool two_symb = false; //Priznak dvuhsimvol'nogo operatora "<=", ">=" ili "<>"
    *temp = *prog;

    if(*prog == '<' or *prog == '>') //Esli natknulis' na "<" ili ">",
       two_symb = true;              //  vozmozhno jeto dvuhsimvol'nyj operator "<=", ">=" ili "<>"

    prog++; // Perehod na sledujuwuju poziciju
  temp++;

    if (two_symb == true)
        if( (*temp == '=') or (*(temp-1) == '<' and *temp == '>' ) )
        {         //Esli vstretili "=" posle "<" ili ">" ("<=",">=") ili
           *temp = *prog;  // ">" posle "<" ("<>"), znachit operator dvuhsimvol'nyj
           prog++;
           temp++;
        }

    *temp = 0;
    return (token_type = OPERATOR);  // Tip "OPERATOR"
  }

  if(isdigit(*prog) == true) /* ChISLO */
  {
    while (isdigit(*prog) == true) //Poka vstrechaem chisla, schityvaem
       *temp++=*prog++;

    if(*prog == '.') //Esli natknulis' na tochku, to jeto libo vewestvennoe chislo "REAL",
    {                //libo diapazon indeksov vnutri massiva
      if (*(prog+1) == '.')//Esli 2 tochki podrjad, znachit
      {                    //jeto diapazon indeksov vnutri massiva "A:array [3..12]"
        *temp = 0;
        return (token_type = INTEGER); //Tip "CELOE ChISLO"
      }

      *temp++ = '.';
      prog++;
      while(isdigit(*prog) == true) //Poka vstrechaem chisla, schityvaem
         *temp++ = *prog++;

      if(*(prog-1) == '.')   // Esli cikl ni razu ne vypolnilsja,
      {                      // znachit nekorrektnoe vyrazhenie tipa "17.a"
        *token = '\0';
        printf("ERROR! Expected REAL number\n");
        return (token_type = ERROR); //Tip "OShIBKA"
      }

      if (isdelim(*prog) == false)  //Esli ne vstretili razdelitelja ili operatora,
      {                              // znachit nekorrektnoe vyrazhenie tipa "17.23a"
        *token = 0;
        printf("ERROR! Expected REAL number\n");
        return (token_type = ERROR);  //Tip "OShIBKA"
      }

      *temp = '\0';
      return(token_type = REAL); //Tip "VEWESTVENNOE ChISLO"
    }
    else if (isdelim(*prog) == false) //Esli ne vstretili razdelitelja ili operatora,
    {                                  // znachit nekorrektnoe vyrazhenie tipa "17a"
      *token = 0;
      printf("ERROR! Expected INTEGER number\n");
      return (token_type = ERROR);  //Tip "OShIBKA"
    }

  *temp = '\0';
  return(token_type = INTEGER); //Tip "CELOE ChISLO"
  }

  if(isalpha(*prog) or *prog == '_') /* Imja "IDENTIFIKATORA", "OPERATORA" ili "SLUZhEBNOE SLOVO"*/
  {
    //Pravila postroenija imen identifikatorov:
    //  1) Imja nachinaetsja s latinskoj bukvy ili simvola '_'.
    //  2) Ostal'nymi simvolami mogut byt' latinskie bukvy, cifry i '_': _A2_B, A2.
    //Imena operatorov i sluzh. slova sostojat tol'ko iz latinskih bukv: IF, For i t.d.

    //Cchityvaem imja poka vstrechaem bukvy, cifry ili '_'
    int ptr=0;
    while(is_good_name (*prog))
    {
      *temp++ = *prog++;
      ptr++;
    }

    //Esli vstretili nepodhodjawij simvol vmesto razdelitelja, vydaem oshibku
    if (!isdelim (*prog)) //
    {
        *token = 0;
        printf("ERROR! Uncorrect IDENTIFIER or OPERATOR name\n");
        return ( token_type = ERROR ); //Tip "OShIBKA"
    }
    if (ptr>8)
    {
        *token = 0;
        printf("ERROR! name of variable > 8\n");
        return ( token_type = ERROR ); //Tip "OShIBKA"
    }
    *temp = 0;

    char type; //Tip leksemy
    tok = look_up(token, &type); // Preobrazovanie vo vnutrennij format.

    if ( type != 0 ) //Esli nashli leksemu sredi "OPERATOROV" ili "SLUZhEBNYH SLOV", vozvrawaem tip leksemy
        return ( token_type = type );
    else //Inache imeem delo s "IDENTIFIKATOROM": peremennoj ili konstantoj
    {
      return ( token_type = VARIABLE );
        ///Nado obdumat'
    }
  }
  ///po idee nado by soobwit' ob oshibki, chto nevernoe imja peremennoj (operatora
  else
    {///jeto nashe--
      *token = 0;
      printf("ERROR! Uncorrect IDENTIFIER or OPERATOR name\n");
      return ( token_type = ERROR ); //Tip "OShIBKA"
    }
}



#endif // GET_TOKEN_H_INCLUDED
