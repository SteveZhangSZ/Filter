namespace szFilter{
    typedef decltype(sizeof(0)) size_type;

    template<bool allTypesSeen, bool PredCondition, template<class...> class HoldsTypes>
    struct filterHelper{ //handles <true,true>
        template<template<class> class, size_type, class T, class... Ts>
        using type = HoldsTypes<Ts...,T>;
    };
    template<template<class...> class HoldsTypes>
    struct filterHelper<true,false,HoldsTypes>{
        template<template<class> class, size_type, class, class... Ts>
        using type = HoldsTypes<Ts...>;
    };
    template<template<class...> class HoldsTypes>
    struct filterHelper<false,false,HoldsTypes>;

    template<template<class...> class HoldsTypes>
    struct filterHelper<false,true,HoldsTypes>{
        template<template<class> class Pred, size_type numTypes, class T, class U, class... Ts>
        using type = typename filterHelper<(numTypes - 1) == 0, Pred<U>::value,HoldsTypes>::template type<Pred,numTypes - 1, U, Ts...,T>;
    };
    template<template<class...> class HoldsTypes>
    struct filterHelper<false,false,HoldsTypes>{
        template<template<class> class Pred, size_type numTypes, class, class U, class... Ts>
        using type = typename filterHelper<(numTypes - 1) == 0, Pred<U>::value,HoldsTypes>::template type<Pred,numTypes - 1, U, Ts...>; //No T appended
    };
    template<template<class> class Pred, template<class...> class HoldsTypes, class... Ts>
    using filter = typename filterHelper<(sizeof...(Ts) == 0),false,HoldsTypes>::template type<Pred, sizeof...(Ts), void, Ts...>;

    template<template<class> class Pred, class... Ts> struct filterWithTypeList;

    template<template<class> class Pred, template<class...> class HoldsTypes, class... Ts> struct filterWithTypeList<Pred, HoldsTypes<Ts...>>{
        using type = filter<Pred,HoldsTypes,Ts...>;
    };

}