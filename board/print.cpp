#include "main.h"
#include "grammar.h"

using namespace logs;

static void msg(gender_s gender, char* result, const char* text_male, const char* text_female, const char* text_pluar) {
	if(gender == Female) {
		if(text_female)
			zcpy(result, text_female);
	} else {
		if(text_male)
			zcpy(result, text_male);
	}
}

void driver::parseidentifier(char* result, const char* result_max, const char* identifier) {
	if(strcmp(identifier, "�����") == 0)
		zcpy(result, name);
	else if(strcmp(identifier, "�����") == 0)
		grammar::of(result, name);
	else if(strcmp(identifier, "���") == 0)
		msg(gender, result, "��", identifier, "���");
	else if(strcmp(identifier, "�") == 0)
		msg(gender, result, "", identifier, "�");
	else if(strcmp(identifier, "��") == 0)
		msg(gender, result, "", identifier, "��");
	else if(strcmp(identifier, "���") == 0)
		msg(gender, result, "��", identifier, "���");
	else if(strcmp(identifier, "��") == 0)
		msg(gender, result, "���", identifier, "��");
	else if(strcmp(identifier, "���") == 0)
		msg(gender, result, "����", identifier, "���");
	else {
		zcat(result, "[-");
		zcat(result, identifier);
		zcat(result, "]");
	}
}