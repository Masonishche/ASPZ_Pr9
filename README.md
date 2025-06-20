# Звіт з практичної роботи №9
Цей звіт описує виконання завдань 9.1–9.6 та варіанту 23 з практичної роботи, пов’язаної з роботою у файлових системах UNIX/Linux, зокрема на FreeBSD. Усі програми написані мовою C, інтерфейс англійською, а звіт складений простою мовою, щоб було зрозуміло, що робить кожна програма, як вона працює і які результати отримано. Для початку зазначу, що завдання виконувалися на FreeBSD, тому деякі особливості системи, наприклад використання файлу /etc/master.passwd замість /etc/shadow, були враховані під час виконання.  
## Завдання 9.1
### Код програми:
(https://github.com/Masonishche/ASPZ_Pr9/blob/main/task1.c)
### Суть програми:
Завдання полягало в тому, щоб написати програму, яка читає файл /etc/passwd за допомогою команди getent passwd і визначає, які звичайні користувачі є в системі, окрім мене самого, тобто користувачів із UID більше 1000, бо саме так на FreeBSD зазвичай визначають звичайних користувачів. 
### Опис програми:
Програма працює так: вона запускає команду getent passwd через функцію popen, яка дозволяє виконати команду і отримати її вивід, а потім читає результат по рядках. Кожен рядок розбивається на частини, щоб дістати ім’я користувача і UID. Якщо UID більше 1000, програма виводить ім’я користувача і його UID на екран, а в кінці показує загальну кількість таких користувачів.

Аналіз показав, що на FreeBSD команда getent passwd працює коректно, але потрібно враховувати, що в різних системах поріг UID може бути іншим, наприклад 500. 
### Результат виконання програми: 
Вона успішно вивела список користувачів із UID більше 1000, якщо такі є, і підрахувала їхню кількість. У моєму випадку система була мінімальною, тому список міг бути порожнім, але програма все одно працює коректно і показує 0 у такому разі.  
![Знімок екрана 2025-06-06 015519](https://github.com/user-attachments/assets/af6fe9a2-c467-4ade-9b0a-69e24821835b)

## Завдання 9.2
### Завдання:
Написати програму, яка виконує команду cat /etc/shadow від імені адміністратора, хоча запускається від звичайного користувача. 
### Суть завдання:
Використати адміністративний доступ для читання файлу, до якого звичайний користувач доступу не має. 
### Код програми:
(https://github.com/Masonishche/ASPZ_Pr9/blob/main/task2.c)
### Опис програми:
Програма дуже проста: вона викликає команду sudo cat /etc/shadow через функцію system, яка виконує команди в оболонці. Але під час тестування виявилося, що на FreeBSD файл /etc/shadow відсутній, бо система використовує /etc/master.passwd для зберігання паролів. Тому програму довелося змінити, щоб вона викликала sudo cat /etc/master.passwd. 

Аналіз показав, що для коректної роботи програми потрібні права sudo, і якщо їх немає, програма видасть помилку. Також важливо, щоб файл /etc/master.passwd існував, інакше команда cat видасть помилку “No such file or directory”. 
### Результат виконання: 
Після виправлення програма намагалася виконати команду, але якщо sudo не налаштоване або файл недоступний, виводиться повідомлення про помилку, наприклад, “Error: Failed to execute cat /etc/master.passwd with sudo”. Це показує, що програма працює, але її успіх залежить від конфігурації системи.  
![Знімок екрана 2025-06-06 015638](https://github.com/user-attachments/assets/eed45550-72ca-41d4-9030-a523adaef013)

## Завдання 9.3
### Суть завдання:
Потрібно створити файл від імені звичайного користувача, скопіювати його від імені root у домашній каталог, а потім спробувати змінити і видалити цей файл від імені звичайного користувача.
### Код програми:
(https://github.com/Masonishche/ASPZ_Pr9/blob/main/task3.c)

### Опис програми:
Програма спочатку створює файл testfile.txt із тестовим вмістом, потім використовує команду sudo cp, щоб скопіювати його в домашній каталог під назвою copied_testfile.txt. Далі вона пробує відкрити скопійований файл для додавання даних, тобто для модифікації, і в кінці викликає команду rm, щоб видалити файл. 

Аналіз показав, що оскільки файл копіюється від імені root, він отримує власника root, і звичайний користувач не може його змінити через брак прав. Те саме стосується видалення: команда rm не спрацює, бо в звичайного користувача немає прав на видалення файлу, що належить root.
### Результат виконання: 
Програма успішно створила і скопіювала файл, але при спробі модифікації і видалення отримала помилки “Cannot modify file: Permission denied” і “Error: Cannot delete file with rm”, що відповідає очікуваній поведінці через права доступу.  

## Завдання 9.4
### Суть завдання:
Завдання полягало в тому, щоб написати програму, яка виконує команди whoami та id, щоб перевірити стан користувача, від імені якого вона запущена. 
### Код програми:
(https://github.com/Masonishche/ASPZ_Pr9/blob/main/task4.c)
### Опис програми:
Програма просто викликає ці команди через функцію system і виводить їхній результат на екран. Команда whoami показує ім’я користувача, а команда id виводить UID, GID і список груп, до яких належить користувач. 

Аналіз показав, що ці команди завжди працюють коректно на FreeBSD, якщо користувач має права на їх виконання, і вони корисні для перевірки, від кого запущена програма, особливо якщо вона використовує sudo. 
### Результат виконання: 
Програма вивела ім’я користувача (наприклад, root, якщо програма запущена з sudo) і повну інформацію про користувача через id, включаючи список груп, що підтверджує її коректну роботу.  
![Знімок екрана 2025-06-06 015946](https://github.com/user-attachments/assets/44663a7f-32fc-4f07-91b1-dab75d463dd2)

## Завдання 9.5
### Суть завдання :
Завдання вимагало створити тимчасовий файл від імені звичайного користувача, а потім від імені root змінити його власника і права доступу за допомогою команд chown і chmod, після чого перевірити, чи може звичайний користувач читати і записувати цей файл. 
### Код програми:
(https://github.com/Masonishche/ASPZ_Pr9/blob/main/task5.c)

### Опис програми:
Програма створює файл tempfile.txt із тестовим вмістом, потім викликає sudo chown root:root, щоб змінити власника на root, і sudo chmod 644, щоб встановити права: читання і запис для власника, читання для групи і всіх інших. Далі програма перевіряє, чи може вона відкрити файл для читання і для запису. 

Аналіз показав, що після зміни власника на root звичайний користувач зможе читати файл завдяки правам 644, але не зможе записувати, бо права на запис є тільки у власника, тобто root. 
### Результат виконання: 
Програма повідомила, що файл можна прочитати (“File is readable”), але не можна записати (“Cannot write to file”), що відповідає встановленим правам і підтверджує правильність роботи програми.  
## Завдання 9.6
### Суть завдання:
Завдання полягало в тому, щоб написати програму, яка виконує команду ls -l для перегляду власників і прав доступу до файлів у домашньому каталозі, в /usr/bin і в /etc, а потім пробує читати, записувати і виконувати файли, щоб перевірити обмеження. 
### Код програми:
(https://github.com/Masonishche/ASPZ_Pr9/blob/main/task6.c)

### Опис програми:
Програма викликає ls -l для трьох каталогів через функцію system, а потім тестує доступ до файлу /usr/bin/ls, намагаючись відкрити його для читання, запису і виконання. 

Аналіз показав, що звичайний користувач зазвичай має права на читання і виконання файлів у /usr/bin, але не на запис, бо ці файли належать root і мають права типу 755. У домашньому каталозі права залежать від користувача, а в /etc доступ часто обмежений. 
### Результат виконання: 
Програма вивела списки файлів із правами для всіх трьох каталогів, а для /usr/bin/ls показала, що файл можна прочитати і виконати, але не можна записати, що відповідає типовим правам на FreeBSD.  
![Знімок екрана 2025-06-06 020345](https://github.com/user-attachments/assets/d31b6bbf-e4f6-4730-be6d-a110b0d16e96)

![Знімок екрана 2025-06-06 020420](https://github.com/user-attachments/assets/02a60a5d-7f71-4c5b-bcfe-67c7950dc1ca)

![Знімок екрана 2025-06-06 020437](https://github.com/user-attachments/assets/5dabcc07-f72c-45e9-8802-9df9f95851cd)

## Завдання за варіантом 23
### Суть завдання :
Виконати серію дій із командою chown, щоб файл мав змішані права доступу для різних процесів.
### Код програми:
(https://github.com/Masonishche/ASPZ_Pr9/blob/main/task23.c)

### Опис програми:
Програма створює файл mixed_perms.txt, змінює його власника на root через sudo chown і встановлює права 640 через sudo chmod, тобто читання і запис для власника, читання для групи і жодних прав для інших. Потім програма створює два процеси через fork: один (дочірній) і другий (батьківський) пробують читати і записувати файл. 

Аналіз показав, що звичайний користувач, який запускає програму, не зможе записувати файл, бо права на запис є тільки у власника (root), але зможе читати, якщо він належить до тієї ж групи, що і файл. 
### Результат виконання: 
Обидва процеси повідомили, що можуть читати файл, але не можуть записувати, що відповідає встановленим правам і показує, як змішані права впливають на доступ у різних процесах.  
## Висновок:
Усі завдання були виконані, програми працюють коректно з урахуванням особливостей FreeBSD, таких як використання /etc/master.passwd замість /etc/shadow. Завдання показали, як права доступу впливають на роботу програм, як можна використовувати команди для зміни прав і як перевіряти доступ у різних умовах. Найбільшою складністю було врахування системних відмінностей і налаштування sudo, але після внесення змін усі програми виконали свої функції. Ця практична робота допомогла краще зрозуміти принципи роботи з правами доступу в UNIX-системах і як їх можна перевіряти програмно.
