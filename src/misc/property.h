#ifndef _PROPERTY_H_
#define _PROPERTY_H_

#include <iostream>

#define CALL_SETTER(propertyp, value) (((propertyp->owner)->*(propertyp->setter))((value)))
#define CALL_GETTER(propertyp) (((propertyp->owner)->*(propertyp->getter))())

template <typename ClassType, typename Type>
class Property
{
    public:
        using SetMethod = void (ClassType::*)(const Type &);
        using GetMethod = const Type &(ClassType::*)(void) const;

        Property(ClassType *owner, SetMethod setter, GetMethod getter);

        operator const Type &(void) const;
        const Type &operator * (void) const;
        const Type &operator = (const Type &value);
        const Type &operator = (const Property<ClassType, Type> &value);
        const Type *operator -> (void) const;

#define DEFINE_OP(op)                                                   \
    const Type &operator op##= (const Type &value)                      \
    {                                                                   \
        CALL_SETTER(this, CALL_GETTER(this) op value);                  \
        return CALL_GETTER(this);                                       \
    }                                                                   \
    const Type &operator op##= (const Property<ClassType, Type> &value) \
    {                                                                   \
        CALL_SETTER(this, CALL_GETTER(this) op *value);                 \
        return CALL_GETTER(this);                                       \
    }

        DEFINE_OP(+);
        DEFINE_OP(-);
        DEFINE_OP(/);
        DEFINE_OP(%);
        DEFINE_OP(*);
        DEFINE_OP(^);
        DEFINE_OP(|);
        DEFINE_OP(&);
        DEFINE_OP(<<);
        DEFINE_OP(>>);
        const Type &operator ~ (void) const;
#undef DEFINE_OP

        Property(const Property &) = delete;
        Property(Property &&) = delete;

    private:
        ClassType *const owner = nullptr;
        const SetMethod setter = nullptr;
        const GetMethod getter = nullptr;
};

template <typename ClassType, typename Type>
Property<ClassType, Type>::Property(ClassType *owner,
                                    SetMethod setter, GetMethod getter)
    : owner(owner), setter(setter), getter(getter) {}

template <typename ClassType, typename Type>
Property<ClassType, Type>::operator const Type &(void) const
{
    return CALL_GETTER(this);
}

template <typename ClassType, typename Type>
const Type &Property<ClassType, Type>::operator * (void) const
{
    return CALL_GETTER(this);
}

template <typename ClassType, typename Type>
const Type &Property<ClassType, Type>::operator = (const Type &value)
{
    CALL_SETTER(this, value);

    return CALL_GETTER(this);
}

template <typename ClassType, typename Type>
const Type &Property<ClassType, Type>::operator = (const Property<ClassType, Type> &value)
{
    CALL_SETTER(this, *value);

    return CALL_GETTER(this);
}

template <typename ClassType, typename Type>
const Type *Property<ClassType, Type>::operator -> (void) const
{
    return &CALL_GETTER(this);
}

template <typename ClassType, typename Type>
const Type &Property<ClassType, Type>::operator ~ (void) const
{
    return ~ CALL_GETTER(this);
}

#undef CALL_SETTER
#undef CALL_GETTER

#define DEFINE_LOGIC(op)                                                        \
template <typename ClassType, typename Type>                                    \
bool operator op (const Property<ClassType, Type> &property1,                   \
                  const Property<ClassType, Type> &property2)                   \
{                                                                               \
    return *property1 op *property2;                                            \
}                                                                               \
template <typename ClassType, typename Type>                                    \
bool operator op (const Property<ClassType, Type> &property, const Type &value) \
{                                                                               \
    return *property op value;                                                  \
}                                                                               \
template <typename ClassType, typename Type>                                    \
bool operator op (const Type &value, const Property<ClassType, Type> &property) \
{                                                                               \
    return value op *property;                                                  \
}

DEFINE_LOGIC(==)
DEFINE_LOGIC(!=)
DEFINE_LOGIC(>)
DEFINE_LOGIC(>=)
DEFINE_LOGIC(<)
DEFINE_LOGIC(<=)
DEFINE_LOGIC(&&)
DEFINE_LOGIC(||)
DEFINE_LOGIC(^)

#undef DEFINE_LOGIC

#define DEFINE_ARITH(op)                                                        \
template <typename ClassType, typename Type>                                    \
Type operator op (const Property<ClassType, Type> &property1,                   \
                  const Property<ClassType, Type> &property2)                   \
{                                                                               \
    return *property1 op *property2;                                            \
}                                                                               \
template <typename ClassType, typename Type>                                    \
Type operator op (const Property<ClassType, Type> &property, const Type &value) \
{                                                                               \
    return *property op value;                                                  \
}                                                                               \
template <typename ClassType, typename Type>                                    \
Type operator op (const Type &value, const Property<ClassType, Type> &property) \
{                                                                               \
    return value op *property;                                                  \
}

DEFINE_ARITH(+)
DEFINE_ARITH(-)
DEFINE_ARITH(/)
DEFINE_ARITH(%)
DEFINE_ARITH(*)

#undef DEFINE_ARITH

template <typename ClassType, typename Type>
std::ostream &operator << (std::ostream& stream, const Property<ClassType, Type> &property)
{
    return stream << *property;
}

#define DEFAULT_GETTER(Type, name, field) \
        const Type &get##name(void) const { return this->field; }
#define DEFAULT_SETTER(Type, name, field) \
        void set##name(const Type &value) { this->field = value; }
#define DEFAULT_SG(Type, name, field) DEFAULT_SETTER(Type, name, field); \
                                      DEFAULT_GETTER(Type, name, field)

#endif

