#include "kglTexture.h"

GLuint KFLoadText( string filename ,		// 貼圖檔名
		  		    GLint mode ,				// RGB or RGBA
				    GLint min_filter ,		// 指定貼圖濾鏡 ,
				    GLint mag_filter ,		// 內定都是 GL_LINEAR
				    GLint wrap_s     ,		// 指定環繞模式
				    GLint wrap_t     )		// 內定都是 GL_REPEAT			     			
{							
	if( filename == "" )// 假如為空檔案名稱,return 0
		return NULL ;

	fstream inf ;
	inf.open(filename.c_str() , ios :: in | ios :: binary ) ;	
	if( !inf ) return NULL ;							// 先找檔案是否存在						

	GLubyte *pixel ,		// 圖形的 pixel 資料
            *b_pixel ,      // bind texture 用的資料		  
	        *position ;		// 記住目前要存放讀取資料的位置 , 輔助用	 
	  char  temp[ 2 ] ;		// 暫存資料用			
	GLuint  textID ,						// texture ID		    
	  	    width ,							// 圖檔寬度
		    height ,						// 圖檔高度			
		    b_width  = MIN_TEXTURE_SIZE ,	// bind texture 用的寬度
		    b_height = MIN_TEXTURE_SIZE ,	// bind texture 用的高度
		    count ;							// 迴圈用		

	inf.read( temp , 2 ) ;						// 先讀 2 bytes 進來	
	if( temp[ 0 ] == 'B' && temp[ 1 ] == 'M' )  // 由 header 確認得知是 BMP file
	{
		inf.seekg( 16 , ios :: cur ) ;						// 先跳過 16 bytes , 用不到的資訊	
		inf.read( ( char* ) &width  , sizeof( GLuint ) ) ;	// 取得圖檔寬度		
		inf.read( ( char* ) &height , sizeof( GLuint ) ) ;	// 取得圖檔長度		
		inf.seekg( 28 , ios :: cur ) ;						// 再跳過 28 bytes				

		height += 2;

		if( GL_RGB == mode  )	// 單純的 RGB
		{
			pixel = new GLubyte[ width * height * 3 ] ;			
			inf.read( ( char* )pixel , width * height * 3) ;			
		}
		else	// 擴為 RGBA => color keying , 用第一個 (左下角) pixel 資料為 key
		{
			pixel = new GLubyte[ width * height * 4 ] ;						
			inf.read( ( char* )pixel , 3 ) ;		// 先讀取要用為 key 的第一個 pixel data
			pixel[ 3 ] = 0 ;			// 並設為透明			
			position = pixel + 4 ;

			for( count = 1 ; count < height * width ; count++ )	// read data
			{
				inf.read( ( char* )position , 3 ) ;					
				if( position[ 0 ] == pixel[ 0 ] && 
					position[ 1 ] == pixel[ 1 ] && 
					position[ 2 ] == pixel[ 2 ] )
					 position[ 3 ] = ( GLubyte ) 0 ;
				else position[ 3 ] = ( GLubyte ) 255 ;		// color keying or not
				position += 4 ;
			}
		}	

		height -= 2;

		while( b_width  < width  ) b_width  += b_width  ;	// 計算出 bind texture 用的 size
		while( b_height < height ) b_height += b_height ;
			
		if( ( b_width == width ) && ( b_height == height ) ) b_pixel = pixel ;	// 原圖已經符合 bind 條件
		else                                                                    // 若是已經符合就不用作 resize
		{
			b_width  /= 2 ;		// 縮小成上一級
			b_height /= 2 ;

			if( GL_RGB == mode )
			{
				b_pixel = new GLubyte[ b_width * b_height * 3 ] ;										

				glPixelStorei( GL_UNPACK_ALIGNMENT , 4  ) ;
				gluScaleImage( GL_RGB , width   , height   , GL_UNSIGNED_BYTE , pixel ,
                                        b_width , b_height , GL_UNSIGNED_BYTE , b_pixel ) ;																
				glPixelStorei( GL_UNPACK_ALIGNMENT , 1  ) ;

			}
			else	// mode == GL_RGBA
			{
				b_pixel = new GLubyte[ b_width * b_height * 4 ] ;						
				gluScaleImage( GL_RGBA , width   , height   , GL_UNSIGNED_BYTE , pixel ,
                                         b_width , b_height , GL_UNSIGNED_BYTE , b_pixel ) ; 
			}
			delete [] pixel ;
		}
	}	
	else	// 讀取 TGA 的格式
	{
		GLushort temp_w , temp_h ;					// 暫存長寬

		inf.seekg( 10 , ios :: cur ) ;				// 先跳過 10 bytes , 用不到的資訊		
		inf.read( ( char* ) &temp_w , 2 ) ;			// 取得圖檔寬度		
		inf.read( ( char* ) &temp_h , 2 ) ;			// 取得圖檔長度				
		inf.seekg( temp[ 0 ] + 2 , ios :: cur ) ;	// 跳到真正存放 pixel 的資料欄		

		pixel = new GLubyte[ temp_w * temp_h * 4 ] ;	// 讀入資料
		inf.read( ( char* )pixel , temp_w * temp_h * 4 ) ;	

		width  = ( GLuint ) temp_w ;				// 給定長寬的資料
		height = ( GLuint ) temp_h ;							
		mode   = GL_RGBA ;							// default to RGBA mode		

		while( b_width  < width  ) b_width  += b_width  ;
		while( b_height < height ) b_height += b_height ;
			
		if( ( b_width == width ) && ( b_height == height ) ) b_pixel = pixel ;
		else 
		{		
			b_width  /= 2 ;				// 縮回上一級
			b_height /= 2 ;

			b_pixel = new GLubyte[ b_width * b_height * 4 ] ;						
			gluScaleImage( GL_RGBA , width   , height   , GL_UNSIGNED_BYTE , pixel ,
				                     b_width , b_height , GL_UNSIGNED_BYTE , b_pixel ) ;
			delete [] pixel ;
		}
	}
	inf.close() ;								// 讀取完畢 , 關閉檔案

	glGenTextures( 1 , &textID ) ;				// 依照參數使用不同的貼圖材質生成方式 
	glBindTexture( GL_TEXTURE_2D, textID ) ;    // 先設定貼圖參數        		
	glTexParameteri( GL_TEXTURE_2D , GL_TEXTURE_MIN_FILTER , min_filter ) ;   
	glTexParameteri( GL_TEXTURE_2D , GL_TEXTURE_MAG_FILTER , mag_filter ) ;
	glTexParameteri( GL_TEXTURE_2D , GL_TEXTURE_WRAP_S     , wrap_s     ) ;
	glTexParameteri( GL_TEXTURE_2D , GL_TEXTURE_WRAP_T     , wrap_t     ) ;		

	if( min_filter == GL_LINEAR || min_filter == GL_NEAREST )	
	{
		if( GL_RGB == mode )
			glTexImage2D( GL_TEXTURE_2D, 0 , GL_RGB , b_width , b_height , 0 , 
			              GL_BGR , GL_UNSIGNED_BYTE , b_pixel ) ;	
		else
			glTexImage2D( GL_TEXTURE_2D, 0 , GL_RGBA , b_width , b_height , 0 , 
			              GL_BGRA , GL_UNSIGNED_BYTE , b_pixel ) ;		
	}
	else		
	{
		if( GL_RGB == mode )
			gluBuild2DMipmaps( GL_TEXTURE_2D, 3 , b_width , b_height , 
			                   GL_BGR , GL_UNSIGNED_BYTE , b_pixel ) ;	
		else
			gluBuild2DMipmaps( GL_TEXTURE_2D, 4 , b_width , b_height ,
			                   GL_BGRA , GL_UNSIGNED_BYTE , b_pixel ) ;		 	
	}
		
	delete [] b_pixel ;		// 釋放 bind texture 用的 b_pixel 資料
	return textID ;			// 傳回貼圖材質的物件 ID
}