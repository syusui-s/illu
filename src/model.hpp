#pragma once

#include <vector>
#include <string>
#include <sstream>
#include <memory>

namespace model {
	/**
	 * Abstract Class for All handlable data
	 */
	class Element
	{
		public:
			/**
			 * destructor
			 */
			virtual ~Element() {}
			/**
			 * check if it is instance of T class by using RTTI
			 */
			template<typename T>
			inline bool instance_of() const {
				return dynamic_cast<const T*>(this) != NULL;
			}

			/**
			 * cast operation for object
			 */
			template<typename T>
			inline T* cast() {
				return this->instance_of<T>() ? static_cast<T*>(this) : NULL;
			}
			virtual std::string to_string() const = 0;
	};

	/**
	 * Handle Stack of Element pointers
	 */
	class Stack : public std::vector<Element*>
	{
		public:
			std::string to_string() const;
			void push(Element*);
			void drop();
			Element* pop();
			void free_memory();
			Stack& operator+=(Stack&);
	};

	//////////////////////////////////
	// Numeric classes
	
	/**
	 * Abstract Class for Numeric data
	 */
	class Numeric : public Element
	{
		public:
			virtual ~Numeric() {}
	};

	/**
	 * Integer data
	 * 
	 * @see Numeric
	 */
	class Integer : public Numeric
	{
		public:
			typedef int TYPE;
		private:
			TYPE data;
		public:
			Integer(const TYPE _data) : data(_data) {}
			Integer(const std::string _data, int base) :
				data(std::stoi(_data, 0, base))
			{}
			virtual ~Integer() {}
			// Instance Methods
			
			/**
			 * get original data
			 */
			inline TYPE get_data() { return data; }
			virtual std::string to_string() const;

			// Operators
			Element* add(Element *other);
			Element* sub(Element *other);
			Element* mul(Element *other);
			Element* div(Element *other);
	};

	/**
	 * Float data
	 * 
	 * @see Numeric
	 */
	class Float : public Numeric
	{
		public: typedef double TYPE;
		private:
			TYPE data;
		public:
			Float(const TYPE _data) : data(_data) {}
			Float(const std::string &_data) :
				data(std::stod(_data, 0))
			{}
			virtual ~Float() {}

			// Instance Methods
			inline TYPE get_data() { return data; }
			virtual std::string to_string() const;

			// Operators
			Element* add(Element *other);
			Element* sub(Element *other);
			Element* mul(Element *other);
			Element* div(Element *other);
	};

	/**
	 * String data
	 *
	 * representation of string data
	 */
	class String : public Element
	{
		private:
			const std::string data;
		public:
			String(const std::string &_data) : data(_data) {}

			// Instance Methods
			virtual std::string to_string() const;
			inline std::string get_data() { return data; }
	};


	/**
	 * Nil data
	 *
	 * This is a singleton class.
	 * Call get_instance to get 
	 * this is called as NULL in other languages.
	 */
	class Nil : public Element
	{
		private:
			Nil() {};
		public:
			virtual ~Nil() {};
			/**
			 * get single instance
			 *
			 * @return Nil&
			 */
			static Element* get_instance() {
				static Nil nil;
				return &nil;
			}

			// Instance Methods
			virtual std::string to_string() const;
	};

	//////////////////////////
	// Instruction Classes
	class Instruction : public Element
	{
		public:
			/**
			 * Definition of All operators
			 */
			enum Instructions {
				// basic arithmetic operators
				INST_PLUS, INST_MINUS, INST_MULTIPLICATION, INST_DIVISION,
				// monadic operators
				INST_ABSOLUTE, INST_SIGN_INVERSE, INST_INVERSE,
				// exponential function
				INST_POWER, INST_SQRT, INST_CBRT, INST_EXP,
				// logarithm functions
				INST_NATURAL_LOG, INST_COMMON_LOG, INST_LOG,
				// trigonometric functions
				INST_SIN, INST_COS, INST_TAN, INST_ASIN, INST_ACOS, INST_ATAN,
				// hyperbolic functions
				INST_SINH, INST_COSH, INST_TANH, INST_ASINH, INST_ACOSH, INST_ATANH,
				// data structure operations
				INST_POP, INST_DROP, INST_ROLL, INST_SWAP,
			};
		private:
			const Instructions data;
		public:
			Instruction(const Instructions _data) : data(_data) {}
			virtual ~Instruction() {}

			std::string to_string() const { return ""; } // TODO implementation

			Stack& applicate(Stack& stack);
			Stack& add(Stack& stack);
			Stack& sub(Stack& stack);
			Stack& mul(Stack& stack);
			Stack& div(Stack& stack);
	};
}
