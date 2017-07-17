/****************************************************************/
/*                                                              */
/*                           date.h                             */
/*                                                              */
/*                  DOS General Date Structure                  */
/*                                                              */
/*                      Copyright (c) 1995                      */
/*                      Pasquale J. Villani                     */
/*                      All Rights Reserved                     */
/*                                                              */
/* This file is part of DOS-C.                                  */
/*                                                              */
/* DOS-C is free software; you can redistribute it and/or       */
/* modify it under the terms of the GNU General Public License  */
/* as published by the Free Software Foundation; either version */
/* 2, or (at your option) any later version.                    */
/*                                                              */
/* DOS-C is distributed in the hope that it will be useful, but */
/* WITHOUT ANY WARRANTY; without even the implied warranty of   */
/* MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See    */
/* the GNU General Public License for more details.             */
/*                                                              */
/* You should have received a copy of the GNU General Public    */
/* License along with DOS-C; see the file COPYING.  If not,     */
/* write to the Free Software Foundation, 675 Mass Ave,         */
/* Cambridge, MA 02139, USA.                                    */
/****************************************************************/

/* TC 2.01 complains if `date' is defined twice. -- ror4 */
#ifndef DOSC_DATE_H
#define DOSC_DATE_H

typedef struct s_dosdate
{
	INT16U year;
	INT8U monthday, month;
} dosdate_t;

typedef struct s_dostime
{
	INT8U minute, hour, hundredth, second;
} dostime_t;

typedef INT16U dostime;
typedef INT16U dosdate;

typedef  INT32U time_t;

struct utimbuf 	 {
	 time_t actime;
	 time_t modtime;
};

/* FAT file date - takes the form of yyyy yyym mmmd dddd where physical */
/* year=1980+yyyyyy                                                     */
#define EPOCH_YEAR      1980    /* for Tues 1-1-80 epoch                */

#define DT_YEAR(d)      ((((d)>>9)&0x7f) + EPOCH_YEAR)
#define DT_MONTH(d)     (((d)>>5)&0x0f)
#define DT_DAY(d)       ((d)&0x1f)

#define TM_HOUR(t)		(((t)>>11)&0x1f)
#define TM_MIN(t)		(((t)>>5)&0x3f)
#define TM_DEC(t)		((t)&0x1f)

#define DT_ENCODE(m,d,y) ((((m)&0x0f)<<5)|((d)&0x1f)|(((y)&0x7f)<<9))

#define EPOCH_WEEKDAY   2       /* Tuesday (i. e.-  0 == Sunday)        */
#define EPOCH_MONTH     1       /* January                              */
#define EPOCH_DAY       1       /* 1 for January 1                      */
#define EPOCH_YEAR      1980    /* for Tues 1-1-80 epoch                */

#endif

