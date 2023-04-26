// Copyright 2022 NNTU-CS
#ifndef INCLUDE_TPQUEUE_H_
#define INCLUDE_TPQUEUE_H_

template<typename T>
class TPQueue {
 private:
    T* createListFromScratch(const T& element) {
        T* temp = new T;
        temp->ch = element.ch;
        temp->prior = element.prior;
        head = temp;
        tail = temp;
        return temp;
    }
    T* CreateHead(const T& element) {
        T* temp = new T;
        temp->ch = element.ch;
        temp->prior = element.prior;
        temp->next = this->head;
        this->head->previous = temp;
        head = temp;
        head->previous = nullptr;
        return temp;
    }
    T* CreateTail(const T& element) {
        T* temp = new T;
        temp->ch = element.ch;
        temp->prior = element.prior;
        temp->previous = this->tail;
        this->tail->next = temp;
        tail = temp;
        tail->next = nullptr;
        return temp;
    }
    T* CreateIntermediate(const T& element) {
        T* iterator = this->head;
        while (element.prior < iterator->prior) {
            iterator = iterator->next;
        }
        T* temp = new T;
        temp->next = iterator;
        temp->ch = element.ch;
        temp->prior = element.prior;
        iterator = iterator->previous;
        temp->previous = iterator;
        iterator->next = temp;
        iterator = iterator->next;
        iterator = iterator->next;
        iterator->previous = temp;
        return temp;
    }
    T* head;
    T* tail;

 public:
    TPQueue() :head(nullptr), tail(nullptr) {}
    T pop() {
        if (head == nullptr) {
            std::cerr << "List is empty (ERROR::POP)" << std::endl;
            return T();
        }
        T* temp = head;
        head = head->next;
        return *temp;
    }
    void push(const T& element) {
        if (!head && !tail) {
            createListFromScratch(element);
        } else {
            if (element.prior > this->head->prior) {
                T* exactComponent = CreateHead(element);
            }
            else if (element.prior <= this->head->prior) {
                if (element.prior < this->head->prior &&
                    element.prior > this->tail->prior) {
                    T* exactComponent = CreateIntermediate(element);
                } else {
                    T* exactComponent = CreateTail(element);
                }
            }
        }
    }
};

struct SYM {
  char ch;
  int prior;
  SYM* previous;
  SYM* next;
  SYM(char leadchar, int priority) :
  ch(leadchar), prior(priority), previous(nullptr), next(nullptr) {}
  SYM() :ch(0), prior(0), previous(nullptr), next(nullptr) {}
};

#endif  // INCLUDE_TPQUEUE_H_
