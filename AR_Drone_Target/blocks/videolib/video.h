/*
    video.h - video driver

    Copyright (C) 2011 Hugo Perquin - http://blog.perquin.com

    This program is free software; you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation; either version 2 of the License, or
    (at your option) any later version.

    This program is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with this program; if not, write to the Free Software
    Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston,
    MA 02110-1301 USA.
*/ 
#ifndef _VIDEO_H
#define _VIDEO_H

#ifndef MATLAB_MEX_FILE

typedef struct {
    void * buf;
    size_t length;
}buffer_struct;

typedef struct {
	int seq;
	double timestamp;
	unsigned char* buf;
	int w;
	int h;
}img_struct;

typedef struct {
	char *device;
	int w;
	int h;
	int seq;
	unsigned int n_buffers;
	
//private members	
	int trigger;
	img_struct *img;
	buffer_struct * buffers;
	int fd;
}vid_struct;

vid_struct vid1;
img_struct* img1;

vid_struct vid2;
img_struct* img2;

#endif //MATLAB_MEX_FILE

void videoInit1(void);
//grabs next B&W image from stream (blocking)
void videorabImage1(unsigned char* mybuf);
void videoClose1(void);

void videoInit2(void);
//grabs next B&W image from stream (blocking)
void videorabImage2(unsigned char* mybuf);
void videoClose2(void);

//return timestamp in seconds with microsecond resolution
double util_timestamp();

#endif