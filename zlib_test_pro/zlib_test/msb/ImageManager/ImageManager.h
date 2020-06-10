/**
 * @file ImageManager.h
 * @brief header file to use ImageManager library
 *
 * @author S.Tanaka
 * @date 2006.07.14
 * 
 * Copyright(C) 2006-2014 Eisai Co., Ltd. All rights reserved.
 */


#ifndef __KOME_IMG_IMAGE_MANAGER_H__
#define __KOME_IMG_IMAGE_MANAGER_H__


//
// macros
// 

#ifdef _MSC_VER
	#define IMAGE_MANAGER_CLASS __declspec(dllimport)
#else
	#define IMAGE_MANAGER_CLASS
#endif	// _MSC_VER


//
// includes
//

#include "ColorTool.h"
#include "Font.h"
#include "BitmapData.h"
#include "Graphics.h"
#include "CairoGraphics.h"
#include "DrawingXYData.h"
#include "GraphTool.h"


#endif	// __KOME_IMG_IMAGE_MANAGER_H__
