#ifndef __BEEP_H
#define __BEEP_H

#include "sys.h"
#define beep  PAout(8)

/*以下为调音符对应的频率*/

#define NOTE_0  		0  //停止符
//中音_1_1代表1#

#define NOTE_1 			523
#define NOTE_1_1 		554
#define NOTE_2 			587
#define NOTE_2_2 		633
#define NOTE_3 			659
#define NOTE_4 			698
#define NOTE_4_1 		740
#define NOTE_5			784
#define NOTE_5_1		831
#define NOTE_6 			880
#define NOTE_6_1 		932
#define NOTE_7 			988

//低音_1_1代表1#
#define NOTE_L1 		262
#define NOTE_L1_1 	277
#define NOTE_L2 		294
#define NOTE_L2_2 	311
#define NOTE_L3 		330
#define NOTE_L4 		349
#define NOTE_L4_1 	370
#define NOTE_L5			392
#define NOTE_L5_1		415
#define NOTE_L6 		440
#define NOTE_L6_1 	466
#define NOTE_L7 		494

//高音_1_1代表1#
#define NOTE_H1 		1046
#define NOTE_H1_1 	1109
#define NOTE_H2 		1175
#define NOTE_H2_2 	1245
#define NOTE_H3 		1318
#define NOTE_H4 		1397
#define NOTE_H4_1 	1480
#define NOTE_H5			1568
#define NOTE_H5_1		1661
#define NOTE_H6 		1760
#define NOTE_H6_1 	1865
#define NOTE_H7 		1976

//以下定为节拍
#define racket_delay 	909 												//歌曲每个拍子需要的延时ms
#define racket_3_2 		((u32)(racket_delay/2.0*3)) //3/2的节拍
#define racket_1_2 		((u32)(racket_delay/2.0))	  //1/2的节拍
#define racket_3_4 		((u32)(racket_delay/4.0*3)) //3/4的节拍
#define racket_3_8 		((u32)(racket_delay/8.0*3)) //3/8的节拍
#define racket_1_4 		((u32)(racket_delay/4.0))	  //1/4的节拍
void BEEP_Init(void);
void BEEP_1(u8 fq);
void MIDI_PLAY(void);
#endif

