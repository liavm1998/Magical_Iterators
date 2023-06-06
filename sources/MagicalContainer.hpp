//
// Created by Liavm on 29/05/2023.
//

#ifndef MAGICALCONTAINER_HPP
#define MAGICALCONTAINER_HPP
#include <vector>
#include <algorithm>
#include <cmath>
#include "data_struct.hpp"
constexpr int five = 5;
constexpr int six = 6;

bool isPrime(int element)
{
    if (element == 2 || element == 3)
    {
        return true;
    }
    if (element % 2 == 0 || element % 3 == 0 || element <= 1)
    {
        return false;
    }
    for (int i = five; i * i <= element; i += six)
    {
        if (element % i == 0 || element % (i + 2) == 0)
        {
            return false;
        }
    }
    return true;
}

namespace ariel
{

    class MagicalContainer
    {
    private:
        LinkedList ascendingVector;
        std::vector<int *> primePointers;
        Node *middle = NULL;

    public:
        ~MagicalContainer(){
            
            middle = nullptr;
            for (auto it = primePointers.begin(); it != primePointers.end(); ++it)
            {
                delete *it;
            }
            primePointers.clear();
            
        }
        void addElement(int element)
        {
            ascendingVector.insert(element);
            if (isPrime(element))
            {
                int *primePtr = new int(element);

                auto primeInsertionPoint = std::upper_bound(primePointers.begin(), primePointers.end(), primePtr,
                                                            [](const int *num1, const int *num2)
                                                            { return *num1 < *num2; });
                primePointers.insert(primeInsertionPoint, primePtr);
            }
            this->middle = this->ascendingVector.At(this->size() / 2);
        }

        void removeElement(int element)
        {
            this->ascendingVector.removeElement(element);
            for (auto it = primePointers.begin(); it != primePointers.end(); ++it)
            {
                if (**it == element)
                {
                    delete *it;
                    primePointers.erase(it);
                    break;
                }
            }
            this->middle = this->ascendingVector.At(this->size() / 2);
        }

        size_t size() const
        {
            return ascendingVector.getSize();
        }

        class AscendingIterator
        {
        private:
            MagicalContainer &container;
            Node current=NULL;
            int index = 0;

        public:
            AscendingIterator(MagicalContainer &cont) : container(cont)
            {
                if(cont.ascendingVector.getSize() != 0){
                    this->current = *cont.ascendingVector.getHead();
                }
            }

            AscendingIterator(MagicalContainer &cont, Node cur) : container(cont), current(cur)
            {
            }

            AscendingIterator(const AscendingIterator &other) : container(other.container), current(other.current)
            {
            }

            ~AscendingIterator() {}

            AscendingIterator &operator=(const AscendingIterator &other)
            {
                if(&this->container != &other.container){
                    throw std::runtime_error("");
                }
                 
                if (this != &other)
                {
                    container = other.container;
                    current = other.current;
                }
                return *this;
            }

            bool operator==(const AscendingIterator &other) const
            {
                return &container == &other.container && current == other.current;
            }

            bool operator<(const AscendingIterator &other) const
            {
                return &container == &other.container && index < other.index;
            }
            bool operator>(const AscendingIterator &other) const
            {
                return &container == &other.container && index > other.index;
            }
            bool operator!=(const AscendingIterator &other) const
            {
                return !(*this == other);
            }

            int operator*() const
            {
                return current.data;
            }

            AscendingIterator &operator++()
            {
                if(*this == end()){
                    throw std::runtime_error("");
                }
                if (current.next != NULL)
                {
                    current = *current.next;
                    index+=1;
                }
                else
                {
                    current = NULL;
                }
                return *this;
            }

            AscendingIterator begin() const
            {
                AscendingIterator iter(container);
                return iter;
            }

            AscendingIterator end() const
            {
                AscendingIterator iter(this->container, NULL);
                //                iter.current = *this->container.ascendingVector.getLast();
                return iter;
            }

            // Move constructor
            AscendingIterator(AscendingIterator&& other)noexcept:container(other.container),index(other.index),current(other.current){};

            // Move assignment operator
            AscendingIterator& operator=(AscendingIterator&& other) noexcept{
                this->container = other.container;
                this->current = other.current;
                this->index = other.index;
                return *this;
            };


        };

        class SideCrossIterator
        {
        private:
            MagicalContainer &container;
            Node *tail;
            Node *head;
            bool odd = false;
            int index = 0;

        public:
            SideCrossIterator(MagicalContainer &cont) : container(cont),
                                                                        tail(cont.ascendingVector.getLast()),
                                                                        head(cont.ascendingVector.getHead()) {}

            SideCrossIterator(const SideCrossIterator &other) : container(other.container), head(other.head), tail(other.tail) {}

            ~SideCrossIterator() {}

            SideCrossIterator &operator=(const SideCrossIterator &other)
            {
                if(&this->container != &other.container){
                    throw std::runtime_error("");
                }
                if (this != &other)
                {
                    container = other.container;
                    head = other.head;
                    tail = other.tail;
                }
                return *this;
            }

            bool operator==(const SideCrossIterator &other) const
            {
                return &container == &other.container && head == other.head && tail == other.tail;
            }
            bool operator<(const SideCrossIterator &other) const
            {
                return &container == &other.container && this->index < other.index;
            }
            bool operator>(const SideCrossIterator &other) const
            {
                return &container == &other.container && this->index > other.index;
            }

            bool operator!=(const SideCrossIterator &other) const
            {
                return !(*this == other);
            }

            int operator*() const
            {
                if (odd && tail != nullptr)
                {
                    return tail->data;
                }
                if(head != nullptr){
                    return head->data;
                }
                // already checked for not null
             
                throw std::runtime_error("already iterated everthing");
            }

            SideCrossIterator &operator++()
            {
                
                if(*this == end()){
                    throw std::runtime_error("");
                }
                if(head == tail){
                    head = nullptr;
                    tail = nullptr;
                    return *this;
                }
                if (odd)
                {
                    this->tail = this->tail->back;
                    odd = false;
                    ++index;
                }
                else
                {
                    this->head = this->head->next;
                    odd = true;
                    ++index;

                }

                if(tail->next != nullptr && tail->next == head)
                {
                    head = nullptr;
                    tail = nullptr;
                }
                return *this;
            }

            SideCrossIterator begin() const
            {
                SideCrossIterator iter(container);
                return iter;
            }

            SideCrossIterator end() const
            {
                SideCrossIterator iter(container);
                iter.head = nullptr;
                iter.tail = nullptr;
                if (this->container.size() % 2 == 1)
                {
                    iter.odd = true;
                }
                return iter;
            }

            // tidy quit
            // Move constructor
            SideCrossIterator(SideCrossIterator&& other) noexcept:container(other.container),
                                                                  head(other.head),
                                                                  tail(other.tail),
                                                                  index(other.index),
                                                                  odd(other.odd){};

            // Move assignment operator
            SideCrossIterator& operator=(SideCrossIterator&& other) noexcept {
                this->container = other.container;
                this->index = other.index;
                this->head = other.head;
                this->tail = other.tail;
                return *this;
            };
        };

        class PrimeIterator
        {
        private:
            MagicalContainer &container;
            size_t currentIndex;

        public:
            PrimeIterator(MagicalContainer &cont, size_t index = 0) : container(cont), currentIndex(index) {}

            PrimeIterator(const PrimeIterator &other) : container(other.container), currentIndex(other.currentIndex) {}

            ~PrimeIterator() {}

            PrimeIterator &operator=(const PrimeIterator &other)
            {
                if(&this->container != &other.container){
                    throw std::runtime_error("");
                }
                if (this != &other)
                {
                    container = other.container;
                    currentIndex = other.currentIndex;
                }
                return *this;
            }

            bool operator==(const PrimeIterator &other) const
            {
                return &container == &other.container && currentIndex == other.currentIndex;
            }

            bool operator>(const PrimeIterator &other) const
            {
                return &container == &other.container && currentIndex > other.currentIndex;
            }

            bool operator<(const PrimeIterator &other) const
            {
                return &container == &other.container && currentIndex < other.currentIndex;
            }

            bool operator!=(const PrimeIterator &other) const
            {
                return !(*this == other);
            }

            int operator*() const
            {
                return *this->container.primePointers[currentIndex];
            }

            PrimeIterator &operator++()
            {
                if(*this == end()){
                    throw std::runtime_error("");
                }
                ++currentIndex;
                return *this;
            }

            PrimeIterator begin() const
            {
                PrimeIterator iter(container);
                return iter;
            }

            PrimeIterator end() const
            {
                PrimeIterator iter(container);
                iter.currentIndex = this->container.primePointers.size();
                return iter;
            }

            // tidy quit
            // Move constructor
            PrimeIterator(PrimeIterator&& other) noexcept:container(other.container), currentIndex(other.currentIndex){};

            // Move assignment operator
            PrimeIterator& operator=(PrimeIterator&& other) noexcept {
                this->container = other.container;
                this->currentIndex = other.currentIndex;
                return *this;
            };
        };
    };
}

#endif //MAGICALCONTAINER_HPP
