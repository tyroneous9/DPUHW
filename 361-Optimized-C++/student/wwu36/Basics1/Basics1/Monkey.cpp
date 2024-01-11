#include <string.h>
#include "Monkey.h"
int Monkey::numStringsCreated = 0;
int Monkey::numStringsDestroyed = 0;

Monkey::Monkey() {
	x = 878;
	y = 979;
	const char* str = "This string was initialized by a default constructor!";
	size_t len = strlen(str) + 1;
	pStatus = new char[len];
	strcpy_s(pStatus, len, str);
	Monkey::numStringsCreated += 1;
}

Monkey::Monkey(Monkey const &r) {
	this->x = r.x;
	this->y = r.y;
	size_t len = strlen(r.pStatus) + 1;
	this->pStatus = new char[len];
	strcpy_s(this->pStatus, len, r.pStatus);
	Monkey::numStringsCreated += 1;
}

Monkey &Monkey::operator = (Monkey const &r) {
	if (this != &r) {
		this->x = r.x;
		this->y = r.y;
		size_t len = strlen(r.pStatus) + 1;
		delete this->pStatus;
		Monkey::numStringsDestroyed += 1;
		this->pStatus = new char[len];
		strcpy_s(this->pStatus, len, r.pStatus);
		Monkey::numStringsCreated += 1;
	}
	return *this;
}

Monkey::Monkey(int x, int y) {
	this->x = x;
	this->y = y;
	const char* str = "ThIs tring was initilizxd by a clever user!";
	size_t len = strlen(str) + 1;
	pStatus = new char[len];
	strcpy_s(pStatus, len, str);
	Monkey::numStringsCreated += 1;
}

Monkey::~Monkey() {
	delete pStatus;
	Monkey::numStringsDestroyed += 1;
}

int Monkey::getX()
{
	return this->x;
}

int Monkey::getY()
{
	return this->y;
}

char *Monkey::getStatus()
{
	return this->pStatus;
};

void Monkey::printStatus()
{
	Trace::out("Monkey (Status): %s\n", this->pStatus);
}


//---  End of File ---
