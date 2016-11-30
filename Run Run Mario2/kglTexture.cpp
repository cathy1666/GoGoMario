#include "kglTexture.h"

GLuint KFLoadText( string filename ,		// �K���ɦW
		  		    GLint mode ,				// RGB or RGBA
				    GLint min_filter ,		// ���w�K���o�� ,
				    GLint mag_filter ,		// ���w���O GL_LINEAR
				    GLint wrap_s     ,		// ���w��¶�Ҧ�
				    GLint wrap_t     )		// ���w���O GL_REPEAT			     			
{							
	if( filename == "" )// ���p�����ɮצW��,return 0
		return NULL ;

	fstream inf ;
	inf.open(filename.c_str() , ios :: in | ios :: binary ) ;	
	if( !inf ) return NULL ;							// �����ɮ׬O�_�s�b						

	GLubyte *pixel ,		// �ϧΪ� pixel ���
            *b_pixel ,      // bind texture �Ϊ����		  
	        *position ;		// �O��ثe�n�s��Ū����ƪ���m , ���U��	 
	  char  temp[ 2 ] ;		// �Ȧs��ƥ�			
	GLuint  textID ,						// texture ID		    
	  	    width ,							// ���ɼe��
		    height ,						// ���ɰ���			
		    b_width  = MIN_TEXTURE_SIZE ,	// bind texture �Ϊ��e��
		    b_height = MIN_TEXTURE_SIZE ,	// bind texture �Ϊ�����
		    count ;							// �j���		

	inf.read( temp , 2 ) ;						// ��Ū 2 bytes �i��	
	if( temp[ 0 ] == 'B' && temp[ 1 ] == 'M' )  // �� header �T�{�o���O BMP file
	{
		inf.seekg( 16 , ios :: cur ) ;						// �����L 16 bytes , �Τ��쪺��T	
		inf.read( ( char* ) &width  , sizeof( GLuint ) ) ;	// ���o���ɼe��		
		inf.read( ( char* ) &height , sizeof( GLuint ) ) ;	// ���o���ɪ���		
		inf.seekg( 28 , ios :: cur ) ;						// �A���L 28 bytes				

		height += 2;

		if( GL_RGB == mode  )	// ��ª� RGB
		{
			pixel = new GLubyte[ width * height * 3 ] ;			
			inf.read( ( char* )pixel , width * height * 3) ;			
		}
		else	// �X�� RGBA => color keying , �βĤ@�� (���U��) pixel ��Ƭ� key
		{
			pixel = new GLubyte[ width * height * 4 ] ;						
			inf.read( ( char* )pixel , 3 ) ;		// ��Ū���n�ά� key ���Ĥ@�� pixel data
			pixel[ 3 ] = 0 ;			// �ó]���z��			
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

		while( b_width  < width  ) b_width  += b_width  ;	// �p��X bind texture �Ϊ� size
		while( b_height < height ) b_height += b_height ;
			
		if( ( b_width == width ) && ( b_height == height ) ) b_pixel = pixel ;	// ��Ϥw�g�ŦX bind ����
		else                                                                    // �Y�O�w�g�ŦX�N���Χ@ resize
		{
			b_width  /= 2 ;		// �Y�p���W�@��
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
	else	// Ū�� TGA ���榡
	{
		GLushort temp_w , temp_h ;					// �Ȧs���e

		inf.seekg( 10 , ios :: cur ) ;				// �����L 10 bytes , �Τ��쪺��T		
		inf.read( ( char* ) &temp_w , 2 ) ;			// ���o���ɼe��		
		inf.read( ( char* ) &temp_h , 2 ) ;			// ���o���ɪ���				
		inf.seekg( temp[ 0 ] + 2 , ios :: cur ) ;	// ����u���s�� pixel �������		

		pixel = new GLubyte[ temp_w * temp_h * 4 ] ;	// Ū�J���
		inf.read( ( char* )pixel , temp_w * temp_h * 4 ) ;	

		width  = ( GLuint ) temp_w ;				// ���w���e�����
		height = ( GLuint ) temp_h ;							
		mode   = GL_RGBA ;							// default to RGBA mode		

		while( b_width  < width  ) b_width  += b_width  ;
		while( b_height < height ) b_height += b_height ;
			
		if( ( b_width == width ) && ( b_height == height ) ) b_pixel = pixel ;
		else 
		{		
			b_width  /= 2 ;				// �Y�^�W�@��
			b_height /= 2 ;

			b_pixel = new GLubyte[ b_width * b_height * 4 ] ;						
			gluScaleImage( GL_RGBA , width   , height   , GL_UNSIGNED_BYTE , pixel ,
				                     b_width , b_height , GL_UNSIGNED_BYTE , b_pixel ) ;
			delete [] pixel ;
		}
	}
	inf.close() ;								// Ū������ , �����ɮ�

	glGenTextures( 1 , &textID ) ;				// �̷ӰѼƨϥΤ��P���K�ϧ���ͦ��覡 
	glBindTexture( GL_TEXTURE_2D, textID ) ;    // ���]�w�K�ϰѼ�        		
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
		
	delete [] b_pixel ;		// ���� bind texture �Ϊ� b_pixel ���
	return textID ;			// �Ǧ^�K�ϧ��誺���� ID
}