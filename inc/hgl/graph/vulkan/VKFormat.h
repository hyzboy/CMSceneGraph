﻿#ifndef HGL_GRAPH_VULKAN_FORMAT_INCLUDE
#define HGL_GRAPH_VULKAN_FORMAT_INCLUDE

#include<hgl/graph/vulkan/VKNamespace.h>

VK_NAMESPACE_BEGIN

#define FMT_UNDEFINED   VK_FORMAT_UNDEFINED

#define FMT_RG4UN       VK_FORMAT_R4G4_UNORM_PACK8

#define FMT_RGBA4       VK_FORMAT_R4G4B4A4_UNORM_PACK16
#define FMT_BGRA4       VK_FORMAT_B4G4R4A4_UNORM_PACK16
#define FMT_RGB565      VK_FORMAT_R5G6B5_UNORM_PACK16
#define FMT_BGR565      VK_FORMAT_B5G6R5_UNORM_PACK16
#define FMT_RGB5A1      VK_FORMAT_R5G5B5A1_UNORM_PACK16
#define FMT_BGR5A1      VK_FORMAT_B5G5R5A1_UNORM_PACK16
#define FMT_A1RGB5      VK_FORMAT_A1R5G5B5_UNORM_PACK16

#define FMT_R8UN        VK_FORMAT_R8_UNORM
#define FMT_R8SN        VK_FORMAT_R8_SNORM
#define FMT_R8US        VK_FORMAT_R8_USCALED
#define FMT_R8SS        VK_FORMAT_R8_SSCALED
#define FMT_R8U         VK_FORMAT_R8_UINT
#define FMT_R8I         VK_FORMAT_R8_SINT
#define FMT_R8s         VK_FORMAT_R8_SRGB

#define FMT_RG8UN       VK_FORMAT_R8G8_UNORM
#define FMT_RG8SN       VK_FORMAT_R8G8_SNORM
#define FMT_RG8US       VK_FORMAT_R8G8_USCALED
#define FMT_RG8SS       VK_FORMAT_R8G8_SSCALED
#define FMT_RG8U        VK_FORMAT_R8G8_UINT
#define FMT_RG8I        VK_FORMAT_R8G8_SINT
#define FMT_RG8s        VK_FORMAT_R8G8_SRGB

#define FMT_RGB8UN      VK_FORMAT_R8G8B8_UNORM      /* no GPU support,don't use */
#define FMT_RGB8SN      VK_FORMAT_R8G8B8_SNORM      /* no GPU support,don't use */
#define FMT_RGB8US      VK_FORMAT_R8G8B8_USCALED    /* no GPU support,don't use */
#define FMT_RGB8SS      VK_FORMAT_R8G8B8_SSCALED    /* no GPU support,don't use */
#define FMT_RGB8U       VK_FORMAT_R8G8B8_UINT       /* no GPU support,don't use */
#define FMT_RGB8I       VK_FORMAT_R8G8B8_SINT       /* no GPU support,don't use */
#define FMT_RGB8s       VK_FORMAT_R8G8B8_SRGB       /* no GPU support,don't use */

#define FMT_BGR8UN      VK_FORMAT_B8G8R8_UNORM      /* no GPU support,don't use */
#define FMT_BGR8SN      VK_FORMAT_B8G8R8_SNORM      /* no GPU support,don't use */
#define FMT_BGR8US      VK_FORMAT_B8G8R8_USCALED    /* no GPU support,don't use */
#define FMT_BGR8SS      VK_FORMAT_B8G8R8_SSCALED    /* no GPU support,don't use */
#define FMT_BGR8U       VK_FORMAT_B8G8R8_UINT       /* no GPU support,don't use */
#define FMT_BGR8I       VK_FORMAT_B8G8R8_SINT       /* no GPU support,don't use */
#define FMT_BGR8s       VK_FORMAT_B8G8R8_SRGB       /* no GPU support,don't use */

#define FMT_RGBA8UN     VK_FORMAT_R8G8B8A8_UNORM
#define FMT_RGBA8SN     VK_FORMAT_R8G8B8A8_SNORM
#define FMT_RGBA8US     VK_FORMAT_R8G8B8A8_USCALED
#define FMT_RGBA8SS     VK_FORMAT_R8G8B8A8_SSCALED
#define FMT_RGBA8U      VK_FORMAT_R8G8B8A8_UINT
#define FMT_RGBA8I      VK_FORMAT_R8G8B8A8_SINT
#define FMT_RGBA8s      VK_FORMAT_R8G8B8A8_SRGB

#define FMT_BGRA8UN     VK_FORMAT_B8G8R8A8_UNORM
#define FMT_BGRA8SN     VK_FORMAT_B8G8R8A8_SNORM
#define FMT_BGRA8US     VK_FORMAT_B8G8R8A8_USCALED
#define FMT_BGRA8SS     VK_FORMAT_B8G8R8A8_SSCALED
#define FMT_BGRA8U      VK_FORMAT_B8G8R8A8_UINT
#define FMT_BGRA8I      VK_FORMAT_B8G8R8A8_SINT
#define FMT_BGRA8s      VK_FORMAT_B8G8R8A8_SRGB

#define FMT_ABGR8UN     VK_FORMAT_A8B8G8R8_UNORM_PACK32
#define FMT_ABGR8SN     VK_FORMAT_A8B8G8R8_SNORM_PACK32
#define FMT_ABGR8US     VK_FORMAT_A8B8G8R8_USCALED_PACK32
#define FMT_ABGR8SS     VK_FORMAT_A8B8G8R8_SSCALED_PACK32
#define FMT_ABGR8U      VK_FORMAT_A8B8G8R8_UINT_PACK32
#define FMT_ABGR8I      VK_FORMAT_A8B8G8R8_SINT_PACK32
#define FMT_ABGR8s      VK_FORMAT_A8B8G8R8_SRGB_PACK32

#define FMT_A2RGB10UN   VK_FORMAT_A2R10G10B10_UNORM_PACK32
#define FMT_A2RGB10SN   VK_FORMAT_A2R10G10B10_SNORM_PACK32
#define FMT_A2RGB10US   VK_FORMAT_A2R10G10B10_USCALED_PACK32
#define FMT_A2RGB10SS   VK_FORMAT_A2R10G10B10_SSCALED_PACK32
#define FMT_A2RGB10U    VK_FORMAT_A2R10G10B10_UINT_PACK32
#define FMT_A2RGB10I    VK_FORMAT_A2R10G10B10_SINT_PACK32

#define FMT_A2BGR10UN   VK_FORMAT_A2B10G10R10_UNORM_PACK32
#define FMT_A2BGR10SN   VK_FORMAT_A2B10G10R10_SNORM_PACK32
#define FMT_A2BGR10US   VK_FORMAT_A2B10G10R10_USCALED_PACK32
#define FMT_A2BGR10SS   VK_FORMAT_A2B10G10R10_SSCALED_PACK32
#define FMT_A2BGR10U    VK_FORMAT_A2B10G10R10_UINT_PACK32
#define FMT_A2BGR10I    VK_FORMAT_A2B10G10R10_SINT_PACK32

#define FMT_R16UN       VK_FORMAT_R16_UNORM
#define FMT_R16SN       VK_FORMAT_R16_SNORM
#define FMT_R16US       VK_FORMAT_R16_USCALED
#define FMT_R16SS       VK_FORMAT_R16_SSCALED
#define FMT_R16U        VK_FORMAT_R16_UINT
#define FMT_R16I        VK_FORMAT_R16_SINT
#define FMT_R16F        VK_FORMAT_R16_SFLOAT

#define FMT_RG16UN      VK_FORMAT_R16G16_UNORM
#define FMT_RG16SN      VK_FORMAT_R16G16_SNORM
#define FMT_RG16US      VK_FORMAT_R16G16_USCALED
#define FMT_RG16SS      VK_FORMAT_R16G16_SSCALED
#define FMT_RG16U       VK_FORMAT_R16G16_UINT
#define FMT_RG16I       VK_FORMAT_R16G16_SINT
#define FMT_RG16F       VK_FORMAT_R16G16_SFLOAT

#define FMT_RGB16UN     VK_FORMAT_R16G16B16_UNORM       /* no GPU support,don't use */
#define FMT_RGB16SN     VK_FORMAT_R16G16B16_SNORM       /* no GPU support,don't use */
#define FMT_RGB16US     VK_FORMAT_R16G16B16_USCALED     /* no GPU support,don't use */
#define FMT_RGB16SS     VK_FORMAT_R16G16B16_SSCALED     /* no GPU support,don't use */
#define FMT_RGB16U      VK_FORMAT_R16G16B16_UINT        /* no GPU support,don't use */
#define FMT_RGB16I      VK_FORMAT_R16G16B16_SINT        /* no GPU support,don't use */
#define FMT_RGB16F      VK_FORMAT_R16G16B16_SFLOAT      /* no GPU support,don't use */

#define FMT_RGBA16UN    VK_FORMAT_R16G16B16A16_UNORM
#define FMT_RGBA16SN    VK_FORMAT_R16G16B16A16_SNORM
#define FMT_RGBA16US    VK_FORMAT_R16G16B16A16_USCALED
#define FMT_RGBA16SS    VK_FORMAT_R16G16B16A16_SSCALED
#define FMT_RGBA16U     VK_FORMAT_R16G16B16A16_UINT
#define FMT_RGBA16I     VK_FORMAT_R16G16B16A16_SINT
#define FMT_RGBA16F     VK_FORMAT_R16G16B16A16_SFLOAT

#define FMT_R32U        VK_FORMAT_R32_UINT
#define FMT_R32I        VK_FORMAT_R32_SINT
#define FMT_R32F        VK_FORMAT_R32_SFLOAT

#define FMT_RG32U       VK_FORMAT_R32G32_UINT
#define FMT_RG32I       VK_FORMAT_R32G32_SINT
#define FMT_RG32F       VK_FORMAT_R32G32_SFLOAT

#define FMT_RGB32U      VK_FORMAT_R32G32B32_UINT
#define FMT_RGB32I      VK_FORMAT_R32G32B32_SINT
#define FMT_RGB32F      VK_FORMAT_R32G32B32_SFLOAT

#define FMT_RGBA32U     VK_FORMAT_R32G32B32A32_UINT
#define FMT_RGBA32I     VK_FORMAT_R32G32B32A32_SINT
#define FMT_RGBA32F     VK_FORMAT_R32G32B32A32_SFLOAT

#define FMT_R64U        VK_FORMAT_R64_UINT
#define FMT_R64I        VK_FORMAT_R64_SINT
#define FMT_R64F        VK_FORMAT_R64_SFLOAT

#define FMT_RG64U       VK_FORMAT_R64G64_UINT
#define FMT_RG64I       VK_FORMAT_R64G64_SINT
#define FMT_RG64F       VK_FORMAT_R64G64_SFLOAT

#define FMT_RGB64U      VK_FORMAT_R64G64B64_UINT
#define FMT_RGB64I      VK_FORMAT_R64G64B64_SINT
#define FMT_RGB64F      VK_FORMAT_R64G64B64_SFLOAT

#define FMT_RGBA64U     VK_FORMAT_R64G64B64A64_UINT
#define FMT_RGBA64I     VK_FORMAT_R64G64B64A64_SINT
#define FMT_RGBA64F     VK_FORMAT_R64G64B64A64_SFLOAT

#define FMT_B10GR11UF   VK_FORMAT_B10G11R11_UFLOAT_PACK32
#define FMT_E5BGR9UF    VK_FORMAT_E5B9G9R9_UFLOAT_PACK32

#define FMT_D16UN       VK_FORMAT_D16_UNORM
#define FMT_X8_D24UN    VK_FORMAT_X8_D24_UNORM_PACK32
#define FMT_D32F        VK_FORMAT_D32_SFLOAT
#define FMT_S8U         VK_FORMAT_S8_UINT
#define FMT_D16UN_S8U   VK_FORMAT_D16_UNORM_S8_UINT
#define FMT_D24UN_S8U   VK_FORMAT_D24_UNORM_S8_UINT
#define FMT_D32F_S8U    VK_FORMAT_D32_SFLOAT_S8_UINT

/**
 *                  Type of data      bytes/pixel     Palette size       Line Segments       User For                    Compressed components/Description
 * ---------------+----------------+---------------+-----------------+-------------------+-----------------------------+--------------------------------------
 *  BC1(S3TC1)      RGB5/RGB5A1         0.5             4                 1                  Color maps,Normal maps
 *  BC2(S3TC3)      RGBA4               1               4                 1                                                 BC1+uncompress 4-bit alpha
 *  BC3(S3TC5)      RGBA4               1               4                 1 Color+1Alpha     Color maps                     BC1+BC4 compress alpha
 *  BC4(ATI1/3Dc+)  Grayscale           0.5             8                 1
 *  BC5(ATI2/3Dc)   2xGrayscale         1               8 per channel     1 per channel      Tangent-space normal maps
 *  BC6H            FloatRGB            1               8-16              1-2                HDR images
 *  BC7             RGB/RGBA            1               4-16              1-3                High-quality color maps
 *
 *  ETC             RGB
 *  ETC2            RGB/RGBA1                                                                Color maps,Normals
 *  EAC             Grayscale
 *  2xEAC           RG
 *  ETC2+EAC        RGBA
 *
 *  PVRTC           RGB/RGBA1/RGBA
 *  PVRTC2          RGB/RGBA1/RGBA
 *
 *  ASTC            R/RG/RGB/RGBA
 * ---------------+----------------+---------------+-----------------+-------------------+-----------------------------+--------------------------------------
 */

#define FMT_BC1_RGBUN   VK_FORMAT_BC1_RGB_UNORM_BLOCK
#define FMT_BC1_RGBs    VK_FORMAT_BC1_RGB_SRGB_BLOCK
#define FMT_BC1_RGBAUN  VK_FORMAT_BC1_RGBA_UNORM_BLOCK
#define FMT_BC1_RGBAs   VK_FORMAT_BC1_RGBA_SRGB_BLOCK

#define FMT_BC2UN       VK_FORMAT_BC2_UNORM_BLOCK
#define FMT_BC2s        VK_FORMAT_BC2_SRGB_BLOCK

#define FMT_BC3UN       VK_FORMAT_BC3_UNORM_BLOCK
#define FMT_BC3s        VK_FORMAT_BC3_SRGB_BLOCK

#define FMT_BC4UN       VK_FORMAT_BC4_UNORM_BLOCK
#define FMT_BC4SN       VK_FORMAT_BC4_SNORM_BLOCK

#define FMT_BC5UN       VK_FORMAT_BC5_UNORM_BLOCK
#define FMT_BC5SN       VK_FORMAT_BC5_SNORM_BLOCK

#define FMT_BC6UF       VK_FORMAT_BC6H_UFLOAT_BLOCK
#define FMT_BC6SF       VK_FORMAT_BC6H_SFLOAT_BLOCK

#define FMT_BC7UN       VK_FORMAT_BC7_UNORM_BLOCK
#define FMT_BC7s        VK_FORMAT_BC7_SRGB_BLOCK

#define FMT_ETC2_RGB8UN     VK_FORMAT_ETC2_R8G8B8_UNORM_BLOCK
#define FMT_ETC2_RGB8s      VK_FORMAT_ETC2_R8G8B8_SRGB_BLOCK
#define FMT_ETC2_RGB8A1UN   VK_FORMAT_ETC2_R8G8B8A1_UNORM_BLOCK
#define FMT_ETC2_RGB8A1s    VK_FORMAT_ETC2_R8G8B8A1_SRGB_BLOCK
#define FMT_ETC2_RGBA8UN    VK_FORMAT_ETC2_R8G8B8A8_UNORM_BLOCK
#define FMT_ETC2_RGBA8s     VK_FORMAT_ETC2_R8G8B8A8_SRGB_BLOCK

#define FMT_EAC_R11UN       VK_FORMAT_EAC_R11_UNORM_BLOCK
#define FMT_EAC_R11SN       VK_FORMAT_EAC_R11_SNORM_BLOCK
#define FMT_EAC_RG11UN      VK_FORMAT_EAC_R11G11_UNORM_BLOCK
#define FMT_EAC_RG11SN      VK_FORMAT_EAC_R11G11_SNORM_BLOCK

#define FMT_ASTC_4x4UN      VK_FORMAT_ASTC_4x4_UNORM_BLOCK
#define FMT_ASTC_4x4s       VK_FORMAT_ASTC_4x4_SRGB_BLOCK
#define FMT_ASTC_5x4UN      VK_FORMAT_ASTC_5x4_UNORM_BLOCK
#define FMT_ASTC_5x4s       VK_FORMAT_ASTC_5x4_SRGB_BLOCK
#define FMT_ASTC_5x5UN      VK_FORMAT_ASTC_5x5_UNORM_BLOCK
#define FMT_ASTC_5x5s       VK_FORMAT_ASTC_5x5_SRGB_BLOCK
#define FMT_ASTC_6x5UN      VK_FORMAT_ASTC_6x5_UNORM_BLOCK
#define FMT_ASTC_6x5s       VK_FORMAT_ASTC_6x5_SRGB_BLOCK
#define FMT_ASTC_6x6UN      VK_FORMAT_ASTC_6x6_UNORM_BLOCK
#define FMT_ASTC_6x6s       VK_FORMAT_ASTC_6x6_SRGB_BLOCK
#define FMT_ASTC_8x5UN      VK_FORMAT_ASTC_8x5_UNORM_BLOCK
#define FMT_ASTC_8x5s       VK_FORMAT_ASTC_8x5_SRGB_BLOCK
#define FMT_ASTC_8x6UN      VK_FORMAT_ASTC_8x6_UNORM_BLOCK
#define FMT_ASTC_8x6s       VK_FORMAT_ASTC_8x6_SRGB_BLOCK
#define FMT_ASTC_8x8UN      VK_FORMAT_ASTC_8x8_UNORM_BLOCK
#define FMT_ASTC_8x8s       VK_FORMAT_ASTC_8x8_SRGB_BLOCK
#define FMT_ASTC_10x5UN     VK_FORMAT_ASTC_10x5_UNORM_BLOCK
#define FMT_ASTC_10x5s      VK_FORMAT_ASTC_10x5_SRGB_BLOCK
#define FMT_ASTC_10x6UN     VK_FORMAT_ASTC_10x6_UNORM_BLOCK
#define FMT_ASTC_10x6s      VK_FORMAT_ASTC_10x6_SRGB_BLOCK
#define FMT_ASTC_10x8UN     VK_FORMAT_ASTC_10x8_UNORM_BLOCK
#define FMT_ASTC_10x8s      VK_FORMAT_ASTC_10x8_SRGB_BLOCK
#define FMT_ASTC_10x10UN    VK_FORMAT_ASTC_10x10_UNORM_BLOCK
#define FMT_ASTC_10x10s     VK_FORMAT_ASTC_10x10_SRGB_BLOCK
#define FMT_ASTC_12x10UN    VK_FORMAT_ASTC_12x10_UNORM_BLOCK
#define FMT_ASTC_12x10s     VK_FORMAT_ASTC_12x10_SRGB_BLOCK
#define FMT_ASTC_12x12UN    VK_FORMAT_ASTC_12x12_UNORM_BLOCK
#define FMT_ASTC_12x12s     VK_FORMAT_ASTC_12x12_SRGB_BLOCK

#define FMT_BEGIN_RANGE FMT_UNDEFINED
#define FMT_END_RANGE   FMT_ASTC_12x12s
constexpr size_t FMT_RANGE_SIZE=FMT_END_RANGE-FMT_BEGIN_RANGE+1;

#define FMT_YUYV8_422   VK_FORMAT_G8B8G8R8_422_UNORM
#define FMT_UYVY8_422   VK_FORMAT_B8G8R8G8_422_UNORM
#define FMT_YUV8_420    VK_FORMAT_G8_B8_R8_3PLANE_420_UNORM
#define FMT_Y8_UV8_420  VK_FORMAT_G8_B8R8_2PLANE_420_UNORM
#define FMT_YUV8_422    VK_FORMAT_G8_B8_R8_3PLANE_422_UNORM
#define FMT_Y8_UV8_422  VK_FORMAT_G8_B8R8_2PLANE_422_UNORM
#define FMT_YUV8_444    VK_FORMAT_G8_B8_R8_3PLANE_444_UNORM

#define FMT_R10X6UN         VK_FORMAT_R10X6_UNORM_PACK16
#define FMT_RG10X6UN        VK_FORMAT_R10X6G10X6_UNORM_2PACK16
#define FMT_RGBA10X6UN      VK_FORMAT_R10X6G10X6B10X6A10X6_UNORM_4PACK16
#define FMT_YUYV10_422      VK_FORMAT_G10X6B10X6G10X6R10X6_422_UNORM_4PACK16
#define FMT_UYVY10_422      VK_FORMAT_B10X6G10X6R10X6G10X6_422_UNORM_4PACK16
#define FMT_YUV10_420       VK_FORMAT_G10X6_B10X6_R10X6_3PLANE_420_UNORM_3PACK16
#define FMT_Y10_UV10_420    VK_FORMAT_G10X6_B10X6R10X6_2PLANE_420_UNORM_3PACK16
#define FMT_YUV10_422       VK_FORMAT_G10X6_B10X6_R10X6_3PLANE_422_UNORM_3PACK16
#define FMT_Y10_UV10_422    VK_FORMAT_G10X6_B10X6R10X6_2PLANE_422_UNORM_3PACK16
#define FMT_YUV10_444       VK_FORMAT_G10X6_B10X6_R10X6_3PLANE_444_UNORM_3PACK16

#define FMT_R12X4UN         VK_FORMAT_R12X4_UNORM_PACK16
#define FMT_RG12X4UN        VK_FORMAT_R12X4G12X4_UNORM_2PACK16
#define FMT_RGBA12X4UN      VK_FORMAT_R12X4G12X4B12X4A12X4_UNORM_4PACK16
#define FMT_YUYV12_422      VK_FORMAT_G12X4B12X4G12X4R12X4_422_UNORM_4PACK16
#define FMT_UYVY12_422      VK_FORMAT_B12X4G12X4R12X4G12X4_422_UNORM_4PACK16
#define FMT_YUV12_420       VK_FORMAT_G12X4_B12X4_R12X4_3PLANE_420_UNORM_3PACK16
#define FMT_Y12_UV12_420    VK_FORMAT_G12X4_B12X4R12X4_2PLANE_420_UNORM_3PACK16
#define FMT_YUV12_422       VK_FORMAT_G12X4_B12X4_R12X4_3PLANE_422_UNORM_3PACK16
#define FMT_Y12_UV12_422    VK_FORMAT_G12X4_B12X4R12X4_2PLANE_422_UNORM_3PACK16
#define FMT_YUV12_444       VK_FORMAT_G12X4_B12X4_R12X4_3PLANE_444_UNORM_3PACK16

#define FMT_YUYV16_422      VK_FORMAT_G16B16G16R16_422_UNORM
#define FMT_UYVY16_422      VK_FORMAT_B16G16R16G16_422_UNORM
#define FMT_YUV16_420       VK_FORMAT_G16_B16_R16_3PLANE_420_UNORM
#define FMT_Y16_UV16_420    VK_FORMAT_G16_B16R16_2PLANE_420_UNORM
#define FMT_YUV16_422       VK_FORMAT_G16_B16_R16_3PLANE_422_UNORM
#define FMT_Y16_UV16_422    VK_FORMAT_G16_B16R16_2PLANE_422_UNORM
#define FMT_YUV16_444       VK_FORMAT_G16_B16_R16_3PLANE_444_UNORM

#define FMT_YUV_BEGIN_RANGE FMT_YUYV8_422
#define FMT_YUV_END_RANGE   FMT_YUV16_444
constexpr size_t FMT_YUV_RANGE_SIZE=FMT_YUV_END_RANGE-FMT_YUV_BEGIN_RANGE+1;

#define FMT_PVRTC1_2UN  VK_FORMAT_PVRTC1_2BPP_UNORM_BLOCK_IMG
#define FMT_PVRTC1_4UN  VK_FORMAT_PVRTC1_4BPP_UNORM_BLOCK_IMG
#define FMT_PVRTC2_2UN  VK_FORMAT_PVRTC2_2BPP_UNORM_BLOCK_IMG
#define FMT_PVRTC2_4UN  VK_FORMAT_PVRTC2_4BPP_UNORM_BLOCK_IMG
#define FMT_PVRTC1_2s  VK_FORMAT_PVRTC1_2BPP_SRGB_BLOCK_IMG
#define FMT_PVRTC1_4s  VK_FORMAT_PVRTC1_4BPP_SRGB_BLOCK_IMG
#define FMT_PVRTC2_2s  VK_FORMAT_PVRTC2_2BPP_SRGB_BLOCK_IMG
#define FMT_PVRTC2_4s  VK_FORMAT_PVRTC2_4BPP_SRGB_BLOCK_IMG

#define FMT_PVRTC_BEGIN_RANGE   FMT_PVRTC1_2UN
#define FMT_PVRTC_END_RANGE     FMT_PVRTC2_4s
constexpr size_t FMT_PVRTC_RANGE_SIZE=FMT_PVRTC_END_RANGE-FMT_PVRTC_BEGIN_RANGE+1;

//以下为AMD/NVIDIA/INTEL/QUALCOMM/ARM/POWERVR全部可用的通用格式
#define UFMT_BGRA4      FMT_BGRA4
#define UFMT_RGB565     FMT_RGB565
#define UFMT_A1RGB5     FMT_A1RGB5
#define UFMT_R8         FMT_R8UN
#define UFMT_RG8        FMT_RG8UN
#define UFMT_RGBA8      FMT_RGBA8UN
#define UFMT_ABGR8      FMT_ABGR8UN
#define UFMT_A2BGR10    FMT_A2BGR10UN
#define UFMT_R16        FMT_R16UN
#define UFMT_R16F       FMT_R16F
#define UFMT_RG16       FMT_RG16UN
#define UFMT_RG16F      FMT_RG16F
#define UFMT_RGBA16     FMT_RGBA16UN
#define UFMT_RGBA16F    FMT_RGBA16F
#define UFMT_R32U       FMT_R32U
#define UFMT_R32I       FMT_R32I
#define UFMT_R32F       FMT_R32F
#define UFMT_RG32U      FMT_RG32U
#define UFMT_RG32I      FMT_RG32I
#define UFMT_RG32F      FMT_RG32F
#define UFMT_RGB32U     FMT_RGB32U
#define UFMT_RGB32I     FMT_RGB32I
#define UFMT_RGB32F     FMT_RGB32F
#define UFMT_RGBA32U    FMT_RGBA32U
#define UFMT_RGBA32I    FMT_RGBA32I
#define UFMT_RGBA32F    FMT_RGBA32F
#define UFMT_B10GR11UF  FMT_B10GR11UF

enum class TextureCompressType
{
    NONE=0,

    S3TC,
    PVRTC,
    ETC1,
    ETC2,
    EAC,
    ATC,
    ASTC,
    YUV,
};//

enum class VulkanDataType
{
    NONE=0,

    UNORM,
    SNORM,
    USCALED,
    SSCALED,
    UINT,
    SINT,
    UFLOAT,
    SFLOAT,
    SRGB,

    END
};//

struct VulkanFormat
{
    VkFormat            format;         ///<Vulkan格式，此值保留仅为参考

    uint32_t            bytes;          ///<每象素字节数

    char                name[16];       ///<名称

    TextureCompressType compress_type;  ///<压缩类型
    VulkanDataType      color;          ///<颜色数据类型
    VulkanDataType      depth,stencil;  ///<是否含有depth,stencil数据
};

#ifdef _DEBUG
bool CheckStrideBytesByFormat();        ///<检验所有数据类型长度数组是否符合规则
#endif//_DEBUG

const VulkanFormat *GetVulkanFormat(const VkFormat &format);
const VulkanFormat *GetVulkanFormatList(uint32_t &);

inline uint32_t GetStrideByFormat(const VkFormat &format)
{
    const VulkanFormat *vcf=GetVulkanFormat(format);

    return (vcf?vcf->bytes:0);
}

inline const char *GetVulkanFormatName(const VkFormat &format)
{
    const VulkanFormat *vcf=GetVulkanFormat(format);

    return (vcf?vcf->name:nullptr);
}

const VulkanFormat *GetVulkanFormat(const char *fmt_name);

/**
 * 根据spirv_cross::SPIRType类型获取vulkan类型
 */
const VkFormat GetVulkanFormat(const uint32_t &basetype,const uint32_t vecsize);
VK_NAMESPACE_END
#endif//HGL_GRAPH_VULKAN_FORMAT_INCLUDE
