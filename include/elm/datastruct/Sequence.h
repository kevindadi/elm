/*
 * $Id$
 * Copyright (c) 2004, Alfheim Corporation.
 *
 * sequence.h -- sequence classes interface.
 */
#ifndef ELM_DATASTRUCT_SEQUENCE_H
#define ELM_DATASTRUCT_SEQUENCE_H

namespace elm {

// Classes
template <class T> class Sequence;

// SeqIterator class
template <class T>
class SeqIteratorInst: public virtual IteratorInst<T> {
public:
	virtual bool begining(void) const = 0;
	virtual void previous(void) = 0;
	virtual void first(void) = 0;
	virtual void last(void) = 0;
};
template <class T>
class SeqIterator: public Iterator<T> {
	inline SeqIteratorInst<T> siter(void) const;
public:
	inline SeqIterator(SeqIteratorInst<T> *_iter);
	inline SeqIterator(Sequence<T> *seq);
	inline SeqIterator(Sequence<T>& seq);
	inline bool begining(void) const;
	inline void previous(void);
	inline void first(void);
	inline void last(void);	
};

// SeqEditor class
template <class T>
class SeqEditorInst: public virtual EditorInst<T> {
public:
	virtual bool begining(void) const = 0;
	virtual void previous(void) = 0;
	virtual void first(void) = 0;
	virtual void last(void) = 0;
	virtual void removeNext(void) = 0;
	virtual void removePrevious(void) = 0;
	virtual void insertAfter(const T value) = 0;
	virtual void insertBefore(const T value) = 0;
};
template <class T>
class SeqEditor: public Editor<T> {
	inline SeqEditorInst<T> *sedit(void) const;
public:
	inline SeqEditor(SeqIteratorInst<T> *_iter);
	inline SeqEditor(Sequence<T> *seq);
	inline SeqEditor(Sequence<T>& seq);
	inline bool begining(void) const;
	inline void previous(void);
	inline void first(void);
	inline void last(void);
	inline void removeNext(void);
	inline void removePrevious(void);
	inline void insertAfter(const T value);
	inline void insertBefore(const T value);
};


// Sequence class
template <class T>
class Sequence: public virtual Collection<T> {
public:
	virtual SeqIteratorInst<T> *visitSeq(void) const = 0;
	virtual SeqEditorInst<T> *editSeq(void) = 0;
	
	virtual T first(void) const = 0;
	virtual T last(void) const = 0;
	
	virtual void addHead(const T value) = 0;
	virtual void addTail(const T value) = 0;
	virtual void removeHead(void) = 0;
	virtual void removeTail(void) = 0;	
};


// SeqIterator<T> methods
template <class T> SeqIteratorInst<T> SeqIterator<T>::siter(void) const {
	return (SeqIteratorInst<T> *)iter;
}
template <class T> SeqIterator<T>::SeqIterator(SeqIteratorInst<T> *_iter)
: Iterator<T>(_iter) {
}
template <class T> SeqIterator<T>::SeqIterator(Sequence<T>& seq)
: Iterator<T>(seq.visitSeq()) {
}
template <class T> SeqIterator<T>::SeqIterator(Sequence<T> *seq)
: Iterator<T>(seq->visitSeq()) {
}
template <class T> bool SeqIterator<T>::begining(void) const {
	return siter()->begining();
}
template <class T> void SeqIterator<T>::previous(void) {
	siter()->previous();
}
template <class T> void SeqIterator<T>::first(void) {
	siter()->first();
}
template <class T> void SeqIterator<T>::last(void) {
	siter()->last();
}


// SeqEditor<T> methods
template <class T> SeqEditorInst<T> *SeqEditor<T>::sedit(void) const {
	return (SeqEditorInst<T> *)edit;
}
template <class T> SeqEditor<T>::SeqEditor(SeqIteratorInst<T> *_edit): Editor<T>(_edit) {
}
template <class T> bool SeqEditor<T>::begining(void) const {
	return sedit()->begining();
}
template <class T> void SeqEditor<T>::previous(void) {
	sedit()->previous();
}
template <class T> void SeqEditor<T>::first(void) {
	sedit()->first();
}
template <class T> void SeqEditor<T>::last(void) {
	sedit()->last();
}
template <class T> void SeqEditor<T>::removeNext(void) {
	sedit()->removeNext();
}
template <class T> void SeqEditor<T>::removePrevious(void) {
	sedit()->removePrevious();
}
template <class T> void SeqEditor<T>::insertAfter(const T value) {
	sedit()->insertAfter(value);
}
template <class T> void SeqEditor<T>::insertBefore(const T value) {
	sedit()->insertBefore(value);
}

};	// namespace elm

#endif	// ELM_SEQUENCE_H
