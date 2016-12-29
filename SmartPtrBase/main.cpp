#include "SmartPtrBase.h"
#include <iostream>
using namespace std;
class Wombat{
public:
	int dig(){ cout << "Digging..." << endl; return 1; }
	int eat() const { cout << "Eatting..." << endl; return 5; }
	int move(int op){ cout << "Moving..." << endl; return 9; }

	/*data member*/
	int _data = 999;
	int* _pdata = &_data;

};

typedef int(Wombat::*PWMF)();
typedef int(Wombat::*PWMFC)() const;
typedef int(Wombat::*PWMF1)(int);

/*pointer to data member*/
typedef int Wombat::*PD;
typedef int* (Wombat::*PPD);

void main()
{
	SP<Wombat> pw = new Wombat;
	PWMF pmf = &Wombat::dig;
	(pw->*pmf)();//Digging...

	PWMFC pmfc = &Wombat::eat;
	(pw->*pmfc)();//Eatting...

	PWMF1 pmf1 = &Wombat::move;
	(pw->*pmf1)(2);//Moving...

	PD pd = &Wombat::_data;
	cout << (pw->*pd) << endl;//999

	PPD ppd = &Wombat::_pdata;
	cout << *(pw->*ppd) << endl;//999

	system("pause");
	_CrtCheckMemory();
	return;
}