#include <iostream>
#include "swift_set.cpp"

using namespace std;

int main()
{
	swift_set <int> s;
	srand(time(NULL));

	cout << s.empty() << " " << s.size() << " " << s.capacity() << endl << endl;

	for (int i = 0; i < 100000; i++)
	{
		s.insert(rand());
	}
	cout << s.empty() << " " << s.size() << " " << s.capacity() << endl << endl;

	cout << "first item: " << s.pop() << endl;
	cout << s.empty() << " " << s.size() << " " << s.capacity() << endl << endl;

	int number;
	cin >> number;
	if (s.find(number))
	{
		s.erase(number);
		cout << "Item deleted " << endl << s.empty() << " " << s.size() << " " << s.capacity() << endl << endl;
	}
	else
	{
		cout << "Item not find" << endl << endl;
	}

	s.reserve(s.capacity() * 2);
	cout << s.empty() << " " << s.size() << " " << s.capacity() << endl << endl;

	s.resize(s.capacity());
	cout << s.empty() << " " << s.size() << " " << s.capacity() << endl << endl;

	s.clear();
	cout << s.empty() << " " << s.size() << " " << s.capacity() << endl << endl;
	
	for (int i = 0; i < 100; i++)
	{
		s.insert(rand());
	}
	s.print();
	cout << endl << s.empty() << " " << s.size() << " " << s.capacity() << endl << endl;

	return 0;
}