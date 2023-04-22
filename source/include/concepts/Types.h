#ifndef _Types_h
#define _Types_h

typedef char* String;
typedef double Time;
typedef unsigned int MEID;
typedef unsigned int ID;

#include "/Users/milos/source/repos/oop_pr/source/include/util/Collect.h"
class ModelElement;
typedef CollectionU<ModelElement*> CollectionME;
typedef IteratorCollection<ModelElement*> CollectionMEIt;

#endif