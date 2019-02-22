#include <stdio.h>
#include <stdlib.h>

void char_ctor(void *obj)
{
	*(char *)obj = '\0';
}

void char_dtor(void *obj)
{
	// Nothing to do
}

void *new_object(size_t size, void (*ctor)(void *))
{
	char *block = malloc(size);
	memset(block, 0, size);
	ctor(block);
	return block;
}

void delete_object(void *ptr, void (*dtor)(void *))
{
	if (ptr == NULL)
		return;

	dtor(ptr);
	free(ptr);
}

void *new_array(size_t size, size_t count, void (*ctor)(void *))
{
	int i;
	char *p;
	char *block;
	char *first;

	// Allocate [count][0][1][2]...
	block = malloc(sizeof(size_t) + size * count);
	first = block + sizeof(size_t);

	// Store count
	*(size_t *)block = count;

	p = first;
	for (i = 0; i < count; i++)
	{
		ctor(p);
		p += size;
	}

	return first;
}

void delete_array(void *ptr, size_t size, void (*dtor)(void *))
{
	int i;
	char *p;
	char *block;
	char *first;
	size_t count;

	if (ptr == NULL)
		return;

	block = ((size_t *)ptr) - 1;
	first = ptr;
	count = *block;

	p = first;
	for (i = 0; i < count; i++)
	{
		dtor(p);
		p += size;
	}

	free(block);
}

#define NEW_ARRAY(type, count) \
	(type *)new_array(sizeof(type), count, type##_ctor)

#define DELETE_ARRAY(type, array) \
	delete_array(array, sizeof(type), type##_dtor)


#define NEW(type) \
	(type *)new_object(sizeof(type), type##_ctor)

#define DELETE(obj, type) \
	delete_object(obj, type##_dtor)


typedef struct BaseClassT
{
	int size;
	char *data;
} BaseClass;

void BaseClass_ctor(BaseClass *_this)
{
	_this->size = 0;

	_this->data = NEW_ARRAY(char, 1);
	_this->data[0] = '\0';
}

void BaseClass_dtor(BaseClass *_this)
{
	DELETE_ARRAY(char, _this->data);
}

void BaseClass_Add(BaseClass *_this, char c)
{
	char *tmp = NEW_ARRAY(char, _this->size + 2);
	memcpy(tmp, _this->data, _this->size);
	tmp[_this->size] = c;
	tmp[_this->size + 1] = '\0';
	_this->size += 1;
	_this->data = tmp;
}

int BaseClass_Size(BaseClass *_this)
{
	return _this->size;
}

char *BaseClass_Str(BaseClass *_this)
{
	return _this->data;
}

int main()
{
	BaseClass cls;
	BaseClass_ctor(&cls);

	printf("size=%d\n", BaseClass_Size(&cls));

	BaseClass_Add(&cls, 'A');

	printf("size=%d\n", BaseClass_Size(&cls));
	printf("str=%s\n", BaseClass_Str(&cls));
	
	{
	BaseClass *ptr = NEW(BaseClass);

	printf("size=%d\n", BaseClass_Size(ptr));

	BaseClass_Add(ptr, 'B');

	printf("size=%d\n", BaseClass_Size(ptr));
	printf("str=%s\n", BaseClass_Str(ptr));

	DELETE(ptr, BaseClass);
	}

	BaseClass_dtor(&cls);

	return 0;	
}
