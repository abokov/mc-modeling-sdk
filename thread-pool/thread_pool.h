#ifndef __MC_THREAD_POOL_INC__
#define __MC_THREAD_POOL_INC__ 1


class McTask {
public:
    McTask(void);
    virtual ~McTask();
    virtual void McRun(void)=0;
    virtual void McGetStatus(std::string &s)=0;
};





#endif
