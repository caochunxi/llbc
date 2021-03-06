// The MIT License (MIT)

// Copyright (c) 2013 lailongwei<lailongwei@126.com>
// 
// Permission is hereby granted, free of charge, to any person obtaining a copy of 
// this software and associated documentation files (the "Software"), to deal in 
// the Software without restriction, including without limitation the rights to 
// use, copy, modify, merge, publish, distribute, sublicense, and/or sell copies of 
// the Software, and to permit persons to whom the Software is furnished to do so, 
// subject to the following conditions:
// 
// The above copyright notice and this permission notice shall be included in all 
// copies or substantial portions of the Software.
// 
// THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR 
// IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS 
// FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR 
// COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER 
// IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN 
// CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.

#include "PoolObjectReflection.h"
#include "PoolObjectReflectionBase.h"

#ifdef __LLBC_CORE_OBJECT_POOL_POOL_OBJECT_REFLECTION_H__

__LLBC_NS_BEGIN

#define __LLBC_CORE_OBJECT_POOL_POOL_OBJECT_INHERIT_DETECT_OBJ \
    std::is_base_of<LLBC_PoolObjectReflectionBase, ObjectType> {}

#define __LLBC_CORE_OBJECT_POOL_POOL_OBJECT_INHERIT_DETECT_RESULT \
    std::is_base_of<LLBC_PoolObjectReflectionBase, ObjectType>::value

template <typename ObjectType>
LLBC_FORCE_INLINE bool LLBC_PoolObjectReflection::IsSupportedPoolObjectReflection()
{
    return IsSupportedPoolObjectReflectionInl<ObjectType>(NULL);
}

template <typename ObjectType>
bool LLBC_PoolObjectReflection::IsSupportedPoolObjectReflectionInl(__LLBC_CORE_OBJECT_POOL_POOL_OBJECT_REFLECTION_DETECT_TYPE_DEF *)
{
    return true;
}

template <typename ObjectType>
bool LLBC_PoolObjectReflection::IsSupportedPoolObjectReflectionInl(...)
{
    return __LLBC_CORE_OBJECT_POOL_POOL_OBJECT_INHERIT_DETECT_RESULT;
}

template <typename ObjectType>
LLBC_FORCE_INLINE void LLBC_PoolObjectReflection::MarkPoolObject(ObjectType *&obj,
                                                                 LLBC_IObjectPoolInst *poolInst)
{
    MarkPoolObjectInl<ObjectType>(obj, poolInst, NULL);
}

template <typename ObjectType>
void LLBC_PoolObjectReflection::MarkPoolObjectInl(ObjectType *&obj,
                                                  LLBC_IObjectPoolInst *poolInst,
                                                  __LLBC_CORE_OBJECT_POOL_POOL_OBJECT_REFLECTION_DETECT_TYPE_DEF *)
{
    obj->MarkPoolObject(*poolInst);
}

template <typename ObjectType>
void LLBC_PoolObjectReflection::MarkPoolObjectInl(ObjectType *&obj,
                                                  LLBC_IObjectPoolInst *poolInst,
                                                  ...)
{
    MarkPoolObjectInl<ObjectType>(obj, poolInst, __LLBC_CORE_OBJECT_POOL_POOL_OBJECT_INHERIT_DETECT_OBJ);
}

template <typename ObjectType>
void LLBC_PoolObjectReflection::MarkPoolObjectInl(ObjectType *&obj,
                                                  LLBC_IObjectPoolInst *poolInst,
                                                  __LLBC_CORE_OBJECT_POOL_POOL_OBJECT_INHERIT_DETECT_TRUE)
{
    obj->MarkPoolObject(*poolInst);
}

template <typename ObjectType>
void LLBC_PoolObjectReflection::MarkPoolObjectInl(ObjectType *&obj,
                                                  LLBC_IObjectPoolInst *poolInst,
                                                  __LLBC_CORE_OBJECT_POOL_POOL_OBJECT_INHERIT_DETECT_FALSE)
{
    // Do nothing.
}

template <typename ObjectType>
LLBC_FORCE_INLINE bool LLBC_PoolObjectReflection::IsPoolObject(ObjectType *&obj)
{
    return IsPoolObjectInl<ObjectType>(obj, NULL);
}

template <typename ObjectType>
bool LLBC_PoolObjectReflection::IsPoolObjectInl(ObjectType *&obj,
                                                __LLBC_CORE_OBJECT_POOL_POOL_OBJECT_REFLECTION_DETECT_TYPE_DEF *)
{
    return obj->IsPoolObject();
}

template <typename ObjectType>
bool LLBC_PoolObjectReflection::IsPoolObjectInl(ObjectType *&obj,
                                                ...)
{
    return __LLBC_CORE_OBJECT_POOL_POOL_OBJECT_INHERIT_DETECT_RESULT;
}

template <typename ObjectType>
LLBC_FORCE_INLINE LLBC_IObjectPoolInst *LLBC_PoolObjectReflection::GetPoolInst(ObjectType *&obj)
{
    return GetPoolInstInl<ObjectType>(obj, NULL);
}

template <typename ObjectType>
LLBC_IObjectPoolInst *LLBC_PoolObjectReflection::GetPoolInstInl(ObjectType *&obj,
                                                                __LLBC_CORE_OBJECT_POOL_POOL_OBJECT_REFLECTION_DETECT_TYPE_DEF *)
{
    return obj->GetPoolInst();
}

template <typename ObjectType>
LLBC_IObjectPoolInst *LLBC_PoolObjectReflection::GetPoolInstInl(ObjectType *&obj,
                                                                ...)
{
    return GetPoolInstInl<ObjectType>(obj, __LLBC_CORE_OBJECT_POOL_POOL_OBJECT_INHERIT_DETECT_OBJ);
}

template <typename ObjectType>
LLBC_IObjectPoolInst *LLBC_PoolObjectReflection::GetPoolInstInl(ObjectType *&obj,
                                                                __LLBC_CORE_OBJECT_POOL_POOL_OBJECT_INHERIT_DETECT_TRUE)
{
    return obj->GetPoolInst();
}

template <typename ObjectType>
LLBC_IObjectPoolInst *LLBC_PoolObjectReflection::GetPoolInstInl(ObjectType *&obj,
                                                                __LLBC_CORE_OBJECT_POOL_POOL_OBJECT_INHERIT_DETECT_FALSE)
{
    return NULL;
}

template <typename ObjectType>
LLBC_FORCE_INLINE void LLBC_PoolObjectReflection::GiveBackToPool(ObjectType *&obj)
{
    GiveBackToPoolInl<ObjectType>(obj, NULL);
}

template <typename ObjectType>
void LLBC_PoolObjectReflection::GiveBackToPoolInl(ObjectType *&obj,
                                                  __LLBC_CORE_OBJECT_POOL_POOL_OBJECT_REFLECTION_DETECT_TYPE_DEF *)
{
    obj->GiveBackToPool();
}

template <typename ObjectType>
void LLBC_PoolObjectReflection::GiveBackToPoolInl(ObjectType *&obj,
                                                  ...)
{
    GiveBackToPoolInl<ObjectType>(obj, __LLBC_CORE_OBJECT_POOL_POOL_OBJECT_INHERIT_DETECT_OBJ);
}

template <typename ObjectType>
void LLBC_PoolObjectReflection::GiveBackToPoolInl(ObjectType *&obj,
                                                  __LLBC_CORE_OBJECT_POOL_POOL_OBJECT_INHERIT_DETECT_TRUE)
{
    obj->GiveBackToPool();
}

template <typename ObjectType>
void LLBC_PoolObjectReflection::GiveBackToPoolInl(ObjectType *&obj,
                                                  __LLBC_CORE_OBJECT_POOL_POOL_OBJECT_INHERIT_DETECT_FALSE)
{
    // Do nothing.
}

template <typename ObjectType>
void LLBC_PoolObjectReflection::Recycle(ObjectType *obj)
{
    RecycleInl<ObjectType>(obj, NULL);
}

template <typename ObjectType>
void LLBC_PoolObjectReflection::RecycleX(ObjectType *&obj)
{
    RecycleXInl<ObjectType>(obj, NULL);
}

template <typename ObjectType>
void LLBC_PoolObjectReflection::RecycleInl(ObjectType *&obj,
                                           __LLBC_CORE_OBJECT_POOL_POOL_OBJECT_REFLECTION_DETECT_TYPE_DEF *)
{
    if (obj->IsPoolObject())
        obj->GiveBackToPool();
    else
        LLBC_Delete(obj);
}

template <typename ObjectType>
void LLBC_PoolObjectReflection::RecycleInl(ObjectType *&obj,
                                           ...)
{
    RecycleInl<ObjectType>(obj, __LLBC_CORE_OBJECT_POOL_POOL_OBJECT_INHERIT_DETECT_OBJ);
}

template <typename ObjectType>
void LLBC_PoolObjectReflection::RecycleInl(ObjectType *&obj,
                                           __LLBC_CORE_OBJECT_POOL_POOL_OBJECT_INHERIT_DETECT_TRUE)
{
    if (obj->IsPoolObject())
        obj->GiveBackToPool();
    else
        LLBC_Delete(obj);
}

template <typename ObjectType>
void LLBC_PoolObjectReflection::RecycleInl(ObjectType *&obj, 
                                           __LLBC_CORE_OBJECT_POOL_POOL_OBJECT_INHERIT_DETECT_FALSE)
{
    bool supportedReflection = IsSupportedPoolObjectReflection<ObjectType>();
    LLBC_Delete(obj);
}

template <typename ObjectType>
void LLBC_PoolObjectReflection::RecycleXInl(ObjectType *&obj,
                                            __LLBC_CORE_OBJECT_POOL_POOL_OBJECT_REFLECTION_DETECT_TYPE_DEF *)
{
    if (LIKELY(obj))
    {
        if (obj->IsPoolObject())
            obj->GiveBackToPool();
        else
            LLBC_Delete(obj);

        obj = NULL;
    }
}

template <typename ObjectType>
void LLBC_PoolObjectReflection::RecycleXInl(ObjectType *&obj,
                                            ...)
{
    RecycleXInl<ObjectType>(obj, __LLBC_CORE_OBJECT_POOL_POOL_OBJECT_INHERIT_DETECT_OBJ);
}

template <typename ObjectType>
void LLBC_PoolObjectReflection::RecycleXInl(ObjectType *&obj, 
                                            __LLBC_CORE_OBJECT_POOL_POOL_OBJECT_INHERIT_DETECT_TRUE)
{
    if (LIKELY(obj))
    {
        if (obj->IsPoolObject())
            obj->GiveBackToPool();
        else
            LLBC_Delete(obj);

        obj = NULL;
    }
}

template <typename ObjectType>
void LLBC_PoolObjectReflection::RecycleXInl(ObjectType *&obj, 
                                            __LLBC_CORE_OBJECT_POOL_POOL_OBJECT_INHERIT_DETECT_FALSE)
{
    LLBC_Delete(obj);
    obj = NULL;
}

// Undefine pool object reflection detect type definition macro.
#undef __LLBC_CORE_OBJECT_POOL_POOL_OBJECT_REFLECTION_DETECT_TYPE_DEF

__LLBC_NS_END

#endif // __LLBC_CORE_OBJECT_POOL_POOL_OBJECT_REFLECTION_H__
