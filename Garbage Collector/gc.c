#include <stdio.h>
#include <stdlib.h>

#define STAK_MAX 256
#define INIT_MAX 8

typedef enum
{
	OBJ_INT,
	OBJ_PAIR
}ObjectType;

typedef struct sObject
{
	ObjectType type;
	unsigned char marked;

	//the next object in the linked list of heap allocated objects
	struct sObject* next;

	union
	{
		int value;

		struct
		{
			struct sObject* head;
			struct sObject* tail;
		};
	};
}Object;

typedef struct
{
	Object* stack[STAK_MAX];
	int stackSize;

	//the first object in the linked list of all objects on the heap
	Object* firstObject;

	//the total number of currently allocated objects
	int numObjects;

	//the number of objects required to trigger a GC
	int maxObjects;
}VM;

void assert(int condition, const char* message)
{
	if (!condition)
	{
		print("%s\n", message);
		exit(1);
	}
}

VM* newVM()
{
	VM* vm = malloc(sizeof(VM));
	vm->stackSize = 0;
	vm->firstObject = NULL;
	vm->numObjects = 0;
	vm->maxObjects = INIT_MAX;

	return vm;
}


void push(VM* vm, Object* value)
{
	assert(vm->stackSize < STAK_MAX, "stack overflow");
	vm->stack[vm->stackSize++] = value;
}

Object* pop(VM* vm)
{
	assert(vm->stackSize > 0, "stack underflow");
	return vm->stack[--vm->stackSize];
}

void mark(Object* object)
{
	//if already marked, we're done. Check this first to avoid recursing
	if (object->marked) return;

	object->marked = 1;

	if (object->type == OBJ_PAIR)
	{
		mark(object->head);
		mark(object->tail);
	}
}

print 9hfasdj