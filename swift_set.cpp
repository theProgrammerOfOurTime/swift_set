#pragma once
#include <iostream>

template<class Item>
class swift_set
{
private:
	template<class Item>
	struct List
	{
		Item item;
		List* next;
		bool state;
		List(Item item, List* next)
		{
			this->item = item;
			this->next = next;
			state = true;
		}
		List()
		{
			item = 0;
			next = nullptr;
			state = false;
		}
	};
	int maxNumberOfItem = 100;
	int numberOfItems = 0;
	List <Item>* listItems;
	void rehash(bool);
	int hash_function(Item);
	void printItemsNode(List <Item>*);
public:
	swift_set()
	{
		listItems = new List <Item>[maxNumberOfItem];
	}
	swift_set(int maxNumberOfItem)
	{
		this->maxNumberOfItem = 2 * maxNumberOfItem;
		listItems = new List <Item>[this->maxNumberOfItem];
	}
	~swift_set()
	{
		delete listItems;
	}
	int size();
	bool find(Item);
	void insert(Item);
	void erase(Item);
	void print();
	bool empty();
	void clear();
	Item pop();
	int capacity();
	void resize(int);
	void reserve(int);
};

//резервирует память и сохраняет все элементы
template <class Item>
void swift_set<Item>::reserve(int maxNumberOfItem)
{
	if (maxNumberOfItem < this->maxNumberOfItem) { return; }
	int prevMaxNumberOfItem = this->maxNumberOfItem;
	this->maxNumberOfItem = maxNumberOfItem;
	List <Item>* prevListItems = listItems;
	listItems = new List <Item>[maxNumberOfItem];
	for (int i = 0; i < prevMaxNumberOfItem; i++)
	{
		if (prevListItems[i].state == true)
		{
			insert(prevListItems[i].item);
			numberOfItems--;
			List <Item>* linkList = prevListItems[i].next;
			while (linkList != nullptr)
			{
				insert(linkList->item);
				numberOfItems--;
				linkList = linkList->next;
			}
		}
	}
	delete prevListItems;
	return;
}

//реинициализирует память
template <class Item>
void swift_set<Item>::resize(int maxNumberOfItem)
{
	delete listItems;
	this->maxNumberOfItem = maxNumberOfItem;
	numberOfItems = 0;
	listItems = new List <Item>[maxNumberOfItem];
	return;
}

//возвращает количество зарезервированной памяти
template <class Item>
int swift_set<Item>::capacity()
{
	return maxNumberOfItem;
}

//удаляет первый элемент в списке и возвращает его
template <class Item>
Item swift_set<Item>::pop()
{
	Item result = 0;
	for (int i = 0; i < maxNumberOfItem; i++)
	{
		if (listItems[i].state == true)
		{
			result = listItems[i].item;
			erase(listItems[i].item);
			break;
		}
	}
	return result;
}

//удаляет все элементы и резервирует новую память
template <class Item>
void swift_set<Item>::clear()
{
	delete listItems;
	maxNumberOfItem = 100;
	numberOfItems = 0;
	listItems = new List <Item>[maxNumberOfItem];
}

//проверка на наличие элементов
template <class Item>
bool swift_set<Item>::empty()
{
	return numberOfItems == 0;
}

//выводит сначала номер узла, а затем все элементы, хранящиеся в нем
template <class Item>
void swift_set<Item>::print()
{
	for (int i = 0; i < maxNumberOfItem; i++)
	{
		if (listItems[i].state == true)
		{
			std::cout << i << " - ";
			printItemsNode(&listItems[i]);
			std::cout << std::endl;
		}
	}
}

//увеличивает или уменьшает значения множества с сохранением элементов
template <class Item>
void swift_set<Item>::rehash(bool flag)
{
	int prevMaxNumberOfItem = maxNumberOfItem;
	(flag == true) ? maxNumberOfItem *= 2 : maxNumberOfItem /= 2;
	List <Item>* prevListItems = listItems;
	listItems = new List <Item>[maxNumberOfItem];
	for (int i = 0; i < prevMaxNumberOfItem; i++)
	{
		if (prevListItems[i].state == true)
		{
			insert(prevListItems[i].item);
			numberOfItems--;
			List <Item>* linkList = prevListItems[i].next;
			while (linkList != nullptr)
			{
				insert(linkList->item);
				numberOfItems--;
				linkList = linkList->next;
			}
		}
	}
	delete prevListItems;
	return;
}

//хэш-функция для целых чисел
template <class Item>
int swift_set<Item>::hash_function(Item object)
{
	object = abs(object);//уменьшает кол-во коллизий
	int hash = 1;
	while (object != 0)
	{
		hash += (object % 100) * hash;
		object = (object * 2 - object % 100) / 100;
	}
	return hash % maxNumberOfItem;
}

//распечатывает все элементы узла
template <class Item>
void swift_set<Item>::printItemsNode(List <Item>* linkList)
{
	std::cout << linkList->item << " ";
	if (linkList->next == nullptr) { return; }
	printItemsNode(linkList->next);
	return;
}

//возвращает количество на данный момент хранящихся элементов
template<class Item>
int swift_set<Item>::size()
{
	return numberOfItems;
}

//вернёт true, если в множестве есть такой эдемент
template <class Item>
bool swift_set<Item>::find(Item element)
{
	int indexItem = abs(hash_function(element));
	if (listItems[indexItem].state == true)
	{
		List <Item>* linkNode = &(listItems[indexItem]);
		do
		{
			if (linkNode->item == element) { return true; }
		} while (linkNode->next != nullptr && (linkNode = linkNode->next));
	}
	return false;
}

//добавляет новый элемент
template <class Item>
void swift_set<Item>::insert(Item element)
{
	if (find(element)) { return; }
	numberOfItems++;
	int indexItem = abs(hash_function(element));
	if (listItems[indexItem].state == false)
	{
		listItems[indexItem].state = true;
		listItems[indexItem].item = element;
	}
	else
	{
		listItems[indexItem].next = new List <Item>(element, listItems[indexItem].next);
	}
	if (numberOfItems + 10 > maxNumberOfItem) { rehash(true); }
	return;
}

//удаляет элемент
template <class Item>
void swift_set<Item>::erase(Item element)
{
	if (!(find(element))) { return; }
	numberOfItems--;
	int indexItem = abs(hash_function(element));
	List <Item>* node = &(listItems[indexItem]);
	if (node->item == element)
	{
		if (node->next == nullptr) { listItems[indexItem].state = false; }
		else { listItems[indexItem] = *(node->next); }
	}
	else
	{
		do
		{
			if (node->next == nullptr)
			{
				delete node;
				break;
			}
			if (node->next->item == element)
			{
				List <Item>* tempLink = node->next;
				node->next = node->next->next;
				delete tempLink;
				break;
			}
		} while (node->next != nullptr && (node = node->next));
	}
	if (numberOfItems + 10 < maxNumberOfItem / 2 && maxNumberOfItem > 100) { rehash(false); }
}