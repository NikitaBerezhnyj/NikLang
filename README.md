# Мова програмування NikLang

<p align='center'>
  <img src='./VS Code Extintion/niklang-extantion/icon-nl.png' alt='NikLang icon' style="width:50%">
</p>

***Мова програмування NikLang*** - це проєкт в якому я намагався створити функціональну мову програмування на C++. В ході розробки якої було також створено простеньке IDE на python для роботи з NikLang, а також розширення для VS code з підсвіткою синтаксису та додаванням нової іконки. Сподіваюсь вам сподобається те що у мене вийшло і ви будете користуватись цим хоч зрідка.

### ***Швидкий перехід між розділами:***

- [Мова програмування NikLang](#мова-програмування-niklang)
    - [***Швидкий перехід між розділами:***](#швидкий-перехід-між-розділами)
  - [Синтаксис](#синтаксис)
  - [Утиліта ./niklang](#утиліта-niklang)
    - [Стандартний режим](#стандартний-режим)
    - [Отримати допомогу](#отримати-допомогу)
    - [Режим тестування](#режим-тестування)
    - [Режим токенізації](#режим-токенізації)
    - [Режим парсингу](#режим-парсингу)
  - [Власне IDE для NikLang](#власне-ide-для-niklang)
  - [Розширення для VS code](#розширення-для-vs-code)

___

## Синтаксис

...

[Дивитись код](./Programing%20Language/)

## Утиліта ./niklang

***./niklang*** - це утиліта для виконання коду написаного на мові програмування NikLang. Вона має кілька режимів роботи, які дозволяють користувачеві виконувати різні завдання, а також тестувати правильність роботи механізмів виконання коду.

### Стандартний режим

У стандартному режимі програма аналізує та парсить один файл з розширенням .nl. Для запуску програми в цьому режимі потрібно ввести наступну команду:

***./niklang <шлях до файлу з розширенням .nl>***

Наприклад, для запуску програми для файлу example.nl, розташованого в поточному каталозі, потрібно ввести наступну команду:

***./niklang example.nl***

### Отримати допомогу

Якщо ви раптом забудете якийсь ключ, або як працює утиліта, то просто виконайте команду:

***./niklang -- help (або ./niklang -h)*** 

Вона виведе на екран детальну інформацію про утиліту, включаючи список ключів, їх значення і опис.

### Режим тестування

Режим тестування дозволяє користувачеві протестувати програму на наборі тестових файлів. Для запуску програми в цьому режимі потрібно ввести наступну команду:

***./niklang test_all***

Ця команда запустить аналіз та парсинг усіх тестових файлів, розташованих у масиві testFile.

### Режим токенізації

Режим токенізації дозволяє користувачеві отримати список усіх токенов, які використовуються в файлі з розширенням .nl. Для запуску програми в цьому режимі потрібно ввести наступну команду:

***./niklang <шлях до файлу з розширенням .nl> -t***

Наприклад, для отримання списку токенов для файлу example.nl, розташованого в поточному каталозі, потрібно ввести наступну команду:

***./niklang example.nl -t***

Також працює з тестовим режимом через команду

***./niklang test_all -t***

### Режим парсингу

Режим парсингу дозволяє користувачеві отримати абстрактну синтаксичну дерево (AST) для файлу з розширенням .nl. Для запуску програми в цьому режимі потрібно ввести наступну команду:

***./niklang <шлях до файлу з розширенням .nl> -p***

Наприклад, для отримання AST для файлу example.nl, розташованого в поточному каталозі, потрібно ввести наступну команду:

***./niklang example.nl -t***

Також працює з тестовим режимом через команду:

***./niklang test_all -p***

## Власне IDE для NikLang

...

[Дивитись код](./NikLang%20IDE/)

## Розширення для VS code

...

[Дивитись код](./VS%20Code%20Extintion/niklang-extantion/)