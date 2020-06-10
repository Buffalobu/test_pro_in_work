/**
 * @file DbTools.h
 * @brief header file to use DbTools library
 *
 * @author S.Tanaka
 * @date 2008.08.11
 * 
 * Copyright(C) 2006-2014 Eisai Co., Ltd. All rights reserved.
 */


#ifndef __KOME_DB_TOOLS_H__
#define __KOME_DB_TOOLS_H__


//
// macros
// 

#ifdef _MSC_VER
	#define DB_TOOLS_CLASS __declspec(dllimport)
#else
	#define DB_TOOLS_CLASS
#endif	// _MSC_VER


//
// includes
//


#include "Table.h"
#include "TableColumn.h"
#include "TableIndex.h"

#include "Database.h"
#include "Statement.h"
#include "ResultSet.h"

#include "DbManager.h"


#endif //  __KOME_DB_TOOLS_H__
