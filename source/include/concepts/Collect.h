// Subject:  Abstract Data Structures
// Module:   Collection
// File:     collect.h
// Date:     August 2001
// Author:   Dragan Milicev
// Contents:
//      Class templates: Collection
//                       CollectionB
//                       CollectionU
//                       IteratorCollection
//                       IteratorCollectionB
//                       IteratorCollectionU

#ifndef _COLLECT_
#define _COLLECT_

#include "bound.h"
#include "unbound.h"

/////////////////////////////////////////////////////////////////////
// class template Collection
/////////////////////////////////////////////////////////////////////

template <class T>
class IteratorCollection;

template <class T>
class Collection {
public:
  virtual ~Collection () {}

  Collection<T>& operator= (const Collection<T>&);

  virtual IteratorCollection<T>* createIterator() const =0;
  virtual IteratorCollection<T>* getIterator() = 0;

  virtual void add    (const T&) =0;
  virtual void add    (const T&, int at) =0;
  virtual void remove (const T&) =0;
  virtual void remove (int at) =0;
  virtual void clear  () =0;

  virtual int      isEmpty  () const =0;
  virtual int      isFull   () const =0;
  virtual int      length   () const =0;
  virtual int      location (const T&) const =0;

  virtual const T& itemAt(int) const =0;
  virtual T&       itemAt(int)       =0;

protected:
  void copy (const Collection<T>&);
};

/////////////////////////////////////////////////////////////////////
// class template IteratorCollection
/////////////////////////////////////////////////////////////////////

template <class T>
class IteratorCollection {
public:
  virtual ~IteratorCollection () {}

  virtual void reset() =0;
  virtual int  next () =0;
  virtual void end() = 0;
  virtual int  prev() = 0;
  virtual int  isDone() const =0;
  virtual const T* currentItem() const =0;
};

template<class T>
void Collection<T>::copy (const Collection<T>& r) {
  IteratorCollection<T>* it=r.getIterator();
  for (it->reset(); !it->isDone(); it->next())
       if (!isFull()) add(*it->currentItem());
}

template<class T>
Collection<T>& Collection<T>::operator= (const Collection<T>& r) {
  clear();
  copy(r);
  return *this;
}

/////////////////////////////////////////////////////////////////////
// class template CollectionB
/////////////////////////////////////////////////////////////////////

template <class T, int N>
class IteratorCollectionB;

template <class T, int N>
class CollectionB : public Collection<T> {
public:
  CollectionB () : myIterator(this) {}
  CollectionB (const Collection<T>&);
  virtual ~CollectionB () {}

  Collection<T>& operator= (const Collection<T>&);

  virtual IteratorCollection<T>* createIterator() const;
  virtual IteratorCollection<T>* getIterator();

  virtual void add    (const T& t)             { rep.append(t); }
  virtual void add    (const T& t, int at)     { rep.insert(t, at); }
  virtual void remove (const T& t)             { rep.remove(t); }
  virtual void remove (int at)                 { rep.remove(at); }
  virtual void clear  ()                       { rep.clear(); }

  virtual int      isEmpty  () const           { return rep.isEmpty(); }
  virtual int      isFull   () const           { return rep.isFull(); }
  virtual int      length   () const           { return rep.length(); }
  virtual int      location (const T& t) const { return rep.location(t); }

  virtual const T& itemAt(int i) const {return rep.itemAt(i);}
  virtual T&       itemAt(int i)       {return rep.itemAt(i);}

private:
  friend class IteratorCollectionB<T,N>;
  Bounded<T,N> rep;
  IteratorCollectionB<T,N> myIterator;
};

/////////////////////////////////////////////////////////////////////
// class template IteratorCollectionB
/////////////////////////////////////////////////////////////////////

template <class T, int N>
class IteratorCollectionB : public IteratorCollection<T>,
			    private IteratorBounded<T,N> {
public:
  IteratorCollectionB (const CollectionB<T,N>* c)
			       : IteratorBounded<T,N>(&c->rep) {}
  virtual ~IteratorCollectionB () {}

  virtual void reset() { IteratorBounded<T,N>::reset(); }
  virtual int  next () { return IteratorBounded<T,N>::next(); }
  virtual void end()  { IteratorBounded<T, N>::end(); }
  virtual int  prev() { return IteratorBounded<T,N>::prev(); }
  virtual int  isDone()    const { return IteratorBounded<T,N>::isDone(); }
  virtual const T* currentItem() const
			      { return IteratorBounded<T,N>::currentItem(); }

};

template<class T, int N>
CollectionB<T,N>::CollectionB (const Collection<T>& r) : myIterator(this){
  copy(r);
}

template<class T, int N>
Collection<T>& CollectionB<T,N>::operator= (const Collection<T>& r) {
  return Collection<T>::operator=(r);
}

template<class T, int N>
IteratorCollection<T>* CollectionB<T,N>::createIterator() const {
  return new IteratorCollectionB<T,N>(this);
}

template<class T, int N>
IteratorCollection<T>* CollectionB<T,N>::getIterator() {
  return &myIterator;
}

/////////////////////////////////////////////////////////////////////
// class template CollectionU
/////////////////////////////////////////////////////////////////////

template <class T>
class IteratorCollectionU;

template <class T>
class CollectionU : public Collection<T> {
public:
  CollectionU () : myIterator(this) {}
  CollectionU (const Collection<T>&);
  virtual ~CollectionU () {}

  Collection<T>& operator= (const Collection<T>&);

  virtual IteratorCollection<T>* createIterator() const;
  virtual IteratorCollection<T>* getIterator();

  virtual void add    (const T& t)             { rep.append(t); }
  virtual void add    (const T& t, int at)     { rep.insert(t, at); }
  virtual void remove (const T& t)             { rep.remove(t); }
  virtual void remove (int at)                 { rep.remove(at); }
  virtual void clear  ()                       { rep.clear(); }

  virtual int      isEmpty  () const           { return rep.isEmpty(); }
  virtual int      isFull   () const           { return rep.isFull(); }
  virtual int      length   () const           { return rep.length(); }
  virtual int      location (const T& t) const { return rep.location(t); }

  virtual const T& itemAt(int i) const {return rep.itemAt(i);}
  virtual T&       itemAt(int i)       {return rep.itemAt(i);}

private:
  friend class IteratorCollectionU<T>;
  Unbounded<T> rep;
  IteratorCollectionU<T> myIterator;
};

/////////////////////////////////////////////////////////////////////
// class template IteratorCollectionU
/////////////////////////////////////////////////////////////////////

template <class T>
class IteratorCollectionU : public IteratorCollection<T>,
			    private IteratorUnbounded<T> {
public:
  IteratorCollectionU (const CollectionU<T>* c)
			       : IteratorUnbounded<T>(&c->rep) {}

  virtual ~IteratorCollectionU () {}

  virtual void reset() { IteratorUnbounded<T>::reset(); }
  virtual int  next () { return IteratorUnbounded<T>::next(); }

  virtual void end() { IteratorUnbounded<T>::end(); }
  virtual int  prev(){ return IteratorUnbounded<T>::prev(); }

  virtual int  isDone()    const { return IteratorUnbounded<T>::isDone(); }

  virtual const T* currentItem() const
			      { return IteratorUnbounded<T>::currentItem(); }
};

template<class T>
CollectionU<T>::CollectionU (const Collection<T>& r) {
  copy(r);
}

template<class T>
Collection<T>& CollectionU<T>::operator= (const Collection<T>& r) {
  return Collection<T>::operator=(r);
}

template<class T>
IteratorCollection<T>* CollectionU<T>::createIterator() const {
  return new IteratorCollectionU<T>(this);
}

template<class T>
IteratorCollection<T>* CollectionU<T>::getIterator() {
  return &myIterator;
}

#endif

