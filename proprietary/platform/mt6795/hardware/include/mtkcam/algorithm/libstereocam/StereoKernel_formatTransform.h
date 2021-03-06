#ifndef __STEREO_KERNEL_FORMAT_TRANSFROM_H__
#define __STEREO_KERNEL_FORMAT_TRANSFROM_H__

#include "MTKUtilType.h"
// for YVU420 (not YUV)

void FORMAT_YVU420toRGB(MUINT8* intput, MUINT8 *output, MUINT32 width, MUINT32 height, MUINT32 rgb_dim, MUINT32 input_w, MUINT32 input_h );
void FORMAT_YVU420toRGB(MUINT8* intput, MUINT8 *output, MUINT32 width, MUINT32 height, MUINT32 rgb_dim);
void FORMAT_RGBtoYVU420(MUINT8* intput, MUINT8 *output, MUINT32 width, MUINT32 height, MUINT32 rgb_dim);

void FORMAT_YUYVtoYUV420( MUINT8* input, MUINT8* output, MUINT32 width, MUINT32 height ) ;
void FORMAT_YUYVtoYV12( MUINT8* input, MUINT8* output, MUINT32 width, MUINT32 height ) ;
void FORMAT_RGBtoYUYV( MUINT8 *input, MUINT8 *output, MUINT32 width, MUINT32 height, MUINT32 rgb_dim ) ;
void FORMAT_YUYVtoRGB( MUINT8 *input, MUINT8 *output, MUINT32 width, MUINT32 height, MUINT32 rgb_dim ) ;

void FORMAT_RGBAtoY( MUINT8 *input, MUINT8 *output, MUINT32 width, MUINT32 height, MUINT32 stride ) ;
void FORMAT_YV12toY( MUINT8 *input, MUINT8 *output, MUINT32 width, MUINT32 height, MUINT32 stride ) ;

#endif