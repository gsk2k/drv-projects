
#ifndef DRIVER_V4L2_H
#define DRIVER_V4L2_H

struct ffe_frame {
	int frame_no;
	u8 *data;
	struct ffe_frame *next;
};

struct ffe_data {
	int framerate;
	int framecount;
	int width;
	int height;
};

struct ffe_frame *V_BUF;
struct ffe_data F_DATA;
bool I_FLAG;
#endif
