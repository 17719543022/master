#pragma once
#include "Poco\Thread.h"
#include "Poco\Runnable.h"

class ProgressBar : public Poco::Runnable
{
public:
	ProgressBar(void);
	~ProgressBar(void);

	void show();
	void stop();

protected:
	virtual void run();
private:
	bool _bStop;
	Poco::Thread th;
};

