// Subject:  Abstract Data Structures
// Module:   Unbound
// File:     unbound.h
// Date:     August 2001
// Author:   Dragan Milicev
// Contents:
//      Class templates: Unbounded
//                       IteratorUnbounded

#ifndef _UNBOUND_
#define _UNBOUND_

template <class T>
struct ELement {
  T t;
  ELement<T> *prev, *next;
  ELement (const T&);
  ELement (const T&, ELement<T>* next);
  ELement (const T&, ELement<T>* prev, ELement<T>* next);
};

template<class T>
ELement<T>::ELement (const T& e) : t(e), prev(0), next(0) {}

template<class T>
ELement<T>::ELement (const T& e, ELement<T> *n)
    : t(e), prev(0), next(n) {
  if (n!=0) n->prev=this;
}

template<class T>
ELement<T>::ELement (const T& e, ELement<T> *p, ELement<T> *n)
    : t(e), prev(p), next(n) {
  if (n!=0) n->prev=this;
  if (p!=0) p->next=this;
}

/////////////////////////////////////////////////////////////////////
// class template IteratorUnbounded
/////////////////////////////////////////////////////////////////////

template <class T>
class Unbounded;

template <class T>
class IteratorUnbounded {
public:
  IteratorUnbounded (const Unbounded<T>*);
  IteratorUnbounded (const IteratorUnbounded<T>&);
 ~IteratorUnbounded ();

  IteratorUnbounded<T>& operator= (const IteratorUnbounded<T>&);
  int operator== (const IteratorUnbounded<T>&);
  int operator!= (const IteratorUnbounded<T>&);

  void reset();
  int  next ();
  void end();
  int  prev();
  int  isDone() const;
  const T* currentItem() const;

private:
  const Unbounded<T>* theSupplier;
  ELement<T>* cur;
};

template <class T>
IteratorUnbounded<T>::IteratorUnbounded (const Unbounded<T>* ub) :
  theSupplier(ub), 
  cur(theSupplier->head){}

template <class T>
IteratorUnbounded<T>::IteratorUnbounded (const IteratorUnbounded<T>& r) : 
  theSupplier(r.theSupplier),
  cur(r.cur){}

template <class T>
IteratorUnbounded<T>& IteratorUnbounded<T>::operator= (const IteratorUnbounded<T>& r) {
  theSupplier=r.theSupplier;
  cur=r.cur;
  return *this;
}

template <class T>
IteratorUnbounded<T>::~IteratorUnbounded () {}

template <class T>
int IteratorUnbounded<T>::operator== (const IteratorUnbounded<T>& r) {
  return (theSupplier==r.theSupplier)&&(cur==r.cur);
}

template <class T>
int IteratorUnbounded<T>::operator!= (const IteratorUnbounded<T>& r) {
  return !(*this==r);
}

template <class T>
void IteratorUnbounded<T>::reset () {
  cur=theSupplier->head;
}

template <class T>
int IteratorUnbounded<T>::next () {
  if (cur!=0) cur=cur->next;
  return !isDone();
}

template <class T>
int IteratorUnbounded<T>::isDone () const {
  return (cur==0);
}

template <class T>
void IteratorUnbounded<T>::end () {
  cur=theSupplier->head;
  while (cur && cur->next) cur=cur->next;
}

template <class T>
int IteratorUnbounded<T>::prev () {
  if (cur!=0) cur=cur->prev;
  return !isDone();
}

template <class T>
const T* IteratorUnbounded<T>::currentItem () const {
  if (isDone()) return 0;
  else return &(cur->t);
}

/////////////////////////////////////////////////////////////////////
// class template Unbounded
/////////////////////////////////////////////////////////////////////

template <class T>
class Unbounded {
public:
  Unbounded ();
  Unbounded (const Unbounded<T>&);
 ~Unbounded ();

  Unbounded<T>& operator= (const Unbounded<T>&);

  IteratorUnbounded<T>* getIterator();

  void append (const T&);
  void insert (const T&, int at=0);
  void remove (const T&);
  void remove (int at=0);
  void clear  ();

  int      isEmpty  () const;
  int      isFull   () const;
  int      length   () const;
  const T& first    () const;
  const T& last     () const;
  const T& itemAt   (int at) const;
  T&       itemAt   (int at);
  int      location (const T&) const;

protected:
  void copy (const Unbounded<T>&);
  void remove (ELement<T>*);

private:
  friend class  IteratorUnbounded<T>;
  friend struct ELement<T>;

  ELement<T>* head;
  int size;
  IteratorUnbounded<T> internalIterator;
};

template<class T>
Unbounded<T>::Unbounded () : 
	size(0), 
	head(0),
	internalIterator(this) {}

template<class T>
Unbounded<T>::Unbounded (const Unbounded<T>& r) : 
	size(0),
	head(0),
	internalIterator(this) 
{
  copy(r);
}

template<class T>
Unbounded<T>::~Unbounded () { clear(); }

template<class T>
void Unbounded<T>::remove (ELement<T>* e) {
  if (e==0) return;
  if (e->next!=0) e->next->prev=e->prev;
  if (e->prev!=0) e->prev->next=e->next;
  else head=e->next;
  delete e;
  size--;
}

template<class T>
void Unbounded<T>::copy (const Unbounded<T>& r) {
  size=0;
  for (ELement<T>* cur=r.head; cur!=0; cur=cur->next) append(cur->t);
}

template<class T>
void Unbounded<T>::clear () {
  for (ELement<T> *cur=head, *temp=0; cur!=0; cur=temp) {
    temp=cur->next;
    delete cur;
  }
  head=0;
  size=0;
}

template<class T>
int Unbounded<T>::isEmpty () const { return size==0; }

template<class T>
int Unbounded<T>::isFull () const { return 0; }


template<class T>
int Unbounded<T>::length () const { return size; }

template<class T>
const T& Unbounded<T>::first () const { return itemAt(0); }

template<class T>
const T& Unbounded<T>::last () const { return itemAt(length()-1); }

template<class T>
const T& Unbounded<T>::itemAt (int at) const {
  static T except;
  if (isEmpty()) return except;  // Exception!
  if (at>=length()) at=length()-1;
  if (at<0) at=0;
  int i=0; ELement<T> *cur;
  for (cur=head; i<at; cur=cur->next, i++);
  return cur->t;
}

template<class T>
T& Unbounded<T>::itemAt (int at) {
  static T except;
  if (isEmpty()) return except;  // Exception!
  if (at>=length()) at=length()-1;
  if (at<0) at=0;
  int i=0; ELement<T> *cur;
  for (cur=head; i<at; cur=cur->next, i++);
  return cur->t;
}

template<class T>
int Unbounded<T>::location (const T& e) const {
  int i=0; ELement<T> *cur;
  for (cur=head; cur!=0; cur=cur->next, i++)
	if (cur->t==e) return i;
  return -1;
}

template<class T>
void Unbounded<T>::append (const T& t) {
  if (head==0) head=new ELement<T>(t);
  else {
	ELement<T> *cur;
    for (cur=head; cur->next!=0; cur=cur->next);
    new ELement<T>(t,cur,0);
  }
  size++;
}

template<class T>
void Unbounded<T>::insert (const T& t, int at) {
  if ((at>size)||(at<0)) return;
  if (at==0) head=new ELement<T>(t,head);
  else if (at==size) { append(t); return; }
  else {
    int i=0; ELement<T> *cur;
    for (cur=head; i<at; cur=cur->next, i++);
    new ELement<T>(t,cur->prev,cur);
  }
  size++;
}

template<class T>
void Unbounded<T>::remove (int at) {
  if ((at>=size)||(at<0)) return;
  int i=0; ELement<T> *cur;
  for (cur=head; i<at; cur=cur->next, i++);
  remove(cur);
}

template<class T>
void Unbounded<T>::remove (const T& t) {
  remove(location(t));
}

template<class T>
Unbounded<T>& Unbounded<T>::operator= (const Unbounded<T>& r) {
  clear();
  copy(r);
  return *this;
}

template <class T>
IteratorUnbounded<T>* Unbounded<T>::getIterator() {
  return &internalIterator;
}

#endif

