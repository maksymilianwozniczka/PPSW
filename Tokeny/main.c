#include "string.h"

#define NULL '\0' 
#define MAX_TOKEN_NR 3 
#define MAX_KEYWORD_STRING_LTH 10 
#define MAX_KEYWORD_NR 3 
#define DELIMITER_CHARACTER ' ' 

enum KeywordCode {LD, ST, RST};

union TokenValue { 
	enum KeywordCode eKeyword;  
	unsigned int uiNumber;  
	char* pcString; 
};

enum TokenType {KEYWORD, NUMBER, STRING};

struct Token { 
	enum TokenType eType;  
	union TokenValue uValue; 
};

struct Token asToken[MAX_TOKEN_NR]; 
unsigned char ucTokenNr;  

struct Keyword { 
enum KeywordCode eCode; 
char cString[MAX_KEYWORD_STRING_LTH + 1]; 
}; 

struct Keyword asKeywordList[MAX_KEYWORD_NR]={ 
	{RST,"reset"}, 
	{LD, "load" }, 
	{ST, "store"} 
}; 

enum State {TOKEN, DELIMITER}; 

unsigned char ucFindTokensInString(char *pcString) {
	
	enum State eCurrentState = DELIMITER; 
	unsigned char ucCharacterCounter; 
	unsigned char ucCurrentCharacter; 
	unsigned char ucTokenNumber = 0; 

	for(ucCharacterCounter = 0; ; ucCharacterCounter++){
		
		ucCurrentCharacter = pcString[ucCharacterCounter];
		
		switch(eCurrentState) {
			
			case DELIMITER:
				if(NULL == ucCurrentCharacter) {
					
					return ucTokenNumber;
				}
				else if(DELIMITER_CHARACTER == ucCurrentCharacter){
				}
				else if(MAX_TOKEN_NR == ucTokenNumber) {
					
					return ucTokenNumber;
				}
				else {
					
					eCurrentState = TOKEN;
					asToken[ucTokenNumber].uValue.pcString = (pcString + ucCharacterCounter);
					ucTokenNumber++;
				}
				break; 
			case TOKEN:
				if(NULL == ucCurrentCharacter){
					
					return ucTokenNumber;
				}
				else if (DELIMITER_CHARACTER == ucCurrentCharacter) {
					
					eCurrentState = DELIMITER;
				}
				else {
					
					eCurrentState = TOKEN;
				}
				break;
		}
	}
}

enum Result {OK, ERROR}; 

enum Result eStringToKeyword (char pcStr[],enum KeywordCode *peKeywordCode) {  
	unsigned char ucKeywordCounter; 

	for(ucKeywordCounter=0; ucKeywordCounter < MAX_KEYWORD_NR; ucKeywordCounter++) {  
		
		if(EQUAL == eCompareString(asKeywordList[ucKeywordCounter].cString, pcStr)) { 

			*peKeywordCode = asKeywordList[ucKeywordCounter].eCode;  
			return OK; 
		} 
	} 
	return ERROR; 
}  

void DecodeTokens(void) {
	
	unsigned char ucTokenCounter; 
	struct Token * psCurrentToken; 
	unsigned int uiTokenNumber = 0;
	enum KeywordCode eTokenCode; 

	for(ucTokenCounter = 0; ucTokenNr > ucTokenCounter; ucTokenCounter++) { 

		psCurrentToken = &asToken[ucTokenCounter]; 

		if(OK == eStringToKeyword(psCurrentToken->uValue.pcString, &eTokenCode)) { 

			psCurrentToken->eType = KEYWORD; 
			psCurrentToken->uValue.eKeyword = eTokenCode;

		} 
		else if(OK == eHexStringToUInt(psCurrentToken->uValue.pcString, &uiTokenNumber)) { 

			psCurrentToken->eType = NUMBER; 
			psCurrentToken->uValue.uiNumber = uiTokenNumber; 
		} 
		else { 

			psCurrentToken->eType = STRING; 

		} 
	}
}

void DecodeMsg(char *pcString) { 
	
	ucTokenNr = ucFindTokensInString(pcString);  
	ReplaceCharactersInString(pcString, DELIMITER_CHARACTER, NULL);  
	DecodeTokens(); 
}

int main(void){
	
	char cTestMessage[] = "load 0x20 kot";
	
	DecodeMsg(cTestMessage);
	
	while(1){
	}
}
