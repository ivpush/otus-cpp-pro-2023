// OTUS C++ developer Pro Course
// homework #3
// Allocators - mine_allocator
//

#ifndef __PRETTY_FUNCTION__			// no PRETTY_FUNCTION defined
   #include "pretty.h"
#else
   #define USE_PRETTY 1				// have PRETTY_FUNCTION defined - use it
#endif

#undef USE_PRETTY			// uncomment this to use __PRETTY_FUNCTION__
#undef DEBUG_IT				// uncomment this while debugging

#include <iostream>
#include <map>
#include <vector>
#include <bitset>

// Allocator 

const int maxCells = 10 + 1;	// number of reserved items in pool in single allocation

template <typename T>
struct mine_allocator 
{
	using value_type = T;

	using pointer = T *;
	using const_pointer = const T *;
	using reference = T &;
	using const_reference = const T &;

	T * m_Pool; 	// current memory pool -> T m_Pool[] for typeT & typeU
	std::bitset<maxCells> m_poolFree ;		// false - free cell, true - busy cell
#ifdef DEBUG_IT
	int m_magic;
#endif
	int m_cellSz;

	template <typename U>
	struct rebind {
		using other = mine_allocator<U>;
	};

	mine_allocator() : 	m_Pool (nullptr), 
						m_poolFree (0),
#ifdef DEBUG_IT
						m_magic (1000 + sizeof(T)), 
#endif
						m_cellSz (sizeof(T)) 
	{
#ifdef DEBUG_IT
#ifndef USE_PRETTY
		std::cout << "ctor : " << m_magic << " : " << sizeof(T) << " : " << this << std::endl;
#else
		std::cout << __PRETTY_FUNCTION__ << std::endl;
#endif
#endif
	}

	~mine_allocator() 
	{
#ifdef DEBUG_IT
#ifndef USE_PRETTY
		std::cout << "dtor : " << m_magic << " : " << this << std::endl;
#else
		std::cout << __PRETTY_FUNCTION__ << std::endl;
#endif
#endif
	}

	template <typename U>
	mine_allocator(const mine_allocator<U> &) : m_Pool (nullptr), 
												m_poolFree (0),
#ifdef DEBUG_IT
												m_magic (1000 + sizeof(U)), 
#endif
												m_cellSz (sizeof(U)) 
	{
#ifdef DEBUG_IT
#ifndef USE_PRETTY
		std::cout << "ctor : " << m_magic << " : " << sizeof(U) << " : " << this << std::endl;
#else
		std::cout << __PRETTY_FUNCTION__ << std::endl;
#endif
#endif
	}

	T *allocate(std::size_t n) 		// allocate n cells
	{
#ifdef DEBUG_IT
#ifndef USE_PRETTY
		std::cout << "allocate: [n = " << n << "] : " << m_magic << " : " << sizeof(T) << " : " << this << std::endl;
#else
		std::cout << __PRETTY_FUNCTION__ << "[n = " << n << "]" << std::endl;
#endif
#endif
		if (m_Pool == nullptr)		// no allocation yet
		{
			auto p = std::malloc (maxCells * m_cellSz);		// allocate a new pool
			if (p == nullptr)		// cannot allocate
				throw std::bad_alloc{};
			m_Pool = reinterpret_cast<T *>(p);
			m_poolFree.reset();		// all cells are free
		}

		int i = findFreeCells (n);

		if (i < 0)		// cannot find free cels
			throw std::bad_alloc{};

		return (m_Pool + i);
	}

	void deallocate(T *p, std::size_t n) 	// deallocate n cells
	{
#ifdef DEBUG_IT
#ifndef USE_PRETTY
		std::cout << "deallocate: [p  = " << p << "] : " << m_Pool << " : " << m_magic << " : " << this << std::endl;
#else
		std::cout << __PRETTY_FUNCTION__ << "[n = " << n << "]" << std::endl;
#endif
#endif
		if (m_Pool != nullptr)
		{
			int i = p - m_Pool;
			
			for (int j = 0; j < n; ++j)
				m_poolFree [i + j] = false;
			if (m_poolFree.none())		// all cells are free
			{
				free (m_Pool);
				m_Pool = nullptr;
			}
		}
	}

	template <typename U, typename... Args>
	void construct(U *p, Args &&...args) 
	{
#ifdef DEBUG_IT
#ifndef USE_PRETTY
		std::cout << "construct : " << m_magic << "  : " << sizeof(U) << " : " << this << std::endl;
#else
		std::cout << __PRETTY_FUNCTION__ << std::endl;
#endif
#endif
		new (p) U(std::forward<Args>(args)...);
	};

	template <typename U>
	void destroy(U *p) 
	{
#ifdef DEBUG_IT
#ifndef USE_PRETTY
		std::cout << "destroy : " << m_magic << " : " << sizeof(U) << " : " << this << std::endl;
#else
		std::cout << __PRETTY_FUNCTION__ << std::endl;
#endif
#endif
		p->~U();
	}

	// findFreeCells - to count max consecutive free cells
	// 
	int findFreeCells (int nCells)
	{
		for (int i = 0, n = 0; i < maxCells; ++i)
		{
			if (m_poolFree [i] == false)	// cell is free
			{
				++n;
				if (n == nCells)		// found required amount of free cells
				{
					i -= nCells - 1;			// index of first cell 
					for (n = 0; n < nCells; ++n)
						m_poolFree [i + n] = true;	// mark as busy
#ifdef DEBUG_IT
std::cout << "findFreeCells : " << m_magic << " : i = " << i << " : " << this << std::endl;						
#endif
					return i;
				}
			}	
			else 				// cell is not free
			{
				n = 0;			// re-init counter
			}
		}
		// cannot find enough free cells
		return -1;
	}

};

// Iterative function to calculate Factorial
//
unsigned int Factorial (unsigned int n)
{
    unsigned int ret = 1;
    for (unsigned int i = 1; i <= n; ++i)
        ret *= i;
    return ret;
}

// main function to test mine_allocator with map
//
int main(int, char *[])
{
	auto sMap = std::map<int, int> {};		// std map with std allocator

	std::cout << "\n***** Start test for 10 items in std::map with std::allocator. Should be Ok." << std::endl;

	try {		// try max allocation of 10 items -> should be Ok
		for (int i = 0; i < 10; ++i) 
		{
			sMap[i] = Factorial (i);
		}
	}
	catch (const std::bad_alloc& e) 
	{
        std::cout << "Allocation failed: " << e.what() << '\n';
	}
	catch (const std::exception& e) // caught by reference to base
    {
        std::cout << " a standard exception was caught, with message '"
                  << e.what() << "'\n";
    }

	std::cout << "Map of " << sMap.size() << " items." << std::endl;

	for (const auto& [n, f] : sMap)
		std::cout << n << " " << f << std::endl;

	auto mMap = std::map<int, int, std::less<int>, mine_allocator<std::pair<const int, int>>>{};

	std::cout << "\n***** Start test for 10 items. Should be Ok." << std::endl;

	try {		// try max allocation of 10 items -> should be Ok
		for (int i = 0; i < 10; ++i) 
		{
			mMap[i] = Factorial (i);
		}
	}
	catch (const std::bad_alloc& e) 
	{
        std::cout << "Allocation failed: " << e.what() << '\n';
	}
	catch (const std::exception& e) // caught by reference to base
    {
        std::cout << " a standard exception was caught, with message '"
                  << e.what() << "'\n";
    }

	std::cout << "Map of " << mMap.size() << " items." << std::endl;

	for (const auto& [n, f] : mMap)
		std::cout << n << " " << f << std::endl;

	mMap.clear ();

	std::cout << "\n***** Start test for more than 10 items. Should be catched with bad allocation error and map should contain 10 items." << std::endl;

	try {			// now try more than 10 items -> should be catched
		for (int i = 0; i < 15; ++i) 
		{
			mMap[i] = i < 10 ? Factorial (i) : 1000 + i;
		}
	}
	catch (const std::bad_alloc& e) 
	{
        std::cout << "Allocation failed: " << e.what() << '\n';
	}
	catch (const std::exception& e) // caught by reference to base
    {
        std::cout << " a standard exception was caught, with message '"
                  << e.what() << "'\n";
    }

	std::cout << "Map contains " << mMap.size() << " items." << std::endl;

	std::cout << "\nComplete.\n" << std::endl;

	return 0;
}

