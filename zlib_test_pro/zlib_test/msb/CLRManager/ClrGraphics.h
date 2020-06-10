/**
 * @file ClrGraphics.h
 * @brief interfaces of ClrGraphics class
 *
 * @author S.Tanaka
 * @date 2006.09.08
 * 
 * Copyright(C) 2006-2014 Eisai Co., Ltd. All rights reserved.
 */


#ifndef __KOME_CLR_GRAPHICS_H__
#define __KOME_CLR_GRAPHICS_H__


#include "ClrGraphicsBase.h"


namespace kome {
	namespace clr {

		/**
		 * @class ClrGraphics
		 * @brief Graphics class that has managed class object
		 */
		class ClrGraphics : public kome::img::Graphics {
		public:
			/**
			 * @fn ClrGraphics()
			 * @brief constructor
			 */
			ClrGraphics();

			/**
			 * @fn virtual ~ClrGraphics()
			 * @brief destructor
			 */
			virtual ~ClrGraphics();

		protected:
			/** base spectrum object */
			gcroot< ClrGraphicsBase^ > m_baseGraphics;

		public:
			/**
			 * @fn void setBaseGraphics( ClrGraphicsBase^ baseGraphics )
			 * @brief sets base graphics object
			 * @param[in] baseGraphics base graphics object
			 */
			void setBaseGraphics( ClrGraphicsBase^ baseGraphics );

			/**
			 * @fn ClrGraphicsBase^ getBaseGraphics()
			 * @brief gets base graphics object
			 * @return base graphics object
			 */
			ClrGraphicsBase^ getBaseGraphics();

		protected:
			/**
			 * @fn virtual void onSetSize( const unsigned int width, const unsigned int height )
			 * @brief This method is called when the size of graphics is changed. (override method)
			 * @param[in] width graphics width
			 * @param[in] height graphics height
			 */
			virtual void onSetSize( const unsigned int width, const unsigned int height );

			/**
			 * @fn virtual void onSetDrawStyle( const DrawStyle style )
			 * @brief This method is called by setDrawStyle method. (override method)
			 * @param[in] style draw style
			 */
			virtual void onSetDrawStyle( const DrawStyle style );

			/**
			 * @fn virtual void onSetFillPattern( const FillPattern pattern )
			 * @brief This method is called by setFillPattern method. (override method)
			 * @param[in] pattern fill pattern
			 */
			virtual void onSetFillPattern( const FillPattern pattern );

			/**
			 * @fn virtual void onSetFillStyle( const FillStyle style )
			 * @brief This method is called by setFillStyle method. (override method)
			 * @param[in] style fill style
			 */
			virtual void onSetFillStyle( const FillStyle style );

			/**
			 * @fn virtual void onSetTextHAlign( const TextHAlign hAlign )
			 * @brief This method is called by setTextHAlign method. (override method)
			 * @param[in] hAlign text horizontal align
			 */
			virtual void onSetTextHAlign( const TextHAlign hAlign );

			/**
			 * @fn virtual void onSetTextVAlign( const TextVAlign vAlign )
			 * @brief This method is called by setTextVAlign method. (override method)
			 * @param[in] vAlign text vertical align
			 */
			virtual void onSetTextVAlign( const TextVAlign vAlign );

			/**
			 * @fn virtual void onSetColor( const COLOR color )
			 * @brief this method is called by setColor method. (override method)
			 * @param[in] color color
			 */
			virtual void onSetColor( const COLOR color );

			/**
			 * @fn virtual void onSetFont( kome::img::Font& font )
			 * @brief This method is called by setFont method. (override method)
			 * @param[in] font font information object
			 */
			virtual void onSetFont( kome::img::Font& font );

			/**
			 * @fn virtual void onSetPen( unsigned int width )
			 * @brief This method is called by setPen method. (override method)
			 * @param[in] width width
			 */
			virtual void onSetPen( unsigned int width );
			
			/**
			 * @fn virtual void onDrawLines(
					int* const points,
					unsigned int num
				)
			 * @brief This mtdhod is called by drawLines method. (override method)
			 * @param[in] points points array
			 * @param[in] num the number of points. (The size of points is 2 * num.)
			 */
			virtual void onDrawLines(
				int* const points,
				const unsigned int num
			);

			/**
			 * @fn virtual void onFillPolygon(
					int* const points,
					const unsigned int num
				)
			 * @brief This method is called by fillPolygon or fillRect. (override method)
			 * @param[in] points the vertex of a polygon
			 * @param[in] num the number of vertices (The size of points is 2 * num.)
			 */
			virtual void onFillPolygon(
				int* const points,
				const unsigned int num
			);

			/**
			 * @fn virtual void onDrawEllipticArc(
						const int px,
						const int py,
						const int width,
						const int height,
						const double start,
						const double end,
						const bool fill
					)
			 * @brief This method is called by drawCircle, drawEllipse, drawArc, drawEllipticArc method. (override method)
			 * @param[in] px the x coordinate of upper-left corner of the rectangle that contains the ellipse
			 * @param[in] py the y coordinate of upper-left corner of the rectangle that contains the ellipse
			 * @param[in] width the width of the rectangle that contains the ellipse
			 * @param[in] height the height of the rectangle that contains the ellipse
			 * @param[in] start start of the arc (degree)
			 * @param[in] end end of the arc (degree)
			 * @param[in] fill If true, drawing shape is filled.
			 */
			virtual void onDrawEllipticArc(
				const int px,
				const int py,
				const int width,
				const int height,
				const double start,
				const double end,
				const bool fill
			);

			/**
			 * @fn virtual void onDrawText(
					const char* str,
					const int px,
					const int py,
					const int angle
				)
			 * @brief This method is called by drawText method. (override method)
			 * @param[in] str the string to be drawn
			 * @param[in] px x coordinate of position
			 * @param[in] py y coordinate of position
			 * @param[in] angle rotated text angle
			 */
			virtual void onDrawText(
				const char* str,
				const int px,
				const int py,
				const int angle
			);

			/**
			 * @fn virtual void onGetTextSize(
					const char* str,
					int* width,
					int* height
				)
			 * @brief This method is called by getTextSize method. (override method)
			 * @param[in] str the string
			 * @param[out] width the pointer to store text width
			 * @param[out] height the pointer to store text height
			 */
			virtual void onGetTextSize(
				const char* str,
				int* width,
				int* height
			);

			/**
			 * @fn virtual void onDrawPoint( const int px, const int py )
			 * @brief This method is called by drawPoint method. (override method)
			 * @param[in] px x coordinate of point
			 * @param[in] py y coordinate of point
			 */
			virtual void onDrawPoint( const int px, const int py );

			/**
			 * @fn virtual void onDrawBitmap( kome::img::BitmapData& bitmap, const int px, const int py, const bool transparent )
			 * @brief This method is called by drawBitmap method (override method)
			 * @param[in] bitmap bitmap data
			 * @param[in] px x coordinate of bitmap position
			 * @param[in] py y coordinate of bitmap position
			 * @param[in] transparent transparent flag
			 */
			virtual void onDrawBitmap( kome::img::BitmapData& bitmap, const int px, const int py, const bool transparent );

			/**
			 * @fn virtual COLOR onGetPixel( const int px, const int py )
			 * @brief This method is called by getPixel method (override method)
			 * @param[in] px x coordinate of bitmap position
			 * @param[in] py y coordinate of bitmap position
			 * @return pixel color
			 */
			virtual COLOR onGetPixel( const int px, const int py );

			/**
			 * @fn virtual void onFlush()
			 * @brief This method is called by flush method. (override method)
			 */
			virtual void onFlush();
		};
	}
}

#endif	// __KOME_CLR_GRAPHICS_H__
