#include <iostream>
#include <memory>

struct BaseClass
{
	BaseClass()
		: size(0),
		  data(new char[1])
	{
		data[0] = '\0';
	}

	~BaseClass()
	{
		delete[] data;
	}

	void Add(char c)
	{
		char *tmp = new char[size + 2];
		memcpy(tmp, data, size);
		tmp[size] = c;
		tmp[size + 1] = '\0';
		size += 1;
		data = tmp;
	}

	int Size() const
	{
		return size;
	}

	const char *Str() const
	{
		return data;
	}

	int size;
	char *data;
};


int main()
{
	BaseClass cls;

	std::cout << "size=" << cls.Size() << std::endl;

	cls.Add('A');

	std::cout << "size=" << cls.Size() << std::endl;
	std::cout << "str=" << cls.Str() << std::endl;


	BaseClass *ptr = new BaseClass();

	std::cout << "size=" << ptr->Size() << std::endl;

	ptr->Add('B');
	std::cout << "size=" << ptr->Size() << std::endl;
	std::cout << "str=" << ptr->Str() << std::endl;

	delete ptr;

	return 0;	
}
