#ifndef VARS&ARRAYS_H_INCLUDED
#define VARS&ARRAYS_H_INCLUDED

#include "Globals.h"
#include "get_token.h"
#include <map>
#include <string>
#include <stdlib.h>

using std::string;
using std::map;
using std::cout;
using std::cin;
using std::endl;


/**@struct array
 Struktura dlja peremennyh tipa INTEGER/REAL
int type - Tip identifikatora
float value - Znachenie identifikatora
bool isConst - Konstanta/peremennaja
*/
struct Var
{
    int type;
    float value;
    bool isConst;
};

/**@struct array
Struktura dlja massivov tipa INTEGER/REAL
int type - Tip massiva
bool isBig - Mnogomernyj/odnomernyj massiv
int from - nizhnjaja granica massiva
int to - verhnjaja granica massiva
float *el - jelementy massiva
*/
struct Array
{
    int type;
    bool isBig;
    int from;
    int to;
    int from2;
    int to2;
    float *el; //ukazatel' na 1 jelement massiva
    float **el2;
};

//Dlja hranenija peremennyh/konstant i massivov ispol'zuem
//associativnye massivy (karty/kontejnery)
///Karta dlja identifikatorov tipa INTEGER/REAL
map <string, Var> Vars;
///Karta dlja massivov tipa INTEGER/REAL
map <string, Array> Arrays;

///Iteratory dlja raboty s kartami v cikle
map <string, Var>::iterator start = Vars.begin ();
map <string, Array>::iterator start2 = Arrays.begin ();

//Vremennye ob#ekty nashih struktur udalil t.k. ispol'zuem lokal'nye
//Var temp;
//Array temp2;

/**@fuction AddVar
Funkcija dobavlenija peremennoj/konstanty v kartu

name - Imja peremennoj/konstanty
type - Tip peremennoj/konstanty
value - Znachenie peremenoj/konstanty
constant - Harakteristika (true - konstanta, false - peremennaja)
*/
bool AddVar (char* name, int type, float value, bool constant)
{
   Var temp;
   if (Vars.count(name) == 0) //Esli v karte net peremennoj s takim imenem
   {
       temp.isConst = constant;
       temp.type = type;
       temp.value = value; //Privodim k tipu INTEGER
       Vars[name] = temp;   //Kidaem v kartu novuju peemennuju/konstantu
       return 1;
   }
   else //Inache soobwaem, chto v karte est' peremennaja/konstanta s takim imenem
       {
           printf ("The variable/constant with this name is already exists");
           return 0;
       }
}

/**@fuction GetTypeVar
Funkcija poluchenija tipa peremennoj/konstanty

name - Imja peremennoj/konstanty
return - Tip peremennoj/konstanty
*/
int GetTypeVar (const char* name)
{
    if (Vars.count(name) != 0) //Nahodim peremennuju/konstantu v karte
    {
        //start->second = Vars[name]; //Stavim iterator na nashu nahodku
        //return start->second.type;  //Vozvrawaem tip
        return Vars[name].type;
    }
    else //Inache opovewaem o tom, chto ne nashli nichego s takim imenem
    {
        printf ("The variable/constant with this name isn't exists");
        return 0;
    }
}

/**@fuction getValue
Funkcija poluchenija znachenija peremennoj/konstanty

name - Imja peremennoj/konstanty
return - Znachenie peremennoj/konstanty
*/
float getValue (const char* name)
{
    if (Vars.count(name) != 0) //Nahodim peremennuju/konstantu v karte
    {
        //start->second = Vars[name]; //Stavim iterator na nashu nahodku
        //return start->second.value;  //Vozvrawaem znachenie
        return Vars[name].value;
    }
    else //Inache opovewaem o tom, chto ne nashli nichego s takim imenem
    {
        printf ("The variable/constant with this name isn't exists");
        return -1.0;
    }
}
 ///Poluchit' znachenie odnomernogo massiva
float getValue (const char* name, int index)
{

    if (Arrays.count(name) != 0) //Nahodim peremennuju/konstantu v karte
    {
        //start->second = Vars[name]; //Stavim iterator na nashu nahodku
        //return start->second.value;  //Vozvrawaem znachenie
        if (index > Arrays[name].to or index<Arrays[name].from)
          throw "Indeks massiva, vyhodit za ego predely";
        return Arrays[name].el[index-Arrays[name].from];
    }
    else //Inache opovewaem o tom, chto ne nashli nichego s takim imenem
    {
        printf ("The variable/constant with this name isn't exists");
        return -1.0;
    }
}

 ///Poluchit' znachenie dvumernogo massiva
float getValue (const char* name, int index, int index2)
{

    if (Arrays.count(name) != 0) //Nahodim peremennuju/konstantu v karte
    {
        //start->second = Vars[name]; //Stavim iterator na nashu nahodku
        //return start->second.value;  //Vozvrawaem znachenie
        if (index > Arrays[name].to or index<Arrays[name].from or index2 > Arrays[name].to2 or index2<Arrays[name].from2)
          throw "Indeks massiva, vyhodit za ego predely";
        return Arrays[name].el2[index-Arrays[name].from][index2-Arrays[name].from2];
    }
    else //Inache opovewaem o tom, chto ne nashli nichego s takim imenem
    {
        printf ("The variable/constant with this name isn't exists");
        throw "Nevernoe imja massiva";
    }
}

/**@fuction isConst
Funkcija proverki na konstantu

name - Imja peremennoj/konstanty
return - Harakteristika (true - konstanta, false - peremennaja)
*/
bool isConst (const char* name)
{
    if (Vars.count(name) != 0) //Nahodim peremennuju/konstantu v karte
    {
        //start->second = Vars[name]; //Stavim iterator na nashu nahodku
        //return start->second.isConst; //Vozvrawaem harakteristiku (true - konstanta, false - peremennaja)

        return Vars[name].isConst;
    }
    else //Inache opovewaem o tom, chto ne nashli nichego s takim imenem
    {
        printf ("The variable/constant with this name isn't exists");
        return 0;
    }
}

/**@fuction fuction
Funkcija vyvoda soderzhanija vseh kart na jekran (dlja testa)*/
void printVars ()
{
    printf ("Name\t\tValue\t\tType\n\n");
    for (start = Vars.begin (); start != Vars.end (); start++)

        if (start->second.type == INTEGER)
            printf ("%s\t\t%.0f\t\t%d - %s\n", start->first.c_str(), getValue(start->first.c_str()), GetTypeVar (start->first.c_str() ), typeToName(GetTypeVar (start->first.c_str() )) );
        //std::cout<<start->first.c_str()<<"\t\t"<<start->second.value<<"\t\t"<<GetTypeVar (start->first.c_str() )<<" - "<<typeToName(GetTypeVar (start->first.c_str() ))<<"\n";
        else if (start->second.type == REAL)
            printf ("%s\t\t%5.3f\t\t%d - %s\n", start->first.c_str(), getValue(start->first.c_str()), GetTypeVar (start->first.c_str() ), typeToName(GetTypeVar (start->first.c_str() )) );

}
/**vyvodit soderzhimoe massivov, dlja otladki*/
void printArrays()
{
    printf ("Name\t\tDimension\t\tType\n\n");
    for (start2 = Arrays.begin (); start2 != Arrays.end (); start2++)
      if (start2->second.isBig == false)
      {
          if (start2->second.type == INTEGER)
          {
             cout<<start2->first.c_str()<<"\t\tOdnomernyj\t\tINTEGER\n";
             for (int i = 0; i < Arrays[start2->first].to - Arrays[start2->first].from; i++)
                cout<<"|"<<(int)Arrays[start2->first].el[i]<<"|";
          }
          else
          {
             cout<<start2->first.c_str()<<"\t\tOdnomernyj\t\tREAL\n";
             for (int i = 0; i < Arrays[start2->first].to - Arrays[start2->first].from; i++)
                cout<<"|"<<Arrays[start2->first].el[i]<<"|";
          }
       }
       else
       {
          if (start2->second.type == INTEGER)
          {
             cout<<start2->first.c_str()<<"\t\tDvumernyj\t\tINTEGER\n";
             for (int i = 0; i < Arrays[start2->first].to - Arrays[start2->first].from; i++)
             {
                 for (int j = 0; j < Arrays[start2->first].to2 - Arrays[start2->first].from2; j++)
                    cout<<"|"<<(int)Arrays[start2->first].el2[i][j]<<"|";
                 cout<<endl;
             }
          }
          else
          {
             cout<<start2->first.c_str()<<"\t\tDvumernyj\t\tREAL\n\n";
             for (int i = 0; i < Arrays[start2->first].to - Arrays[start2->first].from; i++)
             {
                 for (int j = 0; j < Arrays[start2->first].to2 - Arrays[start2->first].from2; j++)
                    cout<<"|"<<(int)Arrays[start2->first].el2[i][j]<<"|";
                 cout<<endl;
             }
          }
       }
//              cout<<start2->first<<endl;
//            for (int i=0;start2->second.to-start2->second.from; i++)
//              //printf ("%s\t\t%.0f\t\t%d - %s\n", start2->first.c_str(), getValue(start2->first.c_str()), GetTypeVar (start2->first.c_str() ), typeToName(GetTypeVar (start2->first.c_str() )) );
//                cout<<"|"<<start2->second.el[i]<<"|";
//            cout<<endl;
      /*    }
        //std::cout<<start2->first.c_str()<<"\t\t"<<start2->second.value<<"\t\t"<<GetTypeVar (start2->first.c_str() )<<" - "<<typeToName(GetTypeVar (start2->first.c_str() ))<<"\n";
        else if (start2->second.type == REAL)
            printf ("%s\t\t%5.3f\t\t%d - %s\n", start2->first.c_str(), getValue(start->first.c_str()), GetTypeVar (start->first.c_str() ), typeToName(GetTypeVar (start->first.c_str() )) );
        }*/

   /** for (int i = 0; i < Arrays[start2->first].to - Arrays[start2->first].from; i++)
    {
        for (int j = 0; j < Arrays[start2->first].to2 - Arrays[start2->first].from2; j++)
           cout<<"|"<<(int)Arrays[start2->first].el2[i][j]<<"|";
        cout<<endl;
    }*/

/*Oleg, tut nado prohodit' iteratorom po vsem imenam, potom ispol'zuja imja i pomnja o isBig vyvodit' soderzhimoe*/

}


/**@function ReadFromTo
chtenie Nizhnej granicy massiva (ljuboj)*/
int ReadFromTo ()
{
    get_token(); //Schityvaem granicu massiva
    ///esli granic - chislo
  if (token_type == INTEGER)
    {
        if (atoi(token) < 0)
        {
            printf ("Granica massiva dolzhna byt' >= 0\n");
            return -1;
        }

        else
        {
            //cout<<atoi(token)<<endl;
            return atoi(token);
        }
        //temp2.from = atoi(token);
    }
    ///esli granica - peremennvja
    if (token_type == VARIABLE)
    {

        if (GetTypeVar (token) != INTEGER)
        {
            printf ("Granica massiva dolzhna byt' tipa INTEGER\n");
            return -1;
        }


        if (isConst (token) != true)
        {
            printf ("Peremennaja ne mozhet byt' granicej massiva\n");
            return -1;
        }

        if (getValue (token) < 0)
        {
            printf ("Granica massiva dolzhna byt' >= 0\n");
            return -1;
        }
            //std::cout<<5;//getValue(token);
        //std::cout<<"call "<<(int) getValue(token)<<std::endl;

        return (int) getValue(token);

                    //temp2.from = atoi(token)

//
    }
}


/**@function AddArray dobavljaet peremennye v kartu peremennyh
*/
int AddArray (const char* name)
{
//    testing=false;
   int from, to, from2, to2;
   Array temp;

   temp.isBig = false;// odnomernyj massiv, po umolchaniju

    get_token();  //Schityvaem sluzhebnoe slovo "array"
    pres(int(tok));
    if ( tok != ARRAY )
  {
    printf ("Expected 'ARRAY'");
    return ERROR;
  }

  get_token(); //Schityvaem "["
   pres(token);
  if ( token[0] != '[' )
  {
    printf ("Expected '['");
    return ERROR;
  }

  from = ReadFromTo (); //Schityvanie nizhnej granicy massiva
  pres(from);
  if ( from == -1 )
    return ERROR;


   get_token(); //Schityvaem razdeliteli granic massiva ".."
  pres(token);
  if ( ! ((token_type == DELIMITER) && (token[0] == '.' ) ) )
  {
    printf ("Expected '..'");
    return ERROR;
  }

  get_token();
  pres(token);
  if ( ! ((token_type == DELIMITER) && (token[0] == '.' ) ) )
  {
    printf("Expected '..'");
    return ERROR;
  }

  to = ReadFromTo (); //Schityvanie verhnej granicy massiva
  pres(to);
  if ( to == -1 )
    return ERROR;

    if (to <= from)
    {
        printf("Verhnjaja granica massiva dolzhna byt' bol'she nizhnej");
        return ERROR;
    }

    get_token();
    pres(token,"token");
    //esli massiv dvumernyj
  if( token_type == DELIMITER && token[0] == ',' )
  {

        from2 = ReadFromTo (); //Schityvanie nizhnej granicy massiva
        pres(from2);
        if ( from2 == -1 )
            return ERROR;

        get_token(); //Schityvaem razdeliteli granic massiva ".."
        pres(token);
        if ( ! ((token_type == DELIMITER) && (token[0] == '.' ) ) )
        {
            printf ("Expected '..'");
            return ERROR;
        }

        get_token();
        pres(token);
        if ( ! ((token_type == DELIMITER) && (token[0] == '.' ) ) )
        {
            printf("Expected '..'");
            return ERROR;
        }

        to2 = ReadFromTo (); //Schityvanie verhnej granicy massiva
      pres(to2);
      //std::cout<<to2<<endl;
        if ( to2 == -1 )
            return ERROR;

        if (to2 <= from2)
        {
            printf("Verhnjaja granica massiva dolzhna byt' bol'she nizhnej\n");
            return ERROR;
        }
        //nashe genial'noe vydelenie pamjati :)
        temp.to2 = to2;
        temp.from2 = from2;
        temp.isBig = true;
        temp.to = to;
        temp.from = from;
        temp.el = NULL;

        temp.el2 = new float* [to-from]; //Vydelenie pamjati pod stroki
        for (int i=0; i<to-from; i++)
        {
            temp.el2[i] = new float [to2-from2]; //Vydelenie pamjati pod stolbcy

            if (testing) // esli otladka, to zapolnjaem indeksami, inache nuljami
                for (int j=0; j<to2-from2;j++)
                {
                    temp.el2[i][j]=(float)j;
                    cout<<temp.el2[i][j];
                }
                    //tut bylo temp.el[j]=j; - najdi, 2 otlichija :)
            else
                for (int j=0; j<to2-from2;j++)
                {
                    temp.el2[i][j]=0;
                    cout<<temp.el2[i][j];
                }

             /**   // ob#javlenie dvumernogo dinamicheskogo massiva na 10 jelementov:
float **ptrarray = new float* [2]; // dve stroki v massive
    for (int count = 0; count < 2; count++)
        ptrarray[count] = new float [5]; // i pjat' stolbcov*/

//                memset(temp.el2[i], 0, to2-from2);
            cout<<endl;
            }



        //Arrays[name] = temp;


        get_token(); //Schityvaem "["
        pres(token);
    }

    if ( ( (token_type==DELIMITER) && (token[0]==']') ) )
    {
        get_token();
        pres((int)tok);
    if ( (int)tok != OF )
    {
      serror("Expected 'of'\n");
      return ERROR;
    }

    get_token();
    pres((int)token_type);
    //if( token_type == ERROR ) return false;

    if ( (int)tok == INTEGER )
    {
        temp.type = INTEGER;
    }
        else if ( (int)tok == REAL )
    {
        temp.type = REAL;
    }
    else
    {
        serror("Expected 'INTEGER' or 'REAL'\n");
      return ERROR;
    }

       //SAMO  vydelenie!
       if (!temp.isBig)
       {
           temp.from = from;
           temp.to = to;
           temp.el = new float [to-from];
           //esli otladka, to zapolnjaem indeksami, inache nuljami
           if (testing)
               for (int i=0;i<to-from;i++)
                       temp.el[i]=i;
           else
               for (int j=0; j<to-from;j++)
                   temp.el[j]=0;
       }
//       else
//           for (int i = 0; i < temp.to - temp.from; i++)
//                delete [] temp.el2[i];
    }
    else
    {
        serror("Expected ']'\n");
        return ERROR;
    }

    Arrays[name] = temp;
cout<<"ARRA: "<<Arrays[name].el2[2][2]<<endl;
    Arrays[name].el2[2][2]=100.0;
 pres(Arrays[name].el2[2][2],"EXAMPLE");
//    Arrays[name].el2[1][0]=(float)50;

//   for (int i=0;i<Arrays[name].to-Arrays[name].from;i++)
//       {
//           for (int j=0; j<Arrays[name].to2-Arrays[name].from2;j++)
//           {
//                cout<<(int)Arrays[name].el2[i][j]<<"|";
//           }
//                cout<<endl;
//       }
//    for (int i = 0; i < Arrays[name].to - Arrays[name].from; i++)
//    {
//        for (int j = 0; j < Arrays[name].to2 - Arrays[name].from2; j++)
//           cout<<"|"<<(int)Arrays[name].el2[i][j]<<"|";
//        cout<<endl;
//    }

 for (int i = 0; i < temp.to - temp.from; i++)
    delete [] temp.el2[i];

    return 1;
}

#endif // VARS&ARRAYS_H_INCLUDED
