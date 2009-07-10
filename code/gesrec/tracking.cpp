#define NUMS 4

#include "gesrec.h"

//int getPointNum(IplImage* src, 

CvSeq* gesTracking(IplImage* src, CvSeq* seq, CvScalar* s) {
	
	int i = 0;
	double range1, range2, range3, range4;
	CvScalar tempS;
	CvConnectedComp* aComp;
	int seq_num = seq->total;
	CvMemStorage* storage;//��̬�ڴ�
	CvSeq* curr_seq;

	range1 = s->val[1] - 10;
	range2 = s->val[1] + 10;
	range3 = s->val[2] - 10;
	range4 = s->val[2] + 10;

	storage = cvCreateMemStorage(0);
	curr_seq = cvCreateSeq(0, sizeof(CvSeq), sizeof(CvConnectedComp), storage);

	CvRect rect;
	int tempNum = 0;
	int sign = 0;

	while( i < seq_num ) {
		sign = 0;
		aComp = (CvConnectedComp* )cvGetSeqElem(seq, i);
		rect = aComp->rect;
		int tempx = 0;
		int tempy = 0;

		// x ������
		tempx = rect.x - 1;
		tempNum = 0;
		for(int k = rect.y; k < min(src->height, rect.y + rect.height); k++) {
			if(tempx < 0) {
				break;
			}
			tempS = cvGet2D(src, k, tempx);
			if(tempS.val[1] >= range1 && tempS.val[1] <= range2 && 
				tempS.val[2] >= range3 && tempS.val[2] <= range4) {
				tempNum++;
				if(tempNum >= NUMS) {
					rect.x -= 1;
					sign = 1;
					break;
				}
			} else {
				tempNum = 0;
			}
		}
		if(tempNum < NUMS) {
			sign = -1;
		}

		while(rect.x > 0 && sign == 1) {
			tempx = rect.x - 1;
			tempNum = 0;
			for(int k = rect.y; k < min(src->height, rect.y + rect.height); k++) {
				if(tempx < 0) {
					break;
				}
				tempS = cvGet2D(src, k, tempx);
				if(tempS.val[1] >= range1 && tempS.val[1] <= range2 && 
					tempS.val[2] >= range3 && tempS.val[2] <= range4) {
					tempNum++;
					if(tempNum >= NUMS) {
						rect.x -= 1;
						break;
					}
				} else {
					tempNum = 0;
				}
			}
			if(tempNum < NUMS) {
				break;
			}
		}
		while( ( (rect.x+rect.width) < src->width-1 ) && sign == -1) {
			tempx = rect.x + 1;
			tempNum = 0;
			for(int k = rect.y; k < min(src->height, rect.y + rect.height); k++) {
				if(tempx >= src->width-1) {
					break;
				}
				tempS = cvGet2D(src, k, tempx);
				if(tempS.val[1] >= range1 && tempS.val[1] <= range2 && 
					tempS.val[2] >= range3 && tempS.val[2] <= range4) {
					tempNum++;
					if(tempNum >= NUMS) {
						break;
					}
				} else {
					tempNum = 0;
				}
			}
			if(tempNum < NUMS) {
				rect.x -= 1;
			} else {
				break;
			}
		}

		// x ������
		tempx = min( rect.x + rect.width + 1, src->width-1 );
		tempNum = 0;
		for(int k = rect.y; k < min(src->height, rect.y + rect.height); k++) {
			if(tempx >= src->width-1) {
				break;
			}
			tempS = cvGet2D(src, k, tempx);
			if(tempS.val[1] >= range1 && tempS.val[1] <= range2 && 
				tempS.val[2] >= range3 && tempS.val[2] <= range4) {
				tempNum++;
				if(tempNum >= NUMS) {
					rect.width += 1;
					sign = 1;
					break;
				}
			} else {
				tempNum = 0;
			}
		}
		if(tempNum < NUMS) {
			sign = -1;
		}

		while( (rect.x + rect.width) < (src->width-1) && sign == 1) {
			tempx = min( rect.x + rect.width + 1, src->width-1 );
			tempNum = 0;
			for(int k = rect.y; k < min(src->height, rect.y + rect.height); k++) {
				if(tempx >= src->width-1) {
					break;
				}
				tempS = cvGet2D(src, k, tempx);
				if(tempS.val[1] >= range1 && tempS.val[1] <= range2 && 
					tempS.val[2] >= range3 && tempS.val[2] <= range4) {
					tempNum++;
					if(tempNum >= NUMS) {
						rect.width += 1;
						break;
					}
				} else {
					tempNum = 0;
				}
			}
			if(tempNum < NUMS) {
				break;
			}
		}
		while( rect.width > 0 && sign == -1) {
			tempx = max( rect.x + rect.width - 1, 0 );
			tempNum = 0;
			for(int k = rect.y; k < min(src->height, rect.y + rect.height); k++) {
				if(tempx <= 0) {
					break;
				}
				tempS = cvGet2D(src, k, tempx);
				if(tempS.val[1] >= range1 && tempS.val[1] <= range2 && 
					tempS.val[2] >= range3 && tempS.val[2] <= range4) {
					tempNum++;
					if(tempNum >= NUMS) {
						break;
					}
				} else {
					tempNum = 0;
				}
			}
			if(tempNum < NUMS) {
				rect.width -= 1;
			} else {
				break;
			}
		}


		// y ������
		tempy = rect.y - 1;
		tempNum = 0;
		for(int k = rect.x; k < min(src->width, rect.x + rect.width); k++) {
			if(tempy < 0) {
				break;
			}
			tempS = cvGet2D(src, tempy, k);
			if(tempS.val[1] >= range1 && tempS.val[1] <= range2 && 
				tempS.val[2] >= range3 && tempS.val[2] <= range4) {
				tempNum++;
				if(tempNum >= NUMS) {
					rect.y -= 1;
					sign = 1;
					break;
				}
			} else {
				tempNum = 0;
			}
		}
		if(tempNum < NUMS) {
			sign = -1;
		}

		while(rect.y > 0 && sign == 1) {
			tempy = rect.y - 1;
			tempNum = 0;
			for(int k = rect.x; k < min(src->width, rect.x + rect.width); k++) {
				if(tempy < 0) {
					break;
				}
				tempS = cvGet2D(src, tempy, k);
				if(tempS.val[1] >= range1 && tempS.val[1] <= range2 && 
					tempS.val[2] >= range3 && tempS.val[2] <= range4) {
					tempNum++;
					if(tempNum >= NUMS) {
						rect.y -= 1;
						break;
					}
				} else {
					tempNum = 0;
				}
			}
			if(tempNum < NUMS) {
				break;
			}
		}
		while( ( (rect.y+rect.height) < src->height-1 ) && sign == -1) {
			tempy = rect.y + 1;
			tempNum = 0;
			for(int k = rect.x; k < min(src->width, rect.x + rect.width); k++) {
				if(tempy >= src->height-1) {
					break;
				}
				tempS = cvGet2D(src, tempy, k);
				if(tempS.val[1] >= range1 && tempS.val[1] <= range2 && 
					tempS.val[2] >= range3 && tempS.val[2] <= range4) {
					tempNum++;
					if(tempNum >= NUMS) {
						break;
					}
				} else {
					tempNum = 0;
				}
			}
			if(tempNum < NUMS) {
				rect.y -= 1;
			} else {
				break;
			}
		}

		// y ������
		tempy = min( rect.y + rect.height + 1, src->height-1 );
		tempNum = 0;
		for(int k = rect.x; k < min(src->width, rect.x + rect.width); k++) {
			if(tempy >= src->height-1) {
				break;
			}
			tempS = cvGet2D(src, tempy, k);
			if(tempS.val[1] >= range1 && tempS.val[1] <= range2 && 
				tempS.val[2] >= range3 && tempS.val[2] <= range4) {
				tempNum++;
				if(tempNum >= NUMS) {
					rect.height += 1;
					sign = 1;
					break;
				}
			} else {
				tempNum = 0;
			}
		}
		if(tempNum < NUMS) {
			sign = -1;
		}

		while( (rect.y + rect.height) < (src->height-1) && sign == 1) {
			tempy = min( rect.y + rect.height + 1, src->height-1 );
			tempNum = 0;
			for(int k = rect.x; k < min(src->width, rect.x + rect.width); k++) {
				if(tempy >= src->height-1) {
					break;
				}
				tempS = cvGet2D(src, tempy, k);
				if(tempS.val[1] >= range1 && tempS.val[1] <= range2 && 
					tempS.val[2] >= range3 && tempS.val[2] <= range4) {
					tempNum++;
					if(tempNum >= NUMS) {
						rect.height += 1;
						break;
					}
				} else {
					tempNum = 0;
				}
			}
			if(tempNum < NUMS) {
				break;
			}
		}
		while( rect.height > 0 && sign == -1) {
			tempy = max( rect.y + rect.height - 1, 0 );
			tempNum = 0;
			for(int k = rect.x; k < min(src->width, rect.x + rect.width); k++) {
				if(tempy <= 0) {
					break;
				}
				tempS = cvGet2D(src, tempy, k);
				if(tempS.val[1] >= range1 && tempS.val[1] <= range2 && 
					tempS.val[2] >= range3 && tempS.val[2] <= range4) {
					tempNum++;
					if(tempNum >= NUMS) {
						break;
					}
				} else {
					tempNum = 0;
				}
			}
			if(tempNum < NUMS) {
				rect.height -= 1;
			} else {
				break;
			}
		}

		i++;
		aComp->rect = rect;
		cvSeqPush(curr_seq, aComp);
	}

	return curr_seq;
}