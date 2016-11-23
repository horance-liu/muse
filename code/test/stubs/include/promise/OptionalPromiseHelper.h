#ifndef HAE0F4466_B0F7_4E56_8BB1_7E355BB97FB4
#define HAE0F4466_B0F7_4E56_8BB1_7E355BB97FB4

#include <muse/promise/OptionalPromise.h>

MUSE_NS_BEGIN

template<typename ...PROMISES> struct OptionalPromiseHelper;

template<typename PROMISE, typename ...OTHERS>
struct OptionalPromiseHelper<PROMISE, OTHERS...> : OptionalPromiseHelper<OTHERS...>
{
    OptionalPromiseHelper(const PROMISE& p, OTHERS... others)
    : OptionalPromiseHelper<OTHERS...>(others...), promise(p)
    {
        this->addPromise(promise);
    }

private:
    PROMISE promise;
};

template<>
struct OptionalPromiseHelper<> : OptionalPromise
{
};

template<typename ...PROMISES>
OptionalPromiseHelper<PROMISES...> createOptionalPromise(PROMISES ... promises)
{
    return OptionalPromiseHelper<PROMISES...>(promises...);
}

MUSE_NS_END

#define __optional(...)  createOptionalPromise(__VA_ARGS__)

#endif
