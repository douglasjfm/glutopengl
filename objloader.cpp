#include "objloader.h"

lint* insereli(lint *head, int x)
{
    lint* p = head;
    if (!p)
    {
        head = (lint*) calloc(1, sizeof(lint));
        head->i = x;
        head->px = NULL;
        return head;
    }
    while (p->px)p = p->px;

    p->px = (lint*) calloc(1, sizeof(lint));
    p->px->i = x;
    p->px->px = NULL;

    return head;
}

lfloat* inserelf(lfloat *head, float x)
{
    lfloat* p = head;
    if (!p)
    {
        head = (lfloat*) calloc(1, sizeof(lfloat));
        head->f = x;
        head->px = NULL;
        return head;
    }
    while (p->px)p = p->px;

    p->px = (lfloat*) calloc(1, sizeof(lfloat));
    p->px->f = x;
    p->px->px = NULL;

    return head;
}

void lerFace(char *linha, OBJETO *o)
{
    int x, y, z;
    char c;
    sscanf(linha,"%c %i %i %i", &c, &x, &y, &z);
    o->f = insereli(o->f, x);
    insereli(o->f, y);
    insereli(o->f, z);
}

void lerFloats(char *linha, OBJETO *o)
{
    float x, y, z;
    char str[3];
    sscanf(linha, "%s %f %f %f", str, &x, &y, &z);
    if (!str[1])
    {
        o->v = inserelf(o->v, x);
        inserelf(o->v, y);
        inserelf(o->v, z);
    }
    else if (str[1] == 't')
    {
        o->vt = inserelf(o->vt, x);
        inserelf(o->vt, y);
        inserelf(o->vt, z);
    }
    else
    {
        o->vn = inserelf(o->vn, x);
        inserelf(o->vn, y);
        inserelf(o->vn, z);
    }
}

OBJETO* loader(char* fname)
{
    FILE * file = fopen(fname, "rb");
    char linha[2048];
    char b;
    int i,fim;

    OBJETO *obj;

    obj = (OBJETO*) calloc(1,sizeof(OBJETO));
    obj->f = NULL;
    obj->v = obj->vt = obj->vn = NULL;

    if (file == NULL)
    {
        printf("arquivo invalido");
        exit(1);
    }
    i = 0;
    while (fim != EOF)
    {
        i = 0;
        while (b != '\n' && fim != EOF)
        {
            fim = fscanf(file, "%c", &b);
            linha[i] = b;
            i++;
        }
        //fscanf(file, "%c", &b);
        b = 'z';
        linha[--i] = '\0';

        if (linha[0] == '#')/* ignore comentarios */;
        else if (linha[0] == 'f' && linha[1] == ' ') lerFace(linha,obj);
        else if (
            (linha[0] == 'v' && linha[1] == 'n' && linha[2] == ' ') ||
            (linha[0] == 'v' && linha[1] == 't' && linha[2] == ' ') ||
            (linha[0] == 'v' && linha[1] == ' ')
        ) lerFloats(linha, obj);
    }

    return obj;
}

