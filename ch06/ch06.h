#pragma once

namespace ch06
{
	namespace sample
	{
		namespace s01
		{
			void calc();
		}

		namespace s02
		{
			void calc();
		}

		namespace s03
		{
			class Token 
			{
				public:
					char
						kind;
					double
						value;
					Token(char c = 0, double d = 0) :
						kind (c), value (d)
					{}
			};
		}

		namespace s05
		{
			//class TokenStream
			//{
			//	public:
			//		//TokenStream();
			//		Token getToken();
			//		void putBack(Token);
			// 
			//	private:
			//		bool 
			//			full{ false };
			//		Token 
			//			buffer;
			//};
			// 
			//using s03::Token;
			// 
			//Token getToken();
			//
			//double expression();
			//
			//double term();
		}
	}

	namespace drill
	{

		namespace d01
		{
			class Token										/// compile error #1
			{
				public:
					char	kind;							// what kind of token
					double	value;							// for numbers: a value 
					
					Token (char ch) :						// make a Token from a char
						kind (ch),	value (0) 
					{}
					
					Token (char ch, double val) :		    // make a Token from a char and a double
						kind (ch),	value (val) 
					{}
			};

			class Token_stream 
			{
				public:
					Token_stream();							// make a Token_stream that reads from cin
					Token get();							// get a Token (get() is defined elsewhere)
					void putback(Token t);					// put a Token back

				private:
					bool full;								// is there a Token in the buffer?
					Token buffer;							// here is where we keep a Token put back using putback()
			};

			double primary();

			double term();

			double expression();

			int main();
		}
	}
}