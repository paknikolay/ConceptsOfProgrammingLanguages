# ConceptsOfProgrammingLanguages
**Важно: регистр верхний**
Инструкции языка:
1. ``ADD`` - складывает 2 числа на стеке, и кладет сумму на стек
2. ``SUB`` - вычитает 2 числа на стеке в обратном порядке(из нижнего верхний) и кладет на стек
3. `MUL`  - умножает 2 числа на стеке и кладет результат на стек
4. `DIV` - делит 2 числа на стеке в обратном порядке на цело и кладет результат на стек
5. `PUSH` -  кладет число на стек `PUSH 5`
6. `POP` - убирает число со стека в регистр `POP 1`:
    1. `1` - `rax`
    2. `2` - `rbx`
    3. `3` - `rcx`
    4. `4` - `rdx`
7. `PUSHR` кладет число в стек с регистра `PUSHR 1`
8. `OUT` - печатает верхушку стека на экран
9. `IN` - ввод с клавиатуры в стек
10. `PRINT` - выводит на экран строку, объявленную в `DATA`, по имени
11. `JMP` - безусловный переход на метку `JMP 3`
12. `JA` - сравнивает 2 числа на верхушке стека, если верхний больше, то осуществляет переход на метку
13. `JB` - сравнивает 2 числа на верхушке стека, если верхний меньше, то осуществляет переход на метку
14. `JE` - сравнивает 2 числа на верхушке стека, если равны, то осуществляет переход на метку
15. `CALL` - вызывает функцию по имени
16. `RET` - возвращается по адресу возврата, положенном `CALL`
17. `:` - лейбл `: 4`(только числа)
18. `STOP` - останавливает процессор, обязательно после кода программы
19. `DATA` - слово, после которого начинается блок с описанием строковых переменных
20. `:` - в секции `DATA` объявление переменной `: 5 "hello world"`, `5` - название переменной(поддерживается только числовые имена), `"hello world"` - значение переменной, кавычки обязательные
21. `END` - обязательно в конце программы, после объявления данных, если они есть, иначе сразу после кода программы
