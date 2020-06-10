/**
 * @file FileFunctions.cpp
 * @brief implements of file system function.
 *
 * @author S.Tanaka
 * @date 2006.06.28
 * 
 * Copyright(C) 2006-2014 Eisai Co., Ltd. All rights reserved.
 */


#include "stdafx.h"


#include "FileFunctions.h"

#include "LogFunctions.h"
#include "StringFunctions.h"
#include "CoreMacros.h"
#include "ErrorCode.h"

#include <vector>
#include <list>

//#include <boost/bind.hpp>
//#include <boost/filesystem.hpp>

#include <QString>
#include <QDir>
#include <QFile>
#include <QFileInfoList>
#include <QFileInfo>

#ifdef __unix
	#include <sys/stat.h>
#else
	#include <direct.h>
#endif //__unix


#ifndef _LARGEFILE_SOURCE
	#define _LARGEFILE_SOURCE
#endif //  _LARGEFILE_SOURCE


/** the array of arguments */
std::vector<std::string> g_arguments;

/** module file path */
std::string g_moduleFile;

/** home directory */
std::string g_homeDir;


// judge where file exists.
bool fileexists( const char* path ) {
	// check parameter
    if( path == nullptr ) {
		return false;
	}

	// create path object
//    boost::filesystem::path p( path/*, boost::filesystem::native */);
    QString p(path);

	// judge
	bool ret = false;
	try{
//		ret = boost::filesystem::exists( p );
        QFile qFile(p);
        ret = qFile.exists();
	}
	catch( ... ) {
		ret = false;
	}

	return ret;
}

// judge where path is directory.
bool isdirectory( const char* path ) {
	// check parameter
	if( !fileexists( path ) ) {
		return false;
	}

	// create path object
//    boost::filesystem::path p( path/*, boost::filesystem::native */);

	// check existing
//	if( !boost::filesystem::exists( p ) ) {
//		return false;
//	}

	// judgement
//	return boost::filesystem::is_directory( p );
    bool ret =false;
    try{
        QString p = QString(path);
        QDir qDir(p);
        ret = qDir.exists();
    }
    catch( ... ) {
        ret = false;
    }
    return ret;
}

// check file before open
bool checkfile( const char* path ) {
	// check parameter
    if( path == nullptr ) {
        LOG_ERROR( FMT( "The file path is nullptr." ) )
		return false;
	}

	//
	if( !fileexists( path ) ) {
		LOG_ERROR_CODE( FMT( "The file does not exist. [%s]", path ), ERR_FILE_NOT_FOUND );
		return false;
	}

	if( isdirectory( path ) ){
		LOG_ERROR_CODE( FMT( "The path is a directory. A file should be specified. [%s]", path ), ERR_PATH_IS_DIRECTORY );
		return false;
	}

	return true;
}

// get file name
std::string getfilename( const char* path ) {
	// check parameter
    if( path == nullptr ) {
		return "";
	}
    return QString(path).toStdString();

	// create path object
//    boost::filesystem::path p( path/*, boost::filesystem::native */);

	// leaf
//	std::string name = p.leaf().string();
//	return name;
}

// get dir name
std::string getdir( const char* path ) {
	// check parameter
    if( path == nullptr ) {
		return "";
	}

	// create path object
//    boost::filesystem::path p( path/*, boost::filesystem::native */);

//	// directory
//	if( p.has_branch_path() ) {
//		p = p.branch_path();
//		return p.string();
//	}

	return std::string( "" );
}

// get path
std::string getpath( const char* dir, const char* file ) {
	// check parameter
    if( dir == nullptr && file == nullptr ) {
		return std::string( "" );
	}
    if( dir == nullptr ) {
		return std::string( file );
	}
    if( file == nullptr ) {
		return std::string( dir );
	}

//	// create path object
//    boost::filesystem::path filePath( file/*, boost::filesystem::native */);

//	std::string mergeFileName = FMT( "%s%s%s", dir, DIR_SEPARATOR, file );
//    boost::filesystem::path mergePath( mergeFileName.c_str()/*, boost::filesystem::native */);

//	// return path
//	boost::filesystem::path p = filePath.is_complete() ? filePath : mergePath;
//	p.normalize();
//	std::string ret = p.string();
//	ret = replacestring( ret.c_str(), "/", DIR_SEPARATOR );
//	ret = replacestring( ret.c_str(), "\\", DIR_SEPARATOR );
//	return ret;
}

// get absolute path
std::string absolutepath( const char* path ) {
	// check parameter
    if( path == nullptr ) {
		return "";
	}
    return std::string(path);

//	// create path object
//    boost::filesystem::path p( path/*, boost::filesystem::native */);

//	// get absolute path
//	boost::filesystem::path absPath = boost::filesystem::absolute( p );

//	return absPath.string();
}

// get absolute path
std::string getabsolutepath( const char* dir, const char* file ) {
    return "";
	// create path object
//    boost::filesystem::path p( getpath( dir, file )/*, boost::filesystem::native */);
//	p.normalize();
//	std::string ret = p.string();
//	ret = replacestring( ret.c_str(), "/", DIR_SEPARATOR );

//	// return path
//	if( p.is_complete() ) {	// dir has root
//		return ret;
//	}

//	return absolutepath( ret.c_str() );
}

// judge absolute file path or not
bool isabsolutepath( const char* file ) {
    return false;
	// create path object
//    boost::filesystem::path p( file/*, boost::filesystem::native */);
//	p.normalize();

//	// judge
//	return p.is_complete();
}

// set arguments
void setarguments( int argc, char** argv ) {
	// initialize the array
	g_arguments.clear();

	// keep arguments
	if( argc > 0 ){
		g_arguments.reserve( argc );
	}
	for( int i = 0; i < argc; i++ ){
		g_arguments.push_back( std::string( argv[i] ) );
	}
}

// get number of arguments
int getargc() {
	// check variable
	if( g_arguments.size() <= 0 ) {
        LOG_WARN( FMT( "\"setarguments\" function has not been called yet." ) )
	}

	return (int)g_arguments.size();
}

// get argument
const char* getargv( int index ) {
	// check variable
	if( g_arguments.size() <= 0 ) {
        LOG_WARN( FMT( "\"setarguments\" function has not been called yet." ) )
	}

	// check index
	if( index < 0 || index >= (int)g_arguments.size() ) {
        return nullptr;
	}

	return g_arguments[index].c_str();
}

// get extension
std::string getext( const char* path ) {
	// check parameter
    if( path == nullptr ) {
		return std::string( "" );
	}

	// find '.'
	std::string p( path );
	size_t pos = p.find_last_of( "." );
	if( pos == p.npos ) {
		return "";
	}
	
	return p.substr( pos + 1 );
}

// get environment variable
std::string getenvariable( const char* name ) {
	// check parameter
    if( name == nullptr ) {
		return std::string( "" );
	}

	// get environment variable
	std::string value;

#ifdef _MSC_VER
	size_t size = 0;
    char* v = nullptr;
	_dupenv_s( &v, &size, name );
    if( v != nullptr ) {
		value = std::string( v );
		delete[] v;
	}
#else
	char* v = getenv( name );
    if( v != nullptr ) {
		value = std::string( v );
	}

#endif	// _MSC_VER

	return value;
}

// get module file path
std::string getmodulefile() {
	// check global variables
	if( !g_moduleFile.empty() ) {
		return g_moduleFile;
	}
	if( g_arguments.size() <= 0 ) {
        LOG_WARN( FMT( "\"setarguments\" function has not been called yet." ) )
		return std::string( "" );
	}

	// get file name
	std::string program = getfilename( g_arguments[0].c_str() );
	std::string fileName = program;

#ifndef __unix		// Windows

	std::string ext = getext( fileName.c_str() );
	if( compareignorecase( ext.c_str(), "exe" ) != 0 ) {
		fileName.append( ".exe" );
	}

#endif	// __unix

	if( strcmp( program.c_str(), g_arguments[0].c_str() ) == 0 ) {	// search PATH
		// get environment variable "PATH"
#ifdef __unix		// unix
		std::string p = getenvariable( "PATH" );
#else		// windows
		std::string p = getenvariable( "Path" );
#endif		// __unix

		// creating search path list
		std::vector<std::string> paths; 
		stringtoken(
			p.c_str(),
			PATH_SEPARATOR, 
				paths
		);

#ifndef __unix		// Windows
		paths.insert(paths.begin(), std::string("."));
#endif	// __unix

		// search path
		for( unsigned int xx = 0; g_moduleFile.empty() && xx < paths.size(); xx++) {

			if( !paths[xx].empty() ) {
				try {
					std::string pgPath = getabsolutepath( paths[xx].c_str(), fileName.c_str() );
					if( fileexists( pgPath.c_str() ) ) {
								g_moduleFile = pgPath;
					}
				}
				catch( ... ) {
				}
			}
		}
	}
	else {	// specified directory
		g_moduleFile = getabsolutepath( getdir( g_arguments[0].c_str() ).c_str(), fileName.c_str() );
	}

	return g_moduleFile;
}

// get module file dir
std::string getmoduledir() {
	return getdir( getmodulefile().c_str() );
}

// get home directory
std::string gethomedir() {
	// check global variable
	if( !g_homeDir.empty() ) {
		return g_homeDir;
	}

	// get home dir
	std::string homeDir;

#ifdef __unix
	homeDir = getenvariable( "HOME" );
	if( homeDir.empty() ) {		
		homeDir = "~";
	}
#else
	std::string homeDrive = getenvariable( "HOMEDRIVE" );
	std::string homePath = getenvariable( "HOMEPATH" );
	homeDir = homeDrive + homePath;
#endif  // __unix
	g_homeDir = absolutepath( homeDir.c_str() );
	
	return g_homeDir;
}

// file open
FILE* fileopen( const char* path, const char* mode ) {
	// file descriptor
    FILE* fp = nullptr;

#ifdef _MSC_VER
	errno_t ret = fopen_s( &fp, path, mode );
	if( ret != 0 ) {
        fp = nullptr;
	}
#else
    /* fopen函数说明：
     * 原型：FILE * fopen ( const char * filename, const char * mode );
     * mode参数有：
     * "r"	read: 为输入操作打开文件，文件必须存在。
     * "w"	write: 为输出操作创建一个空文件，如果文件已存在，则将已有文件内容舍弃，按照空文件对待。
     * "a"	append: 为输出打开文件，输出操作总是再文件末尾追加数据，如果文件不存在，创建新文件。
     * 如果要以二进制形式打开，需要在模式中加上“b”
     */
	fp = fopen( path, mode );
#endif	// MSC_VER

	return fp;
}

// file seek
void fileseek( FILE* fp, long long offset, int origin ) {

#ifdef _MSC_VER
	_fseeki64( fp, offset, origin );
#else
	fseeko64( fp, offset, origin );
#endif
}

// file tell
long long filetell( FILE* fp ) {
	long long pos = 0;
#ifdef _MSC_VER
	pos = _ftelli64( fp );
#else
	pos = ftello64( fp );
#endif

	return pos;
}

// copy file
bool copyfile( const char* src, const char* dst ) {
	// buffer
	char buff[ 0x10000 ];

	// file open
	FILE* srcFp = fileopen( src, "rb" );
    if( srcFp == nullptr ) {
		return false;
	}

	FILE* dstFp = fileopen( dst, "wb" );
    if( dstFp == nullptr ) {
		return false;
	}

	// copy
	size_t len = int();
	while( ( len = fread( buff, 1, 0x10000, srcFp ) ) > 0 ) {
		fwrite( buff, 1, len, dstFp );
	}

	// close
	fflush( dstFp );
	fclose( dstFp );
	fclose( srcFp );

	return true;
}

// remove file
bool removefile( const char* path ) {
	// result
	int ret = 0;

#ifdef _MSC_VER
	ret = _unlink( path );
#else
	ret = unlink( path );
#endif

	if( ret != 0 ) {
        LOG_ERROR( FMT( "Failed to remove the file. [%s]", NVL( path, "" ) ) )
	}

	return ( ret == 0 );
}

// make directory
bool makedirectory( const char* path ) {
	// result
	int ret = 0;

#ifdef  _MSC_VER
	ret = _mkdir( path );
#else
    ret = mkdir( path/*, 0755 */);
#endif

	if( ret != 0 ) {
        LOG_ERROR( FMT( "Failed to create the directory. [%s]", NVL( path, "" ) ) )
	}

	return ( ret == 0 );
}

// remove directories
bool removedirs( const char* path ) {

//	// path object
//    boost::filesystem::path p( path/*, boost::filesystem::native */);
//	boost::filesystem::directory_iterator end;

//	// check
//	if( !boost::filesystem::exists( p ) ) {
//        LOG_WARN( FMT( "%s does not exist.", path ) )
//		return false;
//	}

//	// remove
//	bool ret = true;
//	if( boost::filesystem::is_directory( p ) ) {	// directory
//		for( boost::filesystem::directory_iterator it( p ); it != end; it++ ) {
//			boost::filesystem::path child = boost::filesystem::absolute( *it );
//			if( !removedirs( child.string().c_str() ) ) {
//				ret = false;
//			}
//		}

//#ifdef _MSC_VER
//		_rmdir( path );
//#else
//		rmdir( path );
//#endif
//	}
//	else {  // file
//		if( !removefile( path ) ) {
//			ret = false;
//		}
//	}

//	return ret;

    QString folderDir(path);
    QDir dir(folderDir);
    QFileInfoList fileList;
    QFileInfo curFile;
    if(!dir.exists())  {return false;}//文件不存，则返回false
    fileList=dir.entryInfoList(QDir::Dirs|QDir::Files
                               |QDir::Readable|QDir::Writable
                               |QDir::Hidden|QDir::NoDotAndDotDot
                               ,QDir::Name);
    while(fileList.size()>0)
    {
        int infoNum=fileList.size();
        for(int i=infoNum-1;i>=0;i--)
        {
            curFile=fileList[i];
            if(curFile.isFile())//如果是文件，删除文件
            {
                QFile fileTemp(curFile.filePath());
                fileTemp.remove();
                fileList.removeAt(i);
            }
            if(curFile.isDir())//如果是文件夹
            {
                QDir dirTemp(curFile.filePath());
                QFileInfoList fileList1=dirTemp.entryInfoList(QDir::Dirs|QDir::Files
                                                              |QDir::Readable|QDir::Writable
                                                              |QDir::Hidden|QDir::NoDotAndDotDot
                                                              ,QDir::Name);
                if(fileList1.size()==0)//下层没有文件或文件夹
                {
                    dirTemp.rmdir(".");
                    fileList.removeAt(i);
                }
                else//下层有文件夹或文件
                {
                    for(int j=0;j<fileList1.size();j++)
                    {
                        if(!(fileList.contains(fileList1[j])))
                            fileList.append(fileList1[j]);
                    }
                }
            }
        }
    }
    return true;
}

// make directories
bool makedirs( const char* path ) {
//	// path object
//    boost::filesystem::path p( path/*, boost::filesystem::native */);
//	p = boost::filesystem::absolute( p );

//	// check
//	if( boost::filesystem::exists( p ) ) {
//		return false;
//	}

//	// branch
//	bool ret = true;
//	boost::filesystem::path branche = p.branch_path();
//	if( !boost::filesystem::exists( branche ) ) {
//		if( !makedirs( branche.string().c_str() ) ) {
//			ret = false;
//		}
//	}

//	// make directory
//	if( ret ) {
//		ret = makedirectory( p.string().c_str() );
//	}

//	return ret;
    QString dir_str(path);
    // 检查目录是否存在，若不存在则新建
    QDir dir;
    bool res = false;
    if (!dir.exists(dir_str))
    {
        res = dir.mkpath(dir_str);
    }
    return res;
}

// get mspp plugin dir
std::string getplugindir(){
	std::string strDir;
	strDir = getenvariable( "MSPP_PLUGIN_DIR" );
	return strDir;
}

// file size
unsigned long long filesize( const char* path ) {
//	// path object
//    boost::filesystem::path p( path/*, boost::filesystem::native */);

//	// size
//	unsigned long long size = (unsigned long long)boost::filesystem::file_size( p );

//	return size;
    QString p(path);
    QFileInfo fileInfo(p);
    unsigned long long size = fileInfo.size();
    return size;
}

// search file
std::string searchfile( const char* dir, const char* fileName, const bool recursive ) {
//	// return value
//	std::string filePath;

//	// search files
//	std::vector< std::string > dirs;

//    boost::filesystem::path p( dir/*, boost::filesystem::native */);
//	if( !boost::filesystem::exists( p ) ) {
//		return filePath;
//	}

//	boost::filesystem::directory_iterator end;
//	for( boost::filesystem::directory_iterator it( p ); it != end && filePath.empty(); it++ ) {
//		std::string childName = (*it).path().leaf().string();
//		std::string child = getpath( dir, (*it).path().leaf().string().c_str() );

//		if( childName.compare( fileName ) == 0 ) {
//			filePath = child;
//		}
//		else if( isdirectory( child.c_str() ) ) {
//			dirs.push_back( child );
//		}
//	}

//	// search folders
//	if( recursive ) {
//		for( unsigned int i = 0; i < dirs.size() && filePath.empty(); i++ ) {
//			filePath = searchfile( dirs[ i ].c_str(), fileName, true );
//		}
//	}

//	return filePath;
    return "";
}
