/*
 * =====================================================================================
 *
 *       Filename:  testCountVariadicArguments.cpp
 *
 *    Description:  
 *
 *        Version:  1.0
 *        Created:  03/12/2015 05:40:30 PM
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  Bart Verhagen (bv), bart.verhagen@tass.be
 *   Organization:  TASS
 *
 * =====================================================================================
 */
#include <cstdlib>
#include <string>

#include <catch.hpp>

#include "countVariadicArguments.hpp"

using std::srand;
using std::rand;
using std::string;
using variadic::countArguments;

// Variadic argument classes
class VariadicArgument {
    public:
        VariadicArgument(int t1...) : _nbOfArguments(countArguments(t1)) {
            ;
        }

        uint32_t getNbOfArguments(void) {
            return _nbOfArguments;
        }

    private:
        uint32_t _nbOfArguments;
};

template <typename... T>
class VariadicArgumentTemplate {
    public:
        VariadicArgumentTemplate(T... t1) : _nbOfArguments(countArguments(t1...)) {
			// To check if we are indeed evaluating the number of arguments at compile time,
			// we use it in a static_assert that is always true
			static_assert(countArguments(t1...) == countArguments(t1...), "Checking whether the function call is evaluated at compile time.");
        }
        uint32_t getNbOfArguments(void) {
            return _nbOfArguments;
        }

    private:
        uint32_t _nbOfArguments;
};

SCENARIO("Checking whether the function behaves propery when we pass it one argument", "[simpleTest]") {
	GIVEN("Nothing in particular") {
		srand(0);
		uint32_t correctNbOfArguments = 1U;

		WHEN("We call the counter directly with an integer") {
			uint32_t arg1 = rand();
			uint32_t nbOfFoundArguments = countArguments(arg1); 

			THEN("We should get 1 as a result") {
				REQUIRE(nbOfFoundArguments == correctNbOfArguments);
			}
		}

		WHEN("We call the counter directly with a string") {
			const char* testString = "Hello";

			uint32_t nbOfFoundArguments = countArguments(testString);

			THEN("We should get 1 as a result") {
				REQUIRE(nbOfFoundArguments == correctNbOfArguments);
			}
		}

		WHEN("We call the counter indirectly using variadic arguments in a template") {
			VariadicArgumentTemplate<int> variadicArgumentInt(rand());
			VariadicArgumentTemplate<string> variadicArgumentString("Hello world!");
			
			THEN("We should get 1 as a result") {
				REQUIRE(variadicArgumentInt.getNbOfArguments() == correctNbOfArguments);
				REQUIRE(variadicArgumentString.getNbOfArguments() == correctNbOfArguments);
			}
		}

		WHEN("We call the counter indirectly using variadic arguments in an ordinary class") {
			VariadicArgument variadicArgumentInt(rand());

			THEN("We should get 1 as a result") {
				REQUIRE(variadicArgumentInt.getNbOfArguments() == correctNbOfArguments);
			}
		}
	}	
}

SCENARIO("Checking whether the function behaves propery when we pass it multiple homogeneous arguments", "[simpleTest]") {
	GIVEN("Nothing in particular") {
		srand(0);

		WHEN("We call the counter directly with three integers") {
			uint32_t nbOfFoundArguments = countArguments(rand(), rand(), rand()); 

			THEN("We should get 3 as a result") {
				REQUIRE(nbOfFoundArguments == 3U);
			}
		}

		WHEN("We call the counter indirectly using variadic arguments in a template") {
			VariadicArgumentTemplate<int, int, int> variadicArgumentInt(rand(), rand(), rand());
			VariadicArgumentTemplate<string, string, string> variadicArgumentString("Hello", "world", "!");

			THEN("We should get 3 as a result") {
				REQUIRE(variadicArgumentInt.getNbOfArguments() == 3U);
				REQUIRE(variadicArgumentString.getNbOfArguments() == 3U);
			}
		}

		WHEN("We call the counter indirectly using variadic arguments in an ordinary class") {
			VariadicArgument variadicArgumentInt(rand(), rand(), rand());

			THEN("We should get 3 as a result") {
				//FIXME this one fails due to compilation errors when passing throught the variadic arguments
				REQUIRE(variadicArgumentInt.getNbOfArguments() == 3U);
			}
		}
	}
}

SCENARIO("Checking whether the function behaves propery when we pass it multiple heterogeneous arguments", "[simpleTest]") {
	GIVEN("Nothing in particular") {
		srand(0);

		WHEN("We call the counter directly with three integers") {
			uint32_t nbOfFoundArguments = countArguments(rand(), rand(), "Hello world!"); 

			THEN("We should get 3 as a result") {
				REQUIRE(nbOfFoundArguments == 3U);
			}
		}

		WHEN("We call the counter indirectly using variadic arguments in a template") {
			VariadicArgumentTemplate<int, string, int> variadicArgumentInt(rand(), "Hello world!", rand());

			THEN("We should get 3 as a result") {
				REQUIRE(variadicArgumentInt.getNbOfArguments() == 3U);
			}
		}
	}
}
