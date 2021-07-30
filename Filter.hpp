#ifndef SZFILTER
#define SZFILTER
namespace szFilter{
    namespace impl{
        typedef decltype(sizeof(0)) size_type;

        template<bool AllTypesChecked, bool PredCondition>
        struct filterHelper{ //handles <true,true>
            template<template<class> class, template<class...> class HoldsTypes, size_type, class T, class... Ts>
            using type = HoldsTypes<Ts...,T>;
        };
        template<>
        struct filterHelper<true,false>{
            template<template<class> class, template<class...> class HoldsTypes, size_type, class, class... Ts>
            using type = HoldsTypes<Ts...>;
        };
        template<>
        struct filterHelper<false,false>;

        template<>
        struct filterHelper<false,true>{
            template<template<class> class Pred, template<class...> class HoldsTypes,size_type numTypes, class T, class U, class... Ts>
            using type = typename filterHelper<(numTypes - 1) == 0, Pred<U>::value>::template type<Pred,HoldsTypes,numTypes - 1, U, Ts...,T>;
        };
        template<>
        struct filterHelper<false,false>{
            template<template<class> class Pred, template<class...> class HoldsTypes,size_type numTypes, class, class U, class... Ts>
            using type = typename filterHelper<(numTypes - 1) == 0, Pred<U>::value>::template type<Pred,HoldsTypes,numTypes - 1, U, Ts...>; //No T appended
        };
    }
    template<template<class> class Pred, template<class...> class HoldsTypes, class... Ts>
    using filter = typename impl::filterHelper<(sizeof...(Ts) == 0),false>::template type<Pred,HoldsTypes, sizeof...(Ts), void, Ts...>;

    template<template<class> class Pred, class... Ts> struct filterWithTypeList;

    template<template<class> class Pred, template<class...> class HoldsTypes, class... Ts> struct filterWithTypeList<Pred, HoldsTypes<Ts...>>{
        using type = filter<Pred,HoldsTypes,Ts...>;
    };
}
#endif