/*BRESENHAAM ALGORITHM FOR LINE DRAWING*/
#include<iostream>
#include<stdio.h>
#include<stdlib.h>
#include<math.h>
#include<vector>

using namespace std;

void bhm_line(int, int, int, int);

int x_begin = 0;
int y_begin = 0;
int x_end = 6;
int y_end = 4;
vector<vector<int>> maze;

int main() {

	bhm_line(x_begin, y_begin, x_end, y_end);
	for(unsigned int i = 0; i<maze.size(); i++){
		for(unsigned int j = 0; j<maze[i].size(); j++){
			cout << maze[i][j] << " ";
		}
		cout << endl;
	}
	return 0;
	
}

void bhm_line(int x1, int y1, int x2, int y2) {
	int x,
	y,
	dx,
	dy,
	dx1,
	dy1,
	px,
	py,
	xe,
	ye,
	i;
	dx=x2-x1;
	dy=y2-y1;
	dx1=fabs(dx);
	dy1=fabs(dy);
	px=2*dy1-dx1;
	py=2*dx1-dy1;

	if(dy1<=dx1) {
		if(dx>=0) {
			x=x1;
			y=y1;
			xe=x2;
		}

		else {
			x=x2;
			y=y2;
			xe=x1;
		}

		vector<int> coordenada;
		coordenada.push_back(x);
		coordenada.push_back(y);
		maze.push_back(coordenada);

		for(i=0; x<xe; i++) {
			x=x+1;

			if(px<0) {
				px=px+2*dy1;
			}

			else {
				if((dx<0 && dy<0) || (dx>0 && dy>0)) {
					y=y+1;
				}

				else {
					y=y-1;
				}

				px=px+2*(dy1-dx1);
			}
			
			vector<int> coordenada;
			coordenada.push_back(x);
			coordenada.push_back(y);
			maze.push_back(coordenada);
		}
	}

	else {
		if(dy>=0) {
			x=x1;
			y=y1;
			ye=y2;
		}

		else {
			x=x2;
			y=y2;
			ye=y1;
		}

		vector<int> coordenada;
		coordenada.push_back(x);
		coordenada.push_back(y);
		maze.push_back(coordenada);

		for(i=0; y<ye; i++) {
			y=y+1;

			if(py<=0) {
				py=py+2*dx1;
			}

			else {
				if((dx<0 && dy<0) || (dx>0 && dy>0)) {
					x=x+1;
				}

				else {
					x=x-1;
				}

				py=py+2*(dx1-dy1);
			}

			vector<int> coordenada;
			coordenada.push_back(x);
			coordenada.push_back(y);
			maze.push_back(coordenada);
		}
	}
}