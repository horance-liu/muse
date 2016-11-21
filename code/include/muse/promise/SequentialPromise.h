#ifndef HC626219A_60D0_4BE2_A8BA_6C8F164C301C
#define HC626219A_60D0_4BE2_A8BA_6C8F164C301C

#include <muse/promise/Promise.h>
#include <initializer_list>
#include <list>

MUSE_NS_BEGIN

struct SequentialPromise : Promise
{
    explicit SequentialPromise(std::initializer_list<Promise*>);

private:
    OVERRIDE(void start());
    OVERRIDE(void stop());
    OVERRIDE(void onEvent(const Event&));
    OVERRIDE(Result evaluate() const);

private:
    void doStop();

    void processEvent(const Event&);
    void onCurrentFailed();
    void onCurrentSuccess();
    bool isFinish() const;
    bool atLast() const;
    bool gotoNext();
    Promise& current();

private:
    using Promises = std::list<Promise*>;
    std::list<Promise*> promises;
    Promises::iterator currentPromise;
    Result result{Result::UNKNOWN};
};

MUSE_NS_END

#endif
