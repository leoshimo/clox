#include "memory.h"
#include "object.h"
#include "vm.h"
#include <stdlib.h>

void* reallocate(void* pointer, size_t oldSize, size_t newSize) {
  if (newSize == 0) {
    free(pointer);
    return NULL;
  }

  void* result = realloc(pointer, newSize);
  if (result == NULL)
    exit(1);
  return result;
}

static void freeObject(Obj* obj) {
  switch (obj->type) {
    case OBJ_STRING: {
      ObjString* string = (ObjString*)obj;
      FREE_ARRAY(char, string->chars, string->length + 1);
      FREE(ObjString, obj);
      break;
    }
  }
}

void freeObjects() {
  Obj* obj = vm.objects;
  while (obj != NULL) {
    Obj* next = obj->next;
    freeObject(obj);
    obj = next;
  }
}
