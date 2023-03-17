#pragma once
#include<hgl/type/String.h>
#include<hgl/graph/VKNamespace.h>

VK_NAMESPACE_BEGIN
template<typename T>
inline hgl::String<T> VkUUID2String(const hgl::uint8 *pipelineCacheUUID)
{
    constexpr const size_t UUID_SIZE=16;

    T *hstr=new T[UUID_SIZE*2+1];
    
    DataToLowerHexStr(hstr,pipelineCacheUUID,UUID_SIZE);

    return hgl::String<T>::newOf(hstr,UUID_SIZE*2);
}
VK_NAMESPACE_END