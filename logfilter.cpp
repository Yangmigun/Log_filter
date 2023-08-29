//----------------------------------------------------------------------------------
//		�ΐ��ϊ��t�B���^  for AviUtl ver0.99e�ȍ~
//----------------------------------------------------------------------------------
#include <Windows.h>
#include <filter.h>
#include <cmath>


//---------------------------------------------------------------------
//		�t�B���^�\���̒�`
//---------------------------------------------------------------------
#define	TRACK_N	1		//	�g���b�N�o�[�̐�
TCHAR *track_name[] = { const_cast<char*>("minimum") };
int track_default[] = { 0 };
int track_s[] = { 0 };
int track_e[] = { +4096 };
#define	CHECK_N	0		//	�`�F�b�N�{�b�N�X�̐�

FILTER_DLL filter = {
	.flag = FILTER_FLAG_EX_INFORMATION,
	.x = 0, .y = 0,
	.name = const_cast<char*>("�ΐ��ϊ��t�B���^"),
	.track_n = TRACK_N,
	.track_name = track_name,
	.track_default = track_default,
	.track_s = track_s, .track_e = track_e,
	.check_n = CHECK_N,
	.check_name = NULL,
	.check_default = NULL,
	.func_proc = &func_proc,
	.func_init = NULL,
	.func_exit = NULL,
	.func_update = NULL,
	.func_WndProc = NULL,
	.track = NULL, .check = NULL,
	.ex_data_ptr = NULL,
	.ex_data_size = NULL,
	.information = const_cast<char*>("�ΐ��ϊ��t�B���^ version 0.01 by yangm8i"),
	.func_save_start = NULL,
	.func_save_end = NULL,
};

//---------------------------------------------------------------------
//		�t�B���^�\���̂̃|�C���^��n���֐�
//---------------------------------------------------------------------
EXTERN_C FILTER_DLL __declspec(dllexport)* __stdcall GetFilterTable(void)
{
	return &filter;
}

//---------------------------------------------------------------------
//		�t�B���^�����֐�
//---------------------------------------------------------------------
BOOL func_proc(FILTER* fp, FILTER_PROC_INFO* fpip)
{
	int			x, y;
	PIXEL_YC* ycp;

	int c = 4096 / 7.7;
	int d = 4096 / (4096 - fp->track[0]);
	//	�e�v�f�Ƀg���b�N�o�[�̒l�𑫂�����
	for (y = 0; y < fpip->h; y++) {
		ycp = fpip->ycp_edit + y * fpip->max_w;
		for (x = 0; x < fpip->w; x++) {
			int y2 = ycp->y + 1 - fp->track[0];
			ycp->y = (short)(c * log10(y2 * d));
			ycp++;
		}
	}

	return TRUE;
}