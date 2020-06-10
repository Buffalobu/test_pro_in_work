/**
 * @file MsbIO0202.cpp
 * @brief implements of MsbIO0202 class
 *
 * @author H.Parry
 * @date 2011.04.20
 * 
 * Copyright(C) 2006-2014 Shimadzu Corporation. All rights reserved.
 */


#include "stdafx.h"
#include "MsbIO0202.h"

#include "MsbSample.h"
#include "MsbSampleSet.h"
#include "MsbSpectrum.h"
#include "MsbChromatogram.h"

#include <time.h>
#include <math.h>
//#include <zlib.h>
#include "zlib.h"

#include <QByteArray>

//#include <boost/any.hpp>

using namespace kome::io::msb;


#include <crtdbg.h>
#ifdef _DEBUG
    #define new new( _NORMAL_BLOCK, __FILE__, __LINE__ )
    #define malloc( s ) _malloc_dbg( s, _NORMAL_BLOCK, __FILE__, __LINE__ )
#endif    // _DEBUG



// static members
MsbManager::DataValue MsbIO0202::m_fileHeader[] = {
    DataValue( TYPE_ULONG,  (unsigned int)0 ),				  //  0: File Header Size
	DataValue( TYPE_UCHAR,  (unsigned char)0 ),				  //  1: Endian
    DataValue( TYPE_USHORT, (unsigned short)2 ),			  //  2: Major Version
    DataValue( TYPE_USHORT, (unsigned short)2 ),			  //  3: Minor Version
	DataValue( TYPE_STRING, (MsbString)0 ),					  //  4: Source File Path
	DataValue( TYPE_STRING, (MsbString)0 ),					  //  5: Sample Name
	DataValue( TYPE_STRING, (MsbString)0 ),					  //  6: Instrument
	DataValue( TYPE_STRING, (MsbString)0 ),					  //  7: Instrument
	DataValue( TYPE_STRING, (MsbString)0 ),					  //  8: Instrument
	DataValue( TYPE_STRING, (MsbString)0 ),					  //  9: Instrument

	DataValue( TYPE_ULONGLONG,  (unsigned long long)0 ),		 // 10: Spectrum Group Align
	DataValue( TYPE_ULONGLONG,  (unsigned long long)0 ),		 // 11: Spectrum Group Properties Align
	DataValue( TYPE_ULONGLONG,  (unsigned long long)0 ),		 // 12: Spectrum Group User Properties Align
	DataValue( TYPE_ULONGLONG,  (unsigned long long)0 ),		 // 13: Chromatogram Data Align
	DataValue( TYPE_ULONGLONG,  (unsigned long long)0 ),		 // 14: Chromatogram Align
	DataValue( TYPE_ULONGLONG,  (unsigned long long)0 ),		 // 15: Chromatogram Properties Align
	DataValue( TYPE_ULONGLONG,  (unsigned long long)0 ),		 // 16: Chromatogram User Properties Align
	DataValue( TYPE_ULONGLONG,  (unsigned long long)0 ),		 // 17: Spectrum Data Align
	DataValue( TYPE_ULONGLONG,  (unsigned long long)0 ),		 // 18: Spectrum Align
	DataValue( TYPE_ULONGLONG,  (unsigned long long)0 ),		 // 19: Spectrum Part Align
	DataValue( TYPE_ULONGLONG,  (unsigned long long)0 ),		 // 20: Spectrum Properties Align
	DataValue( TYPE_ULONGLONG,  (unsigned long long)0 ),		 // 21: Spectrum User Properties Align
	DataValue( TYPE_ULONGLONG,  (unsigned long long)0 ),		 // 22: String Table Align
	DataValue( TYPE_ULONG,  (unsigned int)0 ),				  // 23: Compressed String Table Size
	DataValue( TYPE_ULONG,  (unsigned int)0 ),				  // 24: Uncompressed String Table Size
	DataValue( TYPE_TIME,   (time_t)0 )						  // 25: Time
};

MsbManager::DataValue MsbIO0202::m_dataHeader[] = {
	DataValue( TYPE_ULONG, (unsigned int)0 ),		  //  0: header size
	DataValue( TYPE_ULONG, (unsigned int)0 ),		  //  1: data size
	DataValue( TYPE_ULONG, (unsigned int)0 )		   //  2: number of data
};

MsbManager::DataValue MsbIO0202::m_groupInfo[] = {
	DataValue( TYPE_ULONG,  (unsigned int)0 ),		 //  0: spectrum group ID
	DataValue( TYPE_STRING, (MsbString)0 ),			 //  1: spectrum group name
	DataValue( TYPE_ULONG,  (unsigned int)0 ),		 //  2: parent group ID
	DataValue( TYPE_STRING, (MsbString)0 ),			 //  3: spectrum x axis title
	DataValue( TYPE_STRING, (MsbString)0 ),			 //  4: spectrum y axis title
	DataValue( TYPE_STRING, (MsbString)0 ),			 //  5: chromatogram x axis title
    DataValue( TYPE_STRING, (MsbString)0 )			 //  6: chromatogram y axis title
};

MsbManager::DataValue MsbIO0202::m_chromatogramInfo[] = {
    DataValue( TYPE_ULONG,  (unsigned int)0 ),			 //  0: Chromatogram ID
    DataValue( TYPE_STRING, (MsbString)0 ),				 //  1: Chromatogram Name
	DataValue( TYPE_ULONG,  (unsigned int)0 ),			 //  2: Spectrum Group
	DataValue( TYPE_STRING, (MsbString)0 ),				 //  3: Title
	DataValue( TYPE_STRING, (MsbString)0 ),				 //  4: Icon Name
	DataValue( TYPE_ULONG,  (unsigned int)0 ),			 //  5: Length
	DataValue( TYPE_ULONGLONG, (unsigned long long)0 ),	 //  6: RT Data Align
	DataValue( TYPE_ULONGLONG, (unsigned long long)0 ),	 //  7: Intensity Data Align
	DataValue( TYPE_ULONGLONG, (unsigned long long)0 ),	 //  8: Mass Data Align
	DataValue( TYPE_ULONGLONG, (unsigned long long)0 ),	 //  9: MS Stage Data Align
    DataValue( TYPE_ULONGLONG, (unsigned long long)0 )	 // 10: Precursor Data Align
};

MsbManager::DataValue MsbIO0202::m_spectrumInfo[] = {
	DataValue( TYPE_ULONG,  (unsigned int)0 ),	  //  0: Spectrum ID
	DataValue( TYPE_STRING, (MsbString)0 ),		  //  1: Spectrum Name
	DataValue( TYPE_ULONG,  (unsigned int)0 ),	  //  2: Parent Spectrum
	DataValue( TYPE_ULONG,  (unsigned int)0 ),	  //  3: Spectrum Group
	DataValue( TYPE_USHORT, (unsigned short)0 ),	 //  4: MS Stage
	DataValue( TYPE_FLOAT,  (float)0.0f),			//  5: Precursor
	DataValue( TYPE_FLOAT,  (float)0.0f),			//  6: Start Retention Time
	DataValue( TYPE_FLOAT,  (float)0.0f),			//  7: End Retention Time
	DataValue( TYPE_FLOAT,  (float)0.0f),			//  8: min x
	DataValue( TYPE_FLOAT,  (float)0.0f),			//  9: max x
	DataValue( TYPE_FLOAT,  (float)0.0f),			// 10: tic
	DataValue( TYPE_FLOAT,  (float)0.0f),			// 11: bpc
	DataValue( TYPE_ULONG,  (unsigned int)0 ),	  // 12: Scan Number
	DataValue( TYPE_BOOL,   (bool)false ),		   // 13: Centroided
	DataValue( TYPE_FLOAT,  (float)0.2f ),		   // 14: Resolution
	DataValue( TYPE_CHAR,   (char)0 ),			   // 15: Polarity
	DataValue( TYPE_STRING, (MsbString)0 ),		  // 16: MS Type
	DataValue( TYPE_STRING, (MsbString)0 ),		  // 17: Title
	DataValue( TYPE_BOOL,   (bool)false ),		   // 18: Chromatogram Flag
	DataValue( TYPE_STRING, (MsbString)0 )		   // 19: Icon Name
};

MsbManager::DataValue MsbIO0202::m_partInfo[] = {
	DataValue( TYPE_ULONG, (unsigned int)0 ),				//  0: Spectrum
	DataValue( TYPE_ULONG, (unsigned int)0 ),				//  1: Data Length
	DataValue( TYPE_FLOAT, (float)0.0f ),					 //  2: Start m/z
	DataValue( TYPE_FLOAT, (float)0.0f ),					 //  3: End m/z
	DataValue( TYPE_FLOAT, (float)0.0f ),					 //  4: Total Intensity
	DataValue( TYPE_FLOAT, (float)0.0f ),					 //  5: Min Intensity
	DataValue( TYPE_FLOAT, (float)0.0f ),					 //  6: Max Intensity
	DataValue( TYPE_ULONGLONG, (unsigned long long)0 ),	   //  7: m/z Align
	DataValue( TYPE_ULONGLONG, (unsigned long long)0 )		//  8: Intensity Align
};

MsbManager::DataValue MsbIO0202::m_prop[] = {
	DataValue( TYPE_ULONG,  (unsigned int)0 ),	  //  0: Spectrum
	DataValue( TYPE_STRING, (MsbString)0 ),		  //  1: Property Key
	DataValue( TYPE_STRING, (MsbString)0 )		   //  2: Property Value
};

// constructor
MsbIO0202::MsbIO0202() {
}

// destructor
MsbIO0202::~MsbIO0202() {
}

// create string table
void MsbIO0202::createStringTable( char** stringTable ) {
	// get size
    unsigned long stringTableSize = m_fileHeader[ 24 ].val.ul; //24: Uncompressed String Table Size
	if( stringTableSize == 0 ) {
		return;
	}

	// keep position
    /*
     * ftello64()函数
     * 功能：returns the current position of the file pointer in a stream.
     */
    unsigned long long pos = filetell( m_fp );/*ftello64( m_fp );*/

	// create string table array
	char* st = new char[ stringTableSize ];
	*stringTable = st;

	// create buff
    unsigned int buffSize = m_fileHeader[ 23 ].val.ul;       // 23: Compressed String Table Size
    unsigned char* buff = new unsigned char[ buffSize ];
//    char* buff = new char[ buffSize ];

    unsigned long calu_len = compressBound(stringTableSize);
    calu_len ++;

	// read string table
    fileseek( m_fp, m_fileHeader[ 22 ].val.ull, SEEK_SET );  // 22: String Table Align
	fread( buff, 1, buffSize, m_fp );

	// uncompress
    uncompress( (Bytef*)st, &stringTableSize, buff, buffSize );

//    QByteArray data;
//    QString str = QString(buff);
//    data = qUncompress(data);

	// delete buffer
	delete[] buff;

	// restore position
	fileseek( m_fp, pos, SEEK_SET );
}

// get file header info
void MsbIO0202::getFileHeaderInfo( MsbSample& sample, char* stringTable ) {
	// add file info
    unsigned int mfp = m_fileHeader[ 4 ].val.ul;
    mfp++;
	sample.getMsbSampleSet()->setSourceFilePath( stringTable + m_fileHeader[ 4 ].val.ul );
	sample.setName( stringTable + m_fileHeader[ 5 ].val.ul );
	sample.setInstrument( stringTable + m_fileHeader[ 6 ].val.ul );
	sample.setMsCompany( stringTable + m_fileHeader[ 7 ].val.ul );
	sample.setSoftwareName( stringTable + m_fileHeader[ 8 ].val.ul );
    sample.setSoftwareVersion(stringTable + m_fileHeader[ 9 ].val.ul );
}

// read spectrum group
void MsbIO0202::readDataGroupNodes(
		kome::objects::DataGroupNode* parentGroup,
		std::map< unsigned int, kome::objects::DataGroupNode* >& groupMap,
		char* stringTable 
) {
	// read header
    READ_FROM_FILE( m_dataHeader ); //在m_fp文件读取时没有seek

	// check map
	if( groupMap.find( 0 ) == groupMap.end() ) {
		groupMap[ 0 ] = parentGroup;
	}
	// get size
    unsigned int size   = m_dataHeader[ 1 ].val.ul;  //  1: data size
    unsigned int length = m_dataHeader[ 2 ].val.ul;  //  2: number of data
	if( size == 0 || length == 0 ) {
		return;
	}

	// create buffer
	int cnt = 0x10000;
	unsigned char* buff = new unsigned char[ size * cnt ];
	int rest = (int)length;

	// get spectrum group
    unsigned char* pos = nullptr;
	for( unsigned int i = 0; i < length; i++ ) {
		// read
		if( i % cnt == 0 ) {
			int num = std::min( cnt, rest );
			fread( buff, size, cnt, m_fp );
			rest -= num;
			pos = buff;
		}

		// get data from buffer
		READ_FROM_BUFFER( m_groupInfo, pos );

		// parent group
		kome::objects::DataGroupNode* parent = groupMap[ m_groupInfo[ 2 ].val.ul ];

		// create group
		kome::objects::DataGroupNode* group
			= parent->createChildGroup( stringTable + m_groupInfo[ 1 ].val.ms );

		// set axis title
		group->setSpecXTitle( stringTable + m_groupInfo[ 3 ].val.ms );
		group->setSpecYTitle( stringTable + m_groupInfo[ 4 ].val.ms );
		group->setChromXTitle( stringTable + m_groupInfo[ 5 ].val.ms );
		group->setChromYTitle( stringTable + m_groupInfo[ 6 ].val.ms );

		// set to map
		groupMap[ m_groupInfo[ 0 ].val.ul ] = group;

		// move read position
		pos += size;
	}

	// delete buffer
	delete[] buff;
}

// read spectrum group properties
void MsbIO0202::readDataGroupNodeProperties(
		std::map< unsigned int, kome::objects::DataGroupNode* >& groupMap,
		char* stringTable
) {
   // read header
	READ_FROM_FILE( m_dataHeader );

	// get size
    unsigned int size   = m_dataHeader[ 1 ].val.ul;  // 1: data size
    unsigned int length = m_dataHeader[ 2 ].val.ul;  // 2: number of data
	if( size == 0 || length == 0 ) {
		return;
	}

	// create buffer
	int cnt = 0x10000;
	unsigned char* buff = new unsigned char[ size * cnt ];
	int rest = (int)length;

	// get spectrra
    unsigned char* pos = nullptr;
	for( unsigned int i = 0; i < length; i++ ) {
		// read
		if( i % cnt == 0 ) {
			int num = std::min( cnt, rest );
			fread( buff, size, cnt, m_fp );
			rest -= num;
			pos = buff;
		}

		// get data from buffer
		READ_FROM_BUFFER( m_prop, pos );

		// get spectrum
        kome::objects::DataGroupNode* group = groupMap[ m_prop[ 0 ].val.ul ];  //  0: Spectrum

		// add property
		group->getProperties().setValue(
            stringTable + m_prop[ 1 ].val.ms,  //  1: Property Key
            stringTable + m_prop[ 2 ].val.ms   //  2: Property Value
		);

		// move read position
		pos += size;
	}

	// delete buffer
	delete[] buff;
}

// read spectrum group user properties
void MsbIO0202::readDataGroupNodeUserProperties(
		std::map< unsigned int, kome::objects::DataGroupNode* >& groupMap,
		char* stringTable
) {
   // read header
	READ_FROM_FILE( m_dataHeader );

	// get size
	unsigned int size   = m_dataHeader[ 1 ].val.ul;
	unsigned int length = m_dataHeader[ 2 ].val.ul;
	if( size == 0 || length == 0 ) {
		return;
	}

	// create buffer
	int cnt = 0x10000;
	unsigned char* buff = new unsigned char[ size * cnt ];
	int rest = (int)length;

    // get spectra
    unsigned char* pos = nullptr;
	for( unsigned int i = 0; i < length; i++ ) {
		// read
		if( i % cnt == 0 ) {
			int num = std::min( cnt, rest );
			fread( buff, size, cnt, m_fp );
			rest -= num;
			pos = buff;
		}

		// get data from buffer
		READ_FROM_BUFFER( m_prop, pos );

		// get spectrum
        kome::objects::DataGroupNode* group = groupMap[ m_prop[ 0 ].val.ul ];  //  0: Spectrum
		// add user property
		group->getUserProperties().setValue(
            stringTable + m_prop[ 1 ].val.ms,  //  1: Property Key
            stringTable + m_prop[ 2 ].val.ms   //  2: Property Value
		);

		// move read position
		pos += size;
	}

	// delete buffer
	delete[] buff;
}

// read chromatograms
void MsbIO0202::readChromatograms(
		MsbSample& sample,
		std::map< unsigned int, MsbChromatogram* >& chromMap,
		std::map< unsigned int, kome::objects::DataGroupNode* >& groupMap,
		char* stringTable
) {
	// read header
	READ_FROM_FILE( m_dataHeader );

	// get size
	unsigned int size   = m_dataHeader[ 1 ].val.ul;
	unsigned int length = m_dataHeader[ 2 ].val.ul;
	if( size == 0 || length == 0 ) {
		return;
	}

	// create buffer
	int cnt = 0x10000;
	unsigned char* buff = new unsigned char[ size * cnt ];
	int rest = (int)length;

    // get spectra
    unsigned char* pos = nullptr;
	for( unsigned int i = 0; i < length; i++ ) {
		// read
		if( i % cnt == 0 ) {
			int num = std::min( cnt, rest );
			fread( buff, size, cnt, m_fp );
			rest -= num;
			pos = buff;
		}

		// get data from buffer
		READ_FROM_BUFFER( m_chromatogramInfo, pos );

		// create chromatogram
		MsbChromatogram* chrom = new MsbChromatogram( &sample, m_fp );

		// add to group
		groupMap[ m_chromatogramInfo[ 2 ].val.ul ]->addChromatogram( chrom );

		// ID
		chromMap[ m_chromatogramInfo[ 0 ].val.ul ] = chrom;

		// set info
		chrom->setName( stringTable + m_chromatogramInfo[ 1 ].val.ms );
		chrom->setTitle( stringTable + m_chromatogramInfo[ 3 ].val.ms );
		chrom->setIcon( stringTable + m_chromatogramInfo[ 4 ].val.ms );
		chrom->setDataLength( m_chromatogramInfo[ 5 ].val.ul );
		chrom->setRtDataAlign( m_chromatogramInfo[ 6 ].val.ull );
		chrom->setIntensityDataAlign( m_chromatogramInfo[ 7 ].val.ull );
		chrom->setMassDataAlign( m_chromatogramInfo[ 8 ].val.ull );
		chrom->setMsStageDataAlign( m_chromatogramInfo[ 9 ].val.ull );
		chrom->setPrecursorDataAlign( m_chromatogramInfo[ 10 ].val.ull );

		// move read position
		pos += size;
	}

	// delete buffer
	delete[] buff;
}

// read chromatogram property
void MsbIO0202::readChromatogramProperties(
		std::map< unsigned int, MsbChromatogram* >& chromMap,
		char* stringTable
		
){
	// read header
	READ_FROM_FILE( m_dataHeader );

	// get size
	unsigned int size   = m_dataHeader[ 1 ].val.ul;
	unsigned int length = m_dataHeader[ 2 ].val.ul;
	if( size == 0 || length == 0 ) {
		return;
	}

	// create buffer
	int cnt = 0x10000;
	unsigned char* buff = new unsigned char[ size * cnt ];
	int rest = (int)length;

	// get chromatograms properties
	unsigned char* pos = buff;
	for( unsigned int i = 0; i < length; i++ ) {
		// read
		if( i % cnt == 0 ) {
			int num = std::min( cnt, rest );
			fread( buff, size, cnt, m_fp );
			rest -= num;
			pos = buff;
		}

		// get data from buffer
		READ_FROM_BUFFER( m_prop, pos );

		// get spectrum
		MsbChromatogram* chrom = chromMap[ m_prop[ 0 ].val.ul ];

		// add property
		chrom->getProperties().setValue(
			stringTable + m_prop[ 1 ].val.ms,
			stringTable + m_prop[ 2 ].val.ms
		);

		// move read position
		pos += size;
	}

	// delete buffer
	delete[] buff;
}

// read chromatogram user property
void MsbIO0202::readChromatogramUserProperties(
		std::map< unsigned int, MsbChromatogram* >& chromMap,
		char* stringTable
		
){
	// read header
	READ_FROM_FILE( m_dataHeader );

	// get size
	unsigned int size   = m_dataHeader[ 1 ].val.ul;
	unsigned int length = m_dataHeader[ 2 ].val.ul;
	if( size == 0 || length == 0 ) {
		return;
	}

	// create buffer
	int cnt = 0x10000;
	unsigned char* buff = new unsigned char[ size * cnt ];
	int rest = (int)length;

	// get chromatograms user properties
	unsigned char* pos = buff;
	for( unsigned int i = 0; i < length; i++ ) {
		// read
		if( i % cnt == 0 ) {
			int num = std::min( cnt, rest );
			fread( buff, size, cnt, m_fp );
			rest -= num;
			pos = buff;
		}

		// get data from buffer
		READ_FROM_BUFFER( m_prop, pos );

		// get chromatogram
		MsbChromatogram* chrom = chromMap[ m_prop[ 0 ].val.ul ];

		// add user property
		chrom->getUserProperties().setValue(
			stringTable + m_prop[ 1 ].val.ms,
			stringTable + m_prop[ 2 ].val.ms
		);

		// move read position
		pos += size;
	}

	// delete buffer
	delete[] buff;
}

// read spectra
void MsbIO0202::readSpectra(
		MsbSample& sample,
		std::map< unsigned int, MsbSpectrum* >& specMap,
		std::map< unsigned int, kome::objects::DataGroupNode* >& groupMap,
		char* stringTable
) {
	// read header
	READ_FROM_FILE( m_dataHeader );

	// check map
	if( specMap.find( 0 ) == specMap.end() ) {
        specMap[ 0 ] = nullptr;
	}

	// get size
	unsigned int size   = m_dataHeader[ 1 ].val.ul;
	unsigned int length = m_dataHeader[ 2 ].val.ul;
	if( size == 0 || length == 0 ) {
		return;
	}

	// create buffer
	int cnt = 0x10000;
	unsigned char* buff = new unsigned char[ size * cnt ];
	int rest = (int)length;

	// get spectrra
	unsigned char* pos = buff;
	for( unsigned int i = 0; i < length; i++ ) {
		// read
		if( i % cnt == 0 ) {
			int num = std::min( cnt, rest );
			fread( buff, size, cnt, m_fp );
			rest -= num;
			pos = buff;
		}

		// get data from buffer
		READ_FROM_BUFFER( m_spectrumInfo, pos );

		// create spectrum
		MsbSpectrum* spec = new MsbSpectrum(
			&sample,
			stringTable + m_spectrumInfo[ 1 ].val.ms,
			m_fp
		);

		// add to group
		groupMap[ m_spectrumInfo[ 3 ].val.ul ]->addSpectrum( spec );

		// ID
		specMap[ m_spectrumInfo[ 0 ].val.ul ] = spec;

		// set info
		spec->setParentSpectrum( specMap[ m_spectrumInfo[ 2 ].val.ul ] );
		spec->setMsStage( m_spectrumInfo[ 4 ].val.us );
		spec->setPrecursor( (double)m_spectrumInfo[ 5 ].val.f );
		spec->setRt(
			(double)m_spectrumInfo[ 6 ].val.f,
			(double)m_spectrumInfo[ 7 ].val.f
		);

		spec->setXRange( (double)m_spectrumInfo[ 8 ].val.f, (double)m_spectrumInfo[ 9 ].val.f );
		spec->setTotalIntensity( (double)m_spectrumInfo[ 10 ].val.f );
		spec->setMaxIntensity( (double)m_spectrumInfo[ 11 ].val.f );

		spec->setScanNumber( m_spectrumInfo[ 12 ].val.ul );
		spec->setCentroidMode( m_spectrumInfo[ 13 ].val.b );
		spec->setResolution( m_spectrumInfo[ 14 ].val.f );

		char polarity = m_spectrumInfo[ 15 ].val.c;
		if( polarity < 0 ) {
			spec->setPolarity( kome::objects::Spectrum::POLARITY_NEGATIVE );
		}
		else if( polarity > 0 ) {
			spec->setPolarity( kome::objects::Spectrum::POLARITY_POSITIVE );
		}
		else {
			spec->setPolarity( kome::objects::Spectrum::POLARITY_UNKNOWN );
		}

		spec->setSpecType( stringTable + m_spectrumInfo[ 16 ].val.ms );
		spec->setTitle( stringTable + m_spectrumInfo[ 17 ].val.ms );
		spec->setHasChromatogram( m_spectrumInfo[ 18 ].val.b );
		spec->setIcon( stringTable + m_spectrumInfo[ 19 ].val.ms );

		// move read position
		pos += size;
	}

	// delete buffer
	delete[] buff;
}

// read spectrum part
void MsbIO0202::readSpectrumParts(
		std::map< unsigned int, MsbSpectrum* >& specMap
){
	// read header
	READ_FROM_FILE( m_dataHeader );

	// get size
	unsigned int size   = m_dataHeader[ 1 ].val.ul;
	unsigned int length = m_dataHeader[ 2 ].val.ul;
	if( size == 0 || length == 0 ) {
		return;
	}

	// create buffer
	int cnt = 0x10000;
	unsigned char* buff = new unsigned char[ size * cnt ];
	int rest = (int)length;

	// get spectrra
    unsigned char* pos = nullptr;
	for( unsigned int i = 0; i < length; i++ ) {
		// read
		if( i % cnt == 0 ) {
			int num = std::min( cnt, rest );
			fread( buff, size, cnt, m_fp );
			rest -= num;
			pos = buff;
		}

		// get data from buffer
		READ_FROM_BUFFER( m_partInfo, pos );

		// get spectrum
		MsbSpectrum* spec = specMap[ m_partInfo[ 0 ].val.ul ];

		// add part
		spec->addPart(
			m_partInfo[ 1 ].val.ul,
			m_partInfo[ 2 ].val.f,
			m_partInfo[ 3 ].val.f,
			m_partInfo[ 4 ].val.f,
			m_partInfo[ 5 ].val.f,
			m_partInfo[ 6 ].val.f,
			m_partInfo[ 7 ].val.ull,
			m_partInfo[ 8 ].val.ull
		);

		// move read position
		pos += size;
	}

	// delete buffer
	delete[] buff;
}

// read spectrum property
void MsbIO0202::readSpectrumProperties(
		std::map< unsigned int, MsbSpectrum* >& specMap,
		char* stringTable
		
){
	// read header
	READ_FROM_FILE( m_dataHeader );

	// get size
	unsigned int size   = m_dataHeader[ 1 ].val.ul;
	unsigned int length = m_dataHeader[ 2 ].val.ul;
	if( size == 0 || length == 0 ) {
		return;
	}

	// create buffer
	int cnt = 0x10000;
	unsigned char* buff = new unsigned char[ size * cnt ];
	int rest = (int)length;

	// get spectrra
    unsigned char* pos = nullptr;
	for( unsigned int i = 0; i < length; i++ ) {
		// read
		if( i % cnt == 0 ) {
			int num = std::min( cnt, rest );
			fread( buff, size, cnt, m_fp );
			rest -= num;
			pos = buff;
		}

		// get data from buffer
		READ_FROM_BUFFER( m_prop, pos );

		// get spectrum
		MsbSpectrum* spec = specMap[ m_prop[ 0 ].val.ul ];

		// add property
		spec->getProperties().setValue(
			stringTable + m_prop[ 1 ].val.ms,
			stringTable + m_prop[ 2 ].val.ms
		);

		// move read position
		pos += size;
	}

	// delete buffer
	delete[] buff;
}

// read spectrum user property
void MsbIO0202::readSpectrumUserProperties(
		std::map< unsigned int, MsbSpectrum* >& specMap,
		char* stringTable
		
){
	// read header
	READ_FROM_FILE( m_dataHeader );

	// get size
	unsigned int size   = m_dataHeader[ 1 ].val.ul;
	unsigned int length = m_dataHeader[ 2 ].val.ul;
	if( size == 0 || length == 0 ) {
		return;
	}

	// create buffer
	int cnt = 0x10000;
	unsigned char* buff = new unsigned char[ size * cnt ];
	int rest = (int)length;

	// get spectrra
    unsigned char* pos = nullptr;
	for( unsigned int i = 0; i < length; i++ ) {
		// read
		if( i % cnt == 0 ) {
			int num = std::min( cnt, rest );
			fread( buff, size, cnt, m_fp );
			rest -= num;
			pos = buff;
		}

		// get data from buffer
		READ_FROM_BUFFER( m_prop, pos );

		// get spectrum
		MsbSpectrum* spec = specMap[ m_prop[ 0 ].val.ul ];

		// add user property
		spec->getUserProperties().setValue(
			stringTable + m_prop[ 1 ].val.ms,
			stringTable + m_prop[ 2 ].val.ms
		);

		// move read position
		pos += size;
	}

	// delete buffer
	delete[] buff;
}

// write Simplify spectrum groups
void MsbIO0202::writeSimplifyDataGroupNodes(unsigned int frameCnt ) {
    // spectrum group data size
    unsigned int dataSize = GET_DATA_SIZE( m_groupInfo );

    // header
    m_dataHeader[ 0 ].val.ul = GET_DATA_SIZE( m_dataHeader );	// header size
    m_dataHeader[ 1 ].val.ul = dataSize;						// spectrum group size
    m_dataHeader[ 2 ].val.ul = frameCnt;					// number of spectrum groups

    // write header
    WRITE_TO_FILE( m_dataHeader );
    if( frameCnt == 0 ) {
        return;
    }

    // buffer
    unsigned int size = dataSize * frameCnt;
    unsigned char* buff = new unsigned char[ size ];
    unsigned char* pos = buff;

    // write group data
    for( unsigned int i = 0; i < frameCnt; i++ ) {
        // group
//        kome::objects::DataGroupNode* group = groups[ i ];

        // ID
        unsigned id =  i + 1;
        m_groupInfo[ 0 ].val.ul = id;						  // Spectrum Group ID

        // name
        m_groupInfo[ 1 ].val.ms = st( "group->getName()" );	  // Spectrum Group Name

        // parent
        unsigned int parent = 0;
//        if( group->getParentGroup() != nullptr ) {
//            parent = groupMap[ group->getParentGroup() ];
//        }
        m_groupInfo[ 2 ].val.ul = parent;					  // Parent Spectrum Group

        // axis title
        m_groupInfo[ 3 ].val.ms = st( /*group->getSpecXTitle()*/ "m/z");
        m_groupInfo[ 4 ].val.ms = st( /*group->getSpecYTitle()*/ "intensity" );
        m_groupInfo[ 5 ].val.ms = st( /*group->getChromXTitle()*/ "RT" );
        m_groupInfo[ 6 ].val.ms = st( /*group->getChromYTitle()*/ "intensity");

        // write to buffer
        WRITE_TO_BUFFER( m_groupInfo, pos );
        pos += dataSize;
    }

    // write to file
    size_t stReturnValue = fwrite( buff, 1, size, m_fp );	// @date 2013/06/27 <Mod> OKADA
    if( stReturnValue != size ){							// @date 2013/06/27 <Add> OKADA
        LOG_ERROR( FMT( "Writing MSB file error in writeDataGroupNodes(). "
                        "Return value and item size of fwrite() disagree. "
                        "Return value=%d, Item size=%d. errno=%d", stReturnValue, size, errno ) )	// @date 2013/06/27 <Add> OKADA
    }														// @date 2013/06/27 <Add> OKADA

    // delete buffer
    delete[] buff;
}

// write spectrum groups
void MsbIO0202::writeDataGroupNodes(
		std::vector< kome::objects::DataGroupNode* >& groups,
		std::map< kome::objects::DataGroupNode*, unsigned int >& groupMap
) {
	// spectrum group data size
	unsigned int dataSize = GET_DATA_SIZE( m_groupInfo );

	// header
	m_dataHeader[ 0 ].val.ul = GET_DATA_SIZE( m_dataHeader );	// header size
    m_dataHeader[ 1 ].val.ul = dataSize;						// spectrum group size
	m_dataHeader[ 2 ].val.ul = groups.size();					// number of spectrum groups

	// write header
	WRITE_TO_FILE( m_dataHeader );
	if( groups.size() == 0 ) {
		return;
	}

	// buffer
	unsigned int size = dataSize * groups.size();
	unsigned char* buff = new unsigned char[ size ];
	unsigned char* pos = buff;

	// write group data
	for( unsigned int i = 0; i < groups.size(); i++ ) {
		// group
		kome::objects::DataGroupNode* group = groups[ i ];

		// ID		
		unsigned id =  i + 1;
		groupMap[ group ] = id;
		m_groupInfo[ 0 ].val.ul = id;						  // Spectrum Group ID

		// name
		m_groupInfo[ 1 ].val.ms = st( group->getName() );	  // Spectrum Group Name

		// parent
		unsigned int parent = 0;
        if( group->getParentGroup() != nullptr ) {
			parent = groupMap[ group->getParentGroup() ];
		}
		m_groupInfo[ 2 ].val.ul = parent;					  // Parent Spectrum Group

		// axis title
		m_groupInfo[ 3 ].val.ms = st( group->getSpecXTitle() );
		m_groupInfo[ 4 ].val.ms = st( group->getSpecYTitle() );
		m_groupInfo[ 5 ].val.ms = st( group->getChromXTitle() );
		m_groupInfo[ 6 ].val.ms = st( group->getChromYTitle() );

		// write to buffer
		WRITE_TO_BUFFER( m_groupInfo, pos );
		pos += dataSize;
	}

	// write to file
	size_t stReturnValue = fwrite( buff, 1, size, m_fp );	// @date 2013/06/27 <Mod> OKADA
	if( stReturnValue != size ){							// @date 2013/06/27 <Add> OKADA
        LOG_ERROR( FMT( "Writing MSB file error in writeDataGroupNodes(). "
                        "Return value and item size of fwrite() disagree. "
                        "Return value=%d, Item size=%d. errno=%d", stReturnValue, size, errno ) )	// @date 2013/06/27 <Add> OKADA
	}														// @date 2013/06/27 <Add> OKADA

	// delete buffer
	delete[] buff;
}

// write  Simplify spectrum group properties
void MsbIO0202::writeSimplifyDataGroupNodeProperties( unsigned int frameCnt ) {
    // get properties
    std::vector< Prop > properties;

    for( unsigned i = 0; i < frameCnt; i++ ) {
        // spectrum group
//        kome::objects::DataGroupNode* group = groups[ i ];
        unsigned int id = i/*groupMap[ group ]*/;

        // property
        kome::core::Properties props /*= group->getProperties()*/;
        props.setValue("SimplifyDataGroupNodePropertieskey1", "DataGroupNodevalue1");
        props.setValue("SimplifyDataGroupNodePropertieskey2", "DataGroupNodevalue2");

        // add to array
        unsigned int idx = properties.size();
        unsigned int num = props.getNumberOfProperties();
        if( num > 0 ) {
            // resize
            properties.resize( idx + num );

            // set value
            for( unsigned int j = 0; j < num; j++ ) {
                Prop& prop = properties[ idx + j ];
                prop.id = id;
                prop.key = st( props.getKey( j ) );
                prop.value = st( props.getValue( j ) );
            }
        }
    }

    // spectrum property data size
    unsigned int dataSize = GET_DATA_SIZE( m_prop );

    // header
    m_dataHeader[ 0 ].val.ul = GET_DATA_SIZE( m_dataHeader );	// header size
    m_dataHeader[ 1 ].val.ul = dataSize;						 // spectrum property size
    m_dataHeader[ 2 ].val.ul = properties.size();				// number of spectrum properties

    // write header
    WRITE_TO_FILE( m_dataHeader );
    if( properties.size() == 0 ) {
        return;
    }

    // buffer
    unsigned int size = dataSize * properties.size();
    unsigned char* buff = new unsigned char[ size ];
    unsigned char* pos = buff;

    // write to buffer
    for( unsigned int i = 0; i < properties.size(); i++ ) {
        // property
        Prop& prop = properties[ i ];

        // set data
        m_prop[ 0 ].val.ul = prop.id;	   // Spectrum ID
        m_prop[ 1 ].val.ms = prop.key;	  // Property Key
        m_prop[ 2 ].val.ms = prop.value;	// Property Value

        // write to header
        WRITE_TO_BUFFER( m_prop, pos );
        pos += dataSize;
    }

    // write to file
    size_t stReturnValue = fwrite( buff, 1, size, m_fp );	// @date 2013/06/27 <Mod> OKADA
    if( stReturnValue != size ){							// @date 2013/06/27 <Add> OKADA
        LOG_ERROR( FMT( "Writing MSB file error in writeDataGroupNodeProperties(). Return value and item size of fwrite() disagree. Return value=%d, Item size=%d. errno=%d", stReturnValue, size, errno ) );	// @date 2013/06/27 <Add> OKADA
    }														// @date 2013/06/27 <Add> OKADA

    // delete buffer
    delete[] buff;

}

// write spectrum group properties
void MsbIO0202::writeDataGroupNodeProperties(
		std::vector< kome::objects::DataGroupNode* >& groups,
		std::map< kome::objects::DataGroupNode*, unsigned int >& groupMap
) {
	// get properties
	std::vector< Prop > properties;

	for( unsigned i = 0; i < groups.size(); i++ ) {
		// spectrum group
		kome::objects::DataGroupNode* group = groups[ i ];
		unsigned int id = groupMap[ group ];

		// property
		kome::core::Properties& props = group->getProperties();

		// add to array
		unsigned int idx = properties.size();
		unsigned int num = props.getNumberOfProperties();
		if( num > 0 ) {
			// resize
			properties.resize( idx + num );

			// set value
			for( unsigned int j = 0; j < num; j++ ) {
				Prop& prop = properties[ idx + j ];
				prop.id = id;
				prop.key = st( props.getKey( j ) );
				prop.value = st( props.getValue( j ) );
			}
		}
	}

	// spectrum property data size
	unsigned int dataSize = GET_DATA_SIZE( m_prop );

	// header
	m_dataHeader[ 0 ].val.ul = GET_DATA_SIZE( m_dataHeader );	// header size
	m_dataHeader[ 1 ].val.ul = dataSize;						 // spectrum property size
	m_dataHeader[ 2 ].val.ul = properties.size();				// number of spectrum properties

	// write header
	WRITE_TO_FILE( m_dataHeader );
	if( properties.size() == 0 ) {
		return;
	}

	// buffer
	unsigned int size = dataSize * properties.size();
	unsigned char* buff = new unsigned char[ size ];
	unsigned char* pos = buff;

	// write to buffer
	for( unsigned int i = 0; i < properties.size(); i++ ) {
		// property
		Prop& prop = properties[ i ];

		// set data
		m_prop[ 0 ].val.ul = prop.id;	   // Spectrum ID
		m_prop[ 1 ].val.ms = prop.key;	  // Property Key
		m_prop[ 2 ].val.ms = prop.value;	// Property Value

		// write to header
		WRITE_TO_BUFFER( m_prop, pos );
		pos += dataSize;
	}

	// write to file
	size_t stReturnValue = fwrite( buff, 1, size, m_fp );	// @date 2013/06/27 <Mod> OKADA
	if( stReturnValue != size ){							// @date 2013/06/27 <Add> OKADA
		LOG_ERROR( FMT( "Writing MSB file error in writeDataGroupNodeProperties(). Return value and item size of fwrite() disagree. Return value=%d, Item size=%d. errno=%d", stReturnValue, size, errno ) );	// @date 2013/06/27 <Add> OKADA
	}														// @date 2013/06/27 <Add> OKADA

	// delete buffer
	delete[] buff;

}

// write Simplify spectrum group user properties
void MsbIO0202::writeSimplifyDataGroupNodeUserProperties(unsigned int frameCnt ){
    // get properties
    std::vector< Prop > properties;

    for( unsigned i = 0; i < frameCnt; i++ ) {
        // spectrum group
//        kome::objects::DataGroupNode* group = groups[ i ];
        unsigned int id = i/*groupMap[ group ]*/;

        // property
        kome::core::Properties props /*= group->getUserProperties()*/;
        props.setValue("SimplifyDataGroupNodeUserPropertieskey1", "SimplifyDataGroupNodeUserPropertiesvalue1");
        props.setValue("SimplifyDataGroupNodeUserPropertieskey2", "SimplifyDataGroupNodeUserPropertiesvalue2");
        // add to array
        unsigned int idx = properties.size();
        unsigned int num = props.getNumberOfProperties();
        if( num > 0 ) {
            // resize
            properties.resize( idx + num );

            // set value
            for( unsigned int j = 0; j < num; j++ ) {
                Prop& prop = properties[ idx + j ];
                prop.id = id;
                prop.key = st( props.getKey( j ) );
                prop.value = st( props.getValue( j ) );
            }
        }
    }

    // spectrum user property data size
    unsigned int dataSize = GET_DATA_SIZE( m_prop );

    // header
    m_dataHeader[ 0 ].val.ul = GET_DATA_SIZE( m_dataHeader );	// header size
    m_dataHeader[ 1 ].val.ul = dataSize;						 // spectrum user property size
    m_dataHeader[ 2 ].val.ul = properties.size();				// number of spectrum user properties

    // write header
    WRITE_TO_FILE( m_dataHeader );
    if( properties.size() == 0 ) {
        return;
    }

    // buffer
    unsigned int size = dataSize * properties.size();
    unsigned char* buff = new unsigned char[ size ];
    unsigned char* pos = buff;

    // write to buffer
    for( unsigned int i = 0; i < properties.size(); i++ ) {
        // property
        Prop& prop = properties[ i ];

        // set data
        m_prop[ 0 ].val.ul = prop.id;	   // Spectrum ID
        m_prop[ 1 ].val.ms = prop.key;	  // Property Key
        m_prop[ 2 ].val.ms = prop.value;	// Property Value

        // write to header
        WRITE_TO_BUFFER( m_prop, pos );
        pos += dataSize;
    }

    // write to file
    size_t stReturnValue = fwrite( buff, 1, size, m_fp );	// @date 2013/06/27 <Mod> OKADA
    if( stReturnValue != size ){							// @date 2013/06/27 <Add> OKADA
        LOG_ERROR( FMT( "Writing MSB file error in writeDataGroupNodeUserProperties(). Return value and item size of fwrite() disagree. Return value=%d, Item size=%d. errno=%d", stReturnValue, size, errno ) );	// @date 2013/06/27 <Add> OKADA
    }														// @date 2013/06/27 <Add> OKADA

    // delete buffer
    delete[] buff;

}


// write spectrum group user properties
void MsbIO0202::writeDataGroupNodeUserProperties(
		std::vector< kome::objects::DataGroupNode* >& groups,
		std::map< kome::objects::DataGroupNode*, unsigned int >& groupMap
) {
	// get properties
	std::vector< Prop > properties;

	for( unsigned i = 0; i < groups.size(); i++ ) {
		// spectrum group
		kome::objects::DataGroupNode* group = groups[ i ];
		unsigned int id = groupMap[ group ];

		// property
		kome::core::Properties& props = group->getUserProperties();

		// add to array
		unsigned int idx = properties.size();
		unsigned int num = props.getNumberOfProperties();
		if( num > 0 ) {
			// resize
			properties.resize( idx + num );

			// set value
			for( unsigned int j = 0; j < num; j++ ) {
				Prop& prop = properties[ idx + j ];
				prop.id = id;
				prop.key = st( props.getKey( j ) );
				prop.value = st( props.getValue( j ) );
			}
		}
	}

	// spectrum user property data size
	unsigned int dataSize = GET_DATA_SIZE( m_prop );

	// header
	m_dataHeader[ 0 ].val.ul = GET_DATA_SIZE( m_dataHeader );	// header size
	m_dataHeader[ 1 ].val.ul = dataSize;						 // spectrum user property size
	m_dataHeader[ 2 ].val.ul = properties.size();				// number of spectrum user properties

	// write header
	WRITE_TO_FILE( m_dataHeader );
	if( properties.size() == 0 ) {
		return;
	}

	// buffer
	unsigned int size = dataSize * properties.size();
	unsigned char* buff = new unsigned char[ size ];
	unsigned char* pos = buff;

	// write to buffer
	for( unsigned int i = 0; i < properties.size(); i++ ) {
		// property
		Prop& prop = properties[ i ];

		// set data
		m_prop[ 0 ].val.ul = prop.id;	   // Spectrum ID
		m_prop[ 1 ].val.ms = prop.key;	  // Property Key
		m_prop[ 2 ].val.ms = prop.value;	// Property Value

		// write to header
		WRITE_TO_BUFFER( m_prop, pos );
		pos += dataSize;
	}

	// write to file
	size_t stReturnValue = fwrite( buff, 1, size, m_fp );	// @date 2013/06/27 <Mod> OKADA
	if( stReturnValue != size ){							// @date 2013/06/27 <Add> OKADA
		LOG_ERROR( FMT( "Writing MSB file error in writeDataGroupNodeUserProperties(). Return value and item size of fwrite() disagree. Return value=%d, Item size=%d. errno=%d", stReturnValue, size, errno ) );	// @date 2013/06/27 <Add> OKADA
	}														// @date 2013/06/27 <Add> OKADA

	// delete buffer
	delete[] buff;

}

// write chromatogram data
void MsbIO0202::writeChromatogramData(
		unsigned int id,
		kome::objects::Chromatogram& chrom,
		kome::core::DataPoints& points,
		std::vector< ChromatogramDataInfo >& chromData
) {
	// number of points
	unsigned int length = points.getLength();

	// create data
	chromData.resize( chromData.size() + 1 );
	ChromatogramDataInfo& cdi = chromData.back();

	cdi.chrom = &chrom;
	cdi.length = length;
	cdi.rtAlign = 0;
	cdi.intAlign = 0;
	cdi.massAlign = 0;
	cdi.msStageAlign = 0;
	cdi.precursorAlign = 0;
	if( length == 0 ) {
		return;
	}

	// array
	float* fltArr = new float[ length ];
	int* lngArr = new int[ length ];

	// write RT data
	cdi.rtAlign = filetell( m_fp );
	size_t stReturnValue = fwrite( points.getXData(), sizeof( float ), length, m_fp );	// @date 2013/06/27 <Mod> OKADA
	if( stReturnValue !=  length ){							// @date 2013/06/27 <Add> OKADA
		LOG_ERROR( FMT( "[1]Writing MSB file error in writeChromatogramData(). Return value and item size of fwrite() disagree. Return value=%d, Item size=%d. errno=%d", stReturnValue, length, errno ) );	// @date 2013/06/27 <Add> OKADA
	}														// @date 2013/06/27 <Add> OKADA

	// write intensity data
	cdi.intAlign = filetell( m_fp );
	stReturnValue = fwrite( points.getYData(), sizeof( float ), length, m_fp );	// @date 2013/06/27 <Mod> OKADA
	if( stReturnValue != length ){							// @date 2013/06/27 <Add> OKADA
		LOG_ERROR( FMT( "[2]Writing MSB file error in writeChromatogramData(). Return value and item size of fwrite() disagree. Return value=%d, Item size=%d. errno=%d", stReturnValue, length, errno ) );	// @date 2013/06/27 <Add> OKADA
	}														// @date 2013/06/27 <Add> OKADA

	// write mass data
	for( unsigned int i = 0; i < length; i++ ) {
		fltArr[ i ] = (float)chrom.getMass( i );
	}

	cdi.massAlign = filetell( m_fp );
	stReturnValue = fwrite( fltArr, sizeof( float ), length, m_fp );// @date 2013/06/27 <Mod> OKADA
	if( stReturnValue != length ){					// @date 2013/06/27 <Add> OKADA
		LOG_ERROR( FMT( "[3]Writing MSB file error in writeChromatogramData(). Return value and item size of fwrite() disagree. Return value=%d, Item size=%d. errno=%d", stReturnValue, length, errno ) );	// @date 2013/06/27 <Add> OKADA
	}														// @date 2013/06/27 <Add> OKADA

	// write MS stage data
	for( unsigned int i = 0; i < length; i++ ) {
		lngArr[ i ] = chrom.getMsStage( i );
	}

	cdi.msStageAlign = filetell( m_fp );
	stReturnValue = fwrite( lngArr, sizeof( int ), length, m_fp );	// @date 2013/06/27 <Mod> OKADA
	if( stReturnValue != length ){					// @date 2013/06/27 <Add> OKADA
		LOG_ERROR( FMT( "[4]Writing MSB file error in writeChromatogramData(). Return value and item size of fwrite() disagree. Return value=%d, Item size=%d. errno=%d", stReturnValue, length, errno ) );	// @date 2013/06/27 <Add> OKADA
	}														// @date 2013/06/27 <Add> OKADA

	// write precursor data
	for( unsigned int i = 0; i < length; i++ ) {
		fltArr[ i ] = (float)chrom.getPrecursor( i );	// @date 2013/06/27 <Mod> OKADA
	}

	cdi.precursorAlign = filetell( m_fp );
	stReturnValue = fwrite( fltArr, sizeof( float ), length, m_fp );
	if( stReturnValue != length ){					// @date 2013/06/27 <Add> OKADA
		LOG_ERROR( FMT( "[5]Writing MSB file error in writeChromatogramData(). Return value and item size of fwrite() disagree. Return value=%d, Item size=%d. errno=%d", stReturnValue, length, errno ) );	// @date 2013/06/27 <Add> OKADA
	}														// @date 2013/06/27 <Add> OKADA

	// delete array
	delete[] fltArr;
	delete[] lngArr;
}

// write chromatogram information
void MsbIO0202::writeChromatograms(
		std::vector< ChromatogramDataInfo >& chromData,
		std::map< kome::objects::Chromatogram*, unsigned int >& chromatogramMap,
		std::map< kome::objects::DataGroupNode*, unsigned int >& groupMap
) {
	// spectrum data size
	unsigned int dataSize = GET_DATA_SIZE( m_chromatogramInfo );

	// header
	m_dataHeader[ 0 ].val.ul = GET_DATA_SIZE( m_dataHeader );	// header size
	m_dataHeader[ 1 ].val.ul = dataSize;						 // chromatogram size
	m_dataHeader[ 2 ].val.ul = chromData.size();				 // number of chromatograms

	// write header
	WRITE_TO_FILE( m_dataHeader );
	if( chromData.size() == 0 ) {
		return;
	}

	// buffer
	unsigned int size = dataSize * chromData.size();
	unsigned char* buff = new unsigned char[ size ];
	unsigned char* pos = buff;

	// write to buffer
	for( unsigned int i = 0; i < chromData.size(); i++ ) {
		// chromatogram data
		ChromatogramDataInfo& chromInfo = chromData[ i ];
		kome::objects::Chromatogram* chrom = chromInfo.chrom;

		// set data
		m_chromatogramInfo[ 0 ].val.ul   = chromatogramMap[ chrom ];
		m_chromatogramInfo[ 1 ].val.ms   = st( chrom->getName() );
		m_chromatogramInfo[ 2 ].val.ul   = groupMap[ chrom->getGroup() ];
		m_chromatogramInfo[ 3 ].val.ul   = st( chrom->getTitle() );
		m_chromatogramInfo[ 4 ].val.ul   = st( chrom->getIcon() );
		m_chromatogramInfo[ 5 ].val.ul   = chromInfo.length;
		m_chromatogramInfo[ 6 ].val.ull  = chromInfo.rtAlign;
		m_chromatogramInfo[ 7 ].val.ull  = chromInfo.intAlign;
		m_chromatogramInfo[ 8 ].val.ull  = chromInfo.massAlign;
		m_chromatogramInfo[ 9 ].val.ull  = chromInfo.msStageAlign;
		m_chromatogramInfo[ 10 ].val.ull = chromInfo.precursorAlign;

		// write to header
		WRITE_TO_BUFFER( m_chromatogramInfo, pos );
		pos += dataSize;
	}

	// write to file
	size_t stReturnValue = fwrite( buff, 1, size, m_fp );	// @date 2013/06/27 <Mod> OKADA
	if( stReturnValue != size ){							// @date 2013/06/27 <Add> OKADA
        LOG_ERROR( FMT( "Writing MSB file error in writeChromatograms(). "
                        "Return value and item size of fwrite() disagree. "
                        "Return value=%d, Item size=%d. errno=%d", stReturnValue, size, errno ) )	// @date 2013/06/27 <Add> OKADA
	}														// @date 2013/06/27 <Add> OKADA

	// delete buffer
	delete[] buff;
}

// write chromatogram
void MsbIO0202::writeChromatogramProperties(
		kome::objects::DataSet& dataSet,
		std::map< kome::objects::Chromatogram*, unsigned int >& chromatogramMap
) {
	// get properties
	std::vector< Prop > properties;

//	for( unsigned i = 0; i < dataSet.getNumberOfChromatograms(); i++ ) {
//		// chromatogram
//		kome::objects::Chromatogram* chrom = dataSet.getChromatogram( i );
//		unsigned int id = chromatogramMap[ chrom ];

//		// property
//		kome::core::Properties& props = chrom->getProperties();

//		// add to array
//		unsigned int idx = properties.size();
//		unsigned int num = props.getNumberOfProperties();
//		if( num > 0 ) {
//			// resize
//			properties.resize( idx + num );

//			// set value
//			for( unsigned int j = 0; j < num; j++ ) {
//				Prop& prop = properties[ idx + j ];
//				prop.id = id;
//				prop.key = st( props.getKey( j ) );
//				prop.value = st( props.getValue( j ) );
//			}
//		}
//	}

	// chromatogram property data size
	unsigned int dataSize = GET_DATA_SIZE( m_prop );

	// header
	m_dataHeader[ 0 ].val.ul = GET_DATA_SIZE( m_dataHeader );	// header size
	m_dataHeader[ 1 ].val.ul = dataSize;						 // spectrum property size
    m_dataHeader[ 2 ].val.ul = 0/*properties.size()*/;				// number of spectrum properties

	// write header
	WRITE_TO_FILE( m_dataHeader );
	if( properties.size() == 0 ) {
		return;
	}

	// buffer
	unsigned int size = dataSize * properties.size();
	unsigned char* buff = new unsigned char[ size ];
	unsigned char* pos = buff;

	// write to buffer
	for( unsigned int i = 0; i < properties.size(); i++ ) {
		// property
		Prop& prop = properties[ i ];

		// set data
		m_prop[ 0 ].val.ul = prop.id;	   // Chromatogram ID
		m_prop[ 1 ].val.ms = prop.key;	  // Property Key
		m_prop[ 2 ].val.ms = prop.value;	// Property Value

		// write to header
		WRITE_TO_BUFFER( m_prop, pos );
		pos += dataSize;
	}

	// write to file
	size_t stReturnValue = fwrite( buff, 1, size, m_fp );	// @date 2013/06/27 <Mod> OKADA
	if( stReturnValue != size ){							// @date 2013/06/27 <Add> OKADA
		LOG_ERROR( FMT( "Writing MSB file error in writeChromatogramProperties(). Return value and item size of fwrite() disagree. Return value=%d, Item size=%d. errno=%d", stReturnValue, size, errno ) );	// @date 2013/06/27 <Add> OKADA
	}														// @date 2013/06/27 <Add> OKADA

	// delete buffer
	delete[] buff;
}

// write chromatogram user properties
void MsbIO0202::writeChromatogramUserProperties(
		kome::objects::DataSet& dataSet,
		std::map< kome::objects::Chromatogram*, unsigned int >& chromatogramMap
) {
	// get properties
	std::vector< Prop > properties;

//	for( unsigned i = 0; i < dataSet.getNumberOfChromatograms(); i++ ) {
//		// chromatogram
//		kome::objects::Chromatogram* chrom = dataSet.getChromatogram( i );
//		unsigned int id = chromatogramMap[ chrom ];

//		// property
//		kome::core::Properties& props = chrom->getUserProperties();

//		// add to array
//		unsigned int idx = properties.size();
//		unsigned int num = props.getNumberOfProperties();
//		if( num > 0 ) {
//			// resize
//			properties.resize( idx + num );

//			// set value
//			for( unsigned int j = 0; j < num; j++ ) {
//				Prop& prop = properties[ idx + j ];
//				prop.id = id;
//				prop.key = st( props.getKey( j ) );
//				prop.value = st( props.getValue( j ) );
//			}
//		}
//	}

	// chromatogram user property data size
	unsigned int dataSize = GET_DATA_SIZE( m_prop );

	// header
	m_dataHeader[ 0 ].val.ul = GET_DATA_SIZE( m_dataHeader );	// header size
	m_dataHeader[ 1 ].val.ul = dataSize;						 // chromatogram user property size
    m_dataHeader[ 2 ].val.ul = 0/*properties.size()*/;				// number of chromatogram user properties

	// write header
	WRITE_TO_FILE( m_dataHeader );
	if( properties.size() == 0 ) {
		return;
	}

	// buffer
	unsigned int size = dataSize * properties.size();
	unsigned char* buff = new unsigned char[ size ];
	unsigned char* pos = buff;

	// write to buffer
	for( unsigned int i = 0; i < properties.size(); i++ ) {
		// property
		Prop& prop = properties[ i ];

		// set data
		m_prop[ 0 ].val.ul = prop.id;	   // Chromatogram ID
		m_prop[ 1 ].val.ms = prop.key;	  // Property Key
		m_prop[ 2 ].val.ms = prop.value;	// Property Value

		// write to header
		WRITE_TO_BUFFER( m_prop, pos );
		pos += dataSize;
	}

	// write to file
	size_t stReturnValue = fwrite( buff, 1, size, m_fp );// @date 2013/06/27 <Mod> OKADA
	if( stReturnValue != size ){							// @date 2013/06/27 <Add> OKADA
		LOG_ERROR( FMT( "Writing MSB file error in writeChromatogramUserProperties(). Return value and item size of fwrite() disagree. Return value=%d, Item size=%d. errno=%d", stReturnValue, size, errno ) );	// @date 2013/06/27 <Add> OKADA
	}														// @date 2013/06/27 <Add> OKADA

	// delete buffer
	delete[] buff;
}
#if 1
// write Simplify spectrum data
int MsbIO0202::writeSimplifySpectrumData(
        unsigned int id,
        kome::core::DataPoints& points,
        FILE* partsFp
) {
    // array
    unsigned int cnt = 0;
    std::vector< SpectrumPartInfo > parts;

    // number of points
    unsigned int length = points.getLength();
    if( length == 0 ) {
        return 0;
    }

    // number of parts
    SpectrumPartArray arr;
    getParts( points, arr );
    unsigned int num = arr.getNumberOfParts();

    // save data
    unsigned long long xPos = filetell( m_fp );
    size_t stReturnValue = fwrite( points.getXData(), sizeof( float ), length, m_fp );	// @date 2013/06/27 <Mod> OKADA
    if( stReturnValue != length ){							// @date 2013/06/27 <Add> OKADA
        LOG_ERROR( FMT( "[1]Writing MSB file error in writeSpectrumData(). "
                        "Return value and item size of fwrite() disagree. "
                        "Return value=%d, Item size=%d. errno=%d", stReturnValue, length, errno ) )	// @date 2013/06/27 <Add> OKADA
    }														// @date 2013/06/27 <Add> OKADA

    unsigned long long yPos = filetell( m_fp );
    stReturnValue = fwrite( points.getYData(), sizeof( float ), length, m_fp );// @date 2013/06/27 <Mod> OKADA
    if( stReturnValue != length ){							// @date 2013/06/27 <Add> OKADA
        LOG_ERROR( FMT( "[2]Writing MSB file error in writeSpectrumData(). "
                        "Return value and item size of fwrite() disagree. "
                        "Return value=%d, Item size=%d. errno=%d", stReturnValue, length, errno ) )	// @date 2013/06/27 <Add> OKADA
    }														// @date 2013/06/27 <Add> OKADA

    // add parts
    float maxMz = float();
    SpectrumPartInfo* lastPart = nullptr;
    int startIdx = 0;
    double partRange = (double)m_partRange;

    for( unsigned int i = 0; i < points.getLength(); i++ ) {
        float x = (float)points.getX( i );
        float y = (float)points.getY( i );

        if( x > maxMz || lastPart == nullptr ) {		// create new parts
            int num = roundnum( x / partRange );
            float mz = (float)num * partRange;
            maxMz = mz + partRange / 2.0f;

            parts.resize( parts.size() + 1 );
            lastPart = &parts.back();

            lastPart->spectrum = id;
            lastPart->length   = 1;
            lastPart->start = x;
            lastPart->end = x;
            lastPart->totalIntensity = y;
            lastPart->minIntensity = y;
            lastPart->maxIntensity = y;
            lastPart->msAlign = xPos + i * sizeof( float );
            lastPart->intAlign = yPos + i * sizeof( float );
        }
        else {
            float totalIntensity = lastPart->totalIntensity + y;
            float minIntensity = MIN( lastPart->minIntensity, y );
            float maxIntensity = MAX( lastPart->maxIntensity, y );
            unsigned int length = lastPart->length + 1;

            lastPart->end = x;
            lastPart->totalIntensity = totalIntensity;
            lastPart->minIntensity = minIntensity;
            lastPart->maxIntensity = maxIntensity;
            lastPart->length = length;
        }
    }

    // write parts
    unsigned int dataSize = GET_DATA_SIZE( m_partInfo );
    unsigned int size = dataSize * parts.size();
    if( size == 0 ) {
        return 0;
    }

    unsigned char* buff = new unsigned char[ size ];
    unsigned char* pos = buff;

    // write to buffer
    for( unsigned int i = 0; i < parts.size(); i++ ) {
        // spectrum
        SpectrumPartInfo& part = parts[ i ];

        // set data
        m_partInfo[ 0 ].val.ul = part.spectrum;		  // Spectrum ID
        m_partInfo[ 1 ].val.ul = part.length;		  // Data Length
        m_partInfo[ 2 ].val.f  = part.start;		  // Start m/z
        m_partInfo[ 3 ].val.f  = part.end;			  // End m/z
        m_partInfo[ 4 ].val.f  = part.totalIntensity; // Total Intensity
        m_partInfo[ 5 ].val.f  = part.minIntensity;	  // Min Intensity
        m_partInfo[ 6 ].val.f  = part.maxIntensity;	  // Max Intensity
        m_partInfo[ 7 ].val.ul = part.msAlign;		  // m/z Data Align
        m_partInfo[ 8 ].val.ul = part.intAlign;		  // Intensity Data Align

        // write to header
        WRITE_TO_BUFFER( m_partInfo, pos );

        pos += dataSize;
    }

    // write to file
    pos = buff;
    int rest = (int)size;
    while( rest > 0 ) {
        int writeSize = MIN( rest, 0x10000 );
        int s = fwrite( pos, 1, writeSize, partsFp );
        if( s == 0 ) {
            rest = 0;
        }
        else {
            rest -= s;
            pos += s;
        }

        if( s != writeSize ){							// @date 2013/06/27 <Add> OKADA
            LOG_ERROR( FMT( "[3]Writing MSB file error in writeSpectrumData(). "
                            "Return value and item size of fwrite() disagree. "
                            "Return value=%d, Item size=%d. errno=%d", stReturnValue, length, errno ) )	// @date 2013/06/27 <Add> OKADA
        }														// @date 2013/06/27 <Add> OKADA


    }

    // delete buffer
    delete[] buff;

    return (int)parts.size();
}
#endif

// write spectrum data
int MsbIO0202::writeSpectrumData(
		unsigned int id,
		kome::objects::Spectrum& spec,
		kome::core::DataPoints& points,
		FILE* partsFp
) {
	// array
	unsigned int cnt = 0;
	std::vector< SpectrumPartInfo > parts;

	// number of points
	unsigned int length = points.getLength();
	if( length == 0 ) {
		return 0;
	}

	// number of parts
	SpectrumPartArray arr;
	getParts( points, arr );
	unsigned int num = arr.getNumberOfParts();

	// save data
	unsigned long long xPos = filetell( m_fp );
	size_t stReturnValue = fwrite( points.getXData(), sizeof( float ), length, m_fp );	// @date 2013/06/27 <Mod> OKADA
	if( stReturnValue != length ){							// @date 2013/06/27 <Add> OKADA
        LOG_ERROR( FMT( "[1]Writing MSB file error in writeSpectrumData(). "
                        "Return value and item size of fwrite() disagree. "
                        "Return value=%d, Item size=%d. errno=%d", stReturnValue, length, errno ) )	// @date 2013/06/27 <Add> OKADA
	}														// @date 2013/06/27 <Add> OKADA

	unsigned long long yPos = filetell( m_fp );
	stReturnValue = fwrite( points.getYData(), sizeof( float ), length, m_fp );// @date 2013/06/27 <Mod> OKADA
	if( stReturnValue != length ){							// @date 2013/06/27 <Add> OKADA
        LOG_ERROR( FMT( "[2]Writing MSB file error in writeSpectrumData(). "
                        "Return value and item size of fwrite() disagree. "
                        "Return value=%d, Item size=%d. errno=%d", stReturnValue, length, errno ) )	// @date 2013/06/27 <Add> OKADA
	}														// @date 2013/06/27 <Add> OKADA

	// add parts
	float maxMz = float();
    SpectrumPartInfo* lastPart = nullptr;
	int startIdx = 0;
	double partRange = (double)m_partRange;

	for( unsigned int i = 0; i < points.getLength(); i++ ) {
		float x = (float)points.getX( i );
		float y = (float)points.getY( i );

        if( x > maxMz || lastPart == nullptr ) {		// create new parts
			int num = roundnum( x / partRange );
			float mz = (float)num * partRange;
			maxMz = mz + partRange / 2.0f;

			parts.resize( parts.size() + 1 );
			lastPart = &parts.back();

			lastPart->spectrum = id;
			lastPart->length   = 1;
			lastPart->start = x;
			lastPart->end = x;
			lastPart->totalIntensity = y;
			lastPart->minIntensity = y;
			lastPart->maxIntensity = y;
			lastPart->msAlign = xPos + i * sizeof( float );
			lastPart->intAlign = yPos + i * sizeof( float );
		}
		else {
			float totalIntensity = lastPart->totalIntensity + y;
			float minIntensity = MIN( lastPart->minIntensity, y );
			float maxIntensity = MAX( lastPart->maxIntensity, y );
			unsigned int length = lastPart->length + 1;

			lastPart->end = x;
			lastPart->totalIntensity = totalIntensity;
			lastPart->minIntensity = minIntensity;
			lastPart->maxIntensity = maxIntensity;
			lastPart->length = length;
		}
	}

	// write parts
	unsigned int dataSize = GET_DATA_SIZE( m_partInfo );
	unsigned int size = dataSize * parts.size();
	if( size == 0 ) {
		return 0;
	}

	unsigned char* buff = new unsigned char[ size ];
	unsigned char* pos = buff;

	// write to buffer
	for( unsigned int i = 0; i < parts.size(); i++ ) {
		// spectrum
		SpectrumPartInfo& part = parts[ i ];

		// set data
		m_partInfo[ 0 ].val.ul = part.spectrum;		  // Spectrum ID
        m_partInfo[ 1 ].val.ul = part.length;		  // Data Length
        m_partInfo[ 2 ].val.f  = part.start;		  // Start m/z
        m_partInfo[ 3 ].val.f  = part.end;			  // End m/z
        m_partInfo[ 4 ].val.f  = part.totalIntensity; // Total Intensity
		m_partInfo[ 5 ].val.f  = part.minIntensity;	  // Min Intensity
		m_partInfo[ 6 ].val.f  = part.maxIntensity;	  // Max Intensity
        m_partInfo[ 7 ].val.ul = part.msAlign;		  // m/z Data Align
		m_partInfo[ 8 ].val.ul = part.intAlign;		  // Intensity Data Align

		// write to header
		WRITE_TO_BUFFER( m_partInfo, pos );

		pos += dataSize;
	}

	// write to file
	pos = buff;
	int rest = (int)size;
	while( rest > 0 ) {		
		int writeSize = MIN( rest, 0x10000 );
		int s = fwrite( pos, 1, writeSize, partsFp );
		if( s == 0 ) {
			rest = 0;
		}
		else {
			rest -= s;
			pos += s;
		}

		if( s != writeSize ){							// @date 2013/06/27 <Add> OKADA
            LOG_ERROR( FMT( "[3]Writing MSB file error in writeSpectrumData(). "
                            "Return value and item size of fwrite() disagree. "
                            "Return value=%d, Item size=%d. errno=%d", stReturnValue, length, errno ) )	// @date 2013/06/27 <Add> OKADA
		}														// @date 2013/06/27 <Add> OKADA


	}

	// delete buffer
	delete[] buff;

	return (int)parts.size();
}

// write Simplify spectra
void MsbIO0202::writeSimplifySpectra(unsigned int frameCnt) {
    // spectrum data size
    unsigned int dataSize = GET_DATA_SIZE( m_spectrumInfo );

    // header
    m_dataHeader[ 0 ].val.ul = GET_DATA_SIZE( m_dataHeader );	// header size
    m_dataHeader[ 1 ].val.ul = dataSize;						 // spectrum size
    m_dataHeader[ 2 ].val.ul = frameCnt;	 // number of spectra

    // write header
    WRITE_TO_FILE( m_dataHeader );
    if( frameCnt == 0 ) {
        return;
    }

    // buffer
    unsigned int size = dataSize * frameCnt;
    unsigned char* buff = new unsigned char[ size ];
    unsigned char* pos = buff;

    // write to buffer
    for( unsigned int i = 0; i < frameCnt; i++ ) {
        // spectrum
//        kome::objects::Spectrum* spec = dataSet.getSpectrum( i );

        // set data
        m_spectrumInfo[ 0 ].val.ul = i/*spectrumMap[ spec ]*/;					 // Spectrum ID
        m_spectrumInfo[ 1 ].val.ms = st( "spec->getName()" );					 // Spectrum Name

        unsigned int parent = 0;
//        if( spec->getParentSpectrum() != nullptr ) {
//            parent = spectrumMap[ spec->getParentSpectrum() ];
//        }
        m_spectrumInfo[ 2 ].val.ul = parent;									// Parent Spectrum

        m_spectrumInfo[ 3 ].val.ul   = i   /*groupMap[ spec->getGroup() ]*/;	    // Spectrum Group
        m_spectrumInfo[ 4 ].val.us   = i   /*spec->getMsStage()*/;				// MS Stage
        m_spectrumInfo[ 5 ].val.f	 = i   /*spec->getPrecursor()*/;				// Precursor
        m_spectrumInfo[ 6 ].val.f	 = i   /*spec->getStartRt()*/;				// Start Retention Time
        m_spectrumInfo[ 7 ].val.f	 = i   /*spec->getEndRt()*/;					// End Retention Time
        m_spectrumInfo[ 8 ].val.f	 = i   /*spec->getMinX()*/;					// min x
        m_spectrumInfo[ 9 ].val.f	 = i   /*spec->getMaxX()*/;					// max x
        m_spectrumInfo[ 10 ].val.f   = i   /*spec->getTotalIntensity()*/;		// total intensity
        m_spectrumInfo[ 11 ].val.f   = i   /*spec->getMaxIntensity()*/;			// max intensity
        m_spectrumInfo[ 12 ].val.ul  = i   /*spec->getScanNumber()*/;			// Scan Number
        m_spectrumInfo[ 13 ].val.b   = i   /*spec->isCentroidMode()*/;			// Centroided
        m_spectrumInfo[ 14 ].val.f   = i   /*spec->getResolution()*/;			// Resolution
//        if( spec->getPolarity() == kome::objects::Spectrum::POLARITY_NEGATIVE ) {
//            m_spectrumInfo[ 15 ].val.c = -1;
//        }
//        else if( spec->getPolarity() == kome::objects::Spectrum::POLARITY_POSITIVE ) {
//            m_spectrumInfo[ 15 ].val.c = 1;
//        }
//        else {
            m_spectrumInfo[ 15 ].val.c = 0;
//        }																	   // Polarity
        m_spectrumInfo[ 16 ].val.ms =  st( "MS Type" /*spec->getSpecType()*/ );			   // MS Type
        m_spectrumInfo[ 17 ].val.ms  = st( "spectrum_title" /*spec->getTitle()*/ );				  // Title
        m_spectrumInfo[ 18 ].val.b   = false/*spec->hasChromatogram()*/;				 // Chromatogram Flag
        m_spectrumInfo[ 19 ].val.ms  = st( "spec->getIcon()" );				   // Icon Name

        // write to header
        WRITE_TO_BUFFER( m_spectrumInfo, pos );
        pos += dataSize;
    }

    // write to file
    size_t stReturnValue = fwrite( buff, 1, size, m_fp );	// @date 2013/06/27 <Mod> OKADA
    if( stReturnValue != size ){							// @date 2013/06/27 <Add> OKADA
        LOG_ERROR( FMT( "Writing MSB file error in writeSpectra(). Return value and item size of fwrite() disagree. Return value=%d, Item size=%d. errno=%d", stReturnValue, size, errno ) );	// @date 2013/06/27 <Add> OKADA
    }														// @date 2013/06/27 <Add> OKADA

    // delete buffer
    delete[] buff;
}


// write spectra
void MsbIO0202::writeSpectra(
		kome::objects::DataSet& dataSet,
		std::map< kome::objects::Spectrum*, unsigned int >& spectrumMap,
		std::map< kome::objects::DataGroupNode*, unsigned int >& groupMap
) {
	// spectrum data size
	unsigned int dataSize = GET_DATA_SIZE( m_spectrumInfo );

	// header
	m_dataHeader[ 0 ].val.ul = GET_DATA_SIZE( m_dataHeader );	// header size
	m_dataHeader[ 1 ].val.ul = dataSize;						 // spectrum size
	m_dataHeader[ 2 ].val.ul = dataSet.getNumberOfSpectra();	 // number of spectra

	// write header
	WRITE_TO_FILE( m_dataHeader );
	if( dataSet.getNumberOfSpectra() == 0 ) {
		return;
	}

	// buffer
	unsigned int size = dataSize * dataSet.getNumberOfSpectra();
	unsigned char* buff = new unsigned char[ size ];
	unsigned char* pos = buff;

	// write to buffer
	for( unsigned int i = 0; i < dataSet.getNumberOfSpectra(); i++ ) {
		// spectrum
		kome::objects::Spectrum* spec = dataSet.getSpectrum( i );

		// set data
        m_spectrumInfo[ 0 ].val.ul = spectrumMap[ spec ];					 // Spectrum ID
		m_spectrumInfo[ 1 ].val.ms = st( spec->getName() );					 // Spectrum Name

		int parent = 0;
        if( spec->getParentSpectrum() != nullptr ) {
			parent = spectrumMap[ spec->getParentSpectrum() ];
		}
		m_spectrumInfo[ 2 ].val.ul = parent;									// Parent Spectrum

		m_spectrumInfo[ 3 ].val.ul   = groupMap[ spec->getGroup() ];	// Spectrum Group
		m_spectrumInfo[ 4 ].val.us   = spec->getMsStage();					  // MS Stage
		m_spectrumInfo[ 5 ].val.f	= spec->getPrecursor();					// Precursor
		m_spectrumInfo[ 6 ].val.f	= spec->getStartRt();					  // Start Retention Time
		m_spectrumInfo[ 7 ].val.f	= spec->getEndRt();						// End Retention Time
		m_spectrumInfo[ 8 ].val.f	= spec->getMinX();						 // min x
		m_spectrumInfo[ 9 ].val.f	= spec->getMaxX();						 // max x
		m_spectrumInfo[ 10 ].val.f   = spec->getTotalIntensity();			   // total intensity
		m_spectrumInfo[ 11 ].val.f   = spec->getMaxIntensity();				 // max intensity
		m_spectrumInfo[ 12 ].val.ul  = spec->getScanNumber();				   // Scan Number
		m_spectrumInfo[ 13 ].val.b   = spec->isCentroidMode();				  // Centroided
		m_spectrumInfo[ 14 ].val.f   = spec->getResolution();				   // Resolution
		if( spec->getPolarity() == kome::objects::Spectrum::POLARITY_NEGATIVE ) {
			m_spectrumInfo[ 15 ].val.c = -1;
		}
		else if( spec->getPolarity() == kome::objects::Spectrum::POLARITY_POSITIVE ) {
			m_spectrumInfo[ 15 ].val.c = 1;
		}
		else {
			m_spectrumInfo[ 15 ].val.c = 0;
		}																	   // Polarity
		m_spectrumInfo[ 16 ].val.ms =  st( spec->getSpecType() );			   // MS Type
		m_spectrumInfo[ 17 ].val.ms  = st( spec->getTitle() );				  // Title
		m_spectrumInfo[ 18 ].val.b   = spec->hasChromatogram();				 // Chromatogram Flag
		m_spectrumInfo[ 19 ].val.ms  = st( spec->getIcon() );				   // Icon Name

		// write to header
		WRITE_TO_BUFFER( m_spectrumInfo, pos );
		pos += dataSize;
	}

	// write to file
	size_t stReturnValue = fwrite( buff, 1, size, m_fp );	// @date 2013/06/27 <Mod> OKADA
	if( stReturnValue != size ){							// @date 2013/06/27 <Add> OKADA
		LOG_ERROR( FMT( "Writing MSB file error in writeSpectra(). Return value and item size of fwrite() disagree. Return value=%d, Item size=%d. errno=%d", stReturnValue, size, errno ) );	// @date 2013/06/27 <Add> OKADA
	}														// @date 2013/06/27 <Add> OKADA

	// delete buffer
	delete[] buff;
}

// write spectrum parts
void MsbIO0202::writeSpectrumParts( const int cnt, FILE* partsFp ) {
	// spectrum part data size
	unsigned int dataSize = GET_DATA_SIZE( m_partInfo );

	// header
	m_dataHeader[ 0 ].val.ul = GET_DATA_SIZE( m_dataHeader );	// header size
    m_dataHeader[ 1 ].val.ul = dataSize;						// spectrum part size
    m_dataHeader[ 2 ].val.ul = std::max( 0, cnt );			    // number of spectrum parts

	// write header
	WRITE_TO_FILE( m_dataHeader );
    if( cnt <= 0 || partsFp == nullptr ) {
		return;
	}

	// write data
	char buff[ 1024 ];
	int readSize = 0;
	while( ( readSize = fread( buff, 1, 1024, partsFp ) ) > 0 ) {
		size_t stReturnValue = fwrite( buff, 1, readSize, m_fp );// @date 2013/06/27 <Mod> OKADA
		if( stReturnValue != readSize ){						// @date 2013/06/27 <Add> OKADA
            LOG_ERROR( FMT( "Writing MSB file error in writeSpectrumParts(). "
                            "Return value and item size of fwrite() disagree. "
                            "Return value=%d, Item size=%d. errno=%d", stReturnValue, readSize, errno ) )	// @date 2013/06/27 <Add> OKADA
		}														// @date 2013/06/27 <Add> OKADA

	}
}

// write Simplify specrum property
void MsbIO0202::writeSimplifySpectrumProperties(unsigned int frameCnt) {
    // get properties
    std::vector< Prop > properties;

    for( unsigned i = 0; i < frameCnt; i++ ) {
        // spectrum
//        kome::objects::Spectrum* spec = dataSet.getSpectrum( i );
        unsigned int id = i /*spectrumMap[ spec ]*/;

        // property
        kome::core::Properties props /*= spec->getProperties()*/;
        props.setValue("SimplifySpectrumPropertieskey1", "SimplifySpectrumPropertiesvalue1");
        props.setValue("SimplifySpectrumPropertieskey2", "SimplifySpectrumPropertiesvalue2");

        // add to array
        unsigned int idx = properties.size();
        unsigned int num = props.getNumberOfProperties();
        if( num > 0 ) {
            // resize
            properties.resize( idx + num );

            // set value
            for( unsigned int j = 0; j < num; j++ ) {
                Prop& prop = properties[ idx + j ];
                prop.id = id;
                prop.key = st( props.getKey( j ) );
                prop.value = st( props.getValue( j ) );
            }
        }
    }

    // spectrum property data size
    unsigned int dataSize = GET_DATA_SIZE( m_prop );

    // header
    m_dataHeader[ 0 ].val.ul = GET_DATA_SIZE( m_dataHeader );	// header size
    m_dataHeader[ 1 ].val.ul = dataSize;						 // spectrum property size
    m_dataHeader[ 2 ].val.ul = properties.size();				// number of spectrum properties

    // write header
    WRITE_TO_FILE( m_dataHeader );
    if( properties.size() == 0 ) {
        return;
    }

    // buffer
    unsigned int size = dataSize * properties.size();
    unsigned char* buff = new unsigned char[ size ];
    unsigned char* pos = buff;

    // write to buffer
    for( unsigned int i = 0; i < properties.size(); i++ ) {
        // property
        Prop& prop = properties[ i ];

        // set data
        m_prop[ 0 ].val.ul = prop.id;	    // Spectrum ID
        m_prop[ 1 ].val.ms = prop.key;	    // Property Key
        m_prop[ 2 ].val.ms = prop.value;	// Property Value

        // write to header
        WRITE_TO_BUFFER( m_prop, pos );
        pos += dataSize;
    }

    // write to file
    size_t stReturnValue = fwrite( buff, 1, size, m_fp );	// @date 2013/06/27 <Mod> OKADA
    if( stReturnValue != size ){							// @date 2013/06/27 <Add> OKADA
        LOG_ERROR( FMT( "Writing MSB file error in writeSpectrumProperties(). "
                        "Return value and item size of fwrite() disagree. "
                        "Return value=%d, Item size=%d. errno=%d", stReturnValue, size, errno ) )	// @date 2013/06/27 <Add> OKADA
    }														// @date 2013/06/27 <Add> OKADA

    // delete buffer
    delete[] buff;
}

// write specrum property
void MsbIO0202::writeSpectrumProperties(
		kome::objects::DataSet& dataSet,
        std::map< kome::objects::Spectrum*, unsigned int >& spectrumMap
) {
	// get properties
	std::vector< Prop > properties;

	for( unsigned i = 0; i < dataSet.getNumberOfSpectra(); i++ ) {
		// spectrum
		kome::objects::Spectrum* spec = dataSet.getSpectrum( i );
		unsigned int id = spectrumMap[ spec ];

		// property
		kome::core::Properties& props = spec->getProperties();

		// add to array
		unsigned int idx = properties.size();
		unsigned int num = props.getNumberOfProperties();
		if( num > 0 ) {
			// resize
			properties.resize( idx + num );

			// set value
			for( unsigned int j = 0; j < num; j++ ) {
				Prop& prop = properties[ idx + j ];
				prop.id = id;
				prop.key = st( props.getKey( j ) );
				prop.value = st( props.getValue( j ) );
			}
		}
	}

	// spectrum property data size
	unsigned int dataSize = GET_DATA_SIZE( m_prop );

	// header
	m_dataHeader[ 0 ].val.ul = GET_DATA_SIZE( m_dataHeader );	// header size
	m_dataHeader[ 1 ].val.ul = dataSize;						 // spectrum property size
	m_dataHeader[ 2 ].val.ul = properties.size();				// number of spectrum properties

	// write header
	WRITE_TO_FILE( m_dataHeader );
	if( properties.size() == 0 ) {
		return;
	}

	// buffer
	unsigned int size = dataSize * properties.size();
	unsigned char* buff = new unsigned char[ size ];
	unsigned char* pos = buff;

	// write to buffer
	for( unsigned int i = 0; i < properties.size(); i++ ) {
		// property
		Prop& prop = properties[ i ];

		// set data
        m_prop[ 0 ].val.ul = prop.id;	    // Spectrum ID
        m_prop[ 1 ].val.ms = prop.key;	    // Property Key
		m_prop[ 2 ].val.ms = prop.value;	// Property Value

		// write to header
		WRITE_TO_BUFFER( m_prop, pos );
		pos += dataSize;
	}

	// write to file
	size_t stReturnValue = fwrite( buff, 1, size, m_fp );	// @date 2013/06/27 <Mod> OKADA
	if( stReturnValue != size ){							// @date 2013/06/27 <Add> OKADA
        LOG_ERROR( FMT( "Writing MSB file error in writeSpectrumProperties(). "
                        "Return value and item size of fwrite() disagree. "
                        "Return value=%d, Item size=%d. errno=%d", stReturnValue, size, errno ) )	// @date 2013/06/27 <Add> OKADA
	}														// @date 2013/06/27 <Add> OKADA

	// delete buffer
	delete[] buff;
}

// write Simplify specrum user property
void MsbIO0202::writeSimplifySpectrumUserProperties(unsigned int frameCnt){
    // get properties
    std::vector< Prop > properties;

    for( unsigned i = 0; i < frameCnt; i++ ) {
        // spectrum
//        kome::objects::Spectrum* spec = dataSet.getSpectrum( i );
        unsigned int id = i/*spectrumMap[ spec ]*/;

        // property
        kome::core::Properties props /*= spec->getUserProperties()*/;
        props.setValue("SimplifySpectrumUserPropertieskey1", "SimplifySpectrumUserPropertiesvalue1");
        props.setValue("SimplifySpectrumUserPropertieskey2", "SimplifySpectrumUserPropertiesvalue2");

        // add to array
        unsigned int idx = properties.size();
        unsigned int num = props.getNumberOfProperties();
        if( num > 0 ) {
            // resize
            properties.resize( idx + num );

            // set value
            for( unsigned int j = 0; j < num; j++ ) {
                Prop& prop = properties[ idx + j ];
                prop.id = id;
                prop.key = st( props.getKey( j ) );
                prop.value = st( props.getValue( j ) );
            }
        }
    }

    // spectrum user property data size
    unsigned int dataSize = GET_DATA_SIZE( m_prop );

    // header
    m_dataHeader[ 0 ].val.ul = GET_DATA_SIZE( m_dataHeader );	// header size
    m_dataHeader[ 1 ].val.ul = dataSize;						 // spectrum user property size
    m_dataHeader[ 2 ].val.ul = properties.size();				// number of spectrum user properties

    // write header
    WRITE_TO_FILE( m_dataHeader );
    if( properties.size() == 0 ) {
        return;
    }

    // buffer
    unsigned int size = dataSize * properties.size();
    unsigned char* buff = new unsigned char[ size ];
    unsigned char* pos = buff;

    // write to buffer
    for( unsigned int i = 0; i < properties.size(); i++ ) {
        // property
        Prop& prop = properties[ i ];

        // set data
        m_prop[ 0 ].val.ul = prop.id;	   // Spectrum ID
        m_prop[ 1 ].val.ms = prop.key;	  // Property Key
        m_prop[ 2 ].val.ms = prop.value;	// Property Value

        // write to header
        WRITE_TO_BUFFER( m_prop, pos );
        pos += dataSize;
    }

    // write to file
    size_t stReturnValue = fwrite( buff, 1, size, m_fp );	// @date 2013/06/27 <Mod> OKADA
    if( stReturnValue != size ){							// @date 2013/06/27 <Add> OKADA
        LOG_ERROR( FMT( "Writing MSB file error in writeSpectrumUserProperties(). Return value and item size of fwrite() disagree. Return value=%d, Item size=%d. errno=%d", stReturnValue, size, errno ) );	// @date 2013/06/27 <Add> OKADA
    }														// @date 2013/06/27 <Add> OKADA

    // delete buffer
    delete[] buff;
}

// write specrum user property
void MsbIO0202::writeSpectrumUserProperties(
		kome::objects::DataSet& dataSet,
		std::map< kome::objects::Spectrum*, unsigned int >& spectrumMap
) {
	// get properties
	std::vector< Prop > properties;

	for( unsigned i = 0; i < dataSet.getNumberOfSpectra(); i++ ) {
		// spectrum
		kome::objects::Spectrum* spec = dataSet.getSpectrum( i );
		unsigned int id = spectrumMap[ spec ];

		// property
		kome::core::Properties& props = spec->getUserProperties();

		// add to array
		unsigned int idx = properties.size();
		unsigned int num = props.getNumberOfProperties();
		if( num > 0 ) {
			// resize
			properties.resize( idx + num );

			// set value
			for( unsigned int j = 0; j < num; j++ ) {
				Prop& prop = properties[ idx + j ];
				prop.id = id;
				prop.key = st( props.getKey( j ) );
				prop.value = st( props.getValue( j ) );
			}
		}
	}

	// spectrum user property data size
	unsigned int dataSize = GET_DATA_SIZE( m_prop );

	// header
	m_dataHeader[ 0 ].val.ul = GET_DATA_SIZE( m_dataHeader );	// header size
	m_dataHeader[ 1 ].val.ul = dataSize;						 // spectrum user property size
	m_dataHeader[ 2 ].val.ul = properties.size();				// number of spectrum user properties

	// write header
	WRITE_TO_FILE( m_dataHeader );
	if( properties.size() == 0 ) {
		return;
	}

	// buffer
	unsigned int size = dataSize * properties.size();
	unsigned char* buff = new unsigned char[ size ];
	unsigned char* pos = buff;

	// write to buffer
	for( unsigned int i = 0; i < properties.size(); i++ ) {
		// property
		Prop& prop = properties[ i ];

		// set data
		m_prop[ 0 ].val.ul = prop.id;	   // Spectrum ID
		m_prop[ 1 ].val.ms = prop.key;	  // Property Key
		m_prop[ 2 ].val.ms = prop.value;	// Property Value

		// write to header
		WRITE_TO_BUFFER( m_prop, pos );
		pos += dataSize;
	}

	// write to file
	size_t stReturnValue = fwrite( buff, 1, size, m_fp );	// @date 2013/06/27 <Mod> OKADA
	if( stReturnValue != size ){							// @date 2013/06/27 <Add> OKADA
		LOG_ERROR( FMT( "Writing MSB file error in writeSpectrumUserProperties(). Return value and item size of fwrite() disagree. Return value=%d, Item size=%d. errno=%d", stReturnValue, size, errno ) );	// @date 2013/06/27 <Add> OKADA
	}														// @date 2013/06/27 <Add> OKADA

	// delete buffer
	delete[] buff;
}

// get sample information
void MsbIO0202::onReadSampleInfo( MsbSample& sample ) {
	// read file header
	READ_FROM_FILE( m_fileHeader );

	// create string table
    char* stringTable = nullptr;
      createStringTable( &stringTable );
//    std::string eptstr = " ";
//    const char* stringTable = eptstr.c_str();

	// get file Header Info
    getFileHeaderInfo( sample, stringTable );
//    getFileHeaderInfo( sample, (char*)stringTable );

	// delete string table
    if( stringTable != nullptr ) {
		delete[] stringTable;
	}
}

//读取
void MsbIO0202::onReadHisMsb(){

}

// open sample
void MsbIO0202::onReadMsb( MsbSample& sample ) {
	// create string table
    char* stringTable = nullptr;
	createStringTable( &stringTable );

    // keep align
    unsigned long long specGroupAlign	 = m_fileHeader[ 10 ].val.ull;       // 10: Spectrum Group Align
    unsigned long long specGroupPropAlign = m_fileHeader[ 11 ].val.ull;      // 11: Spectrum Group Properties Align
    unsigned long long specGroupUserPropAlign = m_fileHeader[ 12 ].val.ull;  // 12: Spectrum Group User Properties Align
    unsigned long long chromAlign		 = m_fileHeader[ 14 ].val.ull;       // 14: Chromatogram Align
    unsigned long long chromPropAlign	 = m_fileHeader[ 15 ].val.ull;       // 15: Chromatogram Properties Align
    unsigned long long chromUserPropAlign	 = m_fileHeader[ 16 ].val.ull;   // 16: Chromatogram User Properties Align
    unsigned long long spectrumAlign	  = m_fileHeader[ 18 ].val.ull;      // 18: Spectrum Align
    unsigned long long specPartAlign	  = m_fileHeader[ 19 ].val.ull;      // 19: Spectrum Part Align
    unsigned long long specPropAlign	  = m_fileHeader[ 20 ].val.ull;      // 20: Spectrum Properties Align
    unsigned long long specUserPropAlign	  = m_fileHeader[ 21 ].val.ull;  // 21: Spectrum User Properties Align

	// read spectrum group
	std::map< unsigned int, kome::objects::DataGroupNode* > groupMap;
	groupMap[ 0 ] = sample.getRootDataGroupNode();
	fileseek( m_fp, specGroupAlign, SEEK_SET );
	readDataGroupNodes( sample.getRootDataGroupNode(), groupMap, stringTable );

	// read spectrum group properties
	fileseek( m_fp, specGroupPropAlign, SEEK_SET );
	readDataGroupNodeProperties( groupMap, stringTable );

	// read spectrum user group properties
	fileseek( m_fp, specGroupUserPropAlign, SEEK_SET );
	readDataGroupNodeUserProperties( groupMap, stringTable );

	// read chromatogram
	std::map< unsigned int, MsbChromatogram* > chromMap;
	fileseek( m_fp, chromAlign, SEEK_SET );
	readChromatograms( sample, chromMap, groupMap, stringTable );

	// read chromatogram property
	fileseek( m_fp, chromPropAlign, SEEK_SET );
	readChromatogramProperties( chromMap, stringTable );

	// read chromatogram user property
	fileseek( m_fp, chromUserPropAlign, SEEK_SET );
	readChromatogramUserProperties( chromMap, stringTable );
	chromMap.clear();

	// read spectrum
	std::map< unsigned int, MsbSpectrum* > specMap;
	fileseek( m_fp, spectrumAlign, SEEK_SET );
	readSpectra( sample, specMap, groupMap, stringTable );
	groupMap.clear();

	// read spectrum part
	fileseek( m_fp, specPartAlign, SEEK_SET );
	readSpectrumParts( specMap );

	// read spectrum property
	fileseek( m_fp, specPropAlign, SEEK_SET );
	readSpectrumProperties( specMap, stringTable );

	// read spectrum user property
	fileseek( m_fp, specUserPropAlign, SEEK_SET );
	readSpectrumUserProperties( specMap, stringTable );
	specMap.clear();

	// delete string table
    if( stringTable != nullptr ) {
		delete[] stringTable;
	}
}

// write msb
bool MsbIO0202::onWriteMsb(
		kome::objects::Sample& sample,
		kome::objects::DataSet& dataSet,
        bool op ,
		kome::core::Progress& progress
) {
	// log
    LOG_INFO( FMT( "Writing MSB format sample. [ver 2.2]" ) )

	// get spectra and spectrum groups
	if( progress.isStopped() ) {
		return true;
	}
	std::vector< kome::objects::DataGroupNode* > groups;
	getGroups( dataSet, groups );

	// progress
	unsigned int pos = 0;
	unsigned int length = dataSet.getNumberOfSpectra() + dataSet.getNumberOfChromatograms() + 13;
	progress.setRange( 0, length );
	progress.setPosition( pos );

	// file header
	if( progress.isStopped() ) {
		return true;
	}
	progress.setStatus( "Writing file header" );

    m_fileHeader[ 0 ].val.ul = GET_DATA_SIZE( m_fileHeader );				 // Header Size
    m_fileHeader[ 1 ].val.uc = m_bigendian ? 0 : 1;							 // Endian
	m_fileHeader[ 4 ].val.ms = st( sample.getSampleSet()->getFilePath() );	 // File Path
	m_fileHeader[ 5 ].val.ms = st( sample.getName() );						 // Sample Name
    m_fileHeader[ 6 ].val.ms = st( sample.getInstrument() );				 // Instrument Name
    m_fileHeader[ 7 ].val.ms = st( sample.getMsCompany() );					 // manufacture
	m_fileHeader[ 8 ].val.ms = st( sample.getSoftwareName() );				 // software name
    m_fileHeader[ 9 ].val.ms = st( sample.getSoftwareVersion() );			 // software version
    m_fileHeader[ 22 ].val.t = time( nullptr );								 // Time

	WRITE_TO_FILE( m_fileHeader );
	progress.setPosition( ++pos );	// pos == 1

	// spectrum group
	if( progress.isStopped() ) {
		return true;
	}
	progress.setStatus( "Writing spectrum group" );
    m_fileHeader[ 10 ].val.ull = filetell( m_fp );			 // 10: Spectrum Group Align

	std::map< kome::objects::DataGroupNode*, unsigned int > groupMap;
	groupMap[ sample.getRootDataGroupNode() ] = 0;

	writeDataGroupNodes( groups, groupMap );
	progress.setPosition( ++pos );	// pos == 2;
	groups.push_back( sample.getRootDataGroupNode() );

	// spectrum group properties
	if( progress.isStopped() ) {
		return true;
	}
	progress.setStatus( "Writing spectrum group properties" );
    m_fileHeader[ 11 ].val.ull = filetell( m_fp );           // 11: Spectrum Group Properties Align

	writeDataGroupNodeProperties( groups, groupMap );
	progress.setPosition( ++pos );  // pos == 3;

	// spectrum group user properties
	if( progress.isStopped() ) {
		return true;
	}
	progress.setStatus( "Writing spectrum group user properties" );
    m_fileHeader[ 12 ].val.ull = filetell( m_fp );          // 12: Spectrum Group User Properties Align

	writeDataGroupNodeUserProperties( groups, groupMap );
	progress.setPosition( ++pos );  // pos == 4;
	groups.clear();

	// chromatogram data
	if( progress.isStopped() ) {
		return true;
	}
    m_fileHeader[ 13 ].val.ull = filetell( m_fp );          // 13: Chromatogram Data Align
	progress.setStatus( "Writing chromatogram data." );

	kome::core::DataPoints points( kome::core::DataPoints::FLOAT );    
	std::map< kome::objects::Chromatogram*, unsigned int > chromatogramMap;
	std::vector< ChromatogramDataInfo > chromData;

    //make theNumberOfChromatograms() returns zero. There is no Chromatograms data.
	for( unsigned int i = 0; i < dataSet.getNumberOfChromatograms() && !progress.isStopped(); i++ ) {
		// chromatogram
		kome::objects::Chromatogram* chromatogram = dataSet.getChromatogram( i );
		progress.setStatus(
			FMT(
				"Writing Chromatogram Data [%d/%d] (%s)",
				( i + 1 ),
				dataSet.getNumberOfChromatograms(),
				chromatogram->getName()
			).c_str()
		);

		// ID
		unsigned int id = ( i + 1 );
		chromatogramMap[ chromatogram ] = id;

		// gets data points
		chromatogram->getXYData( &points, op );

		// write chromatogram data
		writeChromatogramData( id, *chromatogram, points, chromData );
		progress.setPosition( ++pos );			// pos == 4 + chromatograms

		// clear points
		points.clearPoints();
	}

	// chromatograms
	if( progress.isStopped() ) {
		return true;
	}
    m_fileHeader[ 14 ].val.ull = filetell( m_fp );					  // 14 : Chromatograms Align
	progress.setStatus( "Writing chromatogram information." );

    writeChromatograms( chromData, chromatogramMap, groupMap );//write m_chromatogramInfo to m_fp
	progress.setPosition( ++pos );	// pos == 5 + chromatograms

	// chromatogram property
	if( progress.isStopped() ) {
		return true;
	}
    m_fileHeader[ 15 ].val.ull = filetell( m_fp );					 // 15 : Chromatogram Properties Align
	progress.setStatus( "Writing chromatogram properties." );

	writeChromatogramProperties( dataSet, chromatogramMap );
	progress.setPosition( ++pos );	// pos == 6 + chromatograms

	// chromatogram user property
	if( progress.isStopped() ) {
		return true;
	}
    m_fileHeader[ 16 ].val.ull = filetell( m_fp );					 // 16 : Chromatogram User Properties Align
	progress.setStatus( "Writing chromatogram user properties." );

	writeChromatogramUserProperties( dataSet, chromatogramMap );
	progress.setPosition( ++pos );	// pos == 7 + chromatograms

	// spectrum data
	if( progress.isStopped() ) {
		return true;
	}

    m_fileHeader[ 17 ].val.ull = filetell( m_fp );                  // 17: Spectrum Data Align

	kome::core::MsppManager& msppMgr = kome::core::MsppManager::getInstance();
	std::string fileName = msppMgr.getTmpFileName( "mspp_spec_parts", ".tmp" );
	std::string partsPath = getpath( msppMgr.getTmpDir(), fileName.c_str() );
    FILE* partsFp = fileopen( partsPath.c_str(), "wb" ); //以二进制形式打开，write模式。

	int partsCnt = 0;

	kome::core::DataPoints tmpPts;
	std::map< kome::objects::Spectrum*, unsigned int > spectrumMap;
    //our data storged in here.
	for( unsigned int i = 0; i < dataSet.getNumberOfSpectra() &&  !progress.isStopped(); i++ ) {
		// spectrum
		kome::objects::Spectrum* spectrum = dataSet.getSpectrum( i );
		progress.setStatus(
			FMT(
				"Writing Spectrum Data [%d/%d] (%s)",
				( i + 1 ),
				dataSet.getNumberOfSpectra(),
				spectrum->getName()
			).c_str()
		);

		// ID
		unsigned int id = ( i + 1 );
		spectrumMap[ spectrum ] = id;

        // gets data points. Just one FRAME.
        spectrum->getXYData( &tmpPts, op ); //read XYData from m_fp, op means whether to process the XYData. LY
		for( unsigned int i = 0; i < tmpPts.getLength(); i++ ) {
			// x, y
			double x = tmpPts.getX( i );
			double y = tmpPts.getY( i );

			// add
			if( fabs( y ) > 0.0 ) {
				points.addPoint( x, y );
			}
		}

        // write spectrum data to m_fp, m_partInfo to partsFp.
		partsCnt += writeSpectrumData( id, *spectrum, points, partsFp );
		progress.setPosition( ++pos );	// pos == 7 + chromatograms + spectra

		// clear points
		tmpPts.clearPoints();
		points.clearPoints();
	}

	fflush( partsFp );
	fclose( partsFp );

	// spectra
	if( progress.isStopped() ) {
		return true;
	}
    m_fileHeader[ 18 ].val.ull = filetell( m_fp );					  // 18: Spectrum Align
	progress.setStatus( "Writing spectrum information." );

    writeSpectra( dataSet, spectrumMap, groupMap ); //write m_spectrumInfo to m_fp.
	progress.setPosition( ++pos );	// pos == 8 + chromatograms + spectra

	// spectrum part
	if( progress.isStopped() ) {
		return true;
	}
    m_fileHeader[ 19 ].val.ull = filetell( m_fp );					  // 19: Spectrum Part Align
	progress.setStatus( "Writing spectrum parts." );

    partsFp = fileopen( partsPath.c_str(), "rb" );//以二进制形式打开，read模式。
    writeSpectrumParts( partsCnt, partsFp ); //move m_partInfo from partsFp to m_fp. LY
	fclose( partsFp );
	progress.setPosition( ++pos );	// pos == 9 + chromatograms + spectra

	// spectrum property
	if( progress.isStopped() ) {
		return true;
	}
	m_fileHeader[ 20 ].val.ull = filetell( m_fp );					 // Spectrum Property Align
	progress.setStatus( "Writing spectrum properties." );

	writeSpectrumProperties( dataSet, spectrumMap );
	progress.setPosition( ++pos );	// pos == 10 + chromatograms + spectra

	// spectrum user property
	if( progress.isStopped() ) {
		return true;
	}
	m_fileHeader[ 21 ].val.ull = filetell( m_fp );					 // Spectrum User Property Align
	progress.setStatus( "Writing spectrum user properties." );

	writeSpectrumUserProperties( dataSet, spectrumMap );
	progress.setPosition( ++pos );	// pos == 11 + chromatograms + spectra

	// string table
	if( progress.isStopped() ) {
		return true;
	}
	m_fileHeader[ 22 ].val.ull = filetell( m_fp );					   // String Table Align

	progress.setStatus( "Writing string table." );
	m_fileHeader[ 23 ].val.ul = writeStringTable();				  // Compressed string table seize

	progress.setPosition( ++pos );	// pos == 12 + chromatograms + spectra

	m_fileHeader[ 24 ].val.ul = m_stringTable.size();				// Uncompressed String Table Size
	m_stringTable.clear();

	// rewrite file header
	if( progress.isStopped() ) {
		return true;
	}
	progress.setStatus( "Rewriting file header." );
	fileseek( m_fp, 0, SEEK_SET );
	WRITE_TO_FILE( m_fileHeader );
	progress.setPosition( ++pos );	// pos == 13 + chromatograms + spectra

	return true;
}

bool MsbIO0202::onSimplifyWriteMsb(){
    // log
    LOG_INFO( FMT( "Writing MSB format sample. [ver 2.2]" ) )

    std::vector< kome::objects::DataGroupNode* > groups;
//    getGroups( dataSet, groups );

    // file header
    m_fileHeader[ 0 ].val.ul = GET_DATA_SIZE( m_fileHeader );				     // Header Size
    m_fileHeader[ 1 ].val.uc = m_bigendian ? 0 : 1;							     // Endian
    m_fileHeader[ 4 ].val.ms = st( "sample.getSampleSet()->getFilePath()" );	 // File Path
    m_fileHeader[ 5 ].val.ms = st( "sample.getName()" );						 // Sample Name
    m_fileHeader[ 6 ].val.ms = st( "sample.getInstrument()" );			     	 // Instrument Name
    m_fileHeader[ 7 ].val.ms = st( "sample.getMsCompany()" );					 // manufacture
    m_fileHeader[ 8 ].val.ms = st( "sample.getSoftwareName()" );				 // software name
    m_fileHeader[ 9 ].val.ms = st( "sample.getSoftwareVersion()" );			     // software version
    m_fileHeader[ 22 ].val.t = time( nullptr );								     // Time

    WRITE_TO_FILE( m_fileHeader );

    // spectrum group
    m_fileHeader[ 10 ].val.ull = filetell( m_fp );			 // 10: Spectrum Group Align

    std::map< kome::objects::DataGroupNode*, unsigned int > groupMap;
//    groupMap[ sample.getRootDataGroupNode() ] = 0;
    unsigned int frameCnt = 10;
//    writeDataGroupNodes( groups, groupMap );
    writeSimplifyDataGroupNodes(frameCnt);
//    groups.push_back( sample.getRootDataGroupNode() );

    // spectrum group properties
    m_fileHeader[ 11 ].val.ull = filetell( m_fp );           // 11: Spectrum Group Properties Align

//    writeDataGroupNodeProperties( groups, groupMap );
    writeSimplifyDataGroupNodeProperties(frameCnt);

    m_fileHeader[ 12 ].val.ull = filetell( m_fp );          // 12: Spectrum Group User Properties Align
//    writeDataGroupNodeUserProperties( groups, groupMap );
    writeSimplifyDataGroupNodeUserProperties(frameCnt);

    groups.clear();

    // chromatogram data
    m_fileHeader[ 13 ].val.ull = filetell( m_fp );          // 13: Chromatogram Data Align

    kome::core::DataPoints points( kome::core::DataPoints::FLOAT );
    std::map< kome::objects::Chromatogram*, unsigned int > chromatogramMap;
    std::vector< ChromatogramDataInfo > chromData;

    // chromatograms
    m_fileHeader[ 14 ].val.ull = filetell( m_fp );				 // 14 : Chromatograms Align
    writeChromatograms( chromData, chromatogramMap, groupMap );  //write m_chromatogramInfo to m_fp

    // chromatogram property
    m_fileHeader[ 15 ].val.ull = filetell( m_fp );		 		 // 15 : Chromatogram Properties Align

    kome::objects::DataSet* tmp_dataSet = nullptr;
    writeChromatogramProperties( *tmp_dataSet, chromatogramMap );

    // chromatogram user property
    m_fileHeader[ 16 ].val.ull = filetell( m_fp );					 // 16 : Chromatogram User Properties Align
    writeChromatogramUserProperties( *tmp_dataSet, chromatogramMap );

    // spectrum data
    m_fileHeader[ 17 ].val.ull = filetell( m_fp );                  // 17: Spectrum Data Align

    kome::core::MsppManager& msppMgr = kome::core::MsppManager::getInstance();
    std::string fileName = msppMgr.getTmpFileName( "mspp_spec_parts", ".tmp", "G:\\QT\\qt_msb_test" );
    std::string partsPath = getpath( msppMgr.getTmpDir(), fileName.c_str() );
    FILE* partsFp = fileopen( partsPath.c_str(), "wb" ); //以二进制形式打开，write模式。

    int partsCnt = 0;

    kome::core::DataPoints tmpPts;
    std::map< kome::objects::Spectrum*, unsigned int > spectrumMap;
    //our data storged in here.    
    for( unsigned int i = 0; i < frameCnt; i++ ) {
        float minX = -1.0, maxX = -1.0;
        int length = 100;//每帧数据长度
        // create array
//        float* mzArray = new float[ length ];
//        float* intArray = new float[ length ];
        std::vector<float> mzArray(length);
        for(int j = 0; j < length; j++)
            mzArray[j] = 30 + j;
        std::vector<float> intArray(length, 2);

        // add
        tmpPts.reserve( length );
        for( unsigned int k = 0; k < length; k++ ) {
            // x, y
            double x = (double)mzArray[ k ];
            double y = (double)intArray[ k ];

            // add
            if( ( minX < 0.0 || x >= minX ) && ( maxX < 0.0 || x <= maxX ) ) {
                tmpPts.addPoint( x, y );
            }
        }
        // delete array
//        delete[] mzArray;
//        delete[] intArray;

        // ID
        unsigned int id = ( i + 1 );
//        spectrumMap[ spectrum ] = id;

        // write spectrum data to m_fp, and write m_partInfo to  partsFp.
//        partsCnt += writeSpectrumData( id, nullptr/**spectrum*/, tmpPts, partsFp );
        partsCnt += writeSimplifySpectrumData( id, tmpPts, partsFp );
        // clear points
        tmpPts.clearPoints();
        points.clearPoints();
    }
    fflush( partsFp );
    fclose( partsFp );

    // spectra
    m_fileHeader[ 18 ].val.ull = filetell( m_fp );					  // 18: Spectrum Align
//    writeSpectra( dataSet, spectrumMap, groupMap ); //write m_spectrumInfo to m_fp.
    writeSimplifySpectra( frameCnt ); //write m_spectrumInfo to m_fp. LYYYYY

    // spectrum part
    m_fileHeader[ 19 ].val.ull = filetell( m_fp );					  // 19: Spectrum Part Align

    partsFp = fileopen( partsPath.c_str(), "rb" );//以二进制形式打开，read模式。
    writeSpectrumParts( partsCnt, partsFp ); //move data from partsFp to m_fp. LY
    fclose( partsFp );


    // spectrum property

    m_fileHeader[ 20 ].val.ull = filetell( m_fp );					 // Spectrum Property Align
//    writeSpectrumProperties( dataSet, spectrumMap );
    writeSimplifySpectrumProperties( frameCnt );

    // spectrum user property
    m_fileHeader[ 21 ].val.ull = filetell( m_fp );					 // Spectrum User Property Align

//    writeSpectrumUserProperties( dataSet, spectrumMap );
    writeSimplifySpectrumUserProperties( frameCnt );

    // string table
    m_fileHeader[ 22 ].val.ull = filetell( m_fp );					 // String Table Align
    m_fileHeader[ 23 ].val.ul = writeStringTable();				     // Compressed string table seize
    m_fileHeader[ 24 ].val.ul = m_stringTable.size();				 // Uncompressed String Table Size
    m_stringTable.clear();

    fileseek( m_fp, 0, SEEK_SET );
    WRITE_TO_FILE( m_fileHeader );
    return true;
}
