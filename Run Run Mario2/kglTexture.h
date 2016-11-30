/////////////////////////////////////////////////////////////////////////////////////
//
//		kglTexuture.h
//		kglTexuture.cpp
//
// 用途 : 讀取 BMP 或 TGA 圖檔            
//        並且生成該貼圖材質物件
//
// 1) BMP => 一般讀取 24bit 為圖檔使用的內定格式 ,       
//		     可以使用 color key 透明色 (左下角 pixel 之值) 增加 alpha channel
//	
// 2) TGA => 圖檔格式內定為 32bit 的可含透明色之 alpha channel 
//        
//
// 
//    修正 :
//
// 1) 2003/04/18 crazier
//        利用 glu 的功能來調整圖檔的 dimension ( linear interpolation )
//        使之符合 2^n 的條件 , 所以之後可以讀入的圖檔不再有此限制 
//
// 2) 2003/04/26 
//        為了使用相同的 namespace std , 以配合 STL 的使用
//        所以讀檔的部分更改為 std:: 之下的 fstream 方式   
//
// 3) 2003/05/04   
//		  配合統一使用 string 處理字串
//
// 4) 2003/05/07 
//        傳入 string 的部分由 string* ( pointer ) 改為 string ( instance )
//
// 5) 2003/06/14
//		  加入預設的讀圖檔目錄路徑 , 資料夾的路徑都統一放在 directory.h 中
//
// 6) 2003/08/31
//		  scale image 的時候 , 在 RGB 的情況下 , 因為不是 32 bits 所以會有偏移的狀況發生 	
//        指定 unpack 為 32 bits ( 4 bytes ) 的排列方式 然後再復原
//
// **** last update date : 2003/06/14 C ****            
//
////////////////////////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////////////////////
//
//	****** quick note ******			                     2002/08/11 C
//
//	1) 可以讀取 .bmp .tga 的檔案 , 會依照檔頭自動判斷 
//	   但是限制 .bmp 需為 RGB 3 channel 24bit 而 
//     .tga 需為 RGBA 4 32bit 的格式 , 目前不支援有壓縮的格式
//
//  2) 第 2 項引數可指定為 GL_RGB 或是 GL_RGBA ,
//	   .bmp 指定 GL_RGBA 的話 , 就會用第 1 個 pixel 的資料作為 
//	   color key , 而 .tga 則自動使用 GL_RGBA 的模式
//
//	3) 後面有 4 項貼圖濾鏡的屬性 , 一般來說不指定就使用預設的方式 
//	   分別是 min_filter , mag_filter , wrap_s , wrap_t 
//	   若是有需要就自己設定 , 判斷 filter 有需要時就會自動製作 2d mipmaps
//
/////////////////////////////////////////////////////////////////////////////////


#ifndef _KGLTEXTURE_H_
#define _KGLTEXTURE_H_

#include <windows.h>
#include <gl/gl.h>
#include <gl/glu.h>

#include "kglGLExt.h"	// 預定內定使用 exetension 的定義功能

#include <fstream>
#include <string>
using namespace std ;

#define MIN_TEXTURE_SIZE 8	// 定義貼圖用的 texture 圖檔的最小 size 限制 ,
                            // 確保最少會延伸到這個 texel dimension  


//// 讀取貼圖圖檔 , 並依參數製成貼圖物件 , 傳回貼圖物件的id	////	

GLuint KFLoadText( string ,					// 貼圖檔名
		  		   GLint ,					// RGB or RGBA
				   GLint = GL_LINEAR ,		// 指定貼圖濾鏡 ,
				   GLint = GL_LINEAR ,		// 內定都是 GL_LINEAR
				   GLint = GL_REPEAT ,		// 指定環繞模式
				   GLint = GL_REPEAT 		// 內定都是 GL_REPEAT			     				   
				  ) ;

#endif
