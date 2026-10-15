# Процесс обработки файлов .с компилятором и возможные ошибки

В данной работе будет разбираться сборка программы именно через gcc

Сборка происходит в несколько этапов

* Препроцессирование
* Компиляция
* Ассемблирование
* Линковка
Какие существую ключи для остановки
* -Е  после препроцессирования
* -S после получения ассемблерного кода
* -с после получения объектного файла без линковки
## Препроцессирование
 На данном этапе процессор обрабатывает директивы и подготавливает код
 *  Подключение содержимого заголовка через  #include
 * Раскрытие макросов #define
 * Условное включение кода через #if #ifdef #ifndef 
 *  Обработка других директив, например #error
 Например
 ```c
 #ifndef COUNT
 #define COUNT 3
 #endif
 
 int values[COUNT]
 ```
 Данные команды задают занчения для переменной COUNT, если до этого это не было сделано.

### Вероятные ошибки на данном этапе:
 ```zsh
 fatal error: foo.h No such file or directory
 ```
 Появляются, когда препроцессор не смог найти заголовочный файл
 Пример:
 ```c
 #include <stdioo.h>
 
 int main() {
	 printf("Hello");
	 return 0;
 }
 ```
 Вызывает ошибку:
 ```zsh
 gcc -E main.c -o main.i
 
 main.c:2: fatal error: stdioo.h: No such file or directory
 ```
 Решается простым исправлением имени заголовка
 
 Если заголовок верный, то он может находиться вне пути поиска. Тогда для решения нужно добавить каталог в пути поиска:
 ```zsh
 gcc -E -Iinclude main.c -o main.i
 ```
 Где include - имя каталога, где находится заголовочный файл


 Ещё одной ситуацией может послужить неверные команды препроцессору
 ```c
 #define DEBUG
 
 #ifdef DEBUG
 
 int debug = 1;
 ```
 В результате выполнения появится ошибка
 ```zsh
 gcc -E main.c -o main.i
 
 main.c:2: error: unterminated #ifdef
 ```


 Ещё ошибки могут быть вызваны самим разработчиком:
 ```c
 #ifndef SIZE
 #error "SIZE must be defined"
 #endif
 
 int buffer[SIZE];
 ```
 
 ```zsh
 gcc -E main.c -o main.i
 main.c:2:2: error: #error "SIZE must be defined"
 ```
 Такую ошибку можно решить изменением программы, а можно прямо при запуске gcc
 ```zsh
 gcc -DSIZE=16 -E main.c -0 main.i
 ```
 -D определяет макрос

## Компиляция
На этом этапе компилятор проверяет структкуру и смысл программы, затем генерирует код
Логические шаги:
* Логический анализ - ==🟢распозанёт элементы языка: имена, ключевые слова, числа, строки, операторы==
* Синтаксический анализ - ==🟢проверяет, складываются ли токены в допустимые конструкции языка, и формирует внутреннее представление программы==
* Семантический анализ - ==🟢прверяет объявления, облисти видимости, типы, допустимые операции и вызовы==
* Оптимизация - ==🟢преобразует внутреннее представление, сохраняя поведение корректной программы: вычисляет константы, удаляет ненужный код, встраивает функции, преобразует циклы==
* Генерация кода - ==🟢выбирает машинные инструкции, распределяет значения по регистрам в памяти, реализует вызовы функций согласно соглашениям целевой платформы. В результате получается ассемблерный код==
### Возможные ошибки:
Пропущена ";"
```c
#include <stdio.h>

int main() {
	printf("Hello")
	return 0;
}
```

```zsh
gcc -E main.c -o main.i
gcc -S main.c -o main.i
main.c: In function ‘main’:
main.c:4:24: error: expected ‘;’ before ‘}’ token

```
Пропущена закрывающая  "}"
```c
#include <stdio.h>

int main() {
	print("Hello");
	return 0;
```

```zsh
gcc -E main.c -o main.i
gcc -S main.c -o main.i

main.c: In function ‘main’:
main.c:4:24: error: expected ‘;’ before ‘}’ token
```

Использована необъявленная переменная
```c
int main() {
	return result;
}
```

```zsh
gcc -E main.c -o main.i
gcc -S main.c -o main.i
main.c: In function ‘main’:
main.c:2:16: error: ‘result’ undeclared (first use in this function)
```
Для решения подобной проблемы достаточно объявить переменную, перед тем как использовать

Подобное может случиться, когда переменная объявлена внутри блока
```c
int main(void) {
    {
        int result = 0;
    }

    return result;
}
```

```zsh
gcc -E main.c -o main.i
gcc -S main.c -o main.i
main.c: In function ‘main’:
main.c:6:12: error: ‘result’ undeclared (first use in this function)
```
Переменная существует в области видимости внутренних фигурных скобок. За пределами блока её имя недоступно. Чтобы использовать её дальше, объявление нужно перенести во внешний блок.

Ещё один случай, когда объявление функции противоречит её определению
```c
int square(int x);

double square(double x) {
	return x * x;
}
```

```zsh
gcc -E main.c -o main.i
gcc -S main.c -o main.i
main.c:3:8: error: conflicting types for ‘square’; have ‘double(double)’
    3 | double square(double x) {
      |        ^~~~~~
main.c:1:5: note: previous declaration of ‘square’ with type ‘int(int)’
    1 | int square(int x);

```
Решается исправлением объявления или самого определения
## Ассемблирование
Ассемблер получает текст с инструкциями целевого процессора и создаёт `.o`

Объектный файл обычно содержит:

- машинный код;
- данные;
- таблицу символов — имена определений и внешних ссылок;
- записи релокаций — места, которые нужно скорректировать при связывании;
- отладочную информацию, если она была запрошена.

### Возможные ошибки
Современные сборщики обычно не допускают подобных ошибок, поэтому их можно добиться только введя ассемблерную функцию в код
```c
int main() {
	__asm__("this_is_not_an_instruction");
	return 0;
}
```

```zsh
gcc -E main.c -o main.i
gcc -S main.c -o main.i
gcc -c main.c -o main.i
main.c: Assembler messages:
main.c:2: Error: no such instruction: `this_is_not_an_instruction'
```
Подобные ошибки можно избежать просто не добавляя в код функции ассемблера,  либо вводить их правильно.

## Линковщик
Связывает обЪектные файлы и бибилотеки
Например в данном примере:
```c
`math_utils.h`

#ifndef PROJECT_MATH_UTILS_H
#define PROJECT_MATH_UTILS_H

float power(float a, int b);

#endif
```

```c
`math_utils.c`

#include "math_utils.h"

float power(float number, int pow) {
	float result = 1;
	for(int i = 0; i < pow; ++i)
		result *= number;
	return result;
}
```

```c
`main.c`

#include <stdio.h>
#include "math_utils.h"

int main() {
	printf("%f", power(12, 3));
	return 0;
}
```

Препроцессор только добавляет заголовочный файл, а линковщик уже соединяет файлы вместе.
```zsh
gcc main.c math_utils.c -o program
```
Так можно собрать файлы вместе



```zsh
gcc main.c -o program
```
 Ошибочный вариант, так как линковщик не будет добавлять файлс функцией, но при этом ошибка возникнет только на этапе линковки, ведь препроцессор добавит заголовочный файл.
 ```zsh
gcc -E main.c -o main.i
gcc -S main.c -o main.i
gcc -c main.c -o main.i
gcc main.c -o program
/usr/bin/ld: /tmp/cc1KqzJk.o: in function `main':
main.c:(.text+0x18): undefined reference to `power'
 ```
 Что нужно проверить, если возникает ошибка на данном этапе
 * Реализована ли функция
 * Добавлен ли её объектный файл или библиотека в команду
 * Совпадает ли имя
 * Не скрыто ли определение
 * Не спрятано ли оно директивами #ifdef 
 Также проблемы могут возникнуть, если переменная или функция объявлена дважды:
 ```c
 `counter.c`
 
 int result = 0;
 
 ```

```c
`main.c`

int resultn = 1;

int main() {
	return result;
}
```

```zsh
gcc -c counter.c -o counter
gcc -c main.c -o main
gcc main counter -o program
/usr/bin/ld: counter:(.bss+0x0): multiple definition of `result'; main:(.data+0x0): first defined here
collect2: error: ld returned 1 exit status
```

Чтобы решить данную ситуацию можно:
```c
`main.c`

extern int result;

int main() {
	return result;
}
```
Предупредить компилятор, что данная переменная будет объявлена позже


В случае функции нужно оставить лишь одно определение, либо проконтролировать её определение с помощью директив препроцессора:
```c
#ifndef POWER
#define POWER
double power(double a, int b) {
	int result = 1;
	for(int i = 0; i < b; ++i)
		result *= a;
	return result;
}
#endif
```

Ещё одной проблемой может стать то, что заголовочный файл подключен, а библиотека нет

```c
#include <math.h>
#include <stdio.h>

int main() {
    double x;

    if (scanf("%lf", &x) != 1) {
        return 1;
    }

    printf("%f\n", sqrt(x));
    return 0;
}
```

```zsh
gcc -c main.c -o main
gcc main.c -o program
/usr/bin/ld: /tmp/ccPij6Ed.o: in function `main':
main.c:(.text+0x4c): undefined reference to `sqrt'
collect2: error: ld returned 1 exit status
```

Для решения этой проблемы нужно подключить бибилиотеку вручную:
```zsh
gcc main.c -lm -o program
```
Так линковщик добавит  libm - математическая бибилиотека
## Итог
Сборка С - программы проходит 4 этапа, и на каждом могут встретиться свои ошибки, которые надо уметь различать и решать.
Все скриншоты:
![[Screenshot from 2026-10-15 00-12-43.png]]
![[Screenshot from 2026-10-15 00-13-13.png]]
![[Screenshot from 2026-10-15 00-11-27.png]]
![[Screenshot from 2026-10-15 00-12-02.png]]
![[Screenshot from 2026-10-15 00-16-46.png]]
![[Screenshot from 2026-10-15 00-20-35.png]]
![[Screenshot from 2026-10-15 00-23-16.png]]
![[Screenshot from 2026-10-15 00-27-18.png]]
![[Screenshot from 2026-10-15 00-35-58.png]]
![[Screenshot from 2026-10-15 08-35-35.png]]
![[Screenshot from 2026-10-15 14-19-23.png]]
![[Screenshot from 2026-10-15 14-22-08.png]]
![[Screenshot from 2026-10-15 15-57-51.png]]