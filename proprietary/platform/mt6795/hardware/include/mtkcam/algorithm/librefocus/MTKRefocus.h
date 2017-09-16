/* Copyright Statement:
 *
 * This software/firmware and related documentation ("MediaTek Software") are
 * protected under relevant copyright laws. The information contained herein
 * is confidential and proprietary to MediaTek Inc. and/or its licensors.
 * Without the prior written permission of MediaTek inc. and/or its licensors,
 * any reproduction, modification, use or disclosure of MediaTek Software,
 * and information contained herein, in whole or in part, shall be strictly prohibited.
 */
/* MediaTek Inc. (C) 2010. All rights reserved.
 *
 * BY OPENING THIS FILE, RECEIVER HEREBY UNEQUIVOCALLY ACKNOWLEDGES AND AGREES
 * THAT THE SOFTWARE/FIRMWARE AND ITS DOCUMENTATIONS ("MEDIATEK SOFTWARE")
 * RECEIVED FROM MEDIATEK AND/OR ITS REPRESENTATIVES ARE PROVIDED TO RECEIVER ON
 * AN "AS-IS" BASIS ONLY. MEDIATEK EXPRESSLY DISCLAIMS ANY AND ALL WARRANTIES,
 * EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE IMPLIED WARRANTIES OF
 * MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE OR NONINFRINGEMENT.
 * NEITHER DOES MEDIATEK PROVIDE ANY WARRANTY WHATSOEVER WITH RESPECT TO THE
 * SOFTWARE OF ANY THIRD PARTY WHICH MAY BE USED BY, INCORPORATED IN, OR
 * SUPPLIED WITH THE MEDIATEK SOFTWARE, AND RECEIVER AGREES TO LOOK ONLY TO SUCH
 * THIRD PARTY FOR ANY WARRANTY CLAIM RELATING THERETO. RECEIVER EXPRESSLY ACKNOWLEDGES
 * THAT IT IS RECEIVER'S SOLE RESPONSIBILITY TO OBTAIN FROM ANY THIRD PARTY ALL PROPER LICENSES
 * CONTAINED IN MEDIATEK SOFTWARE. MEDIATEK SHALL ALSO NOT BE RESPONSIBLE FOR ANY MEDIATEK
 * SOFTWARE RELEASES MADE TO RECEIVER'S SPECIFICATION OR TO CONFORM TO A PARTICULAR
 * STANDARD OR OPEN FORUM. RECEIVER'S SOLE AND EXCLUSIVE REMEDY AND MEDIATEK'S ENTIRE AND
 * CUMULATIVE LIABILITY WITH RESPECT TO THE MEDIATEK SOFTWARE RELEASED HEREUNDER WILL BE,
 * AT MEDIATEK'S OPTION, TO REVISE OR REPLACE THE MEDIATEK SOFTWARE AT ISSUE,
 * OR REFUND ANY SOFTWARE LICENSE FEES OR SERVICE CHARGE PAID BY RECEIVER TO
 * MEDIATEK FOR SUCH MEDIATEK SOFTWARE AT ISSUE.
 *
 * The following software/firmware and/or related documentation ("MediaTek Software")
 * have been modified by MediaTek Inc. All revisions are subject to any receiver's
 * applicable license agreements with MediaTek Inc.
 */

/*
**
** Copyright 2008, The Android Open Source Project
**
** Licensed under the Apache License, Version 2.0 (the "License");
** you may not use this file except in compliance with the License.
** You may obtain a copy of the License at
**
**     http://www.apache.org/licenses/LICENSE-2.0
**
** Unless required by applicable law or agreed to in writing, software
** distributed under the License is distributed on an "AS IS" BASIS,
** WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
** See the License for the specific language governing permissions and
** limitations under the License.
*/

#ifndef _MTK_REFOCUS_H
#define _MTK_REFOCUS_H

#include "MTKRefocusType.h"
#include "MTKRefocusErrCode.h"

typedef enum DRVRefocusObject_s {
    DRV_REFOCUS_OBJ_NONE = 0,
    DRV_REFOCUS_OBJ_SW,
    DRV_REFOCUS_OBJ_UNKNOWN = 0xFF,
} DrvRefocusObject_e;

#define REFOCUS_TIME_PROF

/*****************************************************************************
    REFOCUS Define and State Machine 
******************************************************************************/
#define REFOCUS_MAX_IMG_NUM     (25)
#define REFOCUS_MAX_CORE_NUM    (4)
#define REFOCUS_BUFFER_SCALE    (42.0f)
#define RANK                    (3)
#define REFOCUS_MAX_DOF         (32)
#define REFOCUS_MAX_METADATA_SIZE         (1)

//#define REFOCUS_DEBUG
#define REFOCUS_MULTI_CORE_OPT 1
//#define BIT_TRUE_TEST
//#define INPUT_FROM_CMODEL
//#define REFOCUS_OUTPUT_CROP
//#define OPENCV
#define BFILTER_MULTICORE

#ifdef MTK_TC7_FEATURE 
#define REFOCUS_ABORT_SUPPORT
#endif

#define REFOCUS_ENABLE_CONFIDENCE_MAP

/*****************************************************************************
    Process Control 
******************************************************************************/
typedef enum REFOCUS_STATE_ENUM
{
    REFOCUS_STATE_STANDBY=0,            // After Create Obj or Reset
    REFOCUS_STATE_INIT,                 // After Called RefocusInit
    REFOCUS_STATE_PROCESS,              // After Called RefocusMain
    REFOCUS_STATE_GEN_DEPTH,            // In RefocusMain, start to generate depth map
    REFOCUS_STATE_DEFOCUS,              // In RefocusMain, start to defocus
    REFOCUS_STATE_PROCESS_DONE,         // After Finish RefocusMain
} REFOCUS_STATE_ENUM;

typedef enum MTK_REFOCUS_IMAGE_FMT_ENUM
{
    REFOCUS_IMAGE_RGB565=1,
    REFOCUS_IMAGE_BGR565,
    REFOCUS_IMAGE_RGB888,
    REFOCUS_IMAGE_BGR888,
    REFOCUS_IMAGE_ARGB888,
    REFOCUS_IMAGE_ABGR888,
    REFOCUS_IMAGE_BGRA8888,
    REFOCUS_IMAGE_RGBA8888,
    REFOCUS_IMAGE_YUV444,
    REFOCUS_IMAGE_YUV422,
    REFOCUS_IMAGE_YUV420,
    REFOCUS_IMAGE_YUV411,
    REFOCUS_IMAGE_YUV400,
    REFOCUS_IMAGE_PACKET_UYVY422,
    REFOCUS_IMAGE_PACKET_YUY2,
    REFOCUS_IMAGE_PACKET_YVYU,
    REFOCUS_IMAGE_NV21,
    REFOCUS_IMAGE_YV12,

    REFOCUS_IMAGE_RAW8=100,
    REFOCUS_IMAGE_RAW10,
    REFOCUS_IMAGE_EXT_RAW8,
    REFOCUS_IMAGE_EXT_RAW10,
    REFOCUS_IMAGE_JPEG=200
} MTK_REFOCUS_IMAGE_FMT_ENUM;

typedef enum REFOCUS_IO_ENUM
{
    REFOCUS_INPUT,
    REFOCUS_OUTPUT,
    REFOCUS_IO_NUM
} REFOCUS_IO_ENUM;

typedef enum
{
    REFOCUS_ORIENTATION_0,
    REFOCUS_ORIENTATION_90,
    REFOCUS_ORIENTATION_180,
    REFOCUS_ORIENTATION_270,
}REFOCUS_ORIENTATION_ENUM;

typedef enum
{
    REFOCUS_MAINCAM_POS_ON_LEFT,
    REFOCUS_MAINCAM_POS_ON_RIGHT,    
}REFOCUS_MAINCAM_POS_ENUM;

typedef enum
{
    REFOCUS_MODE_FULL,
    REFOCUS_MODE_DEPTH_ONLY,
    REFOCUS_MODE_DEPTH_AND_XMP,
    REFOCUS_MODE_DEPTH_AND_REFOCUS,
    REFOCUS_MODE_MAX,
}MTK_REFOCUS_MODE_ENUM;

/*****************************************************************************
    Feature Control Enum and Structure
******************************************************************************/
typedef enum
{
    REFOCUS_FEATURE_BEGIN,              // minimum of feature id
    REFOCUS_FEATURE_GET_WORKBUF_SIZE,   // feature id to query buffer size
    REFOCUS_FEATURE_SET_WORKBUF_ADDR,   // feature id to set working buffer address
    REFOCUS_FEATURE_ADD_IMG,            // feature id to set image info
    REFOCUS_FEATURE_GET_RESULT,         // feature id to get result
    REFOCUS_FEATURE_GET_LOG,            // feature id to get debugging information
    #ifdef REFOCUS_ABORT_SUPPORT
    REFOCUS_FEATURE_SET_ABORT,
    REFOCUS_FEATURE_GET_ABORT_INFO,
    #endif
    REFOCUS_FEATURE_MAX                 // maximum of feature id
}   REFOCUS_FEATURE_ENUM;

typedef enum 
{
    REFOCUS_METADATA_TYPE_CONFIDENCE_MAP,
    REFOCUS_METADATA_TYPE_MAX,    
}REFOCUS_METADATA_TYPE_ENUM;

typedef struct RefocusMetadataInfo
{
    REFOCUS_METADATA_TYPE_ENUM Type;    //metadata type
    MUINT32 Width;                      //width of metadata buffer
    MUINT32 Height;                     //height of metadata buffer
    MUINT32 Size;                       //size of metadata buffer
    MUINT8* Addr;                       //address of metadata buffer;
}RefocusMetadataInfo;

typedef struct RefocusTuningInfo
{
    MUINT32 HorzDownSampleRatio;        // valid value = {4, 8, 16, 32}
    MUINT32 VertDownSampleRatio;        // valid value = {4, 8, 16, 32}
    MUINT32 IterationTimes;             // valid value = {1 ~ 5}
    MUINT32 InterpolationMode;          // valid value = {0, 1}
    MUINT32 CoreNumber;                 // valid value = {1 ~ REFOCUS_MAX_CORE_NUM}   
    MUINT32 NumOfExecution;             // profiling purpose
    MFLOAT  Baseline;                   // distance between two lenses
} RefocusTuningInfo;

typedef struct RefocusInitInfo
{
    MUINT8*                 WorkingBuffAddr;                // Working buffer start address
    MUINT32                 WorkingBuffSize;                // Working buffer size
    RefocusTuningInfo       *pTuningInfo;                   // Tuning info
} RefocusInitInfo;

// REFOCUS_STATE_GEN_DEPTH & REFOCUS_STATE_DEFOCUS
// Input    : RefocusImageInfo
// Output   : NONE
typedef struct RefocusImageInfo
{
    MTK_REFOCUS_MODE_ENUM       Mode;                           // (both)refocus mode
    MTK_REFOCUS_IMAGE_FMT_ENUM  ImgFmt;                         // (both)input image format    

    MUINT32                     TargetWidth;                    // (defocus)width of target image
    MUINT32                     TargetHeight;                   // (defocus)height of target image
    MUINT8*                     TargetImgAddr;                  // (defocus)buffer address of target image

    MUINT32                     ImgNum;                         // (depth)input image number
    MUINT32                     Width;                          // (depth)input image width
    MUINT32                     Height;                         // (depth)input image height
    MUINT8*                     ImgAddr[REFOCUS_MAX_IMG_NUM];   // (depth)input image address array

    MUINT32                     MaskWidth;                      // (depth)width of Mask
    MUINT32                     MaskHeight;                     // (depth)height of Mask
    MUINT8*                     MaskImageAddr;                  // (depth)Address of Mask    

    MUINT32                     PosX;                           // (depth)Mask Start point X
    MUINT32                     PosY;                           // (depth)Mask Start point Y
    MUINT32                     ViewWidth;                      // (depth)Mask Width
    MUINT32                     ViewHeight;                     // (depth)Mask Height    

    MUINT8*                     DepthBufferAddr;                // (depth)address of temp depth buffer
    MUINT32                     DepthBufferSize;                // (depth)size of temp depth buffer

    MUINT32                     DRZ_WD;                         // (depth)depth map width for xmp data
    MUINT32                     DRZ_HT;                         // (depth)depth map height for xmp data

    MUINT32                     TouchCoordX;                    // (defocus)input touching coordinate X (within image width)
    MUINT32                     TouchCoordY;                    // (defocus)input touching coordinate Y (within image height)
    MUINT32                     DepthOfField;                   //( defocus) input depth of field (within 0 ~ REFOCUS_MAX_DOF)    

    REFOCUS_ORIENTATION_ENUM    JPSOrientation;                 // (depth)Phone orientation when taking photo
    REFOCUS_ORIENTATION_ENUM    JPGOrientation;                 // (depth)JPG orientation (maybe rotated )
    REFOCUS_MAINCAM_POS_ENUM    MainCamPos;                     // (depth)Main cam on Left or Right

    // error handling info
    MFLOAT                      RcfyError;                      // (depth)
    MINT32                      RcfyIterNo;                     // (depth)
    MFLOAT                      Theta[RANK];                    // (depth)
    MINT32                      DisparityRange;                 // (depth)
} RefocusImageInfo;

// REFOCUS_FEATURE_GET_RESULT
// Input    : NONE
// Output   : RefocusResultInfo
typedef struct RefocusResultInfo
{
    MUINT32     RefocusImageWidth;                   // output image width for Refocus
    MUINT32     RefocusImageHeight;                  // output image height for Refocus
    MUINT8*     RefocusedYUVImageAddr;          // refocused image address
    MUINT8*     RefocusedRGBAImageAddr;         // refocused image address

    MUINT32     XMPDepthWidth;                  // output xmp depth map width
    MUINT32     XMPDepthHeight;                 // output xmp depth map height
    MUINT8*     XMPDepthMapAddr;                // output xmp depth map address

    MUINT8*     DepthBufferAddr;                // address of temp depth buffer
    MUINT32     DepthBufferSize;                // size of temp depth buffer
    MUINT32     DepthBufferWidth;               // width of depth buffer
    MUINT32     DepthBufferHeight;              // height of depth buffer
    MUINT32     MetaBufferWidth;                // width of meta data buffer
    MUINT32     MetaBufferHeight;               // height of meta data buffer
    
    MUINT32     NumOfMetadata;
    RefocusMetadataInfo metaInfo[REFOCUS_MAX_METADATA_SIZE];
    MRESULT     RetCode;                        // returned status
}RefocusResultInfo;

#ifdef REFOCUS_ABORT_SUPPORT
typedef struct RefocusAbortInfo
{
    MUINT32 AbortFlag;
    char* AbortPosition;
}RefocusAbortInfo;
#endif

/*******************************************************************************
*
********************************************************************************/
class MTKRefocus {
public:
    static MTKRefocus* createInstance(DrvRefocusObject_e eobject);
    virtual void   destroyInstance(MTKRefocus* obj) = 0;
       
    virtual ~MTKRefocus(){}
    // Process Control
    virtual MRESULT RefocusInit(MUINT32 *InitInData, MUINT32 *InitOutData);    // Env/Cb setting
    virtual MRESULT RefocusMain(void);                                         // START
    virtual MRESULT RefocusReset(void);                                        // RESET
            
    // Feature Control        
    virtual MRESULT RefocusFeatureCtrl(MUINT32 FeatureID, void* pParaIn, void* pParaOut);
private:
    
};

class AppRefocusTmp : public MTKRefocus {
public:
    //
    static MTKRefocus* getInstance();
	virtual void destroyInstance(){};
    //
    AppRefocusTmp() {}; 
    virtual ~AppRefocusTmp() {};
};

#endif

