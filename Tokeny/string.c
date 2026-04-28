#include "string.h"
#include "dekodowanie.h"
#define NULL 0x00

enum CompResult eCompareString(char pcStr1[], char pcStr2[]) {
	
	unsigned char ucCharLocation;
	
	for(ucCharLocation = 0; pcStr1[ucCharLocation] != NULL; ucCharLocation++) {  //TUTAJ 2
		if(pcStr1[ucCharLocation] != pcStr2[ucCharLocation]) {
			return DIFFERENT;
		}
	}
	if(pcStr1[ucCharLocation] == pcStr2[ucCharLocation]) {
		return EQUAL;
	} else {
		return DIFFERENT;
	}
}

enum Result eHexStringToUInt(char pcStr[],unsigned int *puiValue){
	
	unsigned char ucCharacterCounter;
	unsigned char ucCurrentCharacter;
	*puiValue=0;
	
	if((pcStr[0]!='0') || (pcStr[1]!='x') || (pcStr[2]==NULL)){ //TUTAJ 3
		return ERROR;
	}
	for(ucCharacterCounter=2; pcStr[ucCharacterCounter] != NULL; ucCharacterCounter++){ // TUTAJ
		ucCurrentCharacter = pcStr[ucCharacterCounter];
		if(ucCharacterCounter==6){
			return ERROR;
		}
		*puiValue = *puiValue <<4;
		if((ucCurrentCharacter <= '9') && (ucCurrentCharacter >= '0')){
			ucCurrentCharacter = ucCurrentCharacter-'0';
		}
		else if((ucCurrentCharacter <= 'F') && (ucCurrentCharacter >= 'A')){
			ucCurrentCharacter = ucCurrentCharacter-'A'+10;
		}
		else{
			return ERROR;
		}
		*puiValue = (*puiValue) | ucCurrentCharacter;
	}
	return OK;
}

void ReplaceCharactersInString(char pcString[], char cOldChar, char cNewChar) {
	
	unsigned char ucCharLocation;
	
	for(ucCharLocation = 0; pcString[ucCharLocation] != NULL; ucCharLocation++) {
		if(pcString[ucCharLocation] == cOldChar) {
			pcString[ucCharLocation] = cNewChar;
		}
	}
}
