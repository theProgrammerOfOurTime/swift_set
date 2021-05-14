	Шаблонный класс для хранения целочисленных числел.
Данные хранятся в виде массива односвязных списков. При добавление нового элемента хэш-функция высчитывает индекс(хэш), под которым будет храниться элемент. Такая система обеспечивает быстрый поиск, вставку и удаление элементов, чтобы найти произвольный элемент надо просто посчитать его индекс и проверить его наличие под ним. Также класс способен самостоятельно расширяться и сжиматься при недостатке или избытке индексов хранения. Главное преимущество этого класса перед встроенным unordered_set (по идее которого писался этот класс) в том, что он быстрее в среднем в 6 раз. Коллизии возникают, но на один элемент их не так много. Сжимающие отображение хэш-функции при значениях ~0-1000, до конца не соответствует свойству таких функций: значение 99 - будет лежать под индексом 100, значение 100 – под индексом 101, числа в данном диапазоне имеют i = N + 1, где i - индекс, N - число. При значениях, не входящих в данный промежуток, числа минимально различные лежат под более "далёкими" индексами и наоборот. Помимо этого, недостатком хэш-функции является относительно плохая плотность укладки элементов. В перспективе: перегрузка хэш-функции, чтобы класс мог обрабатывать и хранить иных данных кроме целочисленных чисел, и, конечно, добавление класса итератора, чтобы класс хранения можно было использовать в стандартных алгоритмах stl.
