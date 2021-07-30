# Filter

## Introduction
`szFilter::filter` allows the user to remove types from a list of types that fail to satisfy a condition. It accomplishes this by recursively defining type aliases until it has checked all types, meaning it also doesn't instantiate a new struct with each step in the recursion. 

This code is inspired by the problem described in Arthur O'Dwyer's post about [filtering types](https://quuxplusone.github.io/blog/2018/07/23/metafilter/).
## Usage
The alias, inside `namespace szFilter`, is:
```cpp
template<template<class> class Pred, template<class...> class HoldsTypes, class... Ts>
using filter = typename filterHelper<(sizeof...(Ts) == 0),false>::template type<Pred,HoldsTypes, sizeof...(Ts), void, Ts...>;
```
`Pred` is a class whose parameter list is a single class and has a public static member constant bool `value`. `HoldsTypes` is a class whose template parameter list takes a variable number of types. The filtered types will be stored in there. `Ts...` is the list of types from which types failing to satisfy `Pred` will be removed.

Multiple usage of `szFilter::filter`, with different choices for `Pred`, `HoldTypes`, and `Ts...`, will not result in new instantiations since these are parameters for the type alias only.

Should the types be provided inside a class possessing a template parameter list taking a variable number of types, then `szFilter::filterWithTypeList` can be used:
```cpp
template<template<class> class Pred, template<class...> class HoldsTypes, class... Ts> 
struct filterWithTypeList<Pred, HoldsTypes<Ts...>>{
    using type = filter<Pred,HoldsTypes,Ts...>;
};
```

Examples are provided in `main.cpp`.