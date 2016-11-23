#ifndef HFB8BFAE7_6E9E_46ED_81BA_F16B8CADE558
#define HFB8BFAE7_6E9E_46ED_81BA_F16B8CADE558

#include <muse/promise/SequentialPromise.h>

MUSE_NS_BEGIN

template<typename ...PROMISES> struct SequentialPromiseHelper;

template<typename PROMISE, typename ...OTHERS>
struct SequentialPromiseHelper<PROMISE, OTHERS...> : SequentialPromiseHelper<OTHERS...>
{
    SequentialPromiseHelper(const PROMISE& p, OTHERS... others)
    : SequentialPromiseHelper<OTHERS...>(others...), promise(p)
    {
        this->addPromise(promise);
    }

private:
    PROMISE promise;
};

template<typename PROMISE>
struct SequentialPromiseHelper<PROMISE> : SequentialPromise
{
    SequentialPromiseHelper(const PROMISE& p)
    : promise(p)
    {
        this->addPromise(promise);
        this->reset();
    }

private:
    PROMISE promise;
};

template<typename ...PROMISES>
SequentialPromiseHelper<PROMISES...> createSequentialPromise(PROMISES ... promises)
{
    return SequentialPromiseHelper<PROMISES...>(promises...);
}

MUSE_NS_END

#define __seq(...)  createSequentialPromise(__VA_ARGS__)

#endif
