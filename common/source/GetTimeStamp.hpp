#ifndef _COMMON_GETTIMESTAMP_HPP
#define _COMMON_GETTIMESTAMP_HPP

struct TimeStamp
{
	int year;	
	int month;
	int day;
	int secondsToNext;
};

class GetTimeStamp
{
public:
	struct TaskReturn
	{
		TimeStamp stamp;
		int errCode;
	};
	GetTimeStamp(const std::string& url, const std;:string& uid);
	
	bool done();
	
	TimeStamp get();
private:
	lang::Mutex m_mutex;
	bool m_started;
	TaskReturn m_taskRet;
	
	lang::Thread m_thread;
};

#endif