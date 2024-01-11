//---------------------------------------------------------------
// Copyright 2023, Ed Keenan, all rights reserved.
//---------------------------------------------------------------

#include "answerRegistry.h"

#define QuestionAnswer(x,y)  Answer::registerAnswer(0,x,y)

unsigned char data[] =
{ 
  0xEB, 0xCD, 0x22, 0x4F,
  0x73, 0xB5, 0xF3, 0x35,
  0x23, 0x24, 0x01, 0xFE,
  0xCD, 0xE3, 0x44, 0x85,
  0x66, 0x43, 0x75, 0x33,
  0x39, 0x5C, 0x22, 0x11,
  0x56, 0xA8, 0xAA, 0x13,
  0x64, 0x82, 0x68, 0x26 
};


void Students_PointerWalk()
{
	//
	// STARTING:
	//
	//    unsigned char  *p;  // char are 8-bits long
	//    p = &data[0];       
	//
	// Q0:
	//    what value is p[0]?
	// Q1:
	//    what value is *(p+3)?
	// Q2:
	//    what value is *(2+p)?

    // ADD CODE to find the answer...
    // YES - you are coding here:

	// example:  -- no work inside the Answer only Value variable
	unsigned char *p;
	p = &data[0];
	unsigned char val = p[0];
	QuestionAnswer( 0, val);

	val = *(p+3);
	QuestionAnswer( 1, val);

	// Now your turn
	val = *(2 + p);
	QuestionAnswer( 2, val);

	// Continuing (leaving the pointer where it is)
	//
	p = p + 12;
	//
	// Q3:
	//   what is value *(p)?
	// Q4:
	//   what is value p[3]?
	// Q5:
	//   what is value *p++?
	val = *(p);
	QuestionAnswer(3, val);
	val = p[3];
	QuestionAnswer(4, val);
	val = *p++;
	QuestionAnswer(5, val);

	// Continuing (leaving the pointer where it is)
	//
	p += 6;
	//
	// Q6:
	//   what is value *--p?
	// Q7:
	//   what is value p[3]?
	val = *--p;
	QuestionAnswer(6, val);
	val = p[3];
	QuestionAnswer(7, val);

	// Continuing (leaving the pointer where it is)
	//
	p = p + 1;
	//
	// Q8:
	//   what is value *p++?
	// Q9:
	//   what is value *(p + 3)?
	val = *p++;
	QuestionAnswer(8, val);
	val = *(p + 3);
	QuestionAnswer(9, val);

	// Continuing (leaving the pointer where it is)
	//
	p = 5 + p;
	//
	// Q10:
	//   what is value *(p++)?
	// Q11:
	//   what is value *(--p)?
	val = *(p++);
	QuestionAnswer(10, val);
	val = *(--p);
	QuestionAnswer(11, val);

	//
	// STARTING:
	//
	unsigned int   *r;  // ints are 32-bits long
	r = (unsigned int *)&data[0];

	unsigned int val2;
	//
	// Q12:
	//   what is value *(r)?
	// Q13:
	//   what is value *(r + 3)?
	val2 = *(r);
	QuestionAnswer(12, val2);
	val2 = *(r + 3);
	QuestionAnswer(13, val2);


	// Continuing (leaving the pointer where it is)
	//
	r++;
	//
	// Q14:
	//   what is value *r++?
	//
	r = r + 2;
	//
	// Q15:
	//   what is value r[1]?
	//
	r = r + 1;
	//
	// Q16:
	//   what is value r[0]?
	val2 = *r++;
	QuestionAnswer(14, val2);
	val2 = r[1];
	QuestionAnswer(15, val2);
	val2 = r[0];
	QuestionAnswer(16, val2);

	// Continuing (leaving the pointer where it is)
	// 
	unsigned short *s;  // shorts are 16-bits long
	s = (unsigned short *)r;
	//
	// Q17:
	//   what is value s[-3]?
	//
	s = s - 3;
	//
	// Q18:
	//   what is value s[2]?
	//
	s += 5;
	//
	// Q19:
	//   what is value *(s + 3)?
	// Q20:
	//   what is value *(s)?

	unsigned short val3;
	val3 = s[-3];
	QuestionAnswer(17, val3); 
	val3 = s[2];
	QuestionAnswer(18, val3);
	val3 = *(s + 3);
	QuestionAnswer(19, val3);
	val3 = *(s);
	QuestionAnswer(20, val3);

	// Continuing (leaving the pointer where it is)
	//
	p = (unsigned char *)s;
	//
	// Q21:
	//   what is value *(p + 1)?
	//
	p += 5;
	//
	// Q22:
	//   what is value p[-9]?
	//
	--p;
	//
	// Q23:
	//   what is value p[0]?

	unsigned char val4;
	val4 = *(p + 1);
	QuestionAnswer(21, val4);
	val4 = p[-9];
	QuestionAnswer(22, val4);
	val4 = p[0];
	QuestionAnswer(23, val4);

}

// --- End of File ---

