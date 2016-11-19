#include <muse/fact/CollisionFact.h>
#include <muse/validator/FactValidator.h>
#include <muse/validator/NotValidator.h>
#include <muse/event/Event.h>
#include <muse/base/Log.h>

USING_MUSE_NS;

int main(int argc, char** argv)
{
    Result result;
    CollisionFact fact;
    FactValidator validator{fact};
    NotValidator notValiator(validator);

    Validator& v = notValiator;

    v.onEvent(Event{COLLISION, 0.0});

    result = v.evaluate();
    INFO_LOG("result = %d", result);

    v.start();
    v.onEvent(Event{NOTHING, 0.0});

    v.stop();
    v.onEvent(Event{COLLISION, 0.0});

    result = v.evaluate();
    INFO_LOG("result = %d", result);

    return 0;
}
