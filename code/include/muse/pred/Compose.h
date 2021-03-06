#ifndef H942BC4AF_B66C_437E_8834_7D2220FAF1F9
#define H942BC4AF_B66C_437E_8834_7D2220FAF1F9

#include <muse/muse.h>
#include <tuple>

MUSE_NS_BEGIN

template<typename ... Fs>
struct Compose
{
    Compose(const Fs& ... fs) : functions(fs...) {}
    Compose(Fs&& ... fs) : functions(std::move(fs) ...) {}

    template<typename ... Ts>
    auto operator()(Ts&& ... ts) const
    {
        return apply(std::integral_constant<size_t, 0>{}, std::forward<Ts>(ts) ...);
    }

    std::string info() const
    {
        return getInfoOf(std::integral_constant<size_t, 0>{});
    }

private:
    constexpr static size_t size = sizeof ... (Fs) - 1;
    template<size_t N, typename ... Ts>
    auto apply(std::integral_constant<size_t, N>, Ts&& ... ts) const
    {
        return apply( std::integral_constant<size_t, N + 1>{}
                    , std::get<N>(functions)(std::forward<Ts>(ts)...));
    }

    template<typename ... Ts>
    auto apply(std::integral_constant<size_t, size>, Ts&& ... ts) const
    {
        return std::get<size>(functions)(std::forward<Ts>(ts)...);
    }

    template<size_t N>
    std::string getInfoOf(std::integral_constant<size_t, N>) const
    {
        return std::get<N>(functions).info() + std::string(" ") + getInfoOf(std::integral_constant<size_t, N + 1>{});
    }

    std::string getInfoOf(std::integral_constant<size_t, size>) const
    {
        return std::get<size>(functions).info();
    }

private:
    std::tuple<Fs ...> functions;
};

template<typename ... Fs>
auto make_compose(Fs&& ... fs)
{
    return Compose<std::decay_t<Fs> ...>(std::forward<Fs>(fs) ...);
}

MUSE_NS_END

#define __compose(...)  ::MUSE_NS::make_compose(__VA_ARGS__)

#endif
