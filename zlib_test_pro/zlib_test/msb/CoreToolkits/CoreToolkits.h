/**
 * @file CoreToolkits.h
 * @brief header file to use CoreToolkit library
 *
 * @author S.Tanaka
 * @date 2006.07.24
 * 
 * Copyright(C) 2006-2014 Eisai Co., Ltd. All rights reserved.
 */


#ifndef __KOME_CORE_TOOLKITS_H__
#define __KOME_CORE_TOOLKITS_H__

//
// macros
// 

#ifdef _MSC_VER
	#define CORE_TOOLKITS_CLASS __declspec(dllimport)
#else
	#define CORE_TOOLKITS_CLASS
#endif	// _MSC_VER


//
// includes
//

#include "TreeNode.h"
#include "Heap.h"
#include "Properties.h"
#include "IniFile.h"
#include "ConversionTool.h"
#include "Rect.h"
#include "Point.h"
#include "PointArray.h"
#include "RangeList.h"
#include "NumberRestriction.h"
#include "Vector.h"
#include "Matrix.h"
#include "Progress.h"
//#include "DisplayProgress.h"
#include "XYData.h"
#include "DataPoints.h"
#include "SearchTool.h"
#include "Base64.h"
#include "Sha1.h"
#include "Selector.h"
#include "ManualSelector.h"
#include "RangeListSelector.h"
#include "Timer.h"
#include "DataAccessor.h"
#include "MemoryAccessor.h"
#include "FileAccessor.h"
#include "Buffer.h"
//#include "ResourceBundle.h"
#include "MsppManager.h"
#include "CommonTypes.h"
#include "CommonParameterManager.h"

#endif	//  __KOME_CORE_TOOLKITS_H__
