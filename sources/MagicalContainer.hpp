//
// Created by Liavm on 29/05/2023.
//

#ifndef MAGICALCONTAINER_HPP
#define MAGICALCONTAINER_HPP
#include <vector>
#include <algorithm>
#include <cmath>
#include "data_struct.hpp"

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
    for (int i = 5; i * i <= element; i += 6)
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
        void addElement(int element)
        {
            ascendingVector.insert(element);
            if (isPrime(element))
            {
                int *primePtr = new int(element);

                auto primeInsertionPoint = std::upper_bound(primePointers.begin(), primePointers.end(), primePtr,
                                                            [](const int *a, const int *b)
                                                            { return *a < *b; });
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
            Node current;

        public:
            AscendingIterator(MagicalContainer &cont) : container(cont), current(*cont.ascendingVector.getHead())
            {
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
                if (current.next != NULL)
                {
                    current = *current.next;
                }
                else
                    current = NULL;
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
        };

        class SideCrossIterator
        {
        private:
            MagicalContainer &container;
            Node *tail;
            Node *head;
            bool odd = false;

        public:
            SideCrossIterator(MagicalContainer &cont, size_t index = 0) : container(cont),
                                                                          tail(cont.ascendingVector.getLast()),
                                                                          head(cont.ascendingVector.getHead()) {}

            SideCrossIterator(const SideCrossIterator &other) : container(other.container), head(other.head), tail(other.tail) {}

            ~SideCrossIterator() {}

            SideCrossIterator &operator=(const SideCrossIterator &other)
            {
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

            bool operator!=(const SideCrossIterator &other) const
            {
                return !(*this == other);
            }

            int operator*() const
            {
                if (head == nullptr && tail == nullptr)
                {
                    return -1;
                }
                if (odd)
                {
                    return tail->data;
                }
                return head->data;
            }

            SideCrossIterator &operator++()
            {

                if (odd)
                {
                    this->tail = this->tail->back;
                    odd = false;
                }
                else
                {
                    this->head = this->head->next;
                    odd = true;
                }

                if ((this->container.size() % 2 == 0 && head == this->container.middle->back && tail == this->container.middle) ||
                    (this->container.size() % 2 == 1 && head == this->container.middle->next && tail == this->container.middle))
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
        };
    };
}

#endif //MAGICALCONTAINER_HPP
