
#include "doctest.h"
#include "sources/MagicalContainer.hpp"


using namespace ariel;


void printVector(const std::vector<int>& vec)
{
    std::cout << "[";
    for (size_t i = 0; i < vec.size(); ++i)
    {
        std::cout << vec[i];
        if (i != vec.size() - 1)
        {
            std::cout << ", ";
        }
    }
    std::cout << "]" << std::endl;
}



TEST_CASE("Test MagicalContainer")
{
    // Create an instance of MagicalContainer
    ariel::MagicalContainer container;
    SUBCASE("Test adding elements")
    {
        CHECK(container.size() == 0);

        container.addElement(5);
        CHECK(container.size() == 1);

        container.addElement(3);
        CHECK(container.size() == 2);

        container.addElement(7);
        CHECK(container.size() == 3);

        container.addElement(2);
        CHECK(container.size() == 4);
    }

    SUBCASE("Test removing elements")
    {   
        container.addElement(5);
        container.addElement(3);
        container.addElement(7);
        container.addElement(2);
        container.removeElement(3);
        // Check the size of the container after removal
        CHECK(container.size() == 3);
        container.removeElement(2);
        CHECK(container.size() == 2);
    }

    SUBCASE("Test iterating over the ascending order")
    {
        container.addElement(17);
        container.addElement(2);
        container.addElement(25);
        container.addElement(9);
        container.addElement(3);

        std::vector<int> expected = {2, 3, 9, 17, 25};
        std::vector<int> result;
        MagicalContainer::AscendingIterator ascending(container);
        for (const auto& element : ascending)
        {
            result.push_back(element);
        }
        for (size_t i = 0; i < expected.size(); i++)
        {
            CHECK(result[i] == expected[i]);
        }
        
        // Check if the iteration produces the expected result
        CHECK(result == expected);
    }

    SUBCASE("Test iterating over the side cross order"){
        container.addElement(17);
        container.addElement(2);
        container.addElement(25);
        container.addElement(9);
        container.addElement(3);
        MagicalContainer::SideCrossIterator crossIter(container);
        std::cout << std::endl;
        std::vector<int> expected = {2, 25, 3, 17, 9};
        std::vector<int> result;
        MagicalContainer::SideCrossIterator sidecross(container);
        for (const auto& element : sidecross)
        {
            result.push_back(element);
        }
        for (size_t i = 0; i < expected.size(); i++)
        {
            CHECK(result[i] == expected[i]);
        }
        // Check if the iteration produces the expected result
        
    }

    SUBCASE("Test iterating over the prime numbers")
    {
        container.addElement(17);
        container.addElement(2);
        container.addElement(25);
        container.addElement(9);
        container.addElement(3);
        std::vector<int> expected = {2, 3, 17};
        std::vector<int> result;

        MagicalContainer::PrimeIterator prime(container);
        

        for (const auto& element : prime)
        {
            result.push_back(element);
        }

        // Check if the iteration produces the expected result
        CHECK(result == expected);
    }

    SUBCASE("Test ascending Iterating when added numbers in mid-iterating"){
        container.addElement(17);
        container.addElement(2);
        container.addElement(25);
        container.addElement(9);
        container.addElement(3);

        std::vector<int> expected = {2, 3, 9, 17, 25, 30};
        std::vector<int> result;
        MagicalContainer::AscendingIterator ascending(container);
        
        result.push_back(*ascending);

        ++ascending;
        result.push_back(*ascending);
        ++ascending;
        // problem ascending index dont grow
        container.addElement(1);
        container.addElement(30);
        while(ascending != ascending.end())
        {
            const auto& element = *ascending;
            result.push_back(element);
            ++ascending;
        }

        // Check if the iteration produces the expected result
        CHECK(result == expected);
    }

    SUBCASE("Test ascending Iterating when removing numbers in mid-iterating"){
        container.addElement(17);
        container.addElement(2);
        container.addElement(25);
        container.addElement(9);
        container.addElement(3);

        std::vector<int> expected = {2, 9, 25};
        std::vector<int> result;
        MagicalContainer::AscendingIterator ascending(container);
        
        for (size_t i = 0; i < 3; i++)
        {
            result.push_back(*ascending);
            ++ascending;
        }
        
        // problem ascending index dont grow
        container.removeElement(3);
        container.removeElement(17);
        while(ascending != ascending.end())
        {
            const auto& element = *ascending;
            result.push_back(element);
            ++ascending;
        }

        // Check if the iteration produces the expected result
        std::cout << " "<<std::endl;
        CHECK(result == expected);
    }


SUBCASE("Test sidecross Iterating when added numbers in mid-iterating"){
        container.addElement(17);
        container.addElement(2);
        container.addElement(25);
        container.addElement(9);
        container.addElement(3);

        std::vector<int> expected = {2, 3, 9, 17, 25, 30};
        std::vector<int> result;
        MagicalContainer::SideCrossIterator sidecross(container);
        
        result.push_back(*sidecross);

        ++sidecross;
        result.push_back(*sidecross);
        ++sidecross;
        // problem ascending index dont grow
        container.addElement(1);
        container.addElement(30);
        while(sidecross != sidecross.end())
        {
            const auto& element = *sidecross;
            result.push_back(element);
            ++sidecross;
        }

        // Check if the iteration produces the expected result
        CHECK(result == expected);
    }

    SUBCASE("Test ascending Iterating when removing numbers in mid-iterating"){
        container.addElement(17);
        container.addElement(2);
        container.addElement(25);
        container.addElement(9);
        container.addElement(3);

        std::vector<int> expected = {2, 9, 25};
        std::vector<int> result;
        MagicalContainer::SideCrossIterator sidecross(container);
        
        for (size_t i = 0; i < 3; i++)
        {
            result.push_back(*sidecross);
            ++sidecross;
        }
        
        // problem ascending index dont grow
        container.removeElement(3);
        container.removeElement(17);
        while(sidecross != sidecross.end())
        {
            const auto& element = *sidecross;
            result.push_back(element);
            ++sidecross;
        }

        // Check if the iteration produces the expected result
        std::cout << " "<<std::endl;
        CHECK(result == expected);
    }


}

