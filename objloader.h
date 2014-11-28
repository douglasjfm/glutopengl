#ifndef OBJLOADER_H_INCLUDED
#define OBJLOADER_H_INCLUDED

#include <GL/glut.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <iostream>

using namespace std;

typedef struct lfloat
{
    float f;
    struct lfloat *px;
} lfloat;

typedef struct lint
{
    int i;
    struct lint *px;
} lint;


typedef struct OBJETO
{
    lfloat *v;
    lfloat *vt;
    lfloat *vn;
    lint *f;
} OBJETO;

lint* insereli(lint *head, int x);
lfloat* inserelf(lfloat *head, float x);
void lerFace(char *linha, OBJETO *o);
void lerFloats(char *linha, OBJETO *o);
OBJETO* loader(char* fname);

#endif // OBJLOADER_H_INCLUDED
