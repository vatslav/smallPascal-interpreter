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
 Структура для переменных типа INTEGER/REAL
int type - Тип идентификатора
float value - Значение идентификатора
bool isConst - Константа/переменная
*/
struct Var
{
    int type;
    float value;
    bool isConst;
};

/**@struct array
Структура для массивов типа INTEGER/REAL
int type - Тип массива
bool isBig - Многомерный/одномерный массив
int from - нижняя граница массива
int to - верхняя граница массива
float *el - элементы массива
*/
struct Array
{
    int type;
    bool isBig;
    int from;
    int to;
    int from2;
    int to2;
    float *el; //указатель на 1 элемент массива
    float **el2;
};

//Для хранения переменных/констант и массивов используем
//ассоциативные массивы (карты/контейнеры)
///Карта для идентификаторов типа INTEGER/REAL
map <string, Var> Vars;
///Карта для массивов типа INTEGER/REAL
map <string, Array> Arrays;

///Итераторы для работы с картами в цикле
map <string, Var>::iterator start = Vars.begin ();
map <string, Array>::iterator start2 = Arrays.begin ();

//Временные объекты наших структур удалил т.к. используем локальные
//Var temp;
//Array temp2;

/**@fuction AddVar
Функция добавления переменной/константы в карту

name - Имя переменной/константы
type - Тип переменной/константы
value - Значение переменой/константы
constant - Характеристика (true - константа, false - переменная)
*/
bool AddVar (char* name, int type, float value, bool constant)
{
   Var temp;
   if (Vars.count(name) == 0) //Если в карте нет переменной с таким именем
   {
       temp.isConst = constant;
       temp.type = type;
       temp.value = value; //Приводим к типу INTEGER
       Vars[name] = temp;   //Кидаем в карту новую пееменную/константу
       return 1;
   }
   else //Иначе сообщаем, что в карте есть переменная/константа с таким именем
       {
           printf ("The variable/constant with this name is already exists");
           return 0;
       }
}

/**@fuction GetTypeVar
Функция получения типа переменной/константы

name - Имя переменной/константы
return - Тип переменной/константы
*/
int GetTypeVar (const char* name)
{
    if (Vars.count(name) != 0) //Находим переменную/константу в карте
    {
        //start->second = Vars[name]; //Ставим итератор на нашу находку
        //return start->second.type;  //Возвращаем тип
        return Vars[name].type;
    }
    else //Иначе оповещаем о том, что не нашли ничего с таким именем
    {
        printf ("The variable/constant with this name isn't exists");
        return 0;
    }
}

/**@fuction getValue
Функция получения значения переменной/константы

name - Имя переменной/константы
return - Значение переменной/константы
*/
float getValue (const char* name)
{
    if (Vars.count(name) != 0) //Находим переменную/константу в карте
    {
        //start->second = Vars[name]; //Ставим итератор на нашу находку
        //return start->second.value;  //Возвращаем значение
        return Vars[name].value;
    }
    else //Иначе оповещаем о том, что не нашли ничего с таким именем
    {
        printf ("The variable/constant with this name isn't exists");
        return -1.0;
    }
}
 ///Получить значение одномерного массива
float getValue (const char* name, int index)
{

    if (Arrays.count(name) != 0) //Находим переменную/константу в карте
    {
        //start->second = Vars[name]; //Ставим итератор на нашу находку
        //return start->second.value;  //Возвращаем значение
        if (index > Arrays[name].to or index<Arrays[name].from)
          throw "Индекс массива, выходит за его пределы";
        return Arrays[name].el[index-Arrays[name].from];
    }
    else //Иначе оповещаем о том, что не нашли ничего с таким именем
    {
        printf ("The variable/constant with this name isn't exists");
        return -1.0;
    }
}

 ///Получить значение двумерного массива
float getValue (const char* name, int index, int index2)
{

    if (Arrays.count(name) != 0) //Находим переменную/константу в карте
    {
        //start->second = Vars[name]; //Ставим итератор на нашу находку
        //return start->second.value;  //Возвращаем значение
        if (index > Arrays[name].to or index<Arrays[name].from or index2 > Arrays[name].to2 or index2<Arrays[name].from2)
          throw "Индекс массива, выходит за его пределы";
        return Arrays[name].el2[index-Arrays[name].from][index2-Arrays[name].from2];
    }
    else //Иначе оповещаем о том, что не нашли ничего с таким именем
    {
        printf ("The variable/constant with this name isn't exists");
        throw "Неверное имя массива";
    }
}

/**@fuction isConst
Функция проверки на константу

name - Имя переменной/константы
return - Характеристика (true - константа, false - переменная)
*/
bool isConst (const char* name)
{
    if (Vars.count(name) != 0) //Находим переменную/константу в карте
    {
        //start->second = Vars[name]; //Ставим итератор на нашу находку
        //return start->second.isConst; //Возвращаем характеристику (true - константа, false - переменная)

        return Vars[name].isConst;
    }
    else //Иначе оповещаем о том, что не нашли ничего с таким именем
    {
        printf ("The variable/constant with this name isn't exists");
        return 0;
    }
}

/**@fuction fuction
Функция вывода содержания всех карт на экран (для теста)*/
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
/**выводит содержимое массивов, для отладки*/
void printArrays()
{
    printf ("Name\t\tDimension\t\tType\n\n");
    for (start2 = Arrays.begin (); start2 != Arrays.end (); start2++)
      if (start2->second.isBig == false)
      {
          if (start2->second.type == INTEGER)
          {
             cout<<start2->first.c_str()<<"\t\tОдномерный\t\tINTEGER\n";
             for (int i = 0; i < Arrays[start2->first].to - Arrays[start2->first].from; i++)
                cout<<"|"<<(int)Arrays[start2->first].el[i]<<"|";
          }
          else
          {
             cout<<start2->first.c_str()<<"\t\tОдномерный\t\tREAL\n";
             for (int i = 0; i < Arrays[start2->first].to - Arrays[start2->first].from; i++)
                cout<<"|"<<Arrays[start2->first].el[i]<<"|";
          }
       }
       else
       {
          if (start2->second.type == INTEGER)
          {
             cout<<start2->first.c_str()<<"\t\tДвумерный\t\tINTEGER\n";
             for (int i = 0; i < Arrays[start2->first].to - Arrays[start2->first].from; i++)
             {
                 for (int j = 0; j < Arrays[start2->first].to2 - Arrays[start2->first].from2; j++)
                    cout<<"|"<<(int)Arrays[start2->first].el2[i][j]<<"|";
                 cout<<endl;
             }
          }
          else
          {
             cout<<start2->first.c_str()<<"\t\tДвумерный\t\tREAL\n\n";
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

/*Олег, тут надо проходить итератором по всем именам, потом используя имя и помня о isBig выводить содержимое*/

}


/**@function ReadFromTo
чтение Нижней границы массива (любой)*/
int ReadFromTo ()
{
    get_token(); //Считываем границу массива
    ///если границ - число
	if (token_type == INTEGER)
    {
        if (atoi(token) < 0)
        {
            printf ("Граница массива должна быть >= 0\n");
            return -1;
        }

        else
        {
            //cout<<atoi(token)<<endl;
            return atoi(token);
        }
        //temp2.from = atoi(token);
    }
    ///если граница - переменнвя
    if (token_type == VARIABLE)
    {

        if (GetTypeVar (token) != INTEGER)
        {
            printf ("Граница массива должна быть типа INTEGER\n");
            return -1;
        }


        if (isConst (token) != true)
        {
            printf ("Переменная не может быть границей массива\n");
            return -1;
        }

        if (getValue (token) < 0)
        {
            printf ("Граница массива должна быть >= 0\n");
            return -1;
        }
            //std::cout<<5;//getValue(token);
        //std::cout<<"call "<<(int) getValue(token)<<std::endl;

        return (int) getValue(token);

                    //temp2.from = atoi(token)

//
    }
}


/**@function AddArray добавляет переменные в карту переменных
*/
int AddArray (const char* name)
{
//    testing=false;
   int from, to, from2, to2;
   Array temp;

   temp.isBig = false;// одномерный массив, по умолчанию

    get_token();  //Считываем служебное слово "array"
    pres(int(tok));
    if ( tok != ARRAY )
	{
		printf ("Expected 'ARRAY'");
		return ERROR;
	}

	get_token(); //Считываем "["
   pres(token);
	if ( token[0] != '[' )
	{
		printf ("Expected '['");
		return ERROR;
	}

	from = ReadFromTo (); //Считывание нижней границы массива
	pres(from);
	if ( from == -1 )
		return ERROR;


   get_token(); //Считываем разделители границ массива ".."
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

	to = ReadFromTo (); //Считывание верхней границы массива
	pres(to);
	if ( to == -1 )
		return ERROR;

    if (to <= from)
    {
        printf("Верхняя граница массива должна быть больше нижней");
        return ERROR;
    }

    get_token();
    pres(token,"token");
    //если массив двумерный
	if( token_type == DELIMITER && token[0] == ',' )
	{

        from2 = ReadFromTo (); //Считывание нижней границы массива
        pres(from2);
        if ( from2 == -1 )
            return ERROR;

        get_token(); //Считываем разделители границ массива ".."
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

        to2 = ReadFromTo (); //Считывание верхней границы массива
    	pres(to2);
    	//std::cout<<to2<<endl;
        if ( to2 == -1 )
            return ERROR;

        if (to2 <= from2)
        {
            printf("Верхняя граница массива должна быть больше нижней\n");
            return ERROR;
        }
        //наше гениальное выделение памяти :)
        temp.to2 = to2;
        temp.from2 = from2;
        temp.isBig = true;
        temp.to = to;
        temp.from = from;
        temp.el = NULL;

        temp.el2 = new float* [to-from]; //Выделение памяти под строки
        for (int i=0; i<to-from; i++)
        {
            temp.el2[i] = new float [to2-from2]; //Выделение памяти под столбцы

            if (testing) // если отладка, то заполняем индексами, иначе нулями
                for (int j=0; j<to2-from2;j++)
                {
                    temp.el2[i][j]=(float)j;
                    cout<<temp.el2[i][j];
                }
                    //тут было temp.el[j]=j; - найди, 2 отличия :)
            else
                for (int j=0; j<to2-from2;j++)
                {
                    temp.el2[i][j]=0;
                    cout<<temp.el2[i][j];
                }

             /**   // объявление двумерного динамического массива на 10 элементов:
float **ptrarray = new float* [2]; // две строки в массиве
    for (int count = 0; count < 2; count++)
        ptrarray[count] = new float [5]; // и пять столбцов*/

//                memset(temp.el2[i], 0, to2-from2);
            cout<<endl;
            }



        //Arrays[name] = temp;


        get_token(); //Считываем "["
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

       //САМО  выделение!
       if (!temp.isBig)
       {
           temp.from = from;
           temp.to = to;
           temp.el = new float [to-from];
           //если отладка, то заполняем индексами, иначе нулями
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
