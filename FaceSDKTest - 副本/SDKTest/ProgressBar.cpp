#include "stdafx.h"
#include "ProgressBar.h"
#include <iostream>

#ifdef WIN32
#include <Windows.h>
#endif

ProgressBar::ProgressBar(void)
{
}


ProgressBar::~ProgressBar(void)
{
	th.join();
}

void ProgressBar::show()
{
	if(th.isRunning())
	{
		return;
	}
	
	_bStop = false;
	th.start(*this);
}

void ProgressBar::stop()
{
	_bStop = true;
	th.join();
}

void ProgressBar::run()
{
	int num = 0;
	bool bFlag = true;

	while (!_bStop)
	{
		if(num < 10)
		{
			if(bFlag)
			{
				printf("=");
			}
			else
			{
				printf(">");
			}
			num++;
		}
		else
		{
			num = 0;
			printf("\r");
			bFlag = !bFlag;
		}
		Sleep(1000);
	}
}
