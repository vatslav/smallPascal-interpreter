100500!!!

Readme файл пректа

1)синтаксический анализатор - сделать сложение флоат и инт через перегрузку функций

мысль: обертка что бы текст ошибок был на 2 языках

4)анализатор: сделать с использованием с++

5)спроектировать и закодить работу с переменными и массивами, если требуется подкорректить get_token()

дополнительно:
d)Graphviz
1)реализовать отображение строчки в которой возникла проблема например так: 1)В момент вызова ошибки, 2)по prog вычисляем строку и 3)аргумументом передаем её serror в ней 4)печатаем.

Изменения в архитектуре надо сделать: 1)централизовано все менять 2)научиться выводить строчку ошибки и прописать лишь 1 раз 3)с одной стороны вызываем ошибку (и в нем можно передать тип и состояние) с другой стороны можно добавить глобальную переменную типа ошибки)

То, что было в списке выше, но теперь уже сделано
а)внедрить использование doxygen - сделано
b)довести до центразиованной работы на github + wiki - сделано
3)добавить в get_token обработку комментариев
2)сделать putback, что бы интерпритатор продолжал работать после ошибки или сделать завершение логики работы интерпритатора
0)Сделать функцию котороая выполняет вывод ошибки (пусть сейчас она делает просто вывод сообщения об ошибки, но зато можно: - serror