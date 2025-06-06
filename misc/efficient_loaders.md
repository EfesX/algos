# Эффективные погрузчики

На крупном заводе решили проверить эффективность работы погрузчиков и провели эксперимент: установили на складах датчики iBeacon и отслеживали перемещение погрузчиков между различными зонами.

Каждая зона склада обозначается уникальным целым числом. Когда погрузчик перемещается из одной зоны в другую, система регистрирует номер новой зоны, в которую он въехал. В результате движение каждого погрузчика представлено в виде последовательности чисел.

Инженеры завода считают, что наиболее эффективный путь, который может совершить погрузчик, — это поездка из некоторой начальной зоны в конечную, а затем возвращение по тому же маршруту обратно. Такая последовательность перемещений формирует так называемый «идеальный маршрут».

Вам необходимо найти длину самого длинного «идеального маршрута» в записи перемещений погрузчика.

## Формат ввода
Первая строка содержит одно целое число n (1 ≤ n ≤ 10^4) — количество записей о перемещениях погрузчика.

Вторая строка содержит n целых чисел a₁, a₂, ..., aₙ (1 ≤ aᵢ ≤ 10^9) — последовательность зон, через которые проехал погрузчик.

## Формат вывода
Выведите одно целое число — длину самого длинного «идеального маршрута» в записи перемещений. Если такого маршрута не существует, выведите 0.

## Пример 1
### Ввод
7

1 2 3 4 3 2 1

### Вывод
7

## Пример 2
### Ввод
5

1 2 3 4 5

### Вывод
0

## Пример 3
### Ввод
10

1 2 3 4 5 5 4 3 2 1

### Вывод
10

## Пример 4
### Ввод	
6

1 2 3 1 2 3

### Вывод
0

## Пример 5
### Ввод
3
1 1 2

### Вывод
2