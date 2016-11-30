/////////////////////////////////////////////////////////////////////////////////////
//
//		kglTexuture.h
//		kglTexuture.cpp
//
// �γ~ : Ū�� BMP �� TGA ����            
//        �åB�ͦ��ӶK�ϧ��誫��
//
// 1) BMP => �@��Ū�� 24bit �����ɨϥΪ����w�榡 ,       
//		     �i�H�ϥ� color key �z���� (���U�� pixel ����) �W�[ alpha channel
//	
// 2) TGA => ���ɮ榡���w�� 32bit ���i�t�z���⤧ alpha channel 
//        
//
// 
//    �ץ� :
//
// 1) 2003/04/18 crazier
//        �Q�� glu ���\��ӽվ���ɪ� dimension ( linear interpolation )
//        �Ϥ��ŦX 2^n ������ , �ҥH����i�HŪ�J�����ɤ��A�������� 
//
// 2) 2003/04/26 
//        ���F�ϥάۦP�� namespace std , �H�t�X STL ���ϥ�
//        �ҥHŪ�ɪ�������אּ std:: ���U�� fstream �覡   
//
// 3) 2003/05/04   
//		  �t�X�Τ@�ϥ� string �B�z�r��
//
// 4) 2003/05/07 
//        �ǤJ string �������� string* ( pointer ) �אּ string ( instance )
//
// 5) 2003/06/14
//		  �[�J�w�]��Ū���ɥؿ����| , ��Ƨ������|���Τ@��b directory.h ��
//
// 6) 2003/08/31
//		  scale image ���ɭ� , �b RGB �����p�U , �]�����O 32 bits �ҥH�|�����������p�o�� 	
//        ���w unpack �� 32 bits ( 4 bytes ) ���ƦC�覡 �M��A�_��
//
// **** last update date : 2003/06/14 C ****            
//
////////////////////////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////////////////////
//
//	****** quick note ******			                     2002/08/11 C
//
//	1) �i�HŪ�� .bmp .tga ���ɮ� , �|�̷����Y�۰ʧP�_ 
//	   ���O���� .bmp �ݬ� RGB 3 channel 24bit �� 
//     .tga �ݬ� RGBA 4 32bit ���榡 , �ثe���䴩�����Y���榡
//
//  2) �� 2 ���޼ƥi���w�� GL_RGB �άO GL_RGBA ,
//	   .bmp ���w GL_RGBA ���� , �N�|�β� 1 �� pixel ����Ƨ@�� 
//	   color key , �� .tga �h�۰ʨϥ� GL_RGBA ���Ҧ�
//
//	3) �᭱�� 4 ���K���o�誺�ݩ� , �@��ӻ������w�N�ϥιw�]���覡 
//	   ���O�O min_filter , mag_filter , wrap_s , wrap_t 
//	   �Y�O���ݭn�N�ۤv�]�w , �P�_ filter ���ݭn�ɴN�|�۰ʻs�@ 2d mipmaps
//
/////////////////////////////////////////////////////////////////////////////////


#ifndef _KGLTEXTURE_H_
#define _KGLTEXTURE_H_

#include <windows.h>
#include <gl/gl.h>
#include <gl/glu.h>

#include "kglGLExt.h"	// �w�w���w�ϥ� exetension ���w�q�\��

#include <fstream>
#include <string>
using namespace std ;

#define MIN_TEXTURE_SIZE 8	// �w�q�K�ϥΪ� texture ���ɪ��̤p size ���� ,
                            // �T�O�ַ̤|������o�� texel dimension  


//// Ū���K�Ϲ��� , �ḛ̀Ѽƻs���K�Ϫ��� , �Ǧ^�K�Ϫ���id	////	

GLuint KFLoadText( string ,					// �K���ɦW
		  		   GLint ,					// RGB or RGBA
				   GLint = GL_LINEAR ,		// ���w�K���o�� ,
				   GLint = GL_LINEAR ,		// ���w���O GL_LINEAR
				   GLint = GL_REPEAT ,		// ���w��¶�Ҧ�
				   GLint = GL_REPEAT 		// ���w���O GL_REPEAT			     				   
				  ) ;

#endif
