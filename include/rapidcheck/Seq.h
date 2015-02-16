#pragma once

#include <type_traits>

#include "rapidcheck/Maybe.h"
#include "rapidcheck/Traits.h"

namespace rc {

//! This class implements lazy sequences, or streams if you will. This is
//! mainly used by RapidCheck to implement shrinking where it is not feasible to
//! materialize all of the possible shrinks at once. In particular, a Seq may be
//! infinite although that's not appropriate for shrinking, of course!
//!
//! A `Seq` object is constructed either as an empty sequence using the default
//! constructor or with an implementation object that implements the actual
//! sequence.
//!
//! The implementation class must meet the following requirements:
//!   - It must provide a `Maybe<T> operator()()` (i.e. it must be a functor)
//!     which returns the next value or nothing if there are no more valeus.
//!   - It must have a copy constructor that produces a semantically identical
//!     copy. This means that it should provide equal values to the original.
//!
//! However, unless you have a reason to create your own implementation class,
//! you should just use the provided combinators in the `rc::seq` namespace to
//! construct your `Seq`s.
template<typename T>
class Seq
{
    //! Creates a new `Seq` using the implementation class specificed by the
    //! type parameter constructed by forwarding the given arguments.
    template<typename Impl, typename ...Args>
    friend Seq<typename std::result_of<Impl()>::type::ValueType>
    makeSeq(Args &&...args);

public:
    //! The type of the values of this `Seq`.
    typedef T ValueType;

    //! Constructs an empty `Seq` that has no values.
    Seq() = default;

    //! Constructs a `Seq` from the given implementation object.
    template<typename Impl,
             typename = typename std::enable_if<
                 !std::is_same<Decay<Impl>, Seq>::value>::type>
    Seq(Impl &&impl);

    //! Returns the next value.
    Maybe<T> next();

    Seq(const Seq &other);
    Seq &operator=(const Seq &rhs);
    Seq(Seq &&other);
    Seq &operator=(Seq &&rhs);

private:
    class ISeqImpl;

    template<typename Impl>
    class SeqImpl;

    std::unique_ptr<ISeqImpl> m_impl;
};

//! Two `Seq`s are considered equal if they return equal values. Note that this
//! requires either copying or moving of the `Seq`s.
template<typename A, typename B>
bool operator==(Seq<A> lhs, Seq<B> rhs);

template<typename A, typename B>
bool operator!=(Seq<A> lhs, Seq<B> rhs);

} // namespace rc

#include "Seq.hpp"