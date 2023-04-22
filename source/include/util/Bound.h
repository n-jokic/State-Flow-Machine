// Subject:  Abstract Data Structures
// Module:   Bound
// File:     bound.h
// Date:     August 2001
// Author:   Dragan Milicev
// Contents:
//      Class templates: Bounded
//                       IteratorBounded

#ifndef _BOUND_
#define _BOUND_


/////////////////////////////////////////////////////////////////////
// class template IteratorBounded
/////////////////////////////////////////////////////////////////////

template <class T, int N>
class Bounded;

template <class T, int N>
class IteratorBounded {
public:
  IteratorBounded (const Bounded<T,N>*);
  IteratorBounded (const IteratorBounded<T,N>&);
 ~IteratorBounded ();
  IteratorBounded<T,N>& operator= (const IteratorBounded<T,N>&);
  int operator== (const IteratorBounded<T,N>&);
  int operator!= (const IteratorBounded<T,N>&);
  void reset();
  int  next ();
  void end();
  int  prev();
  int isDone() const;
  const T* currentItem() const;
private:
  const Bounded<T,N>* theSupplier;
  int cur;
};

template <class T, int N>
IteratorBounded<T,N>::IteratorBounded (const Bounded<T,N>* b)
  : theSupplier(b), cur(0) {}

template <class T, int N>
IteratorBounded<T,N>::IteratorBounded (const IteratorBounded<T,N>& r)
  : theSupplier(r.theSupplier), cur(r.cur) {}

template <class T, int N>
IteratorBounded<T,N>& IteratorBounded<T,N>::operator= (const IteratorBounded<T,N>& r) {
  theSupplier=r.theSupplier;
  cur=r.cur;
  return *this;
}

template <class T, int N>
IteratorBounded<T,N>::~IteratorBounded () {}

template <class T, int N>
int IteratorBounded<T,N>::operator== (const IteratorBounded<T,N>& r) {
  return (theSupplier==r.theSupplier)&&(cur==r.cur);
}

template <class T, int N>
int IteratorBounded<T,N>::operator!= (const IteratorBounded<T,N>& r) {
  return !(*this==r);
}

template <class T, int N>
void IteratorBounded<T,N>::reset () {
  cur=0;
}

template <class T, int N>
int IteratorBounded<T,N>::next () {
  if (!isDone()) cur++;
  return !isDone();
}

template <class T, int N>
int IteratorBounded<T,N>::isDone () const {
  return (cur>=theSupplier->length() || cur < 0);
}

template <class T, int N>
void IteratorBounded<T,N>::end () {
  cur=theSupplier->length() - 1;
}

template <class T, int N>
int IteratorBounded<T,N>::prev () {
  if (cur>=0) cur--;
  return !(cur < 0);
}

template <class T, int N>
const T* IteratorBounded<T,N>::currentItem () const {
  if (isDone()) return 0;
  else return &theSupplier->itemAt(cur);
}

/////////////////////////////////////////////////////////////////////
// class template Bounded
/////////////////////////////////////////////////////////////////////

template <class T, int N>
class Bounded {
public:
  Bounded ();
  Bounded (const Bounded<T,N>&);
 ~Bounded ();

  Bounded<T,N>& operator= (const Bounded<T,N>&);

  IteratorBounded<T,N>* getIterator();

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
  void copy (const Bounded<T,N>&);
private:
  T dep[N];
  int size;
  IteratorBounded<T,N> internalIterator;
};

template<class T, int N>
Bounded<T,N>::Bounded () : 
	size(0),
	internalIterator(this) {}

template<class T, int N>
Bounded<T,N>::Bounded (const Bounded<T,N>& r) : 
	size(0),
	internalIterator(this)
{
  copy(r);
}

template<class T, int N>
Bounded<T,N>::~Bounded () { clear(); }

template<class T, int N>
void Bounded<T,N>::copy (const Bounded<T,N>& r) {
  size=0;
  for (int i=0; i<r.size; i++) append(r.itemAt(i));
}

template<class T, int N>
void Bounded<T,N>::clear () {
  size=0;
  internalIterator.reset();
}

template<class T, int N>
int Bounded<T,N>::isEmpty () const { return size==0; }

template<class T, int N>
int Bounded<T,N>::isFull () const { return size==N; }

template<class T, int N>
int Bounded<T,N>::length () const { return size; }

template<class T, int N>
const T& Bounded<T,N>::first () const { return itemAt(0); }

template<class T, int N>
const T& Bounded<T,N>::last () const { return itemAt(length()-1); }

template<class T, int N>
const T& Bounded<T,N>::itemAt (int at) const {
  static T except;
  if (isEmpty()) return except;  // Exception!
  if (at>=length()) at=length()-1;
  if (at<0) at=0;
  return dep[at];
}

template<class T, int N>
T& Bounded<T,N>::itemAt (int at) {
  static T except;
  if (isEmpty()) return except;  // Exception!
  if (at>=length()) at=length()-1;
  if (at<0) at=0;
  return dep[at];
}

template<class T, int N>
int Bounded<T,N>::location (const T& e) const {
  for (int i=0; i<size; i++) if (dep[i]==e) return i;
  return -1;
}

template<class T, int N>
void Bounded<T,N>::append (const T& t) {
  if (isFull()) return;
  dep[size++]=t;
}

template<class T, int N>
void Bounded<T,N>::insert (const T& t, int at) {
  if (isFull()) return;
  if ((at>size)||(at<0)) return;
  for (int i=size-1; i>=at; i--) dep[i+1]=dep[i];
  dep[at]=t;
  size++;
}

template<class T, int N>
void Bounded<T,N>::remove (int at) {
  if ((at>=size)||(at<0)) return;
  for (int i=at+1; i<size; i++) dep[i-1]=dep[i];
  size--;
}

template<class T, int N>
void Bounded<T,N>::remove (const T& t) {
  remove(location(t));
}

template<class T, int N>
Bounded<T,N>& Bounded<T,N>::operator= (const Bounded<T,N>& r) {
  clear();
  copy(r);
  return *this;
}

template <class T, int N>
IteratorBounded<T,N>* Bounded<T,N>::getIterator() {
  return &internalIterator;
}


#endif

