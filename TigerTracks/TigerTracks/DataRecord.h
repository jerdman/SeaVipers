#pragma once
#include <QTime>

struct DataRecord{
	QTime time;
	double dist; // distance to target
	double heading; // heading to target
	int frame; // frame number
	int x; // bounding box x
	int y; // bbox y
	int h; // bb height
	int w; // bb width

	DataRecord(void){
		frame = -1;
		x = -1;
		y = -1;
		w = -1;
		h = -1;
	}
};