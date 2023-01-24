# Задача 2-1. Игра "Жизнь"

### Общие сведения
Игра "Жизнь" - клеточный автомат, подробно описанный по [ссылке](http://en.wikipedia.org/wiki/Conway's_Game_of_Life)

### Требования к программе
+ Уметь считывать «вселенную» из файла (см. формат файла ниже). Вселенная описывается: 
  + правилом перехода клетки; 
  + размером поля;
  + состоянием ячеек;
+ Файл может подаваться программе при старте в качестве параметра входной строки. В случае, если файл не подан, начинать игру на произвольно инициализированном поле некоего фиксированного размера, красиво отображающегося на консоли. Поле, инициализированное случайным образом малоинтересно, поэтому рекомендуется начинать игру на каких-нибудь заранее продуманных примерах.
+ Третий режим ("оффлайн"): программе подается входной файл, количество итераций, выходной файл. Программа рассчитывает состояние поля после указанного количества итераций и сохраняет вселенную в указанный выходной файл. Параметры командной строки:
  + `--input <filename>` или `-I <filename>` - входной файл;
  + `--output <filename>` или `-o <filename>` - выходной файл;
  + `--iterations <n>` или `-i <n>` - количество итераций;
+ После старта игры, программа ожидает команды:
  + `dump <filename>` - сохранить вселенную в файл;
  + `tick <n>` - рассчитать n (по умолчанию 1) итераций и напечатать результат. На экране перед распечатанным полем должно отображаться имя вселенной, правило перехода и номер текущей итерации;
  + `exit` - завершить игру;
  + `help` - распечатать справку о командах;
+ Должен поддерживаться расчет по разным правилам перехода состояний ячеек (см. формат файла).
+ Поле игры считать замкнутым (тороидальным). Таким образом, соседи сверху первого ряда поля - клетки последнего ряда и наоборот, аналогично для левого и правого краев вселенной.
+ Программа должна быть разбита на классы, использование единственного God Object, хранящего состояние игры, рассчитывающего состояния и взаимодействующего с пользователем, не допускается.
+ Реализация программы подразумевает активное освоение стандартной библиотеки: файловых потоков, контейнеров, алгоритмов.
+ Реализация игры подразумевает «играбельность» и максимальную дружелюбность к пользователю: ясные сообщения об ошибках формата файла, и пр., наличие справки и демонстрация ее при неправильном вводе и т. д.
+ Основной функционал ("механика") игры должен быть покрыт юнит-тестами.
+ При сдаче задания продемонстрировать 5-10 примеров интересных вселенных с различными правилами перехода (можно брать с википедии или профильных ресурсов).

### Формат файла
[Life 1.06](http://conwaylife.com/wiki/Life_1.06)

### Дополнение к формату
+ Строка файла, содержащая комментарий с именем вселенной:

  Пример: `#N My universe`
+ Строка файла, содержащая комментарий с правилом перехода следующего вида:

    `#R Bx Sy`, где 
  + x и y - последовательности различных цифр из множества [ 0, 8 ];
  + B (birth) содержит количества живых ячеек, необходимых для "рождения" клетки;
  + S (survival) - ячеек, необходимых для "выживания" клетки;
  
  Пример:
  + `#R B3 S23` - классическая игра жизнь (2 ячейки для рождения, 2 или 3 – для выживания)
  + `#R B3 S01234567` - ячейки бессмертны.

+ При разборе формата о некритических ошибках сообщать предупреждениями и продолжать работу (например, повторяющиеся координаты живой ячейки, отсутствие имени или правила перехода)