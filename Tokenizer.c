/*
 * tokenizer.c
 */
#include <stdio.h>
#include <ctype.h>
#include <stdlib.h>
#include <string.h>

/*
 * Tokenizer type.  You need to fill in the type as part of your implementation.
 */

struct TokenizerT_ {

char *p;
char *type;

};

/*typedef struct TokenizerT_ TokenizerT;*/

/*
 * TKCreate creates a new TokenizerT object for a given token stream
 * (given as a string).
 * 
 * TKCreate should copy the arguments so that it is not dependent on
 * them staying immutable after returning.  (In the future, this may change
 * to increase efficiency.)
 *
 * If the function succeeds, it returns a non-NULL TokenizerT.
 * Else it returns NULL.
 *
 * You need to fill in this function as part of your implementation.
 */
	struct TokenizerT_ *list;


void Check(struct TokenizerT_ *x){
		int i = 0;
			
			while(i<strlen(x->p)){
				
				if(x->p[i]=='.'){
					x->type = "floating point";
					break;
					}
				else{
					x->type = "digit";
					}
					i++;
				}
			}


		
					

struct TokenizerT_ *TKCreate( char * ts ) {
	int i = 0;
	int k;	/*counting if k is larger than size of array*/	
	int g=0;	/*index of char array*/
	int q = 0;
	int v = 0;	/*counting if v is larger than size of list array*/
	list = malloc(sizeof(struct TokenizerT_)*10);
	
	while(i<strlen(ts)){
		
		if(isspace(ts[i])){
			
			i++;
			}
		

		else if(ts[i]=='0' && (ts[i+1]=='x' || ts[i+1]=='X')){
				k = 0;
				struct TokenizerT_ *hex = malloc(sizeof(struct TokenizerT_));
				hex->p = malloc(sizeof(char)*10);
				hex->type = malloc(sizeof(char)*12);
				hex->type = "hexadecimal";
				hex->p[k]=ts[i];
				hex->p[k+1]=ts[i+1];
				i=i+2;
				k++;
				g++;
				
				while(isxdigit(ts[i])){
					if(k>10){
						hex->p = realloc(hex->p,sizeof(char)*(strlen(hex->p)+10));
						k=0;
						}
						k++;
						g++;
						hex->p[g]=ts[i];
						i++;
					}
					g=0;
					if(v>=10){
							
							list = realloc(list,(sizeof(struct TokenizerT_))*(q+10));
							v=0;
							}
						list[q] = *hex;
						free(hex);
						q++;
						v++;
						
				}	
				
		else if(isalpha(ts[i])){
			//printf("i is %d",i);						/*IS A WORD*/
			k=0;
			struct TokenizerT_ *word = malloc(sizeof(struct TokenizerT_));	/*create new tokenizer for word*/   
			word->p = malloc(sizeof(char)*10);
			word->type = malloc(sizeof(char)*5);
			word->type = "word";
			(word->p)[k]=ts[i];					/*first letter of the word*/
			i++;		
				while(isalpha(ts[i])){
					
					if(k>10){
						word->p = realloc(word->p,sizeof(char)*(strlen(word->p)+10));
						k=0;						   /*word is larger than 10 so realloc*/
						}
					k++;
					g++;							
					(word->p)[g] = ts[i];
					i++;
					
					
					
					}
						g=0;
						if(v>=10){
							list = realloc(list,(sizeof(struct TokenizerT_))*(q+10));
							v=0;
							}
						list[q] = *word;
						free(word);
						q++;
						v++;
						
					//printf("i is %d",i);
					
				}

				else if(ts[i]=='['){

					if(v>10){
							list = realloc(list,(sizeof(struct TokenizerT_))*(q+10));
							v=0;
							}
					struct TokenizerT_ *lbrace = malloc(sizeof(struct TokenizerT_));
					lbrace->p = malloc(sizeof(char)*2);
					lbrace->p ="[";
					lbrace->type = malloc(sizeof(char)*12);
					lbrace->type = "left brace";
					list[q] = *lbrace;
					free(lbrace);
					q++;
					i++;
					v++;
			}
				else if(ts[i]==']'){
					if(v>=10){
							list = realloc(list,(sizeof(struct TokenizerT_))*(q+10));
							v=0;
							}
					struct TokenizerT_ *rbrace = malloc(sizeof(struct TokenizerT_));
					rbrace->p = malloc(sizeof(char)*2);
					rbrace->p ="]";
					rbrace->type = malloc(sizeof(char)*12);
					rbrace->type = "right brace";
					list[q] = *rbrace;
					free(rbrace);
					q++;
					i++;
					v++;
				}

				else if(isdigit(ts[i])){
					k = 0;
					struct TokenizerT_ *dig = malloc(sizeof(struct TokenizerT_));	
					dig->p = malloc(sizeof(char)*10);
					dig->type = malloc(sizeof(char)*5);
					(dig->p)[k]=ts[i];					
					i++;		
						while(isdigit(ts[i]) || (ts[i]=='.')){
							if(ts[i]=='.'){
								dig->type = "floating point";
								if(k>10){
									dig->p = realloc(dig->p,sizeof(char)*(strlen(dig->p)+10));
									k=0;
									}
								k++;
								g++;
								dig->p[g]=ts[i];
								i++;
								while(isdigit(ts[i]) || ts[i]=='e' || ts[i]=='E' || ts[i]=='-'){
									
									if(k>10){
										dig->p = realloc(dig->p,sizeof(char)*(strlen(dig->p)+10));
										k=0;
										}
									k++;
									g++;
									dig->p[g] = ts[i];
									i++;
									}
									g = 0;

									if(v>=10){
										list = realloc(list,(sizeof(struct TokenizerT_))*(q+10));
										v=0;
										}
								list[q] = *dig;
								
								break;
						
							}	
								
							
							if(k>10){
								dig->p = realloc(dig->p,sizeof(char)*(strlen(dig->p)+10));
								k=0;						   
								}
									k++;
									g++;
									dig->p[g] = ts[i];
									i++;
								}
								g=0;
								
							if(v>=10){
								list = realloc(list,(sizeof(struct TokenizerT_))*(q+10));
								v=0;
							}
								Check(dig);
								list[q] = *dig;
								free(dig);
								q++;
								v++;
								
						
							}
						else if(ts[i]=='+' &&  ts[i+1]=='='){
								if(v>=10){
									list = realloc(list,(sizeof(struct TokenizerT_))*(q+10));
								v=0;
							}
								struct TokenizerT_ *PE = malloc(sizeof(char)*3);
								PE->p = "+=";
								PE->type = "plus equals";
								list[q] = *PE;
								free(PE);
								q++;
								v++;
								i=i+2;
							}
						else if(ts[i]=='>' && ts[i+1]=='>'){
						if(v>=10){
									list = realloc(list,(sizeof(struct TokenizerT_))*(q+10));
								v=0;
							}
								struct TokenizerT_ *PE = malloc(sizeof(char)*3);
								PE->p = ">>";
								PE->type = "shift right";
								list[q] = *PE;
								free(PE);
								q++;
								v++;
								i=i+2; 
							}
					else if(ts[i]=='-' &&  ts[i+1]=='='){
								if(v>=10){
									list = realloc(list,(sizeof(struct TokenizerT_))*(q+10));
								v=0;
							}
								struct TokenizerT_ *PE = malloc(sizeof(char)*3);
								PE->p = "-=";
								PE->type = "minus equals";
								list[q] = *PE;
								free(PE);
								q++;
								v++;
								i=i+2;
							}
					else if(ts[i]=='*' &&  ts[i+1]=='='){
								if(v>=10){
									list = realloc(list,(sizeof(struct TokenizerT_))*(q+10));
								v=0;
							}
								struct TokenizerT_ *PE = malloc(sizeof(char)*3);
								PE->p = "*=";
								PE->type = "times equals";
								list[q] = *PE;
								free(PE);
								q++;
								v++;
								i=i+2;
							}
					else if(ts[i]=='|' && ts[i+1]=='|'){
							if(v>=10){
									list = realloc(list,(sizeof(struct TokenizerT_))*(q+10));
									v=0;
								}
								struct TokenizerT_ *PE = malloc(sizeof(char)*3);
								PE->p = "||";
								PE->type = "logical or";
								list[q] = *PE;
								free(PE);
								q++;
								v++;
								i=i+2;
					}
					else if(ts[i]=='&' && ts[i+1]=='&'){
							if(v>=10){
									list = realloc(list,(sizeof(struct TokenizerT_))*(q+10));
									v=0;
								}
								struct TokenizerT_ *PE = malloc(sizeof(char)*3);
								PE->p = "&&";
								PE->type = "logical and";
								list[q] = *PE;
								free(PE);
								q++;
								v++;
								i=i+2;
					}
					else if(ts[i]=='<' && ts[i+1]=='<'){
							if(v>=10){
									list = realloc(list,(sizeof(struct TokenizerT_))*(q+10));
									v=0;
								}
								struct TokenizerT_ *PE = malloc(sizeof(char)*3);
								PE->p = "<<";
								PE->type = "shift left";
								list[q] = *PE;
								free(PE);
								q++;
								v++;
								i=i+2;
					}
					else if(ts[i]=='/' &&  ts[i+1]=='='){
								if(v>=10){
									list = realloc(list,(sizeof(struct TokenizerT_))*(q+10));
								v=0;
							}
								struct TokenizerT_ *PE = malloc(sizeof(char)*3);
								PE->p = "/=";
								PE->type = "divide equals";
								list[q] = *PE;
								free(PE);
								q++;
								v++;
								i=i+2;
							}
						else if(ts[i]=='<' && ts[i+1]=='<'){
							if(v>=10){
									list = realloc(list,(sizeof(struct TokenizerT_))*(q+10));
									v=0;
								}
								struct TokenizerT_ *PE = malloc(sizeof(char)*3);
								PE->p = "<<";
								PE->type = "shift left";
								list[q] = *PE;
								free(PE);
								q++;
								v++;
								i=i+2;
					}
						else if(ts[i]=='=' && ts[i+1]=='='){
							if(v>=10){
									list = realloc(list,(sizeof(struct TokenizerT_))*(q+10));
									v=0;
								}
								struct TokenizerT_ *PE = malloc(sizeof(char)*3);
								PE->p = "==";
								PE->type = "equals";
								list[q] = *PE;
								free(PE);
								q++;
								v++;
								i=i+2;
					}
						else if(ts[i]=='!' && ts[i+1]=='='){
							if(v>=10){
									list = realloc(list,(sizeof(struct TokenizerT_))*(q+10));
									v=0;
								}
								struct TokenizerT_ *PE = malloc(sizeof(char)*3);
								PE->p = "!=";
								PE->type = "not equals";
								list[q] = *PE;
								free(PE);
								q++;
								v++;
								i=i+2;
					}
					else if(ts[i]=='>' && ts[i+1]=='='){
								if(v>=10){
									list = realloc(list,(sizeof(struct TokenizerT_))*(q+10));
								v=0;
							}
								struct TokenizerT_ *PE = malloc(sizeof(char)*2);
								PE->p = ">=";
								PE->type = "greater or equal";
								list[q] = *PE;
								free(PE);
								q++;
								v++;
								i++;
							}
					else if(ts[i]=='<' && ts[i+1]=='='){
								if(v>=10){
									list = realloc(list,(sizeof(struct TokenizerT_))*(q+10));
								v=0;
							}
								struct TokenizerT_ *PE = malloc(sizeof(char)*2);
								PE->p = "<=";
								PE->type = "less or equal";
								list[q] = *PE;
								free(PE);
								q++;
								v++;
								i++;
							}
					else if(ts[i]=='+'){
								if(v>=10){
									list = realloc(list,(sizeof(struct TokenizerT_))*(q+10));
								v=0;
							}
								struct TokenizerT_ *PE = malloc(sizeof(char)*2);
								PE->p = "+";
								PE->type = "add";
								list[q] = *PE;
								free(PE);
								q++;
								v++;
								i++;
							}
					else if(ts[i]=='%'){
								if(v>=10){
									list = realloc(list,(sizeof(struct TokenizerT_))*(q+10));
								v=0;
							}
								struct TokenizerT_ *PE = malloc(sizeof(char)*2);
								PE->p = "%";
								PE->type = "modulus";
								list[q] = *PE;
								free(PE);
								q++;
								v++;
								i++;
							}
					else if(ts[i]=='^'){
								if(v>=10){
									list = realloc(list,(sizeof(struct TokenizerT_))*(q+10));
								v=0;
							}
								struct TokenizerT_ *PE = malloc(sizeof(char)*2);
								PE->p = "^";
								PE->type = "bitwise exclusive or";
								list[q] = *PE;
								free(PE);
								q++;
								v++;
								i++;
							}
					else if(ts[i]=='&'){
								if(v>=10){
									list = realloc(list,(sizeof(struct TokenizerT_))*(q+10));
								v=0;
							}
								struct TokenizerT_ *PE = malloc(sizeof(char)*2);
								PE->p = "&";
								PE->type = "bitwise and";
								list[q] = *PE;
								free(PE);
								q++;
								v++;
								i++;
							}
					else if(ts[i]=='|'){
								if(v>=10){
									list = realloc(list,(sizeof(struct TokenizerT_))*(q+10));
								v=0;
							}
								struct TokenizerT_ *PE = malloc(sizeof(char)*2);
								PE->p = "|";
								PE->type = "bitwise or";
								list[q] = *PE;
								free(PE);
								q++;
								v++;
								i++;
							}
			
					else if(ts[i]=='-'){
								if(v>=10){
									list = realloc(list,(sizeof(struct TokenizerT_))*(q+10));
								v=0;
							}
								struct TokenizerT_ *PE = malloc(sizeof(char)*2);
								PE->p = "-";
								PE->type = "minus";
								list[q] = *PE;
								free(PE);
								q++;
								v++;
								i++;
							}
					else if(ts[i]=='*'){
								if(v>=10){
									list = realloc(list,(sizeof(struct TokenizerT_))*(q+10));
								v=0;
							}
								struct TokenizerT_ *PE = malloc(sizeof(char)*2);
								PE->p = "*";
								PE->type = "multiply";
								list[q] = *PE;
								free(PE);
								q++;
								v++;
								i++;
							}
					else if(ts[i]=='/'){
								if(v>=10){
									list = realloc(list,(sizeof(struct TokenizerT_))*(q+10));
									v=0;
							}
								struct TokenizerT_ *PE = malloc(sizeof(char)*2);
								PE->p = "/";
								PE->type = "division";
								list[q] = *PE;
								free(PE);
								q++;
								v++;
								i++;
							}
					
					
					}

				
			
  return list;
}
/*
 * TKDestroy destroys a TokenizerT object.  It should free all dynamically
 * allocated memory that is part of the object being destroyed.
 *
 * You need to fill in this function as part of your implementation.
 */

void TKDestroy( struct TokenizerT_ * tk ) {
			
}

/*
 * TKGetNextToken returns the next token from the token stream as a
 * character string.  Space for the returned token should be dynamically
 * allocated.  The caller is responsible for freeing the space once it is
 * no longer needed.
 *
 * If the function succeeds, it returns a C string (delimited by '\0')
 * containing the token.  Else it returns 0.
 *
 * You need to fill in this function as part of your implementation.
 */

char *TKGetNextToken(struct TokenizerT_ * tk, char *p ) {
	int u = 0;
	tk = TKCreate(p);
	while(tk[u].p!=NULL){
		printf("%s",tk[u].type);
		printf(" \"%s\"",tk[u].p);
		printf("\n");
		u++;
		}	
  return NULL;
}

/*
 * main will have a string argument (in argv[1]).
 * The string argument contains the tokens.
 * Print out the tokens in the second string in left-to-right order.
 * Each token should be printed on a separate line.
 */

int main(int argc, char **argv) {
	char *z = argv[1];
	struct TokenizerT_ *y = malloc(sizeof(struct TokenizerT_));
	TKGetNextToken(y,z);

	
	/*struct TokenizerT_ *t;
	t = TKCreate(p);
	
	while(t[u].p!=NULL){
		printf("%s",t[u].p);
		printf("  %s",t[u].type);
		printf("\n");
		u++;
			}
		//printf("%s",t[0].type);*/
		


  return 0;
}
