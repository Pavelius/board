#include "main.h"

int main()
{
	auto u1 = gobject::create(unit_type, "cavalry");
	u1->set("name", "���������");
	u1->set("text", "������ ���� ����������� � �����.");
	auto u2 = gobject::create(player_type);
}