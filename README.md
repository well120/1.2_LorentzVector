# 1.2 Перегрузка операторов для `LorentzVector`

В [предыдущем задании](https://github.com/pycpp2019/1.1_LorentzVector) вы уже реализовали класс `LorentzVector`.

Для класса `LorentzVector` перегрузите операторы
+ Сложения `operator+` и `operator+=`)
+ Вычитания (`operator-` и `operator-=`)
+ Унарного минуса (`operator-`)
+ Умножения (`operator*` и `operator*=`)
+ Вывода в стандартный поток `operator<(std::ostream& out, const LorentzVector& lv)`

Указания
    + Создайте для этой задачи новый проект
    + Оператор вывода в стандартный поток не следует включать в класс `LorentzVector`. Если необходим доступ к приватным членам `LorentzVector`, можно объявить этот оператор с помощью ключевого слова `friend`.
