// Copyright 2022 NNTU-CS
#ifndef INCLUDE_TPQUEUE_H_
#define INCLUDE_TPQUEUE_H_
#include <iostream>
#include <string>
template<typename T>
class TPQueue {
 private:
    struct ITEM {
        T value;
        ITEM *nxt;
        ITEM *prev;
    };

 public:
  T pop();
  void push(const T& value);
  TPQueue():hd(nullptr), tl(nullptr) {}
  ~TPQueue() {
      while (hd)
      pop();
  }

 private:
    TPQueue::ITEM *create(const T& value) {
        ITEM *item = new ITEM;
        item->value = value;
        item->nxt = nullptr;
        item->prev = nullptr;
        return item;
    }
    ITEM *tl;
    ITEM *hd;
};
template<typename T>
void TPQueue<T>::push(const T& value) {
  ITEM *tmp = hd;
  ITEM *item = create(value);
  while (tmp && tmp->value.prior >= value.prior)
  tmp = tmp->nxt;
  if (!tmp && hd) {
      tl->nxt = item;
      tl->nxt->prev = tl;
      tl = item;
  } else if (!tmp && !hd) {
      hd = tl = item;
  } else if (!tmp->prev) {
      tmp->prev = item;
      item->nxt = tmp;
      hd = item;
  } else {
       tmp->prev->nxt = item;
       item->prev = tmp->prev;
       item->nxt = tmp;
       tmp->prev = item;
  }
}
template<typename T>
T TPQueue<T>::pop() {
    if (hd) {
        ITEM *tmp = hd->nxt;
        if (tmp)
          tmp->prev = nullptr;
        T value = hd->value;
        delete hd;
        if (!hd) tl = nullptr;
        hd = tmp;
        return value;
    } else {
        throw std::string("empty!");
    }
}
struct SYM {
  char ch;
  int prior;
};
#endif  // INCLUDE_TPQUEUE_H_
