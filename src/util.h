#include "lib/tinycthread/tinycthread.h"
#include <stdint.h>
#include <stddef.h>
#include <stdarg.h>

#pragma once

#define lovrAssert(c, ...) if (!(c)) { lovrThrow(__VA_ARGS__); }
#define lovrAlloc(T, destructor) (T*) _lovrAlloc(#T, sizeof(T), destructor)

typedef struct ref {
  int count;
  const char* type;
  void (*free)(void*);
} Ref;

typedef struct {
  float r, g, b, a;
} Color;

typedef void (*lovrErrorHandler)(void* userdata, const char* format, va_list args);
extern _Thread_local lovrErrorHandler lovrErrorCallback;
extern _Thread_local void* lovrErrorUserdata;

void lovrSetErrorCallback(lovrErrorHandler callback, void* context);
void lovrThrow(const char* format, ...);
void lovrSleep(double seconds);
void* _lovrAlloc(const char* type, size_t size, void (*destructor)(void*));
void lovrRetain(void* object);
void lovrRelease(void* object);
void* lovrLoadLibrary(const char* filename);
void* lovrLoadSymbol(void* library, const char* symbol);
void lovrCloseLibrary(void* library);
size_t utf8_decode(const char *s, const char *e, unsigned *pch);
uint32_t nextPo2(uint32_t x);
