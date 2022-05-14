#include <iostream>
#include <exception>
#include <stdio.h>
using namespace std;

namespace ExpressionEvaluator {

	enum TOKEN {
			ILLEGAL_TOKEN=-1,
			TOK_PLUS=1,
			TOK_MUL,
			TOK_DIV, 
			TOK_SUB,
			TOK_OPAREN,
			TOK_CPAREN,
			TOK_DOUBLE,
			TOK_NULL 
	};
		
	class Lexer
	{
			string IExpr;
			int    index = 1;
			int    length;
			double number;
			public:
                        Lexer(string Expr)
			{
				IExpr = Expr;
				length = IExpr.length(); 
				index = 0;
            			
			}
                        virtual ~Lexer() {} 
			/// <summary>
			/// 
			/// </summary>
			/// <returns></returns>
			 TOKEN GetToken()
			{
				TOKEN tok = ILLEGAL_TOKEN;

				while (index < length && (IExpr[index] == ' ' || IExpr[index]== '\t') )
					index++;

				if ( index == length)
					return TOK_NULL;
 
				switch(IExpr[index])
				{
					case '+':
						tok = TOK_PLUS;
						index++;
						break;
					case '-':
						tok = TOK_SUB;
						index++;
						break;
					case '/':
						tok = TOK_DIV;
						index++;
						break;
					case '*':
						tok = TOK_MUL;
						index++;
						break;
					case '(':
						tok = TOK_OPAREN;
						index++;
						break;
					case ')':
						tok = TOK_CPAREN;
						index++;
						break;
					case '0':
					case '1':
					case '2':
					case '3':
					case '4':
					case '5':
					case '6':
					case '7': 
					case '8': 
					case '9':
					{
						string str="";
				  
						while ( index < length &&( IExpr[index] == '0' || 
							IExpr[index]==  '1' ||
							IExpr[index] == '2' || 
							IExpr[index]== '3'  ||
							IExpr[index] == '4' || 
							IExpr[index]== '5'  ||
							IExpr[index] == '6' || 
							IExpr[index]== '7'  ||
							IExpr[index] == '8' || 
							IExpr[index]== '9'  ))
						{
							str += IExpr[index];
							index ++;
						}

				   
						number = atof(str.c_str()); 
						tok = TOK_DOUBLE; 

					}
						break;
					default:
						printf("Error While Analyzing Tokens");  
						throw new exception();
				

				}

				return tok; 

			}

			 double GetNumber() { return number; }
		};


		/// <summary>
		/// 
		/// </summary>
		/// 
		class Stack{
			double *stk;
			int top_stack = 0; 
                      public:
			Stack(){stk = new double[256];top_stack = 0;}
                        ~Stack() {
                                if (stk) { delete [] stk; }
                        }
			void Clear(){top_stack = 0;}
			void push(double dbl ){
				if ( top_stack == 255 ){printf("Stack OverFlow"); throw new exception();}
				stk[top_stack++] = dbl;
			}
			double  pop(){
				if ( top_stack == 0 ){printf("Stack UnderFlow"); throw new exception();}
				return stk[--top_stack];
			}
                };

	
		class RDParser : public Lexer{
			TOKEN Current_Token;
			Stack *ValueStack = 0;
			public:
                        RDParser(string str):Lexer(str){
                              ValueStack = new Stack() ;
                        }
			~RDParser() { if (ValueStack ) { delete ValueStack; } }
                        double CallExpr(){ 
				ValueStack->Clear();Current_Token= GetToken(); Expr();  double nd = ValueStack->pop();
				return nd;
			}
			void Expr(){
				TOKEN l_token;
				Term();
				if  ( Current_Token == TOK_PLUS  || Current_Token == TOK_SUB ) {
					l_token = Current_Token;Current_Token = GetToken();
					Expr();
					double x = ValueStack->pop(); double y = ValueStack->pop();
					ValueStack->push( (l_token == TOK_PLUS ) ? (x + y) : (y-x) ); 

				}
                                                   }

			void Term(){
				TOKEN l_token;
				Factor();
				if ( Current_Token == TOK_MUL  || Current_Token == TOK_DIV ) {
					l_token = Current_Token; Current_Token = GetToken();
					Term();
					double x = ValueStack->pop(); double y = ValueStack->pop();
					if ( x == 0 ) { printf("Division By Zero Error");throw new exception();}
					ValueStack->push( (l_token == TOK_MUL ) ? (x * y) :  (y/x) ); 
				
				}
                                                    }

			void Factor(){
				TOKEN l_token;
				if ( Current_Token == TOK_DOUBLE ){
					ValueStack->push(GetNumber()); Current_Token = GetToken();  
				} 
				else if ( Current_Token == TOK_OPAREN ){
					Current_Token = GetToken();   
					Expr();  // Recurse
				                 if ( Current_Token != TOK_CPAREN ){printf("Missing Closing Parenthesis\n"); throw new exception();}   
					Current_Token = GetToken();            
				} 
				else if ( Current_Token == TOK_PLUS || Current_Token == TOK_SUB ){
					l_token = Current_Token; Current_Token = GetToken();
					Factor();
					double  x = ValueStack->pop();
					if ( l_token == TOK_SUB ) { x = -x;}
					ValueStack->push(x);  
   
				}
				else { printf("Illegal Token"); throw new exception();} 
			}

          };
		 
			


	
	
};

using namespace ExpressionEvaluator ;

 int main(int argc , char **argv) {
 		if ( argc == 1 || argc > 2 ) {  
    			printf("Usage : Expr \"<expr>\" \n");
    		        printf(" eg:- Expr \"2*3+4\" \n");
    			printf(" Expr \"-2-3\" \n");
   			return -1;
  		}
                RDParser * parser =  0;         

		try {
    				parser = new RDParser (string(argv[1]));
    				double nd  = parser->CallExpr();
   				printf("The Evaluated Value is {%e} \n",nd );
                                delete parser;
 		}
  		catch(exception& e ) {
    				printf("Error Evaluating Expression\n");
    			        if ( parser ) { delete parser; }
    				return -1;
  			}
		   }