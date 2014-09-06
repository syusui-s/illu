#pragma once

#include <list>
#include <string>
#include <sstream>
#include <memory>
#include <map>

#include "tokentype.hpp"
#include "model.hpp"

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
				return typeid(*this) == typeid(const T);
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
	class Stack : public std::list<Element*>, public Element
	{
		public:
			virtual std::string to_string() const;
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

			// Operators
			Element* add(Element *other);
	};

	/**
	 * Nil data
	 *
	 * NULL data expression
	 */
	class Nil : public Element
	{
		public:
			Nil() {};
			virtual ~Nil() {};
			// Instance Methods
			virtual std::string to_string() const;
	};

	/**
	 * Boolean data
	 *
	 * True / False data
	 */
	class Boolean : public Element
	{
		private:
			const bool data;
		public:
			Boolean(const bool &_data) : data(_data) {};
			virtual ~Boolean() {};
			// Instance Methods
			inline bool get_data() { return data; }
			virtual std::string to_string() const;
	};

	/**
	 * Symbol data
	 *
	 * Symbol represents a string that can be a IDENTIFIER
	 * e.g. used in where interpreter register user defined function to function table
	 */
	class Symbol : public Element
	{
		private:
			const std::string data;
		public:
			Symbol(const std::string &_data) : data(_data) {}

			// Instance Methods
			virtual std::string to_string() const;
			inline std::string get_data() { return data; }
	};

	/**
	 * Identifier
	 *
	 * Identifier is a string data represents some data in the table
	 * instance will be replaced with a tethered data
	 */
	class Identifier : public Element
	{
		private:
			const std::string data;
		public:
			Identifier(const std::string &_data) : data(_data) {}

			// Instance Methods
			virtual std::string to_string() const;
			inline  std::string get_data() { return data; }
	};

	//////////////////////////
	// Instruction Classes
	class Instruction : public Element
	{
		private:
			// Instruction
			typedef struct {
				model::Stack& (*pfunc)(model::Stack&); // Pointer to a static member function
				size_t num_of_args;              // Number of Arguments
				std::string string_expression;         // Human Readable Expression
			} S_Instruction;

			// Instructions Map
			static const std::map<tokentype::Type, S_Instruction> instructions;
			tokentype::Type toktype;

			// Function
			static Stack& add(Stack& stack);
			static Stack& sub(Stack& stack);
			static Stack& mul(Stack& stack);
			static Stack& div(Stack& stack);
			static Stack& drop(Stack& stack);
			static Stack& if_func(Stack& stack);
		public:
			Instruction(const tokentype::Type _toktype) : toktype(_toktype) {}
			virtual ~Instruction() {}

			std::string to_string() const;
			Stack& applicate(Stack& stack);
			size_t num_of_args() const;
	};
}
